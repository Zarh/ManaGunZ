@echo off
cls

set PS3SDK=/c/PSDK3v2
set PS3DEV=/c/PSDK3v2/ps3dev2
set WIN_PS3SDK=C:/PSDK3v2
set PATH=%WIN_PS3SDK%/mingw/msys/1.0/bin;%WIN_PS3SDK%/mingw/bin;%PS3DEV%/ppu/bin;%SCETOOL%;
set SCETOOL=C:\PSDK3v2\ps3dev2\bin
set CC=gcc

cd ps2emu_stage1_file
make -f Makefile clean
cd ..
cd ps2emu_stage2/gxemu
make -f Makefile clean
cd ../..
cd ps2emu_stage2/hwemu
make -f Makefile clean
cd ../..
cd ps2emu_stage2/netemu
make -f Makefile clean
cd ../..

pause