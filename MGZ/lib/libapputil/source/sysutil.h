#ifndef __APPUTIL_SYSUTIL_H__
#define __APPUTIL_SYSUTIL_H__

#include "common.h"

namespace apputil
{
	string_t appGetVersion(string_t app_name, uint32_t version);
	int32_t appShellExcute(string_t app_path, string_t command_line);
}

#endif // __APPUTIL_SYSUTIL_H__
