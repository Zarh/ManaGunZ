=====================================================================
MAMBA + PS3M_API + PS2 ISO + PSP ISO SUPPORT = COBRA :D
=====================================================================

Version of mamba that includes ps3m_api_core by NzV and ps2, psp iso support by Ps3ita Team

- Cobra standard features included in MAMBA
	. ISO Suppport: PS1/PS2/PS3/PSP/DVD/BluRay
	. Split ISO support on FAT32 drives
	. Burned/Burnt Optical media support (PS1/PS3 Games for all Models)
	. NTFS HDD Support
	. Network ISO & folder Support: PS1/PS3/DVD/BluRay /PKGs (requires ps3netsrv)
	. Support for system paths redirection (syscall 35)
	. CFW Syscalls: LV2 peek/poke, LV1 peek/poke, Cobra API (syscall8), LV1 function call, LV2 call to internal functions
	. Allow modification on Syscall 6/7/8/9/10/11/15.
	. Load VSH Plugins on system startup or on demand
	. PS3 MANAGER API commands (syscall management, list processes, attach to processes, load custom modules, etc.)
	. Kernel plugin support
	. Backup Protection Removal, Add full PS3 Backup support on all multiMAN/webMAN,IRIS manager forks and Managunz.
	. Blu Ray Movie region free functionality
	. webMAN MOD support
	. PSNPatch stealth plugin support (Disable CFW Syscalls)
	. Homebrew blocker  – blocks homebrew access while Syscalls are disabled

	*** ISO rips are required to get 100% support, for ex) after disabling syscalls.
	    Games like Call of Duty will not be able to play unless you use ISO rips,
	    Please DO NOT expect everything to be fully functional when you are disabling the built-in features from COBRA.
	    Folder rips are NOT compatible with PSNPatch’s stealth mode due to its ability to disable COBRA’s disc-less feature for folder JB rips****

- New features in 8.2:
	. On-the-fly reActPSN for activation of PSN content (rap files, edat, act.dat) by habib
	. Load Kernel Plugins on startup or on demand (static & dynamic addresses) by habib
	. Advanced QA Flag & Debug Settings Enabler by habib
	. Custom Syscalls for set / get fan policy by habib
	. LV2 module patches for download_plugin, autodownload_plugin, nas_plugin, psp remote play, etc. by Joonie/DeViL303
	. Improvements to PS3MAPI by TheRouletteBoi
		- Added a better set process memory by using the function used to actually write to process, this will allow user to write to memory where writing permissions are disabled.
		- Added ps3mapi_process_page_allocate this function will allocate memory into the eboot process allowing your to write/read/execute code into start_address parameter
		- Added ps3mapi_get_process_module_info which will get the name, module path, module segments, module start and module stop address all in one function
		- Added ps3mapi_create_process_thread to create thread into the process, This is useful if you want to load a small function into the process without needed make and load a sprx module

- New features in 8.3:
	. Restore disabled CFW Syscalls without Reboot just entering to Settings > System Update on XMB by aldo
	. Auto-enable dev_blind by aldo
	. Integrated fan controller (to control fan when webMAN is unloaded) by aldo
	. Support Photo GUI integration with webMAN MOD (mount games from Photo column) by aldo/DeViL303
	. Extended API with additional opcodes for developers by aldo
		. LV1 Pokes (8bit, 16bit, 32bit, 64bit)
		. LV2 Pokes (8bit, 16bit, 32bit, 64bit)
		. Extended Map Path features:
			. Support for non deletable map path entries (allow updates) /./path/etc
			. Support for partial map paths (search non existing files in original path) //path/etc
			. Map Path Callback (experimental)
			. Get Map Path info
		. Get / Set fan speed
		. Enable/disable features: Photo GUI, Auto mount dev_blind, Restore Syscalls
		. Create CFW Syscalls (6,7,8,9,10,11,15,389,409)
		. Updated ps3mapi_load_process_modules to load custom modules and system modules (by haxxxen)
		. Added ps3mapi_get_process_module_info
	. Increased from 24 to 32 the max number of map paths by aldo

----------------------------------------------------------------------
ADD MAMBA TO YOUR BACKUP MANAGER
----------------------------------------------------------------------

To boot MAMBA on startup of REBUG 4.84.2 REX / DREX, disable Cobra payload and add the path of the MAMBA payload file to:
	/dev_hdd0/boot_plugins_kernel_nocobra.txt
or	/dev_hdd0/boot_plugins_kernel_nocobra_dex.txt

Example: /dev_hdd0/plugins/kernel/mamba_484C.bin

For IRISMAN copy the MAMBA payload files to the folder:
	/dev_hdd0/game/IRISMAN00/USRDIR/mamba

To update MAMBA/PRX Loader copy the MAMBA payload files to the folder:
	/dev_hdd0/game/MAMBAPRXL/USRDIR/mamba

To avoid freezes on the Backup Managers use NzV mamba/prx loader to install mamba payload.

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
