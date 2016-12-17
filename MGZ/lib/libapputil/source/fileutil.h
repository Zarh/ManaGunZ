#ifndef __APPUTIL_FILEUTIL_H__
#define __APPUTIL_FILEUTIL_H__

#include "common.h"

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

namespace apputil
{
	bool fileIsFileExists(string_t strFile);
	bool fileIsPathExists(string_t strFile);
		
	string_t fileGetCurDir(void);
	string_t fileGetModulePath(void);

	unsigned long fileCalcCRC(unsigned char *buf, int len);

	void fileFindFiles(string_t inDir, array_string_t &arrFileList, int32_t nSearchRange = -1);
	void fileFindFilesWide(string_t inDir, array_string_t &arrFileList);

	string_t fileGetFileName(string_t strFilePath);
	string_t fileGetExtention(string_t strFileName);
	string_t fileRemoveExtention(string_t strFileName);
	string_t fileGetPureFileName(string_t strFilePath);

	string_t fileFileToString(string_t strFile);
	bool fileStringToFile(string_t strFile, string_t strValue);

	string_t fileGetFormattedPathName(string_t strFuzzyPathName);
	void fileFormatPathName(string_t &strFuzzyPathName);

	bool fileMakeDir(string_t dir_name);

	bool fileReadFile(const char *fname, uint8_t **buffer, uint32_t *buf_size);
	bool fileWriteFile(const char *fname, uint8_t *buffer, uint32_t buf_size);
#if 0
	void AppendUniqueString(string_t &strUnique);

	BOOL ShellExecuteLite(string_t strFilePath, WORD wShowWindow = SW_SHOWNORMAL);

	BOOL ClearFolder(string_t strFolder);
#endif
}

#endif // __APPUTIL_FILEUTIL_H__
