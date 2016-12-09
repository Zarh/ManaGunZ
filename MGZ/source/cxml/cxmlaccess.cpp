/*   SCE CONFIDENTIAL                                       */
/*   PlayStation(R)3 Programmer Tool Runtime Library 400.001 */
/*   Copyright (C) 2006 Sony Computer Entertainment Inc.    */
/*   All Rights Reserved.                                   */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "cxmlaccess.h"
#include "cxmlaccess_private.h"

using namespace cxml;

// -------------------------------------------

static inline int padding16( int i )
{
	if( i % 16 == 0 )
		return 0;
	else
		return 16 - i % 16;
}

static inline int align16( int i )
{
	return i + padding16(i);
}

// -------------------------------------------

#if CXML_ENABLE_DEFAULT_ALLOCATOR
static void default_allocator( AllocationType type, void * userdata, void * old_addr, unsigned int required_size, void ** addr, unsigned int * size )
{
	(void)userdata;

	switch(type)
	{
	case AllocationType_Alloc_Tree:
	case AllocationType_Alloc_IDTable:
	case AllocationType_Alloc_StringTable:
	case AllocationType_Alloc_IntArrayTable:
	case AllocationType_Alloc_FloatArrayTable:
	case AllocationType_Alloc_FileTable:
		*addr = realloc(old_addr,required_size);
		*size = required_size;
		return;

	case AllocationType_Free_Tree:
	case AllocationType_Free_IDTable:
	case AllocationType_Free_StringTable:
	case AllocationType_Free_IntArrayTable:
	case AllocationType_Free_FloatArrayTable:
	case AllocationType_Free_FileTable:
		assert(required_size==0);
		assert(addr==NULL);
		assert(size==NULL);
		free(old_addr);
		return;
	}
}
#endif //CXML_ENABLE_DEFAULT_ALLOCATOR

// -------------------------------------------

Header::Header()
	:
	version(0x110),
	tree_offset(0),
	tree_size(0),
	idtable_offset(0),
	idtable_size(0),
	stringtable_offset(0),
	stringtable_size(0),
	intarraytable_offset(0),
	intarraytable_size(0),
	floatarraytable_offset(0),
	floatarraytable_size(0),
	filetable_offset(0),
	filetable_size(0)
{
	memcpy( magic, "CXML", sizeof(magic) );
}

Document::Document()
	:
	access_mode(AccessMode_ReadWrite),
	#if CXML_ENABLE_FILEIO
	fd(NULL),
	#endif //CXML_ENABLE_FILEIO
	tree(NULL),
	tree_capacity(0),
	idtable(NULL),
	idtable_capacity(0),
	stringtable(NULL),
	stringtable_capacity(0),
	intarraytable(NULL),
	intarraytable_capacity(0),
	floatarraytable(NULL),
	floatarraytable_capacity(0),
	filetable(NULL),
	filetable_capacity(0),
	#if CXML_ENABLE_DEFAULT_ALLOCATOR
	allocator(default_allocator),
	#else
	allocator(NULL),
	#endif
	allocator_userdata(NULL)
{
}

Document::~Document()
{
	Clear();
}

#if CXML_ENABLE_FILEIO
int Document::CreateFromFile( const char * filename, AccessMode _access_mode )
{
	int ret;

	// 引数が正しいかチェック
	if( _access_mode!=AccessMode_ReadWrite && _access_mode!=AccessMode_ReadOnly_File )
	{
		return RESULT_ERROR_ACCESS_MODE;
	}

	// これまでオープンされていたファイルを閉じる
	Clear();

	// アクセスモードを設定する
	access_mode = _access_mode;

	// ファイルをオープンする
	fd = fopen( filename, "rb" );
	if(!fd)
	{
		return RESULT_ERROR_CANT_OPEN;
	}

	// ファイルヘッダを読み込む
	ret = fread( &header, 1, sizeof(header), fd );
	if( ret != sizeof(header) )
	{
		return RESULT_ERROR_CANT_READ;
	}

	// ヘッダバージョンをチェック
	if( header.version!=0x0110 && header.version!=0x0100 )
	{
		return RESULT_ERROR_VERSION;
	}

	// intarraytableのサイズが4byteの倍数であることを確認
	if( header.intarraytable_size % sizeof(int) != 0 )
	{
		return RESULT_ERROR_FORMAT;
	}

	// floatarraytableのサイズが4byteの倍数であることを確認
	if( header.floatarraytable_size % sizeof(float) != 0 )
	{
		return RESULT_ERROR_FORMAT;
	}

	// アロケータが登録されていなければエラー
	if( !allocator )
	{
		return RESULT_ERROR_NO_ALLOCATOR;
	}

	// treeを読む
	if(header.tree_size>0)
	{
		void * addr;
		allocator( AllocationType_Alloc_Tree, allocator_userdata, NULL, header.tree_size, &addr, &tree_capacity );
		if(!addr)
		{
			return RESULT_ERROR_CANT_ALLOC;
		}
		tree = (char*)addr;

		ret = fseek( fd, header.tree_offset, SEEK_SET );
		if(ret)
		{
			return RESULT_ERROR_CANT_SEEK;
		}

		ret = fread( (void*)tree, 1, header.tree_size, fd );
		if( ret != header.tree_size )
		{
			return RESULT_ERROR_CANT_READ;
		}
	}

	// idtableを読む
	if(header.idtable_size>0)
	{
		void * addr;
		allocator( AllocationType_Alloc_IDTable, allocator_userdata, NULL, header.idtable_size, &addr, &idtable_capacity );
		if(!addr)
		{
			return RESULT_ERROR_CANT_ALLOC;
		}
		idtable = (char*)addr;

		ret = fseek( fd, header.idtable_offset, SEEK_SET );
		if(ret)
		{
			return RESULT_ERROR_CANT_SEEK;
		}

		ret = fread( (void*)idtable, 1, header.idtable_size, fd );
		if( ret != header.idtable_size )
		{
			return RESULT_ERROR_CANT_READ;
		}
	}

	// stringtableを読む
	if(header.stringtable_size>0)
	{
		void * addr;
		allocator( AllocationType_Alloc_StringTable, allocator_userdata, NULL, header.stringtable_size, &addr, &stringtable_capacity );
		if(!addr)
		{
			return RESULT_ERROR_CANT_ALLOC;
		}
		stringtable = (char*)addr;

		ret = fseek( fd, header.stringtable_offset, SEEK_SET );
		if(ret)
		{
			return RESULT_ERROR_CANT_SEEK;
		}

		ret = fread( (void*)stringtable, 1, header.stringtable_size, fd );
		if( ret != header.stringtable_size )
		{
			return RESULT_ERROR_CANT_READ;
		}

		// stringtableの末尾が0であることを確認
		if( stringtable[header.stringtable_size-1] != 0 )
		{
			return RESULT_ERROR_FORMAT;
		}
	}

	// intarraytableを読む
	if(header.intarraytable_size>0)
	{
		void * addr;
		allocator( AllocationType_Alloc_IntArrayTable, allocator_userdata, NULL, header.intarraytable_size, &addr, &intarraytable_capacity );
		if(!addr)
		{
			return RESULT_ERROR_CANT_ALLOC;
		}
		intarraytable = (int*)addr;

		ret = fseek( fd, header.intarraytable_offset, SEEK_SET );
		if(ret)
		{
			return RESULT_ERROR_CANT_SEEK;
		}

		ret = fread( (void*)intarraytable, 1, header.intarraytable_size, fd );
		if( ret != header.intarraytable_size )
		{
			return RESULT_ERROR_CANT_READ;
		}
	}

	// floatarraytableを読む
	if(header.floatarraytable_size>0)
	{
		void * addr;
		allocator( AllocationType_Alloc_FloatArrayTable, allocator_userdata, NULL, header.floatarraytable_size, &addr, &floatarraytable_capacity );
		if(!addr)
		{
			return RESULT_ERROR_CANT_ALLOC;
		}
		floatarraytable = (float*)addr;

		ret = fseek( fd, header.floatarraytable_offset, SEEK_SET );
		if(ret)
		{
			return RESULT_ERROR_CANT_SEEK;
		}

		ret = fread( (void*)floatarraytable, 1, header.floatarraytable_size, fd );
		if( ret != header.floatarraytable_size )
		{
			return RESULT_ERROR_CANT_READ;
		}
	}

	// filetableを読む
	if(access_mode==AccessMode_ReadWrite && header.filetable_size>0)
	{
		void * addr;
		allocator( AllocationType_Alloc_FileTable, allocator_userdata, NULL, header.filetable_size, &addr, &filetable_capacity );
		if(!addr)
		{
			return RESULT_ERROR_CANT_ALLOC;
		}
		filetable = (char*)addr;

		ret = fseek( fd, header.filetable_offset, SEEK_SET );
		if(ret)
		{
			return RESULT_ERROR_CANT_SEEK;
		}

		ret = fread( (void*)filetable, 1, header.filetable_size, fd );
		if( ret != header.filetable_size )
		{
			return RESULT_ERROR_CANT_READ;
		}

		// AccessMode_ReadWrite のときは、ファイルを開いておく必要がないので閉じる。
		fclose(fd);
		fd = NULL;
	}

	return 0;
}
#endif //CXML_ENABLE_FILEIO

int Document::CreateFromBuffer( const void * buf, unsigned int bufsize, AccessMode _access_mode )
{
	// 引数が正しいかチェック
	if( _access_mode!=AccessMode_ReadWrite && _access_mode!=AccessMode_ReadOnly_Memory )
	{
		return RESULT_ERROR_ACCESS_MODE;
	}

	// メモリを開放する
	Clear();

	// アクセスモードを設定する
	access_mode = _access_mode;

	// ファイルヘッダを読み込む
	if( sizeof(header) > bufsize )
	{
		return RESULT_ERROR_CANT_READ;
	}

	memcpy( &header, buf, sizeof(header) );

	// ヘッダバージョンをチェック
	if( header.version!=0x0110 && header.version!=0x0100 )
	{
		return RESULT_ERROR_VERSION;
	}

	// intarraytableのサイズが4byteの倍数であることを確認
	if( header.intarraytable_size % sizeof(int) != 0 )
	{
		return RESULT_ERROR_FORMAT;
	}

	// floatarraytableのサイズが4byteの倍数であることを確認
	if( header.floatarraytable_size % sizeof(float) != 0 )
	{
		return RESULT_ERROR_FORMAT;
	}

	// AccessMode_ReadWriteモードでアロケータが登録されていなければエラー
	if( access_mode==AccessMode_ReadWrite && !allocator )
	{
		return RESULT_ERROR_NO_ALLOCATOR;
	}

	// treeを読む
	if( header.tree_size > 0 )
	{
		if( header.tree_offset >= (int)bufsize )
		{
			return RESULT_ERROR_CANT_SEEK;
		}

		if( header.tree_offset + header.tree_size > (int)bufsize )
		{
			return RESULT_ERROR_CANT_READ;
		}

		if(access_mode==AccessMode_ReadWrite)
		{
			void * addr;
			allocator( AllocationType_Alloc_Tree, allocator_userdata, NULL, header.tree_size, &addr, &tree_capacity );
			if(!addr)
			{
				return RESULT_ERROR_CANT_ALLOC;
			}
			tree = (char*)addr;

			memcpy( (void*)tree, (const char*)buf + header.tree_offset, header.tree_size );
		}
		else
		{
			tree = (char*)buf + header.tree_offset;
		}
	}

	// idtableを読む
	if( header.idtable_size > 0 )
	{
		if( header.idtable_offset >= (int)bufsize )
		{
			return RESULT_ERROR_CANT_SEEK;
		}

		if( header.idtable_offset + header.idtable_size > (int)bufsize )
		{
			return RESULT_ERROR_CANT_READ;
		}

		if(access_mode==AccessMode_ReadWrite)
		{
			void * addr;
			allocator( AllocationType_Alloc_IDTable, allocator_userdata, NULL, header.idtable_size, &addr, &idtable_capacity );
			if(!addr)
			{
				return RESULT_ERROR_CANT_ALLOC;
			}
			idtable = (char*)addr;

			memcpy( (void*)idtable, (const char*)buf + header.idtable_offset, header.idtable_size );
		}
		else
		{
			idtable = (char*)buf + header.idtable_offset;
		}
	}

	// stringtableを読む
	if( header.stringtable_size > 0 )
	{
		if( header.stringtable_offset >= (int)bufsize )
		{
			return RESULT_ERROR_CANT_SEEK;
		}

		if( header.stringtable_offset + header.stringtable_size > (int)bufsize )
		{
			return RESULT_ERROR_CANT_READ;
		}

		if(access_mode==AccessMode_ReadWrite)
		{
			void * addr;
			allocator( AllocationType_Alloc_StringTable, allocator_userdata, NULL, header.stringtable_size, &addr, &stringtable_capacity );
			if(!addr)
			{
				return RESULT_ERROR_CANT_ALLOC;
			}
			stringtable = (char*)addr;

			memcpy( (void*)stringtable, (const char*)buf + header.stringtable_offset, header.stringtable_size );
		}
		else
		{
			stringtable = (char*)buf + header.stringtable_offset;
		}

		// stringtableの末尾が0であることを確認
		if( stringtable[header.stringtable_size-1] != 0 )
		{
			return RESULT_ERROR_FORMAT;
		}
	}

	// intarraytableを読む
	if( header.intarraytable_size > 0 )
	{
		if( header.intarraytable_offset >= (int)bufsize )
		{
			return RESULT_ERROR_CANT_SEEK;
		}

		if( header.intarraytable_offset + header.intarraytable_size > (int)bufsize )
		{
			return RESULT_ERROR_CANT_READ;
		}

		if(access_mode==AccessMode_ReadWrite)
		{
			void * addr;
			allocator( AllocationType_Alloc_IntArrayTable, allocator_userdata, NULL, header.intarraytable_size, &addr, &intarraytable_capacity );
			if(!addr)
			{
				return RESULT_ERROR_CANT_ALLOC;
			}
			intarraytable = (int*)addr;

			memcpy( (void*)intarraytable, (const char*)buf + header.intarraytable_offset, header.intarraytable_size );
		}
		else
		{
			intarraytable = (int*)((const char*)buf + header.intarraytable_offset);
		}
	}

	// floatarraytableを読む
	if( header.floatarraytable_size > 0 )
	{
		if( header.floatarraytable_offset >= (int)bufsize )
		{
			return RESULT_ERROR_CANT_SEEK;
		}

		if( header.floatarraytable_offset + header.floatarraytable_size > (int)bufsize )
		{
			return RESULT_ERROR_CANT_READ;
		}

		if(access_mode==AccessMode_ReadWrite)
		{
			void * addr;
			allocator( AllocationType_Alloc_FloatArrayTable, allocator_userdata, NULL, header.floatarraytable_size, &addr, &floatarraytable_capacity );
			if(!addr)
			{
				return RESULT_ERROR_CANT_ALLOC;
			}
			floatarraytable = (float*)addr;

			memcpy( (void*)floatarraytable, (const char*)buf + header.floatarraytable_offset, header.floatarraytable_size );
		}
		else
		{
			floatarraytable = (float*)((const char*)buf + header.floatarraytable_offset);
		}

	}

	// filetableを読む
	if( header.filetable_size > 0 )
	{
		if( header.filetable_offset >= (int)bufsize )
		{
			return RESULT_ERROR_CANT_SEEK;
		}

		if( header.filetable_offset + header.filetable_size > (int)bufsize )
		{
			return RESULT_ERROR_CANT_READ;
		}

		if(access_mode==AccessMode_ReadWrite)
		{
			void * addr;
			allocator( AllocationType_Alloc_FileTable, allocator_userdata, NULL, header.filetable_size, &addr, &filetable_capacity );
			if(!addr)
			{
				return RESULT_ERROR_CANT_ALLOC;
			}
			filetable = (char*)addr;

			memcpy( (void*)filetable, (const char*)buf + header.filetable_offset, header.filetable_size );
		}
		else
		{
			filetable = (char*)buf + header.filetable_offset;
		}
	}

	return 0;
}

int Document::Clear()
{
	header = Header();

	if(access_mode!=AccessMode_ReadOnly_Memory)
	{
		// アロケータが登録されていなければエラー
		if( !allocator )
		{
			return RESULT_ERROR_NO_ALLOCATOR;
		}

		if(tree) allocator( AllocationType_Free_Tree, allocator_userdata, (void*)tree, 0, NULL, NULL );
		tree = NULL;
		tree_capacity = 0;

		if(idtable) allocator( AllocationType_Free_IDTable, allocator_userdata, (void*)idtable, 0, NULL, NULL );
		idtable = NULL;
		idtable_capacity = 0;

		if(stringtable) allocator( AllocationType_Free_StringTable, allocator_userdata, (void*)stringtable, 0, NULL, NULL );
		stringtable = NULL;
		stringtable_capacity = 0;

		if(intarraytable) allocator( AllocationType_Free_IntArrayTable, allocator_userdata, (void*)intarraytable, 0, NULL, NULL );
		intarraytable = NULL;
		intarraytable_capacity = 0;

		if(floatarraytable) allocator( AllocationType_Free_FloatArrayTable, allocator_userdata, (void*)floatarraytable, 0, NULL, NULL );
		floatarraytable = NULL;
		floatarraytable_capacity = 0;

		if(filetable) allocator( AllocationType_Free_FileTable, allocator_userdata, (void*)filetable, 0, NULL, NULL );
		filetable = NULL;
		filetable_capacity = 0;
	}

	#if CXML_ENABLE_FILEIO
	if(fd)
	{
		fclose(fd);
		fd = NULL;
	}
	#endif //CXML_ENABLE_FILEIO

	access_mode = AccessMode_ReadWrite;

	return 0;
}

#if CXML_ENABLE_MODIFY
int Document::GetSize() const
{
	int size = 0;
	size += align16( sizeof(header) );
	size += align16( header.tree_size );
	size += align16( header.idtable_size );
	size += align16( header.stringtable_size );
	size += align16( header.intarraytable_size );
	size += align16( header.floatarraytable_size );
	size += align16( header.filetable_size );
	return size;
}
#endif //CXML_ENABLE_MODIFY

#if CXML_ENABLE_MODIFY
int Document::Write( Writer writer, void * userdata )
{
	if( access_mode!=AccessMode_ReadWrite
	 && access_mode!=AccessMode_ReadOnly_Memory )
	{
		return RESULT_ERROR_ACCESS_MODE;
	}

	int ret;

	char zero[16] = { 0 };

	SettleHeader();

	// ファイルヘッダを書き込む
	ret = writer( &header, sizeof(header), userdata );
	if( ret != sizeof(header) )
	{
		return ret;
	}

	// 16byteアライン
	ret = writer( zero, padding16( sizeof(header) ), userdata );
	if( ret != padding16( sizeof(header) ) )
	{
		return ret;
	}

	// treeを書き込む
	ret = writer( (void*)tree, header.tree_size, userdata );
	if( ret != header.tree_size )
	{
		return ret;
	}

	// 16byteアライン
	ret = writer( zero, padding16( header.tree_size ), userdata );
	if( ret != padding16( header.tree_size ) )
	{
		return ret;
	}

	// idtableを書き込む
	ret = writer( (void*)idtable, header.idtable_size, userdata );
	if( ret != header.idtable_size )
	{
		return ret;
	}

	// 16byteアライン
	ret = writer( zero, padding16( header.idtable_size ), userdata );
	if( ret != padding16( header.idtable_size ) )
	{
		return ret;
	}

	// stringtableを書き込む
	ret = writer( (void*)stringtable, header.stringtable_size, userdata );
	if( ret != header.stringtable_size )
	{
		return ret;
	}

	// 16byteアライン
	ret = writer( zero, padding16( header.stringtable_size ), userdata );
	if( ret != padding16( header.stringtable_size ) )
	{
		return ret;
	}

	// intarraytableを書き込む
	ret = writer( (void*)intarraytable, header.intarraytable_size, userdata );
	if( ret != header.intarraytable_size )
	{
		return ret;
	}

	// 16byteアライン
	ret = writer( zero, padding16( header.intarraytable_size ), userdata );
	if( ret != padding16( header.intarraytable_size ) )
	{
		return ret;
	}

	// floatarraytableを読む
	ret = writer( (void*)floatarraytable, header.floatarraytable_size, userdata );
	if( ret != header.floatarraytable_size )
	{
		return ret;
	}

	// 16byteアライン
	ret = writer( zero, padding16( header.floatarraytable_size ), userdata );
	if( ret != padding16( header.floatarraytable_size ) )
	{
		return ret;
	}

	// filetableを読む
	ret = writer( (void*)filetable, header.filetable_size, userdata );
	if( ret != header.filetable_size )
	{
		return ret;
	}

	// 16byteアライン
	ret = writer( zero, padding16( header.filetable_size ), userdata );
	if( ret != padding16( header.filetable_size ) )
	{
		return ret;
	}

	return 0;
}
#endif //CXML_ENABLE_MODIFY

#if CXML_ENABLE_FILEIO
#if CXML_ENABLE_MODIFY
static int _FileWriter( const void * addr, unsigned int size, void * userdata )
{
	if( fwrite( addr, 1, size, (FILE*)userdata ) != size )
	{
		return RESULT_ERROR_CANT_WRITE;
	}
	return size;
}

int Document::WriteToFile( const char * filename )
{
	int ret;

	// ファイルをオープンする
	FILE * fdo = fopen( filename, "wb" );
	if(!fdo)
	{
		return RESULT_ERROR_CANT_OPEN;
	}

	ret = Write( _FileWriter, fdo );

	fclose(fdo);

	return ret;
}
#endif //CXML_ENABLE_MODIFY
#endif //CXML_ENABLE_FILEIO

#if CXML_ENABLE_MODIFY
static int _BufferWriter( const void * addr, unsigned int size, void * userdata )
{
	char * dst = *(char**)userdata;

	memcpy( dst, addr, size );

	*(char**)userdata += size;

	return size;
}

int Document::WriteToBuffer( void * buf, unsigned int bufsize )
{
	if( header.filetable_offset + align16( header.filetable_size ) > (int)bufsize )
	{
		return RESULT_ERROR_CANT_WRITE;
	}

	return Write( _BufferWriter, &buf );
}
#endif //CXML_ENABLE_MODIFY

Element Document::GetDocumentElement()
{
	if( IsValidElement(0) )
	{
		return Element( this, 0 );
	}
	return Element();
}

void Document::GetHeaderMagic( char buf[4] ) const
{
	memcpy( buf, header.magic, sizeof(buf) );
}

#if CXML_ENABLE_MODIFY
int Document::SetHeaderMagic( const char buf[4] )
{
	if( access_mode != AccessMode_ReadWrite )
	{
		return RESULT_ERROR_ACCESS_MODE;
	}

	memcpy( header.magic, buf, sizeof(header.magic) );

	return 0;
}
#endif //CXML_ENABLE_MODIFY

#if CXML_ENABLE_MODIFY
int Document::CreateElement( const char * name, int attr_num, Element * element )
{
	if( access_mode != AccessMode_ReadWrite )
	{
		return RESULT_ERROR_ACCESS_MODE;
	}

	// アロケータが登録されていなければエラー
	if( !allocator )
	{
		return RESULT_ERROR_NO_ALLOCATOR;
	}

	unsigned int element_size = sizeof(ElementBin) + sizeof(AttributeBin) * attr_num;

	// バッファサイズが十分でないときは再確保する
	if( header.tree_size + element_size > tree_capacity )
	{
		unsigned int required_tree_capacity = header.tree_size + element_size;

		void * new_tree;
		unsigned int new_tree_capacity;
		allocator( AllocationType_Alloc_Tree, allocator_userdata, (void*)tree, required_tree_capacity, &new_tree, &new_tree_capacity );
		if(!new_tree)
		{
			return RESULT_ERROR_CANT_ALLOC;
		}

		tree = (char*)new_tree;
		tree_capacity = new_tree_capacity;
	}

	int offset = header.tree_size;
	header.tree_size += element_size;

	int name_id = RegisterString( name, strlen(name) );
	if(name_id<0)
	{
		return name_id;
	}

	ElementBin * bin = (ElementBin*)&( tree[offset] );
	bin->name = name_id;
	bin->attr_num = attr_num;
	bin->parent = -1;
	bin->prev = -1;
	bin->next = -1;
	bin->first_child = -1;
	bin->last_child = -1;

	// 属性をNone型で初期化する
	for( int i=0 ; i<attr_num ; i++ )
	{
		AttributeBin * attr_bin = (AttributeBin*)&( tree[ offset + sizeof(ElementBin) + sizeof(AttributeBin)*i ] );

		attr_bin->name = -1;
		attr_bin->type = AttributeType_None;
		attr_bin->s.offset = 0;
		attr_bin->s.len = 0;
	}

	*element = Element( this, offset );

	return 0;
}
#endif //CXML_ENABLE_MODIFY

bool Document::IsValidElement( int offset ) const
{
	if( offset<0 || offset+sizeof(ElementBin)>(unsigned int)header.tree_size )
		return false;

	ElementBin * bin = (ElementBin*)&( tree[offset] );

	if( bin->attr_num<0 || offset+sizeof(ElementBin)+sizeof(AttributeBin)*bin->attr_num>(unsigned int)header.tree_size )
		return false;

	return true;
}

bool Document::IsValidAttribute( int offset ) const
{
	if( offset<0 || offset+sizeof(AttributeBin)>(unsigned int)header.tree_size )
		return false;
	return true;
}

const char * Document::GetIDString( int offset ) const
{
	if( offset<0 || offset>=header.idtable_size )
		return NULL;

	IDBin * id_bin = (IDBin*)&(idtable[offset]);

	return id_bin->id;
}

const char * Document::GetString( int offset ) const
{
	if( offset<0 || offset>=header.stringtable_size )
		return NULL;

	return &(stringtable[offset]);
}

const int * Document::GetIntArray( int offset, unsigned int num ) const
{
	if( offset<0 || (offset+num)*sizeof(int)>(unsigned int)header.intarraytable_size )
		return NULL;

	return &(intarraytable[offset]);
}

const float * Document::GetFloatArray( int offset, unsigned int num ) const
{
	if( offset<0 || (offset+num)*sizeof(float)>(unsigned int)header.floatarraytable_size )
		return NULL;

	return &(floatarraytable[offset]);
}

#if CXML_ENABLE_FILEIO
int Document::LoadFile( void * buf, unsigned int bufsize, int offset, unsigned int size ) const
{
	int ret;

	if( access_mode!=AccessMode_ReadOnly_File )
	{
		return RESULT_ERROR_ACCESS_MODE;
	}

	if( bufsize<size )
	{
		return RESULT_ERROR_NOT_ENOUGH_BUF;
	}

	ret = fseek( fd, header.filetable_offset + offset, SEEK_SET );
	if(ret)
	{
		return RESULT_ERROR_CANT_SEEK;
	}

	ret = fread( buf, 1, size, fd );
	if( ret != (int)size )
	{
		return RESULT_ERROR_CANT_READ;
	}

	return 0;
}
#endif //CXML_ENABLE_FILEIO

const void * Document::GetFileAddr( int offset, unsigned int size ) const
{
	if( access_mode!=AccessMode_ReadWrite
	 && access_mode!=AccessMode_ReadOnly_Memory )
	{
		return NULL;
	}

	if( ! filetable )
	{
		return NULL;
	}

	if( offset >= header.filetable_size )
	{
		return NULL;
	}

	if( (int)(offset + size) > header.filetable_size )
	{
		return NULL;
	}

	return filetable + offset;
}

#if CXML_ENABLE_MODIFY
int Document::RegisterString( const char * str, unsigned int len )
{
	// アロケータが登録されていなければエラー
	if( !allocator )
	{
		return RESULT_ERROR_NO_ALLOCATOR;
	}

	// 既に登録済みの文字列に同じものがあれば、それを返す
	for( int i=0 ; i<header.stringtable_size ; i+=strlen( &stringtable[i] )+1 )
	{
		if( stringtable[i]==str[0] && strcmp( &stringtable[i], str )==0 )
		{
			return i;
		}
	}

	// バッファサイズが十分でないときは再確保する
	if( header.stringtable_size + len+1 > stringtable_capacity )
	{
		unsigned int required_stringtable_capacity = header.stringtable_size + len+1;

		void * new_stringtable;
		unsigned int new_stringtable_capacity;
		allocator( AllocationType_Alloc_StringTable, allocator_userdata, (void*)stringtable, required_stringtable_capacity, &new_stringtable, &new_stringtable_capacity );
		if(!new_stringtable)
		{
			return RESULT_ERROR_CANT_ALLOC;
		}

		stringtable = (char*)new_stringtable;
		stringtable_capacity = new_stringtable_capacity;
	}

	int offset = header.stringtable_size;
	header.stringtable_size += len+1;

	memcpy( &stringtable[offset], str, len+1 );

	return offset;
}
#endif //CXML_ENABLE_MODIFY

#if CXML_ENABLE_MODIFY
int Document::RegisterIntArray( const int * addr, unsigned int num )
{
	// アロケータが登録されていなければエラー
	if( !allocator )
	{
		return RESULT_ERROR_NO_ALLOCATOR;
	}

	// バッファサイズが十分でないときは再確保する
	if( header.intarraytable_size + sizeof(int)*num > intarraytable_capacity )
	{
		unsigned int required_intarraytable_capacity = header.intarraytable_size + sizeof(int)*num;

		void * new_intarraytable;
		unsigned int new_intarraytable_capacity;
		allocator( AllocationType_Alloc_IntArrayTable, allocator_userdata, (void*)intarraytable, required_intarraytable_capacity, &new_intarraytable, &new_intarraytable_capacity );
		if(!new_intarraytable)
		{
			return RESULT_ERROR_CANT_ALLOC;
		}

		intarraytable = (int*)new_intarraytable;
		intarraytable_capacity = new_intarraytable_capacity;
	}

	int offset = header.intarraytable_size / sizeof(int);
	header.intarraytable_size += sizeof(int)*num;

	memcpy( &intarraytable[offset], addr, sizeof(int)*num );

	return offset;
}
#endif //CXML_ENABLE_MODIFY

#if CXML_ENABLE_MODIFY
int Document::RegisterFloatArray( const float * addr, unsigned int num )
{
	// アロケータが登録されていなければエラー
	if( !allocator )
	{
		return RESULT_ERROR_NO_ALLOCATOR;
	}

	// バッファサイズが十分でないときは再確保する
	if( header.floatarraytable_size + sizeof(float)*num > floatarraytable_capacity )
	{
		unsigned int required_floatarraytable_capacity = header.floatarraytable_size + sizeof(float)*num;

		void * new_floatarraytable;
		unsigned int new_floatarraytable_capacity;
		allocator( AllocationType_Alloc_FloatArrayTable, allocator_userdata, (void*)floatarraytable, required_floatarraytable_capacity, &new_floatarraytable, &new_floatarraytable_capacity );
		if(!new_floatarraytable)
		{
			return RESULT_ERROR_CANT_ALLOC;
		}

		floatarraytable = (float*)new_floatarraytable;
		floatarraytable_capacity = new_floatarraytable_capacity;
	}

	int offset = header.floatarraytable_size / sizeof(float);
	header.floatarraytable_size += sizeof(float)*num;

	memcpy( &floatarraytable[offset], addr, sizeof(float)*num );

	return offset;
}
#endif //CXML_ENABLE_MODIFY

#if CXML_ENABLE_MODIFY
int Document::RegisterFile( const void * addr, unsigned int size, File * file )
{
	if( access_mode != AccessMode_ReadWrite )
	{
		return RESULT_ERROR_ACCESS_MODE;
	}

	unsigned int size16 = align16(size);

	// アロケータが登録されていなければエラー
	if( !allocator )
	{
		return RESULT_ERROR_NO_ALLOCATOR;
	}

	// バッファサイズが十分でないときは再確保する
	if( header.filetable_size + size16 > filetable_capacity )
	{
		unsigned int required_filetable_capacity = header.filetable_size + size16;

		void * new_filetable;
		unsigned int new_filetable_capacity;
		allocator( AllocationType_Alloc_FileTable, allocator_userdata, (void*)filetable, required_filetable_capacity, &new_filetable, &new_filetable_capacity );
		if(!new_filetable)
		{
			return RESULT_ERROR_CANT_ALLOC;
		}

		filetable = (char*)new_filetable;
		filetable_capacity = new_filetable_capacity;
	}

	int offset = header.filetable_size;
	header.filetable_size += size16;

	memcpy( &filetable[offset], addr, size );
	memset( &filetable[offset+size], 0, size16-size );

	*file = File( this, offset, size );

	return 0;
}
#endif //CXML_ENABLE_MODIFY

#if CXML_ENABLE_MODIFY
int Document::RegisterID( const char * id, int entity_offset )
{
	// アロケータが登録されていなければエラー
	if( !allocator )
	{
		return RESULT_ERROR_NO_ALLOCATOR;
	}

	unsigned int len = strlen(id);
	unsigned int size = sizeof(IDBin)+len+1;

	// 既に登録済みの文字列に同じものがあれば、それを使う
	for( int i=0 ; i<header.idtable_size ; )
	{
		IDBin * id_bin = (IDBin*)&(idtable[i]);

		if( id_bin->id[0]==id[0] && strcmp( id_bin->id, id )==0 )
		{
			if( entity_offset >= 0 )
			{
				id_bin->entity_offset = entity_offset;
			}

			return i;
		}

		i += sizeof(IDBin) + strlen(id_bin->id)+1;
	}

	// バッファサイズが十分でないときは再確保する
	if( header.idtable_size + size > idtable_capacity )
	{
		unsigned int required_idtable_capacity = header.idtable_size + size;

		void * new_idtable;
		unsigned int new_idtable_capacity;
		allocator( AllocationType_Alloc_IDTable, allocator_userdata, (void*)idtable, required_idtable_capacity, &new_idtable, &new_idtable_capacity );
		if(!new_idtable)
		{
			return RESULT_ERROR_CANT_ALLOC;
		}

		idtable = (char*)new_idtable;
		idtable_capacity = new_idtable_capacity;
	}

	int offset = header.idtable_size;
	header.idtable_size += size;

	IDBin * id_bin = (IDBin*)&(idtable[offset]);
	id_bin->entity_offset = entity_offset;
	memcpy( id_bin->id, id, len+1 );

	return offset;
}
#endif //CXML_ENABLE_MODIFY

#if CXML_ENABLE_MODIFY
void Document::SettleHeader()
{
	header.version = 0x110;
	header.tree_offset = align16( sizeof(header) );
	header.idtable_offset = header.tree_offset + align16( header.tree_size );
	header.stringtable_offset = header.idtable_offset + align16( header.idtable_size );
	header.intarraytable_offset = header.stringtable_offset + align16( header.stringtable_size );
	header.floatarraytable_offset = header.intarraytable_offset + align16( header.intarraytable_size );
	header.filetable_offset = header.floatarraytable_offset + align16( header.floatarraytable_size );
}
#endif //CXML_ENABLE_MODIFY

Element Element::GetParent() const
{
	if(doc)
	{
		assert( doc->IsValidElement(offset) );

		ElementBin * bin = (ElementBin*)&( doc->tree[offset] );

		if( doc->IsValidElement(bin->parent) )
		{
			return Element( doc, bin->parent );
		}
	}

	return Element();
}

Element Element::GetPreviousSibling() const
{
	if(doc)
	{
		assert( doc->IsValidElement(offset) );

		ElementBin * bin = (ElementBin*)&( doc->tree[offset] );

		if( doc->IsValidElement(bin->prev) )
		{
			return Element( doc, bin->prev );
		}
	}

	return Element();
}

Element Element::GetNextSibling() const
{
	if(doc)
	{
		assert( doc->IsValidElement(offset) );

		ElementBin * bin = (ElementBin*)&( doc->tree[offset] );

		if( doc->IsValidElement(bin->next) )
		{
			return Element( doc, bin->next );
		}
	}

	return Element();
}

Element Element::GetFirstChild() const
{
	if(doc)
	{
		assert( doc->IsValidElement(offset) );

		ElementBin * bin = (ElementBin*)&( doc->tree[offset] );

		if( doc->IsValidElement(bin->first_child) )
		{
			return Element( doc, bin->first_child );
		}
	}

	return Element();
}

Element Element::GetLastChild() const
{
	if(doc)
	{
		assert( doc->IsValidElement(offset) );

		ElementBin * bin = (ElementBin*)&( doc->tree[offset] );

		if( doc->IsValidElement(bin->last_child) )
		{
			return Element( doc, bin->last_child );
		}
	}

	return Element();
}

const char * Element::GetName() const
{
	if(doc)
	{
		assert( doc->IsValidElement(offset) );

		ElementBin * bin = (ElementBin*)&( doc->tree[offset] );

		return doc->GetString(bin->name);
	}

	return NULL;
}

int Element::NumAttribute() const
{
	if(doc)
	{
		assert( doc->IsValidElement(offset) );

		ElementBin * bin = (ElementBin*)&( doc->tree[offset] );

		return bin->attr_num;
	}

	return 0;
}

int Element::GetAttribute( int index, Attribute * attr ) const
{
	if(doc)
	{
		assert( doc->IsValidElement(offset) );

		ElementBin * element_bin = (ElementBin*)&( doc->tree[offset] );

		if( index < element_bin->attr_num )
		{
			*attr = Attribute( doc, offset, offset + sizeof(ElementBin) + sizeof(AttributeBin)*index );
			return 0;
		}
	}

	return RESULT_ERROR_INVALID_NODE;
}

int Element::GetAttribute( const char * name, Attribute * attr ) const
{
	if(doc)
	{
		assert( doc->IsValidElement(offset) );

		ElementBin * element_bin = (ElementBin*)&( doc->tree[offset] );

		for( int i=0 ; i<element_bin->attr_num ; i++ )
		{
			AttributeBin * attr_bin = (AttributeBin*)&( doc->tree[ offset + sizeof(ElementBin) + sizeof(AttributeBin)*i ] );

			const char * attr_name = doc->GetString(attr_bin->name);

			if( attr_name && attr_name[0]==name[0] && strcmp(attr_name,name)==0 )
			{
				*attr = Attribute( doc, offset, offset + sizeof(ElementBin) + sizeof(AttributeBin)*i );
				return 0;
			}
		}

		return RESULT_ERROR_NOT_EXIST;
	}

	return RESULT_ERROR_INVALID_NODE;
}

#if CXML_ENABLE_MODIFY
int Element::AppendChild( Element & child )
{
	if(doc)
	{
		if( doc->access_mode != AccessMode_ReadWrite )
		{
			return RESULT_ERROR_ACCESS_MODE;
		}

		assert( doc->IsValidElement(offset) );
		assert( doc->IsValidElement(child.offset) );

		ElementBin * bin = (ElementBin*)&( doc->tree[offset] );
		ElementBin * child_bin = (ElementBin*)&( doc->tree[child.offset] );

		// ルート要素または既にツリーに挿入されている要素を、再び他の場所に挿入しなおすことを禁止する
		if( child.offset==0
		 || child_bin->parent>=0 )
		{
			return RESULT_ERROR_CANT_MODIFY;
		}

		int old_last_child = bin->last_child;

		if(bin->first_child<0) bin->first_child = child.offset;
		bin->last_child = child.offset;
		child_bin->parent = offset;
		child_bin->prev = old_last_child;

		if( doc->IsValidElement(old_last_child) )
		{
			ElementBin * old_last_child_bin = (ElementBin*)&( doc->tree[old_last_child] );
			old_last_child_bin->next = child.offset;
		}

		return 0;
	}

	return RESULT_ERROR_INVALID_NODE;
}
#endif //CXML_ENABLE_MODIFY

#if CXML_ENABLE_MODIFY
int Element::InsertBefore( Element & child, Element & ref )
{
	if(doc)
	{
		if( doc->access_mode != AccessMode_ReadWrite )
		{
			return RESULT_ERROR_ACCESS_MODE;
		}

		assert( doc->IsValidElement(offset) );
		assert( doc->IsValidElement(child.offset) );
		assert( doc->IsValidElement(ref.offset) );

		ElementBin * bin = (ElementBin*)&( doc->tree[offset] );
		ElementBin * child_bin = (ElementBin*)&( doc->tree[child.offset] );
		ElementBin * ref_bin = (ElementBin*)&( doc->tree[ref.offset] );

		// ルート要素または既にツリーに挿入されている要素を、再び他の場所に挿入しなおすことを禁止する
		if( child.offset==0
		 || child_bin->parent>=0 )
		{
			return RESULT_ERROR_CANT_MODIFY;
		}

		if( ref_bin->prev<0 ) bin->first_child = child.offset;
		child_bin->parent = offset;
		child_bin->prev = ref_bin->prev;
		child_bin->next = ref.offset;

		if( doc->IsValidElement(child_bin->prev) )
		{
			ElementBin * prev_bin = (ElementBin*)&( doc->tree[child_bin->prev] );
			prev_bin->next = child.offset;
		}

		ref_bin->prev = child.offset;

		return 0;
	}

	return RESULT_ERROR_INVALID_NODE;
}
#endif //CXML_ENABLE_MODIFY

const char * Attribute::GetName() const
{
	if(doc)
	{
		assert( doc->IsValidAttribute(offset) );

		AttributeBin * attr_bin = (AttributeBin*)&( doc->tree[offset] );

		return doc->GetString(attr_bin->name);
	}

	return NULL;
}

#if CXML_ENABLE_MODIFY
int Attribute::SetName( const char * name )
{
	if(doc)
	{
		if( doc->access_mode != AccessMode_ReadWrite )
		{
			return RESULT_ERROR_ACCESS_MODE;
		}

		assert( doc->IsValidAttribute(offset) );

		AttributeBin * attr_bin = (AttributeBin*)&( doc->tree[offset] );

		int name_id = doc->RegisterString( name, strlen(name) );
		if(name_id<0)
		{
			return name_id;
		}

		attr_bin->name = name_id;

		return 0;
	}

	return RESULT_ERROR_INVALID_NODE;
}
#endif //CXML_ENABLE_MODIFY

AttributeType Attribute::GetType() const
{
	if(doc)
	{
		assert( doc->IsValidAttribute(offset) );

		AttributeBin * attr_bin = (AttributeBin*)&( doc->tree[offset] );

		return (AttributeType)attr_bin->type;
	}

	return AttributeType_None;
}

int Attribute::GetInt( int * value ) const
{
	if(doc)
	{
		assert( doc->IsValidAttribute(offset) );

		AttributeBin * attr_bin = (AttributeBin*)&( doc->tree[offset] );

		if( attr_bin->type!=AttributeType_Int )
			return RESULT_ERROR_TYPE;

		*value = attr_bin->i;
		return 0;
	}

	return RESULT_ERROR_INVALID_NODE;
}

#if CXML_ENABLE_MODIFY
int Attribute::SetInt( int value )
{
	if(doc)
	{
		if( doc->access_mode != AccessMode_ReadWrite )
		{
			return RESULT_ERROR_ACCESS_MODE;
		}

		assert( doc->IsValidAttribute(offset) );

		AttributeBin * attr_bin = (AttributeBin*)&( doc->tree[offset] );

		attr_bin->type = AttributeType_Int;
		attr_bin->i = value;

		return 0;
	}

	return RESULT_ERROR_INVALID_NODE;
}
#endif //CXML_ENABLE_MODIFY

int Attribute::GetFloat( float * value ) const
{
	if(doc)
	{
		assert( doc->IsValidAttribute(offset) );

		AttributeBin * attr_bin = (AttributeBin*)&( doc->tree[offset] );

		if( attr_bin->type!=AttributeType_Float )
			return RESULT_ERROR_TYPE;

		*value = attr_bin->f;
		return 0;
	}

	return RESULT_ERROR_INVALID_NODE;
}

#if CXML_ENABLE_MODIFY
int Attribute::SetFloat( float value )
{
	if(doc)
	{
		if( doc->access_mode != AccessMode_ReadWrite )
		{
			return RESULT_ERROR_ACCESS_MODE;
		}

		assert( doc->IsValidAttribute(offset) );

		AttributeBin * attr_bin = (AttributeBin*)&( doc->tree[offset] );

		attr_bin->type = AttributeType_Float;
		attr_bin->f = value;

		return 0;
	}

	return RESULT_ERROR_INVALID_NODE;
}
#endif //CXML_ENABLE_MODIFY

int Attribute::GetString( const char ** value, unsigned int * len ) const
{
	if(doc)
	{
		assert( doc->IsValidAttribute(offset) );

		AttributeBin * attr_bin = (AttributeBin*)&( doc->tree[offset] );

		if( attr_bin->type!=AttributeType_String )
			return RESULT_ERROR_TYPE;

		*value = doc->GetString(attr_bin->s.offset);

		if(*value==NULL)
			return RESULT_ERROR_INVALID_NODE;

		if((*value)[attr_bin->s.len]!=0)
			return RESULT_ERROR_FORMAT;

		*len = attr_bin->s.len;

		return 0;
	}

	return RESULT_ERROR_INVALID_NODE;
}

#if CXML_ENABLE_MODIFY
int Attribute::SetString( const char * value )
{
	if(doc)
	{
		if( doc->access_mode != AccessMode_ReadWrite )
		{
			return RESULT_ERROR_ACCESS_MODE;
		}

		assert( doc->IsValidAttribute(offset) );

		AttributeBin * attr_bin = (AttributeBin*)&( doc->tree[offset] );

		attr_bin->type = AttributeType_String;

		unsigned int len = strlen(value);

		int str_id = doc->RegisterString( value, len );
		if(str_id<0)
		{
			return str_id;
		}

		attr_bin->s.offset = str_id;
		attr_bin->s.len = len;

		return 0;
	}

	return RESULT_ERROR_INVALID_NODE;
}
#endif //CXML_ENABLE_MODIFY

int Attribute::GetIntArray( const int ** addr, unsigned int * num ) const
{
	if(doc)
	{
		assert( doc->IsValidAttribute(offset) );

		AttributeBin * attr_bin = (AttributeBin*)&( doc->tree[offset] );

		if( attr_bin->type!=AttributeType_IntArray )
			return RESULT_ERROR_TYPE;

		*addr = doc->GetIntArray( attr_bin->ia.offset, attr_bin->ia.num );
		if(*addr==NULL)
			return RESULT_ERROR_INVALID_NODE;
		*num = attr_bin->ia.num;
		return 0;
	}

	return RESULT_ERROR_INVALID_NODE;
}

#if CXML_ENABLE_MODIFY
int Attribute::SetIntArray( const int * addr, unsigned int num )
{
	if(doc)
	{
		if( doc->access_mode != AccessMode_ReadWrite )
		{
			return RESULT_ERROR_ACCESS_MODE;
		}

		assert( doc->IsValidAttribute(offset) );

		AttributeBin * attr_bin = (AttributeBin*)&( doc->tree[offset] );

		attr_bin->type = AttributeType_IntArray;

		int id = doc->RegisterIntArray( addr, num );
		if(id<0)
		{
			return id;
		}

		attr_bin->ia.offset = id;
		attr_bin->ia.num = num;

		return 0;
	}

	return RESULT_ERROR_INVALID_NODE;
}
#endif //CXML_ENABLE_MODIFY

int Attribute::GetFloatArray( const float ** addr, unsigned int * num ) const
{
	if(doc)
	{
		assert( doc->IsValidAttribute(offset) );

		AttributeBin * attr_bin = (AttributeBin*)&( doc->tree[offset] );

		if( attr_bin->type!=AttributeType_FloatArray )
			return RESULT_ERROR_TYPE;

		*addr = doc->GetFloatArray( attr_bin->fa.offset, attr_bin->fa.num );
		if(*addr==NULL)
			return RESULT_ERROR_INVALID_NODE;
		*num = attr_bin->fa.num;
		return 0;
	}

	return RESULT_ERROR_INVALID_NODE;
}

#if CXML_ENABLE_MODIFY
int Attribute::SetFloatArray( const float * addr, unsigned int num )
{
	if(doc)
	{
		if( doc->access_mode != AccessMode_ReadWrite )
		{
			return RESULT_ERROR_ACCESS_MODE;
		}

		assert( doc->IsValidAttribute(offset) );

		AttributeBin * attr_bin = (AttributeBin*)&( doc->tree[offset] );

		attr_bin->type = AttributeType_FloatArray;

		int id = doc->RegisterFloatArray( addr, num );
		if(id<0)
		{
			return id;
		}

		attr_bin->fa.offset = id;
		attr_bin->fa.num = num;

		return 0;
	}

	return RESULT_ERROR_INVALID_NODE;
}
#endif //CXML_ENABLE_MODIFY

int Attribute::GetFile( class File * file ) const
{
	if(doc)
	{
		assert( doc->IsValidAttribute(offset) );

		AttributeBin * attr_bin = (AttributeBin*)&( doc->tree[offset] );

		if( attr_bin->type!=AttributeType_File )
			return RESULT_ERROR_TYPE;

		*file = File( doc, attr_bin->file.offset, attr_bin->file.size );
		return 0;
	}

	return RESULT_ERROR_INVALID_NODE;
}

#if CXML_ENABLE_MODIFY
int Attribute::SetFile( const File & file )
{
	if(doc)
	{
		if( doc->access_mode != AccessMode_ReadWrite )
		{
			return RESULT_ERROR_ACCESS_MODE;
		}

		assert( doc->IsValidAttribute(offset) );

		AttributeBin * attr_bin = (AttributeBin*)&( doc->tree[offset] );

		attr_bin->type = AttributeType_File;
		attr_bin->file.offset = file.offset;
		attr_bin->file.size = file.size;

		return 0;
	}

	return RESULT_ERROR_INVALID_NODE;
}
#endif //CXML_ENABLE_MODIFY

int Attribute::GetID( const char ** value ) const
{
	if(doc)
	{
		assert( doc->IsValidAttribute(offset) );

		AttributeBin * attr_bin = (AttributeBin*)&( doc->tree[offset] );

		if( attr_bin->type!=AttributeType_ID )
			return RESULT_ERROR_TYPE;

		*value = doc->GetIDString(attr_bin->id);
		return 0;
	}

	return RESULT_ERROR_INVALID_NODE;
}

#if CXML_ENABLE_MODIFY
int Attribute::SetID( const char * value )
{
	if(doc)
	{
		if( doc->access_mode != AccessMode_ReadWrite )
		{
			return RESULT_ERROR_ACCESS_MODE;
		}

		assert( doc->IsValidAttribute(offset) );

		AttributeBin * attr_bin = (AttributeBin*)&( doc->tree[offset] );

		attr_bin->type = AttributeType_ID;

		int id = doc->RegisterID(value,element_offset);
		if(id<0)
		{
			return id;
		}

		attr_bin->id = id;

		return 0;
	}

	return RESULT_ERROR_INVALID_NODE;
}
#endif //CXML_ENABLE_MODIFY

int Attribute::GetIDRef( const char ** value, Element * entity ) const
{
	if(doc)
	{
		assert( doc->IsValidAttribute(offset) );

		AttributeBin * attr_bin = (AttributeBin*)&( doc->tree[offset] );

		if( attr_bin->type!=AttributeType_IDRef )
			return RESULT_ERROR_TYPE;

		*value = doc->GetIDString(attr_bin->idref);

		IDBin * id_bin = (IDBin*)&(doc->idtable[attr_bin->idref]);

		if( doc->IsValidElement(id_bin->entity_offset) )
			*entity = Element( doc, id_bin->entity_offset );
		else
			*entity = Element();

		return 0;
	}

	return RESULT_ERROR_INVALID_NODE;
}

#if CXML_ENABLE_MODIFY
int Attribute::SetIDRef( const char * value )
{
	if(doc)
	{
		if( doc->access_mode != AccessMode_ReadWrite )
		{
			return RESULT_ERROR_ACCESS_MODE;
		}

		assert( doc->IsValidAttribute(offset) );

		AttributeBin * attr_bin = (AttributeBin*)&( doc->tree[offset] );

		attr_bin->type = AttributeType_IDRef;

		int id = doc->RegisterID(value,-1);
		if(id<0)
		{
			return id;
		}

		attr_bin->id = id;

		return 0;
	}

	return RESULT_ERROR_INVALID_NODE;
}
#endif //CXML_ENABLE_MODIFY

#if CXML_ENABLE_FILEIO
int File::Load( void * buf, unsigned int bufsize ) const
{
	if(doc)
	{
		return doc->LoadFile( buf, bufsize, offset, size );
	}

	return RESULT_ERROR_INVALID_NODE;
}
#endif //CXML_ENABLE_FILEIO

const void * File::GetAddr() const
{
	if(doc)
	{
		return doc->GetFileAddr( offset, size );
	}

	return NULL;
}
