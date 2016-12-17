#ifndef __APPUTIL_COMMON_H__
#define __APPUTIL_COMMON_H__

#include <stdint.h>
#include <string>
#include <vector>

typedef long LONG;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef uint32_t BOOL;
typedef uint32_t UINT;

typedef std::string string_t;
typedef std::wstring wstring_t;
using std::vector;
typedef vector<string_t> array_string_t;

#ifndef SIZE_T_MAX
const size_t SIZE_T_MAX = static_cast<size_t>(-1);
#endif

#endif // __APPUTIL_COMMON_H__
