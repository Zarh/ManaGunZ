
#ifndef __APPUTIL_STRUTIL_H__
#define __APPUTIL_STRUTIL_H__

#include "common.h"

namespace apputil{

	string_t strFormat(const char* format, ...);
	
	char* strGetBuffer(string_t &str);
	wchar_t* strGetBuffer(wstring_t &wstr);

	string_t strEncode(const wstring_t& input);
	wstring_t strEncode(const string_t& input);

	// replace string c1 with string c2
	void strReplace(string_t &str, const char *c1, const char *c2);
	// divide string str by string c1
	array_string_t strSplit(const string_t &str, const char *c1);

	void strSortArrayString(array_string_t &strs);

} // namespace apputil

#endif // __APPUTIL_STRUTIL_H__
