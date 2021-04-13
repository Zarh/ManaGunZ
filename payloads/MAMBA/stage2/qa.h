#ifndef _QA_H
#define _QA_H

#define SHA_BLOCKSIZE        (64)
#define SHA_DIGEST_LENGTH    (20)

#define PS3DM_PID(fid, id)    ((fid) | (id))
#define PS3DM_FID(pid)        ((pid) & ~0xffful)

#define UM_PATCH_OFFSET     0x80000000000FEBD4ULL
#define DM_PATCH1_OFFSET    0x800000000016FA64ULL
#define DM_PATCH2_OFFSET    0x800000000016FA88ULL
#define DM_PATCH3_OFFSET    0x800000000016FB00ULL
#define DM_PATCH4_OFFSET    0x800000000016FB08ULL

#define HV_SIZE2            0x001000 
#define HV_PAGE_SIZE        0x0C 

#define TOKEN_SIZE          0x50
#define IDPS_SIZE           0x10

#define QA_FLAG_OFFSET      0x48C0A

enum ps3dm_function_packet
{
    /* SC manager */
    PS3DM_FID_SCM                    = 0x00009000,
    PS3DM_PID_SCM_GET_REGION_DATA    = PS3DM_PID(PS3DM_FID_SCM, 6),
    PS3DM_PID_SCM_READ_EEPROM        = PS3DM_PID(PS3DM_FID_SCM, 0xB),
    PS3DM_PID_SCM_WRITE_EEPROM       = PS3DM_PID(PS3DM_FID_SCM, 0xC),
};

struct ps3dm_header
{
    uint32_t tag;
    uint32_t fid;            /* enum ps3dm_function_packet */
    uint32_t payload_length;
    uint32_t reply_length;
};

struct ps3dm_ss_header
{
    uint64_t pid;            /* enum ps3dm_function_packet */
    uint64_t fid;            /* enum ps3dm_function_packet */
    uint32_t status;
    uint8_t res[4];
    uint64_t laid;
    uint64_t paid;
};

struct ps3dm_scm_write_eeprom
{
    struct ps3dm_header dm_hdr;
    struct ps3dm_ss_header ss_hdr;
    u32 offset;
    u8 res1[4];
    u32 nwrite;
    u8 res2[4];
    u64 buf_size;
    u8 buf[0x50];
};

static inline void ps3dm_init_header(struct ps3dm_header *hdr, uint32_t tag, uint32_t fid, uint32_t payload_length, uint32_t reply_length)
{
    hdr->tag = tag;
    hdr->fid = fid;
    hdr->payload_length = payload_length;
    hdr->reply_length = reply_length;
}

static inline void ps3dm_init_ss_header( struct ps3dm_ss_header *hdr, uint64_t pid, uint64_t laid, uint64_t paid)
{
    hdr->pid = pid;
    hdr->fid = PS3DM_FID(pid);
    hdr->laid = laid;
    hdr->paid = paid;
}

static inline u64 lv1_peekd2(u64 addr)
{
    return *(u64 *)(HV_BASE + addr);
}

static inline void lv1_poked2(u64 addr, u64 value)
{
    *(u64 *)(HV_BASE + addr) = value;
}

uint8_t read_qa_flag();
int set_qa_flag(uint8_t value);

#endif /* _QA_H */
