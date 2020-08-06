//
// Created by huzongyao on 17-11-24.
//

#include "7zExtractor.h"
#include "7zTypes.h"
#include "7z.h"
#include "7zFile.h"
#include "7zAlloc.h"
#include "7zCrc.h"
#include "7zFunctions.h"

#define OPTION_DETAIL 0x01
#define OPTION_TEST 0x02
#define OPTION_OUTPUT 0x04
#define OPTION_EXTRACT (OPTION_TEST|OPTION_OUTPUT)

#define nullptr 0
#define auto UInt16

static const ISzAlloc g_Alloc = {SzAlloc, SzFree};

static SRes
extractStream(ISeekInStream *seekStream, const char *destDir,
              const int options, callback7z_t callback, size_t inBufSize) {

    ISzAlloc allocImp = g_Alloc;
    ISzAlloc allocTempImp = g_Alloc;
    CLookToRead2 lookStream;
    CSzArEx db;
    SRes res;
    UInt16 *temp = nullptr;
    size_t tempSize = 0;

    LookToRead2_CreateVTable(&lookStream, False);
    lookStream.buf = nullptr;
    res = SZ_OK;
    lookStream.buf = static_cast<Byte *>(ISzAlloc_Alloc(&allocImp, inBufSize));
    if (!lookStream.buf)
        res = SZ_ERROR_MEM;
    else {
        lookStream.bufSize = inBufSize;
        lookStream.realStream = seekStream;
        LookToRead2_Init(&lookStream);
    }

    CrcGenerateTable();
    SzArEx_Init(&db);
    if (res == SZ_OK) {
        res = SzArEx_Open(&db, &lookStream.vt, &allocImp, &allocTempImp);
    }
    if (res == SZ_OK) {
        UInt32 i;
        /*
        if you need cache, use these 3 variables.
        if you use external function, you can make these variable as static.
        */
        UInt32 blockIndex = 0xFFFFFFFF; /* it can have any value before first call (if outBuffer = 0) */
        Byte *outBuffer = nullptr; /* it must be 0 before first call for each new archive. */
        size_t outBufferSize = 0;  /* it can have any value before first call (if outBuffer = 0) */
        CBuf fileNameBuf;
        Buf_Init(&fileNameBuf);

        for (i = 0; i < db.NumFiles; i++) {
            size_t offset = 0;
            size_t outSizeProcessed = 0;
            size_t len;
            auto isDir = (unsigned) SzArEx_IsDir(&db, i);
            len = SzArEx_GetFileNameUtf16(&db, i, NULL);
            if (len > tempSize) {
                SzFree(NULL, temp);
                tempSize = len;
                temp = (UInt16 *) SzAlloc(NULL, tempSize * sizeof(temp[0]));
                if (!temp) {
                    res = SZ_ERROR_MEM;
                    break;
                }
            }
            SzArEx_GetFileNameUtf16(&db, i, temp);
            res = Utf16_To_Char(&fileNameBuf, temp);
            if (res != SZ_OK) {
                break;
            }
            UInt64 fileSize = SzArEx_GetFileSize(&db, i);

            if (callback)
                callback ((char*) fileNameBuf.data, fileSize, i+1, db.NumFiles);

            if (options & OPTION_DETAIL) {
                char attr[8], file_size[32], file_time[32];
                GetAttribString(SzBitWithVals_Check(&db.Attribs, i)
                                ? db.Attribs.Vals[i] : 0, isDir, attr);
                UInt64ToStr(fileSize, file_size, 10);
                if (SzBitWithVals_Check(&db.MTime, i))
                    ConvertFileTimeToString(&db.MTime.Vals[i], file_time);
                else {
                    size_t j;
                    for (j = 0; j < 19; j++)
                        file_time[j] = ' ';
                    file_time[j] = '\0';
                }
            }
            if (options & OPTION_TEST) {
                if (!isDir) {
                    res = SzArEx_Extract(&db, &lookStream.vt, i, &blockIndex, &outBuffer,
                                         &outBufferSize, &offset, &outSizeProcessed,
                                         &allocImp, &allocTempImp);
                    if (res != SZ_OK)
                        break;
                }
                if (options & OPTION_OUTPUT) {
                    CSzFile outFile;
                    size_t processedSize;
                    size_t j;
                    UInt16 *name = temp;
                    const auto *destPath = (const UInt16 *) name;
                    for (j = 0; name[j] != 0; j++) {
                        if (name[j] == '/') {
                            name[j] = 0;
                            MyCreateDir(name, destDir);
                            name[j] = CHAR_PATH_SEPARATOR;
                        }
                    }
                    if (isDir) {
                        MyCreateDir(name, destDir);
                        continue;
                    } else if (OutFile_OpenUtf16(&outFile, destPath, destDir)) {
                        PrintError("can not open output file");
                        res = SZ_ERROR_FAIL;
                        break;
                    }
                    processedSize = outSizeProcessed;
                    if (File_Write(&outFile, outBuffer + offset, &processedSize) != 0 ||
                        processedSize != outSizeProcessed) {
                        PrintError("can not write output file");
                        res = SZ_ERROR_FAIL;
                        break;
                    }
                    if (File_Close(&outFile)) {
                        PrintError("can not close output file");
                        res = SZ_ERROR_FAIL;
                        break;
                    }
                }
            }
        }
        Buf_Free(&fileNameBuf, &g_Alloc);
        ISzAlloc_Free(&allocImp, outBuffer);
    }
    SzFree(nullptr, temp);
    SzArEx_Free(&db, &allocImp);
    ISzAlloc_Free(&allocImp, lookStream.buf);
    if (res != SZ_OK) {
        PrintError("Stream Extract Error");
    }
    return res;
}

int _process7zFile(const char *srcFile, const char *destDir, int opts, callback7z_t callback, size_t inBufSize)
{
    CFileInStream archiveStream;
    if (InFile_Open(&archiveStream.file, srcFile)) {
        PrintError("Input File Open Error");
        return SZ_ERROR_ARCHIVE;
    }
    FileInStream_CreateVTable(&archiveStream);
    SRes res = extractStream(&archiveStream.vt, destDir, opts, callback, inBufSize);
    File_Close(&archiveStream.file);

    return res;
}

/**
 * extract all from 7z
 */
int Extract7zFileEx(const char *srcFile, const char *destDir, callback7z_t callback, unsigned long inBufSize)
{
    return _process7zFile(srcFile, destDir, OPTION_EXTRACT, callback, inBufSize);
}

int Test7zFileEx(const char *srcFile, callback7z_t callback, unsigned long inBufSize)
{
    return _process7zFile(srcFile, NULL, OPTION_TEST, callback, inBufSize);
}

int List7zFile(const char *srcFile, callback7z_t callback)
{
    return _process7zFile(srcFile, NULL, 0, callback, DEFAULT_IN_BUF_SIZE);
}

int Extract7zFile(const char *srcFile, const char *destDir) {
    return Extract7zFileEx(srcFile, destDir, NULL, DEFAULT_IN_BUF_SIZE);
}

int Test7zFile(const char *srcFile) {
    return Test7zFileEx(srcFile, NULL, DEFAULT_IN_BUF_SIZE);
}
