# Exported from MPLAB IDE project `picmmc.mcp' on Mon Dec 24 13:13:53 2007.

"picmmc.hex" : "picmmc.cof"
	"C:\Program Files\Microchip\MPLAB C30\bin\pic30-bin2hex.exe" "picmmc.cof"

"picmmc.cof" : "comm.o" "ff.o" "main.o" "mmc.o" "monitor.o"
	"C:\Program Files\Microchip\MPLAB C30\bin\pic30-gcc.exe" -mcpu=24FJ64GA002 "comm.o" "ff.o" "main.o" "mmc.o" "monitor.o" -o"picmmc.cof" -Wl,-L"C:\Program Files\Microchip\MPLAB C30\lib",-Tp24FJ64GA002.gld,-Map="picmmc.map",--report-mem

"comm.o" : "comm.c" "C:\user\PIC\picmmc\integer.h" "C:\user\PIC\picmmc\comm.h" "C:\user\PIC\picmmc\pic24f.h" "c:\program files\microchip\mplab c30\bin\..\support\h\p24FJ64GA002.h" "c:\program files\microchip\mplab c30\bin\..\include\yvals.h" "c:\program files\microchip\mplab c30\bin\..\include\string.h" "C:\user\PIC\picmmc\comm.c"
	"C:\Program Files\Microchip\MPLAB C30\bin\pic30-gcc.exe" -mcpu=24FJ64GA002 -x c -c   "comm.c" -o"comm.o" -g -Wall -pedantic -Os

"ff.o" : "ff.c" "C:\user\PIC\picmmc\diskio.h" "C:\user\PIC\picmmc\integer.h" "C:\user\PIC\picmmc\ff.h" "c:\program files\microchip\mplab c30\bin\..\include\yvals.h" "c:\program files\microchip\mplab c30\bin\..\include\string.h" "C:\user\PIC\picmmc\ff.c"
	"C:\Program Files\Microchip\MPLAB C30\bin\pic30-gcc.exe" -mcpu=24FJ64GA002 -x c -c   "ff.c" -o"ff.o" -g -Wall -pedantic -Os

"main.o" : "main.c" "C:\user\PIC\picmmc\ff.h" "C:\user\PIC\picmmc\diskio.h" "C:\user\PIC\picmmc\monitor.h" "C:\user\PIC\picmmc\integer.h" "C:\user\PIC\picmmc\comm.h" "C:\user\PIC\picmmc\pic24f.h" "c:\program files\microchip\mplab c30\bin\..\support\h\p24FJ64GA002.h" "c:\program files\microchip\mplab c30\bin\..\include\yvals.h" "c:\program files\microchip\mplab c30\bin\..\include\string.h" "C:\user\PIC\picmmc\main.c"
	"C:\Program Files\Microchip\MPLAB C30\bin\pic30-gcc.exe" -mcpu=24FJ64GA002 -x c -c   "main.c" -o"main.o" -g -Wall -pedantic -Os

"mmc.o" : "mmc.c" "C:\user\PIC\picmmc\integer.h" "C:\user\PIC\picmmc\diskio.h" "c:\program files\microchip\mplab c30\bin\..\support\h\p24FJ64GA002.h" "C:\user\PIC\picmmc\mmc.c"
	"C:\Program Files\Microchip\MPLAB C30\bin\pic30-gcc.exe" -mcpu=24FJ64GA002 -x c -c   "mmc.c" -o"mmc.o" -g -Wall -pedantic -Os

"monitor.o" : "monitor.c" "C:\user\PIC\picmmc\comm.h" "C:\user\PIC\picmmc\integer.h" "C:\user\PIC\picmmc\monitor.h" "c:\program files\microchip\mplab c30\bin\..\include\yvals.h" "c:\program files\microchip\mplab c30\bin\..\include\stdarg.h" "C:\user\PIC\picmmc\monitor.c"
	"C:\Program Files\Microchip\MPLAB C30\bin\pic30-gcc.exe" -mcpu=24FJ64GA002 -x c -c   "monitor.c" -o"monitor.o" -g -Wall -pedantic -Os

clean : 
	del "comm.o" "ff.o" "main.o" "mmc.o" "monitor.o" "picmmc.cof" "picmmc.hex"

