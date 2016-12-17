#include "apputil.h"

#include "strutil.h"
#include "fileutil.h"

#define ETC_VERSION_STRING ""

namespace apputil{

string_t appGetVersion(string_t app_name, uint32_t version)
{
	string_t ver;

	uint32_t major = (version >> 24) & 0xFF;
	uint32_t minor = (version >> 16) & 0xFF;
	uint32_t build = (version >>  8) & 0xFF;
	uint32_t eflag = (version >>  0) & 0xFF;

	ver = strFormat("%s Version %d.%02X", app_name.c_str(), major, minor);
	if(build != 0){
		ver += strFormat(".%02x", build);
	}
	if(eflag == 0xFF){
		ver += strFormat(" %s", ETC_VERSION_STRING);
	}

	return ver;
}

} // namespace apputil
