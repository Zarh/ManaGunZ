#ifndef __PS2EMU_SYMBOLS_H_S__
#define __PS2EMU_SYMBOLS_H_S__

#ifdef PS2HWEMU

	#define DATA_TOC_OFFSET              -0x7358
	#define DATA_SUBTOC_OFFSET           0x20
	#define LPAR_SUBTOC_OFFSET           0x18
	#define FILESZ_TOC_OFFSET            -0x63E0

	#ifdef FIRMWARE_421
		#define TOC                                      0x4EAE30
		#define DISC_SIZE_OFFSET                         0x255A0
		#define DISC_TYPE_OFFSET                         0x2519C
		#define cdvd_send_atapi_command_symbol           0x21FC4
		#define ufs_open_symbol                          0x4DF34
		#define ufs_close_symbol                         0x4E6C0
		#define ufs_read_symbol                          0x4DA04
		#define ufs_write_symbol                         0x4DAF8
		#define ufs_fstat_symbol                         0x4E9C4
		#define zeroalloc_symbol                         0xFDE70
		#define malloc_symbol                            0xFDD88
		#define free_symbol                              0xFDEC8
		#define memcpy_symbol                            0xDFAC
		#define memset_symbol                            0xD488
		#define strcpy_symbol                            0xED04
		#define strcat_symbol                            0xEED0
		#define strlen_symbol                            0xECD8
		#define vuart_read_symbol                        0x1E338
		#define vuart_write_symbol                       0x1E288
		#define ps2_disc_auth_symbol                     0x2053C
		#define ps2_disc_auth_caller_symbol              0x51184
		#define overwritten_symbol                       0x23BF8
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x021f0000
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_430
		#define TOC                                      0x4EB750
		#define DISC_SIZE_OFFSET                         0x255A0
		#define DISC_TYPE_OFFSET                         0x2519C
		#define cdvd_send_atapi_command_symbol           0x21FC4
		#define ufs_open_symbol                          0x4DF34
		#define ufs_close_symbol                         0x4E6C0
		#define ufs_read_symbol                          0x4DA04
		#define ufs_write_symbol                         0x4DAF8
		#define ufs_fstat_symbol                         0x4E9C4
		#define zeroalloc_symbol                         0xFDE70
		#define malloc_symbol                            0xFDD88
		#define free_symbol                              0xFDEC8
		#define memcpy_symbol                            0xDFAC
		#define memset_symbol                            0xD488
		#define strcpy_symbol                            0xED04
		#define strcat_symbol                            0xEED0
		#define strlen_symbol                            0xECD8
		#define vuart_read_symbol                        0x1E338
		#define vuart_write_symbol                       0x1E288
		#define ps2_disc_auth_symbol                     0x2053C
		#define ps2_disc_auth_caller_symbol              0x51184
		#define overwritten_symbol                       0x23BF8
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x021f0000
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_431
		#define TOC                                      0x4EB750
		#define DISC_SIZE_OFFSET                         0x255A0
		#define DISC_TYPE_OFFSET                         0x2519C
		#define cdvd_send_atapi_command_symbol           0x21FC4
		#define ufs_open_symbol                          0x4DF34
		#define ufs_close_symbol                         0x4E6C0
		#define ufs_read_symbol                          0x4DA04
		#define ufs_write_symbol                         0x4DAF8
		#define ufs_fstat_symbol                         0x4E9C4
		#define zeroalloc_symbol                         0xFDE70
		#define malloc_symbol                            0xFDD88
		#define free_symbol                              0xFDEC8
		#define memcpy_symbol                            0xDFAC
		#define memset_symbol                            0xD488
		#define strcpy_symbol                            0xED04
		#define strcat_symbol                            0xEED0
		#define strlen_symbol                            0xECD8
		#define vuart_read_symbol                        0x1E338
		#define vuart_write_symbol                       0x1E288
		#define ps2_disc_auth_symbol                     0x2053C
		#define ps2_disc_auth_caller_symbol              0x51184
		#define overwritten_symbol                       0x23BF8
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x021f0000
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_440
		#define TOC                                      0x4EB840
		#define DISC_SIZE_OFFSET                         0x25694
		#define DISC_TYPE_OFFSET                         0x25290
		#define cdvd_send_atapi_command_symbol           0x220B8
		#define ufs_open_symbol                          0x4E028
		#define ufs_close_symbol                         0x4E7B4
		#define ufs_read_symbol                          0x4DAF8
		#define ufs_write_symbol                         0x4DBEC
		#define ufs_fstat_symbol                         0x4EAB8
		#define zeroalloc_symbol                         0xFDF60
		#define malloc_symbol                            0xFDE78
		#define free_symbol                              0xFDFB8
		#define memcpy_symbol                            0xDFAC
		#define memset_symbol                            0xD488
		#define strcpy_symbol                            0xED04
		#define strcat_symbol                            0xEED0
		#define strlen_symbol                            0xECD8
		#define vuart_read_symbol                        0x1E42C
		#define vuart_write_symbol                       0x1E37C
		#define ps2_disc_auth_symbol                     0x20630
		#define ps2_disc_auth_caller_symbol              0x51278
		#define overwritten_symbol                       0x23CEC
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x021f0000
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_441
		#define TOC                                      0x4EB840
		#define DISC_SIZE_OFFSET                         0x25694
		#define DISC_TYPE_OFFSET                         0x25290
		#define cdvd_send_atapi_command_symbol           0x220B8
		#define ufs_open_symbol                          0x4E028
		#define ufs_close_symbol                         0x4E7B4
		#define ufs_read_symbol                          0x4DAF8
		#define ufs_write_symbol                         0x4DBEC
		#define ufs_fstat_symbol                         0x4EAB8
		#define zeroalloc_symbol                         0xFDF60
		#define malloc_symbol                            0xFDE78
		#define free_symbol                              0xFDFB8
		#define memcpy_symbol                            0xDFAC
		#define memset_symbol                            0xD488
		#define strcpy_symbol                            0xED04
		#define strcat_symbol                            0xEED0
		#define strlen_symbol                            0xECD8
		#define vuart_read_symbol                        0x1E42C
		#define vuart_write_symbol                       0x1E37C
		#define ps2_disc_auth_symbol                     0x20630
		#define ps2_disc_auth_caller_symbol              0x51278
		#define overwritten_symbol                       0x23CEC
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x021f0000
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_446
		#define TOC                                      0x4EB840
		#define DISC_SIZE_OFFSET                         0x25694
		#define DISC_TYPE_OFFSET                         0x25290
		#define cdvd_send_atapi_command_symbol           0x220B8
		#define ufs_open_symbol                          0x4E028
		#define ufs_close_symbol                         0x4E7B4
		#define ufs_read_symbol                          0x4DAF8
		#define ufs_write_symbol                         0x4DBEC
		#define ufs_fstat_symbol                         0x4EAB8
		#define zeroalloc_symbol                         0xFDF60
		#define malloc_symbol                            0xFDE78
		#define free_symbol                              0xFDFB8
		#define memcpy_symbol                            0xDFAC
		#define memset_symbol                            0xD488
		#define strcpy_symbol                            0xED04
		#define strcat_symbol                            0xEED0
		#define strlen_symbol                            0xECD8
		#define vuart_read_symbol                        0x1E42C
		#define vuart_write_symbol                       0x1E37C
		#define ps2_disc_auth_symbol                     0x20630
		#define ps2_disc_auth_caller_symbol              0x51278
		#define overwritten_symbol                       0x23CEC
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x021f0000
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_450
		#define TOC                                      0x4EB840
		#define DISC_SIZE_OFFSET                         0x25694
		#define DISC_TYPE_OFFSET                         0x25290
		#define cdvd_send_atapi_command_symbol           0x220B8
		#define ufs_open_symbol                          0x4E028
		#define ufs_close_symbol                         0x4E7B4
		#define ufs_read_symbol                          0x4DAF8
		#define ufs_write_symbol                         0x4DBEC
		#define ufs_fstat_symbol                         0x4EAB8
		#define zeroalloc_symbol                         0xFDF6C
		#define malloc_symbol                            0xFDE84
		#define free_symbol                              0xFDFC4
		#define memcpy_symbol                            0xDFAC
		#define memset_symbol                            0xD488
		#define strcpy_symbol                            0xED04
		#define strcat_symbol                            0xEED0
		#define strlen_symbol                            0xECD8
		#define vuart_read_symbol                        0x1E42C
		#define vuart_write_symbol                       0x1E37C
		#define ps2_disc_auth_symbol                     0x20630
		#define ps2_disc_auth_caller_symbol              0x51278
		#define overwritten_symbol                       0x23CEC
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x021f0000
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_453
		#define TOC                                      0x4EB8C0
		#define DISC_SIZE_OFFSET                         0x25714
		#define DISC_TYPE_OFFSET                         0x25310
		#define cdvd_send_atapi_command_symbol           0x22138
		#define ufs_open_symbol                          0x4E0A8
		#define ufs_close_symbol                         0x4E834
		#define ufs_read_symbol                          0x4DB78
		#define ufs_write_symbol                         0x4DC6C
		#define ufs_fstat_symbol                         0x4EB38
		#define zeroalloc_symbol                         0xFDFEC
		#define malloc_symbol                            0xFDF04
		#define free_symbol                              0xFE044
		#define memcpy_symbol                            0xDFAC
		#define memset_symbol                            0xD488
		#define strcpy_symbol                            0xED04
		#define strcat_symbol                            0xEED0
		#define strlen_symbol                            0xECD8
		#define vuart_read_symbol                        0x1E42C
		#define vuart_write_symbol                       0x1E37C
		#define ps2_disc_auth_symbol                     0x206B0
		#define ps2_disc_auth_caller_symbol              0x512F8
		#define overwritten_symbol                       0x23D6C
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x021f0000
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_455
		#define TOC                                      0x4EB8C0
		#define DISC_SIZE_OFFSET                         0x25714
		#define DISC_TYPE_OFFSET                         0x25310
		#define cdvd_send_atapi_command_symbol           0x22138
		#define ufs_open_symbol                          0x4E0A8
		#define ufs_close_symbol                         0x4E834
		#define ufs_read_symbol                          0x4DB78
		#define ufs_write_symbol                         0x4DC6C
		#define ufs_fstat_symbol                         0x4EB38
		#define zeroalloc_symbol                         0xFDFEC
		#define malloc_symbol                            0xFDF04
		#define free_symbol                              0xFE044
		#define memcpy_symbol                            0xDFAC
		#define memset_symbol                            0xD488
		#define strcpy_symbol                            0xED04
		#define strcat_symbol                            0xEED0
		#define strlen_symbol                            0xECD8
		#define vuart_read_symbol                        0x1E42C
		#define vuart_write_symbol                       0x1E37C
		#define ps2_disc_auth_symbol                     0x206B0
		#define ps2_disc_auth_caller_symbol              0x512F8
		#define overwritten_symbol                       0x23D6C
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x021f0000
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_460
		#define TOC                                      0x4EB8C0
		#define DISC_SIZE_OFFSET                         0x25714
		#define DISC_TYPE_OFFSET                         0x25310
		#define cdvd_send_atapi_command_symbol           0x22138
		#define ufs_open_symbol                          0x4E0A8
		#define ufs_close_symbol                         0x4E834
		#define ufs_read_symbol                          0x4DB78
		#define ufs_write_symbol                         0x4DC6C
		#define ufs_fstat_symbol                         0x4EB38
		#define zeroalloc_symbol                         0xFDFEC
		#define malloc_symbol                            0xFDF04
		#define free_symbol                              0xFE044
		#define memcpy_symbol                            0xDFAC
		#define memset_symbol                            0xD488
		#define strcpy_symbol                            0xED04
		#define strcat_symbol                            0xEED0
		#define strlen_symbol                            0xECD8
		#define vuart_read_symbol                        0x1E42C
		#define vuart_write_symbol                       0x1E37C
		#define ps2_disc_auth_symbol                     0x206B0
		#define ps2_disc_auth_caller_symbol              0x512F8
		#define overwritten_symbol                       0x23D6C
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x021f0000
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_465
		#define TOC                                      0x4EB8C0
		#define DISC_SIZE_OFFSET                         0x25714
		#define DISC_TYPE_OFFSET                         0x25310
		#define cdvd_send_atapi_command_symbol           0x22138
		#define ufs_open_symbol                          0x4E0A8
		#define ufs_close_symbol                         0x4E834
		#define ufs_read_symbol                          0x4DB78
		#define ufs_write_symbol                         0x4DC6C
		#define ufs_fstat_symbol                         0x4EB38
		#define zeroalloc_symbol                         0xFDFEC
		#define malloc_symbol                            0xFDF04
		#define free_symbol                              0xFE044
		#define memcpy_symbol                            0xDFAC
		#define memset_symbol                            0xD488
		#define strcpy_symbol                            0xED04
		#define strcat_symbol                            0xEED0
		#define strlen_symbol                            0xECD8
		#define vuart_read_symbol                        0x1E42C
		#define vuart_write_symbol                       0x1E37C
		#define ps2_disc_auth_symbol                     0x206B0
		#define ps2_disc_auth_caller_symbol              0x512F8
		#define overwritten_symbol                       0x23D6C
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x021f0000
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_466
		#define TOC                                      0x4EB8C0
		#define DISC_SIZE_OFFSET                         0x25714
		#define DISC_TYPE_OFFSET                         0x25310
		#define cdvd_send_atapi_command_symbol           0x22138
		#define ufs_open_symbol                          0x4E0A8
		#define ufs_close_symbol                         0x4E834
		#define ufs_read_symbol                          0x4DB78
		#define ufs_write_symbol                         0x4DC6C
		#define ufs_fstat_symbol                         0x4EB38
		#define zeroalloc_symbol                         0xFDFEC
		#define malloc_symbol                            0xFDF04
		#define free_symbol                              0xFE044
		#define memcpy_symbol                            0xDFAC
		#define memset_symbol                            0xD488
		#define strcpy_symbol                            0xED04
		#define strcat_symbol                            0xEED0
		#define strlen_symbol                            0xECD8
		#define vuart_read_symbol                        0x1E42C
		#define vuart_write_symbol                       0x1E37C
		#define ps2_disc_auth_symbol                     0x206B0
		#define ps2_disc_auth_caller_symbol              0x512F8
		#define overwritten_symbol                       0x23D6C
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x021f0000
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_470
		#define TOC                                      0x4EB8C0
		#define DISC_SIZE_OFFSET                         0x25714
		#define DISC_TYPE_OFFSET                         0x25310
		#define cdvd_send_atapi_command_symbol           0x22138
		#define ufs_open_symbol                          0x4E0A8
		#define ufs_close_symbol                         0x4E834
		#define ufs_read_symbol                          0x4DB78
		#define ufs_write_symbol                         0x4DC6C
		#define ufs_fstat_symbol                         0x4EB38
		#define zeroalloc_symbol                         0xFDFEC
		#define malloc_symbol                            0xFDF04
		#define free_symbol                              0xFE044
		#define memcpy_symbol                            0xDFAC
		#define memset_symbol                            0xD488
		#define strcpy_symbol                            0xED04
		#define strcat_symbol                            0xEED0
		#define strlen_symbol                            0xECD8
		#define vuart_read_symbol                        0x1E42C
		#define vuart_write_symbol                       0x1E37C
		#define ps2_disc_auth_symbol                     0x206B0
		#define ps2_disc_auth_caller_symbol              0x512F8
		#define overwritten_symbol                       0x23D6C
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x021f0000
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_475
		#define TOC                                      0x4EB8C0
		#define DISC_SIZE_OFFSET                         0x25714
		#define DISC_TYPE_OFFSET                         0x25310
		#define cdvd_send_atapi_command_symbol           0x22138
		#define ufs_open_symbol                          0x4E0A8
		#define ufs_close_symbol                         0x4E834
		#define ufs_read_symbol                          0x4DB78
		#define ufs_write_symbol                         0x4DC6C
		#define ufs_fstat_symbol                         0x4EB38
		#define zeroalloc_symbol                         0xFDFEC
		#define malloc_symbol                            0xFDF04
		#define free_symbol                              0xFE044
		#define memcpy_symbol                            0xDFAC
		#define memset_symbol                            0xD488
		#define strcpy_symbol                            0xED04
		#define strcat_symbol                            0xEED0
		#define strlen_symbol                            0xECD8
		#define vuart_read_symbol                        0x1E42C
		#define vuart_write_symbol                       0x1E37C
		#define ps2_disc_auth_symbol                     0x206B0
		#define ps2_disc_auth_caller_symbol              0x512F8
		#define overwritten_symbol                       0x23D6C
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x021f0000
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_476
		#define TOC                                      0x4EB8C0
		#define DISC_SIZE_OFFSET                         0x25714
		#define DISC_TYPE_OFFSET                         0x25310
		#define cdvd_send_atapi_command_symbol           0x22138
		#define ufs_open_symbol                          0x4E0A8
		#define ufs_close_symbol                         0x4E834
		#define ufs_read_symbol                          0x4DB78
		#define ufs_write_symbol                         0x4DC6C
		#define ufs_fstat_symbol                         0x4EB38
		#define zeroalloc_symbol                         0xFDFEC
		#define malloc_symbol                            0xFDF04
		#define free_symbol                              0xFE044
		#define memcpy_symbol                            0xDFAC
		#define memset_symbol                            0xD488
		#define strcpy_symbol                            0xED04
		#define strcat_symbol                            0xEED0
		#define strlen_symbol                            0xECD8
		#define vuart_read_symbol                        0x1E42C
		#define vuart_write_symbol                       0x1E37C
		#define ps2_disc_auth_symbol                     0x206B0
		#define ps2_disc_auth_caller_symbol              0x512F8
		#define overwritten_symbol                       0x23D6C
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x021f0000
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_478
		#define TOC                                      0x4EB8C0
		#define DISC_SIZE_OFFSET                         0x25714
		#define DISC_TYPE_OFFSET                         0x25310
		#define cdvd_send_atapi_command_symbol           0x22138
		#define ufs_open_symbol                          0x4E0A8
		#define ufs_close_symbol                         0x4E834
		#define ufs_read_symbol                          0x4DB78
		#define ufs_write_symbol                         0x4DC6C
		#define ufs_fstat_symbol                         0x4EB38
		#define zeroalloc_symbol                         0xFDFEC
		#define malloc_symbol                            0xFDF04
		#define free_symbol                              0xFE044
		#define memcpy_symbol                            0xDFAC
		#define memset_symbol                            0xD488
		#define strcpy_symbol                            0xED04
		#define strcat_symbol                            0xEED0
		#define strlen_symbol                            0xECD8
		#define vuart_read_symbol                        0x1E42C
		#define vuart_write_symbol                       0x1E37C
		#define ps2_disc_auth_symbol                     0x206B0
		#define ps2_disc_auth_caller_symbol              0x512F8
		#define overwritten_symbol                       0x23D6C
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x021f0000
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_480
		#define TOC                                      0x4EB8C0
		#define DISC_SIZE_OFFSET                         0x25714
		#define DISC_TYPE_OFFSET                         0x25310
		#define cdvd_send_atapi_command_symbol           0x22138
		#define ufs_open_symbol                          0x4E0A8
		#define ufs_close_symbol                         0x4E834
		#define ufs_read_symbol                          0x4DB78
		#define ufs_write_symbol                         0x4DC6C
		#define ufs_fstat_symbol                         0x4EB38
		#define zeroalloc_symbol                         0xFDFEC
		#define malloc_symbol                            0xFDF04
		#define free_symbol                              0xFE044
		#define memcpy_symbol                            0xDFAC
		#define memset_symbol                            0xD488
		#define strcpy_symbol                            0xED04
		#define strcat_symbol                            0xEED0
		#define strlen_symbol                            0xECD8
		#define vuart_read_symbol                        0x1E42C
		#define vuart_write_symbol                       0x1E37C
		#define ps2_disc_auth_symbol                     0x206B0
		#define ps2_disc_auth_caller_symbol              0x512F8
		#define overwritten_symbol                       0x23D6C
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x021f0000
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_481
		#define TOC                                      0x4EB8C0
		#define DISC_SIZE_OFFSET                         0x25714
		#define DISC_TYPE_OFFSET                         0x25310
		#define cdvd_send_atapi_command_symbol           0x22138
		#define ufs_open_symbol                          0x4E0A8
		#define ufs_close_symbol                         0x4E834
		#define ufs_read_symbol                          0x4DB78
		#define ufs_write_symbol                         0x4DC6C
		#define ufs_fstat_symbol                         0x4EB38
		#define zeroalloc_symbol                         0xFDFEC
		#define malloc_symbol                            0xFDF04
		#define free_symbol                              0xFE044
		#define memcpy_symbol                            0xDFAC
		#define memset_symbol                            0xD488
		#define strcpy_symbol                            0xED04
		#define strcat_symbol                            0xEED0
		#define strlen_symbol                            0xECD8
		#define vuart_read_symbol                        0x1E42C
		#define vuart_write_symbol                       0x1E37C
		#define ps2_disc_auth_symbol                     0x206B0
		#define ps2_disc_auth_caller_symbol              0x512F8
		#define overwritten_symbol                       0x23D6C
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x021f0000
	#endif /* FIRMWARE */

#endif /* PS2HWEMU */

#ifdef PS2GXEMU

	#define DATA_TOC_OFFSET             -0x5B00
	#define LPAR_TOC_OFFSET            -0x5BC8
	#define FILESZ_TOC_OFFSET           -0xE68

	#ifdef FIRMWARE_421
		#define TOC                                      0x677AA8
		#define cdvd_read_symbol                         0x8E364
		#define cdvd_send_atapi_command_symbol           0x8D938
		#define cdvd_send_device_command_symbol          0x8D84C
		#define ufs_open_symbol                          0x24EA70
		#define ufs_close_symbol                         0x24F218
		#define ufs_read_symbol                          0x24E780
		#define ufs_write_symbol                         0x24E8F8
		#define ufs_fstat_symbol                         0x24E5C0
		#define zeroalloc_symbol                         0x1E47AC
		#define malloc_symbol                            0x1E474C
		#define free_symbol                              0x1E47F8
		#define memcpy_symbol                            0x514BC
		#define memset_symbol                            0x51528
		#define strcpy_symbol                            0x51600
		#define strcat_symbol                            0x51634
		#define strlen_symbol                            0x515C8
		#define vuart_read_symbol                        0x49544
		#define vuart_write_symbol                       0x494A4
		#define ps2_disc_auth_symbol                     0x8FFB4
		#define ps2_disc_auth_caller_symbol              0x24F81C
		#define overwritten_symbol                       0x8C990
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x2BB8028
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_430
		#define TOC                                      0x678448
		#define cdvd_read_symbol                         0x8E364
		#define cdvd_send_atapi_command_symbol           0x8D938
		#define cdvd_send_device_command_symbol          0x8D84C
		#define ufs_open_symbol                          0x24EA70
		#define ufs_close_symbol                         0x24F218
		#define ufs_read_symbol                          0x24E780
		#define ufs_write_symbol                         0x24E8F8
		#define ufs_fstat_symbol                         0x24E5C0
		#define zeroalloc_symbol                         0x1E47AC
		#define malloc_symbol                            0x1E474C
		#define free_symbol                              0x1E47F8
		#define memcpy_symbol                            0x514BC
		#define memset_symbol                            0x51528
		#define strcpy_symbol                            0x51600
		#define strcat_symbol                            0x51634
		#define strlen_symbol                            0x515C8
		#define vuart_read_symbol                        0x49544
		#define vuart_write_symbol                       0x494A4
		#define ps2_disc_auth_symbol                     0x8FFB4
		#define ps2_disc_auth_caller_symbol              0x24F81C
		#define overwritten_symbol                       0x8C990
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x2BB8A28
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_431
		#define TOC                                      0x678448
		#define cdvd_read_symbol                         0x8E364
		#define cdvd_send_atapi_command_symbol           0x8D938
		#define cdvd_send_device_command_symbol          0x8D84C
		#define ufs_open_symbol                          0x24EA70
		#define ufs_close_symbol                         0x24F218
		#define ufs_read_symbol                          0x24E780
		#define ufs_write_symbol                         0x24E8F8
		#define ufs_fstat_symbol                         0x24E5C0
		#define zeroalloc_symbol                         0x1E47AC
		#define malloc_symbol                            0x1E474C
		#define free_symbol                              0x1E47F8
		#define memcpy_symbol                            0x514BC
		#define memset_symbol                            0x51528
		#define strcpy_symbol                            0x51600
		#define strcat_symbol                            0x51634
		#define strlen_symbol                            0x515C8
		#define vuart_read_symbol                        0x49544
		#define vuart_write_symbol                       0x494A4
		#define ps2_disc_auth_symbol                     0x8FFB4
		#define ps2_disc_auth_caller_symbol              0x24F81C
		#define overwritten_symbol                       0x8C990
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x2BB8A28
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_440
		#define TOC                                      0x678548
		#define cdvd_read_symbol                         0x8E46C
		#define cdvd_send_atapi_command_symbol           0x8DA40
		#define cdvd_send_device_command_symbol          0x8D954
		#define ufs_open_symbol                          0x24EB70
		#define ufs_close_symbol                         0x24F318
		#define ufs_read_symbol                          0x24E880
		#define ufs_write_symbol                         0x24E9F8
		#define ufs_fstat_symbol                         0x24E6C0
		#define zeroalloc_symbol                         0x1E48AC
		#define malloc_symbol                            0x1E484C
		#define free_symbol                              0x1E48F8
		#define memcpy_symbol                            0x514BC
		#define memset_symbol                            0x51528
		#define strcpy_symbol                            0x51600
		#define strcat_symbol                            0x51634
		#define strlen_symbol                            0x515C8
		#define vuart_read_symbol                        0x49544
		#define vuart_write_symbol                       0x494A4
		#define ps2_disc_auth_symbol                     0x900BC
		#define ps2_disc_auth_caller_symbol              0x24F91C
		#define overwritten_symbol                       0x8CA98
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x2BB8C28
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_441
		#define TOC                                      0x678548
		#define cdvd_read_symbol                         0x8E46C
		#define cdvd_send_atapi_command_symbol           0x8DA40
		#define cdvd_send_device_command_symbol          0x8D954
		#define ufs_open_symbol                          0x24EB70
		#define ufs_close_symbol                         0x24F318
		#define ufs_read_symbol                          0x24E880
		#define ufs_write_symbol                         0x24E9F8
		#define ufs_fstat_symbol                         0x24E6C0
		#define zeroalloc_symbol                         0x1E48AC
		#define malloc_symbol                            0x1E484C
		#define free_symbol                              0x1E48F8
		#define memcpy_symbol                            0x514BC
		#define memset_symbol                            0x51528
		#define strcpy_symbol                            0x51600
		#define strcat_symbol                            0x51634
		#define strlen_symbol                            0x515C8
		#define vuart_read_symbol                        0x49544
		#define vuart_write_symbol                       0x494A4
		#define ps2_disc_auth_symbol                     0x900BC
		#define ps2_disc_auth_caller_symbol              0x24F91C
		#define overwritten_symbol                       0x8CA98
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x2BB8C28
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_446
		#define TOC                                      0x678548
		#define cdvd_read_symbol                         0x8E46C
		#define cdvd_send_atapi_command_symbol           0x8DA40
		#define cdvd_send_device_command_symbol          0x8D954
		#define ufs_open_symbol                          0x24EB70
		#define ufs_close_symbol                         0x24F318
		#define ufs_read_symbol                          0x24E880
		#define ufs_write_symbol                         0x24E9F8
		#define ufs_fstat_symbol                         0x24E6C0
		#define zeroalloc_symbol                         0x1E48AC
		#define malloc_symbol                            0x1E484C
		#define free_symbol                              0x1E48F8
		#define memcpy_symbol                            0x514BC
		#define memset_symbol                            0x51528
		#define strcpy_symbol                            0x51600
		#define strcat_symbol                            0x51634
		#define strlen_symbol                            0x515C8
		#define vuart_read_symbol                        0x49544
		#define vuart_write_symbol                       0x494A4
		#define ps2_disc_auth_symbol                     0x900BC
		#define ps2_disc_auth_caller_symbol              0x24F91C
		#define overwritten_symbol                       0x8CA98
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x2BB8C28
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_450
		#define TOC                                      0x678548
		#define cdvd_read_symbol                         0x8E46C
		#define cdvd_send_atapi_command_symbol           0x8DA40
		#define cdvd_send_device_command_symbol          0x8D954
		#define ufs_open_symbol                          0x24EB70
		#define ufs_close_symbol                         0x24F318
		#define ufs_read_symbol                          0x24E880
		#define ufs_write_symbol                         0x24E9F8
		#define ufs_fstat_symbol                         0x24E6C0
		#define zeroalloc_symbol                         0x1E48AC
		#define malloc_symbol                            0x1E484C
		#define free_symbol                              0x1E48F8
		#define memcpy_symbol                            0x514BC
		#define memset_symbol                            0x51528
		#define strcpy_symbol                            0x51600
		#define strcat_symbol                            0x51634
		#define strlen_symbol                            0x515C8
		#define vuart_read_symbol                        0x49544
		#define vuart_write_symbol                       0x494A4
		#define ps2_disc_auth_symbol                     0x900BC
		#define ps2_disc_auth_caller_symbol              0x24F91C
		#define overwritten_symbol                       0x8CA98
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x2BB8C28
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_453
		#define TOC                                      0x678548
		#define cdvd_read_symbol                         0x8E4AC
		#define cdvd_send_atapi_command_symbol           0x8DA80
		#define cdvd_send_device_command_symbol          0x8D994
		#define ufs_open_symbol                          0x24EBB0
		#define ufs_close_symbol                         0x24F358
		#define ufs_read_symbol                          0x24E8C0
		#define ufs_write_symbol                         0x24EA38
		#define ufs_fstat_symbol                         0x24E700
		#define zeroalloc_symbol                         0x1E48EC
		#define malloc_symbol                            0x1E488C
		#define free_symbol                              0x1E4938
		#define memcpy_symbol                            0x514BC
		#define memset_symbol                            0x51528
		#define strcpy_symbol                            0x51600
		#define strcat_symbol                            0x51634
		#define strlen_symbol                            0x515C8
		#define vuart_read_symbol                        0x49544
		#define vuart_write_symbol                       0x494A4
		#define ps2_disc_auth_symbol                     0x900FC
		#define ps2_disc_auth_caller_symbol              0x24F95C
		#define overwritten_symbol                       0x8CAD8
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x2BBAB28
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_455
		#define TOC                                      0x678548
		#define cdvd_read_symbol                         0x8E4AC
		#define cdvd_send_atapi_command_symbol           0x8DA80
		#define cdvd_send_device_command_symbol          0x8D994
		#define ufs_open_symbol                          0x24EBB0
		#define ufs_close_symbol                         0x24F358
		#define ufs_read_symbol                          0x24E8C0
		#define ufs_write_symbol                         0x24EA38
		#define ufs_fstat_symbol                         0x24E700
		#define zeroalloc_symbol                         0x1E48EC
		#define malloc_symbol                            0x1E488C
		#define free_symbol                              0x1E4938
		#define memcpy_symbol                            0x514BC
		#define memset_symbol                            0x51528
		#define strcpy_symbol                            0x51600
		#define strcat_symbol                            0x51634
		#define strlen_symbol                            0x515C8
		#define vuart_read_symbol                        0x49544
		#define vuart_write_symbol                       0x494A4
		#define ps2_disc_auth_symbol                     0x900FC
		#define ps2_disc_auth_caller_symbol              0x24F95C
		#define overwritten_symbol                       0x8CAD8
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x2BBAB28
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_460
		#define TOC                                      0x678548
		#define cdvd_read_symbol                         0x8E4AC
		#define cdvd_send_atapi_command_symbol           0x8DA80
		#define cdvd_send_device_command_symbol          0x8D994
		#define ufs_open_symbol                          0x24EBB0
		#define ufs_close_symbol                         0x24F358
		#define ufs_read_symbol                          0x24E8C0
		#define ufs_write_symbol                         0x24EA38
		#define ufs_fstat_symbol                         0x24E700
		#define zeroalloc_symbol                         0x1E48EC
		#define malloc_symbol                            0x1E488C
		#define free_symbol                              0x1E4938
		#define memcpy_symbol                            0x514BC
		#define memset_symbol                            0x51528
		#define strcpy_symbol                            0x51600
		#define strcat_symbol                            0x51634
		#define strlen_symbol                            0x515C8
		#define vuart_read_symbol                        0x49544
		#define vuart_write_symbol                       0x494A4
		#define ps2_disc_auth_symbol                     0x900FC
		#define ps2_disc_auth_caller_symbol              0x24F95C
		#define overwritten_symbol                       0x8CAD8
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x2BBAB28
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_465
		#define TOC                                      0x678548
		#define cdvd_read_symbol                         0x8E4AC
		#define cdvd_send_atapi_command_symbol           0x8DA80
		#define cdvd_send_device_command_symbol          0x8D994
		#define ufs_open_symbol                          0x24EBB0
		#define ufs_close_symbol                         0x24F358
		#define ufs_read_symbol                          0x24E8C0
		#define ufs_write_symbol                         0x24EA38
		#define ufs_fstat_symbol                         0x24E700
		#define zeroalloc_symbol                         0x1E48EC
		#define malloc_symbol                            0x1E488C
		#define free_symbol                              0x1E4938
		#define memcpy_symbol                            0x514BC
		#define memset_symbol                            0x51528
		#define strcpy_symbol                            0x51600
		#define strcat_symbol                            0x51634
		#define strlen_symbol                            0x515C8
		#define vuart_read_symbol                        0x49544
		#define vuart_write_symbol                       0x494A4
		#define ps2_disc_auth_symbol                     0x900FC
		#define ps2_disc_auth_caller_symbol              0x24F95C
		#define overwritten_symbol                       0x8CAD8
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x2BBAB28
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_466
		#define TOC                                      0x678548
		#define cdvd_read_symbol                         0x8E4AC
		#define cdvd_send_atapi_command_symbol           0x8DA80
		#define cdvd_send_device_command_symbol          0x8D994
		#define ufs_open_symbol                          0x24EBB0
		#define ufs_close_symbol                         0x24F358
		#define ufs_read_symbol                          0x24E8C0
		#define ufs_write_symbol                         0x24EA38
		#define ufs_fstat_symbol                         0x24E700
		#define zeroalloc_symbol                         0x1E48EC
		#define malloc_symbol                            0x1E488C
		#define free_symbol                              0x1E4938
		#define memcpy_symbol                            0x514BC
		#define memset_symbol                            0x51528
		#define strcpy_symbol                            0x51600
		#define strcat_symbol                            0x51634
		#define strlen_symbol                            0x515C8
		#define vuart_read_symbol                        0x49544
		#define vuart_write_symbol                       0x494A4
		#define ps2_disc_auth_symbol                     0x900FC
		#define ps2_disc_auth_caller_symbol              0x24F95C
		#define overwritten_symbol                       0x8CAD8
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x2BBAB28
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_470
		#define TOC                                      0x678548
		#define cdvd_read_symbol                         0x8E4AC
		#define cdvd_send_atapi_command_symbol           0x8DA80
		#define cdvd_send_device_command_symbol          0x8D994
		#define ufs_open_symbol                          0x24EBB0
		#define ufs_close_symbol                         0x24F358
		#define ufs_read_symbol                          0x24E8C0
		#define ufs_write_symbol                         0x24EA38
		#define ufs_fstat_symbol                         0x24E700
		#define zeroalloc_symbol                         0x1E48EC
		#define malloc_symbol                            0x1E488C
		#define free_symbol                              0x1E4938
		#define memcpy_symbol                            0x514BC
		#define memset_symbol                            0x51528
		#define strcpy_symbol                            0x51600
		#define strcat_symbol                            0x51634
		#define strlen_symbol                            0x515C8
		#define vuart_read_symbol                        0x49544
		#define vuart_write_symbol                       0x494A4
		#define ps2_disc_auth_symbol                     0x900FC
		#define ps2_disc_auth_caller_symbol              0x24F95C
		#define overwritten_symbol                       0x8CAD8
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x2BBAB28
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_475
		#define TOC                                      0x678548
		#define cdvd_read_symbol                         0x8E4AC
		#define cdvd_send_atapi_command_symbol           0x8DA80
		#define cdvd_send_device_command_symbol          0x8D994
		#define ufs_open_symbol                          0x24EBB0
		#define ufs_close_symbol                         0x24F358
		#define ufs_read_symbol                          0x24E8C0
		#define ufs_write_symbol                         0x24EA38
		#define ufs_fstat_symbol                         0x24E700
		#define zeroalloc_symbol                         0x1E48EC
		#define malloc_symbol                            0x1E488C
		#define free_symbol                              0x1E4938
		#define memcpy_symbol                            0x514BC
		#define memset_symbol                            0x51528
		#define strcpy_symbol                            0x51600
		#define strcat_symbol                            0x51634
		#define strlen_symbol                            0x515C8
		#define vuart_read_symbol                        0x49544
		#define vuart_write_symbol                       0x494A4
		#define ps2_disc_auth_symbol                     0x900FC
		#define ps2_disc_auth_caller_symbol              0x24F95C
		#define overwritten_symbol                       0x8CAD8
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x2BBAB28
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_476
		#define TOC                                      0x678548
		#define cdvd_read_symbol                         0x8E4AC
		#define cdvd_send_atapi_command_symbol           0x8DA80
		#define cdvd_send_device_command_symbol          0x8D994
		#define ufs_open_symbol                          0x24EBB0
		#define ufs_close_symbol                         0x24F358
		#define ufs_read_symbol                          0x24E8C0
		#define ufs_write_symbol                         0x24EA38
		#define ufs_fstat_symbol                         0x24E700
		#define zeroalloc_symbol                         0x1E48EC
		#define malloc_symbol                            0x1E488C
		#define free_symbol                              0x1E4938
		#define memcpy_symbol                            0x514BC
		#define memset_symbol                            0x51528
		#define strcpy_symbol                            0x51600
		#define strcat_symbol                            0x51634
		#define strlen_symbol                            0x515C8
		#define vuart_read_symbol                        0x49544
		#define vuart_write_symbol                       0x494A4
		#define ps2_disc_auth_symbol                     0x900FC
		#define ps2_disc_auth_caller_symbol              0x24F95C
		#define overwritten_symbol                       0x8CAD8
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x2BBAB28
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_478
		#define TOC                                      0x678548
		#define cdvd_read_symbol                         0x8E4AC
		#define cdvd_send_atapi_command_symbol           0x8DA80
		#define cdvd_send_device_command_symbol          0x8D994
		#define ufs_open_symbol                          0x24EBB0
		#define ufs_close_symbol                         0x24F358
		#define ufs_read_symbol                          0x24E8C0
		#define ufs_write_symbol                         0x24EA38
		#define ufs_fstat_symbol                         0x24E700
		#define zeroalloc_symbol                         0x1E48EC
		#define malloc_symbol                            0x1E488C
		#define free_symbol                              0x1E4938
		#define memcpy_symbol                            0x514BC
		#define memset_symbol                            0x51528
		#define strcpy_symbol                            0x51600
		#define strcat_symbol                            0x51634
		#define strlen_symbol                            0x515C8
		#define vuart_read_symbol                        0x49544
		#define vuart_write_symbol                       0x494A4
		#define ps2_disc_auth_symbol                     0x900FC
		#define ps2_disc_auth_caller_symbol              0x24F95C
		#define overwritten_symbol                       0x8CAD8
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x2BBAB28
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_480
		#define TOC                                      0x678548
		#define cdvd_read_symbol                         0x8E4AC
		#define cdvd_send_atapi_command_symbol           0x8DA80
		#define cdvd_send_device_command_symbol          0x8D994
		#define ufs_open_symbol                          0x24EBB0
		#define ufs_close_symbol                         0x24F358
		#define ufs_read_symbol                          0x24E8C0
		#define ufs_write_symbol                         0x24EA38
		#define ufs_fstat_symbol                         0x24E700
		#define zeroalloc_symbol                         0x1E48EC
		#define malloc_symbol                            0x1E488C
		#define free_symbol                              0x1E4938
		#define memcpy_symbol                            0x514BC
		#define memset_symbol                            0x51528
		#define strcpy_symbol                            0x51600
		#define strcat_symbol                            0x51634
		#define strlen_symbol                            0x515C8
		#define vuart_read_symbol                        0x49544
		#define vuart_write_symbol                       0x494A4
		#define ps2_disc_auth_symbol                     0x900FC
		#define ps2_disc_auth_caller_symbol              0x24F95C
		#define overwritten_symbol                       0x8CAD8
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x2BBAB28
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_481
		#define TOC                                      0x678548
		#define cdvd_read_symbol                         0x8E4AC
		#define cdvd_send_atapi_command_symbol           0x8DA80
		#define cdvd_send_device_command_symbol          0x8D994
		#define ufs_open_symbol                          0x24EBB0
		#define ufs_close_symbol                         0x24F358
		#define ufs_read_symbol                          0x24E8C0
		#define ufs_write_symbol                         0x24EA38
		#define ufs_fstat_symbol                         0x24E700
		#define zeroalloc_symbol                         0x1E48EC
		#define malloc_symbol                            0x1E488C
		#define free_symbol                              0x1E4938
		#define memcpy_symbol                            0x514BC
		#define memset_symbol                            0x51528
		#define strcpy_symbol                            0x51600
		#define strcat_symbol                            0x51634
		#define strlen_symbol                            0x515C8
		#define vuart_read_symbol                        0x49544
		#define vuart_write_symbol                       0x494A4
		#define ps2_disc_auth_symbol                     0x900FC
		#define ps2_disc_auth_caller_symbol              0x24F95C
		#define overwritten_symbol                       0x8CAD8
		#define stage1_addr                              overwritten_symbol
		#define stage2_addr                              0x2BBAB28
	#endif /* FIRMWARE */

#endif /* PS2GXEMU */

#ifdef PS2NETEMU

	#define EXTENDED_DATA	(0x821000+0x2953478)

	#ifdef FIRMWARE_421
		#define TOC                                      0x7DA500
		#define cdvd_read_symbol                         0x12E9BC
		#define ufs_open_symbol                          0x1E3E64
		#define ufs_close_symbol                         0x1E3D18
		#define ufs_read_symbol                          0x1E47D4
		#define ufs_write_symbol                         0x1E4660
		#define ufs_fstat_symbol                         0x1E3968
		#define memcpy_symbol                            0x111050
		#define memset_symbol                            0x110FFC
		#define strcpy_symbol                            0x110E9C
		#define strcat_symbol                            0x110ED4
		#define strlen_symbol                            0x110E64
		#define decrypt_symbol                           cdvd_read_symbol
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_430
		#define TOC                                      0x74F680
		#define cdvd_read_symbol                         0x12EB2C
		#define ufs_open_symbol                          0x1E3FE4
		#define ufs_close_symbol                         0x1E3E98
		#define ufs_read_symbol                          0x1E4954
		#define ufs_write_symbol                         0x1E47E0
		#define ufs_fstat_symbol                         0x1E3AE8
		#define memcpy_symbol                            0x111190
		#define memset_symbol                            0x11113C
		#define strcpy_symbol                            0x110FDC
		#define strcat_symbol                            0x111014
		#define strlen_symbol                            0x110FA4
		#define decrypt_symbol                           cdvd_read_symbol
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_431
		#define TOC                                      0x74F680
		#define cdvd_read_symbol                         0x12EB2C
		#define ufs_open_symbol                          0x1E3FE4
		#define ufs_close_symbol                         0x1E3E98
		#define ufs_read_symbol                          0x1E4954
		#define ufs_write_symbol                         0x1E47E0
		#define ufs_fstat_symbol                         0x1E3AE8
		#define memcpy_symbol                            0x111190
		#define memset_symbol                            0x11113C
		#define strcpy_symbol                            0x110FDC
		#define strcat_symbol                            0x111014
		#define strlen_symbol                            0x110FA4
		#define decrypt_symbol                           cdvd_read_symbol
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_440
		#define TOC                                      0x74FC80
		#define cdvd_read_symbol                         0x1331DC
		#define ufs_open_symbol                          0x1E8664
		#define ufs_close_symbol                         0x1E8518
		#define ufs_read_symbol                          0x1E8FD4
		#define ufs_write_symbol                         0x1E8E60
		#define ufs_fstat_symbol                         0x1E8168
		#define memcpy_symbol                            0x115290
		#define memset_symbol                            0x11523C
		#define strcpy_symbol                            0x1150DC
		#define strcat_symbol                            0x115114
		#define strlen_symbol                            0x1150A4
		#define decrypt_symbol                           cdvd_read_symbol
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_441
		#define TOC                                      0x74FC80
		#define cdvd_read_symbol                         0x1331DC
		#define ufs_open_symbol                          0x1E8664
		#define ufs_close_symbol                         0x1E8518
		#define ufs_read_symbol                          0x1E8FD4
		#define ufs_write_symbol                         0x1E8E60
		#define ufs_fstat_symbol                         0x1E8168
		#define memcpy_symbol                            0x115290
		#define memset_symbol                            0x11523C
		#define strcpy_symbol                            0x1150DC
		#define strcat_symbol                            0x115114
		#define strlen_symbol                            0x1150A4
		#define decrypt_symbol                           cdvd_read_symbol
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_446
		#define TOC                                      0x74FC80
		#define cdvd_read_symbol                         0x1332F4
		#define ufs_open_symbol                          0x1E87A4
		#define ufs_close_symbol                         0x1E8658
		#define ufs_read_symbol                          0x1E9114
		#define ufs_write_symbol                         0x1E8FA0
		#define ufs_fstat_symbol                         0x1E82A8
		#define memcpy_symbol                            0x115310
		#define memset_symbol                            0x1152BC
		#define strcpy_symbol                            0x11515C
		#define strcat_symbol                            0x115194
		#define strlen_symbol                            0x115124
		#define decrypt_symbol                           cdvd_read_symbol
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_450
		#define TOC                                      0x751180
		#define cdvd_read_symbol                         0x1368BC
		#define ufs_open_symbol                          0x1EBD5C
		#define ufs_close_symbol                         0x1EBC10
		#define ufs_read_symbol                          0x1EC6CC
		#define ufs_write_symbol                         0x1EC558
		#define ufs_fstat_symbol                         0x1EB860
		#define memcpy_symbol                            0x1183D0
		#define memset_symbol                            0x11837C
		#define strcpy_symbol                            0x11821C
		#define strcat_symbol                            0x118254
		#define strlen_symbol                            0x1181E4
		#define decrypt_symbol                           cdvd_read_symbol
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_453
		#define TOC                                      0x751280
		#define cdvd_read_symbol                         0x1374FC
		#define ufs_open_symbol                          0x1EC99C
		#define ufs_close_symbol                         0x1EC850
		#define ufs_read_symbol                          0x1ED30C
		#define ufs_write_symbol                         0x1ED198
		#define ufs_fstat_symbol                         0x1EC4A0
		#define memcpy_symbol                            0x1188D0
		#define memset_symbol                            0x11887C
		#define strcpy_symbol                            0x11871C
		#define strcat_symbol                            0x118754
		#define strlen_symbol                            0x1186E4
		#define decrypt_symbol                           cdvd_read_symbol
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_455
		#define TOC                                      0x751280
		#define cdvd_read_symbol                         0x13757C
		#define ufs_open_symbol                          0x1ECA1C
		#define ufs_close_symbol                         0x1EC8D0
		#define ufs_read_symbol                          0x1ED38C
		#define ufs_write_symbol                         0x1ED218
		#define ufs_fstat_symbol                         0x1EC520
		#define memcpy_symbol                            0x118950
		#define memset_symbol                            0x1188FC
		#define strcpy_symbol                            0x11879C
		#define strcat_symbol                            0x1187D4
		#define strlen_symbol                            0x118764
		#define decrypt_symbol                           cdvd_read_symbol
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_460
		#define TOC                                      0x751280
		#define cdvd_read_symbol                         0x137744
		#define ufs_open_symbol                          0x1ECBDC
		#define ufs_close_symbol                         0x1ECA90
		#define ufs_read_symbol                          0x1ED54C
		#define ufs_write_symbol                         0x1ED3D8
		#define ufs_fstat_symbol                         0x1EC6E0
		#define memcpy_symbol                            0x118A10
		#define memset_symbol                            0x1189BC
		#define strcpy_symbol                            0x11885C
		#define strcat_symbol                            0x118894
		#define strlen_symbol                            0x118824
		#define decrypt_symbol                           cdvd_read_symbol
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_465
		#define TOC                                      0x751280
		#define cdvd_read_symbol                         0x137744
		#define ufs_open_symbol                          0x1ECBDC
		#define ufs_close_symbol                         0x1ECA90
		#define ufs_read_symbol                          0x1ED54C
		#define ufs_write_symbol                         0x1ED3D8
		#define ufs_fstat_symbol                         0x1EC6E0
		#define memcpy_symbol                            0x118A10
		#define memset_symbol                            0x1189BC
		#define strcpy_symbol                            0x11885C
		#define strcat_symbol                            0x118894
		#define strlen_symbol                            0x118824
		#define decrypt_symbol                           cdvd_read_symbol
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_466
		#define TOC                                      0x751280
		#define cdvd_read_symbol                         0x137744
		#define ufs_open_symbol                          0x1ECBDC
		#define ufs_close_symbol                         0x1ECA90
		#define ufs_read_symbol                          0x1ED54C
		#define ufs_write_symbol                         0x1ED3D8
		#define ufs_fstat_symbol                         0x1EC6E0
		#define memcpy_symbol                            0x118A10
		#define memset_symbol                            0x1189BC
		#define strcpy_symbol                            0x11885C
		#define strcat_symbol                            0x118894
		#define strlen_symbol                            0x118824
		#define decrypt_symbol                           cdvd_read_symbol
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_470
		#define TOC                                      0x751280
		#define cdvd_read_symbol                         0x137744
		#define ufs_open_symbol                          0x1ECBDC
		#define ufs_close_symbol                         0x1ECA90
		#define ufs_read_symbol                          0x1ED54C
		#define ufs_write_symbol                         0x1ED3D8
		#define ufs_fstat_symbol                         0x1EC6E0
		#define memcpy_symbol                            0x118A10
		#define memset_symbol                            0x1189BC
		#define strcpy_symbol                            0x11885C
		#define strcat_symbol                            0x118894
		#define strlen_symbol                            0x118824
		#define decrypt_symbol                           cdvd_read_symbol
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_475
		#define TOC                                      0x751280
		#define cdvd_read_symbol                         0x137744
		#define ufs_open_symbol                          0x1ECBDC
		#define ufs_close_symbol                         0x1ECA90
		#define ufs_read_symbol                          0x1ED54C
		#define ufs_write_symbol                         0x1ED3D8
		#define ufs_fstat_symbol                         0x1EC6E0
		#define memcpy_symbol                            0x118A10
		#define memset_symbol                            0x1189BC
		#define strcpy_symbol                            0x11885C
		#define strcat_symbol                            0x118894
		#define strlen_symbol                            0x118824
		#define decrypt_symbol                           cdvd_read_symbol
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_476
		#define TOC                                      0x751280
		#define cdvd_read_symbol                         0x137744
		#define ufs_open_symbol                          0x1ECBDC
		#define ufs_close_symbol                         0x1ECA90
		#define ufs_read_symbol                          0x1ED54C
		#define ufs_write_symbol                         0x1ED3D8
		#define ufs_fstat_symbol                         0x1EC6E0
		#define memcpy_symbol                            0x118A10
		#define memset_symbol                            0x1189BC
		#define strcpy_symbol                            0x11885C
		#define strcat_symbol                            0x118894
		#define strlen_symbol                            0x118824
		#define decrypt_symbol                           cdvd_read_symbol
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_478
		#define TOC                                      0x751280
		#define cdvd_read_symbol                         0x1377C4
		#define ufs_open_symbol                          0x1ECC5C
		#define ufs_close_symbol                         0x1ECB10
		#define ufs_read_symbol                          0x1ED5CC
		#define ufs_write_symbol                         0x1ED458
		#define ufs_fstat_symbol                         0x1EC760
		#define memcpy_symbol                            0x118A90
		#define memset_symbol                            0x118A3C
		#define strcpy_symbol                            0x1188DC
		#define strcat_symbol                            0x118914
		#define strlen_symbol                            0x1188A4
		#define decrypt_symbol                           cdvd_read_symbol
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_480
		#define TOC                                      0x751280
		#define cdvd_read_symbol                         0x1377C4
		#define ufs_open_symbol                          0x1ECC5C
		#define ufs_close_symbol                         0x1ECB10
		#define ufs_read_symbol                          0x1ED5CC
		#define ufs_write_symbol                         0x1ED458
		#define ufs_fstat_symbol                         0x1EC760
		#define memcpy_symbol                            0x118A90
		#define memset_symbol                            0x118A3C
		#define strcpy_symbol                            0x1188DC
		#define strcat_symbol                            0x118914
		#define strlen_symbol                            0x1188A4
		#define decrypt_symbol                           cdvd_read_symbol
	#endif /* FIRMWARE */

	#ifdef FIRMWARE_481
		#define TOC                                      0x751280
		#define cdvd_read_symbol                         0x1377C4
		#define ufs_open_symbol                          0x1ECC5C
		#define ufs_close_symbol                         0x1ECB10
		#define ufs_read_symbol                          0x1ED5CC
		#define ufs_write_symbol                         0x1ED458
		#define ufs_fstat_symbol                         0x1EC760
		#define memcpy_symbol                            0x118A90
		#define memset_symbol                            0x118A3C
		#define strcpy_symbol                            0x1188DC
		#define strcat_symbol                            0x118914
		#define strlen_symbol                            0x1188A4
		#define decrypt_symbol                           cdvd_read_symbol
	#endif /* FIRMWARE */

#endif /* PS2NETEMU */


#endif /* __PS2EMU_SYMBOLS_H_S__ */
