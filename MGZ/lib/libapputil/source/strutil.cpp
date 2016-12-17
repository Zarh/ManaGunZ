#include "strutil.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

namespace apputil{
string_t strFormat(const char* format, ...)
{
   va_list marker;
   va_start(marker, format);

   const int32_t buf_size = 1024;
   int size = buf_size;
   char* buffer = new char[size];
   for( ; ; ){ //while(true){
       int nsize = vsnprintf(buffer, size, format, marker);
       va_end(marker);
	   
	   if(0 <= nsize && nsize < size){
            break;
	   }

       delete[] buffer ,buffer = 0;

       if(nsize < 0){
		   // old ( < C99) vsnprintf case:
           size *= 2;
       }else{
		   // new ( >= C99) vsnprintf case:
           size = nsize + 1;
       }
       buffer = new char[size];
       va_start(marker, format);
   }

   string_t retval = buffer;
   
   delete[] buffer ,buffer = 0;

   return retval;
}

char* strGetBuffer(string_t &str)
{
	return const_cast<char *>(str.data());
}

wchar_t* strGetBuffer(wstring_t &wstr)
{
	return const_cast<wchar_t *>(wstr.data());
}

// replace string c1 with string c2
void strReplace(string_t &str, const char *c1, const char *c2)
{
	string_t ret;
	
	string_t target = c1;
	
	// first position
	size_t pre_pos = 0;
	size_t pos = str.find(target);
	
	while(pos != string_t::npos)
	{
		ret += str.substr(pre_pos, pos - pre_pos);
		ret += c2;
		
		// next
		pre_pos = pos + target.size();
		pos = str.find(target, pre_pos);
	}
	
	// rest
	ret += str.substr(pre_pos, str.size() - pre_pos);
	
	// set result
	str = ret;
}

// divide string str by string c1
array_string_t strSplit(const string_t &str, const char *c1)
{
	// Most is the same as str_replace()
	
	array_string_t ret;
	
	string_t token = c1;
	
	size_t pre_pos = 0;
	size_t pos = str.find(token);
	
	while(pos != string_t::npos){
		ret.push_back(str.substr(pre_pos, pos - pre_pos));
		
		// next
		pre_pos = pos + token.size();
		pos = str.find(token, pre_pos);
	}
	
	// rest
	ret.push_back(str.substr(pre_pos, str.size() - pre_pos));
	
	// return result
	return ret;
}

void strSortArrayString(array_string_t &strs)
{
	int data_size = (int)strs.size();
	for(int j = data_size - 2; j >= 0; j--){
		for(int i = 0; i <= j; i++){
			if(strcmp(strs[i].c_str(), strs[i+1].c_str()) > 0){
				string_t tmp_data = strs[i];
				strs[i] = strs[i+1];
				strs[i+1] = tmp_data;
			}
		}
	}
}

} // namespace apputil

