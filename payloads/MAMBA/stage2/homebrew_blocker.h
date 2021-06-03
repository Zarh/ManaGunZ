//////////////////////////////////////////////////////////////////////////////////////
// KW - HOMEBREW BLOCKER SUPPORT CODE TO USE IN open_path_hook()
//
// Functions, global vars and directives are here to improve code readability
//
//////////////////////////////////////////////////////////////////////////////////////

//extern int disc_emulation; // storage_ext.c

#ifdef DO_AUTO_RESTORE_SC
u8 allow_restore_sc = 1; // allow re-create cfw syscalls accessing system update on XMB
#endif
#ifdef DO_AUTO_MOUNT_DEV_BLIND
u8 auto_dev_blind  = 1; // auto-mount dev_blind
static u8 mount_dev_blind  = 1;
#endif
#ifdef DO_CFW2OFW_FIX
u8 CFW2OFW_game = 0;
#endif

#define BLACKLIST_FILENAME	"/dev_hdd0/tmp/blacklist.cfg"
#define WHITELIST_FILENAME	"/dev_hdd0/tmp/whitelist.cfg"

#define MAX_LIST_ENTRIES	20 // Maximum elements for noth the custom blacklist and whitelist.

static u8 __initialized_lists = 0; // Are the lists initialized ?
static u8 __blacklist_entries = 0; // Module global var to hold the current blacklist entries.
static char  * __blacklist;
static u8 __whitelist_entries = 0; // Module global var to hold the current whitelist entries.
static char  * __whitelist;

static unsigned char no_exists[] = {"/fail"};

int read_text_line(int fd, char *line, unsigned int size, int *eof);

//
// init_list()
//
// inits a list.
// returns the number of elements read from file

static u8 init_list(char *list, const char *path)
{
	int f;

	if (cellFsOpen(path, CELL_FS_O_RDONLY, &f, 0666, NULL, 0) != CELL_FS_SUCCEEDED) return 0; // failed to open

	if(!list) list = palloc(9 * MAX_LIST_ENTRIES);

	char line[0x10];

	u8 loaded = 0;
	while (loaded < MAX_LIST_ENTRIES)
	{
		int eof;
		if (read_text_line(f, line, sizeof(line), &eof) >= 9)
		{
			strncpy(list + (9 * loaded), line, 9); // copy only the first 9 chars - if it has less than 9, it will fail future checks. should correct in file.
			loaded++;
		}
		if (eof) break;
	}
	cellFsClose(f);
	return loaded;
}

//
// listed()
//
// tests if a char gameid[9] is in the blacklist or whitelist
// initialize the both lists, if not yet initialized;
// receives the list to test blacklist (1) or whitelist (0), and the gameid
// to initialize the lists, tries to read them from file BLACKLIST_FILENAME and WHITELIST_FILENAME

static int listed(int blacklist, const char *gameid)
{
	char *list;
	u8 elements;
	if (!__initialized_lists)
	{
		// initialize the lists if not yet done
		__blacklist_entries = init_list(__blacklist, BLACKLIST_FILENAME);
		__whitelist_entries = init_list(__whitelist, WHITELIST_FILENAME);
		__initialized_lists = 1;
	}
	if (blacklist)
		{list = __blacklist, elements = __blacklist_entries;}
	else
		{list = __whitelist, elements = __whitelist_entries;}

	if(!list) return 0;

	for(u8 i = 0; i < elements; i++)
		if (!strncmp(list + (9 * i), gameid, 9))
			return 1; // gameid is in the list

	// if it got here, it is not in the list. return 0
	return 0;
}

// BEGIN KW & AV block access to homebrews when syscalls are disabled
// After the core tests it will test first if the gameid is in whitelist.cfg (superseeds previous tests)
// In the it will test if the gameid is in blacklist.cfg (superseeds all previous tests)
// ** WARNING ** This syscall disablement test assumes that the syscall table entry 6 (peek) was replaced by the original value (equals syscall 0 entry) as done by PSNPatch
// ** WARNING ** If only a parcial disablement was made, this assumption WILL FAIL !!!
static inline int block_homebrew(const char *path)
{
	u8 is_hdd0 = (path[1] == 'd' && path[5] == 'h' && !strncmp(path, "/dev_hdd0/", 10));

	u8 is_game_dir = (is_hdd0 && !strncmp(path + 10, "game/", 5));

	if(is_game_dir)
	{
		u8 syscalls_disabled = ((*(u64 *)MKA(syscall_table_symbol + 8 * 6)) == (*(u64 *)MKA(syscall_table_symbol)));

//		if(!syscalls_disabled && (!strncmp(path + 15, "ENSTONEXX", 9) || !strncmp(path + 15, "IDPSET000", 9))) syscalls_disabled = 1;

		// CFW2OFW fix by Evilnat
		// Fixes black screen while a CFW2OFW game is loaded with a mounted JB folder game
		#ifdef DO_CFW2OFW_FIX
		if (strstr(path + 15, "/LIC.EDAT")) // Check CFW2OFW: /dev_hdd0/game/NPEB12345/LICDIR/LIC.EDAT
		{
			#ifdef DEBUG
			DPRINTF("CFW2OFW detected\n");
			#endif
			CFW2OFW_game = 1; // unmount in post_cellFsUtilMount of storage_ext.c
		}
		else
		#endif
		if (syscalls_disabled && strstr(path + 15, "/EBOOT.BIN"))
		{
			// syscalls are disabled and an EBOOT.BIN is being called from hdd. Let's test it.
			const char *gameid = path + 15;

			// flag "whitelist" id's
			int allow =
			!strncmp(gameid, "NP", 2) ||
			!strncmp(gameid, "BL", 2) ||
			!strncmp(gameid, "BC", 2) ||
			!strncmp(gameid, "_INST_", 6) || // 80010006 error fix when trying to install a game update with syscall disabled. # Joonie's, Alexander's, Aldo's
			!strncmp(gameid, "_DEL_", 5) ||  // Fix data corruption if you uninstall game/game update/homebrew with syscall disabled # Alexander's
			!strncmp(gameid, "KOEI3", 5) ||
			!strncmp(gameid, "KTGS3", 5) ||
			!strncmp(gameid, "MRTC0", 5) ||
			!strncmp(gameid, "ASIA0", 5) ||
			!strncmp(gameid, "GUST0", 5) ;

			// flag some "blacklist" id's
			if (
				!strncmp(gameid, "BLES806", 7)   || // Multiman and assorted tools are in the format BLES806**
				!strncmp(gameid, "BLJS10018", 9) || // PSNPatch Stealth (older versions were already detected as non-NP/BC/BL)
				!strncmp(gameid, "BLES08890", 9) || // PSNope by user
				!strncmp(gameid, "BLES13408", 9) || // FCEU NES Emulator
				!strncmp(gameid, "BLES01337", 9) || // Awesome File Manager
				!strncmp(gameid, "BLND00001", 9) || // dev_blind
				!strncmp(gameid, "NPEA90124", 9) // // SEN Enabler
				) allow = 0;

			// test whitelist.cfg and blacklist.cfg
			if (listed(0, gameid)) allow = 1; // whitelist.cfg test
			if (listed(1, gameid)) allow = 0; // blacklist.cfg test

			// let's now block homebrews if the "allow" flag is false
			if (!allow)
			{
				set_patched_func_param(1, (u64)no_exists); // redirect to invalid path
				#ifdef DO_AUTO_MOUNT_DEV_BLIND
				mount_dev_blind = 1;
				#endif
				return FAILED;
			}
		}
	}
	#ifdef MAKE_RIF
	else if(is_hdd0)
	{
		make_rif(path);
	}
	#endif
	#if defined(DO_AUTO_MOUNT_DEV_BLIND) || defined(DO_AUTO_RESTORE_SC)
	else if(path[1] == 'd' && path[6] == 'l') // /dev_flash || /dev_blind
	{
		#ifdef DO_AUTO_MOUNT_DEV_BLIND
		if(auto_dev_blind && !strncmp(path, "/dev_blind/", 11))
		{
			if(mount_dev_blind)
			{
				cellFsUtilMount("CELL_FS_IOS:BUILTIN_FLSH1", "CELL_FS_FAT", "/dev_blind", 0, 0, 0, 0, 0);
				mount_dev_blind = 0; // do not try to mount accessing consecutive files
				return SUCCEEDED;
			}
		}
		else
		#endif
		#ifdef DO_AUTO_RESTORE_SC
		if(allow_restore_sc)
		{
			if(!strcmp(path, "/dev_flash/vsh/module/software_update_plugin.sprx"))
			{
				u8 syscalls_disabled = ((*(u64 *)MKA(syscall_table_symbol + 8 * 6)) == (*(u64 *)MKA(syscall_table_symbol)));
				if(syscalls_disabled)
					create_syscalls();

				#ifdef MAKE_RIF
				skip_existing_rif = 0;
				#endif
			}
		}
		#endif
	}
	#endif

	#ifdef DO_AUTO_MOUNT_DEV_BLIND
	mount_dev_blind = 1;
	#endif
	return SUCCEEDED;
}
