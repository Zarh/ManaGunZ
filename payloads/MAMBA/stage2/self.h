#ifndef SELF_H__
#define SELF_H__

#include <stdint.h>

//#define SCE_MAGIC 		0x53434500
//#define ELF_MAGIC			0x7F454C46
#define SPRX_EXT_MAGIC		0x6F8A81B0879A3200ULL
#define SPRX_EXT_MAGIC2		0x4A52A57F5957E800ULL
#define SPRX_EXT_MAGIC_MASK	0xFFFFFFFFFFFFFF00ULL

typedef struct
{
	u32 magic;               // 0
	u32 version;             // 4
	uint16_t flags;               // 8
	uint16_t type;                // A
	u32 metadata_offset;     // C
	u64 header_len;          // 10
	u64 elf_filesize;        // 18
	u64 unknown;             // 20
	u64 appinfo_offset;      // 28
	u64 elf_offset;          // 30
	u64 phdr_offset;         // 38
	u64 shdr_offset;         // 40
	u64 section_info_offset; // 48
	u64 sceversion_offset;   // 50
	u64 controlinfo_offset;  // 58
	u64 controlinfo_size;    // 60
	u64 padding;
} __attribute__((packed)) SELF;

/* typedef struct
{
	u64 authid; // 0
	u32 vendor_id; // 8
	u32 self_type; // c
	u32 version; // 10
	u8 padding[12];
} __attribute__((packed)) APP_INFO;
*/

/* typedef struct
{
	u32 magic;
	u8 ident[12];
	uint16_t type;
	uint16_t machine;
	u32 version;
	u64 entry_point;
	u64 phdr_offset;
	u64 shdr_offset;
	uint16_t flags;
	u32 header_size;
	uint16_t phent_size;
	uint16_t phnum;
	uint16_t shent_size;
	uint16_t shnum;
	uint16_t shstrndx;
} __attribute__((packed)) ELF; */

/* typedef struct
{
	u32 type;
	u32 flags;
	u64 offset_in_file;
	u64 vitual_addr;
	u64 phys_addr;
	u64 segment_size;
	u64 segment_mem_size;
	u64 alignment;
} __attribute__((packed)) ELF_PHDR;
*/
/* typedef struct
{
	u32 name_idx;
	u32 type;
	u64 flags;
	u64 virtual_addr;
	u64 offset_in_file;
	u64 segment_size;
	u32 link;
	u32 info;
	u64 addr_align;
	u64 entry_size;
} __attribute__((packed)) ELF_SHDR; */

/* typedef struct
{
	u64 offset;
	u64 size;
	u32 compressed; // 2=compressed
	u32 unknown1;
	u32 unknown2;
	u32 encrypted; // 1=encrypted
} __attribute__((packed)) SECTION_INFO; */

/* typedef struct {
	u32 unknown1;
	u32 unknown2;
	u32 unknown3;
	u32 unknown4;
} __attribute__((packed)) SCEVERSION_INFO; */

/* typedef struct
{
	u32 type; // 1==control flags; 2==file digest        0
	u32 size; // 4
	union
	{
		// type 1
		struct
		{
			u64 control_flags; // 8
			u8 padding[32]; // 10
		} control_flags;

		// type 2
		struct
		{
			u64 unknown; // 8
			u8 digest1[20]; // 10
			u8 digest2[20]; // 24
			u8 padding[8]; // 38
		} file_digest;
	};
} __attribute__((packed)) CONTROL_INFO; */

/* typedef struct
{
	//u8 ignore[32];
	u8 key[16];
	u8 key_pad[16];
	u8 iv[16];
	u8 iv_pad[16];
} __attribute__((packed)) METADATA_INFO; */

/* typedef struct
{
	u64 signature_input_length;
	u32 unknown1;
	u32 section_count;
	u32 key_count;
	u32 signature_info_size;
	u64 unknown2;
} __attribute__((packed)) METADATA_HEADER; */

/* typedef struct
{
	u64 data_offset;
	u64 data_size;
	u32 type; // 1 = shdr, 2 == phdr
	u32 program_idx;
	u32 unknown;
	u32 sha1_idx;
	u32 encrypted; // 3=yes; 1=no
	u32 key_idx;
	u32 iv_idx;
	u32 compressed; // 2=yes; 1=no
} __attribute__((packed)) METADATA_SECTION_HEADER; */

/* typedef struct
{
	u8 sha1[20];
	u8 padding[12];
	u8 hmac_key[64];
} __attribute__((packed)) SECTION_HASH; */

/* typedef struct
{
	u32 unknown1;
	u32 signature_size;
	u64 unknown2;
	u64 unknown3;
	u64 unknown4;
	u64 unknown5;
	u32 unknown6;
	u32 unknown7;
} __attribute__((packed)) SIGNATURE_INFO; */

/* typedef struct
{
	u8 r[21];
	u8 s[21];
	u8 padding[6];
} __attribute__((packed)) SIGNATURE; */


/* typedef struct
{
	u8 *data;
	u64 size;
	u64 offset;
} SELF_SECTION; */


typedef struct
{
	u64 magic;
	u64 nonce_mod;
	u8 keys_mod[16];
} __attribute__((packed)) SPRX_EXT_HEADER;

#endif /* SELF_H__ */
