#include "kernel.h"
#include "hypervisor.h"
#include "spu.h"
#include "debug.h"
#include "mm.h"
#include "util.h"

#define LOADERS_TAB_OFFSET 0x10100ULL
#define METLDR_TAB_OFFSET  0x10
#define METLDR_TAB_SIZE    0x18

#define HV_OFFSET    0x14000000ULL
#define HV_PAGE_SIZE PAGE_SIZE_4KB

#define STUFF_OFFSET       0x15000000ULL
#define STUFF_PAGE_SIZE    PAGE_SIZE_4KB
#define STUFF_SIZE         0x40000ULL
#define STUFF_PORTION_SIZE 0x10000

#define DUMP_LS_ADDR  0x3E000
#define DUMP_SIZE     0x30

#define SPU_SHADOW_OFFSET  0x133D0000ULL
#define SPU_SHADOW_SIZE    0x1000UL

#define SPU_PROBLEM_OFFSET 0x13400000ULL
#define SPU_PROBLEM_SIZE   0x20000UL

#define SPU_PRIV2_OFFSET 0x13420000ULL
#define SPU_PRIV2_SIZE   0x20000UL

#define SPU_LS_OFFSET    0x13440000ULL
#define SPU_LS_SIZE      0x40000UL

extern const uint8_t dumper_payload[];
extern const uint64_t dumper_payload_size;

int payload_main(uint8_t* output_data, uint64_t output_size) {
	int result;

	uint64_t ticks;

	uint64_t hv_lpar_addr;
	uint64_t hv_mapped_size;
	uint8_t* hv;
	uint8_t* metldr;
	uint8_t* stuff;
	uint8_t* dumper;
	uint8_t* work_data;
	uint64_t metldr_offset, metldr_size;
	uint64_t stuff_lpar_addr;
	uint64_t gameos_lpar_base, gameos_lpar_size;

	uint64_t vas_id, spu_id;
	uint64_t esid, vsid;
	uint64_t priv2_addr, problem_phys, local_store_phys, shadow_addr;
	uint64_t intr_status, unused;

	struct spu_shadow volatile* spu_shadow;
	struct spu_problem volatile* spu_problem;
	struct spu_priv2 volatile* spu_priv2;

	uint8_t volatile* spu_ls;
	uint32_t spu_out_intr_mbox_value, spu_out_mbox_value;
	uint8_t mfc_cmd_tag;

	uint32_t force_exit;

	lv2_extend_kstack(0);

	result = 0;

	hv = NULL;
	metldr = NULL;
	stuff = NULL;
	dumper = NULL;
	work_data = NULL;

	hv_lpar_addr = 0;
	stuff_lpar_addr = 0;

	if (!output_data || output_size < DUMP_SIZE) {
		result = EINVAL;
		goto error;
	}

	gameos_lpar_base = *(uint64_t*)GAMEOS_LPAR_BASE_PTR;
	gameos_lpar_size = *(uint64_t*)GAMEOS_LPAR_SIZE_PTR;
	if (!gameos_lpar_base || !gameos_lpar_size) {
		result = EFAULT;
		goto error;
	}

	metldr_offset = lv1_peek64(LOADERS_TAB_OFFSET + METLDR_TAB_OFFSET);
	metldr_size = lv1_peek64(LOADERS_TAB_OFFSET + METLDR_TAB_SIZE);
	if (!metldr_offset || !metldr_size) {
		result = EFAULT;
		goto error;
	}

	hv_mapped_size = align_up(metldr_offset + metldr_size, 1 << HV_PAGE_SIZE);

	result = lv1_undocumented_function_114(0, HV_PAGE_SIZE, hv_mapped_size, &hv_lpar_addr);
	if (result != 0)
		goto error;

	MM_LOAD_BASE(hv, HV_OFFSET);

	result = mm_map_lpar_memory_region(0, MM_EA2VA(hv), hv_lpar_addr, hv_mapped_size, HV_PAGE_SIZE, 0, 0);
	if (result != 0)
		goto error;

	stuff_lpar_addr = gameos_lpar_base + gameos_lpar_size - STUFF_SIZE;

	MM_LOAD_BASE(stuff, STUFF_OFFSET);

	result = mm_map_lpar_memory_region(0, MM_EA2VA(stuff), stuff_lpar_addr, STUFF_SIZE, STUFF_PAGE_SIZE, 0, 0);
	if (result != 0)
		goto error;

	metldr = stuff;
	dumper = ptr_align_up(metldr + metldr_size, 1 << STUFF_PAGE_SIZE);
	work_data = ptr_align_up(dumper + dumper_payload_size, 1 << STUFF_PAGE_SIZE);

	lv2_memcpy(metldr, hv + metldr_offset, metldr_size);
	lv2_memcpy(dumper, dumper_payload, dumper_payload_size);
	lv2_memset(work_data, 0, DUMP_SIZE);

	result = lv1_undocumented_function_115(hv_lpar_addr);
	if (result != 0)
		goto done;

	hv_lpar_addr = 0;

	vas_id = vas_get_id();

	result = lv1_construct_logical_spu(PAGE_SIZE_4KB, PAGE_SIZE_4KB, PAGE_SIZE_4KB, PAGE_SIZE_4KB, PAGE_SIZE_4KB, vas_id, 0, &priv2_addr, &problem_phys, &local_store_phys, &unused, &shadow_addr, &spu_id);
	if (result != 0)
		goto error;

	result = lv1_enable_logical_spu(spu_id, 6);
	if (result != 0)
		goto error;

	result = lv1_set_spu_interrupt_mask(spu_id, 0, 0x7);
	if (result != 0)
		goto error;

	result = lv1_set_spu_interrupt_mask(spu_id, 1, 0xF);
	if (result != 0)
		goto error;

	result = lv1_set_spu_interrupt_mask(spu_id, 2, 0xF);
	if (result != 0)
		goto error;

	MM_LOAD_BASE(spu_shadow, SPU_SHADOW_OFFSET);

	result = mm_map_lpar_memory_region(0, MM_EA2VA(spu_shadow), shadow_addr, SPU_SHADOW_SIZE, PAGE_SIZE_4KB, 0, 0x3);
	if (result != 0)
		goto error;

	MM_LOAD_BASE(spu_problem, SPU_PROBLEM_OFFSET);

	result = mm_map_lpar_memory_region(0, MM_EA2VA(spu_problem), problem_phys, SPU_PROBLEM_SIZE, PAGE_SIZE_4KB, 0, 0);
	if (result != 0)
		goto error;

	MM_LOAD_BASE(spu_priv2, SPU_PRIV2_OFFSET);

	result = mm_map_lpar_memory_region(0, MM_EA2VA(spu_priv2), priv2_addr, SPU_PRIV2_SIZE, PAGE_SIZE_4KB, 0, 0);
	if (result != 0)
		goto error;

	MM_LOAD_BASE(spu_ls, SPU_LS_OFFSET);

	result = mm_map_lpar_memory_region(0, MM_EA2VA(spu_ls), local_store_phys, SPU_LS_SIZE, PAGE_SIZE_4KB, 0, 0);
	if (result != 0)
		goto error;

	result = lv1_set_spu_privilege_state_area_1_register(spu_id, MFC_SR1, 0x10);
	if (result != 0)
		goto error;

	spu_slb_invalidate_all(spu_priv2);

	esid = 0x8000000018000000ULL;
	vsid = 0x0000000000001400ULL;

	spu_slb_set_entry(spu_priv2, 0, esid, vsid);

	spu_priv2->spu_cfg = 0;

	eieio();

	spu_in_mbox_write_64(spu_problem, (uint64_t)dumper);
	spu_sig_notify_1_2_write_64(spu_problem, (uint64_t)metldr);
	spu_iso_load_req_enable(spu_priv2);
	spu_iso_load_req(spu_problem);

	force_exit = 0;

	while (1) {
		if (force_exit) {
			result = ECANCELED;
			goto bad;
		}

		result = lv1_get_spu_interrupt_status(spu_id, 0, &intr_status);
		if (result != 0)
			goto error;

		if (intr_status) {
			result = lv1_clear_spu_interrupt_status(spu_id, 0, intr_status, 0);
			if (result != 0)
				goto error;
		}

		result = lv1_get_spu_interrupt_status(spu_id, 1, &intr_status);
		if (result != 0)
			goto error;
			
		if (intr_status) {
			result = lv1_clear_spu_interrupt_status(spu_id, 1, intr_status, 0);
			if (result != 0)
				goto error;
		}

		result = lv1_get_spu_interrupt_status(spu_id, 2, &intr_status);
		if (result != 0)
			goto error;

		if (intr_status) {
			result = lv1_clear_spu_interrupt_status(spu_id, 2, intr_status, 0);
			if (result != 0)
				goto error;

			if (intr_status & 0x1) {
				if (spu_mbox_stat_intr_out_mbox_count(spu_problem) != 0) {
					spu_out_intr_mbox_value = spu_priv2->spu_out_intr_mbox;

					if (spu_out_intr_mbox_value == 1) {
						if (spu_mbox_stat_out_mbox_count(spu_problem) == 0) {
							result = ECANCELED;
							goto bad;
						}

						spu_out_mbox_value = spu_problem->spu_out_mbox;
						if (spu_out_mbox_value != 1) {
							result = ECANCELED;
							break;
						}

						ticks = 3 * TB_TICKS_PER_SEC;
						sleep(ticks);

						mfc_cmd_tag = 1;

						if (spu_mfc_cmd_exec(spu_problem, DUMP_LS_ADDR, (uint64_t)work_data, DUMP_SIZE, mfc_cmd_tag, 0, MFC_CMD_PUT)) {
							result = ECANCELED;
							goto bad;
						}

						while (spu_mfc_cmd_tag_status(spu_problem, mfc_cmd_tag) == 0) {
							if (force_exit) {
								result = ECANCELED;
								goto bad;
							}
						}

						force_exit = 1;
					} else if (spu_out_intr_mbox_value == 2) {
						spu_out_mbox_value = spu_problem->spu_out_mbox;

						force_exit = 1;
					}
				}
			}
		}

		if ((spu_problem->spu_status & 0x1) == 0)
			break;

		ticks = 1 * TB_TICKS_PER_SEC;
		sleep(ticks);
	}

bad:
	if (spu_shadow) {
	}

	if (spu_problem) {
		spu_iso_exit_req(spu_problem);
		spu_stop_req(spu_problem);
	}

	if (spu_priv2) {
	}

	result = lv1_destruct_logical_spu(spu_id);
	if (result != 0)
		goto error;

	if (work_data)
		result = lv2_copy_to_user(work_data, output_data, DUMP_SIZE);

	ticks = 5 * TB_TICKS_PER_SEC;
	sleep(ticks);

error:
	if (hv_lpar_addr != 0)
		result = lv1_undocumented_function_115(hv_lpar_addr);

done:
	return result;
}
