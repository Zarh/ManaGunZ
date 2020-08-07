#include <minitar.h>
#include <string.h>
#include <stdio.h>

void list_callback(const char* fileName, unsigned long fileSize, char fileType)
{
    printf("Type: (%d) File: %s Size: %ld\n", fileType, fileName, fileSize);
}

int main(void)
{
    // Extract .tar archive contents to /dev_hdd0/tmp/
    untar("/dev_hdd0/tmp/archive.tar", "/dev_hdd0/tmp");

    // Extract .tar.gz archive contents to /dev_hdd0/tmp/
    untar_gz("/dev_hdd0/tmp/archive.tgz", "/dev_hdd0/tmp");

    // Extract .tar.bz2 archive contents to /dev_hdd0/tmp/ with a list callback
    untarEx_bz2("/dev_hdd0/tmp/archive.tar.bz2", "/dev_hdd0/tmp", &list_callback);

    // Create archive.tar and save the folder /dev_hdd0/mydata/
    tar_gz("/dev_hdd0/tmp/archive.tar", "/dev_hdd0/mydata/");

    // Create archive.tar.gz and compress the folder /dev_hdd0/mydata/
    tar_gz("/dev_hdd0/tmp/archive.tar.gz", "/dev_hdd0/mydata/");

    // Create archive.tar.bz2 and compress the folder /dev_hdd0/mydata/
    tar_bz2("/dev_hdd0/tmp/archive.tar.bz2", "/dev_hdd0/mydata/");

    return 0;
}
