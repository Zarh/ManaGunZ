#include <stdarg.h>
#include <cstdarg>
#include <stdio.h>
 
#include "strutil.h"
#include "fileutil.h"
using namespace apputil;

#include "option_handler.h"

// for debug
#ifdef NDEBUG
#define ASSERT(x)
inline void DPRINTF(const char* format, ...){
	(void) format;
}
#else
#define ASSERT(x) assert(x)
inline void DPRINTF(const char* format, ...){
	char buffer[1024];
	va_list marker;
	va_start(marker,format);
	vsprintf(buffer, format, marker);
	va_end(marker);
	
	fprintf(stderr, buffer);
}
#endif

namespace{

	struct my_opt_t{
		string_t option;
		uint8_t argc;
		string_t arg_spec;
		string_t option_spec;
		bool show_usage;

		array_string_t result_list;
		bool result_flag;
		bool checked;
	};

	struct my_imp_t{
		array_string_t file_list;
		vector<my_opt_t> option_list;
		string_t self_path;
	};

	array_string_t sort_flag_option_list(const vector<my_opt_t> &option_list)
	{
		array_string_t flag_option_list;
		for(size_t i = 0; i < option_list.size(); ++i){
			if(option_list[i].argc != 0) continue;
			flag_option_list.push_back(option_list[i].option);
		}

		int data_count = static_cast<int>(flag_option_list.size());

		for(int j = data_count - 2; j >= 0; --j){
			for(int i = 0; i <= j; ++i){
				if(flag_option_list[i].length() < flag_option_list[i+1].length()){
					string_t tmp= flag_option_list[i];
					flag_option_list[i] = flag_option_list[i+1];
					flag_option_list[i+1] = tmp;
				}
			}
		}
		return flag_option_list;
	}

	bool check_option_flag(string_t option, void *m_imp)
	{
		my_imp_t *imp = reinterpret_cast<my_imp_t*>(m_imp);
		vector<my_opt_t> &option_list = imp->option_list;
		array_string_t flag_option_list = sort_flag_option_list(imp->option_list);

		for(size_t i = 0; i < flag_option_list.size(); ++i){
			size_t pos = option.find(flag_option_list[i]);
			if(pos == SIZE_T_MAX) continue;

			for(size_t j = 0; j < option_list.size(); ++j){
				if(option_list[j].option != flag_option_list[i]) continue;
				option_list[j].result_flag = true;
				break;
			}
			DPRINTF("  [%s]: true\n", flag_option_list[i].c_str());

			strReplace(option, flag_option_list[i].c_str(), "");
		}

		return (option == "-");
	}

	inline size_t my_max(size_t a, size_t b){
		return (a > b)? a: b;
	}
}

COptionHandler::COptionHandler(void): m_imp(0)
{
	my_imp_t *imp = new my_imp_t;
	m_imp = reinterpret_cast<void*>(imp);
}

COptionHandler::~COptionHandler(void)
{
	my_imp_t *imp = reinterpret_cast<my_imp_t*>(m_imp);
	delete imp, imp = 0;
	m_imp = 0;
}

bool option_handler_t::add_option(string_t opt, uint8_t argc, string_t arg_spec, string_t option_spec, bool show_usage)
{
	my_imp_t *imp = reinterpret_cast<my_imp_t*>(m_imp);
	vector<my_opt_t> &option_list = imp->option_list;

	array_string_t null_list;
	my_opt_t new_option = {opt, argc, arg_spec, option_spec, show_usage, null_list, false, false};
	option_list.push_back(new_option);

	return true;
}

bool option_handler_t::handle(int argc, char **argv, bool bErrorExit)
{
	DPRINTF("OptionHandler:\n");

	my_imp_t *imp = reinterpret_cast<my_imp_t*>(m_imp);
	array_string_t &file_list = imp->file_list;
	vector<my_opt_t> &option_list = imp->option_list;
	string_t &self_path = imp->self_path;

	string_t ERROR_MSG = "WARNING";
	if(bErrorExit){
		ERROR_MSG = "ERROR";
	}

	string_t ret;

	if(argc <= 0) return false;

	self_path = argv[0];

	for(int arg_index = 1; arg_index < argc; ++arg_index){
		
		if(argv[arg_index][0] != '-'){
			file_list.push_back(argv[arg_index]);
			DPRINTF("  [#]: %s\n", argv[arg_index]);
			continue;
		}

		bool bFound = false;

		string_t option = argv[arg_index];
		for(size_t i = 0; i < option_list.size(); ++i){
			if(option_list[i].checked) continue;

			if(option_list[i].argc != 0){
				string_t reg_opt = string_t("-") + option_list[i].option;
				if(option != reg_opt) continue;
					
				if(arg_index + option_list[i].argc < argc){
					DPRINTF("  [%s]: ", option_list[i].option.c_str());
					for(int j = 0; j < option_list[i].argc; ++j){
						++arg_index;
						option_list[i].result_list.push_back(argv[arg_index]);
						DPRINTF("%s, ", argv[arg_index]);
					}
					DPRINTF("\n");
				}else{
					fprintf(stderr, "%s: Too few arguments in '%s'\n", ERROR_MSG.c_str(), argv[arg_index]);
					if(bErrorExit) return false;
				}
				option_list[i].checked = true;
				bFound = true;
				break;
			}
		}
		if(!bFound){
			for(size_t i = 0; i < option_list.size(); ++i){
				if(option_list[i].checked) continue;
				if(option_list[i].argc != 0) continue;
			
				bool bRet = check_option_flag(option, m_imp);
				if(!bRet){
					fprintf(stderr, "%s: Unknown option: '%s'\n", ERROR_MSG.c_str(), option.c_str());
					if(bErrorExit) return false;
				}
				break;
			}
		}
	}

	return true;
}

array_string_t option_handler_t::get_option(string_t opt)
{
	my_imp_t *imp = reinterpret_cast<my_imp_t*>(m_imp);
	vector<my_opt_t> &option_list = imp->option_list;

	array_string_t result;

	for(size_t i = 0; i < option_list.size(); ++i){
		if(option_list[i].option != opt) continue;
		result = option_list[i].result_list;
		break;
	}
	return result;
}

string_t option_handler_t::get_string(string_t opt)
{
	string_t ret;
	array_string_t result = get_option(opt);

	if(result.size() > 0){
		ret = result[0];
	}

	return ret;
}

bool option_handler_t::get_flag(string_t opt)
{
	my_imp_t *imp = reinterpret_cast<my_imp_t*>(m_imp);
	vector<my_opt_t> &option_list = imp->option_list;

	bool ret = false;

	for(size_t i = 0; i < option_list.size(); ++i){
		if(option_list[i].option != opt) continue;
		ret = option_list[i].result_flag;
		break;
	}
	return ret;
}

array_string_t option_handler_t::get_filelist()
{
	my_imp_t *imp = reinterpret_cast<my_imp_t*>(m_imp);
	array_string_t &file_list = imp->file_list;

	return file_list;
}

string_t option_handler_t::get_self_path()
{
	my_imp_t *imp = reinterpret_cast<my_imp_t*>(m_imp);
	string_t &self_path = imp->self_path;

	return self_path;
}

string_t option_handler_t::get_usage()
{
	string_t ret;

	my_imp_t *imp = reinterpret_cast<my_imp_t*>(m_imp);
	vector<my_opt_t> &option_list = imp->option_list;
	string_t &self_path = imp->self_path;

	string_t self_name = self_path;
	strReplace(self_name, "\\", "/");
	self_name = fileGetFileName(self_name);

	ret += strFormat("Usage: %s [options] file(s)\n", self_name.c_str());
	ret += strFormat("  Options:\n");

	// maxlen
	size_t max_len = 0;
	for(size_t i = 0; i < option_list.size(); ++i){
		if(option_list[i].show_usage == false) continue;
		size_t my_len = option_list[i].option.length() + option_list[i].arg_spec.length();
		
		max_len = my_max(my_len, max_len);
	}

	const int MARGIN = 4;
	string_t out_format = strFormat("   -%%-%ds %%s\n", max_len + MARGIN);
	string_t next_line_format = strFormat("\n%*s", max_len + MARGIN + 5, " ");

	for(size_t i = 0; i < option_list.size(); ++i){
		if(option_list[i].show_usage == false) continue;

		string_t option_spec = option_list[i].option_spec;
		strReplace(option_spec, "\n", next_line_format.c_str());
		string_t cmd_spec = option_list[i].option + " " + option_list[i].arg_spec;

		ret += strFormat(out_format.c_str(), cmd_spec.c_str(), option_spec.c_str());
	}

	return ret;
}
