#ifndef __SPU_H__
#define __SPU_H__

#include "common.h"

#define SPU_SLB_MAX_ENTRIES 8

#define MFC_SR1 0x0000

#define MFC_CMD_PUT 0x20
#define MFC_CMD_GET 0x40

#define SPU_RUNCNTL_STOP_REQ     0x0
#define SPU_RUNCNTL_RUN_REQ      0x1
#define SPU_RUNCNTL_ISO_EXIT_REQ 0x2
#define SPU_RUNCNTL_ISO_LOAD_REQ 0x3

struct spu_shadow {
	uint8_t padding_0x0000_0x0140[0x0140 - 0x0000];
	uint64_t int_status_class0;
	uint64_t int_status_class1;
	uint64_t int_status_class2;
	uint8_t padding_0x0158_0x0610[0x0610 - 0x0158];
	uint64_t mfc_dsisr;
	uint8_t padding_0x0618_0x0620[0x0620 - 0x0618];
	uint64_t mfc_dar;
	uint8_t padding_0x0628_0x0800[0x0800 - 0x0628];
	uint64_t mfc_dsipr;
	uint8_t padding_0x0808_0x0810[0x0810 - 0x0808];
	uint64_t mfc_lscrr;
	uint8_t padding_0x0818_0x0C00[0x0C00 - 0x0818];
	uint64_t mfc_cer;
	uint8_t padding_0x0C08_0x0F00[0x0F00 - 0x0C08];
	uint64_t execution_status;
	uint8_t padding_0x0F08_0x0F10[0x0F10 - 0x0F08];
	uint64_t transition_notifier;
	uint8_t padding_0x0F08_0x1000[0x1000 - 0x0F18];
};

struct spu_priv2 {
	uint8_t padding_0x00000_0x01108[0x01108 - 0x00000];
	uint64_t slb_index;
	uint64_t slb_esid;
	uint64_t slb_vsid;
	uint64_t slb_invalidate_entry;
	uint64_t slb_invalidate_all;
	uint8_t padding_0x01130_0x04000[0x04000 - 0x01130];
	uint64_t spu_out_intr_mbox;
	uint8_t padding_0x04008_0x04040[0x04040 - 0x04008];
	uint64_t spu_privcntl;
	uint8_t padding_0x04048_0x04060[0x04060 - 0x04048];
	uint64_t spu_chnlindex;
	uint64_t spu_chnlcnt;
	uint64_t spu_chnldata;
	uint64_t spu_cfg;
	uint8_t padding_0x04080_0x20000[0x20000 - 0x04080];
};

struct spu_problem {
	uint8_t padding_0x00000_0x03004[0x03004 - 0x00000];
	uint32_t mfc_lsa;
	uint32_t mfc_eah;
	uint32_t mfc_eal;
	uint32_t mfc_size_tag;
	uint32_t mfc_classid_cmd_cmdstatus;
	uint8_t padding_0x03018_0x03104[0x03104 - 0x03018];
	uint32_t mfc_qstatus;
	uint8_t padding_0x03108_0x03204[0x03204 - 0x03108];
	uint32_t prxy_querytype;
	uint8_t padding_0x03208_0x0321C[0x0321C - 0x03208];
	uint32_t prxy_querymask;
	uint8_t padding_0x03220_0x0322C[0x0322C - 0x03220];
	uint32_t prxy_tagstatus;
	uint8_t padding_0x03230_0x04004[0x04004 - 0x03230];
	uint32_t spu_out_mbox;
	uint8_t padding_0x04008_0x0400C[0x0400C - 0x04008];
	uint32_t spu_in_mbox;
	uint8_t padding_0x04010_0x04014[0x04014 - 0x04010];
	uint32_t spu_mbox_stat;
	uint8_t padding_0x04018_0x0401C[0x0401C - 0x04018];
	uint32_t spu_runcntl;
	uint8_t padding_0x04020_0x04024[0x04024 - 0x04020];
	uint32_t spu_status;
	uint8_t padding_0x04028_0x1400C[0x1400C - 0x04028];
	uint32_t spu_sig_notify_1;
	uint8_t padding_0x14010_0x1C00C[0x1C00C - 0x14010];
	uint32_t spu_sig_notify_2;
	uint8_t padding_0x1C010_0x20000[0x20000 - 0x1C010];
};

void spu_slb_invalidate_all(struct spu_priv2 volatile* spu_priv2);
int spu_slb_set_entry(struct spu_priv2 volatile* spu_priv2, uint64_t index, uint64_t esid, uint64_t vsid);

void spu_in_mbox_write(struct spu_problem volatile* spu_problem, uint32_t value);
void spu_in_mbox_write_64(struct spu_problem volatile* spu_problem, uint64_t value);

void spu_sig_notify_1_2_write_64(struct spu_problem volatile* spu_problem, uint64_t value);

void spu_iso_load_req_enable(struct spu_priv2 volatile* spu_priv2);

void spu_iso_load_req(struct spu_problem volatile* spu_problem);
void spu_iso_exit_req(struct spu_problem volatile* spu_problem);

void spu_run_req(struct spu_problem volatile* spu_problem);
void spu_stop_req(struct spu_problem volatile* spu_problem);

uint8_t spu_mbox_stat_intr_out_mbox_count(struct spu_problem volatile* spu_problem);
uint8_t spu_mbox_stat_in_mbox_count(struct spu_problem volatile* spu_problem);
uint8_t spu_mbox_stat_out_mbox_count(struct spu_problem volatile* spu_problem);

uint8_t spu_mfc_cmd_exec(struct spu_problem volatile* spu_problem, uint32_t lsa, uint64_t ea, uint16_t size, uint16_t tag, uint16_t classid, uint16_t cmd);
uint8_t spu_mfc_cmd_tag_status(struct spu_problem volatile* spu_problem, uint8_t tag);

#endif