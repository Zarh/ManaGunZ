=====================================================================
MAMBA + PS3M_API + PS2 ISO + PSP ISO SUPPORT = COBRA :D
=====================================================================

Version of mamba who include ps3m_api_core by NzV and ps2, psp iso support by Ps3ita Team

----------------------------------------------------------------------
ADD MAMBA TO YOUR BACKUP MANAGER
----------------------------------------------------------------------

To avoid that the Backup Manager freezes use NzV mamba loader to install mamba payload

----------------------------------------------------------------------
ORIGINAL README
----------------------------------------------------------------------

'Mamba' is the payload version of Cobra code (developed by Cobra Team) CFW for Iris Manager with some limitations.
Tested working in CFW 4.46 (Rogero v1.01) and CFW 4.53 Habib v1.01
Some differences with Cobra:

1) Mamba don´t support emulators: Iris Manager have your own method for PS1 ISOS. [Ps3ita Team 02/2016 This restriction is now removed]

2) Mamba needs to reload Iris Manager self (iris_manager.self) because Cobra needs to get vsh process (reload causes vsh child process and i get it from here). 
Code is protected from vsh_process NULL condition. [NZV 03/2015 This restriction is now removed, vsh_process is get directly from the process list, no more need to reload a self to get it]

3) Some functions of cobralib are disabled: Iris Manager uses minimal cobralib named 'cobre'

4) Spoof functions are disabled from 4.53: iris Manager don´t support spoof method

5) Others functions for patches can be disabled

6) Multiman is blocked to avoid problems to the users (reboot the console to use it). [NZV 03/2015 This restriction is now removed]

7) 'Mamba' is loaded AFTER of syscall8 Iris Manager payload and uses it for example, for HTAB method. [NZV 03/2015 Mamba as now is own payload to load it]

8) 'Mamba' can be detected using the sys8_mamba() syscalls from Iris Manager: if it return 0x666 is 'Mamba' (and not Cobra)

To port to others CFW:

- This code is released under GPL v3. Please, release your changes!
- USE_LV1_PEEK_POKE must be disabled is you are using an the old LV1 access (CFW 3.55)
- lv2/symbols.h countain the symbols to be defined from LV2 for the payload. 'FIRMWARE_4_78' countain the basic offsets to works
and the code are adapted to it
- Makefile_x.xx: set EMU_SUPPORT to "ps2" if you want ps2 iso support, to "psp" for psp iso support or set to "full" for ps2 and psp iso support.
- stage2/ps3mapi_core.h: add PS3MAPI_IDPS_1, PS3MAPI_IDPS_2 and PS3MAPI_PSID
- stage2/common.h: add FIRMWARE_VERSION
- stage2/modulespatch.h countain patches to do in modules from the payload. If you set a vsh patch to 0x0 the offset of this is obtained via bruteforce

NOTE: Surely some patches from Cobra cannot be done if you enable it: you are working after VSH.SELF is loaded.
Others patches can be done dinamically and it can work if you enable it, of course, pero some patches are done from other methods in the CFW
or from Iris Manager payload.

- I include a very old WIN32 compiler (with minimal environment) to compile the payload
- I include a zlib utility to compress the payloads (.lz.bin)
- IMPORTANT: You needs to alloc extra space to run the payload (or it hang, surely). I alloc 0x4000 bytes extra, fills to 0 
