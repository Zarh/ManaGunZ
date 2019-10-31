#include <sys/memory.h>
#include <sys/process.h>

#include "hvcall.h"
#include "mm.h"
#include "utils.h"
#include "payload.h"

#define SYSMODULE_SYSUTIL_GAME		0x003e

extern void print_load(char *format, ...);

extern u8 eid_root_key[EID_ROOT_KEY_SIZE];
extern u64 HV_START_OFFSET;
extern u64 HTAB_OFFSET;
extern u64 MMAP_OFFSET1;
extern u64 MMAP_OFFSET2;
extern u64 SPE_OFFSET;

static int make_patches(void) {
	
	/* allow mapping of HTAB with write protection */
	lv1_poke64(HTAB_OFFSET, 0x60000000E97F00A8ULL);

	/* allow mapping of any needed memory area */
	lv1_poke64(MMAP_OFFSET1, 0x6000000048000028ULL);
	lv1_poke64(MMAP_OFFSET2, 0x392000014BFFFBFDULL);

	/* allow setting all bits of SPE register MFC_SR1 */
	lv1_poke64(SPE_OFFSET, 0x3920FFFFE9430000ULL);

	/* change region size for lv2 hmac hash calculation */
	lv1_poke64(HV_START_OFFSET     , 0x0000000000000001ULL);
	lv1_poke64(HV_START_OFFSET+0x08, 0xE0D251B556C59F05ULL);
	lv1_poke64(HV_START_OFFSET+0x10, 0xC232FCAD552C80D7ULL);
	lv1_poke64(HV_START_OFFSET+0x18, 0x65140CD200000000ULL);
	
	/* permission patch */
	lv2_poke64(0x8000000000003D90ULL, 0x386000014E800020ULL);
	
	/* remove page protection bits from htab entries */
	patch_htab_entries(0);

	return 0;
}

int dump_eid_root_key(const char* file_path) {
	int result;

	FILE* fp;
	int poke_installed;
	int payload_installed;

	poke_installed = 0;
	payload_installed = 0;

	print_load("Dumping the eid_root_key");
	
	print_load("* install_new_poke");
	result = install_new_poke();
	if (result != 0) {
		print_load("Error : install_new_poke() failed: 0x%08X", result);
		goto error;
	}
	poke_installed = 1;
	print_load("* make_patches");
	result = make_patches();
	if (result != 0) {
		print_load("Error : make_patches() failed: 0x%08X", result);
		goto error;
	}
	print_load("* install_payload");
	result = install_payload();
	if (result != 0) {
		print_load("Error : install_payload() failed: 0x%08X", result);
		goto error;
	}
	payload_installed = 1;

	memset(eid_root_key, 0, EID_ROOT_KEY_SIZE);
	print_load("* run_payload");
	result = run_payload((uintptr_t)eid_root_key, EID_ROOT_KEY_SIZE);
	if (result != 0) {
		print_load("Error : run_payload() failed: 0x%08X", result);
		goto error;
	}
	print_load("* write eid_root_key");
	fp = fopen(file_path, "wb");
	if (!fp) {
		result = errno;
		print_load("Error : fopen() failed: 0x%08X", result);
		goto error;
	}
	
	fwrite(eid_root_key, 1, EID_ROOT_KEY_SIZE, fp);

	fclose(fp);

	result = 0;

error:
	if (payload_installed) {
		print_load("* remove_payload");
		result = remove_payload();
		if (result != 0)
			print_load("remove_payload() failed: 0x%08X", result);
	}

	if (poke_installed) {
		print_load("* remove_new_poke");
		result = remove_new_poke();
		if (result != 0)
			print_load("remove_new_poke() failed: 0x%08X", result);
	}

	return result;
}
