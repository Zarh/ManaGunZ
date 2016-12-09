/*   SCE CONFIDENTIAL                                       */
/*   PlayStation(R)3 Programmer Tool Runtime Library 400.001 */
/*   Copyright (C) 2006 Sony Computer Entertainment Inc.    */
/*   All Rights Reserved.                                   */

#ifndef _CXMLACCESS_PRIVATE_H_
#define _CXMLACCESS_PRIVATE_H_

namespace cxml
{
	/// 要素のバイナリ表現
	struct ElementBin
	{
		int name;
		int attr_num;
		int parent;
		int prev;
		int next;
		int first_child;
		int last_child;
	};

	/// 属性のバイナリ表現
	struct AttributeBin
	{
		int name;
		int type;

		struct StringData
		{
			int offset;
			int len;
		};

		struct IntArrayData
		{
			int offset;
			int num;
		};

		struct FloatArrayData
		{
			int offset;
			int num;
		};

		struct FileData
		{
			int offset;
			int size;
		};

		union
		{
			int i;
			float f;
			StringData s;
			IntArrayData ia;
			FloatArrayData fa;
			FileData file;
			int id;
			int idref;
		};
	};

	/// IDのバイナリ表現
	struct IDBin
	{
		int entity_offset;
		char id[0];
	};
};

#endif //_CXMLACCESS_PRIVATE_H_
