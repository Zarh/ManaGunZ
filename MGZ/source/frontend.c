/*
* Copyright (c) 2011-2013 by naehrwert
* This file is released under the GPLv2.
*/

#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "config.h"
#include "aes.h"
#include "util.h"
#include "keys.h"
#include "sce.h"
#include "sce_inlines.h"
#include "self.h"
#include "np.h"
#include "rvk.h"
#include "spp.h"
#include "util.h"
#include "tables.h"

/*! Parameters. */
extern char *_template;
extern char *_file_type;
extern char *_compress_data;
extern char *_skip_sections;
extern char *_key_rev;
extern char *_meta_info;
extern char *_keyset;
extern char *_auth_id;
extern char *_vendor_id;
extern char *_self_type;
extern char *_app_version;
extern char *_fw_version;
extern char *_add_shdrs;
extern char *_ctrl_flags;
extern char *_cap_flags;
#ifdef CONFIG_CUSTOM_INDIV_SEED
extern char *_indiv_seed;
#endif
extern char *_license_type;
extern char *_app_type;
extern char *_content_id;
extern char *_real_fname;
extern char *_add_sig;

extern void print_load(char *format, ...);
extern void Draw(char *text);
static BOOL _is_hexdigit(char c)
{
	if((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
		return TRUE;
	return FALSE;
}

static BOOL _is_hexnumber(const char *str)
{
	unsigned int i, len = strlen(str);
	for(i = 0; i < len; i++)
		if(_is_hexdigit(str[i]) == FALSE)
			return FALSE;
	return TRUE;
}

static BOOL _fill_self_config_template(char *file, self_config_t *sconf)
{
	unsigned char *buf = _read_buffer(file, NULL);
	if(buf != NULL)
	{
		sce_buffer_ctxt_t *ctxt = sce_create_ctxt_from_buffer(buf);
		if(ctxt != NULL)
		{
			if(sce_decrypt_header(ctxt, NULL, NULL))
			{
				_LOG_VERBOSE("Template header decrypted.\n");

				_LOG_VERBOSE("Using:\n");
				sconf->key_revision = ctxt->sceh->key_revision;
				_IF_VERBOSE(print_load(" Key Revision 0x%04X\n", sconf->key_revision));
				sconf->auth_id = ctxt->self.ai->auth_id;
				_IF_VERBOSE(print_load(" Auth-ID      0x%016llX\n", sconf->auth_id));
				sconf->vendor_id = ctxt->self.ai->vendor_id;
				_IF_VERBOSE(print_load(" Vendor-ID    0x%08X\n", sconf->vendor_id));
				sconf->self_type = ctxt->self.ai->self_type;
				_IF_VERBOSE(print_load(" SELF-Type    0x%08X\n", sconf->self_type));
				sconf->app_version = ctxt->self.ai->version;
				_IF_VERBOSE(print_load(" APP Version  0x%016llX\n", sconf->app_version));

				control_info_t *ci = sce_get_ctrl_info(ctxt, CONTROL_INFO_TYPE_DIGEST);
				ci_data_digest_40_t *cid = (ci_data_digest_40_t *)((unsigned char *)ci + sizeof(control_info_t));
				_es_ci_data_digest_40(cid);
				sconf->fw_version = cid->fw_version;
				_IF_VERBOSE(print_load(" FW Version   0x%016llX\n", sconf->fw_version));

				ci = sce_get_ctrl_info(ctxt, CONTROL_INFO_TYPE_FLAGS);
				sconf->ctrl_flags = (unsigned char *)_memdup(((unsigned char *)ci) + sizeof(control_info_t), 0x20);
				_IF_VERBOSE(_hexdump(stdout, " Control Flags   ", 0, sconf->ctrl_flags, 0x20, 0));


				opt_header_t *oh = sce_get_opt_header(ctxt, OPT_HEADER_TYPE_CAP_FLAGS);
				sconf->cap_flags = (unsigned char *)_memdup(((unsigned char *)oh) + sizeof(opt_header_t), 0x20);
				_IF_VERBOSE(_hexdump(stdout, " Capability Flags", 0, sconf->cap_flags, 0x20, 0));

#ifdef CONFIG_CUSTOM_INDIV_SEED
				sconf->indiv_seed = NULL;
				if(ctxt->self.ai->self_type == SELF_TYPE_ISO)
				{
					oh = sce_get_opt_header(ctxt, OPT_HEADER_TYPE_INDIV_SEED);
					sconf->indiv_seed = (unsigned char *)_memdup(((unsigned char *)oh) + sizeof(opt_header_t), oh->size - sizeof(opt_header_t));
					sconf->indiv_seed_size = oh->size - sizeof(opt_header_t);
					_IF_VERBOSE(_hexdump(stdout, " Individuals Seed", 0, sconf->indiv_seed, sconf->indiv_seed_size, 0));
				}
#endif

				sconf->add_shdrs = TRUE;
				if(_add_shdrs != NULL)
					if(strcmp(_add_shdrs, "FALSE") == 0)
						sconf->add_shdrs = FALSE;

				sconf->skip_sections = TRUE;
				if(_skip_sections != NULL)
					if(strcmp(_skip_sections, "FALSE") == 0)
						sconf->skip_sections = FALSE;

				sconf->npdrm_config = NULL;

				return TRUE;
			}
			else
				print_load("Warning: Could not decrypt template header.\n");
			free(ctxt);
		}
		else
			print_load("Error: Could not process template %s\n", file);
		free(buf);
	}
	else
		print_load("Error: Could not load template %s\n", file);

	return FALSE;
}

static BOOL _fill_self_config(self_config_t *sconf)
{
	if(_key_rev == NULL)
	{
		print_load("Error: Please specify a key revision.\n");
		return FALSE;
	}
	if(_is_hexnumber(_key_rev) == FALSE)
	{
		print_load("Error (Key Revision): Please provide a valid hexadecimal number.\n");
		return FALSE;
	}
	sconf->key_revision = _x_to_u64(_key_rev);

	if(_auth_id == NULL)
	{
		print_load("Error: Please specify an auth ID.\n");
		return FALSE;
	}
	sconf->auth_id = _x_to_u64(_auth_id);

	if(_vendor_id == NULL)
	{
		print_load("Error: Please specify a vendor ID.\n");
		return FALSE;
	}
	sconf->vendor_id = _x_to_u64(_vendor_id);

	if(_self_type == NULL)
	{
		print_load("Error: Please specify a SELF type.\n");
		return FALSE;
	}
	unsigned long long int type = _get_id(_self_types_params, _self_type);
	if(type == (unsigned long long int)(-1))
	{
		print_load("Error: Invalid SELF type.\n");
		return FALSE;
	}
	sconf->self_type = type;

	if(_app_version == NULL)
	{
		print_load("Error: Please specify an application version.\n");
		return FALSE;
	}
	sconf->app_version = _x_to_u64(_app_version);

	sconf->fw_version = 0;
	if(_fw_version != NULL)
		sconf->fw_version = _x_to_u64(_fw_version);

	sconf->add_shdrs = TRUE;
	if(_add_shdrs != NULL)
		if(strcmp(_add_shdrs, "FALSE") == 0)
			sconf->add_shdrs = FALSE;

	sconf->skip_sections = TRUE;
	if(_skip_sections != NULL)
		if(strcmp(_skip_sections, "FALSE") == 0)
			sconf->skip_sections = FALSE;

	sconf->ctrl_flags = NULL;
	if(_ctrl_flags != NULL)
	{
		if(strlen(_ctrl_flags) != 0x20*2)
		{
			print_load("Error: Control flags need to be 32 bytes.\n");
			return FALSE;
		}
		sconf->ctrl_flags = _x_to_u8_buffer(_ctrl_flags);
	}

	sconf->cap_flags = NULL;
	if(_cap_flags != NULL)
	{
		if(strlen(_cap_flags) != 0x20*2)
		{
			print_load("Error: Capability flags need to be 32 bytes.\n");
			return FALSE;
		}
		sconf->cap_flags = _x_to_u8_buffer(_cap_flags);
	}

#ifdef CONFIG_CUSTOM_INDIV_SEED
	sconf->indiv_seed = NULL;
	if(_indiv_seed != NULL)
	{
		unsigned int len = strlen(_indiv_seed);
		if(len > 0x100*2)
		{
			print_load("Error: Individuals seed must be <= 0x100 bytes.\n");
			return FALSE;
		}
		sconf->indiv_seed = _x_to_u8_buffer(_indiv_seed);
		sconf->indiv_seed_size = len / 2;
	}
#endif

	sconf->npdrm_config = NULL;

	return TRUE;
}

static BOOL _fill_npdrm_config(self_config_t *sconf)
{
	if((sconf->npdrm_config = (npdrm_config_t *)malloc(sizeof(npdrm_config_t))) == NULL)
		return FALSE;

	if(_license_type == NULL)
	{
		print_load("Error: Please specify a license type.\n");
		return FALSE;
	}
	//TODO!
	if(strcmp(_license_type, "FREE") == 0)
		sconf->npdrm_config->license_type = NP_LICENSE_FREE;
	else if(strcmp(_license_type, "LOCAL") == 0)
		sconf->npdrm_config->license_type = NP_LICENSE_LOCAL;
	else
	{
		print_load("Error: Only supporting LOCAL and FREE license for now.\n");
		return FALSE;
	}

	if(_app_type == NULL)
	{
		print_load("Error: Please specify an application type.\n");
		return FALSE;
	}
	unsigned long long int type = _get_id(_np_app_types, _app_type);
	if(type == (unsigned long long int)(-1))
	{
		print_load("Error: Invalid application type.\n");
		return FALSE;
	}
	sconf->npdrm_config->app_type = type;

	if(_content_id == NULL)
	{
		print_load("Error: Please specify a content ID.\n");
		return FALSE;
	}
	strncpy((char *)sconf->npdrm_config->content_id, _content_id, 0x30);

	if(_real_fname == NULL)
	{
		print_load("Error: Please specify a real filename.\n");
		return FALSE;
	}
	sconf->npdrm_config->real_fname = _real_fname;

	return TRUE;
}

int frontend_decrypt(char *file_in, char *file_out)
{
	unsigned char *buf = _read_buffer(file_in, NULL);
	if(buf != NULL)
	{
		sce_buffer_ctxt_t *ctxt = sce_create_ctxt_from_buffer(buf);
		if(ctxt != NULL)
		{
			unsigned char *meta_info = NULL;
			if(_meta_info != NULL)
			{
				if(strlen(_meta_info) != 0x40*2)
				{
					print_load("Error: Metadata info needs to be 64 bytes.");
					return -1;
				}
				meta_info = _x_to_u8_buffer(_meta_info);
			}

			unsigned char *keyset = NULL;
			if(_keyset != NULL)
			{
				if(strlen(_keyset) != (0x20 + 0x10 + 0x15 + 0x28 + 0x01)*2)
				{
					print_load("Error: Keyset has a wrong length.\n");
					return -1;
				}
				keyset = _x_to_u8_buffer(_keyset);
			}

			if(sce_decrypt_header(ctxt, meta_info, keyset))
			{
				_LOG_VERBOSE("Header decrypted.\n");
				if(sce_decrypt_data(ctxt))
				{
					_LOG_VERBOSE("Data decrypted.\n");
					if(ctxt->sceh->header_type == SCE_HEADER_TYPE_SELF)
					{
						if(self_write_to_elf(ctxt, file_out)!= TRUE)
						{
							print_load("Error: Could not write ELF.\n");
							return -1;
						}
					}
					else if(ctxt->sceh->header_type == SCE_HEADER_TYPE_RVK)
					{
						if(_write_buffer(file_out, ctxt->scebuffer + ctxt->metash[0].data_offset, 
							ctxt->metash[0].data_size + ctxt->metash[1].data_size) == 0)
						{
							print_load("Error: Could not write RVK.\n");
							return -1;
						}
					}
					else if(ctxt->sceh->header_type == SCE_HEADER_TYPE_PKG)
					{
						/*if(_write_buffer(file_out, ctxt->scebuffer + ctxt->metash[0].data_offset, 
							ctxt->metash[0].data_size + ctxt->metash[1].data_size + ctxt->metash[2].data_size))
							print_load("PKG written to %s.\n", file_out);
						else
							print_load("Error: Could not write PKG.\n");*/
						print_load("soon...\n");
						return -1;
					}
					else if(ctxt->sceh->header_type == SCE_HEADER_TYPE_SPP)
					{
						if(_write_buffer(file_out, ctxt->scebuffer + ctxt->metash[0].data_offset, 
							ctxt->metash[0].data_size + ctxt->metash[1].data_size) == 0)
						{
							print_load("Error: Could not write SPP.\n");
							return -1;
						}
					}
				}
				else 
				{
					print_load("Error: Could not decrypt data.\n");
					return -1;
				}
			}
			else 
			{
				print_load("Error: Could not decrypt header.\n");
				free(ctxt);
				return -1;
			}
		}
		else
		{
			print_load("Error: Could not process file\n");
			free(buf);
			return -1;
		}
	}
	else 
	{
		print_load("Error: Could not load file\n");
		return -1;
	}
	
	return 0;
	
}

int frontend_encrypt(char *file_in, char *file_out)
{
	BOOL can_compress = FALSE;
	self_config_t sconf;
	sce_buffer_ctxt_t *ctxt = NULL;
	unsigned int file_len = 0;
	unsigned char *file;
	
	if(_file_type == NULL)
	{
		print_load("Error: Please specify a file type.\n");
		return -1;
	}
	
	unsigned char *keyset = NULL;
	if(_keyset != NULL)
	{
		if(strlen(_keyset) != (0x20 + 0x10 + 0x15 + 0x28 + 0x01)*2)
		{
			print_load("Error: Keyset has a wrong length.\n");
			return -1;
		}
		keyset = _x_to_u8_buffer(_keyset);
	}
		
	if((file = _read_buffer(file_in, &file_len)) == NULL)
	{
		print_load("Error: Could not read file.");
		return -1;
	}
	
	if(strcmp(_file_type, "SELF") == 0)
	{
		if(_self_type == NULL && _template == NULL)
		{
			print_load("Error: Please specify a SELF type.\n");
			return -1;
		}
		
		if(_template != NULL)
		{
			//Use a template SELF to fill the config.
			if(_fill_self_config_template(_template, &sconf) == FALSE)
				return -1;
		}
		else
		{
			//Fill the config from command line arguments.
			if(_fill_self_config(&sconf) == FALSE)
				return -1;
		}
		
		if(sconf.self_type == SELF_TYPE_NPDRM)
			if(_fill_npdrm_config(&sconf) == FALSE)
				return -1;
		ctxt = sce_create_ctxt_build_self(file, file_len);
		if(self_build_self(ctxt, &sconf) != TRUE) {
			print_load("Error: SELF not built.\n");
			return -1;
		}
		//SPU SELFs may not be compressed.
		if(!(sconf.self_type == SELF_TYPE_LDR || sconf.self_type == SELF_TYPE_ISO))
			can_compress = TRUE;
	}
	else if(strcmp(_file_type, "RVK") == 0)
	{
		print_load("soon...\n");
		return -1;
	}
	else if(strcmp(_file_type, "PKG") == 0)
	{
		print_load("soon...\n");
		return -1;
	}
	else if(strcmp(_file_type, "SPP") == 0)
	{
		print_load("soon...\n");
		return -1;
	}
	
	//Compress data if wanted.
	if(_compress_data != NULL && strcmp(_compress_data, "TRUE") == 0)
	{
		if(can_compress == TRUE)	{
			sce_compress_data(ctxt);
		}	else	print_load("Warning: This type of file will not be compressed.\n");
	}

	//Layout and encrypt context.
	sce_layout_ctxt(ctxt);
	if(sce_encrypt_ctxt(ctxt, keyset) != TRUE)	{
		print_load("Error: Data not encrypted.\n");
		return -1;
	}

	//Write file.
	if(sce_write_ctxt(ctxt, file_out) == TRUE)
	{
		//Add NPDRM footer signature.
		if(sconf.self_type == SELF_TYPE_NPDRM && _add_sig != NULL && strcmp(_add_sig, "TRUE") == 0)
		{
			if(np_sign_file(file_out) != TRUE) 
			{
				print_load("Error: Could not add NPDRM footer signature.\n");
				return -1;
			}	
		}
	}
	else 
	{
		print_load("Error: File not written.\n");
		return -1;
	}
	
	return 0;
}
