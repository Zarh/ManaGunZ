/*   SCE CONFIDENTIAL                                       */
/*   PlayStation(R)3 Programmer Tool Runtime Library 400.001 */
/*   Copyright (C) 2006 Sony Computer Entertainment Inc.    */
/*   All Rights Reserved.                                   */

#ifndef _CXMLACCESS_H_
#define _CXMLACCESS_H_

/// @defgroup CXMLCompileOptions コンパイル時のオプション
/// @{

#if !defined(CXML_ENABLE_FILEIO)
	#define CXML_ENABLE_FILEIO	1		///< ファイルIOに依存する機能を有効にする
#endif

#if !defined(CXML_ENABLE_MODIFY)
	#define CXML_ENABLE_MODIFY	1		///< CXML文書の改変機能を有効にする
#endif

#if !defined(CXML_ENABLE_DEFAULT_ALLOCATOR)
	#define CXML_ENABLE_DEFAULT_ALLOCATOR	1	///< デフォルトアロケータを有効にする
#endif

#if !defined(CXML_ERROR_BASE)
	#define CXML_ERROR_BASE (0x80550000)	///< エラー番号の上位ビット ( CELL_ERROR_FACILITY_CXML == 0x055 )
#endif

/// @}

#if CXML_ENABLE_FILEIO
#include <stdio.h>
#endif //CXML_ENABLE_FILEIO

/// CXMLデータフォーマットのアクセスライブラリ
namespace cxml
{
	class Element;
	class File;

	enum
	{
		RESULT_OK 						= 0,						///< 0			成功
		RESULT_ERROR_CANT_OPEN 			= 0x01	| CXML_ERROR_BASE, 	///< 0x80550001 ファイルがオープンできなかった
		RESULT_ERROR_CANT_READ 			= 0x02	| CXML_ERROR_BASE, 	///< 0x80550002 ファイルまたはバッファから読み出すことができなかった
		RESULT_ERROR_CANT_WRITE 		= 0x03	| CXML_ERROR_BASE, 	///< 0x80550003 ファイルまたはバッファに書き込むことができなかった
		RESULT_ERROR_CANT_SEEK 			= 0x04	| CXML_ERROR_BASE, 	///< 0x80550004 ファイルまたはバッファの読み出し位置の設定ができなかった
		RESULT_ERROR_CANT_ALLOC			= 0x05	| CXML_ERROR_BASE, 	///< 0x80550005 メモリの確保に失敗した
		RESULT_ERROR_FORMAT				= 0x06	| CXML_ERROR_BASE, 	///< 0x80550006 ファイルフォーマットから逸脱している
		RESULT_ERROR_VERSION			= 0x07	| CXML_ERROR_BASE, 	///< 0x80550007 解釈できないファイルバージョン
		RESULT_ERROR_INVALID_NODE		= 0x08	| CXML_ERROR_BASE, 	///< 0x80550008 無効なノード(Element,Attribute,File)へのアクセスだ
		RESULT_ERROR_NOT_ENOUGH_BUF		= 0x09	| CXML_ERROR_BASE, 	///< 0x80550009 与えられたバッファサイズが十分ではない
		RESULT_ERROR_ACCESS_MODE		= 0x10	| CXML_ERROR_BASE, 	///< 0x80550010 現在のアクセスモードで許可されていない操作が行われた
		RESULT_ERROR_NOT_EXIST			= 0x11	| CXML_ERROR_BASE, 	///< 0x80550011 存在しない
		RESULT_ERROR_TYPE				= 0x12	| CXML_ERROR_BASE, 	///< 0x80550012 属性の型が違う
		RESULT_ERROR_CANT_MODIFY		= 0x13	| CXML_ERROR_BASE, 	///< 0x80550013 変更できない
		RESULT_ERROR_NO_ALLOCATOR		= 0x14	| CXML_ERROR_BASE  	///< 0x80550014 アロケータが登録されていない
	};

	// ファイルヘッダ
	struct Header
	{
		Header();

		char magic[4];
		int version;
		int tree_offset;
		int tree_size;
		int idtable_offset;
		int idtable_size;
		int stringtable_offset;
		int stringtable_size;
		int intarraytable_offset;
		int intarraytable_size;
		int floatarraytable_offset;
		int floatarraytable_size;
		int filetable_offset;
		int filetable_size;
	};

	/// 属性の型を表す列挙型
	enum AttributeType
	{
		AttributeType_None = 0, 		///< 属性が存在しない
		AttributeType_Int = 1,			///< 整数(32bit)
		AttributeType_Float = 2,		///< 浮動少数(32bit)
		AttributeType_String = 3,		///< 文字列(UTF-8)
		AttributeType_IntArray = 4,		///< 整数の配列
		AttributeType_FloatArray = 5,	///< 浮動少数の配列
		AttributeType_File = 6,			///< ファイル
		AttributeType_ID = 7,			///< ID
		AttributeType_IDRef = 8,		///< IDへの参照
	};

	/// アクセスモード
	enum AccessMode
	{
		AccessMode_ReadWrite, 			///< 読み書きモード
		AccessMode_ReadOnly_File,		///< ファイルをオープンする読み取り専用モード
		AccessMode_ReadOnly_Memory,		///< メモリのコピーを作成しない読み取り専用モード
	};

	/// メモリ確保/開放の用途の種類
	enum AllocationType
	{
		AllocationType_Alloc_Tree,
		AllocationType_Alloc_IDTable,
		AllocationType_Alloc_StringTable,
		AllocationType_Alloc_IntArrayTable,
		AllocationType_Alloc_FloatArrayTable,
		AllocationType_Alloc_FileTable,

		AllocationType_Free_Tree,
		AllocationType_Free_IDTable,
		AllocationType_Free_StringTable,
		AllocationType_Free_IntArrayTable,
		AllocationType_Free_FloatArrayTable,
		AllocationType_Free_FileTable,
	};

	/// CXML文書クラス
	class Document
	{
		friend class Element;
		friend class Attribute;
		friend class File;

	public:

		/// Documentのメモリ確保/開放関数型
		/// @param type [in] メモリ確保/開放の用途の種類
		/// @param userdata [in] SetAllocatorの第２引数として渡された任意のポインタ
		/// @param old_addr [in] 古いバッファのアドレス
		/// @param required_size [in] 最低限必要なサイズ( Allocのときに使用 )
		/// @param addr [out] 新しいバッファのアドレス ( Allocのときに使用 )
		/// @param size [out] 新しいバッファのサイズ ( Allocのときに使用 )
		/// @note typeがAllocationType_Alloc_Xxxの場合は、old_addr渡された古いバッファの内容をコピーしながら、最低 required_size byteのメモリを確保し、アドレスと実際に確保されたサイズを*addrと*sizeに格納する。
		/// @note typeがAllocationType_Free_Xxxの場合は、old_addrに渡された古いバッファを解放する。required_sizeとaddrとsizeには0が渡される。
		/// @note メモリが新規に確保される場合は、old_addrにはNULLが渡される。
		/// @note required_sizeに渡されたサイズよりも大きなバッファを確保することによって、メモリの再確保やコピーのコストを抑えることができる。
		/// @note また、メモリの使用量に上限を設けるために、old_addrがNULLのときだけ固定サイズのバッファを確保し、old_addrがNULLではないときには確保に失敗させる、という方法が使用できる。
		/// @note メモリ確保に失敗するには、*addrと*sizeに0を格納する。
		/// @sa SetAllocator
		typedef void (*Allocator)( AllocationType type, void * userdata, void * old_addr, unsigned int required_size, void ** addr, unsigned int * size );

		/// Documentの書き出し関数型
		/// @param addr [in] 書き出し元バッファのアドレス
		/// @param size [in] 書き出し元バッファのサイズ
		/// @param userdata [in] Writeの第２引数として渡された任意のポインタ
		/// @return 書き出したサイズ
		/// @note この型の関数をDocument::Writeメソッドの第１引数として渡すことによって、書き出し先や書き出し方法をカスタマイズすることが出来る。
		typedef int (*Writer)( const void * addr, unsigned int size, void * userdata );

	public:
		/// Documentクラスのコンストラクタ
		/// @note Documentクラスの生成直後は、アクセスモードはReadWriteモードに、マジックは"CXML"に、初期化されています。
		Document();

		/// Documentクラスのデストラクタ
		~Document();

		/// ファイルからCXML文書を生成する
		/// @param filename [in] ファイル名
		/// @param access_mode [in] アクセスモード
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		/// @note 引数 access_mode には、AccessMode_ReadOnly_File または AccessMode_ReadWrite のいずれかを与えることが出来る。
		#if CXML_ENABLE_FILEIO
		int CreateFromFile( const char * filename, AccessMode access_mode=AccessMode_ReadOnly_File );
		#endif //CXML_ENABLE_FILEIO

		/// メモリ上のCXMLファイルイメージからCXML文書を生成する
		/// @param buf [in] CXMLファイルイメージの先頭アドレス
		/// @param bufsize [in] CXMLファイルイメージのサイズ
		/// @param access_mode [in] アクセスモード
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		/// @note 引数 access_mode には、AccessMode_ReadOnly_Memory または AccessMode_ReadWrite のいずれかを与えることが出来る。
		int CreateFromBuffer( const void * buf, unsigned int bufsize, AccessMode access_mode=AccessMode_ReadOnly_Memory );

		/// ファイルやバッファを解放する
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		/// @note Documentオブジェクト内部に保持しているバッファや、開いているファイル、参照しているメモリが全て解放される。
		/// @note SetAllocatorメソッドによって設定されたメモリルーチンはリセットされない。
		int Clear();

		/// CXMLファイルイメージのサイズを取得する
		/// @return サイズ
		/// @note WriteToFileやWriteToBufferを呼び出す前に、CXMLのファイルまたはファイルイメージのサイズを知るために使用する。
		#if CXML_ENABLE_MODIFY
		int GetSize() const;
		#endif //CXML_ENABLE_MODIFY

		/// CXMLのファイルイメージを指定された書き出し関数を使って書き出す
		/// @param writer [in] 書き出し関数
		/// @param userdata [in] 任意のポインタ。Writer関数の第３引数としてそのまま渡される。
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		#if CXML_ENABLE_MODIFY
		int Write( Writer writer, void * userdata );
		#endif //CXML_ENABLE_MODIFY

		/// CXMLのファイルイメージをファイルに書き出す
		/// @param filename [in] ファイル名
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		#if CXML_ENABLE_FILEIO
		#if CXML_ENABLE_MODIFY
		int WriteToFile( const char * filename );
		#endif //CXML_ENABLE_MODIFY
		#endif //CXML_ENABLE_FILEIO

		/// CXMLのファイルイメージをバッファに書き出す
		/// @param buf [out] 書き出し先のバッファのアドレス
		/// @param bufsize [in] 書き出し先のバッファサイズ
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		#if CXML_ENABLE_MODIFY
		int WriteToBuffer( void * buf, unsigned int bufsize );
		#endif //CXML_ENABLE_MODIFY

		/// ルート要素を取得する
		/// @return ルート要素
		/// @note ルート要素が存在しない場合は、無効なElementオブジェクトが返る
		Element GetDocumentElement();

		/// ヘッダ中のマジックナンバーを取得する
		/// @param buf [out] マジックの書き出しバッファ
		/// @sa SetHeaderMagic
		void GetHeaderMagic( char buf[4] ) const;

		/// ヘッダ中のマジックナンバーを設定する
		/// @param buf [in] マジック
		/// @sa GetHeaderMagic
		#if CXML_ENABLE_MODIFY
		int SetHeaderMagic( const char buf[4] );
		#endif //CXML_ENABLE_MODIFY

		/// メモリ確保ルーチンをカスタマイズする
		/// @param _allocator [in] メモリ確保/開放関数
		/// @param _userdata [in] 任意のポインタ。Allocator関数の第２引数としてそのまま渡される。
		/// @note Documentオブジェクトがメモリを確保/解放する際に使用する関数を、指定された関数で置き換える。
		/// @note メモリ確保ルーチンのカスタマイズは、パフォーマンスのチューニングや、メモリ使用量に上限を設ける場合に有効である。
		void SetAllocator( Allocator _allocator, void * _userdata ) { allocator=_allocator; allocator_userdata = _userdata; }

		/// 要素を追加する
		/// @param name [in] 要素の名前
		/// @param attr_num [in] 属性の数
		/// @param element [out] 生成されたElementオブジェクトを格納するためのポインタ
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		/// @note このメソッドは、アクセスモードが読み書きモードである場合だけ使用することが出来る。
		/// @note このメソッドを使って要素を追加する時には、同時に要素に所属する属性の数を与える必要があり、生成された後は属性の数を変更することは出来ない。
		#if CXML_ENABLE_MODIFY
		int CreateElement( const char * name, int attr_num, Element * element );
		#endif //CXML_ENABLE_MODIFY

		/// ファイルオブジェクトを登録する
		/// @param addr [in] ファイルイメージの先頭アドレス
		/// @param size [in] ファイルイメージのサイズ
		/// @param file [out] 登録されたFileオブジェクトを格納するためのポインタ
		/// @note このメソッドは、アクセスモードが読み書きモードである場合だけ使用することが出来る。
		#if CXML_ENABLE_MODIFY
		int RegisterFile( const void * addr, unsigned int size, File * file );
		#endif //CXML_ENABLE_MODIFY

	private:
		bool IsValidElement( int offset ) const;
		bool IsValidAttribute( int offset ) const;
		const char * GetIDString( int offset ) const;
		const char * GetString( int offset ) const;
		const int * GetIntArray( int offset, unsigned int num ) const;
		const float * GetFloatArray( int offset, unsigned int num ) const;
		#if CXML_ENABLE_FILEIO
		int LoadFile( void * buf, unsigned int bufsize, int offset, unsigned int size ) const;
		#endif //CXML_ENABLE_FILEIO
		const void * GetFileAddr( int offset, unsigned int size ) const;

		#if CXML_ENABLE_MODIFY
		int RegisterString( const char * str, unsigned int len );
		int RegisterIntArray( const int * addr, unsigned int num );
		int RegisterFloatArray( const float * addr, unsigned int num );
		int RegisterID( const char * id, int entity_offset );
		void SettleHeader();
		#endif //CXML_ENABLE_MODIFY

	private:
		AccessMode access_mode;
		#if CXML_ENABLE_FILEIO
		FILE * fd;
		#endif //CXML_ENABLE_FILEIO
		Header header;
		char * tree;
		unsigned int tree_capacity;
		char * idtable;
		unsigned int idtable_capacity;
		char * stringtable;
		unsigned int stringtable_capacity;
		int * intarraytable;
		unsigned int intarraytable_capacity;
		float * floatarraytable;
		unsigned int floatarraytable_capacity;
		char * filetable;
		unsigned int filetable_capacity;
		Allocator allocator;
		void * allocator_userdata;

	private:
		Document( const Document & src );		// コピー禁止
		void operator=( const Document & src );	// コピー禁止
	};

	/// 要素クラス
	class Element
	{
		friend class Document;
		friend class Attribute;
		friend class capi;

	public:
		/// Elementクラスのコンストラクタ
		Element()
			:
			doc(0),
			offset(-1)
		{
		}

		/// Elementクラスのデストラクタ
		~Element()
		{
		}

		/// 親要素を取得する
		/// @return 親要素を指すElementオブジェクト
		/// @note 親要素が存在しない場合には、無効なElementオブジェクトが返る
		Element GetParent() const;

		/// 前の要素を取得する
		/// @return 前の要素を指すElementオブジェクト
		/// @note 前の要素が存在しない場合には、無効なElementオブジェクトが返る
		Element GetPreviousSibling() const;

		/// 次の要素を取得する
		/// @return 次の要素を指すElementオブジェクト
		/// @note 次の要素が存在しない場合には、無効なElementオブジェクトが返る
		Element GetNextSibling() const;

		/// 最初の子要素を取得する
		/// @return 最初の子要素を指すElementオブジェクト
		/// @note 最初の子要素が存在しない場合には、無効なElementオブジェクトが返る
		Element GetFirstChild() const;

		/// 最後の子要素を取得する
		/// @return 最後の子要素を指すElementオブジェクト
		/// @note 最後の子要素が存在しない場合には、無効なElementオブジェクトが返る
		Element GetLastChild() const;

		/// 要素の名前を取得する
		/// @return 要素の名前
		const char * GetName() const;

		/// 属性の数を取得する
		/// @return 属性の数
		int NumAttribute() const;

		/// 属性を取得する(インデックスで)
		/// @param index [in] インデックス値(0〜)
		/// @param attr [out] Attributeオブジェクトを受け取るためのポインタ
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		int GetAttribute( int index, class Attribute * attr ) const;

		/// 属性を取得する(名前で)
		/// @param name [in] 属性の名前
		/// @param attr [out] Attributeオブジェクトを受け取るためのポインタ
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		int GetAttribute( const char * name, class Attribute * attr ) const;

		/// Elementオブジェクトが有効か無効かを調査する
		/// @return true:有効 false:無効
		operator bool() const { return ( doc!=0 && offset>=0 ); }

		/// Elementオブジェクトが同一か否かを調査する
		/// @return true:同一 false:同一ではない
		bool operator==( const Element & rhs ) const { return ( doc==rhs.doc && offset==rhs.offset ); }

		/// 指定された要素を、最後の子要素として追加する
		/// @param child [in] 子として追加する要素
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		/// @note 引数childは、親を持たない、かつ、ルート要素ではない要素である必要がある。
		#if CXML_ENABLE_MODIFY
		int AppendChild( Element & child );
		#endif //CXML_ENABLE_MODIFY

		/// 指定された要素を、指定された子要素の直前に挿入する
		/// @param child [in] 子として追加する要素
		/// @param ref [in] childの挿入位置となる子要素
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		/// @note refが、このElementオブジェクトの子要素であることは、このメソッドを呼び出す側が保証する必要がある
		/// @note 引数childは、親を持たない、かつ、ルート要素ではない要素である必要がある。
		#if CXML_ENABLE_MODIFY
		int InsertBefore( Element & child, Element & ref );
		#endif //CXML_ENABLE_MODIFY

	private:
		Element( Document * _doc, int _offset )
			:
			doc(_doc),
			offset(_offset)
		{
		}

	private:
		Document * doc;
		int offset;
	};

	/// 属性クラス
	class Attribute
	{
		friend class Element;

	public:

		/// Attributeクラスのコンストラクタ
		Attribute()
			:
			doc(0),
			element_offset(-1),
			offset(-1)
		{
		}

		/// Attributeクラスのデストラクタ
		~Attribute()
		{
		}

		/// 属性の名前を取得する
		/// @return 属性の名前
		const char * GetName() const;

		/// 属性の名前を設定する
		/// @param name [in] 名前
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		#if CXML_ENABLE_MODIFY
		int SetName( const char * name );
		#endif //CXML_ENABLE_MODIFY

		/// 属性の型を取得する
		/// @return 属性の型
		AttributeType GetType() const;

		/// 整数を取得する
		/// @param value [out] 整数を受け取るためのポインタ
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		/// @note 属性の型が整数ではない場合は RESULT_ERROR_TYPE が返ります。
		int GetInt( int * value ) const;

		/// 整数を設定する
		/// @param value [in] 新しい値
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		#if CXML_ENABLE_MODIFY
		int SetInt( int value );
		#endif //CXML_ENABLE_MODIFY

		/// 浮動少数を取得する
		/// @param value [out] 浮動少数を受け取るためのポインタ
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		/// @note 属性の型が浮動少数ではない場合は RESULT_ERROR_TYPE が返ります。
		int GetFloat( float * value ) const;

		/// 浮動少数を設定する
		/// @param value [in] 新しい値
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		#if CXML_ENABLE_MODIFY
		int SetFloat( float value );
		#endif //CXML_ENABLE_MODIFY

		/// 文字列を取得する
		/// @param value [out] 文字列のアドレスを受け取るためのポインタ
		/// @param len [out] 文字列の長さを受け取るためのポインタ
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		/// @note 属性の型が文字列ではない場合は RESULT_ERROR_TYPE が返ります。
		int GetString( const char ** value, unsigned int * len ) const;

		/// 文字列を設定する
		/// @param value [in] 新しい値
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		#if CXML_ENABLE_MODIFY
		int SetString( const char * value );
		#endif //CXML_ENABLE_MODIFY

		/// 整数の配列を取得する
		/// @param addr [out] 整数の配列の先頭アドレスを受け取るためのポインタ
		/// @param num [out] 整数の配列のサイズを受け取るためのポインタ
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		/// @note 属性の型が整数の配列ではない場合は RESULT_ERROR_TYPE が返ります。
		int GetIntArray( const int ** addr, unsigned int * num ) const;

		/// 整数の配列を設定する
		/// @param addr [in] 配列の先頭アドレス
		/// @param num [in] 配列の要素数
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		#if CXML_ENABLE_MODIFY
		int SetIntArray( const int * addr, unsigned int num );
		#endif //CXML_ENABLE_MODIFY

		/// 浮動少数の配列を取得する
		/// @param addr [out] 浮動少数の配列の先頭アドレスを受け取るためのポインタ
		/// @param num [out] 浮動少数の配列のサイズを受け取るためのポインタ
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		/// @note 属性の型が浮動少数の配列ではない場合は RESULT_ERROR_TYPE が返ります。
		int GetFloatArray( const float ** addr, unsigned int * num ) const;

		/// 浮動少数の配列を設定する
		/// @param addr [in] 配列の先頭アドレス
		/// @param num [in] 配列の要素数
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		#if CXML_ENABLE_MODIFY
		int SetFloatArray( const float * addr, unsigned int num );
		#endif //CXML_ENABLE_MODIFY

		/// ファイルを取得する
		/// @param file [out] Fileオブジェクトを受け取るためのポインタ
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		/// @note 属性の型がファイルではない場合は RESULT_ERROR_TYPE が返ります。
		int GetFile( class File * file ) const;

		/// ファイルを設定する
		/// @param file [in] Fileオブジェクト
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		#if CXML_ENABLE_MODIFY
		int SetFile( const class File & file );
		#endif //CXML_ENABLE_MODIFY

		/// ID文字列を取得する
		/// @param value [out] ID文字列を受け取るためのポインタ
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		/// @note 属性の型がIDではない場合は RESULT_ERROR_TYPE が返ります。
		int GetID( const char ** value ) const;

		/// IDを設定する
		/// @param value [in] ID文字列
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		#if CXML_ENABLE_MODIFY
		int SetID( const char * value );
		#endif //CXML_ENABLE_MODIFY

		/// IDへの参照を取得する
		/// @param value [out] ID文字列を受け取るためのポインタ
		/// @param entity [out] ID参照の実体を指し示すElementオブジェクトを受け取るためのポインタ
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		/// @note 属性の型がIDではない場合は RESULT_ERROR_TYPE が返ります。
		int GetIDRef( const char ** value, Element * entity ) const;

		/// IDへの参照を設定する
		/// @param value [in] ID文字列
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		#if CXML_ENABLE_MODIFY
		int SetIDRef( const char * value );
		#endif //CXML_ENABLE_MODIFY

		/// Attributeオブジェクトが有効か無効かを調査する
		/// @return true:有効 false:無効
		operator bool() const { return ( doc!=0 && offset>=0 ); }

	private:

		Attribute( Document * _doc, int _element_offset, int _offset )
			:
			doc(_doc),
			element_offset(_element_offset),
			offset(_offset)
		{
		}

	private:
		Document * doc;
		int element_offset;
		int offset;
	};

	/// ファイルクラス
	class File
	{
		friend class Document;
		friend class Attribute;

	public:
		/// Fileクラスのコンストラクタ
		File()
			:
			doc(0),
			offset(-1),
			size(0)
		{
		}

		/// Fileクラスのデストラクタ
		~File()
		{
		}

		/// ファイルのメモリ上のイメージの先頭アドレスを取得する
		/// @return 先頭アドレス
		/// @note このメソッドは、Documentオブジェクトのアクセスモードが、AccessMode_ReadWrite または AccessMode_ReadOnly_Memory の場合にのみ使用できる。
		const void * GetAddr() const;

		/// ファイルのサイズを取得する
		/// @return ファイルのサイズ
		unsigned int GetSize() const { return size; }

		/// ファイルを指定されたバッファに読み込む
		/// @param buf [out] ファイルを読み込むバッファのアドレス
		/// @param bufsize [in] ファイルを読み込むバッファのサイズ
		/// @return 結果値 (RESULT_OK、RESULT_ERROR_XXXのいずれか)
		/// @note このメソッドは、Documentオブジェクトのアクセスモードが、AccessMode_ReadOnly_File の場合にのみ使用できる。
		#if CXML_ENABLE_FILEIO
		int Load( void * buf, unsigned int bufsize ) const;
		#endif //CXML_ENABLE_FILEIO

		/// Fileオブジェクトが有効か無効かを調査する
		/// @return true:有効 false:無効
		operator bool() const { return ( doc!=0 && offset>=0 ); }

	private:
		File( Document * _doc, int _offset, int _size )
			:
			doc(_doc),
			offset(_offset),
			size(_size)
		{
		}

	private:
		Document * doc;
		int offset;
		int size;
	};

};

#endif //_CXMLACCESS_H_
