# fatfs

Ported to PS3 by lmirel : https://github.com/lmirel/fatfs_psx

--
embedded fatfs/exfat implementation for ps3

original implementation comes from http://elm-chan.org/fsw/ff/00index_e.html
--

FatFs is a generic FAT/exFAT filesystem module for small embedded systems. The FatFs module is written in compliance with ANSI C (C89) and completely separated from the disk I/O layer. Therefore it is independent of the platform. It can be incorporated into small microcontrollers with limited resource, such as 8051, PIC, AVR, ARM, Z80, RX and etc. Also Petit FatFs module is available for tiny microcontrollers.

--
check ffconf.h for enabled functionality and change if/as needed

for PS3, use the sdk from https://github.com/Estwald/PSDK3v2 or any other compatible sdk and build & run the included example

provided 'as is' with no guarantee or warranties. check original LICENSE.txt for details.

cheers
