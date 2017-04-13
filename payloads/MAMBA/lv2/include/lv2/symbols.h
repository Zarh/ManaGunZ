#ifndef __FIRMWARE_SYMBOLS_H_S__
#define __FIRMWARE_SYMBOLS_H_S__

#define umd_mutex_offset (0x64480+0x38C)

#ifdef FIRMWARE_421C

	#define FIRMWARE_VERSION                                 0x421

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x421
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003D9230ULL
		#define PS3MAPI_IDPS_2                               0x8000000000477E9CULL
		#define PS3MAPI_PSID                                 0x8000000000477EB4ULL
	#endif

	/* lv2 */
	#define TOC                                              0x346390
	#define open_shared_kernel_object_symbol                 0x123FC
	#define close_kernel_object_handle_symbol                0x11A1C
	#define open_kernel_object_symbol                        0x125EC
	#define alloc_symbol                                     0x63ED8
	#define dealloc_symbol                                   0x64314
	#define copy_to_user_symbol                              0xF85C
	#define copy_from_user_symbol                            0xFA78
	#define copy_to_process_symbol                           0xF914
	#define copy_from_process_symbol                         0xF724
	#define page_allocate_symbol                             0x5FA48
	#define page_free_symbol                                 0x5F4AC
	#define page_export_to_proc_symbol                       0x5FBE4
	#define page_unexport_from_proc_symbol                   0x5F3A0
	#define kernel_ea_to_lpar_addr_symbol                    0x6F7F0
	#define map_process_memory_symbol                        0x76910
	#define memcpy_symbol                                    0x7DFD0
	#define memset_symbol                                    0x4E508
	#define memcmp_symbol                                    0x4D818
	#define printf_symbol                                    0x29E77C
	#define printfnull_symbol                                0x2A31EC
	#define sprintf_symbol                                   0x4F930
	#define snprintf_symbol                                  0x4F89C
	#define strcpy_symbol                                    0x4E6B4
	#define strncpy_symbol                                   0x4E77C
	#define strlen_symbol                                    0x4E6DC
	#define strcat_symbol                                    0x4E5E4
	#define strcmp_symbol                                    0x4E660
	#define strncmp_symbol                                   0x4E708
	#define strchr_symbol                                    0x4E61C
	#define spin_lock_irqsave_ex_symbol                      0x29C850
	#define spin_unlock_irqrestore_ex_symbol                 0x29C824
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x13EB4
	#define ppu_thread_exit_symbol                           0x13F6C
	#define ppu_thread_join_symbol                           0x13FC0
	#define ppu_thread_delay_symbol                          0x28554
	#define create_user_thread2_symbol                       0x24E38
	#define start_thread_symbol                              0x23B04
	#define run_thread_symbol                                0x23334
	#define register_thread_symbol                           0x296A64
	#define allocate_user_stack_symbol                       0x29724C
	#define mutex_create_symbol                              0x13628
	#define mutex_destroy_symbol                             0x135C0
	#define mutex_lock_symbol                                0x135B8
	#define mutex_unlock_symbol                              0x135B0
	#define event_port_create_symbol                         0x13064
	#define event_port_destroy_symbol                        0x134CC
	#define event_port_connect_symbol                        0x13544
	#define event_port_disconnect_symbol                     0x13470
	#define event_port_send_symbol                           0x1305C
	#define event_queue_create_symbol                        0x1336C
	#define event_queue_destroy_symbol                       0x132F4
	#define event_queue_receive_symbol                       0x13138
	#define cellFsOpen_symbol                                0x2C2820
	#define cellFsClose_symbol                               0x2C2688
	#define cellFsRead_symbol                                0x2C27C4
	#define cellFsWrite_symbol                               0x2C2730
	#define cellFsLseek_symbol                               0x2C1DB8
	#define cellFsStat_symbol                                0x2C203C
	#define cellFsUnlink_internal_symbol                     0x1A96E8
	#define cellFsUtilMount_symbol                           0x2C1B98
	#define cellFsUtilUmount_symbol                          0x2C1B6C
	#define pathdup_from_user_symbol                         0x1B1988
	#define open_path_symbol                                 0x2C2558
	#define open_fs_object_symbol                            0x190970
	#define close_fs_object_symbol                           0x18F940
	#define storage_get_device_info_symbol                   0x2A7BBC
	#define storage_open_symbol                              0x2A70E0
	#define storage_close_symbol                             0x2A767C
	#define storage_read_symbol                              0x2A65F8
	#define storage_send_device_command_symbol               0x2A6734
	#define storage_map_io_memory_symbol                     0x2A7A78
	#define storage_unmap_io_memory_symbol                   0x2A7944
	#define storage_internal_get_device_object_symbol        0x2A5F80
	#define decrypt_func_symbol                              0x346D0
	#define lv1_call_99_wrapper_symbol                       0x4FD44
	#define modules_verification_symbol                      0x59788
	#define prx_load_module_symbol                           0x88168
	#define prx_start_module_symbol                          0x86E34
	#define prx_stop_module_symbol                           0x8820C
	#define prx_unload_module_symbol                         0x86B68
	#define prx_get_module_info_symbol                       0x865F0
	#define prx_get_module_list_symbol                       0x86670
	#define extend_kstack_symbol                             0x6F748
	#define get_pseudo_random_number_symbol                  0x2579CC
	#define syscall_table_symbol                             0x35BCA8
	#define syscall_call_offset                              0x2A3CD0
	#define read_bdvd0_symbol                                0x1BBE5C
	#define read_bdvd1_symbol                                0x1BDA88
	#define read_bdvd2_symbol                                0x1CAC10
	#define device_event_port_send_call                      0x2AFF38
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x2C29B8
	#define fsloop_close_call                                0x2C2A08
	#define fsloop_read_call                                 0x2C2A48
	#define io_rtoc_entry_1                                 -0x178
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x6680
	#define storage_rtoc_entry_1                             0x1E50
	#define device_event_rtoc_entry_1                        0x20C0
	#define process_rtoc_entry_1                            -0x7800
	#define patch_func2                                      0x5A140
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x201B4
	#define user_thread_prio_patch2                          0x201C0
	#define shutdown_patch_offset                            0xAAA8
	#define shutdown_copy_params_call                        0xAABC

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000E6988
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB3B0BE000574C3
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001D8EF
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BEC800006430
	#define PSP_EMULATOR_HASH                           0x7BE65D6D00023702
	#define PEMUCORELIB_HASH                            0xF349A563000BFCC8
	#define EMULATOR_API_HASH                           0xA9F5B2320001E7C6
	#define EMULATOR_DRM_HASH                           0xD2C7F3E20000538F
	#define EMULATOR_DRM_DATA_HASH                      0xB4F919590001B6E7
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC3B800003210

	/* lv1 */
	#define vsh_pos_in_ram                              0x910000

	/* vsh */
	#define ps2tonet_patch                              0xC44EC
	#define ps2tonet_size_patch                         0xC44E0
	#define vmode_patch_offset                          0x43EA78
	#define psp_drm_patch1                              0x23C85C
	#define psp_drm_patch2                              0x23D2F4
	#define psp_drm_patch3                              0x23CF34
	#define psp_drm_patch4                              0x23D73C
	#define psp_drm_patchA                              0x23C978
	#define psp_drm_patchB                              0x23D210
	#define psp_drm_patchC                              0x23C3B0
	#define psp_drm_patchD                              0x23C960
	#define psp_drm_patchE                              0x23C964
	#define psp_drm_patchF                              0x23D328
	#define psp_extra_drm_patch                         0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDAB8C

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x75728

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x16498

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1BE0

	/* emulator_api */
	#define psp_read                                    0xFC64
	#define psp_read_header                             0x10BE8
	#define psp_drm_patch5                              0x10A0C
	#define psp_drm_patch6                              0x10A3C
	#define psp_drm_patch7                              0x10A54
	#define psp_drm_patch8                              0x10A58
	#define psp_drm_patch9                              0x10B98
	#define psp_drm_patch11                             0x10B9C
	#define psp_drm_patch12                             0x10BAC
	#define psp_product_id_patch1                       0x10CAC
	#define psp_product_id_patch3                       0x10F84

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E35C
	#define psp_prx_patch                               0x57478
	#define psp_savedata_bind_patch1                    0x79810
	#define psp_savedata_bind_patch2                    0x79868
	#define psp_savedata_bind_patch3                    0x79384
	#define psp_extra_savedata_patch                    0x851A8
	#define psp_prometheus_patch                        0x12E870
	#define prx_patch_call_lr                           0x585CC

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C64
	#define psp_drm_key_overwrite                       (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46CC
	#define psp_savedata_patch2                         0x46A4
	#define psp_savedata_patch3                         0x4504
	#define psp_savedata_patch4                         0x453C
	#define psp_savedata_patch5                         0x4550
	#define psp_savedata_patch6                         0x46B8

	/* libfs */
	#define aio_copy_root_offset                        0xD5B4

	/* rebug */
	#define EXPLORE_PLUGIN_REBUG_HASH                   0xACF4AF2B000E71CF
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH            0x9CB3C54A00057710
	#define GAME_EXT_PLUGIN_REBUG_HASH                  0xE274AF7B0001D89E
	#define dex_ps2_nonbw_offset                        0xDAFC0
	#define dex_ps2_nonbw_offset2                       0x75464
	#define dex_ps2_nonbw_offset3                       0x16788
	#define dex_ps2tonet_patch                          0xC9A30
	#define dex_ps2tonet_size_patch                     0xC9A24
	#define dex_vmode_patch_offset                      0x446650
	#define dex_psp_drm_patch1                          0x244068
	#define dex_psp_drm_patch2                          0x244B00
	#define dex_psp_drm_patch3                          0x244740
	#define dex_psp_drm_patch4                          0x244F48
	#define dex_psp_drm_patchA                          0x244184
	#define dex_psp_drm_patchB                          0x244A1C
	#define dex_psp_drm_patchC                          0x243BBC
	#define dex_psp_drm_patchD                          0x24416C
	#define dex_psp_drm_patchE                          0x244170
	#define dex_psp_drm_patchF                          0x244B34
	#define dex_psp_extra_drm_patch                     0x0
#endif

#ifdef FIRMWARE_421D

	#define FIRMWARE_VERSION                                 0x421

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x421
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003F7A30ULL
		#define PS3MAPI_IDPS_2                               0x800000000048FE9CULL
		#define PS3MAPI_PSID                                 0x800000000048FEB4ULL
	#endif

	/* lv2 */
	#define TOC                                              0x363E80
	#define open_shared_kernel_object_symbol                 0x12A44
	#define close_kernel_object_handle_symbol                0x12064
	#define open_kernel_object_symbol                        0x12C34
	#define alloc_symbol                                     0x677F0
	#define dealloc_symbol                                   0x67C2C
	#define copy_to_user_symbol                              0xFEA4
	#define copy_from_user_symbol                            0x100C0
	#define copy_to_process_symbol                           0xFF5C
	#define copy_from_process_symbol                         0xFD6C
	#define page_allocate_symbol                             0x63360
	#define page_free_symbol                                 0x62DC4
	#define page_export_to_proc_symbol                       0x634FC
	#define page_unexport_from_proc_symbol                   0x62CB8
	#define kernel_ea_to_lpar_addr_symbol                    0x73288
	#define map_process_memory_symbol                        0x7A934
	#define memcpy_symbol                                    0x81FF4
	#define memset_symbol                                    0x51DF8
	#define memcmp_symbol                                    0x51108
	#define printf_symbol                                    0x2A6828
	#define printfnull_symbol                                0x2AB2AC
	#define sprintf_symbol                                   0x53220
	#define snprintf_symbol                                  0x5318C
	#define strcpy_symbol                                    0x51FA4
	#define strncpy_symbol                                   0x5206C
	#define strlen_symbol                                    0x51FCC
	#define strcat_symbol                                    0x51ED4
	#define strcmp_symbol                                    0x51F50
	#define strncmp_symbol                                   0x51FF8
	#define strchr_symbol                                    0x51F0C
	#define spin_lock_irqsave_ex_symbol                      0x2A46A8
	#define spin_unlock_irqrestore_ex_symbol                 0x2A467C
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x14530
	#define ppu_thread_exit_symbol                           0x145E8
	#define ppu_thread_join_symbol                           0x1463C
	#define ppu_thread_delay_symbol                          0x2A3E0
	#define create_user_thread2_symbol                       0x26A30
	#define start_thread_symbol                              0x25568
	#define run_thread_symbol                                0x24D2C
	#define register_thread_symbol                           0x29D2C8
	#define allocate_user_stack_symbol                       0x29DAB0
	#define mutex_create_symbol                              0x13C78
	#define mutex_destroy_symbol                             0x13C10
	#define mutex_lock_symbol                                0x13C08
	#define mutex_unlock_symbol                              0x13C00
	#define event_port_create_symbol                         0x136B4
	#define event_port_destroy_symbol                        0x13B1C
	#define event_port_connect_symbol                        0x13B94
	#define event_port_disconnect_symbol                     0x13AC0
	#define event_port_send_symbol                           0x136AC
	#define event_queue_create_symbol                        0x139BC
	#define event_queue_destroy_symbol                       0x13944
	#define event_queue_receive_symbol                       0x13788
	#define cellFsOpen_symbol                                0x2D99E0
	#define cellFsClose_symbol                               0x2D9848
	#define cellFsRead_symbol                                0x2D9984
	#define cellFsWrite_symbol                               0x2D98F0
	#define cellFsLseek_symbol                               0x2D9144
	#define cellFsStat_symbol                                0x2D91FC
	#define cellFsUnlink_internal_symbol                     0x1AF9BC
	#define cellFsUtilMount_symbol                           0x2D8EB8
	#define cellFsUtilUmount_symbol                          0x2D8E8C
	#define pathdup_from_user_symbol                         0x1B7D78
	#define open_path_symbol                                 0x2D9718
	#define open_fs_object_symbol                            0x196C44
	#define close_fs_object_symbol                           0x195C14
	#define storage_get_device_info_symbol                   0x2BA4DC
	#define storage_open_symbol                              0x2BA704
	#define storage_close_symbol                             0x2B8B68
	#define storage_read_symbol                              0x2B80E8
	#define storage_send_device_command_symbol               0x2B7C08
	#define storage_map_io_memory_symbol                     0x2BA388
	#define storage_unmap_io_memory_symbol                   0x2BA244
	#define storage_internal_get_device_object_symbol        0x2B76C0
	#define decrypt_func_symbol                              0x37F38
	#define lv1_call_99_wrapper_symbol                       0x53634
	#define modules_verification_symbol                      0x5D0A0
	#define prx_load_module_symbol                           0x8C7B4
	#define prx_start_module_symbol                          0x8B480
	#define prx_stop_module_symbol                           0x8C858
	#define prx_unload_module_symbol                         0x8B1B4
	#define prx_get_module_info_symbol                       0x8ABAC
	#define prx_get_module_list_symbol                       0x8AC2C
	#define extend_kstack_symbol                             0x731E0
	#define get_pseudo_random_number_symbol                  0x25DDE8
	#define syscall_table_symbol                             0x37A1B0
	#define syscall_call_offset                              0x2ABD90
	#define read_bdvd0_symbol                                0x1C224C
	#define read_bdvd1_symbol                                0x1C3E78
	#define read_bdvd2_symbol                                0x1D1000
	#define device_event_port_send_call                      0x2C44E8
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x2D9B78
	#define fsloop_close_call                                0x2D9BC8
	#define fsloop_read_call                                 0x2D9C08
	#define io_rtoc_entry_1                                 -0x48
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65A0
	#define storage_rtoc_entry_1                             0x2328
	#define device_event_rtoc_entry_1                        0x26B0
	#define process_rtoc_entry_1                            -0x77A0
	#define patch_func2                                      0x5DA58
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x21BAC
	#define user_thread_prio_patch2                          0x21BB8
	#define shutdown_patch_offset                            0xAB28
	#define shutdown_copy_params_call                        0xAB3C

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000E71CF
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB3C54A00057710
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001D89E
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BEC800006430
	#define PSP_EMULATOR_HASH                           0x7BE65D6D00023702
	#define PEMUCORELIB_HASH                            0xF349A563000BFCC8
	#define EMULATOR_API_HASH                           0xA9F5B2320001E7C6
	#define EMULATOR_DRM_HASH                           0xD2C7F3E20000538F
	#define EMULATOR_DRM_DATA_HASH                      0xB4F919590001B6E7
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC3B800003210

	/* lv1 */
	#define vsh_pos_in_ram                              0x910000

	/* vsh */
	#define ps2tonet_patch                              0xC9A30
	#define ps2tonet_size_patch                         0xC9A24
	#define vmode_patch_offset                          0x446650
	#define psp_drm_patch1                              0x244068
	#define psp_drm_patch2                              0x244B00
	#define psp_drm_patch3                              0x244740
	#define psp_drm_patch4                              0x244F48
	#define psp_drm_patchA                              0x244184
	#define psp_drm_patchB                              0x244A1C
	#define psp_drm_patchC                              0x243BBC
	#define psp_drm_patchD                              0x24416C
	#define psp_drm_patchE                              0x244170
	#define psp_drm_patchF                              0x244B34
	#define psp_extra_drm_patch                         0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDAFC0

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x75464

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x16788

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1BE0

	/* emulator_api */
	#define psp_read                                    0xFC64
	#define psp_read_header                             0x10BE8
	#define psp_drm_patch5                              0x10A0C
	#define psp_drm_patch6                              0x10A3C
	#define psp_drm_patch7                              0x10A54
	#define psp_drm_patch8                              0x10A58
	#define psp_drm_patch9                              0x10B98
	#define psp_drm_patch11                             0x10B9C
	#define psp_drm_patch12                             0x10BAC
	#define psp_product_id_patch1                       0x10CAC
	#define psp_product_id_patch3                       0x10F84

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E35C
	#define psp_prx_patch                               0x57478
	#define psp_savedata_bind_patch1                    0x79810
	#define psp_savedata_bind_patch2                    0x79868
	#define psp_savedata_bind_patch3                    0x79384
	#define psp_extra_savedata_patch                    0x851A8
	#define psp_prometheus_patch                        0x12E870
	#define prx_patch_call_lr                           0x585CC

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C64
	#define psp_drm_key_overwrite                       (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46CC
	#define psp_savedata_patch2                         0x46A4
	#define psp_savedata_patch3                         0x4504
	#define psp_savedata_patch4                         0x453C
	#define psp_savedata_patch5                         0x4550
	#define psp_savedata_patch6                         0x46B8

	/* libfs */
	#define aio_copy_root_offset                        0xD5B4

	/* CEX */
	#define cex_ps2tonet_patch                          0xC44EC
	#define cex_ps2tonet_size_patch                     0xC44E0
	#define cex_vmode_patch_offset                      0x43EA78
	#define cex_psp_drm_patch1                          0x23C85C
	#define cex_psp_drm_patch2                          0x23D2F4
	#define cex_psp_drm_patch3                          0x23CF34
	#define cex_psp_drm_patch4                          0x23D73C
	#define cex_psp_drm_patchA                          0x23C978
	#define cex_psp_drm_patchB                          0x23D210
	#define cex_psp_drm_patchC                          0x23C3B0
	#define cex_psp_drm_patchD                          0x23C960
	#define cex_psp_drm_patchE                          0x23C964
	#define cex_psp_drm_patchF                          0x23D328
	#define cex_psp_extra_drm_patch                     0x0
#endif

#ifdef FIRMWARE_430C

	#define FIRMWARE_VERSION                                 0x430

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x430
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003DB1B0ULL
		#define PS3MAPI_IDPS_2                               0x8000000000476F3CULL
		#define PS3MAPI_PSID                                 0x8000000000476F54ULL
	#endif

	/* lv2 */
	#define TOC                                              0x348200
	#define open_shared_kernel_object_symbol                 0x123F8
	#define close_kernel_object_handle_symbol                0x11A18
	#define open_kernel_object_symbol                        0x125E8
	#define alloc_symbol                                     0x64028
	#define dealloc_symbol                                   0x64464
	#define copy_to_user_symbol                              0xF858
	#define copy_from_user_symbol                            0xFA74
	#define copy_to_process_symbol                           0xF910
	#define copy_from_process_symbol                         0xF720
	#define page_allocate_symbol                             0x5FB98
	#define page_free_symbol                                 0x5F5FC
	#define page_export_to_proc_symbol                       0x5FD34
	#define page_unexport_from_proc_symbol                   0x5F4F0
	#define kernel_ea_to_lpar_addr_symbol                    0x6F91C
	#define map_process_memory_symbol                        0x76A3C
	#define memcpy_symbol                                    0x7E0FC
	#define memset_symbol                                    0x4E544
	#define memcmp_symbol                                    0x4D854
	#define printf_symbol                                    0x29FEEC
	#define printfnull_symbol                                0x2A495C
	#define sprintf_symbol                                   0x4F96C
	#define snprintf_symbol                                  0x4F8D8
	#define strcpy_symbol                                    0x4E6F0
	#define strncpy_symbol                                   0x4E7B8
	#define strlen_symbol                                    0x4E718
	#define strcat_symbol                                    0x4E620
	#define strcmp_symbol                                    0x4E69C
	#define strncmp_symbol                                   0x4E744
	#define strchr_symbol                                    0x4E658
	#define spin_lock_irqsave_ex_symbol                      0x29DFC0
	#define spin_unlock_irqrestore_ex_symbol                 0x29DF94
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x13EB0
	#define ppu_thread_exit_symbol                           0x13F68
	#define ppu_thread_join_symbol                           0x13FBC
	#define ppu_thread_delay_symbol                          0x28550
	#define create_user_thread2_symbol                       0x24E34
	#define start_thread_symbol                              0x23B00
	#define run_thread_symbol                                0x23330
	#define register_thread_symbol                           0x2981D4
	#define allocate_user_stack_symbol                       0x2989BC
	#define mutex_create_symbol                              0x13624
	#define mutex_destroy_symbol                             0x135BC
	#define mutex_lock_symbol                                0x135B4
	#define mutex_unlock_symbol                              0x135AC
	#define event_port_create_symbol                         0x13060
	#define event_port_destroy_symbol                        0x134C8
	#define event_port_connect_symbol                        0x13540
	#define event_port_disconnect_symbol                     0x1346C
	#define event_port_send_symbol                           0x13058
	#define event_queue_create_symbol                        0x13368
	#define event_queue_destroy_symbol                       0x132F0
	#define event_queue_receive_symbol                       0x13134
	#define cellFsOpen_symbol                                0x2C3F9C
	#define cellFsClose_symbol                               0x2C3E04
	#define cellFsRead_symbol                                0x2C3F40
	#define cellFsWrite_symbol                               0x2C3EAC
	#define cellFsLseek_symbol                               0x2C3534
	#define cellFsStat_symbol                                0x2C37B8
	#define cellFsUnlink_internal_symbol                     0x1AA184
	#define cellFsUtilMount_symbol                           0x2C3314
	#define cellFsUtilUmount_symbol                          0x2C32E8
	#define pathdup_from_user_symbol                         0x1B1DC4
	#define open_path_symbol                                 0x2C3CD4
	#define open_fs_object_symbol                            0x1913E8
	#define close_fs_object_symbol                           0x1903B8
	#define storage_get_device_info_symbol                   0x2A932C
	#define storage_open_symbol                              0x2A8850
	#define storage_close_symbol                             0x2A8DEC
	#define storage_read_symbol                              0x2A7D68
	#define storage_send_device_command_symbol               0x2A7EA4
	#define storage_map_io_memory_symbol                     0x2A91E8
	#define storage_unmap_io_memory_symbol                   0x2A90B4
	#define storage_internal_get_device_object_symbol        0x2A76F0
	#define decrypt_func_symbol                              0x3470C
	#define lv1_call_99_wrapper_symbol                       0x4FD80
	#define modules_verification_symbol                      0x598D8
	#define prx_load_module_symbol                           0x88294
	#define prx_start_module_symbol                          0x86F60
	#define prx_stop_module_symbol                           0x88338
	#define prx_unload_module_symbol                         0x86C94
	#define prx_get_module_info_symbol                       0x8671C
	#define prx_get_module_list_symbol                       0x8679C
	#define extend_kstack_symbol                             0x6F874
	#define get_pseudo_random_number_symbol                  0x2591C8
	#define syscall_table_symbol                             0x35DBE0
	#define syscall_call_offset                              0x2A5440
	#define read_bdvd0_symbol                                0x1BCD24
	#define read_bdvd1_symbol                                0x1BE950
	#define read_bdvd2_symbol                                0x1CBB08
	#define device_event_port_send_call                      0x2B16A8
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x2C4134
	#define fsloop_close_call                                0x2C4184
	#define fsloop_read_call                                 0x2C41C4
	#define io_rtoc_entry_1                                 -0x178
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x6680
	#define storage_rtoc_entry_1                             0x1E40
	#define device_event_rtoc_entry_1                        0x20B0
	#define process_rtoc_entry_1                            -0x7800
	#define patch_func2                                      0x5A290
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x201B0
	#define user_thread_prio_patch2                          0x201BC
	#define shutdown_patch_offset                            0xAAA8
	#define shutdown_copy_params_call                        0xAABC

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000EBA56
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB3CCAD00056F02
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001DD1D
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BEC800006430
	#define PSP_EMULATOR_HASH                           0x7BE646F50002371E
	#define PEMUCORELIB_HASH                            0xF349A563000BFD70
	#define EMULATOR_API_HASH                           0xA9F5B37A0001B739
	#define EMULATOR_DRM_HASH                           0xA324DC4A0000539C
	#define EMULATOR_DRM_DATA_HASH                      0x1D8D2DA00001B6E4
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC04800003207

	/* lv1 */
	#define vsh_pos_in_ram                              0x910000

	/* vsh */
	#define ps2tonet_patch                              0xC4D64
	#define ps2tonet_size_patch                         0xC4D58
	#define vmode_patch_offset                          0x4400CC
	#define psp_drm_patch1                              0x23D27C
	#define psp_drm_patch2                              0x23DD1C
	#define psp_drm_patch3                              0x23D958
	#define psp_drm_patch4                              0x23E164
	#define psp_drm_patchA                              0x23D398
	#define psp_drm_patchB                              0x23DC38
	#define psp_drm_patchC                              0x23CDD0
	#define psp_drm_patchD                              0x23D380
	#define psp_drm_patchE                              0x23D384
	#define psp_drm_patchF                              0x23DD50
	#define psp_extra_drm_patch                         0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDDDC8

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x69B68

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x167D8

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1C10

	/* emulator_api */
	#define psp_read                                    0xFB24
	#define psp_read_header                             0x10AA8
	#define psp_drm_patch5                              0x108CC
	#define psp_drm_patch6                              0x108FC
	#define psp_drm_patch7                              0x10914
	#define psp_drm_patch8                              0x10918
	#define psp_drm_patch9                              0x10A58
	#define psp_drm_patch11                             0x10A5C
	#define psp_drm_patch12                             0x10A6C
	#define psp_product_id_patch1                       0x10B6C
	#define psp_product_id_patch3                       0x10E44

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E340
	#define psp_prx_patch                               0x5745C
	#define psp_savedata_bind_patch1                    0x79810
	#define psp_savedata_bind_patch2                    0x79868
	#define psp_savedata_bind_patch3                    0x79384
	#define psp_extra_savedata_patch                    0x85194
	#define psp_prometheus_patch                        0x12E870
	#define prx_patch_call_lr                           0x585B0

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46D4
	#define psp_savedata_patch2                         0x46AC
	#define psp_savedata_patch3                         0x450C
	#define psp_savedata_patch4                         0x4544
	#define psp_savedata_patch5                         0x4558
	#define psp_savedata_patch6                         0x46C0

	/* libfs */
	#define aio_copy_root_offset                        0xD5B4

	/* rebug */
	#define EXPLORE_PLUGIN_REBUG_HASH                   0xACF4AF2B000EC258
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH            0x9CB3CB3900057221
	#define GAME_EXT_PLUGIN_REBUG_HASH                  0xE274AF7B0001DD6F
	#define dex_ps2_nonbw_offset                        0xDE1F4
	#define dex_ps2_nonbw_offset2                       0x6989C
	#define dex_ps2_nonbw_offset3                       0x16AC8
	#define dex_ps2tonet_patch                          0xCA2B8
	#define dex_ps2tonet_size_patch                     0xCA2AC
	#define dex_vmode_patch_offset                      0x447CB0
	#define dex_psp_drm_patch1                          0x244A94
	#define dex_psp_drm_patch2                          0x245534
	#define dex_psp_drm_patch3                          0x245170
	#define dex_psp_drm_patch4                          0x24597C
	#define dex_psp_drm_patchA                          0x244BB0
	#define dex_psp_drm_patchB                          0x245450
	#define dex_psp_drm_patchC                          0x2445E8
	#define dex_psp_drm_patchD                          0x244B98
	#define dex_psp_drm_patchE                          0x244B9C
	#define dex_psp_drm_patchF                          0x245568
	#define dex_psp_extra_drm_patch                     0x0
#endif

#ifdef FIRMWARE_430D

	#define FIRMWARE_VERSION                                 0x430

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x430
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003F9930ULL
		#define PS3MAPI_IDPS_2                               0x8000000000496F3CULL
		#define PS3MAPI_PSID                                 0x8000000000496F54ULL
	#endif

	/* lv2 */
	#define TOC                                              0x365CA0
	#define open_shared_kernel_object_symbol                 0x12A40
	#define close_kernel_object_handle_symbol                0x12060
	#define open_kernel_object_symbol                        0x12C30
	#define alloc_symbol                                     0x67940
	#define dealloc_symbol                                   0x67D7C
	#define copy_to_user_symbol                              0xFEA0
	#define copy_from_user_symbol                            0x100BC
	#define copy_to_process_symbol                           0xFF58
	#define copy_from_process_symbol                         0xFD68
	#define page_allocate_symbol                             0x634B0
	#define page_free_symbol                                 0x62F14
	#define page_export_to_proc_symbol                       0x6364C
	#define page_unexport_from_proc_symbol                   0x62E08
	#define kernel_ea_to_lpar_addr_symbol                    0x733B4
	#define map_process_memory_symbol                        0x7AA60
	#define memcpy_symbol                                    0x82120
	#define memset_symbol                                    0x51E34
	#define memcmp_symbol                                    0x51144
	#define printf_symbol                                    0x2A7F50
	#define printfnull_symbol                                0x2AC9D4
	#define sprintf_symbol                                   0x5325C
	#define snprintf_symbol                                  0x531C8
	#define strcpy_symbol                                    0x51FE0
	#define strncpy_symbol                                   0x520A8
	#define strlen_symbol                                    0x52008
	#define strcat_symbol                                    0x51F10
	#define strcmp_symbol                                    0x51F8C
	#define strncmp_symbol                                   0x52034
	#define strchr_symbol                                    0x51F48
	#define spin_lock_irqsave_ex_symbol                      0x2A5DD0
	#define spin_unlock_irqrestore_ex_symbol                 0x2A5DA4
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x1452C
	#define ppu_thread_exit_symbol                           0x145E4
	#define ppu_thread_join_symbol                           0x14638
	#define ppu_thread_delay_symbol                          0x2A3DC
	#define create_user_thread2_symbol                       0x26A2C
	#define start_thread_symbol                              0x25564
	#define run_thread_symbol                                0x24D28
	#define register_thread_symbol                           0x29EA38
	#define allocate_user_stack_symbol                       0x29F220
	#define mutex_create_symbol                              0x13C74
	#define mutex_destroy_symbol                             0x13C0C
	#define mutex_lock_symbol                                0x13C04
	#define mutex_unlock_symbol                              0x13BFC
	#define event_port_create_symbol                         0x136B0
	#define event_port_destroy_symbol                        0x13B18
	#define event_port_connect_symbol                        0x13B90
	#define event_port_disconnect_symbol                     0x13ABC
	#define event_port_send_symbol                           0x136A8
	#define event_queue_create_symbol                        0x139B8
	#define event_queue_destroy_symbol                       0x13940
	#define event_queue_receive_symbol                       0x13784
	#define cellFsOpen_symbol                                0x2DB114
	#define cellFsClose_symbol                               0x2DAF7C
	#define cellFsRead_symbol                                0x2DB0B8
	#define cellFsWrite_symbol                               0x2DB024
	#define cellFsLseek_symbol                               0x2DA878
	#define cellFsStat_symbol                                0x2DA930
	#define cellFsUnlink_internal_symbol                     0x1B0458
	#define cellFsUtilMount_symbol                           0x2DA5EC
	#define cellFsUtilUmount_symbol                          0x2DA5C0
	#define pathdup_from_user_symbol                         0x1B81B4
	#define open_path_symbol                                 0x2DAE4C
	#define open_fs_object_symbol                            0x1976BC
	#define close_fs_object_symbol                           0x19668C
	#define storage_get_device_info_symbol                   0x2BBC04
	#define storage_open_symbol                              0x2BBE2C
	#define storage_close_symbol                             0x2BA290
	#define storage_read_symbol                              0x2B9810
	#define storage_send_device_command_symbol               0x2B9330
	#define storage_map_io_memory_symbol                     0x2BBAB0
	#define storage_unmap_io_memory_symbol                   0x2BB96C
	#define storage_internal_get_device_object_symbol        0x2B8DE8
	#define decrypt_func_symbol                              0x37F74
	#define lv1_call_99_wrapper_symbol                       0x53670
	#define modules_verification_symbol                      0x5D1F0
	#define prx_load_module_symbol                           0x8C8E0
	#define prx_start_module_symbol                          0x8B5AC
	#define prx_stop_module_symbol                           0x8C984
	#define prx_unload_module_symbol                         0x8B2E0
	#define prx_get_module_info_symbol                       0x8ACD8
	#define prx_get_module_list_symbol                       0x8AD58
	#define extend_kstack_symbol                             0x7330C
	#define get_pseudo_random_number_symbol                  0x25F5E4
	#define syscall_table_symbol                             0x37C068
	#define syscall_call_offset                              0x2AD4B8
	#define read_bdvd0_symbol                                0x1C3114
	#define read_bdvd1_symbol                                0x1C4D40
	#define read_bdvd2_symbol                                0x1D1EF8
	#define device_event_port_send_call                      0x2C5C10
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x2DB2AC
	#define fsloop_close_call                                0x2DB2FC
	#define fsloop_read_call                                 0x2DB33C
	#define io_rtoc_entry_1                                 -0x48
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65A0
	#define storage_rtoc_entry_1                             0x2318
	#define device_event_rtoc_entry_1                        0x26A0
	#define process_rtoc_entry_1                            -0x77A0
	#define patch_func2                                      0x5DBA8
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x21BA8
	#define user_thread_prio_patch2                          0x21BB4
	#define shutdown_patch_offset                            0xAB28
	#define shutdown_copy_params_call                        0xAB3C

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000EC258
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB3CB3900057221
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001DD6F
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BEC800006430
	#define PSP_EMULATOR_HASH                           0x7BE646F50002371E
	#define PEMUCORELIB_HASH                            0xF349A563000BFD70
	#define EMULATOR_API_HASH                           0xA9F5B37A0001B739
	#define EMULATOR_DRM_HASH                           0xA324DC4A0000539C
	#define EMULATOR_DRM_DATA_HASH                      0x1D8D2DA00001B6E4
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC04800003207

	/* lv1 */
	#define vsh_pos_in_ram                              0x910000

	/* vsh */
	#define ps2tonet_patch                              0xCA2B8
	#define ps2tonet_size_patch                         0xCA2AC
	#define vmode_patch_offset                          0x447CB0
	#define psp_drm_patch1                              0x244A94
	#define psp_drm_patch2                              0x245534
	#define psp_drm_patch3                              0x245170
	#define psp_drm_patch4                              0x24597C
	#define psp_drm_patchA                              0x244BB0
	#define psp_drm_patchB                              0x245450
	#define psp_drm_patchC                              0x2445E8
	#define psp_drm_patchD                              0x244B98
	#define psp_drm_patchE                              0x244B9C
	#define psp_drm_patchF                              0x245568
	#define psp_extra_drm_patch                         0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDE1F4

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x6989C

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x16AC8

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1C10

	/* emulator_api */
	#define psp_read                                    0xFB24
	#define psp_read_header                             0x10AA8
	#define psp_drm_patch5                              0x108CC
	#define psp_drm_patch6                              0x108FC
	#define psp_drm_patch7                              0x10914
	#define psp_drm_patch8                              0x10918
	#define psp_drm_patch9                              0x10A58
	#define psp_drm_patch11                             0x10A5C
	#define psp_drm_patch12                             0x10A6C
	#define psp_product_id_patch1                       0x10B6C
	#define psp_product_id_patch3                       0x10E44

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E340
	#define psp_prx_patch                               0x5745C
	#define psp_savedata_bind_patch1                    0x79810
	#define psp_savedata_bind_patch2                    0x79868
	#define psp_savedata_bind_patch3                    0x79384
	#define psp_extra_savedata_patch                    0x85194
	#define psp_prometheus_patch                        0x12E870
	#define prx_patch_call_lr                           0x585B0

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46D4
	#define psp_savedata_patch2                         0x46AC
	#define psp_savedata_patch3                         0x450C
	#define psp_savedata_patch4                         0x4544
	#define psp_savedata_patch5                         0x4558
	#define psp_savedata_patch6                         0x46C0

	/* libfs */
	#define aio_copy_root_offset                        0xD5B4

	/* CEX */
	#define cex_ps2tonet_patch                          0xC4D64
	#define cex_ps2tonet_size_patch                     0xC4D58
	#define cex_vmode_patch_offset                      0x4400CC
	#define cex_psp_drm_patch1                          0x23D27C
	#define cex_psp_drm_patch2                          0x23DD1C
	#define cex_psp_drm_patch3                          0x23D958
	#define cex_psp_drm_patch4                          0x23E164
	#define cex_psp_drm_patchA                          0x23D398
	#define cex_psp_drm_patchB                          0x23DC38
	#define cex_psp_drm_patchC                          0x23CDD0
	#define cex_psp_drm_patchD                          0x23D380
	#define cex_psp_drm_patchE                          0x23D384
	#define cex_psp_drm_patchF                          0x23DD50
	#define cex_psp_extra_drm_patch                     0x0
#endif

#ifdef FIRMWARE_431C

	#define FIRMWARE_VERSION                                 0x431

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x431
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003DB1B0ULL
		#define PS3MAPI_IDPS_2                               0x8000000000476F3CULL
		#define PS3MAPI_PSID                                 0x8000000000476F54ULL
	#endif

	/* lv2 */
	#define TOC                                              0x348210
	#define open_shared_kernel_object_symbol                 0x123FC
	#define close_kernel_object_handle_symbol                0x11A1C
	#define open_kernel_object_symbol                        0x125EC
	#define alloc_symbol                                     0x6402C
	#define dealloc_symbol                                   0x64468
	#define copy_to_user_symbol                              0xF85C
	#define copy_from_user_symbol                            0xFA78
	#define copy_to_process_symbol                           0xF914
	#define copy_from_process_symbol                         0xF724
	#define page_allocate_symbol                             0x5FB9C
	#define page_free_symbol                                 0x5F600
	#define page_export_to_proc_symbol                       0x5FD38
	#define page_unexport_from_proc_symbol                   0x5F4F4
	#define kernel_ea_to_lpar_addr_symbol                    0x6F920
	#define map_process_memory_symbol                        0x76A40
	#define memcpy_symbol                                    0x7E100
	#define memset_symbol                                    0x4E548
	#define memcmp_symbol                                    0x4D858
	#define printf_symbol                                    0x29FEF8
	#define printfnull_symbol                                0x2A4968
	#define sprintf_symbol                                   0x4F970
	#define snprintf_symbol                                  0x4F8DC
	#define strcpy_symbol                                    0x4E6F4
	#define strncpy_symbol                                   0x4E7BC
	#define strlen_symbol                                    0x4E71C
	#define strcat_symbol                                    0x4E624
	#define strcmp_symbol                                    0x4E6A0
	#define strncmp_symbol                                   0x4E748
	#define strchr_symbol                                    0x4E65C
	#define spin_lock_irqsave_ex_symbol                      0x29DFCC
	#define spin_unlock_irqrestore_ex_symbol                 0x29DFA0
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x13EB4
	#define ppu_thread_exit_symbol                           0x13F6C
	#define ppu_thread_join_symbol                           0x13FC0
	#define ppu_thread_delay_symbol                          0x28554
	#define create_user_thread2_symbol                       0x24E38
	#define start_thread_symbol                              0x23B04
	#define run_thread_symbol                                0x23334
	#define register_thread_symbol                           0x2981E0
	#define allocate_user_stack_symbol                       0x2989C8
	#define mutex_create_symbol                              0x13628
	#define mutex_destroy_symbol                             0x135C0
	#define mutex_lock_symbol                                0x135B8
	#define mutex_unlock_symbol                              0x135B0
	#define event_port_create_symbol                         0x13064
	#define event_port_destroy_symbol                        0x134CC
	#define event_port_connect_symbol                        0x13544
	#define event_port_disconnect_symbol                     0x13470
	#define event_port_send_symbol                           0x1305C
	#define event_queue_create_symbol                        0x1336C
	#define event_queue_destroy_symbol                       0x132F4
	#define event_queue_receive_symbol                       0x13138
	#define cellFsOpen_symbol                                0x2C3FA8
	#define cellFsClose_symbol                               0x2C3E10
	#define cellFsRead_symbol                                0x2C3F4C
	#define cellFsWrite_symbol                               0x2C3EB8
	#define cellFsLseek_symbol                               0x2C3540
	#define cellFsStat_symbol                                0x2C37C4
	#define cellFsUnlink_internal_symbol                     0x1AA18C
	#define cellFsUtilMount_symbol                           0x2C3320
	#define cellFsUtilUmount_symbol                          0x2C32F4
	#define pathdup_from_user_symbol                         0x1B1DCC
	#define open_path_symbol                                 0x2C3CE0
	#define open_fs_object_symbol                            0x1913F0
	#define close_fs_object_symbol                           0x1903C0
	#define storage_get_device_info_symbol                   0x2A9338
	#define storage_open_symbol                              0x2A885C
	#define storage_close_symbol                             0x2A8DF8
	#define storage_read_symbol                              0x2A7D74
	#define storage_send_device_command_symbol               0x2A7EB0
	#define storage_map_io_memory_symbol                     0x2A91F4
	#define storage_unmap_io_memory_symbol                   0x2A90C0
	#define storage_internal_get_device_object_symbol        0x2A76FC
	#define decrypt_func_symbol                              0x34710
	#define lv1_call_99_wrapper_symbol                       0x4FD84
	#define modules_verification_symbol                      0x598DC
	#define prx_load_module_symbol                           0x88298
	#define prx_start_module_symbol                          0x86F64
	#define prx_stop_module_symbol                           0x8833C
	#define prx_unload_module_symbol                         0x86C98
	#define prx_get_module_info_symbol                       0x86720
	#define prx_get_module_list_symbol                       0x867A0
	#define extend_kstack_symbol                             0x6F878
	#define get_pseudo_random_number_symbol                  0x2591D0
	#define syscall_table_symbol                             0x35DBE0
	#define syscall_call_offset                              0x2A544C
	#define read_bdvd0_symbol                                0x1BCD2C
	#define read_bdvd1_symbol                                0x1BE958
	#define read_bdvd2_symbol                                0x1CBB10
	#define device_event_port_send_call                      0x2B16B4
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x2C4140
	#define fsloop_close_call                                0x2C4190
	#define fsloop_read_call                                 0x2C41D0
	#define io_rtoc_entry_1                                 -0x178
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x6680
	#define storage_rtoc_entry_1                             0x1E40
	#define device_event_rtoc_entry_1                        0x20B0
	#define process_rtoc_entry_1                            -0x7800
	#define patch_func2                                      0x5A294
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x201B4
	#define user_thread_prio_patch2                          0x201C0
	#define shutdown_patch_offset                            0xAAA8
	#define shutdown_copy_params_call                        0xAABC

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000EBA56
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB3CCAD00056F02
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001DD1D
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BEC800006430
	#define PSP_EMULATOR_HASH                           0x7BE65D6D00023702
	#define PEMUCORELIB_HASH                            0xF349A563000BFD6F
	#define EMULATOR_API_HASH                           0xA9F5B37A0001B739
	#define EMULATOR_DRM_HASH                           0xA324DC4A0000539C
	#define EMULATOR_DRM_DATA_HASH                      0x1D8D2DA00001B6E4
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC04800003207

	/* lv1 */
	#define vsh_pos_in_ram                              0x910000

	/* vsh */
	#define ps2tonet_patch                              0xC4D64
	#define ps2tonet_size_patch                         0xC4D58
	#define vmode_patch_offset                          0x4400D0
	#define psp_drm_patch1                              0x23D280
	#define psp_drm_patch2                              0x23DD20
	#define psp_drm_patch3                              0x23D95C
	#define psp_drm_patch4                              0x23E168
	#define psp_drm_patchA                              0x23D39C
	#define psp_drm_patchB                              0x23DC3C
	#define psp_drm_patchC                              0x23CDD4
	#define psp_drm_patchD                              0x23D384
	#define psp_drm_patchE                              0x23D388
	#define psp_drm_patchF                              0x23DD54
	#define psp_extra_drm_patch                         0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDDDC8

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x69B68

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x167D8

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1BE0

	/* emulator_api */
	#define psp_read                                    0xFB24
	#define psp_read_header                             0x10AA8
	#define psp_drm_patch5                              0x108CC
	#define psp_drm_patch6                              0x108FC
	#define psp_drm_patch7                              0x10914
	#define psp_drm_patch8                              0x10918
	#define psp_drm_patch9                              0x10A58
	#define psp_drm_patch11                             0x10A5C
	#define psp_drm_patch12                             0x10A6C
	#define psp_product_id_patch1                       0x10B6C
	#define psp_product_id_patch3                       0x10E44

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E340
	#define psp_prx_patch                               0x5745C
	#define psp_savedata_bind_patch1                    0x79810
	#define psp_savedata_bind_patch2                    0x79868
	#define psp_savedata_bind_patch3                    0x79384
	#define psp_extra_savedata_patch                    0x85194
	#define psp_prometheus_patch                        0x12E870
	#define prx_patch_call_lr                           0x585B0

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46D4
	#define psp_savedata_patch2                         0x46AC
	#define psp_savedata_patch3                         0x450C
	#define psp_savedata_patch4                         0x4544
	#define psp_savedata_patch5                         0x4558
	#define psp_savedata_patch6                         0x46C0

	/* libfs */
	#define aio_copy_root_offset                        0xD5B4

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                   0xACF4AF2B000EC258
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH            0x9CB3CB3900057221
	#define GAME_EXT_PLUGIN_REBUG_HASH                  0xE274AF7B0001DD6F
	#define dex_ps2_nonbw_offset                        0xDE1F4
	#define dex_ps2_nonbw_offset2                       0x6989C
	#define dex_ps2_nonbw_offset3                       0x16AC8
	#define dex_ps2tonet_patch                          0xCA2B8
	#define dex_ps2tonet_size_patch                     0xCA2AC
	#define dex_vmode_patch_offset                      0x447CB4
	#define dex_psp_drm_patch1                          0x244A98
	#define dex_psp_drm_patch2                          0x245538
	#define dex_psp_drm_patch3                          0x245174
	#define dex_psp_drm_patch4                          0x245980
	#define dex_psp_drm_patchA                          0x244BB4
	#define dex_psp_drm_patchB                          0x245454
	#define dex_psp_drm_patchC                          0x2445EC
	#define dex_psp_drm_patchD                          0x244B9C
	#define dex_psp_drm_patchE                          0x244BA0
	#define dex_psp_drm_patchF                          0x24556C
	#define dex_psp_extra_drm_patch                     0x0
#endif

#ifdef FIRMWARE_440C

	#define FIRMWARE_VERSION                                 0x440

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x440
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003DB830ULL
		#define PS3MAPI_IDPS_2                               0x8000000000476F3CULL
		#define PS3MAPI_PSID                                 0x8000000000476F54ULL
	#endif

	/* lv2 */
	#define TOC                                              0x3487D0
	#define open_shared_kernel_object_symbol                 0x12470
	#define close_kernel_object_handle_symbol                0x11A90
	#define open_kernel_object_symbol                        0x12660
	#define alloc_symbol                                     0x62F74
	#define dealloc_symbol                                   0x633B0
	#define copy_to_user_symbol                              0xF858
	#define copy_from_user_symbol                            0xFA74
	#define copy_to_process_symbol                           0xF910
	#define copy_from_process_symbol                         0xF720
	#define page_allocate_symbol                             0x5EAE4
	#define page_free_symbol                                 0x5E548
	#define page_export_to_proc_symbol                       0x5EC80
	#define page_unexport_from_proc_symbol                   0x5E43C
	#define kernel_ea_to_lpar_addr_symbol                    0x6E868
	#define map_process_memory_symbol                        0x75988
	#define memcpy_symbol                                    0x7D048
	#define memset_symbol                                    0x4D490
	#define memcmp_symbol                                    0x4C7A0
	#define printf_symbol                                    0x2A02D4
	#define printfnull_symbol                                0x2A4D44
	#define sprintf_symbol                                   0x4E8B8
	#define snprintf_symbol                                  0x4E824
	#define strcpy_symbol                                    0x4D63C
	#define strncpy_symbol                                   0x4D704
	#define strlen_symbol                                    0x4D664
	#define strcat_symbol                                    0x4D56C
	#define strcmp_symbol                                    0x4D5E8
	#define strncmp_symbol                                   0x4D690
	#define strchr_symbol                                    0x4D5A4
	#define spin_lock_irqsave_ex_symbol                      0x29D3D4
	#define spin_unlock_irqrestore_ex_symbol                 0x29D3A8
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x13F28
	#define ppu_thread_exit_symbol                           0x13FE0
	#define ppu_thread_join_symbol                           0x14034
	#define ppu_thread_delay_symbol                          0x285C8
	#define create_user_thread2_symbol                       0x24EAC
	#define start_thread_symbol                              0x23B78
	#define run_thread_symbol                                0x233A8
	#define register_thread_symbol                           0x2975E4
	#define allocate_user_stack_symbol                       0x297DCC
	#define mutex_create_symbol                              0x1369C
	#define mutex_destroy_symbol                             0x13634
	#define mutex_lock_symbol                                0x1362C
	#define mutex_unlock_symbol                              0x13624
	#define event_port_create_symbol                         0x130D8
	#define event_port_destroy_symbol                        0x13540
	#define event_port_connect_symbol                        0x135B8
	#define event_port_disconnect_symbol                     0x134E4
	#define event_port_send_symbol                           0x130D0
	#define event_queue_create_symbol                        0x133E0
	#define event_queue_destroy_symbol                       0x13368
	#define event_queue_receive_symbol                       0x131AC
	#define cellFsOpen_symbol                                0x2C454C
	#define cellFsClose_symbol                               0x2C43B4
	#define cellFsRead_symbol                                0x2C44F0
	#define cellFsWrite_symbol                               0x2C445C
	#define cellFsLseek_symbol                               0x2C3AE4
	#define cellFsStat_symbol                                0x2C3D68
	#define cellFsUnlink_internal_symbol                     0x1AAD08
	#define cellFsUtilMount_symbol                           0x2C38C4
	#define cellFsUtilUmount_symbol                          0x2C3898
	#define pathdup_from_user_symbol                         0x1B0D98
	#define open_path_symbol                                 0x2EA518
	#define open_fs_object_symbol                            0x1903A0
	#define close_fs_object_symbol                           0x18F370
	#define storage_get_device_info_symbol                   0x2A9724
	#define storage_open_symbol                              0x2A9134
	#define storage_close_symbol                             0x2A8F24
	#define storage_read_symbol                              0x2A8494
	#define storage_send_device_command_symbol               0x2A8020
	#define storage_map_io_memory_symbol                     0x2A95E0
	#define storage_unmap_io_memory_symbol                   0x2A94AC
	#define storage_internal_get_device_object_symbol        0x2A7AD8
	#define decrypt_func_symbol                              0x34794
	#define lv1_call_99_wrapper_symbol                       0x4ECCC
	#define modules_verification_symbol                      0x58824
	#define prx_load_module_symbol                           0x87230
	#define prx_start_module_symbol                          0x85EFC
	#define prx_stop_module_symbol                           0x872D4
	#define prx_unload_module_symbol                         0x85C30
	#define prx_get_module_info_symbol                       0x856B8
	#define prx_get_module_list_symbol                       0x85738
	#define extend_kstack_symbol                             0x6E7C0
	#define get_pseudo_random_number_symbol                  0x258278
	#define syscall_table_symbol                             0x35E260
	#define syscall_call_offset                              0x2A5828
	#define read_bdvd0_symbol                                0x1BBD08
	#define read_bdvd1_symbol                                0x1BD934
	#define read_bdvd2_symbol                                0x1CAAEC
	#define device_event_port_send_call                      0x2B1C58
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x2C46E4
	#define fsloop_close_call                                0x2C4734
	#define fsloop_read_call                                 0x2C4774
	#define io_rtoc_entry_1                                 -0x150
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x6688
	#define storage_rtoc_entry_1                             0x1E98
	#define device_event_rtoc_entry_1                        0x2108
	#define process_rtoc_entry_1                            -0x7800
	#define patch_func2                                      0x591DC
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x20228
	#define user_thread_prio_patch2                          0x20234
	#define shutdown_patch_offset                            0xAAA8
	#define shutdown_copy_params_call                        0xAABC

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000EC812
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB2345100056F13
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001DE0E
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BEC800006430
	#define PSP_EMULATOR_HASH                           0x7BE6413100023720
	#define PEMUCORELIB_HASH                            0xF349A563000C0A42
	#define EMULATOR_API_HASH                           0xA9F5B55A0001B7C2
	#define EMULATOR_DRM_HASH                           0xA324DC4A0000539C
	#define EMULATOR_DRM_DATA_HASH                      0x1D8D2DA00001B6E4
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC3B800003212

	/* lv1 */
	#define vsh_pos_in_ram                              0x510000

	/* vsh */
	#define ps2tonet_patch                              0xC4D64
	#define ps2tonet_size_patch                         0xC4D58
	#define vmode_patch_offset                          0x44215C
	#define psp_drm_patch1                              0x23E490
	#define psp_drm_patch2                              0x23EF30
	#define psp_drm_patch3                              0x23EB6C
	#define psp_drm_patch4                              0x23F378
	#define psp_drm_patchA                              0x23E5AC
	#define psp_drm_patchB                              0x23EE4C
	#define psp_drm_patchC                              0x23DFE4
	#define psp_drm_patchD                              0x23E594
	#define psp_drm_patchE                              0x23E598
	#define psp_drm_patchF                              0x23EF64
	#define psp_extra_drm_patch                         0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDE5F0

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x69B6C

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x167F8

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1BF4

	/* emulator_api */
	#define psp_read                                    0xFC60
	#define psp_read_header                             0x10BE4
	#define psp_drm_patch5                              0x10A08
	#define psp_drm_patch6                              0x10A38
	#define psp_drm_patch7                              0x10A50
	#define psp_drm_patch8                              0x10A54
	#define psp_drm_patch9                              0x10B94
	#define psp_drm_patch11                             0x10B98
	#define psp_drm_patch12                             0x10BA8
	#define psp_product_id_patch1                       0x10CA8
	#define psp_product_id_patch3                       0x10F80

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6B0
	#define psp_prx_patch                               0x577CC
	#define psp_savedata_bind_patch1                    0x7A4B0
	#define psp_savedata_bind_patch2                    0x7A508
	#define psp_savedata_bind_patch3                    0x7A024
	#define psp_extra_savedata_patch                    0x87520
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x58920

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46CC
	#define psp_savedata_patch2                         0x46A4
	#define psp_savedata_patch3                         0x4504
	#define psp_savedata_patch4                         0x453C
	#define psp_savedata_patch5                         0x4550
	#define psp_savedata_patch6                         0x46B8

	/* libfs */
	#define aio_copy_root_offset                        0xD5B4

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                   0xACF4AF2B000ED050
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH            0x9CB3CC7100057283
	#define GAME_EXT_PLUGIN_REBUG_HASH                  0xE274AF7B0001DE56
	#define dex_ps2_nonbw_offset                        0xDEA18
	#define dex_ps2_nonbw_offset2                       0x698A4
	#define dex_ps2_nonbw_offset3                       0x16AE8
	#define dex_ps2tonet_patch                          0xCA2C0
	#define dex_ps2tonet_size_patch                     0xCA2B4
	#define dex_vmode_patch_offset                      0x449D64
	#define dex_psp_drm_patch1                          0x245CCC
	#define dex_psp_drm_patch2                          0x24676C
	#define dex_psp_drm_patch3                          0x2463A8
	#define dex_psp_drm_patch4                          0x246BB4
	#define dex_psp_drm_patchA                          0x245DE8
	#define dex_psp_drm_patchB                          0x246688
	#define dex_psp_drm_patchC                          0x245820
	#define dex_psp_drm_patchD                          0x245DD0
	#define dex_psp_drm_patchE                          0x245DD4
	#define dex_psp_drm_patchF                          0x2467A0
	#define dex_psp_extra_drm_patch                     0x0
#endif

#ifdef FIRMWARE_441C

	#define FIRMWARE_VERSION                                 0x441

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x441
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003DB830ULL
		#define PS3MAPI_IDPS_2                               0x8000000000476F3CULL
		#define PS3MAPI_PSID                                 0x8000000000476F54ULL
	#endif

	/* lv2 */
	#define TOC                                              0x3487E0
	#define open_shared_kernel_object_symbol                 0x12474
	#define close_kernel_object_handle_symbol                0x11A94
	#define open_kernel_object_symbol                        0x12664
	#define alloc_symbol                                     0x62F78
	#define dealloc_symbol                                   0x633B4
	#define copy_to_user_symbol                              0xF85C
	#define copy_from_user_symbol                            0xFA78
	#define copy_to_process_symbol                           0xF914
	#define copy_from_process_symbol                         0xF724
	#define page_allocate_symbol                             0x5EAE8
	#define page_free_symbol                                 0x5E54C
	#define page_export_to_proc_symbol                       0x5EC84
	#define page_unexport_from_proc_symbol                   0x5E440
	#define kernel_ea_to_lpar_addr_symbol                    0x6E86C
	#define map_process_memory_symbol                        0x7598C
	#define memcpy_symbol                                    0x7D04C
	#define memset_symbol                                    0x4D494
	#define memcmp_symbol                                    0x4C7A4
	#define printf_symbol                                    0x2A02E0
	#define printfnull_symbol                                0x2A4D50
	#define sprintf_symbol                                   0x4E8BC
	#define snprintf_symbol                                  0x4E828
	#define strcpy_symbol                                    0x4D640
	#define strncpy_symbol                                   0x4D708
	#define strlen_symbol                                    0x4D668
	#define strcat_symbol                                    0x4D570
	#define strcmp_symbol                                    0x4D5EC
	#define strncmp_symbol                                   0x4D694
	#define strchr_symbol                                    0x4D5A8
	#define spin_lock_irqsave_ex_symbol                      0x29D3E0
	#define spin_unlock_irqrestore_ex_symbol                 0x29D3B4
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x13F2C
	#define ppu_thread_exit_symbol                           0x13FE4
	#define ppu_thread_join_symbol                           0x14038
	#define ppu_thread_delay_symbol                          0x285CC
	#define create_user_thread2_symbol                       0x24EB0
	#define start_thread_symbol                              0x23B7C
	#define run_thread_symbol                                0x233AC
	#define register_thread_symbol                           0x2975F0
	#define allocate_user_stack_symbol                       0x297DD8
	#define mutex_create_symbol                              0x136A0
	#define mutex_destroy_symbol                             0x13638
	#define mutex_lock_symbol                                0x13630
	#define mutex_unlock_symbol                              0x13628
	#define event_port_create_symbol                         0x130DC
	#define event_port_destroy_symbol                        0x13544
	#define event_port_connect_symbol                        0x135BC
	#define event_port_disconnect_symbol                     0x134E8
	#define event_port_send_symbol                           0x130D4
	#define event_queue_create_symbol                        0x133E4
	#define event_queue_destroy_symbol                       0x1336C
	#define event_queue_receive_symbol                       0x131B0
	#define cellFsOpen_symbol                                0x2C4558
	#define cellFsClose_symbol                               0x2C43C0
	#define cellFsRead_symbol                                0x2C44FC
	#define cellFsWrite_symbol                               0x2C4468
	#define cellFsLseek_symbol                               0x2C3AF0
	#define cellFsStat_symbol                                0x2C3D74
	#define cellFsUnlink_internal_symbol                     0x1AAD10
	#define cellFsUtilMount_symbol                           0x2C38D0
	#define cellFsUtilUmount_symbol                          0x2C38A4
	#define pathdup_from_user_symbol                         0x1B0DA0
	#define open_path_symbol                                 0x2C4290
	#define open_fs_object_symbol                            0x1903A8
	#define close_fs_object_symbol                           0x18F378
	#define storage_get_device_info_symbol                   0x2A9730
	#define storage_open_symbol                              0x2A9140
	#define storage_close_symbol                             0x2A8F30
	#define storage_read_symbol                              0x2A84A0
	#define storage_send_device_command_symbol               0x2A802C
	#define storage_map_io_memory_symbol                     0x2A95EC
	#define storage_unmap_io_memory_symbol                   0x2A94B8
	#define storage_internal_get_device_object_symbol        0x2A7AE4
	#define decrypt_func_symbol                              0x34798
	#define lv1_call_99_wrapper_symbol                       0x4ECD0
	#define modules_verification_symbol                      0x58828
	#define prx_load_module_symbol                           0x87234
	#define prx_start_module_symbol                          0x85F00
	#define prx_stop_module_symbol                           0x872D8
	#define prx_unload_module_symbol                         0x85C34
	#define prx_get_module_info_symbol                       0x856BC
	#define prx_get_module_list_symbol                       0x8573C
	#define extend_kstack_symbol                             0x6E7C4
	#define get_pseudo_random_number_symbol                  0x258280
	#define syscall_table_symbol                             0x35E260
	#define syscall_call_offset                              0x2A5834
	#define read_bdvd0_symbol                                0x1BBD10
	#define read_bdvd1_symbol                                0x1BD93C
	#define read_bdvd2_symbol                                0x1CAAF4
	#define device_event_port_send_call                      0x2B1C64
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x2C46F0
	#define fsloop_close_call                                0x2C4740
	#define fsloop_read_call                                 0x2C4780
	#define io_rtoc_entry_1                                 -0x150
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x6688
	#define storage_rtoc_entry_1                             0x1E98
	#define device_event_rtoc_entry_1                        0x2108
	#define process_rtoc_entry_1                            -0x7800
	#define patch_func2                                      0x591E0
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x2022C
	#define user_thread_prio_patch2                          0x20238
	#define shutdown_patch_offset                            0xAAA8
	#define shutdown_copy_params_call                        0xAABC

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000EC7FB
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB3C7F100056FE5
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001DE0E
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BEC800006430
	#define PSP_EMULATOR_HASH                           0x7BE6413100023721
	#define PEMUCORELIB_HASH                            0xF349A563000C0A38
	#define EMULATOR_API_HASH                           0xA9F5B55A0001B7C2
	#define EMULATOR_DRM_HASH                           0xA324DC4A0000539C
	#define EMULATOR_DRM_DATA_HASH                      0x1D8D2DA00001B6E4
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC3B800003212

	/* lv1 */
	#define vsh_pos_in_ram                              0x910000

	/* vsh */
	#define ps2tonet_patch                              0xC4D64
	#define ps2tonet_size_patch                         0xC4D58
	#define vmode_patch_offset                          0x442160
	#define psp_drm_patch1                              0x23E494
	#define psp_drm_patch2                              0x23EF34
	#define psp_drm_patch3                              0x23EB70
	#define psp_drm_patch4                              0x23F37C
	#define psp_drm_patchA                              0x23E5B0
	#define psp_drm_patchB                              0x23EE50
	#define psp_drm_patchC                              0x23DFE8
	#define psp_drm_patchD                              0x23E598
	#define psp_drm_patchE                              0x23E59C
	#define psp_drm_patchF                              0x23EF68
	#define psp_extra_drm_patch                         0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDE7A0

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x69D2C

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x167F8

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1BF4

	/* emulator_api */
	#define psp_read                                    0xFC60
	#define psp_read_header                             0x10BE4
	#define psp_drm_patch5                              0x10A08
	#define psp_drm_patch6                              0x10A38
	#define psp_drm_patch7                              0x10A50
	#define psp_drm_patch8                              0x10A54
	#define psp_drm_patch9                              0x10B94
	#define psp_drm_patch11                             0x10B98
	#define psp_drm_patch12                             0x10BA8
	#define psp_product_id_patch1                       0x10CA8
	#define psp_product_id_patch3                       0x10F80

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6B0
	#define psp_prx_patch                               0x577CC
	#define psp_savedata_bind_patch1                    0x7A4B0
	#define psp_savedata_bind_patch2                    0x7A508
	#define psp_savedata_bind_patch3                    0x7A024
	#define psp_extra_savedata_patch                    0x87520
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x58920

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46CC
	#define psp_savedata_patch2                         0x46A4
	#define psp_savedata_patch3                         0x4504
	#define psp_savedata_patch4                         0x453C
	#define psp_savedata_patch5                         0x4550
	#define psp_savedata_patch6                         0x46B8

	/* libfs */
	#define aio_copy_root_offset                        0xD5B4

	/* rebug */
	#define EXPLORE_PLUGIN_REBUG_HASH                   0xACF4AF2B000ED19E
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH            0x9CB3CAF10005734A
	#define GAME_EXT_PLUGIN_REBUG_HASH                  0xE274AF7B0001DE56
	#define dex_ps2_nonbw_offset                        0xDEBC8
	#define dex_ps2_nonbw_offset2                       0x69A64
	#define dex_ps2_nonbw_offset3                       0x16AE8
	#define dex_ps2tonet_patch                          0xCA2C0
	#define dex_ps2tonet_size_patch                     0xCA2B4
	#define dex_vmode_patch_offset                      0x449D68
	#define dex_psp_drm_patch1                          0x245CD0
	#define dex_psp_drm_patch2                          0x246770
	#define dex_psp_drm_patch3                          0x2463AC
	#define dex_psp_drm_patch4                          0x246BB8
	#define dex_psp_drm_patchA                          0x245DEC
	#define dex_psp_drm_patchB                          0x24668C
	#define dex_psp_drm_patchC                          0x245824
	#define dex_psp_drm_patchD                          0x245DD4
	#define dex_psp_drm_patchE                          0x245DD8
	#define dex_psp_drm_patchF                          0x2467A4
	#define dex_psp_extra_drm_patch                     0x0
#endif

#ifdef FIRMWARE_441D

	#define FIRMWARE_VERSION                                 0x441

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x441
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003FA2B0ULL
		#define PS3MAPI_IDPS_2                               0x8000000000496F3CULL
		#define PS3MAPI_PSID                                 0x8000000000496F54ULL
	#endif

	/* lv2 */
	#define TOC                                              0x3665C0
	#define open_shared_kernel_object_symbol                 0x12ABC
	#define close_kernel_object_handle_symbol                0x120DC
	#define open_kernel_object_symbol                        0x12CAC
	#define alloc_symbol                                     0x66890
	#define dealloc_symbol                                   0x66CCC
	#define copy_to_user_symbol                              0xFEA4
	#define copy_from_user_symbol                            0x100C0
	#define copy_to_process_symbol                           0xFF5C
	#define copy_from_process_symbol                         0xFD6C
	#define page_allocate_symbol                             0x62400
	#define page_free_symbol                                 0x61E64
	#define page_export_to_proc_symbol                       0x6259C
	#define page_unexport_from_proc_symbol                   0x61D58
	#define kernel_ea_to_lpar_addr_symbol                    0x72304
	#define map_process_memory_symbol                        0x799B0
	#define memcpy_symbol                                    0x81070
	#define memset_symbol                                    0x50D84
	#define memcmp_symbol                                    0x50094
	#define printf_symbol                                    0x2A8520
	#define printfnull_symbol                                0x2ACFA4
	#define sprintf_symbol                                   0x521AC
	#define snprintf_symbol                                  0x52118
	#define strcpy_symbol                                    0x50F30
	#define strncpy_symbol                                   0x50FF8
	#define strlen_symbol                                    0x50F58
	#define strcat_symbol                                    0x50E60
	#define strcmp_symbol                                    0x50EDC
	#define strncmp_symbol                                   0x50F84
	#define strchr_symbol                                    0x50E98
	#define spin_lock_irqsave_ex_symbol                      0x2A522C
	#define spin_unlock_irqrestore_ex_symbol                 0x2A5200
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x145A8
	#define ppu_thread_exit_symbol                           0x14660
	#define ppu_thread_join_symbol                           0x146B4
	#define ppu_thread_delay_symbol                          0x2A458
	#define create_user_thread2_symbol                       0x26AA8
	#define start_thread_symbol                              0x255E0
	#define run_thread_symbol                                0x24DA4
	#define register_thread_symbol                           0x29DE54
	#define allocate_user_stack_symbol                       0x29E63C
	#define mutex_create_symbol                              0x13CF0
	#define mutex_destroy_symbol                             0x13C88
	#define mutex_lock_symbol                                0x13C80
	#define mutex_unlock_symbol                              0x13C78
	#define event_port_create_symbol                         0x1372C
	#define event_port_destroy_symbol                        0x13B94
	#define event_port_connect_symbol                        0x13C0C
	#define event_port_disconnect_symbol                     0x13B38
	#define event_port_send_symbol                           0x13724
	#define event_queue_create_symbol                        0x13A34
	#define event_queue_destroy_symbol                       0x139BC
	#define event_queue_receive_symbol                       0x13800
	#define cellFsOpen_symbol                                0x2DBA04
	#define cellFsClose_symbol                               0x2DB86C
	#define cellFsRead_symbol                                0x2DB9A8
	#define cellFsWrite_symbol                               0x2DB914
	#define cellFsLseek_symbol                               0x2DB168
	#define cellFsStat_symbol                                0x2DB220
	#define cellFsUnlink_internal_symbol                     0x1B0FE4
	#define cellFsUtilMount_symbol                           0x2DAEDC
	#define cellFsUtilUmount_symbol                          0x2DAEB0
	#define pathdup_from_user_symbol                         0x1B7190
	#define open_path_symbol                                 0x2DB73C
	#define open_fs_object_symbol                            0x19667C
	#define close_fs_object_symbol                           0x19564C
	#define storage_get_device_info_symbol                   0x2BC338
	#define storage_open_symbol                              0x2BC560
	#define storage_close_symbol                             0x2BAD4C
	#define storage_read_symbol                              0x2B9F34
	#define storage_send_device_command_symbol               0x2B9A54
	#define storage_map_io_memory_symbol                     0x2BC1E4
	#define storage_unmap_io_memory_symbol                   0x2BC0A0
	#define storage_internal_get_device_object_symbol        0x2B950C
	#define decrypt_func_symbol                              0x38000
	#define lv1_call_99_wrapper_symbol                       0x525C0
	#define modules_verification_symbol                      0x5C140
	#define prx_load_module_symbol                           0x8B880
	#define prx_start_module_symbol                          0x8A54C
	#define prx_stop_module_symbol                           0x8B924
	#define prx_unload_module_symbol                         0x8A280
	#define prx_get_module_info_symbol                       0x89C78
	#define prx_get_module_list_symbol                       0x89CF8
	#define extend_kstack_symbol                             0x7225C
	#define get_pseudo_random_number_symbol                  0x25E69C
	#define syscall_table_symbol                             0x37C9E8
	#define syscall_call_offset                              0x2ADA88
	#define read_bdvd0_symbol                                0x1C2100
	#define read_bdvd1_symbol                                0x1C3D2C
	#define read_bdvd2_symbol                                0x1D0EE4
	#define device_event_port_send_call                      0x2C64FC
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x2DBB9C
	#define fsloop_close_call                                0x2DBBEC
	#define fsloop_read_call                                 0x2DBC2C
	#define io_rtoc_entry_1                                 -0x20
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65A8
	#define storage_rtoc_entry_1                             0x2370
	#define device_event_rtoc_entry_1                        0x26F8
	#define process_rtoc_entry_1                            -0x77A0
	#define patch_func2                                      0x5CAF8
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x21C24
	#define user_thread_prio_patch2                          0x21C30
	#define shutdown_patch_offset                            0xAB28
	#define shutdown_copy_params_call                        0xAB3C

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000ED19E
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB3CAF10005734A
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001DE56
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BEC800006430
	#define PSP_EMULATOR_HASH                           0x7BE6413100023721
	#define PEMUCORELIB_HASH                            0xF349A563000C0A38
	#define EMULATOR_API_HASH                           0xA9F5B55A0001B7C2
	#define EMULATOR_DRM_HASH                           0xA324DC4A0000539C
	#define EMULATOR_DRM_DATA_HASH                      0x1D8D2DA00001B6E4
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC3B800003212

	/* lv1 */
	#define vsh_pos_in_ram                              0x910000

	/* vsh */
	#define ps2tonet_patch                              0xCA2C0
	#define ps2tonet_size_patch                         0xCA2B4
	#define vmode_patch_offset                          0x449D68
	#define psp_drm_patch1                              0x245CD0
	#define psp_drm_patch2                              0x246770
	#define psp_drm_patch3                              0x2463AC
	#define psp_drm_patch4                              0x246BB8
	#define psp_drm_patchA                              0x245DEC
	#define psp_drm_patchB                              0x24668C
	#define psp_drm_patchC                              0x245824
	#define psp_drm_patchD                              0x245DD4
	#define psp_drm_patchE                              0x245DD8
	#define psp_drm_patchF                              0x2467A4
	#define psp_extra_drm_patch                         0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDEBC8

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x69A64

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x16AE8

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1BF4

	/* emulator_api */
	#define psp_read                                    0xFC60
	#define psp_read_header                             0x10BE4
	#define psp_drm_patch5                              0x10A08
	#define psp_drm_patch6                              0x10A38
	#define psp_drm_patch7                              0x10A50
	#define psp_drm_patch8                              0x10A54
	#define psp_drm_patch9                              0x10B94
	#define psp_drm_patch11                             0x10B98
	#define psp_drm_patch12                             0x10BA8
	#define psp_product_id_patch1                       0x10CA8
	#define psp_product_id_patch3                       0x10F80

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6B0
	#define psp_prx_patch                               0x577CC
	#define psp_savedata_bind_patch1                    0x7A4B0
	#define psp_savedata_bind_patch2                    0x7A508
	#define psp_savedata_bind_patch3                    0x7A024
	#define psp_extra_savedata_patch                    0x87520
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x58920

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46CC
	#define psp_savedata_patch2                         0x46A4
	#define psp_savedata_patch3                         0x4504
	#define psp_savedata_patch4                         0x453C
	#define psp_savedata_patch5                         0x4550
	#define psp_savedata_patch6                         0x46B8

	/* libfs */
	#define aio_copy_root_offset                        0xD5B4

	/* CEX */
	#define cex_ps2tonet_patch                          0xC4D64
	#define cex_ps2tonet_size_patch                     0xC4D58
	#define cex_vmode_patch_offset                      0x442160
	#define cex_psp_drm_patch1                          0x23E494
	#define cex_psp_drm_patch2                          0x23EF34
	#define cex_psp_drm_patch3                          0x23EB70
	#define cex_psp_drm_patch4                          0x23F37C
	#define cex_psp_drm_patchA                          0x23E5B0
	#define cex_psp_drm_patchB                          0x23EE50
	#define cex_psp_drm_patchC                          0x23DFE8
	#define cex_psp_drm_patchD                          0x23E598
	#define cex_psp_drm_patchE                          0x23E59C
	#define cex_psp_drm_patchF                          0x23EF68
	#define cex_psp_extra_drm_patch                     0x0
#endif

#ifdef FIRMWARE_446C

	#define FIRMWARE_VERSION                                 0x446

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x446
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003DBE30ULL
		#define PS3MAPI_IDPS_2                               0x8000000000476F3CULL
		#define PS3MAPI_PSID                                 0x8000000000476F54ULL
	#endif

	/* lv2 */
	#define TOC                                              0x348DF0
	#define open_shared_kernel_object_symbol                 0x12474
	#define close_kernel_object_handle_symbol                0x11A94
	#define open_kernel_object_symbol                        0x12664
	#define alloc_symbol                                     0x62F78
	#define dealloc_symbol                                   0x633B4
	#define copy_to_user_symbol                              0xF85C
	#define copy_from_user_symbol                            0xFA78
	#define copy_to_process_symbol                           0xF914
	#define copy_from_process_symbol                         0xF724
	#define page_allocate_symbol                             0x5EAE8
	#define page_free_symbol                                 0x5E54C
	#define page_export_to_proc_symbol                       0x5EC84
	#define page_unexport_from_proc_symbol                   0x5E440
	#define kernel_ea_to_lpar_addr_symbol                    0x6E86C
	#define map_process_memory_symbol                        0x7598C
	#define memcpy_symbol                                    0x7D04C
	#define memset_symbol                                    0x4D494
	#define memcmp_symbol                                    0x4C7A4
	#define printf_symbol                                    0x2A0800
	#define printfnull_symbol                                0x2A5270
	#define sprintf_symbol                                   0x4E8BC
	#define snprintf_symbol                                  0x4E828
	#define strcpy_symbol                                    0x4D640
	#define strncpy_symbol                                   0x4D708
	#define strlen_symbol                                    0x4D668
	#define strcat_symbol                                    0x4D570
	#define strcmp_symbol                                    0x4D5EC
	#define strncmp_symbol                                   0x4D694
	#define strchr_symbol                                    0x4D5A8
	#define spin_lock_irqsave_ex_symbol                      0x29D900
	#define spin_unlock_irqrestore_ex_symbol                 0x29D8D4
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x13F2C
	#define ppu_thread_exit_symbol                           0x13FE4
	#define ppu_thread_join_symbol                           0x14038
	#define ppu_thread_delay_symbol                          0x285CC
	#define create_user_thread2_symbol                       0x24EB0
	#define start_thread_symbol                              0x23B7C
	#define run_thread_symbol                                0x233AC
	#define register_thread_symbol                           0x297B10
	#define allocate_user_stack_symbol                       0x2982F8
	#define mutex_create_symbol                              0x136A0
	#define mutex_destroy_symbol                             0x13638
	#define mutex_lock_symbol                                0x13630
	#define mutex_unlock_symbol                              0x13628
	#define event_port_create_symbol                         0x130DC
	#define event_port_destroy_symbol                        0x13544
	#define event_port_connect_symbol                        0x135BC
	#define event_port_disconnect_symbol                     0x134E8
	#define event_port_send_symbol                           0x130D4
	#define event_queue_create_symbol                        0x133E4
	#define event_queue_destroy_symbol                       0x1336C
	#define event_queue_receive_symbol                       0x131B0
	#define cellFsOpen_symbol                                0x2C4A78
	#define cellFsClose_symbol                               0x2C48E0
	#define cellFsRead_symbol                                0x2C4A1C
	#define cellFsWrite_symbol                               0x2C4988
	#define cellFsLseek_symbol                               0x2C4010
	#define cellFsStat_symbol                                0x2C4294
	#define cellFsUnlink_internal_symbol                     0x1AAF70
	#define cellFsUtilMount_symbol                           0x2C3DF0
	#define cellFsUtilUmount_symbol                          0x2C3DC4
	#define pathdup_from_user_symbol                         0x1B1000
	#define open_path_symbol                                 0x2C47B0
	#define open_fs_object_symbol                            0x190420
	#define close_fs_object_symbol                           0x18F41C
	#define storage_get_device_info_symbol                   0x2A9C50
	#define storage_open_symbol                              0x2A9660
	#define storage_close_symbol                             0x2A9450
	#define storage_read_symbol                              0x2A89C0
	#define storage_send_device_command_symbol               0x2A854C
	#define storage_map_io_memory_symbol                     0x2A9B0C
	#define storage_unmap_io_memory_symbol                   0x2A99D8
	#define storage_internal_get_device_object_symbol        0x2A8004
	#define decrypt_func_symbol                              0x34798
	#define lv1_call_99_wrapper_symbol                       0x4ECD0
	#define modules_verification_symbol                      0x58828
	#define prx_load_module_symbol                           0x87234
	#define prx_start_module_symbol                          0x85F00
	#define prx_stop_module_symbol                           0x872D8
	#define prx_unload_module_symbol                         0x85C34
	#define prx_get_module_info_symbol                       0x856BC
	#define prx_get_module_list_symbol                       0x8573C
	#define extend_kstack_symbol                             0x6E7C4
	#define get_pseudo_random_number_symbol                  0x2587A0
	#define syscall_table_symbol                             0x35E860
	#define syscall_call_offset                              0x2A5D54
	#define read_bdvd0_symbol                                0x1BBF70
	#define read_bdvd1_symbol                                0x1BDB9C
	#define read_bdvd2_symbol                                0x1CAD54
	#define device_event_port_send_call                      0x2B2184
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x2C4C10
	#define fsloop_close_call                                0x2C4C60
	#define fsloop_read_call                                 0x2C4CA0
	#define io_rtoc_entry_1                                 -0x150
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x6688
	#define storage_rtoc_entry_1                             0x1E98
	#define device_event_rtoc_entry_1                        0x2108
	#define process_rtoc_entry_1                            -0x7800
	#define patch_func2                                      0x591E0
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x2022C
	#define user_thread_prio_patch2                          0x20238
	#define shutdown_patch_offset                            0xAAA8
	#define shutdown_copy_params_call                        0xAABC

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000EC8A6
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB3C7F100056FAA
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001DDFD
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BEC800006433
	#define PSP_EMULATOR_HASH                           0x7BE645A900023721
	#define PEMUCORELIB_HASH                            0xF349A563000C0CF3
	#define EMULATOR_API_HASH                           0xA9F5B55A0001B7C2
	#define EMULATOR_DRM_HASH                           0xA324DC4A0000539C
	#define EMULATOR_DRM_DATA_HASH                      0x1D8D2DA00001B6E4
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC3B800003212

	/* lv1 */
	#define vsh_pos_in_ram                              0x910000

	/* vsh */
	#define ps2tonet_patch                              0xC4D64
	#define ps2tonet_size_patch                         0xC4D58
	#define vmode_patch_offset                          0x442D68
	#define psp_drm_patch1                              0x23EEF8
	#define psp_drm_patch2                              0x23F998
	#define psp_drm_patch3                              0x23F5D4
	#define psp_drm_patch4                              0x23FDE0
	#define psp_drm_patchA                              0x23F014
	#define psp_drm_patchB                              0x23F8B4
	#define psp_drm_patchC                              0x23EA4C
	#define psp_drm_patchD                              0x23EFFC
	#define psp_drm_patchE                              0x23F000
	#define psp_drm_patchF                              0x23F9CC
	#define psp_extra_drm_patch                         0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDE81C

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x69D28

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x167F8

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1BF8

	/* emulator_api */
	#define psp_read                                    0xFC60
	#define psp_read_header                             0x10BE4
	#define psp_drm_patch5                              0x10A08
	#define psp_drm_patch6                              0x10A38
	#define psp_drm_patch7                              0x10A50
	#define psp_drm_patch8                              0x10A54
	#define psp_drm_patch9                              0x10B94
	#define psp_drm_patch11                             0x10B98
	#define psp_drm_patch12                             0x10BA8
	#define psp_product_id_patch1                       0x10CA8
	#define psp_product_id_patch3                       0x10F80

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6B0
	#define psp_prx_patch                               0x577CC
	#define psp_savedata_bind_patch1                    0x7A4B0
	#define psp_savedata_bind_patch2                    0x7A508
	#define psp_savedata_bind_patch3                    0x7A024
	#define psp_extra_savedata_patch                    0x87530
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x58920

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46CC
	#define psp_savedata_patch2                         0x46A4
	#define psp_savedata_patch3                         0x4504
	#define psp_savedata_patch4                         0x453C
	#define psp_savedata_patch5                         0x4550
	#define psp_savedata_patch6                         0x46B8

	/* libfs */
	#define aio_copy_root_offset                        0xD5B4

	/* rebug */
	#define EXPLORE_PLUGIN_REBUG_HASH                   0xACF4AF2B000ED168
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH            0x9CB3CAFD000572DD
	#define GAME_EXT_PLUGIN_REBUG_HASH                  0xE274AF7B0001DE6B
	#define dex_ps2_nonbw_offset                        0xDEC48
	#define dex_ps2_nonbw_offset2                       0x69A5C
	#define dex_ps2_nonbw_offset3                       0x16AE8
	#define dex_ps2tonet_patch                          0xCA2C0
	#define dex_ps2tonet_size_patch                     0xCA2B4
	#define dex_vmode_patch_offset                      0x44A970
	#define dex_psp_drm_patch1                          0x246734
	#define dex_psp_drm_patch2                          0x2471D4
	#define dex_psp_drm_patch3                          0x246E10
	#define dex_psp_drm_patch4                          0x24761C
	#define dex_psp_drm_patchA                          0x246850
	#define dex_psp_drm_patchB                          0x2470F0
	#define dex_psp_drm_patchC                          0x246288
	#define dex_psp_drm_patchD                          0x246838
	#define dex_psp_drm_patchE                          0x24683C
	#define dex_psp_drm_patchF                          0x247208
	#define dex_psp_extra_drm_patch                     0x0
#endif

#ifdef FIRMWARE_446D

	#define FIRMWARE_VERSION                                 0x446

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x446
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003FA8B0ULL
		#define PS3MAPI_IDPS_2                               0x8000000000496F3CULL
		#define PS3MAPI_PSID                                 0x8000000000496F54ULL
	#endif

	/* lv2 */
	#define TOC                                              0x366BD0
	#define open_shared_kernel_object_symbol                 0x12ABC
	#define close_kernel_object_handle_symbol                0x120DC
	#define open_kernel_object_symbol                        0x12CAC
	#define alloc_symbol                                     0x66890
	#define dealloc_symbol                                   0x66CCC
	#define copy_to_user_symbol                              0xFEA4
	#define copy_from_user_symbol                            0x100C0
	#define copy_to_process_symbol                           0xFF5C
	#define copy_from_process_symbol                         0xFD6C
	#define page_allocate_symbol                             0x62400
	#define page_free_symbol                                 0x61E64
	#define page_export_to_proc_symbol                       0x6259C
	#define page_unexport_from_proc_symbol                   0x61D58
	#define kernel_ea_to_lpar_addr_symbol                    0x72304
	#define map_process_memory_symbol                        0x799B0
	#define memcpy_symbol                                    0x81070
	#define memset_symbol                                    0x50D84
	#define memcmp_symbol                                    0x50094
	#define printf_symbol                                    0x2A8A40
	#define printfnull_symbol                                0x2AD4C4
	#define sprintf_symbol                                   0x521AC
	#define snprintf_symbol                                  0x52118
	#define strcpy_symbol                                    0x50F30
	#define strncpy_symbol                                   0x50FF8
	#define strlen_symbol                                    0x50F58
	#define strcat_symbol                                    0x50E60
	#define strcmp_symbol                                    0x50EDC
	#define strncmp_symbol                                   0x50F84
	#define strchr_symbol                                    0x50E98
	#define spin_lock_irqsave_ex_symbol                      0x2A574C
	#define spin_unlock_irqrestore_ex_symbol                 0x2A5720
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x145A8
	#define ppu_thread_exit_symbol                           0x14660
	#define ppu_thread_join_symbol                           0x146B4
	#define ppu_thread_delay_symbol                          0x2A458
	#define create_user_thread2_symbol                       0x26AA8
	#define start_thread_symbol                              0x255E0
	#define run_thread_symbol                                0x24DA4
	#define register_thread_symbol                           0x29E374
	#define allocate_user_stack_symbol                       0x29EB5C
	#define mutex_create_symbol                              0x13CF0
	#define mutex_destroy_symbol                             0x13C88
	#define mutex_lock_symbol                                0x13C80
	#define mutex_unlock_symbol                              0x13C78
	#define event_port_create_symbol                         0x1372C
	#define event_port_destroy_symbol                        0x13B94
	#define event_port_connect_symbol                        0x13C0C
	#define event_port_disconnect_symbol                     0x13B38
	#define event_port_send_symbol                           0x13724
	#define event_queue_create_symbol                        0x13A34
	#define event_queue_destroy_symbol                       0x139BC
	#define event_queue_receive_symbol                       0x13800
	#define cellFsOpen_symbol                                0x2DBF24
	#define cellFsClose_symbol                               0x2DBD8C
	#define cellFsRead_symbol                                0x2DBEC8
	#define cellFsWrite_symbol                               0x2DBE34
	#define cellFsLseek_symbol                               0x2DB688
	#define cellFsStat_symbol                                0x2DB740
	#define cellFsUnlink_internal_symbol                     0x1B1244
	#define cellFsUtilMount_symbol                           0x2DB3FC
	#define cellFsUtilUmount_symbol                          0x2DB3D0
	#define pathdup_from_user_symbol                         0x1B73F0
	#define open_path_symbol                                 0x2DBC5C
	#define open_fs_object_symbol                            0x1966F4
	#define close_fs_object_symbol                           0x1956F0
	#define storage_get_device_info_symbol                   0x2BC858
	#define storage_open_symbol                              0x2BCA80
	#define storage_close_symbol                             0x2BB26C
	#define storage_read_symbol                              0x2BA454
	#define storage_send_device_command_symbol               0x2B9F74
	#define storage_map_io_memory_symbol                     0x2BC704
	#define storage_unmap_io_memory_symbol                   0x2BC5C0
	#define storage_internal_get_device_object_symbol        0x2B9A2C
	#define decrypt_func_symbol                              0x38000
	#define lv1_call_99_wrapper_symbol                       0x525C0
	#define modules_verification_symbol                      0x5C140
	#define prx_load_module_symbol                           0x8B880
	#define prx_start_module_symbol                          0x8A54C
	#define prx_stop_module_symbol                           0x8B924
	#define prx_unload_module_symbol                         0x8A280
	#define prx_get_module_info_symbol                       0x89C78
	#define prx_get_module_list_symbol                       0x89CF8
	#define extend_kstack_symbol                             0x7225C
	#define get_pseudo_random_number_symbol                  0x25EBBC
	#define syscall_table_symbol                             0x37CFE8
	#define syscall_call_offset                              0x2ADFA8
	#define read_bdvd0_symbol                                0x1C2360
	#define read_bdvd1_symbol                                0x1C3F8C
	#define read_bdvd2_symbol                                0x1D1144
	#define device_event_port_send_call                      0x2C6A1C
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x2DC0BC
	#define fsloop_close_call                                0x2DC10C
	#define fsloop_read_call                                 0x2DC14C
	#define io_rtoc_entry_1                                 -0x20
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65A8
	#define storage_rtoc_entry_1                             0x2370
	#define device_event_rtoc_entry_1                        0x26F8
	#define process_rtoc_entry_1                            -0x77A0
	#define patch_func2                                      0x5CAF8
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x21C24
	#define user_thread_prio_patch2                          0x21C30
	#define shutdown_patch_offset                            0xAB28
	#define shutdown_copy_params_call                        0xAB3C

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000ED168
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB3CAFD000572DD
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001DE6B
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BEC800006433
	#define PSP_EMULATOR_HASH                           0x7BE645A900023721
	#define PEMUCORELIB_HASH                            0xF349A563000C0CF3
	#define EMULATOR_API_HASH                           0xA9F5B55A0001B7C2
	#define EMULATOR_DRM_HASH                           0xA324DC4A0000539C
	#define EMULATOR_DRM_DATA_HASH                      0x1D8D2DA00001B6E4
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC3B800003212

	/* lv1 */
	#define vsh_pos_in_ram                              0x910000

	/* vsh */
	#define ps2tonet_patch                              0xCA2C0
	#define ps2tonet_size_patch                         0xCA2B4
	#define vmode_patch_offset                          0x44A970
	#define psp_drm_patch1                              0x246734
	#define psp_drm_patch2                              0x2471D4
	#define psp_drm_patch3                              0x246E10
	#define psp_drm_patch4                              0x24761C
	#define psp_drm_patchA                              0x246850
	#define psp_drm_patchB                              0x2470F0
	#define psp_drm_patchC                              0x246288
	#define psp_drm_patchD                              0x246838
	#define psp_drm_patchE                              0x24683C
	#define psp_drm_patchF                              0x247208
	#define psp_extra_drm_patch                         0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDEC48

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x69A5C

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x16AE8

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1BF8

	/* emulator_api */
	#define psp_read                                    0xFC60
	#define psp_read_header                             0x10BE4
	#define psp_drm_patch5                              0x10A08
	#define psp_drm_patch6                              0x10A38
	#define psp_drm_patch7                              0x10A50
	#define psp_drm_patch8                              0x10A54
	#define psp_drm_patch9                              0x10B94
	#define psp_drm_patch11                             0x10B98
	#define psp_drm_patch12                             0x10BA8
	#define psp_product_id_patch1                       0x10CA8
	#define psp_product_id_patch3                       0x10F80

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6B0
	#define psp_prx_patch                               0x577CC
	#define psp_savedata_bind_patch1                    0x7A4B0
	#define psp_savedata_bind_patch2                    0x7A508
	#define psp_savedata_bind_patch3                    0x7A024
	#define psp_extra_savedata_patch                    0x87530
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x58920

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46CC
	#define psp_savedata_patch2                         0x46A4
	#define psp_savedata_patch3                         0x4504
	#define psp_savedata_patch4                         0x453C
	#define psp_savedata_patch5                         0x4550
	#define psp_savedata_patch6                         0x46B8

	/* libfs */
	#define aio_copy_root_offset                        0xD5B4

	/* CEX */
	#define cex_ps2tonet_patch                          0xC4D64
	#define cex_ps2tonet_size_patch                     0xC4D58
	#define cex_vmode_patch_offset                      0x442D68
	#define cex_psp_drm_patch1                          0x23EEF8
	#define cex_psp_drm_patch2                          0x23F998
	#define cex_psp_drm_patch3                          0x23F5D4
	#define cex_psp_drm_patch4                          0x23FDE0
	#define cex_psp_drm_patchA                          0x23F014
	#define cex_psp_drm_patchB                          0x23F8B4
	#define cex_psp_drm_patchC                          0x23EA4C
	#define cex_psp_drm_patchD                          0x23EFFC
	#define cex_psp_drm_patchE                          0x23F000
	#define cex_psp_drm_patchF                          0x23F9CC
	#define cex_psp_extra_drm_patch                     0x0
#endif

#ifdef FIRMWARE_450C

	#define FIRMWARE_VERSION                                 0x450

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x450
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003DE230ULL
		#define PS3MAPI_IDPS_2                               0x800000000046CF0CULL
		#define PS3MAPI_PSID                                 0x800000000046CF24ULL
	#endif

	/* lv2 */
	#define TOC                                              0x34B160
	#define open_shared_kernel_object_symbol                 0x12470
	#define close_kernel_object_handle_symbol                0x11A90
	#define open_kernel_object_symbol                        0x12660
	#define alloc_symbol                                     0x62F74
	#define dealloc_symbol                                   0x633B0
	#define copy_to_user_symbol                              0xF858
	#define copy_from_user_symbol                            0xFA74
	#define copy_to_process_symbol                           0xF910
	#define copy_from_process_symbol                         0xF720
	#define page_allocate_symbol                             0x5EAE4
	#define page_free_symbol                                 0x5E548
	#define page_export_to_proc_symbol                       0x5EC80
	#define page_unexport_from_proc_symbol                   0x5E43C
	#define kernel_ea_to_lpar_addr_symbol                    0x6E868
	#define map_process_memory_symbol                        0x75988
	#define memcpy_symbol                                    0x7D048
	#define memset_symbol                                    0x4D490
	#define memcmp_symbol                                    0x4C7A0
	#define printf_symbol                                    0x278B08
	#define printfnull_symbol                                0x27D578
	#define sprintf_symbol                                   0x4E8B8
	#define snprintf_symbol                                  0x4E824
	#define strcpy_symbol                                    0x4D63C
	#define strncpy_symbol                                   0x4D704
	#define strlen_symbol                                    0x4D664
	#define strcat_symbol                                    0x4D56C
	#define strcmp_symbol                                    0x4D5E8
	#define strncmp_symbol                                   0x4D690
	#define strchr_symbol                                    0x4D5A4
	#define spin_lock_irqsave_ex_symbol                      0x275C08
	#define spin_unlock_irqrestore_ex_symbol                 0x275BDC
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x13F28
	#define ppu_thread_exit_symbol                           0x13FE0
	#define ppu_thread_join_symbol                           0x14034
	#define ppu_thread_delay_symbol                          0x285C8
	#define create_user_thread2_symbol                       0x24EAC
	#define start_thread_symbol                              0x23B78
	#define run_thread_symbol                                0x233A8
	#define register_thread_symbol                           0x26FE18
	#define allocate_user_stack_symbol                       0x270600
	#define mutex_create_symbol                              0x1369C
	#define mutex_destroy_symbol                             0x13634
	#define mutex_lock_symbol                                0x1362C
	#define mutex_unlock_symbol                              0x13624
	#define event_port_create_symbol                         0x130D8
	#define event_port_destroy_symbol                        0x13540
	#define event_port_connect_symbol                        0x135B8
	#define event_port_disconnect_symbol                     0x134E4
	#define event_port_send_symbol                           0x130D0
	#define event_queue_create_symbol                        0x133E0
	#define event_queue_destroy_symbol                       0x13368
	#define event_queue_receive_symbol                       0x131AC
	#define cellFsOpen_symbol                                0x29DFE8
	#define cellFsClose_symbol                               0x29DE50
	#define cellFsRead_symbol                                0x29DF8C
	#define cellFsWrite_symbol                               0x29DEF8
	#define cellFsLseek_symbol                               0x29D580
	#define cellFsStat_symbol                                0x29D804
	#define cellFsUnlink_internal_symbol                     0x19BFA4
	#define cellFsUtilMount_symbol                           0x29D360
	#define cellFsUtilUmount_symbol                          0x29D334
	#define pathdup_from_user_symbol                         0x1A20DC
	#define open_path_symbol                                 0x2E9C48
	#define open_fs_object_symbol                            0x18A6DC
	#define close_fs_object_symbol                           0x189618
	#define storage_get_device_info_symbol                   0x281F58
	#define storage_open_symbol                              0x281968
	#define storage_close_symbol                             0x281758
	#define storage_read_symbol                              0x280CC8
	#define storage_send_device_command_symbol               0x280854
	#define storage_map_io_memory_symbol                     0x281E14
	#define storage_unmap_io_memory_symbol                   0x281CE0
	#define storage_internal_get_device_object_symbol        0x28030C
	#define decrypt_func_symbol                              0x34794
	#define lv1_call_99_wrapper_symbol                       0x4ECCC
	#define modules_verification_symbol                      0x58824
	#define prx_load_module_symbol                           0x87230
	#define prx_start_module_symbol                          0x85EFC
	#define prx_stop_module_symbol                           0x872D4
	#define prx_unload_module_symbol                         0x85C30
	#define prx_get_module_info_symbol                       0x856B8
	#define prx_get_module_list_symbol                       0x85738
	#define extend_kstack_symbol                             0x6E7C0
	#define get_pseudo_random_number_symbol                  0x230930
	#define syscall_table_symbol                             0x35F0D0
	#define syscall_call_offset                              0x27E05C
	#define read_bdvd0_symbol                                0x1AD04C
	#define read_bdvd1_symbol                                0x1AEC78
	#define read_bdvd2_symbol                                0x1BBE00
	#define device_event_port_send_call                      0x28A4C4
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x29E180
	#define fsloop_close_call                                0x29E1D0
	#define fsloop_read_call                                 0x29E210
	#define io_rtoc_entry_1                                 -0x1E8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x6688
	#define storage_rtoc_entry_1                             0x1DC8
	#define device_event_rtoc_entry_1                        0x2038
	#define process_rtoc_entry_1                            -0x7800
	#define patch_func2                                      0x591DC
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x20228
	#define user_thread_prio_patch2                          0x20234
	#define shutdown_patch_offset                            0xAAA8
	#define shutdown_copy_params_call                        0xAABC

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000EC573
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB3259A00056DB7
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001E2A0
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BCE800006477
	#define PSP_EMULATOR_HASH                           0x7BE641F500023793
	#define PEMUCORELIB_HASH                            0xF349A563000C0D00
	#define EMULATOR_API_HASH                           0xA9F5BC7A0001BAAC
	#define EMULATOR_DRM_HASH                           0xA324DC4A0000539C
	#define EMULATOR_DRM_DATA_HASH                      0x1D8D2DA00001B6E4
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC04800003207

	/* lv1 */
	#define vsh_pos_in_ram                              0x910000

	/* vsh */
	#define ps2tonet_patch                              0xC4C40
	#define ps2tonet_size_patch                         0xC4C34
	#define vmode_patch_offset                          0x441F78
	#define psp_drm_patch1                              0x240650
	#define psp_drm_patch2                              0x2410F0
	#define psp_drm_patch3                              0x240D2C
	#define psp_drm_patch4                              0x241538
	#define psp_drm_patchA                              0x24076C
	#define psp_drm_patchB                              0x24100C
	#define psp_drm_patchC                              0x2401A4
	#define psp_drm_patchD                              0x240754
	#define psp_drm_patchE                              0x240758
	#define psp_drm_patchF                              0x241124
	#define psp_extra_drm_patch                         0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDD8F0

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x685CC

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x16814

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1C18

	/* emulator_api */
	#define psp_read                                    0x10198
	#define psp_read_header                             0x1111C
	#define psp_drm_patch5                              0x10F40
	#define psp_drm_patch6                              0x10F70
	#define psp_drm_patch7                              0x10F88
	#define psp_drm_patch8                              0x10F8C
	#define psp_drm_patch9                              0x110CC
	#define psp_drm_patch11                             0x110D0
	#define psp_drm_patch12                             0x110E0
	#define psp_product_id_patch1                       0x111E0
	#define psp_product_id_patch3                       0x114B8

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6BC
	#define psp_prx_patch                               0x577D8
	#define psp_savedata_bind_patch1                    0x7A4BC
	#define psp_savedata_bind_patch2                    0x7A514
	#define psp_savedata_bind_patch3                    0x7A030
	#define psp_extra_savedata_patch                    0x8753C
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46D4
	#define psp_savedata_patch2                         0x46AC
	#define psp_savedata_patch3                         0x450C
	#define psp_savedata_patch4                         0x4544
	#define psp_savedata_patch5                         0x4558
	#define psp_savedata_patch6                         0x46C0

	/* libfs */
	#define aio_copy_root_offset                        0xD658

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                   0xACF4AF2B000ECDF3
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH            0x9CB333060005707B
	#define GAME_EXT_PLUGIN_REBUG_HASH                  0xE274AF7B0001E2BA
	#define dex_ps2_nonbw_offset                        0xDDD18
	#define dex_ps2_nonbw_offset2                       0x682F0
	#define dex_ps2_nonbw_offset3                       0x16B04
	#define dex_ps2tonet_patch                          0xCA18C
	#define dex_ps2tonet_size_patch                     0xCA180
	#define dex_vmode_patch_offset                      0x449B6C
	#define dex_psp_drm_patch1                          0x247E78
	#define dex_psp_drm_patch2                          0x248918
	#define dex_psp_drm_patch3                          0x248554
	#define dex_psp_drm_patch4                          0x248D60
	#define dex_psp_drm_patchA                          0x247F94
	#define dex_psp_drm_patchB                          0x248834
	#define dex_psp_drm_patchC                          0x2479CC
	#define dex_psp_drm_patchD                          0x247F7C
	#define dex_psp_drm_patchE                          0x247F80
	#define dex_psp_drm_patchF                          0x24894C
	#define dex_psp_extra_drm_patch                     0x0
#endif

#ifdef FIRMWARE_450D

	#define FIRMWARE_VERSION                                 0x450

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x450
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x8000000000402AB0ULL
		#define PS3MAPI_IDPS_2                               0x8000000000494F0CULL
		#define PS3MAPI_PSID                                 0x8000000000494F24ULL
	#endif

	/* lv2 */
	#define TOC                                              0x36EC40
	#define open_shared_kernel_object_symbol                 0x12AB8
	#define close_kernel_object_handle_symbol                0x120D8
	#define open_kernel_object_symbol                        0x12CA8
	#define alloc_symbol                                     0x66944
	#define dealloc_symbol                                   0x66D80
	#define copy_to_user_symbol                              0xFEA0
	#define copy_from_user_symbol                            0x100BC
	#define copy_to_process_symbol                           0xFF58
	#define copy_from_process_symbol                         0xFD68
	#define page_allocate_symbol                             0x624B4
	#define page_free_symbol                                 0x61F18
	#define page_export_to_proc_symbol                       0x62650
	#define page_unexport_from_proc_symbol                   0x61E0C
	#define kernel_ea_to_lpar_addr_symbol                    0x723B8
	#define map_process_memory_symbol                        0x79A64
	#define memcpy_symbol                                    0x81124
	#define memset_symbol                                    0x50E38
	#define memcmp_symbol                                    0x50148
	#define printf_symbol                                    0x280E08
	#define printfnull_symbol                                0x28588C
	#define sprintf_symbol                                   0x52260
	#define snprintf_symbol                                  0x521CC
	#define strcpy_symbol                                    0x50FE4
	#define strncpy_symbol                                   0x510AC
	#define strlen_symbol                                    0x5100C
	#define strcat_symbol                                    0x50F14
	#define strcmp_symbol                                    0x50F90
	#define strncmp_symbol                                   0x51038
	#define strchr_symbol                                    0x50F4C
	#define spin_lock_irqsave_ex_symbol                      0x27DB14
	#define spin_unlock_irqrestore_ex_symbol                 0x27DAE8
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x1465C
	#define ppu_thread_exit_symbol                           0x14714
	#define ppu_thread_join_symbol                           0x14768
	#define ppu_thread_delay_symbol                          0x2A50C
	#define create_user_thread2_symbol                       0x26B5C
	#define start_thread_symbol                              0x25694
	#define run_thread_symbol                                0x24E58
	#define register_thread_symbol                           0x27673C
	#define allocate_user_stack_symbol                       0x276F24
	#define mutex_create_symbol                              0x13CEC
	#define mutex_destroy_symbol                             0x13C84
	#define mutex_lock_symbol                                0x13C7C
	#define mutex_unlock_symbol                              0x13C74
	#define event_port_create_symbol                         0x13728
	#define event_port_destroy_symbol                        0x13B90
	#define event_port_connect_symbol                        0x13C08
	#define event_port_disconnect_symbol                     0x13B34
	#define event_port_send_symbol                           0x13720
	#define event_queue_create_symbol                        0x13A30
	#define event_queue_destroy_symbol                       0x139B8
	#define event_queue_receive_symbol                       0x137FC
	#define cellFsOpen_symbol                                0x2B84B0
	#define cellFsClose_symbol                               0x2B8318
	#define cellFsRead_symbol                                0x2B8454
	#define cellFsWrite_symbol                               0x2B83C0
	#define cellFsLseek_symbol                               0x2B7C14
	#define cellFsStat_symbol                                0x2B7CCC
	#define cellFsUnlink_internal_symbol                     0x1A2330
	#define cellFsUtilMount_symbol                           0x2B7988
	#define cellFsUtilUmount_symbol                          0x2B795C
	#define pathdup_from_user_symbol                         0x1A858C
	#define open_path_symbol                                 0x2B81E8
	#define open_fs_object_symbol                            0x190A68
	#define close_fs_object_symbol                           0x18F9A4
	#define storage_get_device_info_symbol                   0x294E8C
	#define storage_open_symbol                              0x2950B4
	#define storage_close_symbol                             0x2938A0
	#define storage_read_symbol                              0x29281C
	#define storage_send_device_command_symbol               0x29233C
	#define storage_map_io_memory_symbol                     0x294D38
	#define storage_unmap_io_memory_symbol                   0x294BF4
	#define storage_internal_get_device_object_symbol        0x291DF4
	#define decrypt_func_symbol                              0x380B4
	#define lv1_call_99_wrapper_symbol                       0x52674
	#define modules_verification_symbol                      0x5C1F4
	#define prx_load_module_symbol                           0x8B934
	#define prx_start_module_symbol                          0x8A600
	#define prx_stop_module_symbol                           0x8B9D8
	#define prx_unload_module_symbol                         0x8A334
	#define prx_get_module_info_symbol                       0x89D2C
	#define prx_get_module_list_symbol                       0x89DAC
	#define extend_kstack_symbol                             0x72310
	#define get_pseudo_random_number_symbol                  0x236E0C
	#define syscall_table_symbol                             0x383658
	#define syscall_call_offset                              0x286370
	#define read_bdvd0_symbol                                0x1B34FC
	#define read_bdvd1_symbol                                0x1B5128
	#define read_bdvd2_symbol                                0x1C22B0
	#define device_event_port_send_call                      0x29F088
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x2B8648
	#define fsloop_close_call                                0x2B8698
	#define fsloop_read_call                                 0x2B86D8
	#define io_rtoc_entry_1                                 -0xB8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65A8
	#define storage_rtoc_entry_1                             0x22A0
	#define device_event_rtoc_entry_1                        0x2628
	#define process_rtoc_entry_1                            -0x77A0
	#define patch_func2                                      0x5CBAC
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x21CD8
	#define user_thread_prio_patch2                          0x21CE4
	#define shutdown_patch_offset                            0xAB28
	#define shutdown_copy_params_call                        0xAB3C

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000ECDF3
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB333060005707B
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001E2BA
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BCE800006477
	#define PSP_EMULATOR_HASH                           0x7BE641F500023793
	#define PEMUCORELIB_HASH                            0xF349A563000C0D00
	#define EMULATOR_API_HASH                           0xA9F5BC7A0001BAAC
	#define EMULATOR_DRM_HASH                           0xA324DC4A0000539C
	#define EMULATOR_DRM_DATA_HASH                      0x1D8D2DA00001B6E4
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC04800003207

	/* lv1 */
	#define vsh_pos_in_ram                              0x520000

	/* vsh */
	#define ps2tonet_patch                              0xCA18C
	#define ps2tonet_size_patch                         0xCA180
	#define vmode_patch_offset                          0x449B6C
	#define psp_drm_patch1                              0x247E78
	#define psp_drm_patch2                              0x248918
	#define psp_drm_patch3                              0x248554
	#define psp_drm_patch4                              0x248D60
	#define psp_drm_patchA                              0x247F94
	#define psp_drm_patchB                              0x248834
	#define psp_drm_patchC                              0x2479CC
	#define psp_drm_patchD                              0x247F7C
	#define psp_drm_patchE                              0x247F80
	#define psp_drm_patchF                              0x24894C
	#define psp_extra_drm_patch                         0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDDD18

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x682F0

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x16B04

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1C18

	/* emulator_api */
	#define psp_read                                    0x10198
	#define psp_read_header                             0x1111C
	#define psp_drm_patch5                              0x10F40
	#define psp_drm_patch6                              0x10F70
	#define psp_drm_patch7                              0x10F88
	#define psp_drm_patch8                              0x10F8C
	#define psp_drm_patch9                              0x110CC
	#define psp_drm_patch11                             0x110D0
	#define psp_drm_patch12                             0x110E0
	#define psp_product_id_patch1                       0x111E0
	#define psp_product_id_patch3                       0x114B8

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6BC
	#define psp_prx_patch                               0x577D8
	#define psp_savedata_bind_patch1                    0x7A4BC
	#define psp_savedata_bind_patch2                    0x7A514
	#define psp_savedata_bind_patch3                    0x7A030
	#define psp_extra_savedata_patch                    0x8753C
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46D4
	#define psp_savedata_patch2                         0x46AC
	#define psp_savedata_patch3                         0x450C
	#define psp_savedata_patch4                         0x4544
	#define psp_savedata_patch5                         0x4558
	#define psp_savedata_patch6                         0x46C0

	/* libfs */
	#define aio_copy_root_offset                        0xD658

	/* CEX */
	#define cex_ps2tonet_patch                          0xC4C40
	#define cex_ps2tonet_size_patch                     0xC4C34
	#define cex_vmode_patch_offset                      0x441F78
	#define cex_psp_drm_patch1                          0x240650
	#define cex_psp_drm_patch2                          0x2410F0
	#define cex_psp_drm_patch3                          0x240D2C
	#define cex_psp_drm_patch4                          0x241538
	#define cex_psp_drm_patchA                          0x24076C
	#define cex_psp_drm_patchB                          0x24100C
	#define cex_psp_drm_patchC                          0x2401A4
	#define cex_psp_drm_patchD                          0x240754
	#define cex_psp_drm_patchE                          0x240758
	#define cex_psp_drm_patchF                          0x241124
	#define cex_psp_extra_drm_patch                     0x0
#endif

#ifdef FIRMWARE_453C

	#define FIRMWARE_VERSION                                 0x453

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x453
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003DE430ULL
		#define PS3MAPI_IDPS_2                               0x800000000046CF0CULL
		#define PS3MAPI_PSID                                 0x800000000046CF24ULL
	#endif

	/* lv2 */
	#define TOC                                              0x34B2E0
	#define open_shared_kernel_object_symbol                 0x12474
	#define close_kernel_object_handle_symbol                0x11A94
	#define open_kernel_object_symbol                        0x12664
	#define alloc_symbol                                     0x62F78
	#define dealloc_symbol                                   0x633B4
	#define copy_to_user_symbol                              0xF85C
	#define copy_from_user_symbol                            0xFA78
	#define copy_to_process_symbol                           0xF914
	#define copy_from_process_symbol                         0xF724
	#define page_allocate_symbol                             0x5EAE8
	#define page_free_symbol                                 0x5E54C
	#define page_export_to_proc_symbol                       0x5EC84
	#define page_unexport_from_proc_symbol                   0x5E440
	#define kernel_ea_to_lpar_addr_symbol                    0x6E86C
	#define map_process_memory_symbol                        0x7598C
	#define memcpy_symbol                                    0x7D04C
	#define memset_symbol                                    0x4D494
	#define memcmp_symbol                                    0x4C7A4
	#define printf_symbol                                    0x278CE0
	#define printfnull_symbol                                0x27D750
	#define sprintf_symbol                                   0x4E8BC
	#define snprintf_symbol                                  0x4E828
	#define strcpy_symbol                                    0x4D640
	#define strncpy_symbol                                   0x4D708
	#define strlen_symbol                                    0x4D668
	#define strcat_symbol                                    0x4D570
	#define strcmp_symbol                                    0x4D5EC
	#define strncmp_symbol                                   0x4D694
	#define strchr_symbol                                    0x4D5A8
	#define spin_lock_irqsave_ex_symbol                      0x275DE0
	#define spin_unlock_irqrestore_ex_symbol                 0x275DB4
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x13F2C
	#define ppu_thread_exit_symbol                           0x13FE4
	#define ppu_thread_join_symbol                           0x14038
	#define ppu_thread_delay_symbol                          0x285CC
	#define create_user_thread2_symbol                       0x24EB0
	#define start_thread_symbol                              0x23B7C
	#define run_thread_symbol                                0x233AC
	#define register_thread_symbol                           0x26FFF0
	#define allocate_user_stack_symbol                       0x2707D8
	#define mutex_create_symbol                              0x136A0
	#define mutex_destroy_symbol                             0x13638
	#define mutex_lock_symbol                                0x13630
	#define mutex_unlock_symbol                              0x13628
	#define event_port_create_symbol                         0x130DC
	#define event_port_destroy_symbol                        0x13544
	#define event_port_connect_symbol                        0x135BC
	#define event_port_disconnect_symbol                     0x134E8
	#define event_port_send_symbol                           0x130D4
	#define event_queue_create_symbol                        0x133E4
	#define event_queue_destroy_symbol                       0x1336C
	#define event_queue_receive_symbol                       0x131B0
	#define cellFsOpen_symbol                                0x29E1C0
	#define cellFsClose_symbol                               0x29E028
	#define cellFsRead_symbol                                0x29E164
	#define cellFsWrite_symbol                               0x29E0D0
	#define cellFsLseek_symbol                               0x29D758
	#define cellFsStat_symbol                                0x29D9DC
	#define cellFsUnlink_internal_symbol                     0x19C350
	#define cellFsUtilMount_symbol                           0x29D538
	#define cellFsUtilUmount_symbol                          0x29D50C
	#define pathdup_from_user_symbol                         0x1A2244
	#define open_path_symbol                                 0x29DEF8
	#define open_fs_object_symbol                            0x18A6F0
	#define close_fs_object_symbol                           0x18962C
	#define storage_get_device_info_symbol                   0x282130
	#define storage_open_symbol                              0x281B40
	#define storage_close_symbol                             0x281930
	#define storage_read_symbol                              0x280EA0
	#define storage_send_device_command_symbol               0x280A2C
	#define storage_map_io_memory_symbol                     0x281FEC
	#define storage_unmap_io_memory_symbol                   0x281EB8
	#define storage_internal_get_device_object_symbol        0x2804E4
	#define decrypt_func_symbol                              0x34798
	#define lv1_call_99_wrapper_symbol                       0x4ECD0
	#define modules_verification_symbol                      0x58828
	#define prx_load_module_symbol                           0x87234
	#define prx_start_module_symbol                          0x85F00
	#define prx_stop_module_symbol                           0x872D8
	#define prx_unload_module_symbol                         0x85C34
	#define prx_get_module_info_symbol                       0x856BC
	#define prx_get_module_list_symbol                       0x8573C
	#define extend_kstack_symbol                             0x6E7C4
	#define get_pseudo_random_number_symbol                  0x230B04
	#define syscall_table_symbol                             0x35F300
	#define syscall_call_offset                              0x27E234
	#define read_bdvd0_symbol                                0x1AD1B4
	#define read_bdvd1_symbol                                0x1AEDE0
	#define read_bdvd2_symbol                                0x1BBF98
	#define device_event_port_send_call                      0x28A69C
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x29E358
	#define fsloop_close_call                                0x29E3A8
	#define fsloop_read_call                                 0x29E3E8
	#define io_rtoc_entry_1                                 -0x1E8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x6688
	#define storage_rtoc_entry_1                             0x1DC8
	#define device_event_rtoc_entry_1                        0x2038
	#define process_rtoc_entry_1                            -0x7800
	#define patch_func2                                      0x591E0
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x2022C
	#define user_thread_prio_patch2                          0x20238
	#define shutdown_patch_offset                            0xAAA8
	#define shutdown_copy_params_call                        0xAABC

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000EC3A6
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB3205600056C47
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001E2C8
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BCE800006477
	#define PSP_EMULATOR_HASH                           0x7BE641F500023794
	#define PEMUCORELIB_HASH                            0xF349A563000C0CFC
	#define EMULATOR_API_HASH                           0xA9F5B37A0001BB36
	#define EMULATOR_DRM_HASH                           0xA324DC4A0000539C
	#define EMULATOR_DRM_DATA_HASH                      0x1D8D2DA00001B6E4
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC04800003207

	/* lv1 */
	#define vsh_pos_in_ram                              0x910000

	/* vsh */
	#define ps2tonet_patch                              0xC4C5C
	#define ps2tonet_size_patch                         0xC4C50
	#define vmode_patch_offset                          0x4422FC
	#define psp_drm_patch1                              0x24071C
	#define psp_drm_patch2                              0x2411BC
	#define psp_drm_patch3                              0x240DF8
	#define psp_drm_patch4                              0x241604
	#define psp_drm_patchA                              0x240838
	#define psp_drm_patchB                              0x2410D8
	#define psp_drm_patchC                              0x240270
	#define psp_drm_patchD                              0x240820
	#define psp_drm_patchE                              0x240824
	#define psp_drm_patchF                              0x2411F0
	#define psp_extra_drm_patch                         0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDD754

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x68430

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x16850

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1C18

	/* emulator_api */
	#define psp_read                                    0x102D8
	#define psp_read_header                             0x1125C
	#define psp_drm_patch5                              0x11080
	#define psp_drm_patch6                              0x110B0
	#define psp_drm_patch7                              0x110C8
	#define psp_drm_patch8                              0x110CC
	#define psp_drm_patch9                              0x1120C
	#define psp_drm_patch11                             0x11210
	#define psp_drm_patch12                             0x11220
	#define psp_product_id_patch1                       0x11320
	#define psp_product_id_patch3                       0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6BC
	#define psp_prx_patch                               0x577D8
	#define psp_savedata_bind_patch1                    0x7A4BC
	#define psp_savedata_bind_patch2                    0x7A514
	#define psp_savedata_bind_patch3                    0x7A030
	#define psp_extra_savedata_patch                    0x8753C
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46D4
	#define psp_savedata_patch2                         0x46AC
	#define psp_savedata_patch3                         0x450C
	#define psp_savedata_patch4                         0x4544
	#define psp_savedata_patch5                         0x4558
	#define psp_savedata_patch6                         0x46C0

	/* libfs */
	#define aio_copy_root_offset                        0xD658

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                   0xACF4AF2B000ECBBB
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH            0x9CB325E600056E4C
	#define GAME_EXT_PLUGIN_REBUG_HASH                  0xE274AF7B0001E2CF
	#define dex_ps2_nonbw_offset                        0xDD6D0
	#define dex_ps2_nonbw_offset2                       0x68244
	#define dex_ps2_nonbw_offset3                       0x16B40
	#define dex_ps2tonet_patch                          0xCA1A8
	#define dex_ps2tonet_size_patch                     0xCA19C
	#define dex_vmode_patch_offset                      0x449EF0
	#define dex_psp_drm_patch1                          0x247F44
	#define dex_psp_drm_patch2                          0x2489E4
	#define dex_psp_drm_patch3                          0x248620
	#define dex_psp_drm_patch4                          0x248E2C
	#define dex_psp_drm_patchA                          0x248060
	#define dex_psp_drm_patchB                          0x248900
	#define dex_psp_drm_patchC                          0x247A98
	#define dex_psp_drm_patchD                          0x248048
	#define dex_psp_drm_patchE                          0x24804C
	#define dex_psp_drm_patchF                          0x248A18
	#define dex_psp_extra_drm_patch                     0x0
#endif

#ifdef FIRMWARE_453D

	#define FIRMWARE_VERSION                                 0x453

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x453
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000004045B0ULL
		#define PS3MAPI_IDPS_2                               0x8000000000494F0CULL
		#define PS3MAPI_PSID                                 0x8000000000494F24ULL
	#endif

	/* lv2 */
	#define TOC                                              0x370620
	#define open_shared_kernel_object_symbol                 0x12ABC
	#define close_kernel_object_handle_symbol                0x120DC
	#define open_kernel_object_symbol                        0x12CAC
	#define alloc_symbol                                     0x66948
	#define dealloc_symbol                                   0x66D84
	#define copy_to_user_symbol                              0xFEA4
	#define copy_from_user_symbol                            0x100C0
	#define copy_to_process_symbol                           0xFF5C
	#define copy_from_process_symbol                         0xFD6C
	#define page_allocate_symbol                             0x624B8
	#define page_free_symbol                                 0x61F1C
	#define page_export_to_proc_symbol                       0x62654
	#define page_unexport_from_proc_symbol                   0x61E10
	#define kernel_ea_to_lpar_addr_symbol                    0x723BC
	#define map_process_memory_symbol                        0x79A68
	#define memcpy_symbol                                    0x81128
	#define memset_symbol                                    0x50E3C
	#define memcmp_symbol                                    0x5014C
	#define printf_symbol                                    0x280FE0
	#define printfnull_symbol                                0x285A64
	#define sprintf_symbol                                   0x52264
	#define snprintf_symbol                                  0x521D0
	#define strcpy_symbol                                    0x50FE8
	#define strncpy_symbol                                   0x510B0
	#define strlen_symbol                                    0x51010
	#define strcat_symbol                                    0x50F18
	#define strcmp_symbol                                    0x50F94
	#define strncmp_symbol                                   0x5103C
	#define strchr_symbol                                    0x50F50
	#define spin_lock_irqsave_ex_symbol                      0x27DCEC
	#define spin_unlock_irqrestore_ex_symbol                 0x27DCC0
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x14660
	#define ppu_thread_exit_symbol                           0x14718
	#define ppu_thread_join_symbol                           0x1476C
	#define ppu_thread_delay_symbol                          0x2A510
	#define create_user_thread2_symbol                       0x26B60
	#define start_thread_symbol                              0x25698
	#define run_thread_symbol                                0x24E5C
	#define register_thread_symbol                           0x276914
	#define allocate_user_stack_symbol                       0x2770FC
	#define mutex_create_symbol                              0x13CF0
	#define mutex_destroy_symbol                             0x13C88
	#define mutex_lock_symbol                                0x13C80
	#define mutex_unlock_symbol                              0x13C78
	#define event_port_create_symbol                         0x1372C
	#define event_port_destroy_symbol                        0x13B94
	#define event_port_connect_symbol                        0x13C0C
	#define event_port_disconnect_symbol                     0x13B38
	#define event_port_send_symbol                           0x13724
	#define event_queue_create_symbol                        0x13A34
	#define event_queue_destroy_symbol                       0x139BC
	#define event_queue_receive_symbol                       0x13800
	#define cellFsOpen_symbol                                0x2B8688
	#define cellFsClose_symbol                               0x2B84F0
	#define cellFsRead_symbol                                0x2B862C
	#define cellFsWrite_symbol                               0x2B8598
	#define cellFsLseek_symbol                               0x2B7DEC
	#define cellFsStat_symbol                                0x2B7EA4
	#define cellFsUnlink_internal_symbol                     0x1A26DC
	#define cellFsUtilMount_symbol                           0x2B7B60
	#define cellFsUtilUmount_symbol                          0x2B7B34
	#define pathdup_from_user_symbol                         0x1A86F4
	#define open_path_symbol                                 0x2B83C0
	#define open_fs_object_symbol                            0x190A7C
	#define close_fs_object_symbol                           0x18F9B8
	#define storage_get_device_info_symbol                   0x295064
	#define storage_open_symbol                              0x29528C
	#define storage_close_symbol                             0x293A78
	#define storage_read_symbol                              0x2929F4
	#define storage_send_device_command_symbol               0x292514
	#define storage_map_io_memory_symbol                     0x294F10
	#define storage_unmap_io_memory_symbol                   0x294DCC
	#define storage_internal_get_device_object_symbol        0x291FCC
	#define decrypt_func_symbol                              0x380B8
	#define lv1_call_99_wrapper_symbol                       0x52678
	#define modules_verification_symbol                      0x5C1F8
	#define prx_load_module_symbol                           0x8B938
	#define prx_start_module_symbol                          0x8A604
	#define prx_stop_module_symbol                           0x8B9DC
	#define prx_unload_module_symbol                         0x8A338
	#define prx_get_module_info_symbol                       0x89D30
	#define prx_get_module_list_symbol                       0x89DB0
	#define extend_kstack_symbol                             0x72314
	#define get_pseudo_random_number_symbol                  0x236FE0
	#define syscall_table_symbol                             0x385108
	#define syscall_call_offset                              0x286548
	#define read_bdvd0_symbol                                0x1B3664
	#define read_bdvd1_symbol                                0x1B5290
	#define read_bdvd2_symbol                                0x1C2448
	#define device_event_port_send_call                      0x29F260
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x2B8820
	#define fsloop_close_call                                0x2B8870
	#define fsloop_read_call                                 0x2B88B0
	#define io_rtoc_entry_1                                 -0xB8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65A8
	#define storage_rtoc_entry_1                             0x22A0
	#define device_event_rtoc_entry_1                        0x2628
	#define process_rtoc_entry_1                            -0x77A0
	#define patch_func2                                      0x5CBB0
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x21CDC
	#define user_thread_prio_patch2                          0x21CE8
	#define shutdown_patch_offset                            0xAB28
	#define shutdown_copy_params_call                        0xAB3C

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000ECBBB
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB325E600056E4C
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001E2CF
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BCE800006477
	#define PSP_EMULATOR_HASH                           0x7BE641F500023794
	#define PEMUCORELIB_HASH                            0xF349A563000C0CFC
	#define EMULATOR_API_HASH                           0xA9F5B37A0001BB36
	#define EMULATOR_DRM_HASH                           0xA324DC4A0000539C
	#define EMULATOR_DRM_DATA_HASH                      0x1D8D2DA00001B6E4
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC04800003207

	/* lv1 */
	#define vsh_pos_in_ram                              0x910000

	/* vsh */
	#define ps2tonet_patch                              0xCA1A8
	#define ps2tonet_size_patch                         0xCA19C
	#define vmode_patch_offset                          0x449EF0
	#define psp_drm_patch1                              0x247F44
	#define psp_drm_patch2                              0x2489E4
	#define psp_drm_patch3                              0x248620
	#define psp_drm_patch4                              0x248E2C
	#define psp_drm_patchA                              0x248060
	#define psp_drm_patchB                              0x248900
	#define psp_drm_patchC                              0x247A98
	#define psp_drm_patchD                              0x248048
	#define psp_drm_patchE                              0x24804C
	#define psp_drm_patchF                              0x248A18
	#define psp_extra_drm_patch                         0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDD6D0

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x68244

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x16B40

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1C18

	/* emulator_api */
	#define psp_read                                    0x102D8
	#define psp_read_header                             0x1125C
	#define psp_drm_patch5                              0x11080
	#define psp_drm_patch6                              0x110B0
	#define psp_drm_patch7                              0x110C8
	#define psp_drm_patch8                              0x110CC
	#define psp_drm_patch9                              0x1120C
	#define psp_drm_patch11                             0x11210
	#define psp_drm_patch12                             0x11220
	#define psp_product_id_patch1                       0x11320
	#define psp_product_id_patch3                       0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6BC
	#define psp_prx_patch                               0x577D8
	#define psp_savedata_bind_patch1                    0x7A4BC
	#define psp_savedata_bind_patch2                    0x7A514
	#define psp_savedata_bind_patch3                    0x7A030
	#define psp_extra_savedata_patch                    0x8753C
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46D4
	#define psp_savedata_patch2                         0x46AC
	#define psp_savedata_patch3                         0x450C
	#define psp_savedata_patch4                         0x4544
	#define psp_savedata_patch5                         0x4558
	#define psp_savedata_patch6                         0x46C0

	/* libfs */
	#define aio_copy_root_offset                        0xD658

	/* CEX */
	#define cex_ps2tonet_patch                          0xC4C5C
	#define cex_ps2tonet_size_patch                     0xC4C50
	#define cex_vmode_patch_offset                      0x4422FC
	#define cex_psp_drm_patch1                          0x24071C
	#define cex_psp_drm_patch2                          0x2411BC
	#define cex_psp_drm_patch3                          0x240DF8
	#define cex_psp_drm_patch4                          0x241604
	#define cex_psp_drm_patchA                          0x240838
	#define cex_psp_drm_patchB                          0x2410D8
	#define cex_psp_drm_patchC                          0x240270
	#define cex_psp_drm_patchD                          0x240820
	#define cex_psp_drm_patchE                          0x240824
	#define cex_psp_drm_patchF                          0x2411F0
	#define cex_psp_extra_drm_patch                     0x0
#endif

#ifdef FIRMWARE_455C

	#define FIRMWARE_VERSION                                 0x455

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x455
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E17B0ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474F1CULL
		#define PS3MAPI_PSID                                 0x8000000000474F34ULL
	#endif

	/* lv2 */
	#define TOC                                              0x34E620
	#define open_shared_kernel_object_symbol                 0x12484
	#define close_kernel_object_handle_symbol                0x11AA4
	#define open_kernel_object_symbol                        0x12674
	#define alloc_symbol                                     0x643B4
	#define dealloc_symbol                                   0x647F0
	#define copy_to_user_symbol                              0xF86C
	#define copy_from_user_symbol                            0xFA88
	#define copy_to_process_symbol                           0xF924
	#define copy_from_process_symbol                         0xF734
	#define page_allocate_symbol                             0x5FF24
	#define page_free_symbol                                 0x5F988
	#define page_export_to_proc_symbol                       0x600C0
	#define page_unexport_from_proc_symbol                   0x5F87C
	#define kernel_ea_to_lpar_addr_symbol                    0x6FCA8
	#define map_process_memory_symbol                        0x76DC8
	#define memcpy_symbol                                    0x7E488
	#define memset_symbol                                    0x4D6D8
	#define memcmp_symbol                                    0x4C9E8
	#define printf_symbol                                    0x27A530
	#define printfnull_symbol                                0x27EFA0
	#define sprintf_symbol                                   0x4EB00
	#define snprintf_symbol                                  0x4EA6C
	#define strcpy_symbol                                    0x4D884
	#define strncpy_symbol                                   0x4D94C
	#define strlen_symbol                                    0x4D8AC
	#define strcat_symbol                                    0x4D7B4
	#define strcmp_symbol                                    0x4D830
	#define strncmp_symbol                                   0x4D8D8
	#define strchr_symbol                                    0x4D7EC
	#define spin_lock_irqsave_ex_symbol                      0x277630
	#define spin_unlock_irqrestore_ex_symbol                 0x277604
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x13F3C
	#define ppu_thread_exit_symbol                           0x13FF4
	#define ppu_thread_join_symbol                           0x14048
	#define ppu_thread_delay_symbol                          0x28810
	#define create_user_thread2_symbol                       0x250F4
	#define start_thread_symbol                              0x23DC0
	#define run_thread_symbol                                0x235F0
	#define register_thread_symbol                           0x27183C
	#define allocate_user_stack_symbol                       0x272024
	#define mutex_create_symbol                              0x136B0
	#define mutex_destroy_symbol                             0x13648
	#define mutex_lock_symbol                                0x13640
	#define mutex_unlock_symbol                              0x13638
	#define event_port_create_symbol                         0x130EC
	#define event_port_destroy_symbol                        0x13554
	#define event_port_connect_symbol                        0x135CC
	#define event_port_disconnect_symbol                     0x134F8
	#define event_port_send_symbol                           0x130E4
	#define event_queue_create_symbol                        0x133F4
	#define event_queue_destroy_symbol                       0x1337C
	#define event_queue_receive_symbol                       0x131C0
	#define cellFsOpen_symbol                                0x29FA10
	#define cellFsClose_symbol                               0x29F878
	#define cellFsRead_symbol                                0x29F9B4
	#define cellFsWrite_symbol                               0x29F920
	#define cellFsLseek_symbol                               0x29EFA8
	#define cellFsStat_symbol                                0x29F22C
	#define cellFsUnlink_internal_symbol                     0x19D83C
	#define cellFsUtilMount_symbol                           0x29ED88
	#define cellFsUtilUmount_symbol                          0x29ED5C
	#define pathdup_from_user_symbol                         0x1A3730
	#define open_path_symbol                                 0x29F748
	#define open_fs_object_symbol                            0x18BB60
	#define close_fs_object_symbol                           0x18AA9C
	#define storage_get_device_info_symbol                   0x283980
	#define storage_open_symbol                              0x283390
	#define storage_close_symbol                             0x283180
	#define storage_read_symbol                              0x2826F0
	#define storage_send_device_command_symbol               0x28227C
	#define storage_map_io_memory_symbol                     0x28383C
	#define storage_unmap_io_memory_symbol                   0x283708
	#define storage_internal_get_device_object_symbol        0x281D34
	#define decrypt_func_symbol                              0x349DC
	#define lv1_call_99_wrapper_symbol                       0x4EF14
	#define modules_verification_symbol                      0x586E8
	#define prx_load_module_symbol                           0x88680
	#define prx_start_module_symbol                          0x8734C
	#define prx_stop_module_symbol                           0x88724
	#define prx_unload_module_symbol                         0x87080
	#define prx_get_module_info_symbol                       0x86B08
	#define prx_get_module_list_symbol                       0x86B88
	#define extend_kstack_symbol                             0x6FC00
	#define get_pseudo_random_number_symbol                  0x2321D4
	#define syscall_table_symbol                             0x362680
	#define syscall_call_offset                              0x27FA84
	#define read_bdvd0_symbol                                0x1AE6A0
	#define read_bdvd1_symbol                                0x1B02CC
	#define read_bdvd2_symbol                                0x1BD454
	#define device_event_port_send_call                      0x28BEEC
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x29FBA8
	#define fsloop_close_call                                0x29FBF8
	#define fsloop_read_call                                 0x29FC38
	#define io_rtoc_entry_1                                 -0x1B8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A8
	#define storage_rtoc_entry_1                             0x1E10
	#define device_event_rtoc_entry_1                        0x2080
	#define process_rtoc_entry_1                            -0x7800
	#define patch_func2                                      0x59990
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x20470
	#define user_thread_prio_patch2                          0x2047C
	#define shutdown_patch_offset                            0xAAB8
	#define shutdown_copy_params_call                        0xAACC

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000EC3A6
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB3205600056C47
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001E2C8
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BCE800006477
	#define PSP_EMULATOR_HASH                           0x7BE641F500023794
	#define PEMUCORELIB_HASH                            0xF349A563000C0CFC
	#define EMULATOR_API_HASH                           0xA9F5B37A0001BB36
	#define EMULATOR_DRM_HASH                           0xA324DC4A0000539C
	#define EMULATOR_DRM_DATA_HASH                      0x1D8D2DA00001B6E4
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC04800003207

	/* lv1 */
	#define vsh_pos_in_ram                              0x840000

	/* vsh */
	#define ps2tonet_patch                              0xC4C5C
	#define ps2tonet_size_patch                         0xC4C50
	#define vmode_patch_offset                          0x4430E8
	#define psp_drm_patch1                              0x24071C
	#define psp_drm_patch2                              0x2411BC
	#define psp_drm_patch3                              0x240DF8
	#define psp_drm_patch4                              0x241604
	#define psp_drm_patchA                              0x240838
	#define psp_drm_patchB                              0x2410D8
	#define psp_drm_patchC                              0x240270
	#define psp_drm_patchD                              0x240820
	#define psp_drm_patchE                              0x240824
	#define psp_drm_patchF                              0x2411F0
	#define psp_extra_drm_patch                         0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDD754

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x68430

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x16850

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1C18

	/* emulator_api */
	#define psp_read                                    0x102D8
	#define psp_read_header                             0x1125C
	#define psp_drm_patch5                              0x11080
	#define psp_drm_patch6                              0x110B0
	#define psp_drm_patch7                              0x110C8
	#define psp_drm_patch8                              0x110CC
	#define psp_drm_patch9                              0x1120C
	#define psp_drm_patch11                             0x11210
	#define psp_drm_patch12                             0x11220
	#define psp_product_id_patch1                       0x11320
	#define psp_product_id_patch3                       0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6BC
	#define psp_prx_patch                               0x577D8
	#define psp_savedata_bind_patch1                    0x7A4BC
	#define psp_savedata_bind_patch2                    0x7A514
	#define psp_savedata_bind_patch3                    0x7A030
	#define psp_extra_savedata_patch                    0x8753C
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46D4
	#define psp_savedata_patch2                         0x46AC
	#define psp_savedata_patch3                         0x450C
	#define psp_savedata_patch4                         0x4544
	#define psp_savedata_patch5                         0x4558
	#define psp_savedata_patch6                         0x46C0

	/* libfs */
	#define aio_copy_root_offset                        0xD658

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                   0xACF4AF2B000ECBBD
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH            0x9CB325E600056E4C
	#define GAME_EXT_PLUGIN_REBUG_HASH                  0xE274AF7B0001E2CF
	#define dex_ps2_nonbw_offset                        0xDD6D0
	#define dex_ps2_nonbw_offset2                       0x68244
	#define dex_ps2_nonbw_offset3                       0x16B40
	#define dex_ps2tonet_patch                          0xCA1A8
	#define dex_ps2tonet_size_patch                     0xCA19C
	#define dex_vmode_patch_offset                      0x44ACDC
	#define dex_psp_drm_patch1                          0x247F44
	#define dex_psp_drm_patch2                          0x2489E4
	#define dex_psp_drm_patch3                          0x248620
	#define dex_psp_drm_patch4                          0x248E2C
	#define dex_psp_drm_patchA                          0x248060
	#define dex_psp_drm_patchB                          0x248900
	#define dex_psp_drm_patchC                          0x247A98
	#define dex_psp_drm_patchD                          0x248048
	#define dex_psp_drm_patchE                          0x24804C
	#define dex_psp_drm_patchF                          0x248A18
	#define dex_psp_extra_drm_patch                     0x0
#endif

#ifdef FIRMWARE_455D

	#define FIRMWARE_VERSION                                 0x455

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x455
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x8000000000407930ULL
		#define PS3MAPI_IDPS_2                               0x8000000000494F1CULL
		#define PS3MAPI_PSID                                 0x8000000000494F34ULL
	#endif

	/* lv2 */
	#define TOC                                              0x3738E0
	#define open_shared_kernel_object_symbol                 0x12ACC
	#define close_kernel_object_handle_symbol                0x120EC
	#define open_kernel_object_symbol                        0x12CBC
	#define alloc_symbol                                     0x67D84
	#define dealloc_symbol                                   0x681C0
	#define copy_to_user_symbol                              0xFEB4
	#define copy_from_user_symbol                            0x100D0
	#define copy_to_process_symbol                           0xFF6C
	#define copy_from_process_symbol                         0xFD7C
	#define page_allocate_symbol                             0x638F4
	#define page_free_symbol                                 0x63358
	#define page_export_to_proc_symbol                       0x63A90
	#define page_unexport_from_proc_symbol                   0x6324C
	#define kernel_ea_to_lpar_addr_symbol                    0x737F8
	#define map_process_memory_symbol                        0x7AEA4
	#define memcpy_symbol                                    0x82564
	#define memset_symbol                                    0x51080
	#define memcmp_symbol                                    0x50390
	#define printf_symbol                                    0x282838
	#define printfnull_symbol                                0x2872BC
	#define sprintf_symbol                                   0x524A8
	#define snprintf_symbol                                  0x52414
	#define strcpy_symbol                                    0x5122C
	#define strncpy_symbol                                   0x512F4
	#define strlen_symbol                                    0x51254
	#define strcat_symbol                                    0x5115C
	#define strcmp_symbol                                    0x511D8
	#define strncmp_symbol                                   0x51280
	#define strchr_symbol                                    0x51194
	#define spin_lock_irqsave_ex_symbol                      0x27F544
	#define spin_unlock_irqrestore_ex_symbol                 0x27F518
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x14670
	#define ppu_thread_exit_symbol                           0x14728
	#define ppu_thread_join_symbol                           0x1477C
	#define ppu_thread_delay_symbol                          0x2A754
	#define create_user_thread2_symbol                       0x26DA4
	#define start_thread_symbol                              0x258DC
	#define run_thread_symbol                                0x250A0
	#define register_thread_symbol                           0x278160
	#define allocate_user_stack_symbol                       0x278948
	#define mutex_create_symbol                              0x13D00
	#define mutex_destroy_symbol                             0x13C98
	#define mutex_lock_symbol                                0x13C90
	#define mutex_unlock_symbol                              0x13C88
	#define event_port_create_symbol                         0x1373C
	#define event_port_destroy_symbol                        0x13BA4
	#define event_port_connect_symbol                        0x13C1C
	#define event_port_disconnect_symbol                     0x13B48
	#define event_port_send_symbol                           0x13734
	#define event_queue_create_symbol                        0x13A44
	#define event_queue_destroy_symbol                       0x139CC
	#define event_queue_receive_symbol                       0x13810
	#define cellFsOpen_symbol                                0x2B9EDC
	#define cellFsClose_symbol                               0x2B9D44
	#define cellFsRead_symbol                                0x2B9E80
	#define cellFsWrite_symbol                               0x2B9DEC
	#define cellFsLseek_symbol                               0x2B9640
	#define cellFsStat_symbol                                0x2B96F8
	#define cellFsUnlink_internal_symbol                     0x1A3BC8
	#define cellFsUtilMount_symbol                           0x2B93B4
	#define cellFsUtilUmount_symbol                          0x2B9388
	#define pathdup_from_user_symbol                         0x1A9BE0
	#define open_path_symbol                                 0x2B9C14
	#define open_fs_object_symbol                            0x191EEC
	#define close_fs_object_symbol                           0x190E28
	#define storage_get_device_info_symbol                   0x2968BC
	#define storage_open_symbol                              0x296AE4
	#define storage_close_symbol                             0x2952D0
	#define storage_read_symbol                              0x29424C
	#define storage_send_device_command_symbol               0x293D6C
	#define storage_map_io_memory_symbol                     0x296768
	#define storage_unmap_io_memory_symbol                   0x296624
	#define storage_internal_get_device_object_symbol        0x293824
	#define decrypt_func_symbol                              0x382FC
	#define lv1_call_99_wrapper_symbol                       0x528BC
	#define modules_verification_symbol                      0x5C0B8
	#define prx_load_module_symbol                           0x8CD84
	#define prx_start_module_symbol                          0x8BA50
	#define prx_stop_module_symbol                           0x8CE28
	#define prx_unload_module_symbol                         0x8B784
	#define prx_get_module_info_symbol                       0x8B17C
	#define prx_get_module_list_symbol                       0x8B1FC
	#define extend_kstack_symbol                             0x73750
	#define get_pseudo_random_number_symbol                  0x2386B0
	#define syscall_table_symbol                             0x388488
	#define syscall_call_offset                              0x287DA0
	#define read_bdvd0_symbol                                0x1B4B50
	#define read_bdvd1_symbol                                0x1B677C
	#define read_bdvd2_symbol                                0x1C3904
	#define device_event_port_send_call                      0x2A0AB8
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x2BA074
	#define fsloop_close_call                                0x2BA0C4
	#define fsloop_read_call                                 0x2BA104
	#define io_rtoc_entry_1                                 -0x88
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65C8
	#define storage_rtoc_entry_1                             0x22E8
	#define device_event_rtoc_entry_1                        0x2670
	#define process_rtoc_entry_1                            -0x77A0
	#define patch_func2                                      0x5D360
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x21F20
	#define user_thread_prio_patch2                          0x21F2C
	#define shutdown_patch_offset                            0xAB38
	#define shutdown_copy_params_call                        0xAB4C

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000ECBBD
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB325E600056E4C
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001E2CF
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BCE800006477
	#define PSP_EMULATOR_HASH                           0x7BE641F500023794
	#define PEMUCORELIB_HASH                            0xF349A563000C0CFC
	#define EMULATOR_API_HASH                           0xA9F5B37A0001BB36
	#define EMULATOR_DRM_HASH                           0xA324DC4A0000539C
	#define EMULATOR_DRM_DATA_HASH                      0x1D8D2DA00001B6E4
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC04800003207

	/* lv1 */
	#define vsh_pos_in_ram                              0x840000

	/* vsh */
	#define ps2tonet_patch                              0xCA1A8
	#define ps2tonet_size_patch                         0xCA19C
	#define vmode_patch_offset                          0x44ACDC
	#define psp_drm_patch1                              0x247F44
	#define psp_drm_patch2                              0x2489E4
	#define psp_drm_patch3                              0x248620
	#define psp_drm_patch4                              0x248E2C
	#define psp_drm_patchA                              0x248060
	#define psp_drm_patchB                              0x248900
	#define psp_drm_patchC                              0x247A98
	#define psp_drm_patchD                              0x248048
	#define psp_drm_patchE                              0x24804C
	#define psp_drm_patchF                              0x248A18
	#define psp_extra_drm_patch                         0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDD6D0

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x68244

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x16B40

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1C18

	/* emulator_api */
	#define psp_read                                    0x102D8
	#define psp_read_header                             0x1125C
	#define psp_drm_patch5                              0x11080
	#define psp_drm_patch6                              0x110B0
	#define psp_drm_patch7                              0x110C8
	#define psp_drm_patch8                              0x110CC
	#define psp_drm_patch9                              0x1120C
	#define psp_drm_patch11                             0x11210
	#define psp_drm_patch12                             0x11220
	#define psp_product_id_patch1                       0x11320
	#define psp_product_id_patch3                       0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6BC
	#define psp_prx_patch                               0x577D8
	#define psp_savedata_bind_patch1                    0x7A4BC
	#define psp_savedata_bind_patch2                    0x7A514
	#define psp_savedata_bind_patch3                    0x7A030
	#define psp_extra_savedata_patch                    0x8753C
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46D4
	#define psp_savedata_patch2                         0x46AC
	#define psp_savedata_patch3                         0x450C
	#define psp_savedata_patch4                         0x4544
	#define psp_savedata_patch5                         0x4558
	#define psp_savedata_patch6                         0x46C0

	/* libfs */
	#define aio_copy_root_offset                        0xD658

	/* CEX */
	#define cex_ps2tonet_patch                          0xC4C5C
	#define cex_ps2tonet_size_patch                     0xC4C50
	#define cex_vmode_patch_offset                      0x4430E8
	#define cex_psp_drm_patch1                          0x24071C
	#define cex_psp_drm_patch2                          0x2411BC
	#define cex_psp_drm_patch3                          0x240DF8
	#define cex_psp_drm_patch4                          0x241604
	#define cex_psp_drm_patchA                          0x240838
	#define cex_psp_drm_patchB                          0x2410D8
	#define cex_psp_drm_patchC                          0x240270
	#define cex_psp_drm_patchD                          0x240820
	#define cex_psp_drm_patchE                          0x240824
	#define cex_psp_drm_patchF                          0x2411F0
	#define cex_psp_extra_drm_patch                     0x0
#endif

#ifdef FIRMWARE_460C

	#define FIRMWARE_VERSION                                 0x460

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x460
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2BB0ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474F1CULL
		#define PS3MAPI_PSID                                 0x8000000000474F34ULL
	#endif

	/* lv2 */
	#define TOC                                              0x34F950
	#define open_shared_kernel_object_symbol                 0x1240C
	#define close_kernel_object_handle_symbol                0x11A2C
	#define open_kernel_object_symbol                        0x125FC
	#define alloc_symbol                                     0x64798
	#define dealloc_symbol                                   0x64BD4
	#define copy_to_user_symbol                              0xF868
	#define copy_from_user_symbol                            0xFA84
	#define copy_to_process_symbol                           0xF920
	#define copy_from_process_symbol                         0xF730
	#define page_allocate_symbol                             0x60308
	#define page_free_symbol                                 0x5FD6C
	#define page_export_to_proc_symbol                       0x604A4
	#define page_unexport_from_proc_symbol                   0x5FC60
	#define kernel_ea_to_lpar_addr_symbol                    0x700C0
	#define map_process_memory_symbol                        0x771E0
	#define memcpy_symbol                                    0x7E8A0
	#define memset_symbol                                    0x4D668
	#define memcmp_symbol                                    0x4C978
	#define printf_symbol                                    0x279330
	#define printfnull_symbol                                0x27DDA4
	#define sprintf_symbol                                   0x4EA90
	#define snprintf_symbol                                  0x4E9FC
	#define strcpy_symbol                                    0x4D814
	#define strncpy_symbol                                   0x4D8DC
	#define strlen_symbol                                    0x4D83C
	#define strcat_symbol                                    0x4D744
	#define strcmp_symbol                                    0x4D7C0
	#define strncmp_symbol                                   0x4D868
	#define strchr_symbol                                    0x4D77C
	#define spin_lock_irqsave_ex_symbol                      0x27641C
	#define spin_unlock_irqrestore_ex_symbol                 0x2763F0
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x13EC4
	#define ppu_thread_exit_symbol                           0x13F7C
	#define ppu_thread_join_symbol                           0x13FD0
	#define ppu_thread_delay_symbol                          0x287A0
	#define create_user_thread2_symbol                       0x2507C
	#define start_thread_symbol                              0x23D48
	#define run_thread_symbol                                0x23578
	#define register_thread_symbol                           0x2705D0
	#define allocate_user_stack_symbol                       0x270DB8
	#define mutex_create_symbol                              0x13638
	#define mutex_destroy_symbol                             0x135D0
	#define mutex_lock_symbol                                0x135C8
	#define mutex_unlock_symbol                              0x135C0
	#define event_port_create_symbol                         0x13074
	#define event_port_destroy_symbol                        0x134DC
	#define event_port_connect_symbol                        0x13554
	#define event_port_disconnect_symbol                     0x13480
	#define event_port_send_symbol                           0x1306C
	#define event_queue_create_symbol                        0x1337C
	#define event_queue_destroy_symbol                       0x13304
	#define event_queue_receive_symbol                       0x13148
	#define cellFsOpen_symbol                                0x2A0584
	#define cellFsClose_symbol                               0x2A03EC
	#define cellFsRead_symbol                                0x2A0528
	#define cellFsWrite_symbol                               0x2A0494
	#define cellFsLseek_symbol                               0x29FB1C
	#define cellFsStat_symbol                                0x29FDA0
	#define cellFsUnlink_internal_symbol                     0x19C4AC
	#define cellFsUtilMount_symbol                           0x29F8FC
	#define cellFsUtilUmount_symbol                          0x29F8D0
	#define pathdup_from_user_symbol                         0x1A23A0
	#define open_path_symbol                                 0x2A02BC
	#define open_fs_object_symbol                            0x18A7D0
	#define close_fs_object_symbol                           0x18970C
	#define storage_get_device_info_symbol                   0x282784
	#define storage_open_symbol                              0x282194
	#define storage_close_symbol                             0x281F84
	#define storage_read_symbol                              0x2814F4
	#define storage_send_device_command_symbol               0x281080
	#define storage_map_io_memory_symbol                     0x282640
	#define storage_unmap_io_memory_symbol                   0x28250C
	#define storage_internal_get_device_object_symbol        0x280B38
	#define decrypt_func_symbol                              0x3496C
	#define lv1_call_99_wrapper_symbol                       0x4EEA4
	#define modules_verification_symbol                      0x58A48
	#define prx_load_module_symbol                           0x88B78
	#define prx_start_module_symbol                          0x87844
	#define prx_stop_module_symbol                           0x88C1C
	#define prx_unload_module_symbol                         0x87578
	#define prx_get_module_info_symbol                       0x87000
	#define prx_get_module_list_symbol                       0x87080
	#define extend_kstack_symbol                             0x70018
	#define get_pseudo_random_number_symbol                  0x230E74
	#define syscall_table_symbol                             0x363A18
	#define syscall_call_offset                              0x27E888
	#define read_bdvd0_symbol                                0x1AD310
	#define read_bdvd1_symbol                                0x1AEF3C
	#define read_bdvd2_symbol                                0x1BC0F4
	#define device_event_port_send_call                      0x28ACF0
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x2A071C
	#define fsloop_close_call                                0x2A076C
	#define fsloop_read_call                                 0x2A07AC
	#define io_rtoc_entry_1                                 -0x1F0
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0
	#define storage_rtoc_entry_1                             0x1DD8
	#define device_event_rtoc_entry_1                        0x2048
	#define process_rtoc_entry_1                            -0x7800
	#define patch_func2                                      0x59CF8
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x203F8
	#define user_thread_prio_patch2                          0x20404
	#define shutdown_patch_offset                            0xAAB8
	#define shutdown_copy_params_call                        0xAACC

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000EC8C2
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB322B600056E97
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001E76A
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BCE800006477
	#define PSP_EMULATOR_HASH                           0x7BE641F500023793
	#define PEMUCORELIB_HASH                            0xF349A563000C0D6B
	#define EMULATOR_API_HASH                           0xA9F5B37A0001BB3C
	#define EMULATOR_DRM_HASH                           0xA324DC4A00005399
	#define EMULATOR_DRM_DATA_HASH                      0x75C390860001B75F
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC3B800003212

	/* lv1 */
	#define vsh_pos_in_ram                              0x510000

	/* vsh */
	#define ps2tonet_patch                              0xC4C24
	#define ps2tonet_size_patch                         0xC4C18
	#define vmode_patch_offset                          0x444DCC
	#define psp_drm_patch1                              0x241E28
	#define psp_drm_patch2                              0x2428C8
	#define psp_drm_patch3                              0x242504
	#define psp_drm_patch4                              0x242D10
	#define psp_drm_patchA                              0x241F44
	#define psp_drm_patchB                              0x2427E4
	#define psp_drm_patchC                              0x24197C
	#define psp_drm_patchD                              0x241F2C
	#define psp_drm_patchE                              0x241F30
	#define psp_drm_patchF                              0x2428FC
	#define psp_extra_drm_patch                         0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDD978

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x68354

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x17004

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1C18

	/* emulator_api */
	#define psp_read                                    0x102D8
	#define psp_read_header                             0x1125C
	#define psp_drm_patch5                              0x11080
	#define psp_drm_patch6                              0x110B0
	#define psp_drm_patch7                              0x110C8
	#define psp_drm_patch8                              0x110CC
	#define psp_drm_patch9                              0x1120C
	#define psp_drm_patch11                             0x11210
	#define psp_drm_patch12                             0x11220
	#define psp_product_id_patch1                       0x11320
	#define psp_product_id_patch3                       0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6BC
	#define psp_prx_patch                               0x577D8
	#define psp_savedata_bind_patch1                    0x7A4BC
	#define psp_savedata_bind_patch2                    0x7A514
	#define psp_savedata_bind_patch3                    0x7A030
	#define psp_extra_savedata_patch                    0x87540
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46CC
	#define psp_savedata_patch2                         0x46A4
	#define psp_savedata_patch3                         0x4504
	#define psp_savedata_patch4                         0x453C
	#define psp_savedata_patch5                         0x4550
	#define psp_savedata_patch6                         0x46B8

	/* libfs */
	#define aio_copy_root_offset                        0xD658

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                   0xACF4AF2B000ED045
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH            0x9CB337A200056FAD
	#define GAME_EXT_PLUGIN_REBUG_HASH                  0xE274AF7B0001E7C3
	#define dex_ps2_nonbw_offset                        0xDDD88
	#define dex_ps2_nonbw_offset2                       0x68294
	#define dex_ps2_nonbw_offset3                       0x172F4
	#define dex_ps2tonet_patch                          0xCA170
	#define dex_ps2tonet_size_patch                     0xCA164
	#define dex_vmode_patch_offset                      0x44C9C0
	#define dex_psp_drm_patch1                          0x249650
	#define dex_psp_drm_patch2                          0x24A0F0
	#define dex_psp_drm_patch3                          0x249D2C
	#define dex_psp_drm_patch4                          0x24A538
	#define dex_psp_drm_patchA                          0x24976C
	#define dex_psp_drm_patchB                          0x24A00C
	#define dex_psp_drm_patchC                          0x2491A4
	#define dex_psp_drm_patchD                          0x249754
	#define dex_psp_drm_patchE                          0x249758
	#define dex_psp_drm_patchF                          0x24A124
	#define dex_psp_extra_drm_patch                     0x0
#endif

#ifdef FIRMWARE_465C

	#define FIRMWARE_VERSION                                 0x465

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x465
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2BB0ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474F1CULL
		#define PS3MAPI_PSID                                 0x8000000000474F34ULL
	#endif

	/* lv2 */
	#define TOC                                              0x34F960
	#define open_shared_kernel_object_symbol                 0x12410
	#define close_kernel_object_handle_symbol                0x11A30
	#define open_kernel_object_symbol                        0x12600
	#define alloc_symbol                                     0x6479C
	#define dealloc_symbol                                   0x64BD8
	#define copy_to_user_symbol                              0xF86C
	#define copy_from_user_symbol                            0xFA88
	#define copy_to_process_symbol                           0xF924
	#define copy_from_process_symbol                         0xF734
	#define page_allocate_symbol                             0x6030C
	#define page_free_symbol                                 0x5FD70
	#define page_export_to_proc_symbol                       0x604A8
	#define page_unexport_from_proc_symbol                   0x5FC64
	#define kernel_ea_to_lpar_addr_symbol                    0x700C4
	#define map_process_memory_symbol                        0x771E4
	#define memcpy_symbol                                    0x7E8A4
	#define memset_symbol                                    0x4D66C
	#define memcmp_symbol                                    0x4C97C
	#define printf_symbol                                    0x27933C
	#define printfnull_symbol                                0x27DDB0
	#define sprintf_symbol                                   0x4EA94
	#define snprintf_symbol                                  0x4EA00
	#define strcpy_symbol                                    0x4D818
	#define strncpy_symbol                                   0x4D8E0
	#define strlen_symbol                                    0x4D840
	#define strcat_symbol                                    0x4D748
	#define strcmp_symbol                                    0x4D7C4
	#define strncmp_symbol                                   0x4D86C
	#define strchr_symbol                                    0x4D780
	#define spin_lock_irqsave_ex_symbol                      0x276428
	#define spin_unlock_irqrestore_ex_symbol                 0x2763FC
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x13EC8
	#define ppu_thread_exit_symbol                           0x13F80
	#define ppu_thread_join_symbol                           0x13FD4
	#define ppu_thread_delay_symbol                          0x287A4
	#define create_user_thread2_symbol                       0x25080
	#define start_thread_symbol                              0x23D4C
	#define run_thread_symbol                                0x2357C
	#define register_thread_symbol                           0x2705DC
	#define allocate_user_stack_symbol                       0x270DC4
	#define mutex_create_symbol                              0x1363C
	#define mutex_destroy_symbol                             0x135D4
	#define mutex_lock_symbol                                0x135CC
	#define mutex_unlock_symbol                              0x135C4
	#define event_port_create_symbol                         0x13078
	#define event_port_destroy_symbol                        0x134E0
	#define event_port_connect_symbol                        0x13558
	#define event_port_disconnect_symbol                     0x13484
	#define event_port_send_symbol                           0x13070
	#define event_queue_create_symbol                        0x13380
	#define event_queue_destroy_symbol                       0x13308
	#define event_queue_receive_symbol                       0x1314C
	#define cellFsOpen_symbol                                0x2A0590
	#define cellFsClose_symbol                               0x2A03F8
	#define cellFsRead_symbol                                0x2A0534
	#define cellFsWrite_symbol                               0x2A04A0
	#define cellFsLseek_symbol                               0x29FB28
	#define cellFsStat_symbol                                0x29FDAC
	#define cellFsUnlink_internal_symbol                     0x19C4B4
	#define cellFsUtilMount_symbol                           0x29F908
	#define cellFsUtilUmount_symbol                          0x29F8DC
	#define pathdup_from_user_symbol                         0x1A23A8
	#define open_path_symbol                                 0x2A02C8
	#define open_fs_object_symbol                            0x18A7D8
	#define close_fs_object_symbol                           0x189714
	#define storage_get_device_info_symbol                   0x282790
	#define storage_open_symbol                              0x2821A0
	#define storage_close_symbol                             0x281F90
	#define storage_read_symbol                              0x281500
	#define storage_send_device_command_symbol               0x28108C
	#define storage_map_io_memory_symbol                     0x28264C
	#define storage_unmap_io_memory_symbol                   0x282518
	#define storage_internal_get_device_object_symbol        0x280B44
	#define decrypt_func_symbol                              0x34970
	#define lv1_call_99_wrapper_symbol                       0x4EEA8
	#define modules_verification_symbol                      0x58A4C
	#define prx_load_module_symbol                           0x88B7C
	#define prx_start_module_symbol                          0x87848
	#define prx_stop_module_symbol                           0x88C20
	#define prx_unload_module_symbol                         0x8757C
	#define prx_get_module_info_symbol                       0x87004
	#define prx_get_module_list_symbol                       0x87084
	#define extend_kstack_symbol                             0x7001C
	#define get_pseudo_random_number_symbol                  0x230E7C
	#define syscall_table_symbol                             0x363A18
	#define syscall_call_offset                              0x27E894
	#define read_bdvd0_symbol                                0x1AD318
	#define read_bdvd1_symbol                                0x1AEF44
	#define read_bdvd2_symbol                                0x1BC0FC
	#define device_event_port_send_call                      0x28ACFC
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x2A0728
	#define fsloop_close_call                                0x2A0778
	#define fsloop_read_call                                 0x2A07B8
	#define io_rtoc_entry_1                                 -0x1F0
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0
	#define storage_rtoc_entry_1                             0x1DD8
	#define device_event_rtoc_entry_1                        0x2048
	#define process_rtoc_entry_1                            -0x7800
	#define patch_func2                                      0x59CFC
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x203FC
	#define user_thread_prio_patch2                          0x20408
	#define shutdown_patch_offset                            0xAAB8
	#define shutdown_copy_params_call                        0xAACC

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000EC8C7
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB322B600056E97
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001E76A
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BCE800006477
	#define PSP_EMULATOR_HASH                           0x7BE641F500023794
	#define PEMUCORELIB_HASH                            0xF349A563000C0D66
	#define EMULATOR_API_HASH                           0xA9F5B37A0001BB3C
	#define EMULATOR_DRM_HASH                           0xA324DC4A00005399
	#define EMULATOR_DRM_DATA_HASH                      0x75C390860001B75F
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC3B800003212

	/* lv1 */
	#define vsh_pos_in_ram                              0x910000

	/* vsh */
	#define ps2tonet_patch                              0xC4C24
	#define ps2tonet_size_patch                         0xC4C18
	#define vmode_patch_offset                          0x444E28
	#define psp_drm_patch1                              0x241E84
	#define psp_drm_patch2                              0x242924
	#define psp_drm_patch3                              0x242560
	#define psp_drm_patch4                              0x242D6C
	#define psp_drm_patchA                              0x241FA0
	#define psp_drm_patchB                              0x242840
	#define psp_drm_patchC                              0x2419D8
	#define psp_drm_patchD                              0x241F88
	#define psp_drm_patchE                              0x241F8C
	#define psp_drm_patchF                              0x242958
	#define psp_extra_drm_patch                         0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDD978

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x68354

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x17004

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1C18

	/* emulator_api */
	#define psp_read                                    0x102D8
	#define psp_read_header                             0x1125C
	#define psp_drm_patch5                              0x11080
	#define psp_drm_patch6                              0x110B0
	#define psp_drm_patch7                              0x110C8
	#define psp_drm_patch8                              0x110CC
	#define psp_drm_patch9                              0x1120C
	#define psp_drm_patch11                             0x11210
	#define psp_drm_patch12                             0x11220
	#define psp_product_id_patch1                       0x11320
	#define psp_product_id_patch3                       0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6BC
	#define psp_prx_patch                               0x577D8
	#define psp_savedata_bind_patch1                    0x7A4BC
	#define psp_savedata_bind_patch2                    0x7A514
	#define psp_savedata_bind_patch3                    0x7A030
	#define psp_extra_savedata_patch                    0x87540
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46CC
	#define psp_savedata_patch2                         0x46A4
	#define psp_savedata_patch3                         0x4504
	#define psp_savedata_patch4                         0x453C
	#define psp_savedata_patch5                         0x4550
	#define psp_savedata_patch6                         0x46B8

	/* libfs */
	#define aio_copy_root_offset                        0xD658

	/* rebug */
	#define EXPLORE_PLUGIN_REBUG_HASH                   0xACF4AF2B000ED047
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH            0x9CB337A200056FAD
	#define GAME_EXT_PLUGIN_REBUG_HASH                  0xE274AF7B0001E7C3
	#define dex_ps2_nonbw_offset                        0xDDD88
	#define dex_ps2_nonbw_offset2                       0x68294
	#define dex_ps2_nonbw_offset3                       0x172F4
	#define dex_ps2tonet_patch                          0xCA170
	#define dex_ps2tonet_size_patch                     0xCA164
	#define dex_vmode_patch_offset                      0x44CA1C
	#define dex_psp_drm_patch1                          0x2496AC
	#define dex_psp_drm_patch2                          0x24A14C
	#define dex_psp_drm_patch3                          0x249D88
	#define dex_psp_drm_patch4                          0x24A594
	#define dex_psp_drm_patchA                          0x2497C8
	#define dex_psp_drm_patchB                          0x24A068
	#define dex_psp_drm_patchC                          0x249200
	#define dex_psp_drm_patchD                          0x2497B0
	#define dex_psp_drm_patchE                          0x2497B4
	#define dex_psp_drm_patchF                          0x24A180
	#define dex_psp_extra_drm_patch                     0x0
#endif

#ifdef FIRMWARE_465D

	#define FIRMWARE_VERSION                                 0x465

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x465
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000004095B0ULL
		#define PS3MAPI_IDPS_2                               0x800000000049CF1CULL
		#define PS3MAPI_PSID                                 0x800000000049CF34ULL
	#endif

	/* lv2 */
	#define TOC                                              0x375510
	#define open_shared_kernel_object_symbol                 0x12A58
	#define close_kernel_object_handle_symbol                0x12078
	#define open_kernel_object_symbol                        0x12C48
	#define alloc_symbol                                     0x6816C
	#define dealloc_symbol                                   0x685A8
	#define copy_to_user_symbol                              0xFEB4
	#define copy_from_user_symbol                            0x100D0
	#define copy_to_process_symbol                           0xFF6C
	#define copy_from_process_symbol                         0xFD7C
	#define page_allocate_symbol                             0x63CDC
	#define page_free_symbol                                 0x63740
	#define page_export_to_proc_symbol                       0x63E78
	#define page_unexport_from_proc_symbol                   0x63634
	#define kernel_ea_to_lpar_addr_symbol                    0x73C14
	#define map_process_memory_symbol                        0x7B2C0
	#define memcpy_symbol                                    0x82980
	#define memset_symbol                                    0x51014
	#define memcmp_symbol                                    0x50324
	#define printf_symbol                                    0x281608
	#define printfnull_symbol                                0x286090
	#define sprintf_symbol                                   0x5243C
	#define snprintf_symbol                                  0x523A8
	#define strcpy_symbol                                    0x511C0
	#define strncpy_symbol                                   0x51288
	#define strlen_symbol                                    0x511E8
	#define strcat_symbol                                    0x510F0
	#define strcmp_symbol                                    0x5116C
	#define strncmp_symbol                                   0x51214
	#define strchr_symbol                                    0x51128
	#define spin_lock_irqsave_ex_symbol                      0x27E300
	#define spin_unlock_irqrestore_ex_symbol                 0x27E2D4
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x145FC
	#define ppu_thread_exit_symbol                           0x146B4
	#define ppu_thread_join_symbol                           0x14708
	#define ppu_thread_delay_symbol                          0x2A6E8
	#define create_user_thread2_symbol                       0x26D30
	#define start_thread_symbol                              0x25868
	#define run_thread_symbol                                0x2502C
	#define register_thread_symbol                           0x276F00
	#define allocate_user_stack_symbol                       0x2776E8
	#define mutex_create_symbol                              0x13C8C
	#define mutex_destroy_symbol                             0x13C24
	#define mutex_lock_symbol                                0x13C1C
	#define mutex_unlock_symbol                              0x13C14
	#define event_port_create_symbol                         0x136C8
	#define event_port_destroy_symbol                        0x13B30
	#define event_port_connect_symbol                        0x13BA8
	#define event_port_disconnect_symbol                     0x13AD4
	#define event_port_send_symbol                           0x136C0
	#define event_queue_create_symbol                        0x139D0
	#define event_queue_destroy_symbol                       0x13958
	#define event_queue_receive_symbol                       0x1379C
	#define cellFsOpen_symbol                                0x2BB2D8
	#define cellFsClose_symbol                               0x2BB140
	#define cellFsRead_symbol                                0x2BB27C
	#define cellFsWrite_symbol                               0x2BB1E8
	#define cellFsLseek_symbol                               0x2BAA3C
	#define cellFsStat_symbol                                0x2BAAF4
	#define cellFsUnlink_internal_symbol                     0x1A2840
	#define cellFsUtilMount_symbol                           0x2BA7B0
	#define cellFsUtilUmount_symbol                          0x2BA784
	#define pathdup_from_user_symbol                         0x1A8858
	#define open_path_symbol                                 0x2BB010
	#define open_fs_object_symbol                            0x190B64
	#define close_fs_object_symbol                           0x18FAA0
	#define storage_get_device_info_symbol                   0x295690
	#define storage_open_symbol                              0x2958B8
	#define storage_close_symbol                             0x2940A4
	#define storage_read_symbol                              0x293020
	#define storage_send_device_command_symbol               0x292B40
	#define storage_map_io_memory_symbol                     0x29553C
	#define storage_unmap_io_memory_symbol                   0x2953F8
	#define storage_internal_get_device_object_symbol        0x2925F8
	#define decrypt_func_symbol                              0x38290
	#define lv1_call_99_wrapper_symbol                       0x52850
	#define modules_verification_symbol                      0x5C41C
	#define prx_load_module_symbol                           0x8D280
	#define prx_start_module_symbol                          0x8BF4C
	#define prx_stop_module_symbol                           0x8D324
	#define prx_unload_module_symbol                         0x8BC80
	#define prx_get_module_info_symbol                       0x8B678
	#define prx_get_module_list_symbol                       0x8B6F8
	#define extend_kstack_symbol                             0x73B6C
	#define get_pseudo_random_number_symbol                  0x237358
	#define syscall_table_symbol                             0x38A120
	#define syscall_call_offset                              0x286B74
	#define read_bdvd0_symbol                                0x1B37C8
	#define read_bdvd1_symbol                                0x1B53F4
	#define read_bdvd2_symbol                                0x1C25AC
	#define device_event_port_send_call                      0x29F88C
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x2BB470
	#define fsloop_close_call                                0x2BB4C0
	#define fsloop_read_call                                 0x2BB500
	#define io_rtoc_entry_1                                 -0xC0
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65C0
	#define storage_rtoc_entry_1                             0x22B0
	#define device_event_rtoc_entry_1                        0x2638
	#define process_rtoc_entry_1                            -0x77A0
	#define patch_func2                                      0x5D6CC
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x21EAC
	#define user_thread_prio_patch2                          0x21EB8
	#define shutdown_patch_offset                            0xAB38
	#define shutdown_copy_params_call                        0xAB4C

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000ED047
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB337A200056FAD
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001E7C3
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BCE800006477
	#define PSP_EMULATOR_HASH                           0x7BE641F500023794
	#define PEMUCORELIB_HASH                            0xF349A563000C0D66
	#define EMULATOR_API_HASH                           0xA9F5B37A0001BB3C
	#define EMULATOR_DRM_HASH                           0xA324DC4A00005399
	#define EMULATOR_DRM_DATA_HASH                      0x75C390860001B75F
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC3B800003212

	/* lv1 */
	#define vsh_pos_in_ram                              0x910000

	/* vsh */
	#define ps2tonet_patch                              0xCA170
	#define ps2tonet_size_patch                         0xCA164
	#define vmode_patch_offset                          0x44CA1C
	#define psp_drm_patch1                              0x2496AC
	#define psp_drm_patch2                              0x24A14C
	#define psp_drm_patch3                              0x249D88
	#define psp_drm_patch4                              0x24A594
	#define psp_drm_patchA                              0x2497C8
	#define psp_drm_patchB                              0x24A068
	#define psp_drm_patchC                              0x249200
	#define psp_drm_patchD                              0x2497B0
	#define psp_drm_patchE                              0x2497B4
	#define psp_drm_patchF                              0x24A180
	#define psp_extra_drm_patch                         0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDDD88

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x68294

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x172F4

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1C18

	/* emulator_api */
	#define psp_read                                    0x102D8
	#define psp_read_header                             0x1125C
	#define psp_drm_patch5                              0x11080
	#define psp_drm_patch6                              0x110B0
	#define psp_drm_patch7                              0x110C8
	#define psp_drm_patch8                              0x110CC
	#define psp_drm_patch9                              0x1120C
	#define psp_drm_patch11                             0x11210
	#define psp_drm_patch12                             0x11220
	#define psp_product_id_patch1                       0x11320
	#define psp_product_id_patch3                       0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6BC
	#define psp_prx_patch                               0x577D8
	#define psp_savedata_bind_patch1                    0x7A4BC
	#define psp_savedata_bind_patch2                    0x7A514
	#define psp_savedata_bind_patch3                    0x7A030
	#define psp_extra_savedata_patch                    0x87540
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46CC
	#define psp_savedata_patch2                         0x46A4
	#define psp_savedata_patch3                         0x4504
	#define psp_savedata_patch4                         0x453C
	#define psp_savedata_patch5                         0x4550
	#define psp_savedata_patch6                         0x46B8

	/* libfs */
	#define aio_copy_root_offset                        0xD658

	/* CEX */
	#define cex_ps2tonet_patch                          0xC4C24
	#define cex_ps2tonet_size_patch                     0xC4C18
	#define cex_vmode_patch_offset                      0x444E28
	#define cex_psp_drm_patch1                          0x241E84
	#define cex_psp_drm_patch2                          0x242924
	#define cex_psp_drm_patch3                          0x242560
	#define cex_psp_drm_patch4                          0x242D6C
	#define cex_psp_drm_patchA                          0x241FA0
	#define cex_psp_drm_patchB                          0x242840
	#define cex_psp_drm_patchC                          0x2419D8
	#define cex_psp_drm_patchD                          0x241F88
	#define cex_psp_drm_patchE                          0x241F8C
	#define cex_psp_drm_patchF                          0x242958
	#define cex_psp_extra_drm_patch                     0x0
#endif

#ifdef FIRMWARE_470C

	#define FIRMWARE_VERSION                                 0x470

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x470
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2DB0ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474AF4ULL
		#define PS3MAPI_PSID                                 0x8000000000474B0CULL
	#endif

	/* lv2 */
	#define TOC                                              0x34FB10
	#define open_shared_kernel_object_symbol                 0x1240C
	#define close_kernel_object_handle_symbol                0x11A2C
	#define open_kernel_object_symbol                        0x125FC
	#define alloc_symbol                                     0x64820
	#define dealloc_symbol                                   0x64C5C
	#define copy_to_user_symbol                              0xF868
	#define copy_from_user_symbol                            0xFA84
	#define copy_to_process_symbol                           0xF920
	#define copy_from_process_symbol                         0xF730
	#define page_allocate_symbol                             0x60390
	#define page_free_symbol                                 0x5FDF4
	#define page_export_to_proc_symbol                       0x6052C
	#define page_unexport_from_proc_symbol                   0x5FCE8
	#define kernel_ea_to_lpar_addr_symbol                    0x70148
	#define map_process_memory_symbol                        0x77268
	#define memcpy_symbol                                    0x7E928
	#define memset_symbol                                    0x4D668
	#define memcmp_symbol                                    0x4C978
	#define printf_symbol                                    0x270634
	#define printfnull_symbol                                0x2750A8
	#define sprintf_symbol                                   0x4EA90
	#define snprintf_symbol                                  0x4E9FC
	#define strcpy_symbol                                    0x4D814
	#define strncpy_symbol                                   0x4D8DC
	#define strlen_symbol                                    0x4D83C
	#define strcat_symbol                                    0x4D744
	#define strcmp_symbol                                    0x4D7C0
	#define strncmp_symbol                                   0x4D868
	#define strchr_symbol                                    0x4D77C
	#define spin_lock_irqsave_ex_symbol                      0x26D720
	#define spin_unlock_irqrestore_ex_symbol                 0x26D6F4
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x13EC4
	#define ppu_thread_exit_symbol                           0x13F7C
	#define ppu_thread_join_symbol                           0x13FD0
	#define ppu_thread_delay_symbol                          0x287A0
	#define create_user_thread2_symbol                       0x2507C
	#define start_thread_symbol                              0x23D48
	#define run_thread_symbol                                0x23578
	#define register_thread_symbol                           0x2678D4
	#define allocate_user_stack_symbol                       0x2680BC
	#define mutex_create_symbol                              0x13638
	#define mutex_destroy_symbol                             0x135D0
	#define mutex_lock_symbol                                0x135C8
	#define mutex_unlock_symbol                              0x135C0
	#define event_port_create_symbol                         0x13074
	#define event_port_destroy_symbol                        0x134DC
	#define event_port_connect_symbol                        0x13554
	#define event_port_disconnect_symbol                     0x13480
	#define event_port_send_symbol                           0x1306C
	#define event_queue_create_symbol                        0x1337C
	#define event_queue_destroy_symbol                       0x13304
	#define event_queue_receive_symbol                       0x13148
	#define cellFsOpen_symbol                                0x297888
	#define cellFsClose_symbol                               0x2976F0
	#define cellFsRead_symbol                                0x29782C
	#define cellFsWrite_symbol                               0x297798
	#define cellFsLseek_symbol                               0x296E20
	#define cellFsStat_symbol                                0x2970A4
	#define cellFsUnlink_internal_symbol                     0x19C644
	#define cellFsUtilMount_symbol                           0x296C00
	#define cellFsUtilUmount_symbol                          0x296BD4
	#define pathdup_from_user_symbol                         0x29C86C
	#define open_path_symbol                                 0x2975C0
	#define open_fs_object_symbol                            0x18A968
	#define close_fs_object_symbol                           0x1898A4
	#define storage_get_device_info_symbol                   0x279A88
	#define storage_open_symbol                              0x279498
	#define storage_close_symbol                             0x279288
	#define storage_read_symbol                              0x2787F8
	#define storage_send_device_command_symbol               0x278384
	#define storage_map_io_memory_symbol                     0x279944
	#define storage_unmap_io_memory_symbol                   0x279810
	#define storage_internal_get_device_object_symbol        0x277E3C
	#define decrypt_func_symbol                              0x3496C
	#define lv1_call_99_wrapper_symbol                       0x4EEA4
	#define modules_verification_symbol                      0x58AB4
	#define prx_load_module_symbol                           0x88C00
	#define prx_start_module_symbol                          0x878CC
	#define prx_stop_module_symbol                           0x88CA4
	#define prx_unload_module_symbol                         0x87600
	#define prx_get_module_info_symbol                       0x87088
	#define prx_get_module_list_symbol                       0x87108
	#define extend_kstack_symbol                             0x700A0
	#define get_pseudo_random_number_symbol                  0x228178
	#define syscall_table_symbol                             0x363B60
	#define syscall_call_offset                              0x275B8C
	#define read_bdvd0_symbol                                0x1A4614
	#define read_bdvd1_symbol                                0x1A6240
	#define read_bdvd2_symbol                                0x1B33F8
	#define device_event_port_send_call                      0x281FF4
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x297A20
	#define fsloop_close_call                                0x297A70
	#define fsloop_read_call                                 0x297AB0
	#define io_rtoc_entry_1                                  0x25B0
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0
	#define storage_rtoc_entry_1                             0x1DD0
	#define device_event_rtoc_entry_1                        0x2040
	#define process_rtoc_entry_1                            -0x7800
	#define patch_func2                                      0x59D80
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x203F8
	#define user_thread_prio_patch2                          0x20404
	#define shutdown_patch_offset                            0xAAB8
	#define shutdown_copy_params_call                        0xAACC

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000EC54E
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB378E600056ADD
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001E6C9
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BCE800006477
	#define PSP_EMULATOR_HASH                           0x7BE641F500023793
	#define PEMUCORELIB_HASH                            0xF349A563000C0D6C
	#define EMULATOR_API_HASH                           0xA9F5B37A0001BB45
	#define EMULATOR_DRM_HASH                           0xA324DC4A00005399
	#define EMULATOR_DRM_DATA_HASH                      0x75C390860001B75F
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC3B800003212

	/* lv1 */
	#define vsh_pos_in_ram                              0x910000

	/* vsh */
	#define ps2tonet_patch                              0xC4B14
	#define ps2tonet_size_patch                         0xC4B08
	#define vmode_patch_offset                          0x445630
	#define psp_drm_patch1                              0x24265C
	#define psp_drm_patch2                              0x2430FC
	#define psp_drm_patch3                              0x242D38
	#define psp_drm_patch4                              0x243544
	#define psp_drm_patchA                              0x242778
	#define psp_drm_patchB                              0x243018
	#define psp_drm_patchC                              0x2421B0
	#define psp_drm_patchD                              0x242760
	#define psp_drm_patchE                              0x242764
	#define psp_drm_patchF                              0x243130
	#define psp_extra_drm_patch                         0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDD97C

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x68324

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x17004

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1C18

	/* emulator_api */
	#define psp_read                                    0x102D8
	#define psp_read_header                             0x1125C
	#define psp_drm_patch5                              0x11080
	#define psp_drm_patch6                              0x110B0
	#define psp_drm_patch7                              0x110C8
	#define psp_drm_patch8                              0x110CC
	#define psp_drm_patch9                              0x1120C
	#define psp_drm_patch11                             0x11210
	#define psp_drm_patch12                             0x11220
	#define psp_product_id_patch1                       0x11320
	#define psp_product_id_patch3                       0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6BC
	#define psp_prx_patch                               0x577D8
	#define psp_savedata_bind_patch1                    0x7A4BC
	#define psp_savedata_bind_patch2                    0x7A514
	#define psp_savedata_bind_patch3                    0x7A030
	#define psp_extra_savedata_patch                    0x87540
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46CC
	#define psp_savedata_patch2                         0x46A4
	#define psp_savedata_patch3                         0x4504
	#define psp_savedata_patch4                         0x453C
	#define psp_savedata_patch5                         0x4550
	#define psp_savedata_patch6                         0x46B8

	/* libfs */
	#define aio_copy_root_offset                        0xD658

	/* rebug */
	#define EXPLORE_PLUGIN_REBUG_HASH                   0xACF4AF2B000ECCEB
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH            0x9CB3396E00056CE1
	#define GAME_EXT_PLUGIN_REBUG_HASH                  0xE274AF7B0001E733
	#define dex_ps2_nonbw_offset                        0xDDD8C
	#define dex_ps2_nonbw_offset2                       0x68264
	#define dex_ps2_nonbw_offset3                       0x172F4
	#define dex_ps2tonet_patch                          0xCA060
	#define dex_ps2tonet_size_patch                     0xCA054
	#define dex_vmode_patch_offset                      0x44D224
	#define dex_psp_drm_patch1                          0x249E84
	#define dex_psp_drm_patch2                          0x24A924
	#define dex_psp_drm_patch3                          0x24A560
	#define dex_psp_drm_patch4                          0x24AD6C
	#define dex_psp_drm_patchA                          0x249FA0
	#define dex_psp_drm_patchB                          0x24A840
	#define dex_psp_drm_patchC                          0x2499D8
	#define dex_psp_drm_patchD                          0x249F88
	#define dex_psp_drm_patchE                          0x249F8C
	#define dex_psp_drm_patchF                          0x24A958
	#define dex_psp_extra_drm_patch                     0x0
#endif

#ifdef FIRMWARE_470D

	#define FIRMWARE_VERSION                                 0x470

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x470
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000004098B0ULL
		#define PS3MAPI_IDPS_2                               0x800000000049CAF4ULL
		#define PS3MAPI_PSID                                 0x800000000049CB0CULL
	#endif

	/* lv2 */
	#define TOC                                              0x375850
	#define open_shared_kernel_object_symbol                 0x12A54
	#define close_kernel_object_handle_symbol                0x12074
	#define open_kernel_object_symbol                        0x12C44
	#define alloc_symbol                                     0x681F0
	#define dealloc_symbol                                   0x6862C
	#define copy_to_user_symbol                              0xFEB0
	#define copy_from_user_symbol                            0x100CC
	#define copy_to_process_symbol                           0xFF68
	#define copy_from_process_symbol                         0xFD78
	#define page_allocate_symbol                             0x63D60
	#define page_free_symbol                                 0x637C4
	#define page_export_to_proc_symbol                       0x63EFC
	#define page_unexport_from_proc_symbol                   0x636B8
	#define kernel_ea_to_lpar_addr_symbol                    0x73C98
	#define map_process_memory_symbol                        0x7B344
	#define memcpy_symbol                                    0x82A04
	#define memset_symbol                                    0x51010
	#define memcmp_symbol                                    0x50320
	#define printf_symbol                                    0x278900
	#define printfnull_symbol                                0x27D388
	#define sprintf_symbol                                   0x52438
	#define snprintf_symbol                                  0x523A4
	#define strcpy_symbol                                    0x511BC
	#define strncpy_symbol                                   0x51284
	#define strlen_symbol                                    0x511E4
	#define strcat_symbol                                    0x510EC
	#define strcmp_symbol                                    0x51168
	#define strncmp_symbol                                   0x51210
	#define strchr_symbol                                    0x51124
	#define spin_lock_irqsave_ex_symbol                      0x2755F8
	#define spin_unlock_irqrestore_ex_symbol                 0x2755CC
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x145F8
	#define ppu_thread_exit_symbol                           0x146B0
	#define ppu_thread_join_symbol                           0x14704
	#define ppu_thread_delay_symbol                          0x2A6E4
	#define create_user_thread2_symbol                       0x26D2C
	#define start_thread_symbol                              0x25864
	#define run_thread_symbol                                0x25028
	#define register_thread_symbol                           0x26E1F8
	#define allocate_user_stack_symbol                       0x26E9E0
	#define mutex_create_symbol                              0x13C88
	#define mutex_destroy_symbol                             0x13C20
	#define mutex_lock_symbol                                0x13C18
	#define mutex_unlock_symbol                              0x13C10
	#define event_port_create_symbol                         0x136C4
	#define event_port_destroy_symbol                        0x13B2C
	#define event_port_connect_symbol                        0x13BA4
	#define event_port_disconnect_symbol                     0x13AD0
	#define event_port_send_symbol                           0x136BC
	#define event_queue_create_symbol                        0x139CC
	#define event_queue_destroy_symbol                       0x13954
	#define event_queue_receive_symbol                       0x13798
	#define cellFsOpen_symbol                                0x2B2748
	#define cellFsClose_symbol                               0x2B25B0
	#define cellFsRead_symbol                                0x2B26EC
	#define cellFsWrite_symbol                               0x2B2658
	#define cellFsLseek_symbol                               0x2B1EAC
	#define cellFsStat_symbol                                0x2B1F64
	#define cellFsUnlink_internal_symbol                     0x1A29D0
	#define cellFsUtilMount_symbol                           0x2B1C20
	#define cellFsUtilUmount_symbol                          0x2B1BF4
	#define pathdup_from_user_symbol                         0x2B7A0C
	#define open_path_symbol                                 0x2B2480
	#define open_fs_object_symbol                            0x190CF4
	#define close_fs_object_symbol                           0x18FC30
	#define storage_get_device_info_symbol                   0x28C988
	#define storage_open_symbol                              0x28CBB0
	#define storage_close_symbol                             0x28B39C
	#define storage_read_symbol                              0x28A318
	#define storage_send_device_command_symbol               0x289E38
	#define storage_map_io_memory_symbol                     0x28C834
	#define storage_unmap_io_memory_symbol                   0x28C6F0
	#define storage_internal_get_device_object_symbol        0x2898F0
	#define decrypt_func_symbol                              0x3828C
	#define lv1_call_99_wrapper_symbol                       0x5284C
	#define modules_verification_symbol                      0x5C484
	#define prx_load_module_symbol                           0x8D304
	#define prx_start_module_symbol                          0x8BFD0
	#define prx_stop_module_symbol                           0x8D3A8
	#define prx_unload_module_symbol                         0x8BD04
	#define prx_get_module_info_symbol                       0x8B6FC
	#define prx_get_module_list_symbol                       0x8B77C
	#define extend_kstack_symbol                             0x73BF0
	#define get_pseudo_random_number_symbol                  0x22E654
	#define syscall_table_symbol                             0x38A368
	#define syscall_call_offset                              0x27DE6C
	#define read_bdvd0_symbol                                0x1AAAC4
	#define read_bdvd1_symbol                                0x1AC6F0
	#define read_bdvd2_symbol                                0x1B98A8
	#define device_event_port_send_call                      0x296B84
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x2B28E0
	#define fsloop_close_call                                0x2B2930
	#define fsloop_read_call                                 0x2B2970
	#define io_rtoc_entry_1                                  0x2EB8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65C0
	#define storage_rtoc_entry_1                             0x22A8
	#define device_event_rtoc_entry_1                        0x2630
	#define process_rtoc_entry_1                            -0x77A0
	#define patch_func2                                      0x5D750
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x21EA8
	#define user_thread_prio_patch2                          0x21EB4
	#define shutdown_patch_offset                            0xAB38
	#define shutdown_copy_params_call                        0xAB4C

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000ECCEB
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB3396E00056CE1
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001E733
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BCE800006477
	#define PSP_EMULATOR_HASH                           0x7BE641F500023793
	#define PEMUCORELIB_HASH                            0xF349A563000C0D6C
	#define EMULATOR_API_HASH                           0xA9F5B37A0001BB45
	#define EMULATOR_DRM_HASH                           0xA324DC4A00005399
	#define EMULATOR_DRM_DATA_HASH                      0x75C390860001B75F
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC3B800003212

	/* lv1 */
	#define vsh_pos_in_ram                              0x910000

	/* vsh */
	#define ps2tonet_patch                              0xCA060
	#define ps2tonet_size_patch                         0xCA054
	#define vmode_patch_offset                          0x44D224
	#define psp_drm_patch1                              0x249E84
	#define psp_drm_patch2                              0x24A924
	#define psp_drm_patch3                              0x24A560
	#define psp_drm_patch4                              0x24AD6C
	#define psp_drm_patchA                              0x249FA0
	#define psp_drm_patchB                              0x24A840
	#define psp_drm_patchC                              0x2499D8
	#define psp_drm_patchD                              0x249F88
	#define psp_drm_patchE                              0x249F8C
	#define psp_drm_patchF                              0x24A958
	#define psp_extra_drm_patch                         0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDDD8C

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x68264

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x172F4

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1C18

	/* emulator_api */
	#define psp_read                                    0x102D8
	#define psp_read_header                             0x1125C
	#define psp_drm_patch5                              0x11080
	#define psp_drm_patch6                              0x110B0
	#define psp_drm_patch7                              0x110C8
	#define psp_drm_patch8                              0x110CC
	#define psp_drm_patch9                              0x1120C
	#define psp_drm_patch11                             0x11210
	#define psp_drm_patch12                             0x11220
	#define psp_product_id_patch1                       0x11320
	#define psp_product_id_patch3                       0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6BC
	#define psp_prx_patch                               0x577D8
	#define psp_savedata_bind_patch1                    0x7A4BC
	#define psp_savedata_bind_patch2                    0x7A514
	#define psp_savedata_bind_patch3                    0x7A030
	#define psp_extra_savedata_patch                    0x87540
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46CC
	#define psp_savedata_patch2                         0x46A4
	#define psp_savedata_patch3                         0x4504
	#define psp_savedata_patch4                         0x453C
	#define psp_savedata_patch5                         0x4550
	#define psp_savedata_patch6                         0x46B8

	/* libfs */
	#define aio_copy_root_offset                        0xD658

	/* CEX */
	#define cex_ps2tonet_patch                          0xC4B14
	#define cex_ps2tonet_size_patch                     0xC4B08
	#define cex_vmode_patch_offset                      0x445630
	#define cex_psp_drm_patch1                          0x24265C
	#define cex_psp_drm_patch2                          0x2430FC
	#define cex_psp_drm_patch3                          0x242D38
	#define cex_psp_drm_patch4                          0x243544
	#define cex_psp_drm_patchA                          0x242778
	#define cex_psp_drm_patchB                          0x243018
	#define cex_psp_drm_patchC                          0x2421B0
	#define cex_psp_drm_patchD                          0x242760
	#define cex_psp_drm_patchE                          0x242764
	#define cex_psp_drm_patchF                          0x243130
	#define cex_psp_extra_drm_patch                     0x0
#endif

#ifdef FIRMWARE_475C

	#define FIRMWARE_VERSION                                 0x475

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x475
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2E30ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474AF4ULL
		#define PS3MAPI_PSID                                 0x8000000000474B0CULL
	#endif

	/* lv2 */
	#define TOC                                              0x34FBB0
	#define open_shared_kernel_object_symbol                 0x12410
	#define close_kernel_object_handle_symbol                0x11A30
	#define open_kernel_object_symbol                        0x12600
	#define alloc_symbol                                     0x64824
	#define dealloc_symbol                                   0x64C60
	#define copy_to_user_symbol                              0xF86C
	#define copy_from_user_symbol                            0xFA88
	#define copy_to_process_symbol                           0xF924
	#define copy_from_process_symbol                         0xF734
	#define page_allocate_symbol                             0x60394
	#define page_free_symbol                                 0x5FDF8
	#define page_export_to_proc_symbol                       0x60530
	#define page_unexport_from_proc_symbol                   0x5FCEC
	#define kernel_ea_to_lpar_addr_symbol                    0x7014C
	#define map_process_memory_symbol                        0x7726C
	#define memcpy_symbol                                    0x7E92C
	#define memset_symbol                                    0x4D66C
	#define memcmp_symbol                                    0x4C97C
	#define printf_symbol                                    0x2706AC
	#define printfnull_symbol                                0x275120
	#define sprintf_symbol                                   0x4EA94
	#define snprintf_symbol                                  0x4EA00
	#define strcpy_symbol                                    0x4D818
	#define strncpy_symbol                                   0x4D8E0
	#define strlen_symbol                                    0x4D840
	#define strcat_symbol                                    0x4D748
	#define strcmp_symbol                                    0x4D7C4
	#define strncmp_symbol                                   0x4D86C
	#define strchr_symbol                                    0x4D780
	#define spin_lock_irqsave_ex_symbol                      0x26D798
	#define spin_unlock_irqrestore_ex_symbol                 0x26D76C
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x13EC8
	#define ppu_thread_exit_symbol                           0x13F80
	#define ppu_thread_join_symbol                           0x13FD4
	#define ppu_thread_delay_symbol                          0x287A4
	#define create_user_thread2_symbol                       0x25080
	#define start_thread_symbol                              0x23D4C
	#define run_thread_symbol                                0x2357C
	#define register_thread_symbol                           0x26794C
	#define allocate_user_stack_symbol                       0x268134
	#define mutex_create_symbol                              0x1363C
	#define mutex_destroy_symbol                             0x135D4
	#define mutex_lock_symbol                                0x135CC
	#define mutex_unlock_symbol                              0x135C4
	#define event_port_create_symbol                         0x13078
	#define event_port_destroy_symbol                        0x134E0
	#define event_port_connect_symbol                        0x13558
	#define event_port_disconnect_symbol                     0x13484
	#define event_port_send_symbol                           0x13070
	#define event_queue_create_symbol                        0x13380
	#define event_queue_destroy_symbol                       0x13308
	#define event_queue_receive_symbol                       0x1314C
	#define cellFsOpen_symbol                                0x297900
	#define cellFsClose_symbol                               0x297768
	#define cellFsRead_symbol                                0x2978A4
	#define cellFsWrite_symbol                               0x297810
	#define cellFsLseek_symbol                               0x296E98
	#define cellFsStat_symbol                                0x29711C
	#define cellFsUnlink_internal_symbol                     0x19C64C
	#define cellFsUtilMount_symbol                           0x296C78
	#define cellFsUtilUmount_symbol                          0x296C4C
	#define pathdup_from_user_symbol                         0x29C8E4
	#define open_path_symbol                                 0x297638
	#define open_fs_object_symbol                            0x18A970
	#define close_fs_object_symbol                           0x1898AC
	#define storage_get_device_info_symbol                   0x279B00
	#define storage_open_symbol                              0x279510
	#define storage_close_symbol                             0x279300
	#define storage_read_symbol                              0x278870
	#define storage_send_device_command_symbol               0x2783FC
	#define storage_map_io_memory_symbol                     0x2799BC
	#define storage_unmap_io_memory_symbol                   0x279888
	#define storage_internal_get_device_object_symbol        0x277EB4
	#define decrypt_func_symbol                              0x34970
	#define lv1_call_99_wrapper_symbol                       0x4EEA8
	#define modules_verification_symbol                      0x58AB8
	#define prx_load_module_symbol                           0x88C04
	#define prx_start_module_symbol                          0x878D0
	#define prx_stop_module_symbol                           0x88CA8
	#define prx_unload_module_symbol                         0x87604
	#define prx_get_module_info_symbol                       0x8708C
	#define prx_get_module_list_symbol                       0x8710C
	#define extend_kstack_symbol                             0x700A4
	#define get_pseudo_random_number_symbol                  0x228180
	#define syscall_table_symbol                             0x363BE0
	#define syscall_call_offset                              0x275C04
	#define read_bdvd0_symbol                                0x1A461C
	#define read_bdvd1_symbol                                0x1A6248
	#define read_bdvd2_symbol                                0x1B3400
	#define device_event_port_send_call                      0x28206C
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x297A98
	#define fsloop_close_call                                0x297AE8
	#define fsloop_read_call                                 0x297B28
	#define io_rtoc_entry_1                                  0x25B8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0
	#define storage_rtoc_entry_1                             0x1DD8
	#define device_event_rtoc_entry_1                        0x2048
	#define process_rtoc_entry_1                            -0x7800
	#define patch_func2                                      0x59D84
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x203FC
	#define user_thread_prio_patch2                          0x20408
	#define shutdown_patch_offset                            0xAAB8
	#define shutdown_copy_params_call                        0xAACC

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000EC55B
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB378E600056AE1
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001E6C1
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BCE800006477
	#define PSP_EMULATOR_HASH                           0x7BE641F500023794
	#define PEMUCORELIB_HASH                            0xF349A563000C0D66
	#define EMULATOR_API_HASH                           0xA9F5B37A0001BB45
	#define EMULATOR_DRM_HASH                           0xA324DC4A00005399
	#define EMULATOR_DRM_DATA_HASH                      0x75C390860001B75F
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC3B800003212

	/* lv1 */
	#define vsh_pos_in_ram                              0x510000

	/* vsh */
	#define ps2tonet_patch                              0xC4B14
	#define ps2tonet_size_patch                         0xC4B08
	#define vmode_patch_offset                          0x445BEC
	#define psp_drm_patch1                              0x24277C
	#define psp_drm_patch2                              0x24321C
	#define psp_drm_patch3                              0x242E58
	#define psp_drm_patch4                              0x243664
	#define psp_drm_patchA                              0x242898
	#define psp_drm_patchB                              0x243138
	#define psp_drm_patchC                              0x2422D0
	#define psp_drm_patchD                              0x242880
	#define psp_drm_patchE                              0x242884
	#define psp_drm_patchF                              0x243250
	#define psp_extra_drm_patch                         0x2452AC

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDD97C

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x68324

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x17004

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1C18

	/* emulator_api */
	#define psp_read                                    0x102D8
	#define psp_read_header                             0x1125C
	#define psp_drm_patch5                              0x11080
	#define psp_drm_patch6                              0x110B0
	#define psp_drm_patch7                              0x110C8
	#define psp_drm_patch8                              0x110CC
	#define psp_drm_patch9                              0x1120C
	#define psp_drm_patch11                             0x11210
	#define psp_drm_patch12                             0x11220
	#define psp_product_id_patch1                       0x11320
	#define psp_product_id_patch3                       0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6BC
	#define psp_prx_patch                               0x577D8
	#define psp_savedata_bind_patch1                    0x7A4BC
	#define psp_savedata_bind_patch2                    0x7A514
	#define psp_savedata_bind_patch3                    0x7A030
	#define psp_extra_savedata_patch                    0x87540
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46CC
	#define psp_savedata_patch2                         0x46A4
	#define psp_savedata_patch3                         0x4504
	#define psp_savedata_patch4                         0x453C
	#define psp_savedata_patch5                         0x4550
	#define psp_savedata_patch6                         0x46B8

	/* libfs */
	#define aio_copy_root_offset                        0xD658

	/* rebug */
	#define EXPLORE_PLUGIN_REBUG_HASH                   0xACF4AF2B000ECCF7
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH            0x9CB3396E00056CE1
	#define GAME_EXT_PLUGIN_REBUG_HASH                  0xE274AF7B0001E6E8
	#define dex_ps2_nonbw_offset                        0xDDD8C
	#define dex_ps2_nonbw_offset2                       0x68264
	#define dex_ps2_nonbw_offset3                       0x172F4
	#define dex_ps2tonet_patch                          0xCA060
	#define dex_ps2tonet_size_patch                     0xCA054
	#define dex_vmode_patch_offset                      0x44D7E0
	#define dex_psp_drm_patch1                          0x249FA4
	#define dex_psp_drm_patch2                          0x24AA44
	#define dex_psp_drm_patch3                          0x24A680
	#define dex_psp_drm_patch4                          0x24AE8C
	#define dex_psp_drm_patchA                          0x24A0C0
	#define dex_psp_drm_patchB                          0x24A960
	#define dex_psp_drm_patchC                          0x249AF8
	#define dex_psp_drm_patchD                          0x24A0A8
	#define dex_psp_drm_patchE                          0x24A0AC
	#define dex_psp_drm_patchF                          0x24AA78
	#define dex_psp_extra_drm_patch                     0x24CAD4
#endif

#ifdef FIRMWARE_475D

	#define FIRMWARE_VERSION                                 0x475

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x475
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x8000000000409930ULL
		#define PS3MAPI_IDPS_2                               0x800000000049CAF4ULL
		#define PS3MAPI_PSID                                 0x800000000049CB0CULL
	#endif

	/* lv2 */
	#define TOC                                              0x3758E0
	#define open_shared_kernel_object_symbol                 0x12A58
	#define close_kernel_object_handle_symbol                0x12078
	#define open_kernel_object_symbol                        0x12C48
	#define alloc_symbol                                     0x681F4
	#define dealloc_symbol                                   0x68630
	#define copy_to_user_symbol                              0xFEB4
	#define copy_from_user_symbol                            0x100D0
	#define copy_to_process_symbol                           0xFF6C
	#define copy_from_process_symbol                         0xFD7C
	#define page_allocate_symbol                             0x63D64
	#define page_free_symbol                                 0x637C8
	#define page_export_to_proc_symbol                       0x63F00
	#define page_unexport_from_proc_symbol                   0x636BC
	#define kernel_ea_to_lpar_addr_symbol                    0x73C9C
	#define map_process_memory_symbol                        0x7B348
	#define memcpy_symbol                                    0x82A08
	#define memset_symbol                                    0x51014
	#define memcmp_symbol                                    0x50324
	#define printf_symbol                                    0x278978
	#define printfnull_symbol                                0x27D400
	#define sprintf_symbol                                   0x5243C
	#define snprintf_symbol                                  0x523A8
	#define strcpy_symbol                                    0x511C0
	#define strncpy_symbol                                   0x51288
	#define strlen_symbol                                    0x511E8
	#define strcat_symbol                                    0x510F0
	#define strcmp_symbol                                    0x5116C
	#define strncmp_symbol                                   0x51214
	#define strchr_symbol                                    0x51128
	#define spin_lock_irqsave_ex_symbol                      0x275670
	#define spin_unlock_irqrestore_ex_symbol                 0x275644
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x145FC
	#define ppu_thread_exit_symbol                           0x146B4
	#define ppu_thread_join_symbol                           0x14708
	#define ppu_thread_delay_symbol                          0x2A6E8
	#define create_user_thread2_symbol                       0x26D30
	#define start_thread_symbol                              0x25868
	#define run_thread_symbol                                0x2502C
	#define register_thread_symbol                           0x26E270
	#define allocate_user_stack_symbol                       0x26EA58
	#define mutex_create_symbol                              0x13C8C
	#define mutex_destroy_symbol                             0x13C24
	#define mutex_lock_symbol                                0x13C1C
	#define mutex_unlock_symbol                              0x13C14
	#define event_port_create_symbol                         0x136C8
	#define event_port_destroy_symbol                        0x13B30
	#define event_port_connect_symbol                        0x13BA8
	#define event_port_disconnect_symbol                     0x13AD4
	#define event_port_send_symbol                           0x136C0
	#define event_queue_create_symbol                        0x139D0
	#define event_queue_destroy_symbol                       0x13958
	#define event_queue_receive_symbol                       0x1379C
	#define cellFsOpen_symbol                                0x2B27C0
	#define cellFsClose_symbol                               0x2B2628
	#define cellFsRead_symbol                                0x2B2764
	#define cellFsWrite_symbol                               0x2B26D0
	#define cellFsLseek_symbol                               0x2B1F24
	#define cellFsStat_symbol                                0x2B1FDC
	#define cellFsUnlink_internal_symbol                     0x1A29D8
	#define cellFsUtilMount_symbol                           0x2B1C98
	#define cellFsUtilUmount_symbol                          0x2B1C6C
	#define pathdup_from_user_symbol                         0x2B7A84
	#define open_path_symbol                                 0x2B24F8
	#define open_fs_object_symbol                            0x190CFC
	#define close_fs_object_symbol                           0x18FC38
	#define storage_get_device_info_symbol                   0x28CA00
	#define storage_open_symbol                              0x28CC28
	#define storage_close_symbol                             0x28B414
	#define storage_read_symbol                              0x28A390
	#define storage_send_device_command_symbol               0x289EB0
	#define storage_map_io_memory_symbol                     0x28C8AC
	#define storage_unmap_io_memory_symbol                   0x28C768
	#define storage_internal_get_device_object_symbol        0x289968
	#define decrypt_func_symbol                              0x38290
	#define lv1_call_99_wrapper_symbol                       0x52850
	#define modules_verification_symbol                      0x5C488
	#define prx_load_module_symbol                           0x8D308
	#define prx_start_module_symbol                          0x8BFD4
	#define prx_stop_module_symbol                           0x8D3AC
	#define prx_unload_module_symbol                         0x8BD08
	#define prx_get_module_info_symbol                       0x8B700
	#define prx_get_module_list_symbol                       0x8B780
	#define extend_kstack_symbol                             0x73BF4
	#define get_pseudo_random_number_symbol                  0x22E65C
	#define syscall_table_symbol                             0x38A3E8
	#define syscall_call_offset                              0x27DEE4
	#define read_bdvd0_symbol                                0x1AAACC
	#define read_bdvd1_symbol                                0x1AC6F8
	#define read_bdvd2_symbol                                0x1B98B0
	#define device_event_port_send_call                      0x296BFC
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x2B2958
	#define fsloop_close_call                                0x2B29A8
	#define fsloop_read_call                                 0x2B29E8
	#define io_rtoc_entry_1                                  0x2EC0
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65C0
	#define storage_rtoc_entry_1                             0x22B0
	#define device_event_rtoc_entry_1                        0x2638
	#define process_rtoc_entry_1                            -0x77A0
	#define patch_func2                                      0x5D754
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x21EAC
	#define user_thread_prio_patch2                          0x21EB8
	#define shutdown_patch_offset                            0xAB38
	#define shutdown_copy_params_call                        0xAB4C

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000ECCF7
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB3396E00056CE1
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001E6E8
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BCE800006477
	#define PSP_EMULATOR_HASH                           0x7BE641F500023794
	#define PEMUCORELIB_HASH                            0xF349A563000C0D66
	#define EMULATOR_API_HASH                           0xA9F5B37A0001BB45
	#define EMULATOR_DRM_HASH                           0xA324DC4A00005399
	#define EMULATOR_DRM_DATA_HASH                      0x75C390860001B75F
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC3B800003212

	/* lv1 */
	#define vsh_pos_in_ram                              0x510000

	/* vsh */
	#define ps2tonet_patch                              0xCA060
	#define ps2tonet_size_patch                         0xCA054
	#define vmode_patch_offset                          0x44D7E0
	#define psp_drm_patch1                              0x249FA4
	#define psp_drm_patch2                              0x24AA44
	#define psp_drm_patch3                              0x24A680
	#define psp_drm_patch4                              0x24AE8C
	#define psp_drm_patchA                              0x24A0C0
	#define psp_drm_patchB                              0x24A960
	#define psp_drm_patchC                              0x249AF8
	#define psp_drm_patchD                              0x24A0A8
	#define psp_drm_patchE                              0x24A0AC
	#define psp_drm_patchF                              0x24AA78
	#define psp_extra_drm_patch                         0x24CAD4

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDDD8C

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x68264

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x172F4

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1C18

	/* emulator_api */
	#define psp_read                                    0x102D8
	#define psp_read_header                             0x1125C
	#define psp_drm_patch5                              0x11080
	#define psp_drm_patch6                              0x110B0
	#define psp_drm_patch7                              0x110C8
	#define psp_drm_patch8                              0x110CC
	#define psp_drm_patch9                              0x1120C
	#define psp_drm_patch11                             0x11210
	#define psp_drm_patch12                             0x11220
	#define psp_product_id_patch1                       0x11320
	#define psp_product_id_patch3                       0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6BC
	#define psp_prx_patch                               0x577D8
	#define psp_savedata_bind_patch1                    0x7A4BC
	#define psp_savedata_bind_patch2                    0x7A514
	#define psp_savedata_bind_patch3                    0x7A030
	#define psp_extra_savedata_patch                    0x87540
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46CC
	#define psp_savedata_patch2                         0x46A4
	#define psp_savedata_patch3                         0x4504
	#define psp_savedata_patch4                         0x453C
	#define psp_savedata_patch5                         0x4550
	#define psp_savedata_patch6                         0x46B8

	/* libfs */
	#define aio_copy_root_offset                        0xD658

	/* CEX */
	#define cex_ps2tonet_patch                          0xC4B14
	#define cex_ps2tonet_size_patch                     0xC4B08
	#define cex_vmode_patch_offset                      0x445BEC
	#define cex_psp_drm_patch1                          0x24277C
	#define cex_psp_drm_patch2                          0x24321C
	#define cex_psp_drm_patch3                          0x242E58
	#define cex_psp_drm_patch4                          0x243664
	#define cex_psp_drm_patchA                          0x242898
	#define cex_psp_drm_patchB                          0x243138
	#define cex_psp_drm_patchC                          0x2422D0
	#define cex_psp_drm_patchD                          0x242880
	#define cex_psp_drm_patchE                          0x242884
	#define cex_psp_drm_patchF                          0x243250
	#define cex_psp_extra_drm_patch                     0x2452AC
#endif

#ifdef FIRMWARE_476C

	#define FIRMWARE_VERSION                                 0x476

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x476
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2E30ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474AF4ULL
		#define PS3MAPI_PSID                                 0x8000000000474B0CULL
	#endif

	/* lv2 */
	#define TOC                                              0x34FBB0
	#define open_shared_kernel_object_symbol                 0x12410
	#define close_kernel_object_handle_symbol                0x11A30
	#define open_kernel_object_symbol                        0x12600
	#define alloc_symbol                                     0x64824
	#define dealloc_symbol                                   0x64C60
	#define copy_to_user_symbol                              0xF86C
	#define copy_from_user_symbol                            0xFA88
	#define copy_to_process_symbol                           0xF924
	#define copy_from_process_symbol                         0xF734
	#define page_allocate_symbol                             0x60394
	#define page_free_symbol                                 0x5FDF8
	#define page_export_to_proc_symbol                       0x60530
	#define page_unexport_from_proc_symbol                   0x5FCEC
	#define kernel_ea_to_lpar_addr_symbol                    0x7014C
	#define map_process_memory_symbol                        0x7726C
	#define memcpy_symbol                                    0x7E92C
	#define memset_symbol                                    0x4D66C
	#define memcmp_symbol                                    0x4C97C
	#define printf_symbol                                    0x2706AC
	#define printfnull_symbol                                0x275120
	#define sprintf_symbol                                   0x4EA94
	#define snprintf_symbol                                  0x4EA00
	#define strcpy_symbol                                    0x4D818
	#define strncpy_symbol                                   0x4D8E0
	#define strlen_symbol                                    0x4D840
	#define strcat_symbol                                    0x4D748
	#define strcmp_symbol                                    0x4D7C4
	#define strncmp_symbol                                   0x4D86C
	#define strchr_symbol                                    0x4D780
	#define spin_lock_irqsave_ex_symbol                      0x26D798
	#define spin_unlock_irqrestore_ex_symbol                 0x26D76C
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x13EC8
	#define ppu_thread_exit_symbol                           0x13F80
	#define ppu_thread_join_symbol                           0x13FD4
	#define ppu_thread_delay_symbol                          0x287A4
	#define create_user_thread2_symbol                       0x25080
	#define start_thread_symbol                              0x23D4C
	#define run_thread_symbol                                0x2357C
	#define register_thread_symbol                           0x26794C
	#define allocate_user_stack_symbol                       0x268134
	#define mutex_create_symbol                              0x1363C
	#define mutex_destroy_symbol                             0x135D4
	#define mutex_lock_symbol                                0x135CC
	#define mutex_unlock_symbol                              0x135C4
	#define event_port_create_symbol                         0x13078
	#define event_port_destroy_symbol                        0x134E0
	#define event_port_connect_symbol                        0x13558
	#define event_port_disconnect_symbol                     0x13484
	#define event_port_send_symbol                           0x13070
	#define event_queue_create_symbol                        0x13380
	#define event_queue_destroy_symbol                       0x13308
	#define event_queue_receive_symbol                       0x1314C
	#define cellFsOpen_symbol                                0x297900
	#define cellFsClose_symbol                               0x297768
	#define cellFsRead_symbol                                0x2978A4
	#define cellFsWrite_symbol                               0x297810
	#define cellFsLseek_symbol                               0x296E98
	#define cellFsStat_symbol                                0x29711C
	#define cellFsUnlink_internal_symbol                     0x19C64C
	#define cellFsUtilMount_symbol                           0x296C78
	#define cellFsUtilUmount_symbol                          0x296C4C
	#define pathdup_from_user_symbol                         0x29C8E4
	#define open_path_symbol                                 0x297638
	#define open_fs_object_symbol                            0x18A970
	#define close_fs_object_symbol                           0x1898AC
	#define storage_get_device_info_symbol                   0x279B00
	#define storage_open_symbol                              0x279510
	#define storage_close_symbol                             0x279300
	#define storage_read_symbol                              0x278870
	#define storage_send_device_command_symbol               0x2783FC
	#define storage_map_io_memory_symbol                     0x2799BC
	#define storage_unmap_io_memory_symbol                   0x279888
	#define storage_internal_get_device_object_symbol        0x277EB4
	#define decrypt_func_symbol                              0x34970
	#define lv1_call_99_wrapper_symbol                       0x4EEA8
	#define modules_verification_symbol                      0x58AB8
	#define prx_load_module_symbol                           0x88C04
	#define prx_start_module_symbol                          0x878D0
	#define prx_stop_module_symbol                           0x88CA8
	#define prx_unload_module_symbol                         0x87604
	#define prx_get_module_info_symbol                       0x8708C
	#define prx_get_module_list_symbol                       0x8710C
	#define extend_kstack_symbol                             0x700A4
	#define get_pseudo_random_number_symbol                  0x228180
	#define syscall_table_symbol                             0x363BE0
	#define syscall_call_offset                              0x275C04
	#define read_bdvd0_symbol                                0x1A461C
	#define read_bdvd1_symbol                                0x1A6248
	#define read_bdvd2_symbol                                0x1B3400
	#define device_event_port_send_call                      0x28206C
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x297A98
	#define fsloop_close_call                                0x297AE8
	#define fsloop_read_call                                 0x297B28
	#define io_rtoc_entry_1                                  0x25B8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0
	#define storage_rtoc_entry_1                             0x1DD8
	#define device_event_rtoc_entry_1                        0x2048
	#define process_rtoc_entry_1                            -0x7800
	#define patch_func2                                      0x59D84
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x203FC
	#define user_thread_prio_patch2                          0x20408
	#define shutdown_patch_offset                            0xAAB8
	#define shutdown_copy_params_call                        0xAACC

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000EC55B
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB378E600056AE1
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001E6C1
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BCE800006477
	#define PSP_EMULATOR_HASH                           0x7BE641F500023793
	#define PEMUCORELIB_HASH                            0xF349A563000C0D66
	#define EMULATOR_API_HASH                           0xA9F5B37A0001BB45
	#define EMULATOR_DRM_HASH                           0xA324DC4A00005399
	#define EMULATOR_DRM_DATA_HASH                      0x75C390860001B75F
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC3B800003212

	/* lv1 */
	#define vsh_pos_in_ram                              0x510000

	/* vsh */
	#define ps2tonet_patch                              0xC4B14
	#define ps2tonet_size_patch                         0xC4B08
	#define vmode_patch_offset                          0x445BEC
	#define psp_drm_patch1                              0x24277C
	#define psp_drm_patch2                              0x24321C
	#define psp_drm_patch3                              0x242E58
	#define psp_drm_patch4                              0x243664
	#define psp_drm_patchA                              0x242898
	#define psp_drm_patchB                              0x243138
	#define psp_drm_patchC                              0x2422D0
	#define psp_drm_patchD                              0x242880
	#define psp_drm_patchE                              0x242884
	#define psp_drm_patchF                              0x243250
	#define psp_extra_drm_patch                         0x2452AC

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDD97C

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x68324

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x17004

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1C18

	/* emulator_api */
	#define psp_read                                    0x102D8
	#define psp_read_header                             0x1125C
	#define psp_drm_patch5                              0x11080
	#define psp_drm_patch6                              0x110B0
	#define psp_drm_patch7                              0x110C8
	#define psp_drm_patch8                              0x110CC
	#define psp_drm_patch9                              0x1120C
	#define psp_drm_patch11                             0x11210
	#define psp_drm_patch12                             0x11220
	#define psp_product_id_patch1                       0x11320
	#define psp_product_id_patch3                       0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6BC
	#define psp_prx_patch                               0x577D8
	#define psp_savedata_bind_patch1                    0x7A4BC
	#define psp_savedata_bind_patch2                    0x7A514
	#define psp_savedata_bind_patch3                    0x7A030
	#define psp_extra_savedata_patch                    0x87540
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46CC
	#define psp_savedata_patch2                         0x46A4
	#define psp_savedata_patch3                         0x4504
	#define psp_savedata_patch4                         0x453C
	#define psp_savedata_patch5                         0x4550
	#define psp_savedata_patch6                         0x46B8

	/* libfs */
	#define aio_copy_root_offset                        0xD658

	/* rebug */
	#define EXPLORE_PLUGIN_REBUG_HASH                   0xACF4AF2B000ECCF8
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH            0x9CB3396E00056CE1
	#define GAME_EXT_PLUGIN_REBUG_HASH                  0xE274AF7B0001E6E8
	#define dex_ps2_nonbw_offset                        0xDDD8C
	#define dex_ps2_nonbw_offset2                       0x68264
	#define dex_ps2_nonbw_offset3                       0x172F4
	#define dex_ps2tonet_patch                          0xCA060
	#define dex_ps2tonet_size_patch                     0xCA054
	#define dex_vmode_patch_offset                      0x44D7E0
	#define dex_psp_drm_patch1                          0x249FA4
	#define dex_psp_drm_patch2                          0x24AA44
	#define dex_psp_drm_patch3                          0x24A680
	#define dex_psp_drm_patch4                          0x24AE8C
	#define dex_psp_drm_patchA                          0x24A0C0
	#define dex_psp_drm_patchB                          0x24A960
	#define dex_psp_drm_patchC                          0x249AF8
	#define dex_psp_drm_patchD                          0x24A0A8
	#define dex_psp_drm_patchE                          0x24A0AC
	#define dex_psp_drm_patchF                          0x24AA78
	#define dex_psp_extra_drm_patch                     0x24CAD4
#endif

#ifdef FIRMWARE_476D

	#define FIRMWARE_VERSION                                 0x476

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x476
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x8000000000409930ULL
		#define PS3MAPI_IDPS_2                               0x800000000049CAF4ULL
		#define PS3MAPI_PSID                                 0x800000000049CB0CULL
	#endif

	/* lv2 */
	#define TOC                                              0x3758E0
	#define open_shared_kernel_object_symbol                 0x12A58
	#define close_kernel_object_handle_symbol                0x12078
	#define open_kernel_object_symbol                        0x12C48
	#define alloc_symbol                                     0x681F4
	#define dealloc_symbol                                   0x68630
	#define copy_to_user_symbol                              0xFEB4
	#define copy_from_user_symbol                            0x100D0
	#define copy_to_process_symbol                           0xFF6C
	#define copy_from_process_symbol                         0xFD7C
	#define page_allocate_symbol                             0x63D64
	#define page_free_symbol                                 0x637C8
	#define page_export_to_proc_symbol                       0x63F00
	#define page_unexport_from_proc_symbol                   0x636BC
	#define kernel_ea_to_lpar_addr_symbol                    0x73C9C
	#define map_process_memory_symbol                        0x7B348
	#define memcpy_symbol                                    0x82A08
	#define memset_symbol                                    0x51014
	#define memcmp_symbol                                    0x50324
	#define printf_symbol                                    0x278978
	#define printfnull_symbol                                0x27D400
	#define sprintf_symbol                                   0x5243C
	#define snprintf_symbol                                  0x523A8
	#define strcpy_symbol                                    0x511C0
	#define strncpy_symbol                                   0x51288
	#define strlen_symbol                                    0x511E8
	#define strcat_symbol                                    0x510F0
	#define strcmp_symbol                                    0x5116C
	#define strncmp_symbol                                   0x51214
	#define strchr_symbol                                    0x51128
	#define spin_lock_irqsave_ex_symbol                      0x275670
	#define spin_unlock_irqrestore_ex_symbol                 0x275644
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x145FC
	#define ppu_thread_exit_symbol                           0x146B4
	#define ppu_thread_join_symbol                           0x14708
	#define ppu_thread_delay_symbol                          0x2A6E8
	#define create_user_thread2_symbol                       0x26D30
	#define start_thread_symbol                              0x25868
	#define run_thread_symbol                                0x2502C
	#define register_thread_symbol                           0x26E270
	#define allocate_user_stack_symbol                       0x26EA58
	#define mutex_create_symbol                              0x13C8C
	#define mutex_destroy_symbol                             0x13C24
	#define mutex_lock_symbol                                0x13C1C
	#define mutex_unlock_symbol                              0x13C14
	#define event_port_create_symbol                         0x136C8
	#define event_port_destroy_symbol                        0x13B30
	#define event_port_connect_symbol                        0x13BA8
	#define event_port_disconnect_symbol                     0x13AD4
	#define event_port_send_symbol                           0x136C0
	#define event_queue_create_symbol                        0x139D0
	#define event_queue_destroy_symbol                       0x13958
	#define event_queue_receive_symbol                       0x1379C
	#define cellFsOpen_symbol                                0x2B27C0
	#define cellFsClose_symbol                               0x2B2628
	#define cellFsRead_symbol                                0x2B2764
	#define cellFsWrite_symbol                               0x2B26D0
	#define cellFsLseek_symbol                               0x2B1F24
	#define cellFsStat_symbol                                0x2B1FDC
	#define cellFsUnlink_internal_symbol                     0x1A29D8
	#define cellFsUtilMount_symbol                           0x2B1C98
	#define cellFsUtilUmount_symbol                          0x2B1C6C
	#define pathdup_from_user_symbol                         0x2B7A84
	#define open_path_symbol                                 0x2B24F8
	#define open_fs_object_symbol                            0x190CFC
	#define close_fs_object_symbol                           0x18FC38
	#define storage_get_device_info_symbol                   0x28CA00
	#define storage_open_symbol                              0x28CC28
	#define storage_close_symbol                             0x28B414
	#define storage_read_symbol                              0x28A390
	#define storage_send_device_command_symbol               0x289EB0
	#define storage_map_io_memory_symbol                     0x28C8AC
	#define storage_unmap_io_memory_symbol                   0x28C768
	#define storage_internal_get_device_object_symbol        0x289968
	#define decrypt_func_symbol                              0x38290
	#define lv1_call_99_wrapper_symbol                       0x52850
	#define modules_verification_symbol                      0x5C488
	#define prx_load_module_symbol                           0x8D308
	#define prx_start_module_symbol                          0x8BFD4
	#define prx_stop_module_symbol                           0x8D3AC
	#define prx_unload_module_symbol                         0x8BD08
	#define prx_get_module_info_symbol                       0x8B700
	#define prx_get_module_list_symbol                       0x8B780
	#define extend_kstack_symbol                             0x73BF4
	#define get_pseudo_random_number_symbol                  0x22E65C
	#define syscall_table_symbol                             0x38A3E8
	#define syscall_call_offset                              0x27DEE4
	#define read_bdvd0_symbol                                0x1AAACC
	#define read_bdvd1_symbol                                0x1AC6F8
	#define read_bdvd2_symbol                                0x1B98B0
	#define device_event_port_send_call                      0x296BFC
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x2B2958
	#define fsloop_close_call                                0x2B29A8
	#define fsloop_read_call                                 0x2B29E8
	#define io_rtoc_entry_1                                  0x2EC0
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65C0
	#define storage_rtoc_entry_1                             0x22B0
	#define device_event_rtoc_entry_1                        0x2638
	#define process_rtoc_entry_1                            -0x77A0
	#define patch_func2                                      0x5D754
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x21EAC
	#define user_thread_prio_patch2                          0x21EB8
	#define shutdown_patch_offset                            0xAB38
	#define shutdown_copy_params_call                        0xAB4C

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000ECCF8
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB3396E00056CE1
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001E6E8
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BCE800006477
	#define PSP_EMULATOR_HASH                           0x7BE641F500023793
	#define PEMUCORELIB_HASH                            0xF349A563000C0D66
	#define EMULATOR_API_HASH                           0xA9F5B37A0001BB45
	#define EMULATOR_DRM_HASH                           0xA324DC4A00005399
	#define EMULATOR_DRM_DATA_HASH                      0x75C390860001B75F
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC3B800003212

	/* lv1 */
	#define vsh_pos_in_ram                              0x910000

	/* vsh */
	#define ps2tonet_patch                              0xCA060
	#define ps2tonet_size_patch                         0xCA054
	#define vmode_patch_offset                          0x44D7E0
	#define psp_drm_patch1                              0x249FA4
	#define psp_drm_patch2                              0x24AA44
	#define psp_drm_patch3                              0x24A680
	#define psp_drm_patch4                              0x24AE8C
	#define psp_drm_patchA                              0x24A0C0
	#define psp_drm_patchB                              0x24A960
	#define psp_drm_patchC                              0x249AF8
	#define psp_drm_patchD                              0x24A0A8
	#define psp_drm_patchE                              0x24A0AC
	#define psp_drm_patchF                              0x24AA78
	#define psp_extra_drm_patch                         0x24CAD4

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDDD8C

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x68264

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x172F4

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1C18

	/* emulator_api */
	#define psp_read                                    0x102D8
	#define psp_read_header                             0x1125C
	#define psp_drm_patch5                              0x11080
	#define psp_drm_patch6                              0x110B0
	#define psp_drm_patch7                              0x110C8
	#define psp_drm_patch8                              0x110CC
	#define psp_drm_patch9                              0x1120C
	#define psp_drm_patch11                             0x11210
	#define psp_drm_patch12                             0x11220
	#define psp_product_id_patch1                       0x11320
	#define psp_product_id_patch3                       0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6BC
	#define psp_prx_patch                               0x577D8
	#define psp_savedata_bind_patch1                    0x7A4BC
	#define psp_savedata_bind_patch2                    0x7A514
	#define psp_savedata_bind_patch3                    0x7A030
	#define psp_extra_savedata_patch                    0x87540
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46CC
	#define psp_savedata_patch2                         0x46A4
	#define psp_savedata_patch3                         0x4504
	#define psp_savedata_patch4                         0x453C
	#define psp_savedata_patch5                         0x4550
	#define psp_savedata_patch6                         0x46B8

	/* libfs */
	#define aio_copy_root_offset                        0xD658

	/* CEX */
	#define cex_ps2tonet_patch                          0xC4B14
	#define cex_ps2tonet_size_patch                     0xC4B08
	#define cex_vmode_patch_offset                      0x445BEC
	#define cex_psp_drm_patch1                          0x24277C
	#define cex_psp_drm_patch2                          0x24321C
	#define cex_psp_drm_patch3                          0x242E58
	#define cex_psp_drm_patch4                          0x243664
	#define cex_psp_drm_patchA                          0x242898
	#define cex_psp_drm_patchB                          0x243138
	#define cex_psp_drm_patchC                          0x2422D0
	#define cex_psp_drm_patchD                          0x242880
	#define cex_psp_drm_patchE                          0x242884
	#define cex_psp_drm_patchF                          0x243250
	#define cex_psp_extra_drm_patch                     0x2452AC
#endif

#ifdef FIRMWARE_478C

	#define FIRMWARE_VERSION                                 0x478

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x478
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2E30ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474AF4ULL
		#define PS3MAPI_PSID                                 0x8000000000474B0CULL
	#endif

	/* lv2 */
	#define TOC                                              0x34FBB0
	#define open_shared_kernel_object_symbol                 0x12410
	#define close_kernel_object_handle_symbol                0x11A30
	#define open_kernel_object_symbol                        0x12600
	#define alloc_symbol                                     0x64824
	#define dealloc_symbol                                   0x64C60
	#define copy_to_user_symbol                              0xF86C
	#define copy_from_user_symbol                            0xFA88
	#define copy_to_process_symbol                           0xF924
	#define copy_from_process_symbol                         0xF734
	#define page_allocate_symbol                             0x60394
	#define page_free_symbol                                 0x5FDF8
	#define page_export_to_proc_symbol                       0x60530
	#define page_unexport_from_proc_symbol                   0x5FCEC
	#define kernel_ea_to_lpar_addr_symbol                    0x7014C
	#define map_process_memory_symbol                        0x7726C
	#define memcpy_symbol                                    0x7E92C
	#define memset_symbol                                    0x4D66C
	#define memcmp_symbol                                    0x4C97C
	#define printf_symbol                                    0x2706AC
	#define printfnull_symbol                                0x275120
	#define sprintf_symbol                                   0x4EA94
	#define snprintf_symbol                                  0x4EA00
	#define strcpy_symbol                                    0x4D818
	#define strncpy_symbol                                   0x4D8E0
	#define strlen_symbol                                    0x4D840
	#define strcat_symbol                                    0x4D748
	#define strcmp_symbol                                    0x4D7C4
	#define strncmp_symbol                                   0x4D86C
	#define strchr_symbol                                    0x4D780
	#define spin_lock_irqsave_ex_symbol                      0x26D798
	#define spin_unlock_irqrestore_ex_symbol                 0x26D76C
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x13EC8
	#define ppu_thread_exit_symbol                           0x13F80
	#define ppu_thread_join_symbol                           0x13FD4
	#define ppu_thread_delay_symbol                          0x287A4
	#define create_user_thread2_symbol                       0x25080
	#define start_thread_symbol                              0x23D4C
	#define run_thread_symbol                                0x2357C
	#define register_thread_symbol                           0x26794C
	#define allocate_user_stack_symbol                       0x268134
	#define mutex_create_symbol                              0x1363C
	#define mutex_destroy_symbol                             0x135D4
	#define mutex_lock_symbol                                0x135CC
	#define mutex_unlock_symbol                              0x135C4
	#define event_port_create_symbol                         0x13078
	#define event_port_destroy_symbol                        0x134E0
	#define event_port_connect_symbol                        0x13558
	#define event_port_disconnect_symbol                     0x13484
	#define event_port_send_symbol                           0x13070
	#define event_queue_create_symbol                        0x13380
	#define event_queue_destroy_symbol                       0x13308
	#define event_queue_receive_symbol                       0x1314C
	#define cellFsOpen_symbol                                0x297900
	#define cellFsClose_symbol                               0x297768
	#define cellFsRead_symbol                                0x2978A4
	#define cellFsWrite_symbol                               0x297810
	#define cellFsLseek_symbol                               0x296E98
	#define cellFsStat_symbol                                0x29711C
	#define cellFsUnlink_internal_symbol                     0x19C64C
	#define cellFsUtilMount_symbol                           0x296C78
	#define cellFsUtilUmount_symbol                          0x296C4C
	#define pathdup_from_user_symbol                         0x29C8E4
	#define open_path_symbol                                 0x297638
	#define open_fs_object_symbol                            0x18A970
	#define close_fs_object_symbol                           0x1898AC
	#define storage_get_device_info_symbol                   0x279B00
	#define storage_open_symbol                              0x279510
	#define storage_close_symbol                             0x279300
	#define storage_read_symbol                              0x278870
	#define storage_send_device_command_symbol               0x2783FC
	#define storage_map_io_memory_symbol                     0x2799BC
	#define storage_unmap_io_memory_symbol                   0x279888
	#define storage_internal_get_device_object_symbol        0x277EB4
	#define decrypt_func_symbol                              0x34970
	#define lv1_call_99_wrapper_symbol                       0x4EEA8
	#define modules_verification_symbol                      0x58AB8
	#define prx_load_module_symbol                           0x88C04
	#define prx_start_module_symbol                          0x878D0
	#define prx_stop_module_symbol                           0x88CA8
	#define prx_unload_module_symbol                         0x87604
	#define prx_get_module_info_symbol                       0x8708C
	#define prx_get_module_list_symbol                       0x8710C
	#define extend_kstack_symbol                             0x700A4
	#define get_pseudo_random_number_symbol                  0x228180
	#define syscall_table_symbol                             0x363BE0
	#define syscall_call_offset                              0x275C04
	#define read_bdvd0_symbol                                0x1A461C
	#define read_bdvd1_symbol                                0x1A6248
	#define read_bdvd2_symbol                                0x1B3400
	#define device_event_port_send_call                      0x28206C
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x297A98
	#define fsloop_close_call                                0x297AE8
	#define fsloop_read_call                                 0x297B28
	#define io_rtoc_entry_1                                  0x25B8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0
	#define storage_rtoc_entry_1                             0x1DD8
	#define device_event_rtoc_entry_1                        0x2048
	#define process_rtoc_entry_1                            -0x7800
	#define patch_func2                                      0x59D84
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x203FC
	#define user_thread_prio_patch2                          0x20408
	#define shutdown_patch_offset                            0xAAB8
	#define shutdown_copy_params_call                        0xAACC

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000EC41A
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB378E600056AE1
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001E6C1
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BCE800006477
	#define PSP_EMULATOR_HASH                           0x7BE641F500023793
	#define PEMUCORELIB_HASH                            0xF349A563000C0D66
	#define EMULATOR_API_HASH                           0xA9F5B37A0001BB45
	#define EMULATOR_DRM_HASH                           0xA324DC4A00005399
	#define EMULATOR_DRM_DATA_HASH                      0x75C390860001B75F
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC3B800003212

	/* lv1 */
	#define vsh_pos_in_ram                              0x510000

	/* vsh */
	#define ps2tonet_patch                              0xC4B14
	#define ps2tonet_size_patch                         0xC4B08
	#define vmode_patch_offset                          0x442E5C
	#define psp_drm_patch1                              0x242C74
	#define psp_drm_patch2                              0x243714
	#define psp_drm_patch3                              0x243350
	#define psp_drm_patch4                              0x243B5C
	#define psp_drm_patchA                              0x242D90
	#define psp_drm_patchB                              0x243630
	#define psp_drm_patchC                              0x2427C8
	#define psp_drm_patchD                              0x242D78
	#define psp_drm_patchE                              0x242D7C
	#define psp_drm_patchF                              0x243748
	#define psp_extra_drm_patch                         0x2457A4

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDD9B4

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x68324

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x17004

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1C18

	/* emulator_api */
	#define psp_read                                    0x102D8
	#define psp_read_header                             0x1125C
	#define psp_drm_patch5                              0x11080
	#define psp_drm_patch6                              0x110B0
	#define psp_drm_patch7                              0x110C8
	#define psp_drm_patch8                              0x110CC
	#define psp_drm_patch9                              0x1120C
	#define psp_drm_patch11                             0x11210
	#define psp_drm_patch12                             0x11220
	#define psp_product_id_patch1                       0x11320
	#define psp_product_id_patch3                       0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6BC
	#define psp_prx_patch                               0x577D8
	#define psp_savedata_bind_patch1                    0x7A4BC
	#define psp_savedata_bind_patch2                    0x7A514
	#define psp_savedata_bind_patch3                    0x7A030
	#define psp_extra_savedata_patch                    0x87540
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46CC
	#define psp_savedata_patch2                         0x46A4
	#define psp_savedata_patch3                         0x4504
	#define psp_savedata_patch4                         0x453C
	#define psp_savedata_patch5                         0x4550
	#define psp_savedata_patch6                         0x46B8

	/* libfs */
	#define aio_copy_root_offset                        0xD658

	/* rebug */
	#define EXPLORE_PLUGIN_REBUG_HASH                   0xACF4AF2B000ECCFD
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH            0x9CB3396E00056CE1
	#define GAME_EXT_PLUGIN_REBUG_HASH                  0xE274AF7B0001E6E8
	#define dex_ps2_nonbw_offset                        0xDDDC4
	#define dex_ps2_nonbw_offset2                       0x68264
	#define dex_ps2_nonbw_offset3                       0x172F4
	#define dex_ps2tonet_patch                          0xCA060
	#define dex_ps2tonet_size_patch                     0xCA054
	#define dex_vmode_patch_offset                      0x44AA50
	#define dex_psp_drm_patch1                          0x24A49C
	#define dex_psp_drm_patch2                          0x24AF3C
	#define dex_psp_drm_patch3                          0x24AB78
	#define dex_psp_drm_patch4                          0x24B384
	#define dex_psp_drm_patchA                          0x24A5B8
	#define dex_psp_drm_patchB                          0x24AE58
	#define dex_psp_drm_patchC                          0x249FF0
	#define dex_psp_drm_patchD                          0x24A5A0
	#define dex_psp_drm_patchE                          0x24A5A4
	#define dex_psp_drm_patchF                          0x24AF70
	#define dex_psp_extra_drm_patch                     0x24CFCC
#endif

#ifdef FIRMWARE_478D

	#define FIRMWARE_VERSION                                 0x478

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x478
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x8000000000409930ULL
		#define PS3MAPI_IDPS_2                               0x800000000049CAF4ULL
		#define PS3MAPI_PSID                                 0x800000000049CB0CULL
	#endif

	/* lv2 */
	#define TOC                                              0x3758E0
	#define open_shared_kernel_object_symbol                 0x12A58
	#define close_kernel_object_handle_symbol                0x12078
	#define open_kernel_object_symbol                        0x12C48
	#define alloc_symbol                                     0x681F4
	#define dealloc_symbol                                   0x68630
	#define copy_to_user_symbol                              0xFEB4
	#define copy_from_user_symbol                            0x100D0
	#define copy_to_process_symbol                           0xFF6C
	#define copy_from_process_symbol                         0xFD7C
	#define page_allocate_symbol                             0x63D64
	#define page_free_symbol                                 0x637C8
	#define page_export_to_proc_symbol                       0x63F00
	#define page_unexport_from_proc_symbol                   0x636BC
	#define kernel_ea_to_lpar_addr_symbol                    0x73C9C
	#define map_process_memory_symbol                        0x7B348
	#define memcpy_symbol                                    0x82A08
	#define memset_symbol                                    0x51014
	#define memcmp_symbol                                    0x50324
	#define printf_symbol                                    0x278978
	#define printfnull_symbol                                0x27D400
	#define sprintf_symbol                                   0x5243C
	#define snprintf_symbol                                  0x523A8
	#define strcpy_symbol                                    0x511C0
	#define strncpy_symbol                                   0x51288
	#define strlen_symbol                                    0x511E8
	#define strcat_symbol                                    0x510F0
	#define strcmp_symbol                                    0x5116C
	#define strncmp_symbol                                   0x51214
	#define strchr_symbol                                    0x51128
	#define spin_lock_irqsave_ex_symbol                      0x275670
	#define spin_unlock_irqrestore_ex_symbol                 0x275644
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x145FC
	#define ppu_thread_exit_symbol                           0x146B4
	#define ppu_thread_join_symbol                           0x14708
	#define ppu_thread_delay_symbol                          0x2A6E8
	#define create_user_thread2_symbol                       0x26D30
	#define start_thread_symbol                              0x25868
	#define run_thread_symbol                                0x2502C
	#define register_thread_symbol                           0x26E270
	#define allocate_user_stack_symbol                       0x26EA58
	#define mutex_create_symbol                              0x13C8C
	#define mutex_destroy_symbol                             0x13C24
	#define mutex_lock_symbol                                0x13C1C
	#define mutex_unlock_symbol                              0x13C14
	#define event_port_create_symbol                         0x136C8
	#define event_port_destroy_symbol                        0x13B30
	#define event_port_connect_symbol                        0x13BA8
	#define event_port_disconnect_symbol                     0x13AD4
	#define event_port_send_symbol                           0x136C0
	#define event_queue_create_symbol                        0x139D0
	#define event_queue_destroy_symbol                       0x13958
	#define event_queue_receive_symbol                       0x1379C
	#define cellFsOpen_symbol                                0x2B27C0
	#define cellFsClose_symbol                               0x2B2628
	#define cellFsRead_symbol                                0x2B2764
	#define cellFsWrite_symbol                               0x2B26D0
	#define cellFsLseek_symbol                               0x2B1F24
	#define cellFsStat_symbol                                0x2B1FDC
	#define cellFsUnlink_internal_symbol                     0x1A29D8
	#define cellFsUtilMount_symbol                           0x2B1C98
	#define cellFsUtilUmount_symbol                          0x2B1C6C
	#define pathdup_from_user_symbol                         0x2B7A84
	#define open_path_symbol                                 0x2B24F8
	#define open_fs_object_symbol                            0x190CFC
	#define close_fs_object_symbol                           0x18FC38
	#define storage_get_device_info_symbol                   0x28CA00
	#define storage_open_symbol                              0x28CC28
	#define storage_close_symbol                             0x28B414
	#define storage_read_symbol                              0x28A390
	#define storage_send_device_command_symbol               0x289EB0
	#define storage_map_io_memory_symbol                     0x28C8AC
	#define storage_unmap_io_memory_symbol                   0x28C768
	#define storage_internal_get_device_object_symbol        0x289968
	#define decrypt_func_symbol                              0x38290
	#define lv1_call_99_wrapper_symbol                       0x52850
	#define modules_verification_symbol                      0x5C488
	#define prx_load_module_symbol                           0x8D308
	#define prx_start_module_symbol                          0x8BFD4
	#define prx_stop_module_symbol                           0x8D3AC
	#define prx_unload_module_symbol                         0x8BD08
	#define prx_get_module_info_symbol                       0x8B700
	#define prx_get_module_list_symbol                       0x8B780
	#define extend_kstack_symbol                             0x73BF4
	#define get_pseudo_random_number_symbol                  0x22E65C
	#define syscall_table_symbol                             0x3D01B8
	#define syscall_call_offset                              0x27DEE4
	#define read_bdvd0_symbol                                0x1AAACC
	#define read_bdvd1_symbol                                0x1AC6F8
	#define read_bdvd2_symbol                                0x1B98B0
	#define device_event_port_send_call                      0x296BFC
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x2B2958
	#define fsloop_close_call                                0x2B29A8
	#define fsloop_read_call                                 0x2B29E8
	#define io_rtoc_entry_1                                  0x2EC0
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65C0
	#define storage_rtoc_entry_1                             0x22B0
	#define device_event_rtoc_entry_1                        0x2638
	#define process_rtoc_entry_1                            -0x77A0
	#define patch_func2                                      0x5D754
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x21EAC
	#define user_thread_prio_patch2                          0x21EB8
	#define shutdown_patch_offset                            0xAB38
	#define shutdown_copy_params_call                        0xAB4C

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000ECCFD
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB3396E00056CE1
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001E6E8
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BCE800006477
	#define PSP_EMULATOR_HASH                           0x7BE641F500023793
	#define PEMUCORELIB_HASH                            0xF349A563000C0D66
	#define EMULATOR_API_HASH                           0xA9F5B37A0001BB45
	#define EMULATOR_DRM_HASH                           0xA324DC4A00005399
	#define EMULATOR_DRM_DATA_HASH                      0x75C390860001B75F
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC3B800003212

	/* lv1 */
	#define vsh_pos_in_ram                              0x910000

	/* vsh */
	#define ps2tonet_patch                              0xCA060
	#define ps2tonet_size_patch                         0xCA054
	#define vmode_patch_offset                          0x44AA50
	#define psp_drm_patch1                              0x24A49C
	#define psp_drm_patch2                              0x24AF3C
	#define psp_drm_patch3                              0x24AB78
	#define psp_drm_patch4                              0x24B384
	#define psp_drm_patchA                              0x24A5B8
	#define psp_drm_patchB                              0x24AE58
	#define psp_drm_patchC                              0x249FF0
	#define psp_drm_patchD                              0x24A5A0
	#define psp_drm_patchE                              0x24A5A4
	#define psp_drm_patchF                              0x24AF70
	#define psp_extra_drm_patch                         0x24CFCC

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDDDC4

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x68264

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x172F4

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1C18

	/* emulator_api */
	#define psp_read                                    0x102D8
	#define psp_read_header                             0x1125C
	#define psp_drm_patch5                              0x11080
	#define psp_drm_patch6                              0x110B0
	#define psp_drm_patch7                              0x110C8
	#define psp_drm_patch8                              0x110CC
	#define psp_drm_patch9                              0x1120C
	#define psp_drm_patch11                             0x11210
	#define psp_drm_patch12                             0x11220
	#define psp_product_id_patch1                       0x11320
	#define psp_product_id_patch3                       0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6BC
	#define psp_prx_patch                               0x577D8
	#define psp_savedata_bind_patch1                    0x7A4BC
	#define psp_savedata_bind_patch2                    0x7A514
	#define psp_savedata_bind_patch3                    0x7A030
	#define psp_extra_savedata_patch                    0x87540
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46CC
	#define psp_savedata_patch2                         0x46A4
	#define psp_savedata_patch3                         0x4504
	#define psp_savedata_patch4                         0x453C
	#define psp_savedata_patch5                         0x4550
	#define psp_savedata_patch6                         0x46B8

	/* libfs */
	#define aio_copy_root_offset                        0xD658

	/* CEX */
	#define cex_ps2tonet_patch                          0xC4B14
	#define cex_ps2tonet_size_patch                     0xC4B08
	#define cex_vmode_patch_offset                      0x442E5C
	#define cex_psp_drm_patch1                          0x242C74
	#define cex_psp_drm_patch2                          0x243714
	#define cex_psp_drm_patch3                          0x243350
	#define cex_psp_drm_patch4                          0x243B5C
	#define cex_psp_drm_patchA                          0x242D90
	#define cex_psp_drm_patchB                          0x243630
	#define cex_psp_drm_patchC                          0x2427C8
	#define cex_psp_drm_patchD                          0x242D78
	#define cex_psp_drm_patchE                          0x242D7C
	#define cex_psp_drm_patchF                          0x243748
	#define cex_psp_extra_drm_patch                     0x2457A4
#endif

#ifdef FIRMWARE_480C

	#define FIRMWARE_VERSION                                 0x480

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x480
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2E30ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474AF4ULL
		#define PS3MAPI_PSID                                 0x8000000000474B0CULL
	#endif

	/* lv2 */
	#define TOC                                              0x34FBA0
	#define open_shared_kernel_object_symbol                 0x1240C
	#define close_kernel_object_handle_symbol                0x11A2C
	#define open_kernel_object_symbol                        0x125FC
	#define alloc_symbol                                     0x64820
	#define dealloc_symbol                                   0x64C5C
	#define copy_to_user_symbol                              0xF868
	#define copy_from_user_symbol                            0xFA84
	#define copy_to_process_symbol                           0xF920
	#define copy_from_process_symbol                         0xF730
	#define page_allocate_symbol                             0x60390
	#define page_free_symbol                                 0x5FDF4
	#define page_export_to_proc_symbol                       0x6052C
	#define page_unexport_from_proc_symbol                   0x5FCE8
	#define kernel_ea_to_lpar_addr_symbol                    0x70148
	#define map_process_memory_symbol                        0x77268
	#define memcpy_symbol                                    0x7E928
	#define memset_symbol                                    0x4D668
	#define memcmp_symbol                                    0x4C978
	#define printf_symbol                                    0x2706A0
	#define printfnull_symbol                                0x275114
	#define sprintf_symbol                                   0x4EA90
	#define snprintf_symbol                                  0x4E9FC
	#define strcpy_symbol                                    0x4D814
	#define strncpy_symbol                                   0x4D8DC
	#define strlen_symbol                                    0x4D83C
	#define strcat_symbol                                    0x4D744
	#define strcmp_symbol                                    0x4D7C0
	#define strncmp_symbol                                   0x4D868
	#define strchr_symbol                                    0x4D77C
	#define spin_lock_irqsave_ex_symbol                      0x26D78C
	#define spin_unlock_irqrestore_ex_symbol                 0x26D760
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x13EC4
	#define ppu_thread_exit_symbol                           0x13F7C
	#define ppu_thread_join_symbol                           0x13FD0
	#define ppu_thread_delay_symbol                          0x287A0
	#define create_user_thread2_symbol                       0x2507C
	#define start_thread_symbol                              0x23D48
	#define run_thread_symbol                                0x23578
	#define register_thread_symbol                           0x267940
	#define allocate_user_stack_symbol                       0x268128
	#define mutex_create_symbol                              0x13638
	#define mutex_destroy_symbol                             0x135D0
	#define mutex_lock_symbol                                0x135C8
	#define mutex_unlock_symbol                              0x135C0
	#define event_port_create_symbol                         0x13074
	#define event_port_destroy_symbol                        0x134DC
	#define event_port_connect_symbol                        0x13554
	#define event_port_disconnect_symbol                     0x13480
	#define event_port_send_symbol                           0x1306C
	#define event_queue_create_symbol                        0x1337C
	#define event_queue_destroy_symbol                       0x13304
	#define event_queue_receive_symbol                       0x13148
	#define cellFsOpen_symbol                                0x2978F4
	#define cellFsClose_symbol                               0x29775C
	#define cellFsRead_symbol                                0x297898
	#define cellFsWrite_symbol                               0x297804
	#define cellFsLseek_symbol                               0x296E8C
	#define cellFsStat_symbol                                0x297110
	#define cellFsUnlink_internal_symbol                     0x19C644
	#define cellFsUtilMount_symbol                           0x296C6C
	#define cellFsUtilUmount_symbol                          0x296C40
	#define pathdup_from_user_symbol                         0x29C8D8
	#define open_path_symbol                                 0x2ED870
	#define open_fs_object_symbol                            0x18A968
	#define close_fs_object_symbol                           0x1898A4
	#define storage_get_device_info_symbol                   0x279AF4
	#define storage_open_symbol                              0x279504
	#define storage_close_symbol                             0x2792F4
	#define storage_read_symbol                              0x278864
	#define storage_send_device_command_symbol               0x2783F0
	#define storage_map_io_memory_symbol                     0x2799B0
	#define storage_unmap_io_memory_symbol                   0x27987C
	#define storage_internal_get_device_object_symbol        0x277EA8
	#define decrypt_func_symbol                              0x3496C
	#define lv1_call_99_wrapper_symbol                       0x4EEA4
	#define modules_verification_symbol                      0x58AB4
	#define prx_load_module_symbol                           0x88C00
	#define prx_start_module_symbol                          0x878CC
	#define prx_stop_module_symbol                           0x88CA4
	#define prx_unload_module_symbol                         0x87600
	#define prx_get_module_info_symbol                       0x87088
	#define prx_get_module_list_symbol                       0x87108
	#define extend_kstack_symbol                             0x700A0
	#define get_pseudo_random_number_symbol                  0x228178
	#define syscall_table_symbol                             0x363BE0
	#define syscall_call_offset                              0x275BF8
	#define read_bdvd0_symbol                                0x1A4614
	#define read_bdvd1_symbol                                0x1A6240
	#define read_bdvd2_symbol                                0x1B33F8
	#define device_event_port_send_call                      0x282060
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x297A8C
	#define fsloop_close_call                                0x297ADC
	#define fsloop_read_call                                 0x297B1C
	#define io_rtoc_entry_1                                  0x25B8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0
	#define storage_rtoc_entry_1                             0x1DD8
	#define device_event_rtoc_entry_1                        0x2048
	#define process_rtoc_entry_1                            -0x7800
	#define patch_func2                                      0x59D80
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x203F8
	#define user_thread_prio_patch2                          0x20404
	#define shutdown_patch_offset                            0xAAB8
	#define shutdown_copy_params_call                        0xAACC

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000EC469
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB378E600056AE5
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001E5C4
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BCE800006477
	#define PSP_EMULATOR_HASH                           0x7BE641F500023793
	#define PEMUCORELIB_HASH                            0xF349A563000C0D6C
	#define EMULATOR_API_HASH                           0xA9F5B37A0001BB45
	#define EMULATOR_DRM_HASH                           0xA324DC4A00005399
	#define EMULATOR_DRM_DATA_HASH                      0x75C390860001B75F
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC3B800003212

	/* lv1 */
	#define vsh_pos_in_ram                              0x910000

	/* vsh */
	#define ps2tonet_patch                              0xC4E34
	#define ps2tonet_size_patch                         0xC4E28
	#define vmode_patch_offset                          0x4431E4
	#define psp_drm_patch1                              0x242FBC
	#define psp_drm_patch2                              0x243A5C
	#define psp_drm_patch3                              0x243698
	#define psp_drm_patch4                              0x243EA4
	#define psp_drm_patchA                              0x2430D8
	#define psp_drm_patchB                              0x243978
	#define psp_drm_patchC                              0x242B10
	#define psp_drm_patchD                              0x2430C0
	#define psp_drm_patchE                              0x2430C4
	#define psp_drm_patchF                              0x243A90
	#define psp_extra_drm_patch                         0x245AEC

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDD9B4

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x68324

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x17000

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1C18

	/* emulator_api */
	#define psp_read                                    0x102D8
	#define psp_read_header                             0x1125C
	#define psp_drm_patch5                              0x11080
	#define psp_drm_patch6                              0x110B0
	#define psp_drm_patch7                              0x110C8
	#define psp_drm_patch8                              0x110CC
	#define psp_drm_patch9                              0x1120C
	#define psp_drm_patch11                             0x11210
	#define psp_drm_patch12                             0x11220
	#define psp_product_id_patch1                       0x11320
	#define psp_product_id_patch3                       0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6BC
	#define psp_prx_patch                               0x577D8
	#define psp_savedata_bind_patch1                    0x7A4BC
	#define psp_savedata_bind_patch2                    0x7A514
	#define psp_savedata_bind_patch3                    0x7A030
	#define psp_extra_savedata_patch                    0x87540
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46CC
	#define psp_savedata_patch2                         0x46A4
	#define psp_savedata_patch3                         0x4504
	#define psp_savedata_patch4                         0x453C
	#define psp_savedata_patch5                         0x4550
	#define psp_savedata_patch6                         0x46B8

	/* libfs */
	#define aio_copy_root_offset                        0xD658

	/* rebug */
	#define EXPLORE_PLUGIN_REBUG_HASH                   0xACF4AF2B000ECC8A
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH            0x9CB3396E00056CE9
	#define GAME_EXT_PLUGIN_REBUG_HASH                  0xE274AF7B0001E5DB
	#define dex_ps2_nonbw_offset                        0xDDDC4
	#define dex_ps2_nonbw_offset2                       0x68264
	#define dex_ps2_nonbw_offset3                       0x172F0
	#define dex_ps2tonet_patch                          0xCA380
	#define dex_ps2tonet_size_patch                     0xCA374
	#define dex_vmode_patch_offset                      0x44ADD8
	#define dex_psp_drm_patch1                          0x24A7E4
	#define dex_psp_drm_patch2                          0x24B284
	#define dex_psp_drm_patch3                          0x24AEC0
	#define dex_psp_drm_patch4                          0x24B6CC
	#define dex_psp_drm_patchA                          0x24A900
	#define dex_psp_drm_patchB                          0x24B1A0
	#define dex_psp_drm_patchC                          0x24A338
	#define dex_psp_drm_patchD                          0x24A8E8
	#define dex_psp_drm_patchE                          0x24A8EC
	#define dex_psp_drm_patchF                          0x24B2B8
	#define dex_psp_extra_drm_patch                     0x24D314
#endif

#ifdef FIRMWARE_480D

	#define FIRMWARE_VERSION                                 0x480

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x480
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x8000000000409A30ULL
		#define PS3MAPI_IDPS_2                               0x800000000049CAF4ULL
		#define PS3MAPI_PSID                                 0x800000000049CB0CULL
	#endif

	/* lv2 */
	#define TOC                                              0x3759B0
	#define open_shared_kernel_object_symbol                 0x12A54
	#define close_kernel_object_handle_symbol                0x12074
	#define open_kernel_object_symbol                        0x12C44
	#define alloc_symbol                                     0x681F0
	#define dealloc_symbol                                   0x6862C
	#define copy_to_user_symbol                              0xFEB0
	#define copy_from_user_symbol                            0x100CC
	#define copy_to_process_symbol                           0xFF68
	#define copy_from_process_symbol                         0xFD78
	#define page_allocate_symbol                             0x63D60
	#define page_free_symbol                                 0x637C4
	#define page_export_to_proc_symbol                       0x63EFC
	#define page_unexport_from_proc_symbol                   0x636B8
	#define kernel_ea_to_lpar_addr_symbol                    0x73C98
	#define map_process_memory_symbol                        0x7B344
	#define memcpy_symbol                                    0x82A04
	#define memset_symbol                                    0x51010
	#define memcmp_symbol                                    0x50320
	#define printf_symbol                                    0x27896C
	#define printfnull_symbol                                0x27D3F4
	#define sprintf_symbol                                   0x52438
	#define snprintf_symbol                                  0x523A4
	#define strcpy_symbol                                    0x511BC
	#define strncpy_symbol                                   0x51284
	#define strlen_symbol                                    0x511E4
	#define strcat_symbol                                    0x510EC
	#define strcmp_symbol                                    0x51168
	#define strncmp_symbol                                   0x51210
	#define strchr_symbol                                    0x51124
	#define spin_lock_irqsave_ex_symbol                      0x275664
	#define spin_unlock_irqrestore_ex_symbol                 0x275638
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x145F8
	#define ppu_thread_exit_symbol                           0x146B0
	#define ppu_thread_join_symbol                           0x14704
	#define ppu_thread_delay_symbol                          0x2A6E4
	#define create_user_thread2_symbol                       0x26D2C
	#define start_thread_symbol                              0x25864
	#define run_thread_symbol                                0x25028
	#define register_thread_symbol                           0x26E264
	#define allocate_user_stack_symbol                       0x26EA4C
	#define mutex_create_symbol                              0x13C88
	#define mutex_destroy_symbol                             0x13C20
	#define mutex_lock_symbol                                0x13C18
	#define mutex_unlock_symbol                              0x13C10
	#define event_port_create_symbol                         0x136C4
	#define event_port_destroy_symbol                        0x13B2C
	#define event_port_connect_symbol                        0x13BA4
	#define event_port_disconnect_symbol                     0x13AD0
	#define event_port_send_symbol                           0x136BC
	#define event_queue_create_symbol                        0x139CC
	#define event_queue_destroy_symbol                       0x13954
	#define event_queue_receive_symbol                       0x13798
	#define cellFsOpen_symbol                                0x2B288C
	#define cellFsClose_symbol                               0x2B26F4
	#define cellFsRead_symbol                                0x2B2830
	#define cellFsWrite_symbol                               0x2B279C
	#define cellFsLseek_symbol                               0x2B1FF0
	#define cellFsStat_symbol                                0x2B20A8
	#define cellFsUnlink_internal_symbol                     0x1A29D0
	#define cellFsUtilMount_symbol                           0x2B1D64
	#define cellFsUtilUmount_symbol                          0x2B1D38
	#define pathdup_from_user_symbol                         0x2B7B50
	#define open_path_symbol                                 0x2B25C4
	#define open_fs_object_symbol                            0x190CF4
	#define close_fs_object_symbol                           0x18FC30
	#define storage_get_device_info_symbol                   0x28C9F4
	#define storage_open_symbol                              0x28CC1C
	#define storage_close_symbol                             0x28B408
	#define storage_read_symbol                              0x28A384
	#define storage_send_device_command_symbol               0x289EA4
	#define storage_map_io_memory_symbol                     0x28C8A0
	#define storage_unmap_io_memory_symbol                   0x28C75C
	#define storage_internal_get_device_object_symbol        0x28995C
	#define decrypt_func_symbol                              0x3828C
	#define lv1_call_99_wrapper_symbol                       0x5284C
	#define modules_verification_symbol                      0x5C484
	#define prx_load_module_symbol                           0x8D304
	#define prx_start_module_symbol                          0x8BFD0
	#define prx_stop_module_symbol                           0x8D3A8
	#define prx_unload_module_symbol                         0x8BD04
	#define prx_get_module_info_symbol                       0x8B6FC
	#define prx_get_module_list_symbol                       0x8B77C
	#define extend_kstack_symbol                             0x73BF0
	#define get_pseudo_random_number_symbol                  0x22E654
	#define syscall_table_symbol                             0x38A4E8
	#define syscall_call_offset                              0x27DED8
	#define read_bdvd0_symbol                                0x1AAAC4
	#define read_bdvd1_symbol                                0x1AC6F0
	#define read_bdvd2_symbol                                0x1B98A8
	#define device_event_port_send_call                      0x296BF0
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x2B2A24
	#define fsloop_close_call                                0x2B2A74
	#define fsloop_read_call                                 0x2B2AB4
	#define io_rtoc_entry_1                                  0x2EC0
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65C0
	#define storage_rtoc_entry_1                             0x22B0
	#define device_event_rtoc_entry_1                        0x2638
	#define process_rtoc_entry_1                            -0x77A0
	#define patch_func2                                      0x5D750
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x21EA8
	#define user_thread_prio_patch2                          0x21EB4
	#define shutdown_patch_offset                            0xAB38
	#define shutdown_copy_params_call                        0xAB4C

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000ECC8A
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB3396E00056CE9
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001E5DB
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BCE800006477
	#define PSP_EMULATOR_HASH                           0x7BE641F500023793
	#define PEMUCORELIB_HASH                            0xF349A563000C0D6C
	#define EMULATOR_API_HASH                           0xA9F5B37A0001BB45
	#define EMULATOR_DRM_HASH                           0xA324DC4A00005399
	#define EMULATOR_DRM_DATA_HASH                      0x75C390860001B75F
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC3B800003212

	/* lv1 */
	#define vsh_pos_in_ram                              0x910000

	/* vsh */
	#define ps2tonet_patch                              0xCA380
	#define ps2tonet_size_patch                         0xCA374
	#define vmode_patch_offset                          0x44ADD8
	#define psp_drm_patch1                              0x24A7E4
	#define psp_drm_patch2                              0x24B284
	#define psp_drm_patch3                              0x24AEC0
	#define psp_drm_patch4                              0x24B6CC
	#define psp_drm_patchA                              0x24A900
	#define psp_drm_patchB                              0x24B1A0
	#define psp_drm_patchC                              0x24A338
	#define psp_drm_patchD                              0x24A8E8
	#define psp_drm_patchE                              0x24A8EC
	#define psp_drm_patchF                              0x24B2B8
	#define psp_extra_drm_patch                         0x24D314

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDDDC4

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x68264

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x172F0

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1C18

	/* emulator_api */
	#define psp_read                                    0x102D8
	#define psp_read_header                             0x1125C
	#define psp_drm_patch5                              0x11080
	#define psp_drm_patch6                              0x110B0
	#define psp_drm_patch7                              0x110C8
	#define psp_drm_patch8                              0x110CC
	#define psp_drm_patch9                              0x1120C
	#define psp_drm_patch11                             0x11210
	#define psp_drm_patch12                             0x11220
	#define psp_product_id_patch1                       0x11320
	#define psp_product_id_patch3                       0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6BC
	#define psp_prx_patch                               0x577D8
	#define psp_savedata_bind_patch1                    0x7A4BC
	#define psp_savedata_bind_patch2                    0x7A514
	#define psp_savedata_bind_patch3                    0x7A030
	#define psp_extra_savedata_patch                    0x87540
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46CC
	#define psp_savedata_patch2                         0x46A4
	#define psp_savedata_patch3                         0x4504
	#define psp_savedata_patch4                         0x453C
	#define psp_savedata_patch5                         0x4550
	#define psp_savedata_patch6                         0x46B8

	/* libfs */
	#define aio_copy_root_offset                        0xD658

	/* CEX */
	#define cex_ps2tonet_patch                          0xC4E34
	#define cex_ps2tonet_size_patch                     0xC4E28
	#define cex_vmode_patch_offset                      0x4431E4
	#define cex_psp_drm_patch1                          0x242FBC
	#define cex_psp_drm_patch2                          0x243A5C
	#define cex_psp_drm_patch3                          0x243698
	#define cex_psp_drm_patch4                          0x243EA4
	#define cex_psp_drm_patchA                          0x2430D8
	#define cex_psp_drm_patchB                          0x243978
	#define cex_psp_drm_patchC                          0x242B10
	#define cex_psp_drm_patchD                          0x2430C0
	#define cex_psp_drm_patchE                          0x2430C4
	#define cex_psp_drm_patchF                          0x243A90
	#define cex_psp_extra_drm_patch                     0x245AEC
#endif

#ifdef FIRMWARE_481C

	#define FIRMWARE_VERSION                                 0x481

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x481
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2E30ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474AF4ULL
		#define PS3MAPI_PSID                                 0x8000000000474B0CULL
	#endif

	/* lv2 */
	#define TOC                                              0x34FBB0
	#define open_shared_kernel_object_symbol                 0x12410
	#define close_kernel_object_handle_symbol                0x11A30
	#define open_kernel_object_symbol                        0x12600
	#define alloc_symbol                                     0x64824
	#define dealloc_symbol                                   0x64C60
	#define copy_to_user_symbol                              0xF86C
	#define copy_from_user_symbol                            0xFA88
	#define copy_to_process_symbol                           0xF924
	#define copy_from_process_symbol                         0xF734
	#define page_allocate_symbol                             0x60394
	#define page_free_symbol                                 0x5FDF8
	#define page_export_to_proc_symbol                       0x60530
	#define page_unexport_from_proc_symbol                   0x5FCEC
	#define kernel_ea_to_lpar_addr_symbol                    0x7014C
	#define map_process_memory_symbol                        0x7726C
	#define memcpy_symbol                                    0x7E92C
	#define memset_symbol                                    0x4D66C
	#define memcmp_symbol                                    0x4C97C
	#define printf_symbol                                    0x2706AC
	#define printfnull_symbol                                0x275120
	#define sprintf_symbol                                   0x4EA94
	#define snprintf_symbol                                  0x4EA00
	#define strcpy_symbol                                    0x4D818
	#define strncpy_symbol                                   0x4D8E0
	#define strlen_symbol                                    0x4D840
	#define strcat_symbol                                    0x4D748
	#define strcmp_symbol                                    0x4D7C4
	#define strncmp_symbol                                   0x4D86C
	#define strchr_symbol                                    0x4D780
	#define spin_lock_irqsave_ex_symbol                      0x26D798
	#define spin_unlock_irqrestore_ex_symbol                 0x26D76C
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x13EC8
	#define ppu_thread_exit_symbol                           0x13F80
	#define ppu_thread_join_symbol                           0x13FD4
	#define ppu_thread_delay_symbol                          0x287A4
	#define create_user_thread2_symbol                       0x25080
	#define start_thread_symbol                              0x23D4C
	#define run_thread_symbol                                0x2357C
	#define register_thread_symbol                           0x26794C
	#define allocate_user_stack_symbol                       0x268134
	#define mutex_create_symbol                              0x1363C
	#define mutex_destroy_symbol                             0x135D4
	#define mutex_lock_symbol                                0x135CC
	#define mutex_unlock_symbol                              0x135C4
	#define event_port_create_symbol                         0x13078
	#define event_port_destroy_symbol                        0x134E0
	#define event_port_connect_symbol                        0x13558
	#define event_port_disconnect_symbol                     0x13484
	#define event_port_send_symbol                           0x13070
	#define event_queue_create_symbol                        0x13380
	#define event_queue_destroy_symbol                       0x13308
	#define event_queue_receive_symbol                       0x1314C
	#define cellFsOpen_symbol                                0x297900
	#define cellFsClose_symbol                               0x297768
	#define cellFsRead_symbol                                0x2978A4
	#define cellFsWrite_symbol                               0x297810
	#define cellFsLseek_symbol                               0x296E98
	#define cellFsStat_symbol                                0x29711C
	#define cellFsUnlink_internal_symbol                     0x19C64C
	#define cellFsUtilMount_symbol                           0x296C78
	#define cellFsUtilUmount_symbol                          0x296C4C
	#define pathdup_from_user_symbol                         0x29C8E4
	#define open_path_symbol                                 0x297638
	#define open_fs_object_symbol                            0x18A970
	#define close_fs_object_symbol                           0x1898AC
	#define storage_get_device_info_symbol                   0x279B00
	#define storage_open_symbol                              0x279510
	#define storage_close_symbol                             0x279300
	#define storage_read_symbol                              0x278870
	#define storage_send_device_command_symbol               0x2783FC
	#define storage_map_io_memory_symbol                     0x2799BC
	#define storage_unmap_io_memory_symbol                   0x279888
	#define storage_internal_get_device_object_symbol        0x277EB4
	#define decrypt_func_symbol                              0x34970
	#define lv1_call_99_wrapper_symbol                       0x4EEA8
	#define modules_verification_symbol                      0x58AB8
	#define prx_load_module_symbol                           0x88C04
	#define prx_start_module_symbol                          0x878D0
	#define prx_stop_module_symbol                           0x88CA8
	#define prx_unload_module_symbol                         0x87604
	#define prx_get_module_info_symbol                       0x8708C
	#define prx_get_module_list_symbol                       0x8710C
	#define extend_kstack_symbol                             0x700A4
	#define get_pseudo_random_number_symbol                  0x228180
	#define syscall_table_symbol                             0x363BE0
	#define syscall_call_offset                              0x275C04
	#define read_bdvd0_symbol                                0x1A461C
	#define read_bdvd1_symbol                                0x1A6248
	#define read_bdvd2_symbol                                0x1B3400
	#define device_event_port_send_call                      0x28206C
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x297A98
	#define fsloop_close_call                                0x297AE8
	#define fsloop_read_call                                 0x297B28
	#define io_rtoc_entry_1                                  0x25B8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0
	#define storage_rtoc_entry_1                             0x1DD8
	#define device_event_rtoc_entry_1                        0x2048
	#define process_rtoc_entry_1                            -0x7800
	#define patch_func2                                      0x59D84
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x203FC
	#define user_thread_prio_patch2                          0x20408
	#define shutdown_patch_offset                            0xAAB8
	#define shutdown_copy_params_call                        0xAACC

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000EC47F
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB378E600056AE5
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001E594
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BCE800006477
	#define PSP_EMULATOR_HASH                           0x7BE641F500023794
	#define PEMUCORELIB_HASH                            0xF349A563000C0D67
	#define EMULATOR_API_HASH                           0xA9F5B37A0001BB45
	#define EMULATOR_DRM_HASH                           0xA324DC4A00005399
	#define EMULATOR_DRM_DATA_HASH                      0x75C390860001B75F
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC3B800003212

	/* lv1 */
	#define vsh_pos_in_ram                              0x510000

	/* vsh */
	#define ps2tonet_patch                              0xC4E34
	#define ps2tonet_size_patch                         0xC4E28
	#define vmode_patch_offset                          0x4431D8
	#define psp_drm_patch1                              0x242FC0
	#define psp_drm_patch2                              0x243A60
	#define psp_drm_patch3                              0x24369C
	#define psp_drm_patch4                              0x243EA8
	#define psp_drm_patchA                              0x2430DC
	#define psp_drm_patchB                              0x24397C
	#define psp_drm_patchC                              0x242B14
	#define psp_drm_patchD                              0x2430C4
	#define psp_drm_patchE                              0x2430C8
	#define psp_drm_patchF                              0x243A94
	#define psp_extra_drm_patch                         0x245AF0

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDD9B4

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x68324

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x17000

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1C18

	/* emulator_api */
	#define psp_read                                    0x102D8
	#define psp_read_header                             0x1125C
	#define psp_drm_patch5                              0x11080
	#define psp_drm_patch6                              0x110B0
	#define psp_drm_patch7                              0x110C8
	#define psp_drm_patch8                              0x110CC
	#define psp_drm_patch9                              0x1120C
	#define psp_drm_patch11                             0x11210
	#define psp_drm_patch12                             0x11220
	#define psp_product_id_patch1                       0x11320
	#define psp_product_id_patch3                       0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6BC
	#define psp_prx_patch                               0x577D8
	#define psp_savedata_bind_patch1                    0x7A4BC
	#define psp_savedata_bind_patch2                    0x7A514
	#define psp_savedata_bind_patch3                    0x7A030
	#define psp_extra_savedata_patch                    0x87540
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46CC
	#define psp_savedata_patch2                         0x46A4
	#define psp_savedata_patch3                         0x4504
	#define psp_savedata_patch4                         0x453C
	#define psp_savedata_patch5                         0x4550
	#define psp_savedata_patch6                         0x46B8

	/* libfs */
	#define aio_copy_root_offset                        0xD658

	/* rebug */
	#define EXPLORE_PLUGIN_REBUG_HASH                   0xACF4AF2B000ECC8F
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH            0x9CB3396E00056CE9
	#define GAME_EXT_PLUGIN_REBUG_HASH                  0xE274AF7B0001E5D3
	#define dex_ps2_nonbw_offset                        0xDDDC4
	#define dex_ps2_nonbw_offset2                       0x68264
	#define dex_ps2_nonbw_offset3                       0x172F0
	#define dex_ps2tonet_patch                          0xCA380
	#define dex_ps2tonet_size_patch                     0xCA374
	#define dex_vmode_patch_offset                      0x44ADCC
	#define dex_psp_drm_patch1                          0x24A7E8
	#define dex_psp_drm_patch2                          0x24B288
	#define dex_psp_drm_patch3                          0x24AEC4
	#define dex_psp_drm_patch4                          0x24B6D0
	#define dex_psp_drm_patchA                          0x24A904
	#define dex_psp_drm_patchB                          0x24B1A4
	#define dex_psp_drm_patchC                          0x24A33C
	#define dex_psp_drm_patchD                          0x24A8EC
	#define dex_psp_drm_patchE                          0x24A8F0
	#define dex_psp_drm_patchF                          0x24B2BC
	#define dex_psp_extra_drm_patch                     0x24D318
#endif

#ifdef FIRMWARE_481D

	#define FIRMWARE_VERSION                                 0x481

	#ifdef PS3M_API
		#define PS3MAPI_FW_VERSION                           0x481
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x8000000000409A30ULL
		#define PS3MAPI_IDPS_2                               0x800000000049CAF4ULL
		#define PS3MAPI_PSID                                 0x800000000049CB0CULL
	#endif

	/* lv2 */
	#define TOC                                              0x3759C0
	#define open_shared_kernel_object_symbol                 0x12A58
	#define close_kernel_object_handle_symbol                0x12078
	#define open_kernel_object_symbol                        0x12C48
	#define alloc_symbol                                     0x681F4
	#define dealloc_symbol                                   0x68630
	#define copy_to_user_symbol                              0xFEB4
	#define copy_from_user_symbol                            0x100D0
	#define copy_to_process_symbol                           0xFF6C
	#define copy_from_process_symbol                         0xFD7C
	#define page_allocate_symbol                             0x63D64
	#define page_free_symbol                                 0x637C8
	#define page_export_to_proc_symbol                       0x63F00
	#define page_unexport_from_proc_symbol                   0x636BC
	#define kernel_ea_to_lpar_addr_symbol                    0x73C9C
	#define map_process_memory_symbol                        0x7B348
	#define memcpy_symbol                                    0x82A08
	#define memset_symbol                                    0x51014
	#define memcmp_symbol                                    0x50324
	#define printf_symbol                                    0x278978
	#define printfnull_symbol                                0x27D400
	#define sprintf_symbol                                   0x5243C
	#define snprintf_symbol                                  0x523A8
	#define strcpy_symbol                                    0x511C0
	#define strncpy_symbol                                   0x51288
	#define strlen_symbol                                    0x511E8
	#define strcat_symbol                                    0x510F0
	#define strcmp_symbol                                    0x5116C
	#define strncmp_symbol                                   0x51214
	#define strchr_symbol                                    0x51128
	#define spin_lock_irqsave_ex_symbol                      0x275670
	#define spin_unlock_irqrestore_ex_symbol                 0x275644
	#define load_process_symbol                              0x5004
	#define ppu_thread_create_symbol                         0x145FC
	#define ppu_thread_exit_symbol                           0x146B4
	#define ppu_thread_join_symbol                           0x14708
	#define ppu_thread_delay_symbol                          0x2A6E8
	#define create_user_thread2_symbol                       0x26D30
	#define start_thread_symbol                              0x25868
	#define run_thread_symbol                                0x2502C
	#define register_thread_symbol                           0x26E270
	#define allocate_user_stack_symbol                       0x26EA58
	#define mutex_create_symbol                              0x13C8C
	#define mutex_destroy_symbol                             0x13C24
	#define mutex_lock_symbol                                0x13C1C
	#define mutex_unlock_symbol                              0x13C14
	#define event_port_create_symbol                         0x136C8
	#define event_port_destroy_symbol                        0x13B30
	#define event_port_connect_symbol                        0x13BA8
	#define event_port_disconnect_symbol                     0x13AD4
	#define event_port_send_symbol                           0x136C0
	#define event_queue_create_symbol                        0x139D0
	#define event_queue_destroy_symbol                       0x13958
	#define event_queue_receive_symbol                       0x1379C
	#define cellFsOpen_symbol                                0x2B2898
	#define cellFsClose_symbol                               0x2B2700
	#define cellFsRead_symbol                                0x2B283C
	#define cellFsWrite_symbol                               0x2B27A8
	#define cellFsLseek_symbol                               0x2B1FFC
	#define cellFsStat_symbol                                0x2B20B4
	#define cellFsUnlink_internal_symbol                     0x1A29D8
	#define cellFsUtilMount_symbol                           0x2B1D70
	#define cellFsUtilUmount_symbol                          0x2B1D44
	#define pathdup_from_user_symbol                         0x2B7B5C
	#define open_path_symbol                                 0x2B25D0
	#define open_fs_object_symbol                            0x190CFC
	#define close_fs_object_symbol                           0x18FC38
	#define storage_get_device_info_symbol                   0x28CA00
	#define storage_open_symbol                              0x28CC28
	#define storage_close_symbol                             0x28B414
	#define storage_read_symbol                              0x28A390
	#define storage_send_device_command_symbol               0x289EB0
	#define storage_map_io_memory_symbol                     0x28C8AC
	#define storage_unmap_io_memory_symbol                   0x28C768
	#define storage_internal_get_device_object_symbol        0x289968
	#define decrypt_func_symbol                              0x38290
	#define lv1_call_99_wrapper_symbol                       0x52850
	#define modules_verification_symbol                      0x5C488
	#define prx_load_module_symbol                           0x8D308
	#define prx_start_module_symbol                          0x8BFD4
	#define prx_stop_module_symbol                           0x8D3AC
	#define prx_unload_module_symbol                         0x8BD08
	#define prx_get_module_info_symbol                       0x8B700
	#define prx_get_module_list_symbol                       0x8B780
	#define extend_kstack_symbol                             0x73BF4
	#define get_pseudo_random_number_symbol                  0x22E65C
	#define syscall_table_symbol                             0x38A4E8
	#define syscall_call_offset                              0x27DEE4
	#define read_bdvd0_symbol                                0x1AAACC
	#define read_bdvd1_symbol                                0x1AC6F8
	#define read_bdvd2_symbol                                0x1B98B0
	#define device_event_port_send_call                      0x296BFC
	#define process_map_caller_call                          0x4D24
	#define fsloop_open_call                                 0x2B2A30
	#define fsloop_close_call                                0x2B2A80
	#define fsloop_read_call                                 0x2B2AC0
	#define io_rtoc_entry_1                                  0x2EC0
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65C0
	#define storage_rtoc_entry_1                             0x22B0
	#define device_event_rtoc_entry_1                        0x2638
	#define process_rtoc_entry_1                            -0x77A0
	#define patch_func2                                      0x5D754
	#define patch_func2_offset                               0x2C
	#define user_thread_prio_patch                           0x21EAC
	#define user_thread_prio_patch2                          0x21EB8
	#define shutdown_patch_offset                            0xAB38
	#define shutdown_copy_params_call                        0xAB4C

	/* hash */
	#define EXPLORE_PLUGIN_HASH                         0xACF4AF2B000ECC8F
	#define EXPLORE_CATEGORY_GAME_HASH                  0x9CB3396E00056CE9
	#define GAME_EXT_PLUGIN_HASH                        0xE274AF7B0001E5D3
	#define LIBFS_EXTERNAL_HASH                         0x5BC7BCE800006477
	#define PSP_EMULATOR_HASH                           0x7BE641F500023794
	#define PEMUCORELIB_HASH                            0xF349A563000C0D67
	#define EMULATOR_API_HASH                           0xA9F5B37A0001BB45
	#define EMULATOR_DRM_HASH                           0xA324DC4A00005399
	#define EMULATOR_DRM_DATA_HASH                      0x75C390860001B75F
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                0x57BBC3B800003212

	/* lv1 */
	#define vsh_pos_in_ram                              0x910000

	/* vsh */
	#define ps2tonet_patch                              0xCA380
	#define ps2tonet_size_patch                         0xCA374
	#define vmode_patch_offset                          0x44ADCC
	#define psp_drm_patch1                              0x24A7E8
	#define psp_drm_patch2                              0x24B288
	#define psp_drm_patch3                              0x24AEC4
	#define psp_drm_patch4                              0x24B6D0
	#define psp_drm_patchA                              0x24A904
	#define psp_drm_patchB                              0x24B1A4
	#define psp_drm_patchC                              0x24A33C
	#define psp_drm_patchD                              0x24A8EC
	#define psp_drm_patchE                              0x24A8F0
	#define psp_drm_patchF                              0x24B2BC
	#define psp_extra_drm_patch                         0x24D318

	/* explore_plugin */
	#define ps2_nonbw_offset                            0xDDDC4

	/* explore_category_game */
	#define ps2_nonbw_offset2                           0x68264

	/* game_ext_plugin */
	#define ps2_nonbw_offset3                           0x172F0

	/* psp_emulator */
	#define psp_set_psp_mode_offset                     0x1C18

	/* emulator_api */
	#define psp_read                                    0x102D8
	#define psp_read_header                             0x1125C
	#define psp_drm_patch5                              0x11080
	#define psp_drm_patch6                              0x110B0
	#define psp_drm_patch7                              0x110C8
	#define psp_drm_patch8                              0x110CC
	#define psp_drm_patch9                              0x1120C
	#define psp_drm_patch11                             0x11210
	#define psp_drm_patch12                             0x11220
	#define psp_product_id_patch1                       0x11320
	#define psp_product_id_patch3                       0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                         0x5E6BC
	#define psp_prx_patch                               0x577D8
	#define psp_savedata_bind_patch1                    0x7A4BC
	#define psp_savedata_bind_patch2                    0x7A514
	#define psp_savedata_bind_patch3                    0x7A030
	#define psp_extra_savedata_patch                    0x87540
	#define psp_prometheus_patch                        0x12EA28
	#define prx_patch_call_lr                           0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                       0x4C68
	#define psp_drm_key_overwrite                       (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                         0x46CC
	#define psp_savedata_patch2                         0x46A4
	#define psp_savedata_patch3                         0x4504
	#define psp_savedata_patch4                         0x453C
	#define psp_savedata_patch5                         0x4550
	#define psp_savedata_patch6                         0x46B8

	/* libfs */
	#define aio_copy_root_offset                        0xD658

	/* CEX */
	#define cex_ps2tonet_patch                          0xC4E34
	#define cex_ps2tonet_size_patch                     0xC4E28
	#define cex_vmode_patch_offset                      0x4431D8
	#define cex_psp_drm_patch1                          0x242FC0
	#define cex_psp_drm_patch2                          0x243A60
	#define cex_psp_drm_patch3                          0x24369C
	#define cex_psp_drm_patch4                          0x243EA8
	#define cex_psp_drm_patchA                          0x2430DC
	#define cex_psp_drm_patchB                          0x24397C
	#define cex_psp_drm_patchC                          0x242B14
	#define cex_psp_drm_patchD                          0x2430C4
	#define cex_psp_drm_patchE                          0x2430C8
	#define cex_psp_drm_patchF                          0x243A94
	#define cex_psp_extra_drm_patch                     0x245AF0
#endif


#endif /* __FIRMWARE_SYMBOLS_H_S__ */
