#ifndef __APPUTIL_CLASS_OPTION_HANDLER_H__
#define __APPUTIL_CLASS_OPTION_HANDLER_H__

#include "common.h"

typedef class COptionHandler
{
private:
	COptionHandler(const COptionHandler&);
	COptionHandler& operator = (const COptionHandler&);

protected:
	void *m_imp;

public:
	COptionHandler(void);
	virtual ~COptionHandler(void);

	bool add_option(string_t opt, uint8_t argc, string_t arg_spec, string_t option_spec, bool show_usage = true);
	bool handle(int argc, char **argv, bool bErrorExit = false);

	array_string_t get_option(string_t opt);
	string_t get_string(string_t opt);
	bool get_flag(string_t opt);
	array_string_t get_filelist();
	string_t get_self_path();

	string_t get_usage();

} option_handler_t;

#endif // __APPUTIL_CLASS_OPTION_HANDLER_H__
