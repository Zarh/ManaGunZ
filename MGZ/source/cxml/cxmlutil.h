/*   SCE CONFIDENTIAL                                       */
/*   PlayStation(R)3 Programmer Tool Runtime Library 400.001 */
/*   Copyright (C) 2006 Sony Computer Entertainment Inc.    */
/*   All Rights Reserved.                                   */

#ifndef _CXMLUTIL_H_
#define _CXMLUTIL_H_

#include "cxmlaccess.h"

/// CXMLデータフォーマットのアクセスを支援するライブラリ
namespace cxmlutil
{
	/// 要素の名前が、指定されたものと一致するかを検査する
	/// @param elm [in] 要素
	/// @param valid_name [in] 期待している要素の名前
	/// @return true:一致した false:不一致だった
	bool CheckElementName( const cxml::Element & elm, const char * valid_name );

	/// 指定した名前とid属性を持つ子要素を検索する
	/// @param parent [in] 検索対象となる親要素
	/// @param name [in] 要素の名前
	/// @param idname [in] 検索条件とするID属性の名前
	/// @param idvalue [in] 検索条件とするID属性の値
	/// @return 最初に見つかった要素
	/// @note 引数idname/idvalueを省略するかNULLを与えたときは、IDは検索条件として使用されない
	/// @note 条件に一致する要素が発見されなかった場合には、無効なElementオブジェクトが返る
	cxml::Element FindChildElement( const cxml::Element & parent, const char * name, const char * idname=0, const char * idvalue=0 );

	/// 要素の使われていない属性を検索する
	/// @param elm [in] 検索対象となる要素
	/// @param attr [out] 使われていない属性を格納するためのポインタ
	/// @return 結果値(CXML_OK、CXML_ERROR_XXXのいずれか)
	int FindEmptyAttribute( const cxml::Element & elm, cxml::Attribute * attr );

	/// 要素の指定された名前の整数型の属性を取得する
	/// @param elm [in] 要素
	/// @param attrname [in] 属性の名前
	/// @param i [out] 属性の値を格納するためのポインタ
	/// @return 結果値(CXML_OK、CXML_ERROR_XXXのいずれか)
	int GetInt( const cxml::Element & elm, const char * attrname, int * i );

	/// 要素の指定された名前の整数型の属性を設定する
	/// @param elm [in] 要素
	/// @param attrname [in] 属性の名前
	/// @param i [in] 属性の値
	/// @return 結果値(CXML_OK、CXML_ERROR_XXXのいずれか)
	/// @note 指定された名前の属性が存在すればその属性を上書きし、存在しなければ空いている属性を探して名前と値を設定する
	#if CXML_ENABLE_MODIFY
	int SetInt( const cxml::Element & elm, const char * attrname, int i );
	#endif //CXML_ENABLE_MODIFY

	/// 要素の指定された名前の浮動少数型の属性を取得する
	/// @param elm [in] 要素
	/// @param attrname [in] 属性の名前
	/// @param f [out] 属性の値を格納するためのポインタ
	/// @return 結果値(CXML_OK、CXML_ERROR_XXXのいずれか)
	int GetFloat( const cxml::Element & elm, const char * attrname, float * f );

	/// 要素の指定された名前の浮動少数型の属性を設定する
	/// @param elm [in] 要素
	/// @param attrname [in] 属性の名前
	/// @param f [in] 属性の値
	/// @return 結果値(CXML_OK、CXML_ERROR_XXXのいずれか)
	/// @note 指定された名前の属性が存在すればその属性を上書きし、存在しなければ空いている属性を探して名前と値を設定する
	#if CXML_ENABLE_MODIFY
	int SetFloat( const cxml::Element & elm, const char * attrname, float f );
	#endif //CXML_ENABLE_MODIFY

	/// 要素の指定された名前の文字列型の属性を取得する
	/// @param elm [in] 要素
	/// @param attrname [in] 属性の名前
	/// @param str [out] 文字列のアドレスを格納するためのポインタ
	/// @param len [out] 文字列の長さを格納するためのポインタ
	/// @return 結果値(CXML_OK、CXML_ERROR_XXXのいずれか)
	int GetString( const cxml::Element & elm, const char * attrname, const char ** str, unsigned int * len );

	/// 要素の指定された名前の文字列型の属性を設定する
	/// @param elm [in] 要素
	/// @param attrname [in] 属性の名前
	/// @param str [in] 属性の値
	/// @return 結果値(CXML_OK、CXML_ERROR_XXXのいずれか)
	/// @note 指定された名前の属性が存在すればその属性を上書きし、存在しなければ空いている属性を探して名前と値を設定する
	#if CXML_ENABLE_MODIFY
	int SetString( const cxml::Element & elm, const char * attrname, const char * str );
	#endif //CXML_ENABLE_MODIFY

	/// 要素の指定された名前の整数配列型の属性を取得する
	/// @param elm [in] 要素
	/// @param attrname [in] 属性の名前
	/// @param addr [out] 配列の先頭アドレスを格納するためのポインタ
	/// @param num [out] 配列の要素数を格納するためのポインタ
	/// @return 結果値(CXML_OK、CXML_ERROR_XXXのいずれか)
	int GetIntArray( const cxml::Element & elm, const char * attrname, const int ** addr, unsigned int * num );

	/// 要素の指定された名前の整数配列型の属性を設定する
	/// @param elm [in] 要素
	/// @param attrname [in] 属性の名前
	/// @param addr [in] 配列のアドレス
	/// @param num [in] 配列の要素数
	/// @return 結果値(CXML_OK、CXML_ERROR_XXXのいずれか)
	/// @note 指定された名前の属性が存在すればその属性を上書きし、存在しなければ空いている属性を探して名前と値を設定する
	#if CXML_ENABLE_MODIFY
	int SetIntArray( const cxml::Element & elm, const char * attrname, const int * addr, unsigned int num );
	#endif //CXML_ENABLE_MODIFY

	/// 要素の指定された名前の浮動少数配列型の属性を取得する
	/// @param elm [in] 要素
	/// @param attrname [in] 属性の名前
	/// @param addr [out] 配列の先頭アドレスを格納するためのポインタ
	/// @param num [out] 配列の要素数を格納するためのポインタ
	/// @return 結果値(CXML_OK、CXML_ERROR_XXXのいずれか)
	int GetFloatArray( const cxml::Element & elm, const char * attrname, const float ** addr, unsigned int * num );

	/// 要素の指定された名前の浮動少数配列型の属性を設定する
	/// @param elm [in] 要素
	/// @param attrname [in] 属性の名前
	/// @param addr [in] 配列のアドレス
	/// @param num [in] 配列の要素数
	/// @return 結果値(CXML_OK、CXML_ERROR_XXXのいずれか)
	/// @note 指定された名前の属性が存在すればその属性を上書きし、存在しなければ空いている属性を探して名前と値を設定する
	#if CXML_ENABLE_MODIFY
	int SetFloatArray( const cxml::Element & elm, const char * attrname, const float * addr, unsigned int num );
	#endif //CXML_ENABLE_MODIFY

	/// 要素の指定された名前のファイル型の属性を取得する
	/// @param elm [in] 要素
	/// @param attrname [in] 属性の名前
	/// @param file [out] Fileオブジェクトを格納するためのポインタ
	/// @return 結果値(CXML_OK、CXML_ERROR_XXXのいずれか)
	int GetFile( const cxml::Element & elm, const char * attrname, cxml::File * file );

	/// 要素の指定された名前のファイル型の属性を設定する
	/// @param elm [in] 要素
	/// @param attrname [in] 属性の名前
	/// @param file [in] 属性の値
	/// @return 結果値(CXML_OK、CXML_ERROR_XXXのいずれか)
	/// @note 指定された名前の属性が存在すればその属性を上書きし、存在しなければ空いている属性を探して名前と値を設定する
	#if CXML_ENABLE_MODIFY
	int SetFile( const cxml::Element & elm, const char * attrname, const cxml::File & file );
	#endif //CXML_ENABLE_MODIFY

	/// 要素の指定された名前のID型の属性を取得する
	/// @param elm [in] 要素
	/// @param attrname [in] 属性の名前
	/// @param str [out] ID文字列のアドレスを格納するためのポインタ
	/// @return 結果値(CXML_OK、CXML_ERROR_XXXのいずれか)
	int GetID( const cxml::Element & elm, const char * attrname, const char ** str );

	/// 要素の指定された名前のID型の属性を設定する
	/// @param elm [in] 要素
	/// @param attrname [in] 属性の名前
	/// @param str [in] 属性の値
	/// @return 結果値(CXML_OK、CXML_ERROR_XXXのいずれか)
	/// @note 指定された名前の属性が存在すればその属性を上書きし、存在しなければ空いている属性を探して名前と値を設定する
	#if CXML_ENABLE_MODIFY
	int SetID( const cxml::Element & elm, const char * attrname, const char * str );
	#endif //CXML_ENABLE_MODIFY

	/// 要素の指定された名前のID参照型の属性を取得する
	/// @param elm [in] 要素
	/// @param attrname [in] 属性の名前
	/// @param str [out] ID文字列のアドレスを格納するためのポインタ
	/// @param entity [out] ID参照の実体を示すElementオブジェクトを格納するためのポインタ
	/// @return 結果値(CXML_OK、CXML_ERROR_XXXのいずれか)
	int GetIDRef( const cxml::Element & elm, const char * attrname, const char ** str, cxml::Element * entity );

	/// 要素の指定された名前のIDRef型の属性を設定する
	/// @param elm [in] 要素
	/// @param attrname [in] 属性の名前
	/// @param str [in] 属性の値
	/// @return 結果値(CXML_OK、CXML_ERROR_XXXのいずれか)
	/// @note 指定された名前の属性が存在すればその属性を上書きし、存在しなければ空いている属性を探して名前と値を設定する
	#if CXML_ENABLE_MODIFY
	int SetIDRef( const cxml::Element & elm, const char * attrname, const char * str );
	#endif //CXML_ENABLE_MODIFY

};

#endif //_CXMLUTIL_H_
