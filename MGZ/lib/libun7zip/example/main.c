#include <un7zip.h>
#include <string.h>
#include <stdio.h>


void callback(const char* fileName, unsigned long fileSize, unsigned fileNum, unsigned numFiles)
{
    printf("[%d/%d] File: %s Size: %ld\n", fileNum, numFiles, fileName, fileSize);
}

int main(void)
{
    // List 7-Zip archive contents
    List7zFile("/dev_hdd0/tmp/archive.7z", &callback);

    // Test 7-Zip archive contents
    Test7zFile("/dev_hdd0/tmp/archive.7z");

    // Extract 7-Zip archive contents to /dev_hdd0/tmp/
    Extract7zFile("/dev_hdd0/tmp/archive.7z", "/dev_hdd0/tmp");
    
    return 0;
}
