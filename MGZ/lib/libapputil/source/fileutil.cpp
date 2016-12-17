#include <stdio.h>

#include "strutil.h"
#include "fileutil.h"

namespace apputil{

bool fileIsFileExists(string_t strFile)
{
	FILE *fp = fopen(strFile.c_str(), "r");
	if(fp == NULL) return false;

	fclose(fp);

	return true;
}

bool fileIsPathExists(string_t strFile)
{
	string_t base_dir = strFile;
	DIR *dirp = opendir(base_dir.c_str());
	if(dirp == NULL) return false;

	closedir(dirp);

	return true;
}

string_t fileGetCurDir(void)
{
	return "./";
}

string_t fileGetModulePath(void)
{
	return "./";
}

string_t get_ext(string_t fname)
{
	size_t pos = fname.rfind(".");
	if(pos == SIZE_T_MAX) return "";

	return fname.substr(pos + 1, fname.length() - pos - 1);
}

// フォルダ内を検索する
// nSearchRange は検索する階層の深さを表す
//  0: そのフォルダのみを検索
// -1: 全てのサブフォルダを含めて検索
void fileFindFiles(string_t inDir, array_string_t &arrFileList, int32_t nSearchRange)
{
	array_string_t list_dir;
	
	string_t base_dir = inDir;
	DIR *dirp = opendir(base_dir.c_str());
	if(dirp == NULL) return;

	{
		dirent *dir_info = readdir(dirp);
		while(dir_info != NULL){
			string_t fname = dir_info->d_name;
			string_t fpath = base_dir + "/" + fname;
			
			if(fname == "." || fname == ".."){
				dir_info = readdir(dirp);
				continue;
			}

			if(dir_info->d_type == DT_DIR){
				list_dir.push_back(fpath);
			}else if(dir_info->d_type == DT_REG){
				arrFileList.push_back(fpath);
			}

			dir_info = readdir(dirp);
		}
	}

	closedir(dirp);
	dirp = NULL;

	if(nSearchRange != 0){
		for(unsigned int i = 0; i < list_dir.size(); i++){
			fileFindFiles(list_dir[i], arrFileList, nSearchRange - 1);
		}
	}
}

void fileFindFilesWide(string_t inDir, array_string_t &arrFileList)
{
	array_string_t list_dir;
	
	string_t base_dir = inDir;
	DIR *dirp = opendir(base_dir.c_str());
	if(dirp == NULL) return;

	// 検索したいフォルダを格納する
	list_dir.push_back(inDir);
	
	while(list_dir.size() > 0){
		// 検索フォルダリストから先頭のフォルダを取り出して処理
		string_t strPathName = list_dir[0];
		vector<string_t>::iterator it = list_dir.begin(); 
		list_dir.erase(it);

		// パス名の整形
		if(strPathName.substr(strPathName.length()) == "/"){
			strPathName = strPathName.substr(strPathName.length() - 1);
		}
		string_t strSearchName = strPathName + "/*.*";
		strPathName += "/";

		// フォルダ内のファイルを検索
		DIR *dirp = opendir(base_dir.c_str());
		if(dirp == NULL) continue;
		
		dirent *dir_info = readdir(dirp);
		while(dir_info != NULL){
			string_t fname = dir_info->d_name;
			string_t fpath = base_dir + "/" + fname;
			
			if(fname == "." || fname == ".."){
				dir_info = readdir(dirp);
				continue;
			}

			if(dir_info->d_type == DT_DIR){
				list_dir.push_back(fpath);
			}else if(dir_info->d_type == DT_REG){
				arrFileList.push_back(fpath);
			}

			dir_info = readdir(dirp);
		}	    

		closedir(dirp);
		dirp = NULL;
	}
}

string_t fileGetFileName(string_t strFilePath)
{
	size_t pos = strFilePath.find_last_of('/', strFilePath.length());
	if(pos == SIZE_T_MAX){
		return string_t(strFilePath);
	}else{
		return strFilePath.substr(pos + 1);
	}
}

string_t fileGetExtention(string_t strFileName)
{
	size_t pos = strFileName.find_last_of('.', strFileName.length());
	if(pos == SIZE_T_MAX){
		return string_t(strFileName);
	}else{
		return strFileName.substr(pos + 1);
	}
}

string_t fileRemoveExtention(string_t strFileName)
{
	size_t pos = strFileName.find_last_of('.', strFileName.length());
	if(pos == SIZE_T_MAX){
		return string_t(strFileName);
	}else{
		return strFileName.substr(0, pos);
	}
}

string_t fileGetPureFileName(string_t strFileName)
{
	string_t str = fileGetFileName(strFileName);
	string_t ext = fileGetExtention(strFileName);
	if(ext != ""){
		return (str.substr(0, str.length() - ext.length() - 1));
	}else{
		return str;
	}
}

string_t fileFileToString(string_t strFile)
{
	string_t strReturn;

	FILE *fp;
	fp = fopen(strFile.c_str(), "rb");
	if(fp != NULL){
		fseek(fp, 0L, SEEK_END);
		uint32_t buff_size = ftell(fp);
		fseek(fp, 0L, SEEK_SET);

		if(buff_size > 0){
			strReturn.resize(buff_size);
			fread(strGetBuffer(strReturn), buff_size, 1, fp);
		}

		fclose(fp);
	}

	return strReturn;
}

bool fileStringToFile(string_t strFile, string_t strValue)
{
	string_t strReturn;

	FILE *fp;
	fp = fopen(strFile.c_str(), "wb");
	if(fp == NULL) return false;

	fwrite(strValue.c_str(), strValue.length(), 1, fp);

	fclose(fp);

	return true;
}

unsigned long fileCalcCRC(unsigned char *buf, int len)
{
	unsigned long crc = 0xffffffffL;
	unsigned long crc_table[256];
	
	// CRCテーブルの作成
	for(int item = 0; item < 256; item++){
		unsigned long value = (unsigned long) item;
		for(int i = 0; i < 8; i++){
			if(value & 1){
				value = 0xedb88320L ^ (value >> 1);
			}else{
				value = value >> 1;
			}
		}
		crc_table[item] = value;
	}
	
	// CRCの算出
	for(int i = 0; i < len; i++){
		crc = crc_table[(crc ^ buf[i]) & 0xff] ^ (crc >> 8);
	}

	return crc ^ 0xffffffffL;
}

string_t fileGetFormattedPathName(string_t strFuzzyPathName)
{
	string_t strPathName = strFuzzyPathName;
	if(strPathName.substr(strPathName.length()) == "/"){
		strPathName = strPathName.substr(strPathName.length() - 1);
	}
	strPathName += "/";

	return strPathName;
}

void fileFormatPathName(string_t &strFuzzyPathName)
{
	if(strFuzzyPathName.substr(strFuzzyPathName.length()) == "/"){
		strFuzzyPathName = strFuzzyPathName.substr(strFuzzyPathName.length() - 1);
	}
	strFuzzyPathName += "/";
}

bool fileMakeDir(string_t dir_name)
{
	return mkdir(dir_name.c_str(), 0755) == 0;
}

bool fileReadFile(const char *fname, uint8_t **buffer, uint32_t *buf_size)
{
	if(!fname) return false;
	if(!buffer) return false;
	if(!buf_size) return false;

	FILE *fp;
	fp = fopen(fname, "rb");
	if(fp == NULL) return false;

	fseek(fp, 0L, SEEK_END);
	*buf_size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	if(*buf_size > 0){
		*buffer = new uint8_t[*buf_size];
		fread(*buffer, *buf_size, 1, fp);
	}
	fclose(fp);

	return true;
}

bool fileWriteFile(const char *fname, uint8_t *buffer, uint32_t buf_size)
{
	if(!fname) return false;
	if(!buffer) return false;

	FILE *fp;
	fp = fopen(fname, "wb");
	if(fp == NULL) return false;

	fwrite(buffer, buf_size, 1, fp);
	fclose(fp);
		
	return true;
}

} // namespace apputil
