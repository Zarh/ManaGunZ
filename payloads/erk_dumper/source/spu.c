#include "spu.h"
#include "util.h"

void spu_slb_invalidate_all(struct spu_priv2 volatile* spu_priv2) {
	int i;

	spu_priv2->slb_invalidate_all = 0;

	eieio();

	for (i = 0; i < SPU_SLB_MAX_ENTRIES; ++i) {
		spu_priv2->slb_index = i;
		spu_priv2->slb_vsid = 0;
		spu_priv2->slb_esid = 0;

		eieio();
	}
}

int spu_slb_set_entry(struct spu_priv2 volatile* spu_priv2, uint64_t index, uint64_t esid, uint64_t vsid) {
	if (index >= SPU_SLB_MAX_ENTRIES)
		return -1;

	spu_priv2->slb_index = index;
	spu_priv2->slb_vsid = vsid;

	eieio();

	spu_priv2->slb_esid = esid;

	eieio();

	return 0;
}

void spu_in_mbox_write(struct spu_problem volatile* spu_problem, uint32_t value) {
	spu_problem->spu_in_mbox = value;

	eieio();
}

void spu_in_mbox_write_64(struct spu_problem volatile* spu_problem, uint64_t value) {
	spu_problem->spu_in_mbox = value >> 32;
	spu_problem->spu_in_mbox = value & 0xFFFFFFFFUL;

	eieio();
}

void spu_sig_notify_1_2_write_64(struct spu_problem volatile* spu_problem, uint64_t value) {
	spu_problem->spu_sig_notify_1 = value >> 32;
	spu_problem->spu_sig_notify_2 = value & 0xFFFFFFFFUL;

	eieio();
}

void spu_iso_load_req_enable(struct spu_priv2 volatile* spu_priv2) {
	spu_priv2->spu_privcntl = 0x4;

	eieio();
}

void spu_iso_load_req(struct spu_problem volatile* spu_problem) {
	spu_problem->spu_runcntl = SPU_RUNCNTL_ISO_LOAD_REQ;

	eieio();
}

void spu_iso_exit_req(struct spu_problem volatile* spu_problem) {
	spu_problem->spu_runcntl = SPU_RUNCNTL_ISO_EXIT_REQ;

	eieio();
}

void spu_run_req(struct spu_problem volatile* spu_problem) {
	spu_problem->spu_runcntl = SPU_RUNCNTL_RUN_REQ;

	eieio();
}

void spu_stop_req(struct spu_problem volatile* spu_problem) {
	spu_problem->spu_runcntl = SPU_RUNCNTL_STOP_REQ;

	eieio();
}

uint8_t spu_mbox_stat_intr_out_mbox_count(struct spu_problem volatile* spu_problem) {
	return ((spu_problem->spu_mbox_stat) >> 16) & 0xFF;
}

uint8_t spu_mbox_stat_in_mbox_count(struct spu_problem volatile* spu_problem) {
	return ((spu_problem->spu_mbox_stat) >> 8) & 0xFF;
}

uint8_t spu_mbox_stat_out_mbox_count(struct spu_problem volatile* spu_problem) {
	return spu_problem->spu_mbox_stat & 0xFF;
}

uint8_t spu_mfc_cmd_exec(struct spu_problem volatile* spu_problem, uint32_t lsa, uint64_t ea, uint16_t size, uint16_t tag, uint16_t classid, uint16_t cmd) {
	spu_problem->mfc_lsa = lsa;
	spu_problem->mfc_eah = ea >> 32;
	spu_problem->mfc_eal = ea & 0xFFFFFFFFUL;
	spu_problem->mfc_size_tag = (size << 16) | tag;
	spu_problem->mfc_classid_cmd_cmdstatus = (classid << 16) | cmd;

	eieio();

	return (spu_problem->mfc_classid_cmd_cmdstatus & 0x3);
}

uint8_t spu_mfc_cmd_tag_status(struct spu_problem volatile* spu_problem, uint8_t tag) {
	spu_problem->prxy_querytype = 0;
	spu_problem->prxy_querymask = 1 << tag;

	eieio();

	return (spu_problem->prxy_tagstatus >> tag) & 0x1;
}
