#ifndef __FIRMWARE_SYMBOLS_H_S__
#define __FIRMWARE_SYMBOLS_H_S__

#define umd_mutex_offset (0x64480+0x38C)

#ifdef FIRMWARE_421C

	#define FIRMWARE_VERSION                                 0x421

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003D9230ULL
		#define PS3MAPI_IDPS_2                               0x8000000000477E9CULL
		#define PS3MAPI_PSID                                 0x8000000000477EB4ULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x346390

	#define create_kernel_object_symbol                      0x11F9C
	#define destroy_kernel_object_symbol                     0x11900
	#define destroy_shared_kernel_object_symbol              0x11274
	#define open_kernel_object_symbol                        0x125EC
	#define open_shared_kernel_object_symbol                 0x123FC
	#define close_kernel_object_handle_symbol                0x11A1C

	#define alloc_symbol                                     0x63ED8
	#define dealloc_symbol                                   0x64314
	#define copy_to_user_symbol                              0xF85C
	#define copy_from_user_symbol                            0xFA78
	#define copy_to_process_symbol                           0xF914
	#define copy_from_process_symbol                         0xF724
	#define process_read_memory_symbol                       0x296FD8
	#define process_write_memory_symbol                      0x296E4C
	#define page_allocate_symbol                             0x5FA48
	#define page_free_symbol                                 0x5F4AC
	#define page_export_to_proc_symbol                       0x5FBE4
	#define page_unexport_from_proc_symbol                   0x5F3A0
	#define kernel_ea_to_lpar_addr_symbol                    0x6F7F0
	#define process_ea_to_lpar_addr_ex_symbol                0x76E04
	#define set_pte_symbol                                   0x5DA44
	#define map_process_memory_symbol                        0x76910
	#define panic_symbol                                     0x29C680

	#define memcpy_symbol                                    0x7DFD0
	#define memset_symbol                                    0x4E508
	#define memcmp_symbol                                    0x4D818
	#define memchr_symbol                                    0x4D7C8
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
	#define strrchr_symbol                                   0x4E7EC

	#define spin_lock_irqsave_ex_symbol                      0x29C850
	#define spin_unlock_irqrestore_ex_symbol                 0x29C824

	#define create_process_common_symbol                     0x29A64C
	#define create_process_base_symbol                       0x299D08
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x29A458

	#define ppu_thread_create_symbol                         0x13EB4
	#define ppu_thread_exit_symbol                           0x13F6C
	#define ppu_thread_join_symbol                           0x13FC0
	#define ppu_thread_delay_symbol                          0x28554
	#define create_kernel_thread_symbol                      0x248D8
	#define create_user_thread_symbol                        0x25014
	#define create_user_thread2_symbol                       0x24E38
	#define start_thread_symbol                              0x23B04
	#define run_thread_symbol                                0x23334
	#define self_threading_symbol                            0x25620
	#define register_thread_symbol                           0x296A64
	#define allocate_user_stack_symbol                       0x29724C
	#define deallocate_user_stack_symbol                     0x2971B4

	#define mutex_create_symbol                              0x13628
	#define mutex_destroy_symbol                             0x135C0
	#define mutex_lock_symbol                                0x135B8
	#define mutex_lock_ex_symbol                             0x1D914
	#define mutex_trylock_symbol                             0x135B4
	#define mutex_unlock_symbol                              0x135B0

	#define cond_create_symbol                               0x13794
	#define cond_destroy_symbol                              0x13744
	#define cond_wait_symbol                                 0x1373C
	#define cond_wait_ex_symbol                              0x1EF00
	#define cond_signal_symbol                               0x13718
	#define cond_signal_all_symbol                           0x136F4

	#define semaphore_initialize_symbol                      0x309C4
	#define semaphore_wait_ex_symbol                         0x306CC
	#define semaphore_trywait_symbol                         0x302B4
	#define semaphore_post_ex_symbol                         0x30400

	#define event_port_create_symbol                         0x13064
	#define event_port_destroy_symbol                        0x134CC
	#define event_port_connect_symbol                        0x13544
	#define event_port_disconnect_symbol                     0x13470
	#define event_port_send_symbol                           0x1305C
	#define event_port_send_ex_symbol                        0x2AFB4

	#define event_queue_create_symbol                        0x1336C
	#define event_queue_destroy_symbol                       0x132F4
	#define event_queue_receive_symbol                       0x13138
	#define event_queue_tryreceive_symbol                    0x13204

	#define cellFsOpen_symbol                                0x2C2820
	#define cellFsClose_symbol                               0x2C2688
	#define cellFsRead_symbol                                0x2C27C4
	#define cellFsWrite_symbol                               0x2C2730
	#define cellFsLseek_symbol                               0x2C1DB8
	#define cellFsStat_symbol                                0x2C203C
	#define cellFsUtime_symbol                               0x2C3A58
	#define cellFsUnlink_internal_symbol                     0x1A96E8
	#define cellFsRename_internal_symbol                     0x1A62E4

	#define cellFsUtilMount_symbol                           0x2C1B98
	#define cellFsUtilUmount_symbol                          0x2C1B6C
	#define cellFsUtilNewfs_symbol                           0x2C34F0

	#define pathdup_from_user_symbol                         0x1B1988
	#define open_path_symbol                                 0x2C2558
	#define open_fs_object_symbol                            0x190970
	#define close_fs_object_symbol                           0x18F940

	#define storage_get_device_info_symbol                   0x2A7BBC
	#define storage_get_device_config_symbol                 0x2A788C
	#define storage_open_symbol                              0x2A70E0
	#define storage_close_symbol                             0x2A767C
	#define storage_read_symbol                              0x2A65F8
	#define storage_write_symbol                             0x2A64C8
	#define storage_send_device_command_symbol               0x2A6734
	#define storage_map_io_memory_symbol                     0x2A7A78
	#define storage_unmap_io_memory_symbol                   0x2A7944
	#define new_medium_listener_object_symbol                0x96A2C
	#define delete_medium_listener_object_symbol             0x98264
	#define set_medium_event_callbacks_symbol                0x985C8

	#define cellUsbdRegisterLdd_symbol                       0x28F2CC
	#define cellUsbdUnregisterLdd_symbol                     0x28F27C
	#define cellUsbdScanStaticDescriptor_symbol              0x2904CC
	#define cellUsbdOpenPipe_symbol                          0x29057C
	#define cellUsbdClosePipe_symbol                         0x29052C
	#define cellUsbdControlTransfer_symbol                   0x290430
	#define cellUsbdBulkTransfer_symbol                      0x2903B0

	#define decrypt_func_symbol                              0x346D0
	#define lv1_call_99_wrapper_symbol                       0x4FD44
	#define modules_verification_symbol                      0x59788
	#define authenticate_program_segment_symbol              0x5ABC4

	#define prx_load_module_symbol                           0x88168
	#define prx_start_module_symbol                          0x86E34
	#define prx_stop_module_symbol                           0x8820C
	#define prx_unload_module_symbol                         0x86B68
	#define prx_get_module_info_symbol                       0x865F0
	#define prx_get_module_id_by_address_symbol              0x86500
	#define prx_get_module_id_by_name_symbol                 0x86550
	#define prx_get_module_list_symbol                       0x86670
	#define load_module_by_fd_symbol                         0x87798
	#define parse_sprx_symbol                                0x8551C
	#define open_prx_object_symbol                           0x7EB8C
	#define close_prx_object_symbol                          0x7F49C
	#define lock_prx_mutex_symbol                            0x864A8
	#define unlock_prx_mutex_symbol                          0x864B4

	#define extend_kstack_symbol                             0x6F748

	#define get_pseudo_random_number_symbol                  0x2579CC
	#define md5_reset_symbol                                 0x163C40
	#define md5_update_symbol                                0x1646E0
	#define md5_final_symbol                                 0x164860
	#define ss_get_open_psid_symbol                          0x259D94
	#define update_mgr_read_eeprom_symbol                    0x253BDC
	#define update_mgr_write_eeprom_symbol                   0x253B24
	#define update_mgr_if_get_token_symbol                   0x255540

	#define ss_params_get_update_status_symbol               0x5192C

	#define sm_get_temperature_symbol                        0x2925F8
	#define sm_get_fan_policy_symbol                         0x29198C
	#define sm_set_fan_policy_symbol                         0x293784
	#define sm_get_temperature_patch                         0xC698
	#define sm_get_fan_policy_patch                          0x9E28
	#define sm_set_fan_policy_patch                          0xA324

	#define SHA1_init_symbol                                 0x2C77E0
	#define SHA1_update_symbol                               0x2C7840
	#define SHA1_final_symbol                                0x2C79F4
	#define aescbccfb_dec_symbol                             0x2C5CD4
	#define aescbccfb_enc_symbol                             0x2C5A84
	#define get_path_by_fd_symbol                            0x1B0B2C

	#define ECDSA_1                                          0x5A180
	#define ECDSA_2                                          0x2CAC00
	#define ECDSA_FLAG                                       0x477E28
	#define sysmem_obj                                       0x477FE0
	#define qa_eeprom_offset                                 0x4896A

	#define syscall_table_symbol                             0x35BCA8
	#define syscall_call_offset                              0x2A3CD0

	#define read_bdvd0_symbol                                0x1BBE5C
	#define read_bdvd1_symbol                                0x1BDA88
	#define read_bdvd2_symbol                                0x1CAC10

	#define storage_internal_get_device_object_symbol        0x2A5F80

	#define hid_mgr_read_usb_symbol                          0x1046A8
	#define hid_mgr_read_bt_symbol                           0xFE580

	#define bt_set_controller_info_internal_symbol           0xF25F8

	#define device_event_port_send_call                      0x2AFF38
	#define device_event_port_send_call_restore              0x2431D64B

	#define ss_pid_call_1                                    0x24342C

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7EA80
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x88004

	#define shutdown_copy_params_call                        0xAABC
	#define shutdown_copy_params_call_restore                0xBD4F0048

	#define fsloop_open_call                                 0x2C29B8
	#define fsloop_close_call                                0x2C2A08
	#define fsloop_read_call                                 0x2C2A48

	#define shutdown_patch_offset                            0xAAA8
	#define module_sdk_version_patch_offset                  0x296294
	#define module_add_parameter_to_parse_sprxpatch_offset   0x87874

	#define user_thread_prio_patch                           0x201B4
	#define user_thread_prio_patch2                          0x201C4

	#define lic_patch                                        0x56CEC
	#define lic_patch_restore                                0x4826B351
	#define ode_patch                                        0x257224
	#define fix_80010009                                     0x5AA58
	#define fix_8001003D                                     0x57020
	#define fix_8001003E                                     0x570E4
	#define PATCH_JUMP                                       0x57098

	#define io_rtoc_entry_1                                 -0x178
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x6680

	#define storage_rtoc_entry_1                             0x1E50

	#define device_event_rtoc_entry_1                        0x20C0

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x3600

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x24EB8
	#define permissions_exception2                           0xC433C
	#define permissions_exception3                           0x20288

	#define patch_data1_offset                               0x3D9240
	#define patch_func2                                      0x5A140
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDA565
	#define patch_func8_offset1                              0x56F48
	#define patch_func8_offset2                              0x570A8
	#define patch_func8_offset2_restore                      0x482455D9
	#define patch_func9_offset                               0x5AA6C
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x374230

	#define mmapper_flags_temp_patch                         0x7061C

	#define rsx_syscall_check                                0x7E3C
	#define unk_func2_unregister_service                     0x986F8
	#define unk_func3_unregister_service                     0x9D18C

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002DE000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000E6000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52A00000057000
	#define PS1_EMU_HASH                                     0xCC28B000000A1000
	#define PS1_NETEMU_HASH                                  0xCC28D000000C4000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001D000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000025000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC28B00000339000
	#define BDP_BDVD_HASH                                    0xCC284000003FD000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC2680000001B000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000034000
	#define PREMO_PLUGIN_HASH                                0x3E80800000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x27B600000001F000
	#define PSP_EMULATOR_HASH                                0xCC29A00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000BF000
	#define EMULATOR_API_HASH                                0x8409F0000001E000
	#define EMULATOR_DRM_HASH                                0x74B9800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x8FFBF0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x1528

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xB18BC

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC44EC
	#define ps2tonet_size_patch                              0xC44E0
	#define vmode_patch_offset                               0x43EA78
	#define psp_drm_patch1                                   0x23C85C
	#define psp_drm_patch2                                   0x23D2F4
	#define psp_drm_patch3                                   0x23CF34
	#define psp_drm_patch4                                   0x23D73C
	#define psp_drm_patchA                                   0x23C978
	#define psp_drm_patchB                                   0x23D210
	#define psp_drm_patchC                                   0x23C3B0
	#define psp_drm_patchD                                   0x23C960
	#define psp_drm_patchE                                   0x23C964
	#define psp_drm_patchF                                   0x23D328
	#define psp_extra_drm_patch                              0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDAB8C
	#define app_home_offset                                  0x245F68

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x75728

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x22E38
	#define ps_region_error_offset                           0x6854
	#define remote_play_offset                               0x5F54
	#define ps2_nonbw_offset3                                0x16498

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB8D8

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xCAA4

	/* nas_plugin */
	#define patch1_nas                                       0x2DF00
	#define patch2_nas                                       0x2E064
	#define patch3_nas                                       0x1ED68

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F62C
	#define pspemu_path_offset                               0x4AA68
	#define psptrans_path_offset                             0x4AAD0

	/* download_plugin */
	#define elf_patch1_download                              0x366EC
	#define elf_patch2_download                              0x366F4
	#define elf_patch3_download                              0x40700
	#define elf_patch4_download                              0x41430
	#define elf_patch5_download                              0x41450
	#define elf_patch6_download                              0x41498

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x711E4
	#define elf_patch2_autodownload                          0x711EC

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x159C4C
	#define bdp_cinavia1_patch                               0x159C78

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1BE0

	/* emulator_api */
	#define psp_read                                         0xFC64
	#define psp_read_header                                  0x10BE8
	#define psp_drm_patch5                                   0x10A0C
	#define psp_drm_patch6                                   0x10A3C
	#define psp_drm_patch7                                   0x10A54
	#define psp_drm_patch8                                   0x10A58
	#define psp_drm_patch9                                   0x10B98
	#define psp_drm_patch11                                  0x10B9C
	#define psp_drm_patch12                                  0x10BAC
	#define psp_product_id_patch1                            0x10CAC
	#define psp_product_id_patch3                            0x10F84

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E35C
	#define psp_prx_patch                                    0x57478
	#define psp_savedata_bind_patch1                         0x79810
	#define psp_savedata_bind_patch2                         0x79868
	#define psp_savedata_bind_patch3                         0x79384
	#define psp_extra_savedata_patch                         0x851A8
	#define psp_prometheus_patch                             0x12E870
	#define prx_patch_call_lr                                0x585CC

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C64
	#define psp_drm_key_overwrite                            (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD5B4

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                        0xC50D0000000E7000
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH                 0xDE52A00000057000
	#define GAME_EXT_PLUGIN_REBUG_HASH                       0xCC2680000001D000
	#define dex_ps2_nonbw_offset                             0xDAFC0
	#define dex_ps2_nonbw_offset2                            0x75464
	#define dex_ps2_nonbw_offset3                            0x16788
	#define dex_ps2tonet_patch                               0xC9A30
	#define dex_ps2tonet_size_patch                          0xC9A24
	#define dex_vmode_patch_offset                           0x446650
	#define dex_psp_drm_patch1                               0x244068
	#define dex_psp_drm_patch2                               0x244B00
	#define dex_psp_drm_patch3                               0x244740
	#define dex_psp_drm_patch4                               0x244F48
	#define dex_psp_drm_patchA                               0x244184
	#define dex_psp_drm_patchB                               0x244A1C
	#define dex_psp_drm_patchC                               0x243BBC
	#define dex_psp_drm_patchD                               0x24416C
	#define dex_psp_drm_patchE                               0x244170
	#define dex_psp_drm_patchF                               0x244B34
	#define dex_psp_extra_drm_patch                          0x0
#endif

#ifdef FIRMWARE_421D

	#define FIRMWARE_VERSION                                 0x421

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003F7A30ULL
		#define PS3MAPI_IDPS_2                               0x800000000048FE9CULL
		#define PS3MAPI_PSID                                 0x800000000048FEB4ULL
	#endif
	#define FIRMWARE_DEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x363E80

	#define create_kernel_object_symbol                      0x125E4
	#define destroy_kernel_object_symbol                     0x11F48
	#define destroy_shared_kernel_object_symbol              0x118BC
	#define open_kernel_object_symbol                        0x12C34
	#define open_shared_kernel_object_symbol                 0x12A44
	#define close_kernel_object_handle_symbol                0x12064

	#define alloc_symbol                                     0x677F0
	#define dealloc_symbol                                   0x67C2C
	#define copy_to_user_symbol                              0xFEA4
	#define copy_from_user_symbol                            0x100C0
	#define copy_to_process_symbol                           0xFF5C
	#define copy_from_process_symbol                         0xFD6C
	#define process_read_memory_symbol                       0x29D83C
	#define process_write_memory_symbol                      0x29D6B0
	#define page_allocate_symbol                             0x63360
	#define page_free_symbol                                 0x62DC4
	#define page_export_to_proc_symbol                       0x634FC
	#define page_unexport_from_proc_symbol                   0x62CB8
	#define kernel_ea_to_lpar_addr_symbol                    0x73288
	#define process_ea_to_lpar_addr_ex_symbol                0x7AE28
	#define set_pte_symbol                                   0x6135C
	#define map_process_memory_symbol                        0x7A934
	#define panic_symbol                                     0x2A44D8

	#define memcpy_symbol                                    0x81FF4
	#define memset_symbol                                    0x51DF8
	#define memcmp_symbol                                    0x51108
	#define memchr_symbol                                    0x510B8
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
	#define strrchr_symbol                                   0x520DC

	#define spin_lock_irqsave_ex_symbol                      0x2A46A8
	#define spin_unlock_irqrestore_ex_symbol                 0x2A467C

	#define create_process_common_symbol                     0x2A14C0
	#define create_process_base_symbol                       0x2A0B58
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x2A12C0

	#define ppu_thread_create_symbol                         0x14530
	#define ppu_thread_exit_symbol                           0x145E8
	#define ppu_thread_join_symbol                           0x1463C
	#define ppu_thread_delay_symbol                          0x2A3E0
	#define create_kernel_thread_symbol                      0x264D0
	#define create_user_thread_symbol                        0x26C0C
	#define create_user_thread2_symbol                       0x26A30
	#define start_thread_symbol                              0x25568
	#define run_thread_symbol                                0x24D2C
	#define self_threading_symbol                            0x27218
	#define register_thread_symbol                           0x29D2C8
	#define allocate_user_stack_symbol                       0x29DAB0
	#define deallocate_user_stack_symbol                     0x29DA18

	#define mutex_create_symbol                              0x13C78
	#define mutex_destroy_symbol                             0x13C10
	#define mutex_lock_symbol                                0x13C08
	#define mutex_lock_ex_symbol                             0x1F30C
	#define mutex_trylock_symbol                             0x13C04
	#define mutex_unlock_symbol                              0x13C00

	#define cond_create_symbol                               0x13DE4
	#define cond_destroy_symbol                              0x13D94
	#define cond_wait_symbol                                 0x13D8C
	#define cond_wait_ex_symbol                              0x208F8
	#define cond_signal_symbol                               0x13D68
	#define cond_signal_all_symbol                           0x13D44

	#define semaphore_initialize_symbol                      0x3422C
	#define semaphore_wait_ex_symbol                         0x33F34
	#define semaphore_trywait_symbol                         0x33B1C
	#define semaphore_post_ex_symbol                         0x33C68

	#define event_port_create_symbol                         0x136B4
	#define event_port_destroy_symbol                        0x13B1C
	#define event_port_connect_symbol                        0x13B94
	#define event_port_disconnect_symbol                     0x13AC0
	#define event_port_send_symbol                           0x136AC
	#define event_port_send_ex_symbol                        0x2CFC0

	#define event_queue_create_symbol                        0x139BC
	#define event_queue_destroy_symbol                       0x13944
	#define event_queue_receive_symbol                       0x13788
	#define event_queue_tryreceive_symbol                    0x13854

	#define cellFsOpen_symbol                                0x2D99E0
	#define cellFsClose_symbol                               0x2D9848
	#define cellFsRead_symbol                                0x2D9984
	#define cellFsWrite_symbol                               0x2D98F0
	#define cellFsLseek_symbol                               0x2D9144
	#define cellFsStat_symbol                                0x2D91FC
	#define cellFsUtime_symbol                               0x2DAAAC
	#define cellFsUnlink_internal_symbol                     0x1AF9BC
	#define cellFsRename_internal_symbol                     0x1AC5B8

	#define cellFsUtilMount_symbol                           0x2D8EB8
	#define cellFsUtilUmount_symbol                          0x2D8E8C
	#define cellFsUtilNewfs_symbol                           0x2DA744

	#define pathdup_from_user_symbol                         0x1B7D78
	#define open_path_symbol                                 0x2D9718
	#define open_fs_object_symbol                            0x196C44
	#define close_fs_object_symbol                           0x195C14

	#define storage_get_device_info_symbol                   0x2BA4DC
	#define storage_get_device_config_symbol                 0x2B9048
	#define storage_open_symbol                              0x2BA704
	#define storage_close_symbol                             0x2B8B68
	#define storage_read_symbol                              0x2B80E8
	#define storage_write_symbol                             0x2B7FB8
	#define storage_send_device_command_symbol               0x2B7C08
	#define storage_map_io_memory_symbol                     0x2BA388
	#define storage_unmap_io_memory_symbol                   0x2BA244
	#define new_medium_listener_object_symbol                0x9C0E4
	#define delete_medium_listener_object_symbol             0x9D91C
	#define set_medium_event_callbacks_symbol                0x9DC80

	#define cellUsbdRegisterLdd_symbol                       0x2956E8
	#define cellUsbdUnregisterLdd_symbol                     0x295698
	#define cellUsbdScanStaticDescriptor_symbol              0x2968E8
	#define cellUsbdOpenPipe_symbol                          0x296998
	#define cellUsbdClosePipe_symbol                         0x296948
	#define cellUsbdControlTransfer_symbol                   0x29684C
	#define cellUsbdBulkTransfer_symbol                      0x2967CC

	#define decrypt_func_symbol                              0x37F38
	#define lv1_call_99_wrapper_symbol                       0x53634
	#define modules_verification_symbol                      0x5D0A0
	#define authenticate_program_segment_symbol              0x5E4DC

	#define prx_load_module_symbol                           0x8C7B4
	#define prx_start_module_symbol                          0x8B480
	#define prx_stop_module_symbol                           0x8C858
	#define prx_unload_module_symbol                         0x8B1B4
	#define prx_get_module_info_symbol                       0x8ABAC
	#define prx_get_module_id_by_address_symbol              0x8AABC
	#define prx_get_module_id_by_name_symbol                 0x8AB0C
	#define prx_get_module_list_symbol                       0x8AC2C
	#define load_module_by_fd_symbol                         0x8BDE4
	#define parse_sprx_symbol                                0x89AD8
	#define open_prx_object_symbol                           0x82BB0
	#define close_prx_object_symbol                          0x834C0
	#define lock_prx_mutex_symbol                            0x8AA64
	#define unlock_prx_mutex_symbol                          0x8AA70

	#define extend_kstack_symbol                             0x731E0

	#define get_pseudo_random_number_symbol                  0x25DDE8
	#define md5_reset_symbol                                 0x169F14
	#define md5_update_symbol                                0x16A9B4
	#define md5_final_symbol                                 0x16AB34
	#define ss_get_open_psid_symbol                          0x2601B0
	#define update_mgr_read_eeprom_symbol                    0x259FE0
	#define update_mgr_write_eeprom_symbol                   0x259F14
	#define update_mgr_if_get_token_symbol                   0x25B95C

	#define ss_params_get_update_status_symbol               0x5521C

	#define sm_get_temperature_symbol                        0x298A14
	#define sm_get_fan_policy_symbol                         0x297DA8
	#define sm_set_fan_policy_symbol                         0x299D70
	#define sm_get_temperature_patch                         0xC718
	#define sm_get_fan_policy_patch                          0x9EA8
	#define sm_set_fan_policy_patch                          0xA3A4

	#define SHA1_init_symbol                                 0x2E1F58
	#define SHA1_update_symbol                               0x2E1FB8
	#define SHA1_final_symbol                                0x2E216C
	#define aescbccfb_dec_symbol                             0x2E044C
	#define aescbccfb_enc_symbol                             0x2E01FC
	#define get_path_by_fd_symbol                            0x1B6F1C

	#define ECDSA_1                                          0x5DA98
	#define ECDSA_2                                          0x2E5378
	#define ECDSA_FLAG                                       0x48FE28
	#define sysmem_obj                                       0x48FFE0
	#define qa_eeprom_offset                                 0x4C216

	#define syscall_table_symbol                             0x37A1B0
	#define syscall_call_offset                              0x2ABD90

	#define read_bdvd0_symbol                                0x1C224C
	#define read_bdvd1_symbol                                0x1C3E78
	#define read_bdvd2_symbol                                0x1D1000

	#define storage_internal_get_device_object_symbol        0x2B76C0

	#define hid_mgr_read_usb_symbol                          0x10A0F4
	#define hid_mgr_read_bt_symbol                           0x103FCC

	#define bt_set_controller_info_internal_symbol           0xF8044

	#define device_event_port_send_call                      0x2C44E8
	#define device_event_port_send_call_restore              0xC4F1D44B

	#define ss_pid_call_1                                    0x24981C

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x82AA4
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x8C650

	#define shutdown_copy_params_call                        0xAB3C
	#define shutdown_copy_params_call_restore                0x85550048

	#define fsloop_open_call                                 0x2D9B78
	#define fsloop_close_call                                0x2D9BC8
	#define fsloop_read_call                                 0x2D9C08

	#define shutdown_patch_offset                            0xAB28
	#define module_sdk_version_patch_offset                  0x29C8F0
	#define module_add_parameter_to_parse_sprxpatch_offset   0x8BEC0

	#define user_thread_prio_patch                           0x21BAC
	#define user_thread_prio_patch2                          0x21BBC

	#define lic_patch                                        0x5A604
	#define lic_patch_restore                                0x4827EBF9
	#define ode_patch                                        0x25D640
	#define fix_80010009                                     0x5E370
	#define fix_8001003D                                     0x5A938
	#define fix_8001003E                                     0x5A9FC
	#define PATCH_JUMP                                       0x5A9B0

	#define io_rtoc_entry_1                                 -0x48
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65A0

	#define storage_rtoc_entry_1                             0x2328

	#define device_event_rtoc_entry_1                        0x26B0

	#define time_rtoc_entry_1                               -0x75E0
	#define time_rtoc_entry_2                               -0x75E8

	#define thread_rtoc_entry_1                             -0x7660

	#define process_rtoc_entry_1                            -0x77A0

	#define bt_rtoc_entry_1                                 -0x34D8

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x26AB0
	#define permissions_exception2                           0xC99F4
	#define permissions_exception3                           0x21C80

	#define patch_data1_offset                               0x3F7A40
	#define patch_func2                                      0x5DA58
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDA4B5
	#define patch_func8_offset1                              0x5A860
	#define patch_func8_offset2                              0x5A9C0
	#define patch_func8_offset2_restore                      0x48249B19
	#define patch_func9_offset                               0x5E384
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x392A30

	#define mmapper_flags_temp_patch                         0x741F4

	#define rsx_syscall_check                                0x7E3C
	#define unk_func2_unregister_service                     0x9DDB0
	#define unk_func3_unregister_service                     0xA2844

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E2000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000E7000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52A00000057000
	#define PS1_EMU_HASH                                     0xCC28B000000A1000
	#define PS1_NETEMU_HASH                                  0xCC28D000000C4000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001D000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000026000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC28B00000339000
	#define BDP_BDVD_HASH                                    0xCC284000003FD000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC2680000001B000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000034000
	#define PREMO_PLUGIN_HASH                                0x3E80800000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x27B600000001F000
	#define PSP_EMULATOR_HASH                                0xCC29A00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000BF000
	#define EMULATOR_API_HASH                                0x8409F0000001E000
	#define EMULATOR_DRM_HASH                                0x74B9800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x8FFBF0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x1528

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xB18BC

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC9A30
	#define ps2tonet_size_patch                              0xC9A24
	#define vmode_patch_offset                               0x446650
	#define psp_drm_patch1                                   0x244068
	#define psp_drm_patch2                                   0x244B00
	#define psp_drm_patch3                                   0x244740
	#define psp_drm_patch4                                   0x244F48
	#define psp_drm_patchA                                   0x244184
	#define psp_drm_patchB                                   0x244A1C
	#define psp_drm_patchC                                   0x243BBC
	#define psp_drm_patchD                                   0x24416C
	#define psp_drm_patchE                                   0x244170
	#define psp_drm_patchF                                   0x244B34
	#define psp_extra_drm_patch                              0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDAFC0
	#define app_home_offset                                  0x246BD8

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x75464

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23054
	#define ps_region_error_offset                           0x6810
	#define remote_play_offset                               0x5F54
	#define ps2_nonbw_offset3                                0x16788

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB8D8

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xCAA4

	/* nas_plugin */
	#define patch1_nas                                       0x2E320
	#define patch2_nas                                       0x2E484
	#define patch3_nas                                       0x1F028

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x20114
	#define pspemu_path_offset                               0x4BBF8
	#define psptrans_path_offset                             0x4BC88

	/* download_plugin */
	#define elf_patch1_download                              0x36680
	#define elf_patch2_download                              0x36688
	#define elf_patch3_download                              0x40618
	#define elf_patch4_download                              0x41348
	#define elf_patch5_download                              0x41368
	#define elf_patch6_download                              0x413B0

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x71094
	#define elf_patch2_autodownload                          0x7109C

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x159C4C
	#define bdp_cinavia1_patch                               0x159C78

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1BE0

	/* emulator_api */
	#define psp_read                                         0xFC64
	#define psp_read_header                                  0x10BE8
	#define psp_drm_patch5                                   0x10A0C
	#define psp_drm_patch6                                   0x10A3C
	#define psp_drm_patch7                                   0x10A54
	#define psp_drm_patch8                                   0x10A58
	#define psp_drm_patch9                                   0x10B98
	#define psp_drm_patch11                                  0x10B9C
	#define psp_drm_patch12                                  0x10BAC
	#define psp_product_id_patch1                            0x10CAC
	#define psp_product_id_patch3                            0x10F84

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E35C
	#define psp_prx_patch                                    0x57478
	#define psp_savedata_bind_patch1                         0x79810
	#define psp_savedata_bind_patch2                         0x79868
	#define psp_savedata_bind_patch3                         0x79384
	#define psp_extra_savedata_patch                         0x851A8
	#define psp_prometheus_patch                             0x12E870
	#define prx_patch_call_lr                                0x585CC

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C64
	#define psp_drm_key_overwrite                            (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD5B4

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* CEX */
	#define cex_ps2tonet_patch                               0xC44EC
	#define cex_ps2tonet_size_patch                          0xC44E0
	#define cex_vmode_patch_offset                           0x43EA78
	#define cex_psp_drm_patch1                               0x23C85C
	#define cex_psp_drm_patch2                               0x23D2F4
	#define cex_psp_drm_patch3                               0x23CF34
	#define cex_psp_drm_patch4                               0x23D73C
	#define cex_psp_drm_patchA                               0x23C978
	#define cex_psp_drm_patchB                               0x23D210
	#define cex_psp_drm_patchC                               0x23C3B0
	#define cex_psp_drm_patchD                               0x23C960
	#define cex_psp_drm_patchE                               0x23C964
	#define cex_psp_drm_patchF                               0x23D328
	#define cex_psp_extra_drm_patch                          0x0
#endif

#ifdef FIRMWARE_430C

	#define FIRMWARE_VERSION                                 0x430

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003DB1B0ULL
		#define PS3MAPI_IDPS_2                               0x8000000000476F3CULL
		#define PS3MAPI_PSID                                 0x8000000000476F54ULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x348200

	#define create_kernel_object_symbol                      0x11F98
	#define destroy_kernel_object_symbol                     0x118FC
	#define destroy_shared_kernel_object_symbol              0x11270
	#define open_kernel_object_symbol                        0x125E8
	#define open_shared_kernel_object_symbol                 0x123F8
	#define close_kernel_object_handle_symbol                0x11A18

	#define alloc_symbol                                     0x64028
	#define dealloc_symbol                                   0x64464
	#define copy_to_user_symbol                              0xF858
	#define copy_from_user_symbol                            0xFA74
	#define copy_to_process_symbol                           0xF910
	#define copy_from_process_symbol                         0xF720
	#define process_read_memory_symbol                       0x298748
	#define process_write_memory_symbol                      0x2985BC
	#define page_allocate_symbol                             0x5FB98
	#define page_free_symbol                                 0x5F5FC
	#define page_export_to_proc_symbol                       0x5FD34
	#define page_unexport_from_proc_symbol                   0x5F4F0
	#define kernel_ea_to_lpar_addr_symbol                    0x6F91C
	#define process_ea_to_lpar_addr_ex_symbol                0x76F30
	#define set_pte_symbol                                   0x5DB94
	#define map_process_memory_symbol                        0x76A3C
	#define panic_symbol                                     0x29DDF0

	#define memcpy_symbol                                    0x7E0FC
	#define memset_symbol                                    0x4E544
	#define memcmp_symbol                                    0x4D854
	#define memchr_symbol                                    0x4D804
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
	#define strrchr_symbol                                   0x4E828

	#define spin_lock_irqsave_ex_symbol                      0x29DFC0
	#define spin_unlock_irqrestore_ex_symbol                 0x29DF94

	#define create_process_common_symbol                     0x29BDBC
	#define create_process_base_symbol                       0x29B478
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x29BBC8

	#define ppu_thread_create_symbol                         0x13EB0
	#define ppu_thread_exit_symbol                           0x13F68
	#define ppu_thread_join_symbol                           0x13FBC
	#define ppu_thread_delay_symbol                          0x28550
	#define create_kernel_thread_symbol                      0x248D4
	#define create_user_thread_symbol                        0x25010
	#define create_user_thread2_symbol                       0x24E34
	#define start_thread_symbol                              0x23B00
	#define run_thread_symbol                                0x23330
	#define self_threading_symbol                            0x2561C
	#define register_thread_symbol                           0x2981D4
	#define allocate_user_stack_symbol                       0x2989BC
	#define deallocate_user_stack_symbol                     0x298924

	#define mutex_create_symbol                              0x13624
	#define mutex_destroy_symbol                             0x135BC
	#define mutex_lock_symbol                                0x135B4
	#define mutex_lock_ex_symbol                             0x1D910
	#define mutex_trylock_symbol                             0x135B0
	#define mutex_unlock_symbol                              0x135AC

	#define cond_create_symbol                               0x13790
	#define cond_destroy_symbol                              0x13740
	#define cond_wait_symbol                                 0x13738
	#define cond_wait_ex_symbol                              0x1EEFC
	#define cond_signal_symbol                               0x13714
	#define cond_signal_all_symbol                           0x136F0

	#define semaphore_initialize_symbol                      0x30A00
	#define semaphore_wait_ex_symbol                         0x30708
	#define semaphore_trywait_symbol                         0x302F0
	#define semaphore_post_ex_symbol                         0x3043C

	#define event_port_create_symbol                         0x13060
	#define event_port_destroy_symbol                        0x134C8
	#define event_port_connect_symbol                        0x13540
	#define event_port_disconnect_symbol                     0x1346C
	#define event_port_send_symbol                           0x13058
	#define event_port_send_ex_symbol                        0x2AFB0

	#define event_queue_create_symbol                        0x13368
	#define event_queue_destroy_symbol                       0x132F0
	#define event_queue_receive_symbol                       0x13134
	#define event_queue_tryreceive_symbol                    0x13200

	#define cellFsOpen_symbol                                0x2C3F9C
	#define cellFsClose_symbol                               0x2C3E04
	#define cellFsRead_symbol                                0x2C3F40
	#define cellFsWrite_symbol                               0x2C3EAC
	#define cellFsLseek_symbol                               0x2C3534
	#define cellFsStat_symbol                                0x2C37B8
	#define cellFsUtime_symbol                               0x2C51D4
	#define cellFsUnlink_internal_symbol                     0x1AA184
	#define cellFsRename_internal_symbol                     0x1A6D54

	#define cellFsUtilMount_symbol                           0x2C3314
	#define cellFsUtilUmount_symbol                          0x2C32E8
	#define cellFsUtilNewfs_symbol                           0x2C4C6C

	#define pathdup_from_user_symbol                         0x1B1DC4
	#define open_path_symbol                                 0x2C3CD4
	#define open_fs_object_symbol                            0x1913E8
	#define close_fs_object_symbol                           0x1903B8

	#define storage_get_device_info_symbol                   0x2A932C
	#define storage_get_device_config_symbol                 0x2A8FFC
	#define storage_open_symbol                              0x2A8850
	#define storage_close_symbol                             0x2A8DEC
	#define storage_read_symbol                              0x2A7D68
	#define storage_write_symbol                             0x2A7C38
	#define storage_send_device_command_symbol               0x2A7EA4
	#define storage_map_io_memory_symbol                     0x2A91E8
	#define storage_unmap_io_memory_symbol                   0x2A90B4
	#define new_medium_listener_object_symbol                0x96B3C
	#define delete_medium_listener_object_symbol             0x98374
	#define set_medium_event_callbacks_symbol                0x986D8

	#define cellUsbdRegisterLdd_symbol                       0x290B30
	#define cellUsbdUnregisterLdd_symbol                     0x290AE0
	#define cellUsbdScanStaticDescriptor_symbol              0x291D30
	#define cellUsbdOpenPipe_symbol                          0x291DE0
	#define cellUsbdClosePipe_symbol                         0x291D90
	#define cellUsbdControlTransfer_symbol                   0x291C94
	#define cellUsbdBulkTransfer_symbol                      0x291C14

	#define decrypt_func_symbol                              0x3470C
	#define lv1_call_99_wrapper_symbol                       0x4FD80
	#define modules_verification_symbol                      0x598D8
	#define authenticate_program_segment_symbol              0x5AD14

	#define prx_load_module_symbol                           0x88294
	#define prx_start_module_symbol                          0x86F60
	#define prx_stop_module_symbol                           0x88338
	#define prx_unload_module_symbol                         0x86C94
	#define prx_get_module_info_symbol                       0x8671C
	#define prx_get_module_id_by_address_symbol              0x8662C
	#define prx_get_module_id_by_name_symbol                 0x8667C
	#define prx_get_module_list_symbol                       0x8679C
	#define load_module_by_fd_symbol                         0x878C4
	#define parse_sprx_symbol                                0x85648
	#define open_prx_object_symbol                           0x7ECB8
	#define close_prx_object_symbol                          0x7F5C8
	#define lock_prx_mutex_symbol                            0x865D4
	#define unlock_prx_mutex_symbol                          0x865E0

	#define extend_kstack_symbol                             0x6F874

	#define get_pseudo_random_number_symbol                  0x2591C8
	#define md5_reset_symbol                                 0x163D60
	#define md5_update_symbol                                0x164800
	#define md5_final_symbol                                 0x164980
	#define ss_get_open_psid_symbol                          0x25B590
	#define update_mgr_read_eeprom_symbol                    0x254DD4
	#define update_mgr_write_eeprom_symbol                   0x254D1C
	#define update_mgr_if_get_token_symbol                   0x256738

	#define ss_params_get_update_status_symbol               0x5198C

	#define sm_get_temperature_symbol                        0x293E5C
	#define sm_get_fan_policy_symbol                         0x2931F0
	#define sm_set_fan_policy_symbol                         0x294FE8
	#define sm_get_temperature_patch                         0xC694
	#define sm_get_fan_policy_patch                          0x9E28
	#define sm_set_fan_policy_patch                          0xA324

	#define SHA1_init_symbol                                 0x2C8F5C
	#define SHA1_update_symbol                               0x2C8FBC
	#define SHA1_final_symbol                                0x2C9170
	#define aescbccfb_dec_symbol                             0x2C7450
	#define aescbccfb_enc_symbol                             0x2C7200
	#define get_path_by_fd_symbol                            0x1B1660

	#define ECDSA_1                                          0x5A2D0
	#define ECDSA_2                                          0x2CC37C
	#define ECDSA_FLAG                                       0x476EC8
	#define sysmem_obj                                       0x477080
	#define qa_eeprom_offset                                 0x489A6

	#define syscall_table_symbol                             0x35DBE0
	#define syscall_call_offset                              0x2A5440

	#define read_bdvd0_symbol                                0x1BCD24
	#define read_bdvd1_symbol                                0x1BE950
	#define read_bdvd2_symbol                                0x1CBB08

	#define storage_internal_get_device_object_symbol        0x2A76F0

	#define hid_mgr_read_usb_symbol                          0x1047C8
	#define hid_mgr_read_bt_symbol                           0xFE6A0

	#define bt_set_controller_info_internal_symbol           0xF2718

	#define device_event_port_send_call                      0x2B16A8
	#define device_event_port_send_call_restore              0xB019D64B

	#define ss_pid_call_1                                    0x2445F8

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7EBAC
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x88130

	#define shutdown_copy_params_call                        0xAABC
	#define shutdown_copy_params_call_restore                0xB94F0048

	#define fsloop_open_call                                 0x2C4134
	#define fsloop_close_call                                0x2C4184
	#define fsloop_read_call                                 0x2C41C4

	#define shutdown_patch_offset                            0xAAA8
	#define module_sdk_version_patch_offset                  0x297A04
	#define module_add_parameter_to_parse_sprxpatch_offset   0x879A0

	#define user_thread_prio_patch                           0x201B0
	#define user_thread_prio_patch2                          0x201C0

	#define lic_patch                                        0x56E3C
	#define lic_patch_restore                                0x4826C97D
	#define ode_patch                                        0x2587D0
	#define fix_80010009                                     0x5ABA8
	#define fix_8001003D                                     0x57170
	#define fix_8001003E                                     0x57234
	#define PATCH_JUMP                                       0x571E8

	#define io_rtoc_entry_1                                 -0x178
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x6680

	#define storage_rtoc_entry_1                             0x1E40

	#define device_event_rtoc_entry_1                        0x20B0

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x3600

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x24EB4
	#define permissions_exception2                           0xC444C
	#define permissions_exception3                           0x20284

	#define patch_data1_offset                               0x3DB1C0
	#define patch_func2                                      0x5A290
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDA451
	#define patch_func8_offset1                              0x57098
	#define patch_func8_offset2                              0x571F8
	#define patch_func8_offset2_restore                      0x48246BF9
	#define patch_func9_offset                               0x5ABBC
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x3761B0

	#define mmapper_flags_temp_patch                         0x70748

	#define rsx_syscall_check                                0x7E3C
	#define unk_func2_unregister_service                     0x98808
	#define unk_func3_unregister_service                     0x9D29C

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002DF000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EB000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52E00000056000
	#define PS1_EMU_HASH                                     0xCC28B000000A1000
	#define PS1_NETEMU_HASH                                  0xCC28D000000C4000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001D000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000026000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC28B00000339000
	#define BDP_BDVD_HASH                                    0xCC284000003FD000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC2680000001D000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000034000
	#define PREMO_PLUGIN_HASH                                0x3E80800000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x27B600000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000BF000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0xC02C70000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x1528

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xB19CC

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4D64
	#define ps2tonet_size_patch                              0xC4D58
	#define vmode_patch_offset                               0x4400CC
	#define psp_drm_patch1                                   0x23D27C
	#define psp_drm_patch2                                   0x23DD1C
	#define psp_drm_patch3                                   0x23D958
	#define psp_drm_patch4                                   0x23E164
	#define psp_drm_patchA                                   0x23D398
	#define psp_drm_patchB                                   0x23DC38
	#define psp_drm_patchC                                   0x23CDD0
	#define psp_drm_patchD                                   0x23D380
	#define psp_drm_patchE                                   0x23D384
	#define psp_drm_patchF                                   0x23DD50
	#define psp_extra_drm_patch                              0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDDDC8
	#define app_home_offset                                  0x250560

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x69B68

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x2364C
	#define ps_region_error_offset                           0x699C
	#define remote_play_offset                               0x609C
	#define ps2_nonbw_offset3                                0x167D8

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB8D8

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xCAA4

	/* nas_plugin */
	#define patch1_nas                                       0x2E6E0
	#define patch2_nas                                       0x2E844
	#define patch3_nas                                       0x1F4CC

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F678
	#define pspemu_path_offset                               0x4B148
	#define psptrans_path_offset                             0x4B1D8

	/* download_plugin */
	#define elf_patch1_download                              0x3B0B8
	#define elf_patch2_download                              0x3B0C0
	#define elf_patch3_download                              0x452B0
	#define elf_patch4_download                              0x46030
	#define elf_patch5_download                              0x46050
	#define elf_patch6_download                              0x46098

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x717FC
	#define elf_patch2_autodownload                          0x71804

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x159C4C
	#define bdp_cinavia1_patch                               0x159C78

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C10

	/* emulator_api */
	#define psp_read                                         0xFB24
	#define psp_read_header                                  0x10AA8
	#define psp_drm_patch5                                   0x108CC
	#define psp_drm_patch6                                   0x108FC
	#define psp_drm_patch7                                   0x10914
	#define psp_drm_patch8                                   0x10918
	#define psp_drm_patch9                                   0x10A58
	#define psp_drm_patch11                                  0x10A5C
	#define psp_drm_patch12                                  0x10A6C
	#define psp_product_id_patch1                            0x10B6C
	#define psp_product_id_patch3                            0x10E44

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E340
	#define psp_prx_patch                                    0x5745C
	#define psp_savedata_bind_patch1                         0x79810
	#define psp_savedata_bind_patch2                         0x79868
	#define psp_savedata_bind_patch3                         0x79384
	#define psp_extra_savedata_patch                         0x85194
	#define psp_prometheus_patch                             0x12E870
	#define prx_patch_call_lr                                0x585B0

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46D4
	#define psp_savedata_patch2                              0x46AC
	#define psp_savedata_patch3                              0x450C
	#define psp_savedata_patch4                              0x4544
	#define psp_savedata_patch5                              0x4558
	#define psp_savedata_patch6                              0x46C0

	/* libfs */
	#define aio_copy_root_offset                             0xD5B4

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                        0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH                 0xDE52D00000057000
	#define GAME_EXT_PLUGIN_REBUG_HASH                       0xCC2680000001D000
	#define dex_ps2_nonbw_offset                             0xDE1F4
	#define dex_ps2_nonbw_offset2                            0x6989C
	#define dex_ps2_nonbw_offset3                            0x16AC8
	#define dex_ps2tonet_patch                               0xCA2B8
	#define dex_ps2tonet_size_patch                          0xCA2AC
	#define dex_vmode_patch_offset                           0x447CB0
	#define dex_psp_drm_patch1                               0x244A94
	#define dex_psp_drm_patch2                               0x245534
	#define dex_psp_drm_patch3                               0x245170
	#define dex_psp_drm_patch4                               0x24597C
	#define dex_psp_drm_patchA                               0x244BB0
	#define dex_psp_drm_patchB                               0x245450
	#define dex_psp_drm_patchC                               0x2445E8
	#define dex_psp_drm_patchD                               0x244B98
	#define dex_psp_drm_patchE                               0x244B9C
	#define dex_psp_drm_patchF                               0x245568
	#define dex_psp_extra_drm_patch                          0x0
#endif

#ifdef FIRMWARE_430D

	#define FIRMWARE_VERSION                                 0x430

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003F9930ULL
		#define PS3MAPI_IDPS_2                               0x8000000000496F3CULL
		#define PS3MAPI_PSID                                 0x8000000000496F54ULL
	#endif
	#define FIRMWARE_DEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x365CA0

	#define create_kernel_object_symbol                      0x125E0
	#define destroy_kernel_object_symbol                     0x11F44
	#define destroy_shared_kernel_object_symbol              0x118B8
	#define open_kernel_object_symbol                        0x12C30
	#define open_shared_kernel_object_symbol                 0x12A40
	#define close_kernel_object_handle_symbol                0x12060

	#define alloc_symbol                                     0x67940
	#define dealloc_symbol                                   0x67D7C
	#define copy_to_user_symbol                              0xFEA0
	#define copy_from_user_symbol                            0x100BC
	#define copy_to_process_symbol                           0xFF58
	#define copy_from_process_symbol                         0xFD68
	#define process_read_memory_symbol                       0x29EFAC
	#define process_write_memory_symbol                      0x29EE20
	#define page_allocate_symbol                             0x634B0
	#define page_free_symbol                                 0x62F14
	#define page_export_to_proc_symbol                       0x6364C
	#define page_unexport_from_proc_symbol                   0x62E08
	#define kernel_ea_to_lpar_addr_symbol                    0x733B4
	#define process_ea_to_lpar_addr_ex_symbol                0x7AF54
	#define set_pte_symbol                                   0x614AC
	#define map_process_memory_symbol                        0x7AA60
	#define panic_symbol                                     0x2A5C00

	#define memcpy_symbol                                    0x82120
	#define memset_symbol                                    0x51E34
	#define memcmp_symbol                                    0x51144
	#define memchr_symbol                                    0x510F4
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
	#define strrchr_symbol                                   0x52118

	#define spin_lock_irqsave_ex_symbol                      0x2A5DD0
	#define spin_unlock_irqrestore_ex_symbol                 0x2A5DA4

	#define create_process_common_symbol                     0x2A2C30
	#define create_process_base_symbol                       0x2A22C8
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x2A2A30

	#define ppu_thread_create_symbol                         0x1452C
	#define ppu_thread_exit_symbol                           0x145E4
	#define ppu_thread_join_symbol                           0x14638
	#define ppu_thread_delay_symbol                          0x2A3DC
	#define create_kernel_thread_symbol                      0x264CC
	#define create_user_thread_symbol                        0x26C08
	#define create_user_thread2_symbol                       0x26A2C
	#define start_thread_symbol                              0x25564
	#define run_thread_symbol                                0x24D28
	#define self_threading_symbol                            0x27214
	#define register_thread_symbol                           0x29EA38
	#define allocate_user_stack_symbol                       0x29F220
	#define deallocate_user_stack_symbol                     0x29F188

	#define mutex_create_symbol                              0x13C74
	#define mutex_destroy_symbol                             0x13C0C
	#define mutex_lock_symbol                                0x13C04
	#define mutex_lock_ex_symbol                             0x1F308
	#define mutex_trylock_symbol                             0x13C00
	#define mutex_unlock_symbol                              0x13BFC

	#define cond_create_symbol                               0x13DE0
	#define cond_destroy_symbol                              0x13D90
	#define cond_wait_symbol                                 0x13D88
	#define cond_wait_ex_symbol                              0x208F4
	#define cond_signal_symbol                               0x13D64
	#define cond_signal_all_symbol                           0x13D40

	#define semaphore_initialize_symbol                      0x34268
	#define semaphore_wait_ex_symbol                         0x33F70
	#define semaphore_trywait_symbol                         0x33B58
	#define semaphore_post_ex_symbol                         0x33CA4

	#define event_port_create_symbol                         0x136B0
	#define event_port_destroy_symbol                        0x13B18
	#define event_port_connect_symbol                        0x13B90
	#define event_port_disconnect_symbol                     0x13ABC
	#define event_port_send_symbol                           0x136A8
	#define event_port_send_ex_symbol                        0x2CFBC

	#define event_queue_create_symbol                        0x139B8
	#define event_queue_destroy_symbol                       0x13940
	#define event_queue_receive_symbol                       0x13784
	#define event_queue_tryreceive_symbol                    0x13850

	#define cellFsOpen_symbol                                0x2DB114
	#define cellFsClose_symbol                               0x2DAF7C
	#define cellFsRead_symbol                                0x2DB0B8
	#define cellFsWrite_symbol                               0x2DB024
	#define cellFsLseek_symbol                               0x2DA878
	#define cellFsStat_symbol                                0x2DA930
	#define cellFsUtime_symbol                               0x2DC1E0
	#define cellFsUnlink_internal_symbol                     0x1B0458
	#define cellFsRename_internal_symbol                     0x1AD028

	#define cellFsUtilMount_symbol                           0x2DA5EC
	#define cellFsUtilUmount_symbol                          0x2DA5C0
	#define cellFsUtilNewfs_symbol                           0x2DBE78

	#define pathdup_from_user_symbol                         0x1B81B4
	#define open_path_symbol                                 0x2DAE4C
	#define open_fs_object_symbol                            0x1976BC
	#define close_fs_object_symbol                           0x19668C

	#define storage_get_device_info_symbol                   0x2BBC04
	#define storage_get_device_config_symbol                 0x2BA770
	#define storage_open_symbol                              0x2BBE2C
	#define storage_close_symbol                             0x2BA290
	#define storage_read_symbol                              0x2B9810
	#define storage_write_symbol                             0x2B96E0
	#define storage_send_device_command_symbol               0x2B9330
	#define storage_map_io_memory_symbol                     0x2BBAB0
	#define storage_unmap_io_memory_symbol                   0x2BB96C
	#define new_medium_listener_object_symbol                0x9C1F4
	#define delete_medium_listener_object_symbol             0x9DA2C
	#define set_medium_event_callbacks_symbol                0x9DD90

	#define cellUsbdRegisterLdd_symbol                       0x296F4C
	#define cellUsbdUnregisterLdd_symbol                     0x296EFC
	#define cellUsbdScanStaticDescriptor_symbol              0x29814C
	#define cellUsbdOpenPipe_symbol                          0x2981FC
	#define cellUsbdClosePipe_symbol                         0x2981AC
	#define cellUsbdControlTransfer_symbol                   0x2980B0
	#define cellUsbdBulkTransfer_symbol                      0x298030

	#define decrypt_func_symbol                              0x37F74
	#define lv1_call_99_wrapper_symbol                       0x53670
	#define modules_verification_symbol                      0x5D1F0
	#define authenticate_program_segment_symbol              0x5E62C

	#define prx_load_module_symbol                           0x8C8E0
	#define prx_start_module_symbol                          0x8B5AC
	#define prx_stop_module_symbol                           0x8C984
	#define prx_unload_module_symbol                         0x8B2E0
	#define prx_get_module_info_symbol                       0x8ACD8
	#define prx_get_module_id_by_address_symbol              0x8ABE8
	#define prx_get_module_id_by_name_symbol                 0x8AC38
	#define prx_get_module_list_symbol                       0x8AD58
	#define load_module_by_fd_symbol                         0x8BF10
	#define parse_sprx_symbol                                0x89C04
	#define open_prx_object_symbol                           0x82CDC
	#define close_prx_object_symbol                          0x835EC
	#define lock_prx_mutex_symbol                            0x8AB90
	#define unlock_prx_mutex_symbol                          0x8AB9C

	#define extend_kstack_symbol                             0x7330C

	#define get_pseudo_random_number_symbol                  0x25F5E4
	#define md5_reset_symbol                                 0x16A034
	#define md5_update_symbol                                0x16AAD4
	#define md5_final_symbol                                 0x16AC54
	#define ss_get_open_psid_symbol                          0x2619AC
	#define update_mgr_read_eeprom_symbol                    0x25B1D8
	#define update_mgr_write_eeprom_symbol                   0x25B10C
	#define update_mgr_if_get_token_symbol                   0x25CB54

	#define ss_params_get_update_status_symbol               0x5527C

	#define sm_get_temperature_symbol                        0x29A278
	#define sm_get_fan_policy_symbol                         0x29960C
	#define sm_set_fan_policy_symbol                         0x29B5D4
	#define sm_get_temperature_patch                         0xC714
	#define sm_get_fan_policy_patch                          0x9EA8
	#define sm_set_fan_policy_patch                          0xA3A4

	#define SHA1_init_symbol                                 0x2E368C
	#define SHA1_update_symbol                               0x2E36EC
	#define SHA1_final_symbol                                0x2E38A0
	#define aescbccfb_dec_symbol                             0x2E1B80
	#define aescbccfb_enc_symbol                             0x2E1930
	#define get_path_by_fd_symbol                            0x1B7A50

	#define ECDSA_1                                          0x5DBE8
	#define ECDSA_2                                          0x2E6AAC
	#define ECDSA_FLAG                                       0x496EC8
	#define sysmem_obj                                       0x497080
	#define qa_eeprom_offset                                 0x4C252

	#define syscall_table_symbol                             0x37C068
	#define syscall_call_offset                              0x2AD4B8

	#define read_bdvd0_symbol                                0x1C3114
	#define read_bdvd1_symbol                                0x1C4D40
	#define read_bdvd2_symbol                                0x1D1EF8

	#define storage_internal_get_device_object_symbol        0x2B8DE8

	#define hid_mgr_read_usb_symbol                          0x10A214
	#define hid_mgr_read_bt_symbol                           0x1040EC

	#define bt_set_controller_info_internal_symbol           0xF8164

	#define device_event_port_send_call                      0x2C5C10
	#define device_event_port_send_call_restore              0x98DAD44B

	#define ss_pid_call_1                                    0x24A9E8

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x82BD0
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x8C77C

	#define shutdown_copy_params_call                        0xAB3C
	#define shutdown_copy_params_call_restore                0x81550048

	#define fsloop_open_call                                 0x2DB2AC
	#define fsloop_close_call                                0x2DB2FC
	#define fsloop_read_call                                 0x2DB33C

	#define shutdown_patch_offset                            0xAB28
	#define module_sdk_version_patch_offset                  0x29E060
	#define module_add_parameter_to_parse_sprxpatch_offset   0x8BFEC

	#define user_thread_prio_patch                           0x21BA8
	#define user_thread_prio_patch2                          0x21BB8

	#define lic_patch                                        0x5A754
	#define lic_patch_restore                                0x482801DD
	#define ode_patch                                        0x25EBEC
	#define fix_80010009                                     0x5E4C0
	#define fix_8001003D                                     0x5AA88
	#define fix_8001003E                                     0x5AB4C
	#define PATCH_JUMP                                       0x5AB00

	#define io_rtoc_entry_1                                 -0x48
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65A0

	#define storage_rtoc_entry_1                             0x2318

	#define device_event_rtoc_entry_1                        0x26A0

	#define time_rtoc_entry_1                               -0x75E0
	#define time_rtoc_entry_2                               -0x75E8

	#define thread_rtoc_entry_1                             -0x7660

	#define process_rtoc_entry_1                            -0x77A0

	#define bt_rtoc_entry_1                                 -0x34D8

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x26AAC
	#define permissions_exception2                           0xC9B04
	#define permissions_exception3                           0x21C7C

	#define patch_data1_offset                               0x3F9940
	#define patch_func2                                      0x5DBA8
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDA3A1
	#define patch_func8_offset1                              0x5A9B0
	#define patch_func8_offset2                              0x5AB10
	#define patch_func8_offset2_restore                      0x4824B0F1
	#define patch_func9_offset                               0x5E4D4
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x394930

	#define mmapper_flags_temp_patch                         0x74320

	#define rsx_syscall_check                                0x7E3C
	#define unk_func2_unregister_service                     0x9DEC0
	#define unk_func3_unregister_service                     0xA2954

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E2000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52D00000057000
	#define PS1_EMU_HASH                                     0xCC28B000000A1000
	#define PS1_NETEMU_HASH                                  0xCC28D000000C4000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001D000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000026000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC28B00000339000
	#define BDP_BDVD_HASH                                    0xCC284000003FD000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC2680000001D000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000034000
	#define PREMO_PLUGIN_HASH                                0x3E80800000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x27B600000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000BF000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0xC02C70000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x1528

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xB19CC

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xCA2B8
	#define ps2tonet_size_patch                              0xCA2AC
	#define vmode_patch_offset                               0x447CB0
	#define psp_drm_patch1                                   0x244A94
	#define psp_drm_patch2                                   0x245534
	#define psp_drm_patch3                                   0x245170
	#define psp_drm_patch4                                   0x24597C
	#define psp_drm_patchA                                   0x244BB0
	#define psp_drm_patchB                                   0x245450
	#define psp_drm_patchC                                   0x2445E8
	#define psp_drm_patchD                                   0x244B98
	#define psp_drm_patchE                                   0x244B9C
	#define psp_drm_patchF                                   0x245568
	#define psp_extra_drm_patch                              0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDE1F4
	#define app_home_offset                                  0x2511B0

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x6989C

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23868
	#define ps_region_error_offset                           0x6958
	#define remote_play_offset                               0x609C
	#define ps2_nonbw_offset3                                0x16AC8

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB8D8

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xCAA4

	/* nas_plugin */
	#define patch1_nas                                       0x2EAF8
	#define patch2_nas                                       0x2EC5C
	#define patch3_nas                                       0x1F784

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x20160
	#define pspemu_path_offset                               0x4C398
	#define psptrans_path_offset                             0x4C450

	/* download_plugin */
	#define elf_patch1_download                              0x3B04C
	#define elf_patch2_download                              0x3B054
	#define elf_patch3_download                              0x451B8
	#define elf_patch4_download                              0x45F38
	#define elf_patch5_download                              0x45F58
	#define elf_patch6_download                              0x45FA0

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x716AC
	#define elf_patch2_autodownload                          0x716B4

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x159C4C
	#define bdp_cinavia1_patch                               0x159C78

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C10

	/* emulator_api */
	#define psp_read                                         0xFB24
	#define psp_read_header                                  0x10AA8
	#define psp_drm_patch5                                   0x108CC
	#define psp_drm_patch6                                   0x108FC
	#define psp_drm_patch7                                   0x10914
	#define psp_drm_patch8                                   0x10918
	#define psp_drm_patch9                                   0x10A58
	#define psp_drm_patch11                                  0x10A5C
	#define psp_drm_patch12                                  0x10A6C
	#define psp_product_id_patch1                            0x10B6C
	#define psp_product_id_patch3                            0x10E44

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E340
	#define psp_prx_patch                                    0x5745C
	#define psp_savedata_bind_patch1                         0x79810
	#define psp_savedata_bind_patch2                         0x79868
	#define psp_savedata_bind_patch3                         0x79384
	#define psp_extra_savedata_patch                         0x85194
	#define psp_prometheus_patch                             0x12E870
	#define prx_patch_call_lr                                0x585B0

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46D4
	#define psp_savedata_patch2                              0x46AC
	#define psp_savedata_patch3                              0x450C
	#define psp_savedata_patch4                              0x4544
	#define psp_savedata_patch5                              0x4558
	#define psp_savedata_patch6                              0x46C0

	/* libfs */
	#define aio_copy_root_offset                             0xD5B4

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* CEX */
	#define cex_ps2tonet_patch                               0xC4D64
	#define cex_ps2tonet_size_patch                          0xC4D58
	#define cex_vmode_patch_offset                           0x4400CC
	#define cex_psp_drm_patch1                               0x23D27C
	#define cex_psp_drm_patch2                               0x23DD1C
	#define cex_psp_drm_patch3                               0x23D958
	#define cex_psp_drm_patch4                               0x23E164
	#define cex_psp_drm_patchA                               0x23D398
	#define cex_psp_drm_patchB                               0x23DC38
	#define cex_psp_drm_patchC                               0x23CDD0
	#define cex_psp_drm_patchD                               0x23D380
	#define cex_psp_drm_patchE                               0x23D384
	#define cex_psp_drm_patchF                               0x23DD50
	#define cex_psp_extra_drm_patch                          0x0
#endif

#ifdef FIRMWARE_431C

	#define FIRMWARE_VERSION                                 0x431

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003DB1B0ULL
		#define PS3MAPI_IDPS_2                               0x8000000000476F3CULL
		#define PS3MAPI_PSID                                 0x8000000000476F54ULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x348210

	#define create_kernel_object_symbol                      0x11F9C
	#define destroy_kernel_object_symbol                     0x11900
	#define destroy_shared_kernel_object_symbol              0x11274
	#define open_kernel_object_symbol                        0x125EC
	#define open_shared_kernel_object_symbol                 0x123FC
	#define close_kernel_object_handle_symbol                0x11A1C

	#define alloc_symbol                                     0x6402C
	#define dealloc_symbol                                   0x64468
	#define copy_to_user_symbol                              0xF85C
	#define copy_from_user_symbol                            0xFA78
	#define copy_to_process_symbol                           0xF914
	#define copy_from_process_symbol                         0xF724
	#define process_read_memory_symbol                       0x298754
	#define process_write_memory_symbol                      0x2985C8
	#define page_allocate_symbol                             0x5FB9C
	#define page_free_symbol                                 0x5F600
	#define page_export_to_proc_symbol                       0x5FD38
	#define page_unexport_from_proc_symbol                   0x5F4F4
	#define kernel_ea_to_lpar_addr_symbol                    0x6F920
	#define process_ea_to_lpar_addr_ex_symbol                0x76F34
	#define set_pte_symbol                                   0x5DB98
	#define map_process_memory_symbol                        0x76A40
	#define panic_symbol                                     0x29DDFC

	#define memcpy_symbol                                    0x7E100
	#define memset_symbol                                    0x4E548
	#define memcmp_symbol                                    0x4D858
	#define memchr_symbol                                    0x4D808
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
	#define strrchr_symbol                                   0x4E82C

	#define spin_lock_irqsave_ex_symbol                      0x29DFCC
	#define spin_unlock_irqrestore_ex_symbol                 0x29DFA0

	#define create_process_common_symbol                     0x29BDC8
	#define create_process_base_symbol                       0x29B484
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x29BBD4

	#define ppu_thread_create_symbol                         0x13EB4
	#define ppu_thread_exit_symbol                           0x13F6C
	#define ppu_thread_join_symbol                           0x13FC0
	#define ppu_thread_delay_symbol                          0x28554
	#define create_kernel_thread_symbol                      0x248D8
	#define create_user_thread_symbol                        0x25014
	#define create_user_thread2_symbol                       0x24E38
	#define start_thread_symbol                              0x23B04
	#define run_thread_symbol                                0x23334
	#define self_threading_symbol                            0x25620
	#define register_thread_symbol                           0x2981E0
	#define allocate_user_stack_symbol                       0x2989C8
	#define deallocate_user_stack_symbol                     0x298930

	#define mutex_create_symbol                              0x13628
	#define mutex_destroy_symbol                             0x135C0
	#define mutex_lock_symbol                                0x135B8
	#define mutex_lock_ex_symbol                             0x1D914
	#define mutex_trylock_symbol                             0x135B4
	#define mutex_unlock_symbol                              0x135B0

	#define cond_create_symbol                               0x13794
	#define cond_destroy_symbol                              0x13744
	#define cond_wait_symbol                                 0x1373C
	#define cond_wait_ex_symbol                              0x1EF00
	#define cond_signal_symbol                               0x13718
	#define cond_signal_all_symbol                           0x136F4

	#define semaphore_initialize_symbol                      0x30A04
	#define semaphore_wait_ex_symbol                         0x3070C
	#define semaphore_trywait_symbol                         0x302F4
	#define semaphore_post_ex_symbol                         0x30440

	#define event_port_create_symbol                         0x13064
	#define event_port_destroy_symbol                        0x134CC
	#define event_port_connect_symbol                        0x13544
	#define event_port_disconnect_symbol                     0x13470
	#define event_port_send_symbol                           0x1305C
	#define event_port_send_ex_symbol                        0x2AFB4

	#define event_queue_create_symbol                        0x1336C
	#define event_queue_destroy_symbol                       0x132F4
	#define event_queue_receive_symbol                       0x13138
	#define event_queue_tryreceive_symbol                    0x13204

	#define cellFsOpen_symbol                                0x2C3FA8
	#define cellFsClose_symbol                               0x2C3E10
	#define cellFsRead_symbol                                0x2C3F4C
	#define cellFsWrite_symbol                               0x2C3EB8
	#define cellFsLseek_symbol                               0x2C3540
	#define cellFsStat_symbol                                0x2C37C4
	#define cellFsUtime_symbol                               0x2C51E0
	#define cellFsUnlink_internal_symbol                     0x1AA18C
	#define cellFsRename_internal_symbol                     0x1A6D5C

	#define cellFsUtilMount_symbol                           0x2C3320
	#define cellFsUtilUmount_symbol                          0x2C32F4
	#define cellFsUtilNewfs_symbol                           0x2C4C78

	#define pathdup_from_user_symbol                         0x1B1DCC
	#define open_path_symbol                                 0x2C3CE0
	#define open_fs_object_symbol                            0x1913F0
	#define close_fs_object_symbol                           0x1903C0

	#define storage_get_device_info_symbol                   0x2A9338
	#define storage_get_device_config_symbol                 0x2A9008
	#define storage_open_symbol                              0x2A885C
	#define storage_close_symbol                             0x2A8DF8
	#define storage_read_symbol                              0x2A7D74
	#define storage_write_symbol                             0x2A7C44
	#define storage_send_device_command_symbol               0x2A7EB0
	#define storage_map_io_memory_symbol                     0x2A91F4
	#define storage_unmap_io_memory_symbol                   0x2A90C0
	#define new_medium_listener_object_symbol                0x96B44
	#define delete_medium_listener_object_symbol             0x9837C
	#define set_medium_event_callbacks_symbol                0x986E0

	#define cellUsbdRegisterLdd_symbol                       0x290B38
	#define cellUsbdUnregisterLdd_symbol                     0x290AE8
	#define cellUsbdScanStaticDescriptor_symbol              0x291D38
	#define cellUsbdOpenPipe_symbol                          0x291DE8
	#define cellUsbdClosePipe_symbol                         0x291D98
	#define cellUsbdControlTransfer_symbol                   0x291C9C
	#define cellUsbdBulkTransfer_symbol                      0x291C1C

	#define decrypt_func_symbol                              0x34710
	#define lv1_call_99_wrapper_symbol                       0x4FD84
	#define modules_verification_symbol                      0x598DC
	#define authenticate_program_segment_symbol              0x5AD18

	#define prx_load_module_symbol                           0x88298
	#define prx_start_module_symbol                          0x86F64
	#define prx_stop_module_symbol                           0x8833C
	#define prx_unload_module_symbol                         0x86C98
	#define prx_get_module_info_symbol                       0x86720
	#define prx_get_module_id_by_address_symbol              0x86630
	#define prx_get_module_id_by_name_symbol                 0x86680
	#define prx_get_module_list_symbol                       0x867A0
	#define load_module_by_fd_symbol                         0x878C8
	#define parse_sprx_symbol                                0x8564C
	#define open_prx_object_symbol                           0x7ECBC
	#define close_prx_object_symbol                          0x7F5CC
	#define lock_prx_mutex_symbol                            0x865D8
	#define unlock_prx_mutex_symbol                          0x865E4

	#define extend_kstack_symbol                             0x6F878

	#define get_pseudo_random_number_symbol                  0x2591D0
	#define md5_reset_symbol                                 0x163D68
	#define md5_update_symbol                                0x164808
	#define md5_final_symbol                                 0x164988
	#define ss_get_open_psid_symbol                          0x25B598
	#define update_mgr_read_eeprom_symbol                    0x254DDC
	#define update_mgr_write_eeprom_symbol                   0x254D24
	#define update_mgr_if_get_token_symbol                   0x256740

	#define ss_params_get_update_status_symbol               0x51990

	#define sm_get_temperature_symbol                        0x293E64
	#define sm_get_fan_policy_symbol                         0x2931F8
	#define sm_set_fan_policy_symbol                         0x294FF0
	#define sm_get_temperature_patch                         0xC698
	#define sm_get_fan_policy_patch                          0x9E28
	#define sm_set_fan_policy_patch                          0xA324

	#define SHA1_init_symbol                                 0x2C8F68
	#define SHA1_update_symbol                               0x2C8FC8
	#define SHA1_final_symbol                                0x2C917C
	#define aescbccfb_dec_symbol                             0x2C745C
	#define aescbccfb_enc_symbol                             0x2C720C
	#define get_path_by_fd_symbol                            0x1B1668

	#define ECDSA_1                                          0x5A2D4
	#define ECDSA_2                                          0x2CC388
	#define ECDSA_FLAG                                       0x476EC8
	#define sysmem_obj                                       0x477080
	#define qa_eeprom_offset                                 0x489AA

	#define syscall_table_symbol                             0x35DBE0
	#define syscall_call_offset                              0x2A544C

	#define read_bdvd0_symbol                                0x1BCD2C
	#define read_bdvd1_symbol                                0x1BE958
	#define read_bdvd2_symbol                                0x1CBB10

	#define storage_internal_get_device_object_symbol        0x2A76FC

	#define hid_mgr_read_usb_symbol                          0x1047D0
	#define hid_mgr_read_bt_symbol                           0xFE6A8

	#define bt_set_controller_info_internal_symbol           0xF2720

	#define device_event_port_send_call                      0x2B16B4
	#define device_event_port_send_call_restore              0xA819D64B

	#define ss_pid_call_1                                    0x244600

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7EBB0
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x88134

	#define shutdown_copy_params_call                        0xAABC
	#define shutdown_copy_params_call_restore                0xBD4F0048

	#define fsloop_open_call                                 0x2C4140
	#define fsloop_close_call                                0x2C4190
	#define fsloop_read_call                                 0x2C41D0

	#define shutdown_patch_offset                            0xAAA8
	#define module_sdk_version_patch_offset                  0x297A10
	#define module_add_parameter_to_parse_sprxpatch_offset   0x879A4

	#define user_thread_prio_patch                           0x201B4
	#define user_thread_prio_patch2                          0x201C4

	#define lic_patch                                        0x56E40
	#define lic_patch_restore                                0x4826C985
	#define ode_patch                                        0x2587D8
	#define fix_80010009                                     0x5ABAC
	#define fix_8001003D                                     0x57174
	#define fix_8001003E                                     0x57238
	#define PATCH_JUMP                                       0x571EC

	#define io_rtoc_entry_1                                 -0x178
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x6680

	#define storage_rtoc_entry_1                             0x1E40

	#define device_event_rtoc_entry_1                        0x20B0

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x3600

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x24EB8
	#define permissions_exception2                           0xC4454
	#define permissions_exception3                           0x20288

	#define patch_data1_offset                               0x3DB1C0
	#define patch_func2                                      0x5A294
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDA451
	#define patch_func8_offset1                              0x5709C
	#define patch_func8_offset2                              0x571FC
	#define patch_func8_offset2_restore                      0x48246C01
	#define patch_func9_offset                               0x0
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x3761B0

	#define mmapper_flags_temp_patch                         0x7074C

	#define rsx_syscall_check                                0x7E3C
	#define unk_func2_unregister_service                     0x98810
	#define unk_func3_unregister_service                     0x9D2A4

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002DF000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EB000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52E00000056000
	#define PS1_EMU_HASH                                     0xCC28B000000A1000
	#define PS1_NETEMU_HASH                                  0xCC28D000000C4000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001D000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000026000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC28B00000339000
	#define BDP_BDVD_HASH                                    0xCC284000003FD000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC2680000001D000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000034000
	#define PREMO_PLUGIN_HASH                                0x3E80800000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x27B600000001F000
	#define PSP_EMULATOR_HASH                                0xCC29A00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000BF000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0xC02C70000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x1528

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xB19CC

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4D64
	#define ps2tonet_size_patch                              0xC4D58
	#define vmode_patch_offset                               0x4400D0
	#define psp_drm_patch1                                   0x23D280
	#define psp_drm_patch2                                   0x23DD20
	#define psp_drm_patch3                                   0x23D95C
	#define psp_drm_patch4                                   0x23E168
	#define psp_drm_patchA                                   0x23D39C
	#define psp_drm_patchB                                   0x23DC3C
	#define psp_drm_patchC                                   0x23CDD4
	#define psp_drm_patchD                                   0x23D384
	#define psp_drm_patchE                                   0x23D388
	#define psp_drm_patchF                                   0x23DD54
	#define psp_extra_drm_patch                              0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDDDC8
	#define app_home_offset                                  0x250560

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x69B68

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x2364C
	#define ps_region_error_offset                           0x699C
	#define remote_play_offset                               0x609C
	#define ps2_nonbw_offset3                                0x167D8

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB8D8

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xCAA4

	/* nas_plugin */
	#define patch1_nas                                       0x2E6E0
	#define patch2_nas                                       0x2E844
	#define patch3_nas                                       0x1F4CC

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F678
	#define pspemu_path_offset                               0x4B148
	#define psptrans_path_offset                             0x4B1D8

	/* download_plugin */
	#define elf_patch1_download                              0x3B0B8
	#define elf_patch2_download                              0x3B0C0
	#define elf_patch3_download                              0x452B0
	#define elf_patch4_download                              0x46030
	#define elf_patch5_download                              0x46050
	#define elf_patch6_download                              0x46098

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x717FC
	#define elf_patch2_autodownload                          0x71804

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x159C4C
	#define bdp_cinavia1_patch                               0x159C78

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1BE0

	/* emulator_api */
	#define psp_read                                         0xFB24
	#define psp_read_header                                  0x10AA8
	#define psp_drm_patch5                                   0x108CC
	#define psp_drm_patch6                                   0x108FC
	#define psp_drm_patch7                                   0x10914
	#define psp_drm_patch8                                   0x10918
	#define psp_drm_patch9                                   0x10A58
	#define psp_drm_patch11                                  0x10A5C
	#define psp_drm_patch12                                  0x10A6C
	#define psp_product_id_patch1                            0x10B6C
	#define psp_product_id_patch3                            0x10E44

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E340
	#define psp_prx_patch                                    0x5745C
	#define psp_savedata_bind_patch1                         0x79810
	#define psp_savedata_bind_patch2                         0x79868
	#define psp_savedata_bind_patch3                         0x79384
	#define psp_extra_savedata_patch                         0x85194
	#define psp_prometheus_patch                             0x12E870
	#define prx_patch_call_lr                                0x585B0

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46D4
	#define psp_savedata_patch2                              0x46AC
	#define psp_savedata_patch3                              0x450C
	#define psp_savedata_patch4                              0x4544
	#define psp_savedata_patch5                              0x4558
	#define psp_savedata_patch6                              0x46C0

	/* libfs */
	#define aio_copy_root_offset                             0xD5B4

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                        0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH                 0xDE52D00000057000
	#define GAME_EXT_PLUGIN_REBUG_HASH                       0xCC2680000001D000
	#define dex_ps2_nonbw_offset                             0xDE1F4
	#define dex_ps2_nonbw_offset2                            0x6989C
	#define dex_ps2_nonbw_offset3                            0x16AC8
	#define dex_ps2tonet_patch                               0xCA2B8
	#define dex_ps2tonet_size_patch                          0xCA2AC
	#define dex_vmode_patch_offset                           0x447CB4
	#define dex_psp_drm_patch1                               0x244A98
	#define dex_psp_drm_patch2                               0x245538
	#define dex_psp_drm_patch3                               0x245174
	#define dex_psp_drm_patch4                               0x245980
	#define dex_psp_drm_patchA                               0x244BB4
	#define dex_psp_drm_patchB                               0x245454
	#define dex_psp_drm_patchC                               0x2445EC
	#define dex_psp_drm_patchD                               0x244B9C
	#define dex_psp_drm_patchE                               0x244BA0
	#define dex_psp_drm_patchF                               0x24556C
	#define dex_psp_extra_drm_patch                          0x0
#endif

#ifdef FIRMWARE_440C

	#define FIRMWARE_VERSION                                 0x440

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003DB830ULL
		#define PS3MAPI_IDPS_2                               0x8000000000476F3CULL
		#define PS3MAPI_PSID                                 0x8000000000476F54ULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x3487D0

	#define create_kernel_object_symbol                      0x12010
	#define destroy_kernel_object_symbol                     0x11974
	#define destroy_shared_kernel_object_symbol              0x112E8
	#define open_kernel_object_symbol                        0x12660
	#define open_shared_kernel_object_symbol                 0x12470
	#define close_kernel_object_handle_symbol                0x11A90

	#define alloc_symbol                                     0x62F74
	#define dealloc_symbol                                   0x633B0
	#define copy_to_user_symbol                              0xF858
	#define copy_from_user_symbol                            0xFA74
	#define copy_to_process_symbol                           0xF910
	#define copy_from_process_symbol                         0xF720
	#define process_read_memory_symbol                       0x297B58
	#define process_write_memory_symbol                      0x2979CC
	#define page_allocate_symbol                             0x5EAE4
	#define page_free_symbol                                 0x5E548
	#define page_export_to_proc_symbol                       0x5EC80
	#define page_unexport_from_proc_symbol                   0x5E43C
	#define kernel_ea_to_lpar_addr_symbol                    0x6E868
	#define process_ea_to_lpar_addr_ex_symbol                0x75E7C
	#define set_pte_symbol                                   0x5CAE0
	#define map_process_memory_symbol                        0x75988
	#define panic_symbol                                     0x29D204

	#define memcpy_symbol                                    0x7D048
	#define memset_symbol                                    0x4D490
	#define memcmp_symbol                                    0x4C7A0
	#define memchr_symbol                                    0x4C750
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
	#define strrchr_symbol                                   0x4D774

	#define spin_lock_irqsave_ex_symbol                      0x29D3D4
	#define spin_unlock_irqrestore_ex_symbol                 0x29D3A8

	#define create_process_common_symbol                     0x29B1CC
	#define create_process_base_symbol                       0x29A888
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x29AFD8

	#define ppu_thread_create_symbol                         0x13F28
	#define ppu_thread_exit_symbol                           0x13FE0
	#define ppu_thread_join_symbol                           0x14034
	#define ppu_thread_delay_symbol                          0x285C8
	#define create_kernel_thread_symbol                      0x2494C
	#define create_user_thread_symbol                        0x25088
	#define create_user_thread2_symbol                       0x24EAC
	#define start_thread_symbol                              0x23B78
	#define run_thread_symbol                                0x233A8
	#define self_threading_symbol                            0x25694
	#define register_thread_symbol                           0x2975E4
	#define allocate_user_stack_symbol                       0x297DCC
	#define deallocate_user_stack_symbol                     0x297D34

	#define mutex_create_symbol                              0x1369C
	#define mutex_destroy_symbol                             0x13634
	#define mutex_lock_symbol                                0x1362C
	#define mutex_lock_ex_symbol                             0x1D988
	#define mutex_trylock_symbol                             0x13628
	#define mutex_unlock_symbol                              0x13624

	#define cond_create_symbol                               0x13808
	#define cond_destroy_symbol                              0x137B8
	#define cond_wait_symbol                                 0x137B0
	#define cond_wait_ex_symbol                              0x1EF74
	#define cond_signal_symbol                               0x1378C
	#define cond_signal_all_symbol                           0x13768

	#define semaphore_initialize_symbol                      0x30A78
	#define semaphore_wait_ex_symbol                         0x30780
	#define semaphore_trywait_symbol                         0x30368
	#define semaphore_post_ex_symbol                         0x304B4

	#define event_port_create_symbol                         0x130D8
	#define event_port_destroy_symbol                        0x13540
	#define event_port_connect_symbol                        0x135B8
	#define event_port_disconnect_symbol                     0x134E4
	#define event_port_send_symbol                           0x130D0
	#define event_port_send_ex_symbol                        0x2B028

	#define event_queue_create_symbol                        0x133E0
	#define event_queue_destroy_symbol                       0x13368
	#define event_queue_receive_symbol                       0x131AC
	#define event_queue_tryreceive_symbol                    0x13278

	#define cellFsOpen_symbol                                0x2C454C
	#define cellFsClose_symbol                               0x2C43B4
	#define cellFsRead_symbol                                0x2C44F0
	#define cellFsWrite_symbol                               0x2C445C
	#define cellFsLseek_symbol                               0x2C3AE4
	#define cellFsStat_symbol                                0x2C3D68
	#define cellFsUtime_symbol                               0x2C5784
	#define cellFsUnlink_internal_symbol                     0x1AAD08
	#define cellFsRename_internal_symbol                     0x1A5D14

	#define cellFsUtilMount_symbol                           0x2C38C4
	#define cellFsUtilUmount_symbol                          0x2C3898
	#define cellFsUtilNewfs_symbol                           0x2C521C

	#define pathdup_from_user_symbol                         0x1B0D98
	#define open_path_symbol                                 0x2EA518
	#define open_fs_object_symbol                            0x1903A0
	#define close_fs_object_symbol                           0x18F370

	#define storage_get_device_info_symbol                   0x2A9724
	#define storage_get_device_config_symbol                 0x2A8BB4
	#define storage_open_symbol                              0x2A9134
	#define storage_close_symbol                             0x2A8F24
	#define storage_read_symbol                              0x2A8494
	#define storage_write_symbol                             0x2A8364
	#define storage_send_device_command_symbol               0x2A8020
	#define storage_map_io_memory_symbol                     0x2A95E0
	#define storage_unmap_io_memory_symbol                   0x2A94AC
	#define new_medium_listener_object_symbol                0x95AEC
	#define delete_medium_listener_object_symbol             0x97324
	#define set_medium_event_callbacks_symbol                0x97688

	#define cellUsbdRegisterLdd_symbol                       0x28FF1C
	#define cellUsbdUnregisterLdd_symbol                     0x28FECC
	#define cellUsbdScanStaticDescriptor_symbol              0x29111C
	#define cellUsbdOpenPipe_symbol                          0x2911CC
	#define cellUsbdClosePipe_symbol                         0x29117C
	#define cellUsbdControlTransfer_symbol                   0x291080
	#define cellUsbdBulkTransfer_symbol                      0x291000

	#define decrypt_func_symbol                              0x34794
	#define lv1_call_99_wrapper_symbol                       0x4ECCC
	#define modules_verification_symbol                      0x58824
	#define authenticate_program_segment_symbol              0x59C60

	#define prx_load_module_symbol                           0x87230
	#define prx_start_module_symbol                          0x85EFC
	#define prx_stop_module_symbol                           0x872D4
	#define prx_unload_module_symbol                         0x85C30
	#define prx_get_module_info_symbol                       0x856B8
	#define prx_get_module_id_by_address_symbol              0x855C8
	#define prx_get_module_id_by_name_symbol                 0x85618
	#define prx_get_module_list_symbol                       0x85738
	#define load_module_by_fd_symbol                         0x86860
	#define parse_sprx_symbol                                0x845E4
	#define open_prx_object_symbol                           0x7DC04
	#define close_prx_object_symbol                          0x7E514
	#define lock_prx_mutex_symbol                            0x85570
	#define unlock_prx_mutex_symbol                          0x8557C

	#define extend_kstack_symbol                             0x6E7C0

	#define get_pseudo_random_number_symbol                  0x258278
	#define md5_reset_symbol                                 0x162D2C
	#define md5_update_symbol                                0x1637CC
	#define md5_final_symbol                                 0x16394C
	#define ss_get_open_psid_symbol                          0x25A640
	#define update_mgr_read_eeprom_symbol                    0x253D84
	#define update_mgr_write_eeprom_symbol                   0x253CCC
	#define update_mgr_if_get_token_symbol                   0x2556E8

	#define ss_params_get_update_status_symbol               0x508D8

	#define sm_get_temperature_symbol                        0x293248
	#define sm_get_fan_policy_symbol                         0x2925DC
	#define sm_set_fan_policy_symbol                         0x2943D4
	#define sm_get_temperature_patch                         0xC694
	#define sm_get_fan_policy_patch                          0x9E28
	#define sm_set_fan_policy_patch                          0xA324

	#define SHA1_init_symbol                                 0x2C950C
	#define SHA1_update_symbol                               0x2C956C
	#define SHA1_final_symbol                                0x2C9720
	#define aescbccfb_dec_symbol                             0x2C7A00
	#define aescbccfb_enc_symbol                             0x2C77B0
	#define get_path_by_fd_symbol                            0x1B0634

	#define ECDSA_1                                          0x5921C
	#define ECDSA_2                                          0x2CC92C
	#define ECDSA_FLAG                                       0x476EC8
	#define sysmem_obj                                       0x477080
	#define qa_eeprom_offset                                 0x48A2E

	#define syscall_table_symbol                             0x35E260
	#define syscall_call_offset                              0x2A5828

	#define read_bdvd0_symbol                                0x1BBD08
	#define read_bdvd1_symbol                                0x1BD934
	#define read_bdvd2_symbol                                0x1CAAEC

	#define storage_internal_get_device_object_symbol        0x2A7AD8

	#define hid_mgr_read_usb_symbol                          0x1037A8
	#define hid_mgr_read_bt_symbol                           0xFD680

	#define bt_set_controller_info_internal_symbol           0xF16F8

	#define device_event_port_send_call                      0x2B1C58
	#define device_event_port_send_call_restore              0x7814D64B

	#define ss_pid_call_1                                    0x2435A8

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7DAF8
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x870CC

	#define shutdown_copy_params_call                        0xAABC
	#define shutdown_copy_params_call_restore                0xB94F0048

	#define fsloop_open_call                                 0x2C46E4
	#define fsloop_close_call                                0x2C4734
	#define fsloop_read_call                                 0x2C4774

	#define shutdown_patch_offset                            0xAAA8
	#define module_sdk_version_patch_offset                  0x296E14
	#define module_add_parameter_to_parse_sprxpatch_offset   0x8693C

	#define user_thread_prio_patch                           0x20228
	#define user_thread_prio_patch2                          0x20238

	#define lic_patch                                        0x55D88
	#define lic_patch_restore                                0x4826DFE1
	#define ode_patch                                        0x257880
	#define fix_80010009                                     0x59AF4
	#define fix_8001003D                                     0x560BC
	#define fix_8001003E                                     0x56180
	#define PATCH_JUMP                                       0x56134

	#define io_rtoc_entry_1                                 -0x150
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x6688

	#define storage_rtoc_entry_1                             0x1E98

	#define device_event_rtoc_entry_1                        0x2108

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x35D8

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x24F2C
	#define permissions_exception2                           0xC354C
	#define permissions_exception3                           0x202FC

	#define patch_data1_offset                               0x3DB840
	#define patch_func2                                      0x591DC
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDB58D
	#define patch_func8_offset1                              0x55FE4
	#define patch_func8_offset2                              0x56144
	#define patch_func8_offset2_restore                      0x482470C1
	#define patch_func9_offset                               0x59B08
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x376830

	#define mmapper_flags_temp_patch                         0x6F694

	#define rsx_syscall_check                                0x7E3C
	#define unk_func2_unregister_service                     0x977B8
	#define unk_func3_unregister_service                     0x9C24C

	/* lv1 */
	#define vsh_pos_in_ram                                   0x510000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E0000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52E00000056000
	#define PS1_EMU_HASH                                     0xCC28B000000A1000
	#define PS1_NETEMU_HASH                                  0xCC28D000000C4000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001D000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000026000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC28B00000339000
	#define BDP_BDVD_HASH                                    0xCC287000003FD000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000020000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000040000
	#define PREMO_PLUGIN_HASH                                0x3E80800000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x27B600000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0xC02C70000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xB19CC

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4D64
	#define ps2tonet_size_patch                              0xC4D58
	#define vmode_patch_offset                               0x44215C
	#define psp_drm_patch1                                   0x23E490
	#define psp_drm_patch2                                   0x23EF30
	#define psp_drm_patch3                                   0x23EB6C
	#define psp_drm_patch4                                   0x23F378
	#define psp_drm_patchA                                   0x23E5AC
	#define psp_drm_patchB                                   0x23EE4C
	#define psp_drm_patchC                                   0x23DFE4
	#define psp_drm_patchD                                   0x23E594
	#define psp_drm_patchE                                   0x23E598
	#define psp_drm_patchF                                   0x23EF64
	#define psp_extra_drm_patch                              0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDE5F0
	#define app_home_offset                                  0x252360

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x69B6C

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x2366C
	#define ps_region_error_offset                           0x699C
	#define remote_play_offset                               0x609C
	#define ps2_nonbw_offset3                                0x167F8

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB8D8

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xCAA4

	/* nas_plugin */
	#define patch1_nas                                       0x2E84C
	#define patch2_nas                                       0x2E9B0
	#define patch3_nas                                       0x1F59C

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F678
	#define pspemu_path_offset                               0x4B148
	#define psptrans_path_offset                             0x4B1D8

	/* download_plugin */
	#define elf_patch1_download                              0x41154
	#define elf_patch2_download                              0x4115C
	#define elf_patch3_download                              0x4B920
	#define elf_patch4_download                              0x4C678
	#define elf_patch5_download                              0x4C698
	#define elf_patch6_download                              0x4C6E0

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x76450
	#define elf_patch2_autodownload                          0x76458

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x159F28
	#define bdp_cinavia1_patch                               0x159F54

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1BF4

	/* emulator_api */
	#define psp_read                                         0xFC60
	#define psp_read_header                                  0x10BE4
	#define psp_drm_patch5                                   0x10A08
	#define psp_drm_patch6                                   0x10A38
	#define psp_drm_patch7                                   0x10A50
	#define psp_drm_patch8                                   0x10A54
	#define psp_drm_patch9                                   0x10B94
	#define psp_drm_patch11                                  0x10B98
	#define psp_drm_patch12                                  0x10BA8
	#define psp_product_id_patch1                            0x10CA8
	#define psp_product_id_patch3                            0x10F80

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6B0
	#define psp_prx_patch                                    0x577CC
	#define psp_savedata_bind_patch1                         0x7A4B0
	#define psp_savedata_bind_patch2                         0x7A508
	#define psp_savedata_bind_patch3                         0x7A024
	#define psp_extra_savedata_patch                         0x87520
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x58920

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD5B4

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                        0xC50D0000000ED000
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH                 0xDE52D00000057000
	#define GAME_EXT_PLUGIN_REBUG_HASH                       0xCC2680000001D000
	#define dex_ps2_nonbw_offset                             0xDEA18
	#define dex_ps2_nonbw_offset2                            0x698A4
	#define dex_ps2_nonbw_offset3                            0x16AE8
	#define dex_ps2tonet_patch                               0xCA2C0
	#define dex_ps2tonet_size_patch                          0xCA2B4
	#define dex_vmode_patch_offset                           0x449D64
	#define dex_psp_drm_patch1                               0x245CCC
	#define dex_psp_drm_patch2                               0x24676C
	#define dex_psp_drm_patch3                               0x2463A8
	#define dex_psp_drm_patch4                               0x246BB4
	#define dex_psp_drm_patchA                               0x245DE8
	#define dex_psp_drm_patchB                               0x246688
	#define dex_psp_drm_patchC                               0x245820
	#define dex_psp_drm_patchD                               0x245DD0
	#define dex_psp_drm_patchE                               0x245DD4
	#define dex_psp_drm_patchF                               0x2467A0
	#define dex_psp_extra_drm_patch                          0x0
#endif

#ifdef FIRMWARE_441C

	#define FIRMWARE_VERSION                                 0x441

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003DB830ULL
		#define PS3MAPI_IDPS_2                               0x8000000000476F3CULL
		#define PS3MAPI_PSID                                 0x8000000000476F54ULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x3487E0

	#define create_kernel_object_symbol                      0x12014
	#define destroy_kernel_object_symbol                     0x11978
	#define destroy_shared_kernel_object_symbol              0x112EC
	#define open_kernel_object_symbol                        0x12664
	#define open_shared_kernel_object_symbol                 0x12474
	#define close_kernel_object_handle_symbol                0x11A94

	#define alloc_symbol                                     0x62F78
	#define dealloc_symbol                                   0x633B4
	#define copy_to_user_symbol                              0xF85C
	#define copy_from_user_symbol                            0xFA78
	#define copy_to_process_symbol                           0xF914
	#define copy_from_process_symbol                         0xF724
	#define process_read_memory_symbol                       0x297B64
	#define process_write_memory_symbol                      0x2979D8
	#define page_allocate_symbol                             0x5EAE8
	#define page_free_symbol                                 0x5E54C
	#define page_export_to_proc_symbol                       0x5EC84
	#define page_unexport_from_proc_symbol                   0x5E440
	#define kernel_ea_to_lpar_addr_symbol                    0x6E86C
	#define process_ea_to_lpar_addr_ex_symbol                0x75E80
	#define set_pte_symbol                                   0x5CAE4
	#define map_process_memory_symbol                        0x7598C
	#define panic_symbol                                     0x29D210

	#define memcpy_symbol                                    0x7D04C
	#define memset_symbol                                    0x4D494
	#define memcmp_symbol                                    0x4C7A4
	#define memchr_symbol                                    0x4C754
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
	#define strrchr_symbol                                   0x4D778

	#define spin_lock_irqsave_ex_symbol                      0x29D3E0
	#define spin_unlock_irqrestore_ex_symbol                 0x29D3B4

	#define create_process_common_symbol                     0x29B1D8
	#define create_process_base_symbol                       0x29A894
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x29AFE4

	#define ppu_thread_create_symbol                         0x13F2C
	#define ppu_thread_exit_symbol                           0x13FE4
	#define ppu_thread_join_symbol                           0x14038
	#define ppu_thread_delay_symbol                          0x285CC
	#define create_kernel_thread_symbol                      0x24950
	#define create_user_thread_symbol                        0x2508C
	#define create_user_thread2_symbol                       0x24EB0
	#define start_thread_symbol                              0x23B7C
	#define run_thread_symbol                                0x233AC
	#define self_threading_symbol                            0x25698
	#define register_thread_symbol                           0x2975F0
	#define allocate_user_stack_symbol                       0x297DD8
	#define deallocate_user_stack_symbol                     0x297D40

	#define mutex_create_symbol                              0x136A0
	#define mutex_destroy_symbol                             0x13638
	#define mutex_lock_symbol                                0x13630
	#define mutex_lock_ex_symbol                             0x1D98C
	#define mutex_trylock_symbol                             0x1362C
	#define mutex_unlock_symbol                              0x13628

	#define cond_create_symbol                               0x1380C
	#define cond_destroy_symbol                              0x137BC
	#define cond_wait_symbol                                 0x137B4
	#define cond_wait_ex_symbol                              0x1EF78
	#define cond_signal_symbol                               0x13790
	#define cond_signal_all_symbol                           0x1376C

	#define semaphore_initialize_symbol                      0x30A7C
	#define semaphore_wait_ex_symbol                         0x30784
	#define semaphore_trywait_symbol                         0x3036C
	#define semaphore_post_ex_symbol                         0x304B8

	#define event_port_create_symbol                         0x130DC
	#define event_port_destroy_symbol                        0x13544
	#define event_port_connect_symbol                        0x135BC
	#define event_port_disconnect_symbol                     0x134E8
	#define event_port_send_symbol                           0x130D4
	#define event_port_send_ex_symbol                        0x2B02C

	#define event_queue_create_symbol                        0x133E4
	#define event_queue_destroy_symbol                       0x1336C
	#define event_queue_receive_symbol                       0x131B0
	#define event_queue_tryreceive_symbol                    0x1327C

	#define cellFsOpen_symbol                                0x2C4558
	#define cellFsClose_symbol                               0x2C43C0
	#define cellFsRead_symbol                                0x2C44FC
	#define cellFsWrite_symbol                               0x2C4468
	#define cellFsLseek_symbol                               0x2C3AF0
	#define cellFsStat_symbol                                0x2C3D74
	#define cellFsUtime_symbol                               0x2C5790
	#define cellFsUnlink_internal_symbol                     0x1AAD10
	#define cellFsRename_internal_symbol                     0x1A5D1C

	#define cellFsUtilMount_symbol                           0x2C38D0
	#define cellFsUtilUmount_symbol                          0x2C38A4
	#define cellFsUtilNewfs_symbol                           0x2C5228

	#define pathdup_from_user_symbol                         0x1B0DA0
	#define open_path_symbol                                 0x2C4290
	#define open_fs_object_symbol                            0x1903A8
	#define close_fs_object_symbol                           0x18F378

	#define storage_get_device_info_symbol                   0x2A9730
	#define storage_get_device_config_symbol                 0x2A8BC0
	#define storage_open_symbol                              0x2A9140
	#define storage_close_symbol                             0x2A8F30
	#define storage_read_symbol                              0x2A84A0
	#define storage_write_symbol                             0x2A8370
	#define storage_send_device_command_symbol               0x2A802C
	#define storage_map_io_memory_symbol                     0x2A95EC
	#define storage_unmap_io_memory_symbol                   0x2A94B8
	#define new_medium_listener_object_symbol                0x95AF4
	#define delete_medium_listener_object_symbol             0x9732C
	#define set_medium_event_callbacks_symbol                0x97690

	#define cellUsbdRegisterLdd_symbol                       0x28FF24
	#define cellUsbdUnregisterLdd_symbol                     0x28FED4
	#define cellUsbdScanStaticDescriptor_symbol              0x291124
	#define cellUsbdOpenPipe_symbol                          0x2911D4
	#define cellUsbdClosePipe_symbol                         0x291184
	#define cellUsbdControlTransfer_symbol                   0x291088
	#define cellUsbdBulkTransfer_symbol                      0x291008

	#define decrypt_func_symbol                              0x34798
	#define lv1_call_99_wrapper_symbol                       0x4ECD0
	#define modules_verification_symbol                      0x58828
	#define authenticate_program_segment_symbol              0x59C64

	#define prx_load_module_symbol                           0x87234
	#define prx_start_module_symbol                          0x85F00
	#define prx_stop_module_symbol                           0x872D8
	#define prx_unload_module_symbol                         0x85C34
	#define prx_get_module_info_symbol                       0x856BC
	#define prx_get_module_id_by_address_symbol              0x855CC
	#define prx_get_module_id_by_name_symbol                 0x8561C
	#define prx_get_module_list_symbol                       0x8573C
	#define load_module_by_fd_symbol                         0x86864
	#define parse_sprx_symbol                                0x845E8
	#define open_prx_object_symbol                           0x7DC08
	#define close_prx_object_symbol                          0x7E518
	#define lock_prx_mutex_symbol                            0x85574
	#define unlock_prx_mutex_symbol                          0x85580

	#define extend_kstack_symbol                             0x6E7C4

	#define get_pseudo_random_number_symbol                  0x258280
	#define md5_reset_symbol                                 0x162D34
	#define md5_update_symbol                                0x1637D4
	#define md5_final_symbol                                 0x163954
	#define ss_get_open_psid_symbol                          0x25A648
	#define update_mgr_read_eeprom_symbol                    0x253D8C
	#define update_mgr_write_eeprom_symbol                   0x253CD4
	#define update_mgr_if_get_token_symbol                   0x2556F0

	#define ss_params_get_update_status_symbol               0x508DC

	#define sm_get_temperature_symbol                        0x293250
	#define sm_get_fan_policy_symbol                         0x2925E4
	#define sm_set_fan_policy_symbol                         0x2943DC
	#define sm_get_temperature_patch                         0xC698
	#define sm_get_fan_policy_patch                          0x9E28
	#define sm_set_fan_policy_patch                          0xA324

	#define SHA1_init_symbol                                 0x2C9518
	#define SHA1_update_symbol                               0x2C9578
	#define SHA1_final_symbol                                0x2C972C
	#define aescbccfb_dec_symbol                             0x2C7A0C
	#define aescbccfb_enc_symbol                             0x2C77BC
	#define get_path_by_fd_symbol                            0x1B063C

	#define ECDSA_1                                          0x59220
	#define ECDSA_2                                          0x2CC938
	#define ECDSA_FLAG                                       0x476EC8
	#define sysmem_obj                                       0x477080
	#define qa_eeprom_offset                                 0x48A32

	#define syscall_table_symbol                             0x35E260
	#define syscall_call_offset                              0x2A5834

	#define read_bdvd0_symbol                                0x1BBD10
	#define read_bdvd1_symbol                                0x1BD93C
	#define read_bdvd2_symbol                                0x1CAAF4

	#define storage_internal_get_device_object_symbol        0x2A7AE4

	#define hid_mgr_read_usb_symbol                          0x1037B0
	#define hid_mgr_read_bt_symbol                           0xFD688

	#define bt_set_controller_info_internal_symbol           0xF1700

	#define device_event_port_send_call                      0x2B1C64
	#define device_event_port_send_call_restore              0x7014D64B

	#define ss_pid_call_1                                    0x2435B0

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7DAFC
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x870D0

	#define shutdown_copy_params_call                        0xAABC
	#define shutdown_copy_params_call_restore                0xBD4F0048

	#define fsloop_open_call                                 0x2C46F0
	#define fsloop_close_call                                0x2C4740
	#define fsloop_read_call                                 0x2C4780

	#define shutdown_patch_offset                            0xAAA8
	#define module_sdk_version_patch_offset                  0x296E20
	#define module_add_parameter_to_parse_sprxpatch_offset   0x86940

	#define user_thread_prio_patch                           0x2022C
	#define user_thread_prio_patch2                          0x2023C

	#define lic_patch                                        0x55D8C
	#define lic_patch_restore                                0x4826DFE9
	#define ode_patch                                        0x257888
	#define fix_80010009                                     0x59AF8
	#define fix_8001003D                                     0x560C0
	#define fix_8001003E                                     0x56184
	#define PATCH_JUMP                                       0x56138

	#define io_rtoc_entry_1                                 -0x150
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x6688

	#define storage_rtoc_entry_1                             0x1E98

	#define device_event_rtoc_entry_1                        0x2108

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x35D8

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x24F30
	#define permissions_exception2                           0xC3554
	#define permissions_exception3                           0x20300

	#define patch_data1_offset                               0x3DB840
	#define patch_func2                                      0x591E0
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDB58D
	#define patch_func8_offset1                              0x55FE8
	#define patch_func8_offset2                              0x56148
	#define patch_func8_offset2_restore                      0x482470C9
	#define patch_func9_offset                               0x59B0C
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x376830

	#define mmapper_flags_temp_patch                         0x6F698

	#define rsx_syscall_check                                0x7E3C
	#define unk_func2_unregister_service                     0x977C0
	#define unk_func3_unregister_service                     0x9C254

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E0000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52E00000056000
	#define PS1_EMU_HASH                                     0xCC28B000000A1000
	#define PS1_NETEMU_HASH                                  0xCC28D000000C4000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001D000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000026000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC28B00000339000
	#define BDP_BDVD_HASH                                    0xCC287000003FD000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000020000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000040000
	#define PREMO_PLUGIN_HASH                                0x3E80800000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x27B600000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0xC02C70000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xB19CC

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4D64
	#define ps2tonet_size_patch                              0xC4D58
	#define vmode_patch_offset                               0x442160
	#define psp_drm_patch1                                   0x23E494
	#define psp_drm_patch2                                   0x23EF34
	#define psp_drm_patch3                                   0x23EB70
	#define psp_drm_patch4                                   0x23F37C
	#define psp_drm_patchA                                   0x23E5B0
	#define psp_drm_patchB                                   0x23EE50
	#define psp_drm_patchC                                   0x23DFE8
	#define psp_drm_patchD                                   0x23E598
	#define psp_drm_patchE                                   0x23E59C
	#define psp_drm_patchF                                   0x23EF68
	#define psp_extra_drm_patch                              0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDE7A0
	#define app_home_offset                                  0x252510

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x69D2C

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x2366C
	#define ps_region_error_offset                           0x699C
	#define remote_play_offset                               0x609C
	#define ps2_nonbw_offset3                                0x167F8

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB8D8

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xCAA4

	/* nas_plugin */
	#define patch1_nas                                       0x2E84C
	#define patch2_nas                                       0x2E9B0
	#define patch3_nas                                       0x1F59C

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F678
	#define pspemu_path_offset                               0x4B148
	#define psptrans_path_offset                             0x4B1D8

	/* download_plugin */
	#define elf_patch1_download                              0x413A4
	#define elf_patch2_download                              0x413AC
	#define elf_patch3_download                              0x4BBE8
	#define elf_patch4_download                              0x4C948
	#define elf_patch5_download                              0x4C968
	#define elf_patch6_download                              0x4C9B0

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x76520
	#define elf_patch2_autodownload                          0x76528

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x159F28
	#define bdp_cinavia1_patch                               0x159F54

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1BF4

	/* emulator_api */
	#define psp_read                                         0xFC60
	#define psp_read_header                                  0x10BE4
	#define psp_drm_patch5                                   0x10A08
	#define psp_drm_patch6                                   0x10A38
	#define psp_drm_patch7                                   0x10A50
	#define psp_drm_patch8                                   0x10A54
	#define psp_drm_patch9                                   0x10B94
	#define psp_drm_patch11                                  0x10B98
	#define psp_drm_patch12                                  0x10BA8
	#define psp_product_id_patch1                            0x10CA8
	#define psp_product_id_patch3                            0x10F80

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6B0
	#define psp_prx_patch                                    0x577CC
	#define psp_savedata_bind_patch1                         0x7A4B0
	#define psp_savedata_bind_patch2                         0x7A508
	#define psp_savedata_bind_patch3                         0x7A024
	#define psp_extra_savedata_patch                         0x87520
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x58920

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD5B4

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                        0xC50D0000000ED000
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH                 0xDE52D00000057000
	#define GAME_EXT_PLUGIN_REBUG_HASH                       0xCC2680000001D000
	#define dex_ps2_nonbw_offset                             0xDEBC8
	#define dex_ps2_nonbw_offset2                            0x69A64
	#define dex_ps2_nonbw_offset3                            0x16AE8
	#define dex_ps2tonet_patch                               0xCA2C0
	#define dex_ps2tonet_size_patch                          0xCA2B4
	#define dex_vmode_patch_offset                           0x449D68
	#define dex_psp_drm_patch1                               0x245CD0
	#define dex_psp_drm_patch2                               0x246770
	#define dex_psp_drm_patch3                               0x2463AC
	#define dex_psp_drm_patch4                               0x246BB8
	#define dex_psp_drm_patchA                               0x245DEC
	#define dex_psp_drm_patchB                               0x24668C
	#define dex_psp_drm_patchC                               0x245824
	#define dex_psp_drm_patchD                               0x245DD4
	#define dex_psp_drm_patchE                               0x245DD8
	#define dex_psp_drm_patchF                               0x2467A4
	#define dex_psp_extra_drm_patch                          0x0
#endif

#ifdef FIRMWARE_441D

	#define FIRMWARE_VERSION                                 0x441

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003FA2B0ULL
		#define PS3MAPI_IDPS_2                               0x8000000000496F3CULL
		#define PS3MAPI_PSID                                 0x8000000000496F54ULL
	#endif
	#define FIRMWARE_DEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x3665C0

	#define create_kernel_object_symbol                      0x1265C
	#define destroy_kernel_object_symbol                     0x11FC0
	#define destroy_shared_kernel_object_symbol              0x11934
	#define open_kernel_object_symbol                        0x12CAC
	#define open_shared_kernel_object_symbol                 0x12ABC
	#define close_kernel_object_handle_symbol                0x120DC

	#define alloc_symbol                                     0x66890
	#define dealloc_symbol                                   0x66CCC
	#define copy_to_user_symbol                              0xFEA4
	#define copy_from_user_symbol                            0x100C0
	#define copy_to_process_symbol                           0xFF5C
	#define copy_from_process_symbol                         0xFD6C
	#define process_read_memory_symbol                       0x29E3C8
	#define process_write_memory_symbol                      0x29E23C
	#define page_allocate_symbol                             0x62400
	#define page_free_symbol                                 0x61E64
	#define page_export_to_proc_symbol                       0x6259C
	#define page_unexport_from_proc_symbol                   0x61D58
	#define kernel_ea_to_lpar_addr_symbol                    0x72304
	#define process_ea_to_lpar_addr_ex_symbol                0x79EA4
	#define set_pte_symbol                                   0x603FC
	#define map_process_memory_symbol                        0x799B0
	#define panic_symbol                                     0x2A505C

	#define memcpy_symbol                                    0x81070
	#define memset_symbol                                    0x50D84
	#define memcmp_symbol                                    0x50094
	#define memchr_symbol                                    0x50044
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
	#define strrchr_symbol                                   0x51068

	#define spin_lock_irqsave_ex_symbol                      0x2A522C
	#define spin_unlock_irqrestore_ex_symbol                 0x2A5200

	#define create_process_common_symbol                     0x2A2040
	#define create_process_base_symbol                       0x2A16E4
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x2A1E40

	#define ppu_thread_create_symbol                         0x145A8
	#define ppu_thread_exit_symbol                           0x14660
	#define ppu_thread_join_symbol                           0x146B4
	#define ppu_thread_delay_symbol                          0x2A458
	#define create_kernel_thread_symbol                      0x26548
	#define create_user_thread_symbol                        0x26C84
	#define create_user_thread2_symbol                       0x26AA8
	#define start_thread_symbol                              0x255E0
	#define run_thread_symbol                                0x24DA4
	#define self_threading_symbol                            0x27290
	#define register_thread_symbol                           0x29DE54
	#define allocate_user_stack_symbol                       0x29E63C
	#define deallocate_user_stack_symbol                     0x29E5A4

	#define mutex_create_symbol                              0x13CF0
	#define mutex_destroy_symbol                             0x13C88
	#define mutex_lock_symbol                                0x13C80
	#define mutex_lock_ex_symbol                             0x1F384
	#define mutex_trylock_symbol                             0x13C7C
	#define mutex_unlock_symbol                              0x13C78

	#define cond_create_symbol                               0x13E5C
	#define cond_destroy_symbol                              0x13E0C
	#define cond_wait_symbol                                 0x13E04
	#define cond_wait_ex_symbol                              0x20970
	#define cond_signal_symbol                               0x13DE0
	#define cond_signal_all_symbol                           0x13DBC

	#define semaphore_initialize_symbol                      0x342E4
	#define semaphore_wait_ex_symbol                         0x33FEC
	#define semaphore_trywait_symbol                         0x33BD4
	#define semaphore_post_ex_symbol                         0x33D20

	#define event_port_create_symbol                         0x1372C
	#define event_port_destroy_symbol                        0x13B94
	#define event_port_connect_symbol                        0x13C0C
	#define event_port_disconnect_symbol                     0x13B38
	#define event_port_send_symbol                           0x13724
	#define event_port_send_ex_symbol                        0x2D038

	#define event_queue_create_symbol                        0x13A34
	#define event_queue_destroy_symbol                       0x139BC
	#define event_queue_receive_symbol                       0x13800
	#define event_queue_tryreceive_symbol                    0x138CC

	#define cellFsOpen_symbol                                0x2DBA04
	#define cellFsClose_symbol                               0x2DB86C
	#define cellFsRead_symbol                                0x2DB9A8
	#define cellFsWrite_symbol                               0x2DB914
	#define cellFsLseek_symbol                               0x2DB168
	#define cellFsStat_symbol                                0x2DB220
	#define cellFsUtime_symbol                               0x2DCAD0
	#define cellFsUnlink_internal_symbol                     0x1B0FE4
	#define cellFsRename_internal_symbol                     0x1ABFF0

	#define cellFsUtilMount_symbol                           0x2DAEDC
	#define cellFsUtilUmount_symbol                          0x2DAEB0
	#define cellFsUtilNewfs_symbol                           0x2DC768

	#define pathdup_from_user_symbol                         0x1B7190
	#define open_path_symbol                                 0x2DB73C
	#define open_fs_object_symbol                            0x19667C
	#define close_fs_object_symbol                           0x19564C

	#define storage_get_device_info_symbol                   0x2BC338
	#define storage_get_device_config_symbol                 0x2BA9C4
	#define storage_open_symbol                              0x2BC560
	#define storage_close_symbol                             0x2BAD4C
	#define storage_read_symbol                              0x2B9F34
	#define storage_write_symbol                             0x2B9E04
	#define storage_send_device_command_symbol               0x2B9A54
	#define storage_map_io_memory_symbol                     0x2BC1E4
	#define storage_unmap_io_memory_symbol                   0x2BC0A0
	#define new_medium_listener_object_symbol                0x9B1AC
	#define delete_medium_listener_object_symbol             0x9C9E4
	#define set_medium_event_callbacks_symbol                0x9CD48

	#define cellUsbdRegisterLdd_symbol                       0x296340
	#define cellUsbdUnregisterLdd_symbol                     0x2962F0
	#define cellUsbdScanStaticDescriptor_symbol              0x297540
	#define cellUsbdOpenPipe_symbol                          0x2975F0
	#define cellUsbdClosePipe_symbol                         0x2975A0
	#define cellUsbdControlTransfer_symbol                   0x2974A4
	#define cellUsbdBulkTransfer_symbol                      0x297424

	#define decrypt_func_symbol                              0x38000
	#define lv1_call_99_wrapper_symbol                       0x525C0
	#define modules_verification_symbol                      0x5C140
	#define authenticate_program_segment_symbol              0x5D57C

	#define prx_load_module_symbol                           0x8B880
	#define prx_start_module_symbol                          0x8A54C
	#define prx_stop_module_symbol                           0x8B924
	#define prx_unload_module_symbol                         0x8A280
	#define prx_get_module_info_symbol                       0x89C78
	#define prx_get_module_id_by_address_symbol              0x89B88
	#define prx_get_module_id_by_name_symbol                 0x89BD8
	#define prx_get_module_list_symbol                       0x89CF8
	#define load_module_by_fd_symbol                         0x8AEB0
	#define parse_sprx_symbol                                0x88BA4
	#define open_prx_object_symbol                           0x81C2C
	#define close_prx_object_symbol                          0x8253C
	#define lock_prx_mutex_symbol                            0x89B30
	#define unlock_prx_mutex_symbol                          0x89B3C

	#define extend_kstack_symbol                             0x7225C

	#define get_pseudo_random_number_symbol                  0x25E69C
	#define md5_reset_symbol                                 0x169008
	#define md5_update_symbol                                0x169AA8
	#define md5_final_symbol                                 0x169C28
	#define ss_get_open_psid_symbol                          0x260A64
	#define update_mgr_read_eeprom_symbol                    0x25A190
	#define update_mgr_write_eeprom_symbol                   0x25A0C4
	#define update_mgr_if_get_token_symbol                   0x25BB0C

	#define ss_params_get_update_status_symbol               0x541CC

	#define sm_get_temperature_symbol                        0x29966C
	#define sm_get_fan_policy_symbol                         0x298A00
	#define sm_set_fan_policy_symbol                         0x29A9C8
	#define sm_get_temperature_patch                         0xC718
	#define sm_get_fan_policy_patch                          0x9EA8
	#define sm_set_fan_policy_patch                          0xA3A4

	#define SHA1_init_symbol                                 0x2E3F7C
	#define SHA1_update_symbol                               0x2E3FDC
	#define SHA1_final_symbol                                0x2E4190
	#define aescbccfb_dec_symbol                             0x2E2470
	#define aescbccfb_enc_symbol                             0x2E2220
	#define get_path_by_fd_symbol                            0x1B6A2C

	#define ECDSA_1                                          0x5CB38
	#define ECDSA_2                                          0x2E739C
	#define ECDSA_FLAG                                       0x496EC8
	#define sysmem_obj                                       0x497080
	#define qa_eeprom_offset                                 0x4C2DE

	#define syscall_table_symbol                             0x37C9E8
	#define syscall_call_offset                              0x2ADA88

	#define read_bdvd0_symbol                                0x1C2100
	#define read_bdvd1_symbol                                0x1C3D2C
	#define read_bdvd2_symbol                                0x1D0EE4

	#define storage_internal_get_device_object_symbol        0x2B950C

	#define hid_mgr_read_usb_symbol                          0x1091FC
	#define hid_mgr_read_bt_symbol                           0x1030D4

	#define bt_set_controller_info_internal_symbol           0xF714C

	#define device_event_port_send_call                      0x2C64FC
	#define device_event_port_send_call_restore              0x28D2D44B

	#define ss_pid_call_1                                    0x2499A0

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x81B20
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x8B71C

	#define shutdown_copy_params_call                        0xAB3C
	#define shutdown_copy_params_call_restore                0x85550048

	#define fsloop_open_call                                 0x2DBB9C
	#define fsloop_close_call                                0x2DBBEC
	#define fsloop_read_call                                 0x2DBC2C

	#define shutdown_patch_offset                            0xAB28
	#define module_sdk_version_patch_offset                  0x29D47C
	#define module_add_parameter_to_parse_sprxpatch_offset   0x8AF8C

	#define user_thread_prio_patch                           0x21C24
	#define user_thread_prio_patch2                          0x21C34

	#define lic_patch                                        0x596A4
	#define lic_patch_restore                                0x48281B7D
	#define ode_patch                                        0x25DCA4
	#define fix_80010009                                     0x5D410
	#define fix_8001003D                                     0x599D8
	#define fix_8001003E                                     0x59A9C
	#define PATCH_JUMP                                       0x59A50

	#define io_rtoc_entry_1                                 -0x20
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65A8

	#define storage_rtoc_entry_1                             0x2370

	#define device_event_rtoc_entry_1                        0x26F8

	#define time_rtoc_entry_1                               -0x75E0
	#define time_rtoc_entry_2                               -0x75E8

	#define thread_rtoc_entry_1                             -0x7660

	#define process_rtoc_entry_1                            -0x77A0

	#define bt_rtoc_entry_1                                 -0x34B0

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x26B28
	#define permissions_exception2                           0xC8C0C
	#define permissions_exception3                           0x21CF8

	#define patch_data1_offset                               0x3FA2C0
	#define patch_func2                                      0x5CAF8
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDB4DD
	#define patch_func8_offset1                              0x59900
	#define patch_func8_offset2                              0x59A60
	#define patch_func8_offset2_restore                      0x4824B5FD
	#define patch_func9_offset                               0x5D424
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x3952B0

	#define mmapper_flags_temp_patch                         0x73270

	#define rsx_syscall_check                                0x7E3C
	#define unk_func2_unregister_service                     0x9CE78
	#define unk_func3_unregister_service                     0xA190C

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E3000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000ED000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52D00000057000
	#define PS1_EMU_HASH                                     0xCC28B000000A1000
	#define PS1_NETEMU_HASH                                  0xCC28D000000C4000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001D000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000026000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC28B00000339000
	#define BDP_BDVD_HASH                                    0xCC287000003FD000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000020000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000040000
	#define PREMO_PLUGIN_HASH                                0x3E80800000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x27B600000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0xC02C70000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xB19CC

	/* vsh */
	#define vsh_text_size                                    0x6C0000
	#define ps2tonet_patch                                   0xCA2C0
	#define ps2tonet_size_patch                              0xCA2B4
	#define vmode_patch_offset                               0x449D68
	#define psp_drm_patch1                                   0x245CD0
	#define psp_drm_patch2                                   0x246770
	#define psp_drm_patch3                                   0x2463AC
	#define psp_drm_patch4                                   0x246BB8
	#define psp_drm_patchA                                   0x245DEC
	#define psp_drm_patchB                                   0x24668C
	#define psp_drm_patchC                                   0x245824
	#define psp_drm_patchD                                   0x245DD4
	#define psp_drm_patchE                                   0x245DD8
	#define psp_drm_patchF                                   0x2467A4
	#define psp_extra_drm_patch                              0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDEBC8
	#define app_home_offset                                  0x253160

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x69A64

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23888
	#define ps_region_error_offset                           0x6958
	#define remote_play_offset                               0x609C
	#define ps2_nonbw_offset3                                0x16AE8

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB8D8

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xCAA4

	/* nas_plugin */
	#define patch1_nas                                       0x2EC6C
	#define patch2_nas                                       0x2EDD0
	#define patch3_nas                                       0x1F85C

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x20160
	#define pspemu_path_offset                               0x4C398
	#define psptrans_path_offset                             0x4C450

	/* download_plugin */
	#define elf_patch1_download                              0x41338
	#define elf_patch2_download                              0x41340
	#define elf_patch3_download                              0x4BB00
	#define elf_patch4_download                              0x4C860
	#define elf_patch5_download                              0x4C880
	#define elf_patch6_download                              0x4C8C8

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x763D0
	#define elf_patch2_autodownload                          0x763D8

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x159F28
	#define bdp_cinavia1_patch                               0x159F54

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1BF4

	/* emulator_api */
	#define psp_read                                         0xFC60
	#define psp_read_header                                  0x10BE4
	#define psp_drm_patch5                                   0x10A08
	#define psp_drm_patch6                                   0x10A38
	#define psp_drm_patch7                                   0x10A50
	#define psp_drm_patch8                                   0x10A54
	#define psp_drm_patch9                                   0x10B94
	#define psp_drm_patch11                                  0x10B98
	#define psp_drm_patch12                                  0x10BA8
	#define psp_product_id_patch1                            0x10CA8
	#define psp_product_id_patch3                            0x10F80

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6B0
	#define psp_prx_patch                                    0x577CC
	#define psp_savedata_bind_patch1                         0x7A4B0
	#define psp_savedata_bind_patch2                         0x7A508
	#define psp_savedata_bind_patch3                         0x7A024
	#define psp_extra_savedata_patch                         0x87520
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x58920

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD5B4

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* CEX */
	#define cex_ps2tonet_patch                               0xC4D64
	#define cex_ps2tonet_size_patch                          0xC4D58
	#define cex_vmode_patch_offset                           0x442160
	#define cex_psp_drm_patch1                               0x23E494
	#define cex_psp_drm_patch2                               0x23EF34
	#define cex_psp_drm_patch3                               0x23EB70
	#define cex_psp_drm_patch4                               0x23F37C
	#define cex_psp_drm_patchA                               0x23E5B0
	#define cex_psp_drm_patchB                               0x23EE50
	#define cex_psp_drm_patchC                               0x23DFE8
	#define cex_psp_drm_patchD                               0x23E598
	#define cex_psp_drm_patchE                               0x23E59C
	#define cex_psp_drm_patchF                               0x23EF68
	#define cex_psp_extra_drm_patch                          0x0
#endif

#ifdef FIRMWARE_446C

	#define FIRMWARE_VERSION                                 0x446

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003DBE30ULL
		#define PS3MAPI_IDPS_2                               0x8000000000476F3CULL
		#define PS3MAPI_PSID                                 0x8000000000476F54ULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x348DF0

	#define create_kernel_object_symbol                      0x12014
	#define destroy_kernel_object_symbol                     0x11978
	#define destroy_shared_kernel_object_symbol              0x112EC
	#define open_kernel_object_symbol                        0x12664
	#define open_shared_kernel_object_symbol                 0x12474
	#define close_kernel_object_handle_symbol                0x11A94

	#define alloc_symbol                                     0x62F78
	#define dealloc_symbol                                   0x633B4
	#define copy_to_user_symbol                              0xF85C
	#define copy_from_user_symbol                            0xFA78
	#define copy_to_process_symbol                           0xF914
	#define copy_from_process_symbol                         0xF724
	#define process_read_memory_symbol                       0x298084
	#define process_write_memory_symbol                      0x297EF8
	#define page_allocate_symbol                             0x5EAE8
	#define page_free_symbol                                 0x5E54C
	#define page_export_to_proc_symbol                       0x5EC84
	#define page_unexport_from_proc_symbol                   0x5E440
	#define kernel_ea_to_lpar_addr_symbol                    0x6E86C
	#define process_ea_to_lpar_addr_ex_symbol                0x75E80
	#define set_pte_symbol                                   0x5CAE4
	#define map_process_memory_symbol                        0x7598C
	#define panic_symbol                                     0x29D730

	#define memcpy_symbol                                    0x7D04C
	#define memset_symbol                                    0x4D494
	#define memcmp_symbol                                    0x4C7A4
	#define memchr_symbol                                    0x4C754
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
	#define strrchr_symbol                                   0x4D778

	#define spin_lock_irqsave_ex_symbol                      0x29D900
	#define spin_unlock_irqrestore_ex_symbol                 0x29D8D4

	#define create_process_common_symbol                     0x29B6F8
	#define create_process_base_symbol                       0x29ADB4
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x29B504

	#define ppu_thread_create_symbol                         0x13F2C
	#define ppu_thread_exit_symbol                           0x13FE4
	#define ppu_thread_join_symbol                           0x14038
	#define ppu_thread_delay_symbol                          0x285CC
	#define create_kernel_thread_symbol                      0x24950
	#define create_user_thread_symbol                        0x2508C
	#define create_user_thread2_symbol                       0x24EB0
	#define start_thread_symbol                              0x23B7C
	#define run_thread_symbol                                0x233AC
	#define self_threading_symbol                            0x25698
	#define register_thread_symbol                           0x297B10
	#define allocate_user_stack_symbol                       0x2982F8
	#define deallocate_user_stack_symbol                     0x298260

	#define mutex_create_symbol                              0x136A0
	#define mutex_destroy_symbol                             0x13638
	#define mutex_lock_symbol                                0x13630
	#define mutex_lock_ex_symbol                             0x1D98C
	#define mutex_trylock_symbol                             0x1362C
	#define mutex_unlock_symbol                              0x13628

	#define cond_create_symbol                               0x1380C
	#define cond_destroy_symbol                              0x137BC
	#define cond_wait_symbol                                 0x137B4
	#define cond_wait_ex_symbol                              0x1EF78
	#define cond_signal_symbol                               0x13790
	#define cond_signal_all_symbol                           0x1376C

	#define semaphore_initialize_symbol                      0x30A7C
	#define semaphore_wait_ex_symbol                         0x30784
	#define semaphore_trywait_symbol                         0x3036C
	#define semaphore_post_ex_symbol                         0x304B8

	#define event_port_create_symbol                         0x130DC
	#define event_port_destroy_symbol                        0x13544
	#define event_port_connect_symbol                        0x135BC
	#define event_port_disconnect_symbol                     0x134E8
	#define event_port_send_symbol                           0x130D4
	#define event_port_send_ex_symbol                        0x2B02C

	#define event_queue_create_symbol                        0x133E4
	#define event_queue_destroy_symbol                       0x1336C
	#define event_queue_receive_symbol                       0x131B0
	#define event_queue_tryreceive_symbol                    0x1327C

	#define cellFsOpen_symbol                                0x2C4A78
	#define cellFsClose_symbol                               0x2C48E0
	#define cellFsRead_symbol                                0x2C4A1C
	#define cellFsWrite_symbol                               0x2C4988
	#define cellFsLseek_symbol                               0x2C4010
	#define cellFsStat_symbol                                0x2C4294
	#define cellFsUtime_symbol                               0x2C5CB0
	#define cellFsUnlink_internal_symbol                     0x1AAF70
	#define cellFsRename_internal_symbol                     0x1A5F7C

	#define cellFsUtilMount_symbol                           0x2C3DF0
	#define cellFsUtilUmount_symbol                          0x2C3DC4
	#define cellFsUtilNewfs_symbol                           0x2C5748

	#define pathdup_from_user_symbol                         0x1B1000
	#define open_path_symbol                                 0x2C47B0
	#define open_fs_object_symbol                            0x190420
	#define close_fs_object_symbol                           0x18F41C

	#define storage_get_device_info_symbol                   0x2A9C50
	#define storage_get_device_config_symbol                 0x2A90E0
	#define storage_open_symbol                              0x2A9660
	#define storage_close_symbol                             0x2A9450
	#define storage_read_symbol                              0x2A89C0
	#define storage_write_symbol                             0x2A8890
	#define storage_send_device_command_symbol               0x2A854C
	#define storage_map_io_memory_symbol                     0x2A9B0C
	#define storage_unmap_io_memory_symbol                   0x2A99D8
	#define new_medium_listener_object_symbol                0x95AF4
	#define delete_medium_listener_object_symbol             0x9732C
	#define set_medium_event_callbacks_symbol                0x97690

	#define cellUsbdRegisterLdd_symbol                       0x290444
	#define cellUsbdUnregisterLdd_symbol                     0x2903F4
	#define cellUsbdScanStaticDescriptor_symbol              0x291644
	#define cellUsbdOpenPipe_symbol                          0x2916F4
	#define cellUsbdClosePipe_symbol                         0x2916A4
	#define cellUsbdControlTransfer_symbol                   0x2915A8
	#define cellUsbdBulkTransfer_symbol                      0x291528

	#define decrypt_func_symbol                              0x34798
	#define lv1_call_99_wrapper_symbol                       0x4ECD0
	#define modules_verification_symbol                      0x58828
	#define authenticate_program_segment_symbol              0x59C64

	#define prx_load_module_symbol                           0x87234
	#define prx_start_module_symbol                          0x85F00
	#define prx_stop_module_symbol                           0x872D8
	#define prx_unload_module_symbol                         0x85C34
	#define prx_get_module_info_symbol                       0x856BC
	#define prx_get_module_id_by_address_symbol              0x855CC
	#define prx_get_module_id_by_name_symbol                 0x8561C
	#define prx_get_module_list_symbol                       0x8573C
	#define load_module_by_fd_symbol                         0x86864
	#define parse_sprx_symbol                                0x845E8
	#define open_prx_object_symbol                           0x7DC08
	#define close_prx_object_symbol                          0x7E518
	#define lock_prx_mutex_symbol                            0x85574
	#define unlock_prx_mutex_symbol                          0x85580

	#define extend_kstack_symbol                             0x6E7C4

	#define get_pseudo_random_number_symbol                  0x2587A0
	#define md5_reset_symbol                                 0x162DB0
	#define md5_update_symbol                                0x163850
	#define md5_final_symbol                                 0x1639D0
	#define ss_get_open_psid_symbol                          0x25AB68
	#define update_mgr_read_eeprom_symbol                    0x2542AC
	#define update_mgr_write_eeprom_symbol                   0x2541F4
	#define update_mgr_if_get_token_symbol                   0x255C10

	#define ss_params_get_update_status_symbol               0x508DC

	#define sm_get_temperature_symbol                        0x293770
	#define sm_get_fan_policy_symbol                         0x292B04
	#define sm_set_fan_policy_symbol                         0x2948FC
	#define sm_get_temperature_patch                         0xC698
	#define sm_get_fan_policy_patch                          0x9E28
	#define sm_set_fan_policy_patch                          0xA324

	#define SHA1_init_symbol                                 0x2C9A38
	#define SHA1_update_symbol                               0x2C9A98
	#define SHA1_final_symbol                                0x2C9C4C
	#define aescbccfb_dec_symbol                             0x2C7F2C
	#define aescbccfb_enc_symbol                             0x2C7CDC
	#define get_path_by_fd_symbol                            0x1B089C

	#define ECDSA_1                                          0x59220
	#define ECDSA_2                                          0x2CCE58
	#define ECDSA_FLAG                                       0x476EC8
	#define sysmem_obj                                       0x477080
	#define qa_eeprom_offset                                 0x48A32

	#define syscall_table_symbol                             0x35E860
	#define syscall_call_offset                              0x2A5D54

	#define read_bdvd0_symbol                                0x1BBF70
	#define read_bdvd1_symbol                                0x1BDB9C
	#define read_bdvd2_symbol                                0x1CAD54

	#define storage_internal_get_device_object_symbol        0x2A8004

	#define hid_mgr_read_usb_symbol                          0x1037EC
	#define hid_mgr_read_bt_symbol                           0xFD6C4

	#define bt_set_controller_info_internal_symbol           0xF1730

	#define device_event_port_send_call                      0x2B2184
	#define device_event_port_send_call_restore              0x500FD64B

	#define ss_pid_call_1                                    0x243AD0

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7DAFC
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x870D0

	#define shutdown_copy_params_call                        0xAABC
	#define shutdown_copy_params_call_restore                0xBD4F0048

	#define fsloop_open_call                                 0x2C4C10
	#define fsloop_close_call                                0x2C4C60
	#define fsloop_read_call                                 0x2C4CA0

	#define shutdown_patch_offset                            0xAAA8
	#define module_sdk_version_patch_offset                  0x297340
	#define module_add_parameter_to_parse_sprxpatch_offset   0x86940

	#define user_thread_prio_patch                           0x2022C
	#define user_thread_prio_patch2                          0x2023C

	#define lic_patch                                        0x55D8C
	#define lic_patch_restore                                0x4826E509
	#define ode_patch                                        0x257DA8
	#define fix_80010009                                     0x59AF8
	#define fix_8001003D                                     0x560C0
	#define fix_8001003E                                     0x56184
	#define PATCH_JUMP                                       0x56138

	#define io_rtoc_entry_1                                 -0x150
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x6688

	#define storage_rtoc_entry_1                             0x1E98

	#define device_event_rtoc_entry_1                        0x2108

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x35D8

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x24F30
	#define permissions_exception2                           0xC3554
	#define permissions_exception3                           0x20300

	#define patch_data1_offset                               0x3DBE40
	#define patch_func2                                      0x591E0
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDB58D
	#define patch_func8_offset1                              0x55FE8
	#define patch_func8_offset2                              0x56148
	#define patch_func8_offset2_restore                      0x482475E9
	#define patch_func9_offset                               0x59B0C
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x376E30

	#define mmapper_flags_temp_patch                         0x6F698

	#define rsx_syscall_check                                0x7E3C
	#define unk_func2_unregister_service                     0x977C0
	#define unk_func3_unregister_service                     0x9C254

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E0000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52E00000056000
	#define PS1_EMU_HASH                                     0xCC28B000000A1000
	#define PS1_NETEMU_HASH                                  0xCC28D000000C4000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001D000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000026000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC28B00000339000
	#define BDP_BDVD_HASH                                    0xCC287000003FD000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000020000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000040000
	#define PREMO_PLUGIN_HASH                                0x3E80800000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x27B600000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0xC02C70000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xB19CC

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4D64
	#define ps2tonet_size_patch                              0xC4D58
	#define vmode_patch_offset                               0x442D68
	#define psp_drm_patch1                                   0x23EEF8
	#define psp_drm_patch2                                   0x23F998
	#define psp_drm_patch3                                   0x23F5D4
	#define psp_drm_patch4                                   0x23FDE0
	#define psp_drm_patchA                                   0x23F014
	#define psp_drm_patchB                                   0x23F8B4
	#define psp_drm_patchC                                   0x23EA4C
	#define psp_drm_patchD                                   0x23EFFC
	#define psp_drm_patchE                                   0x23F000
	#define psp_drm_patchF                                   0x23F9CC
	#define psp_extra_drm_patch                              0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDE81C
	#define app_home_offset                                  0x252538

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x69D28

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x2366C
	#define ps_region_error_offset                           0x699C
	#define remote_play_offset                               0x609C
	#define ps2_nonbw_offset3                                0x167F8

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB8D8

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xCAA4

	/* nas_plugin */
	#define patch1_nas                                       0x2E8A0
	#define patch2_nas                                       0x2EA04
	#define patch3_nas                                       0x1F5F0

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F678
	#define pspemu_path_offset                               0x4B158
	#define psptrans_path_offset                             0x4B1E8

	/* download_plugin */
	#define elf_patch1_download                              0x42560
	#define elf_patch2_download                              0x42568
	#define elf_patch3_download                              0x4CDE8
	#define elf_patch4_download                              0x4DB60
	#define elf_patch5_download                              0x4DB80
	#define elf_patch6_download                              0x4DCD8

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x794E0
	#define elf_patch2_autodownload                          0x794E8

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x159F28
	#define bdp_cinavia1_patch                               0x159F54

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1BF8

	/* emulator_api */
	#define psp_read                                         0xFC60
	#define psp_read_header                                  0x10BE4
	#define psp_drm_patch5                                   0x10A08
	#define psp_drm_patch6                                   0x10A38
	#define psp_drm_patch7                                   0x10A50
	#define psp_drm_patch8                                   0x10A54
	#define psp_drm_patch9                                   0x10B94
	#define psp_drm_patch11                                  0x10B98
	#define psp_drm_patch12                                  0x10BA8
	#define psp_product_id_patch1                            0x10CA8
	#define psp_product_id_patch3                            0x10F80

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6B0
	#define psp_prx_patch                                    0x577CC
	#define psp_savedata_bind_patch1                         0x7A4B0
	#define psp_savedata_bind_patch2                         0x7A508
	#define psp_savedata_bind_patch3                         0x7A024
	#define psp_extra_savedata_patch                         0x87530
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x58920

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD5B4

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                        0xC50D0000000ED000
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH                 0xDE52D00000057000
	#define GAME_EXT_PLUGIN_REBUG_HASH                       0xCC2680000001D000
	#define dex_ps2_nonbw_offset                             0xDEC48
	#define dex_ps2_nonbw_offset2                            0x69A5C
	#define dex_ps2_nonbw_offset3                            0x16AE8
	#define dex_ps2tonet_patch                               0xCA2C0
	#define dex_ps2tonet_size_patch                          0xCA2B4
	#define dex_vmode_patch_offset                           0x44A970
	#define dex_psp_drm_patch1                               0x246734
	#define dex_psp_drm_patch2                               0x2471D4
	#define dex_psp_drm_patch3                               0x246E10
	#define dex_psp_drm_patch4                               0x24761C
	#define dex_psp_drm_patchA                               0x246850
	#define dex_psp_drm_patchB                               0x2470F0
	#define dex_psp_drm_patchC                               0x246288
	#define dex_psp_drm_patchD                               0x246838
	#define dex_psp_drm_patchE                               0x24683C
	#define dex_psp_drm_patchF                               0x247208
	#define dex_psp_extra_drm_patch                          0x0
#endif

#ifdef FIRMWARE_446D

	#define FIRMWARE_VERSION                                 0x446

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003FA8B0ULL
		#define PS3MAPI_IDPS_2                               0x8000000000496F3CULL
		#define PS3MAPI_PSID                                 0x8000000000496F54ULL
	#endif
	#define FIRMWARE_DEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x366BD0

	#define create_kernel_object_symbol                      0x1265C
	#define destroy_kernel_object_symbol                     0x11FC0
	#define destroy_shared_kernel_object_symbol              0x11934
	#define open_kernel_object_symbol                        0x12CAC
	#define open_shared_kernel_object_symbol                 0x12ABC
	#define close_kernel_object_handle_symbol                0x120DC

	#define alloc_symbol                                     0x66890
	#define dealloc_symbol                                   0x66CCC
	#define copy_to_user_symbol                              0xFEA4
	#define copy_from_user_symbol                            0x100C0
	#define copy_to_process_symbol                           0xFF5C
	#define copy_from_process_symbol                         0xFD6C
	#define process_read_memory_symbol                       0x29E8E8
	#define process_write_memory_symbol                      0x29E75C
	#define page_allocate_symbol                             0x62400
	#define page_free_symbol                                 0x61E64
	#define page_export_to_proc_symbol                       0x6259C
	#define page_unexport_from_proc_symbol                   0x61D58
	#define kernel_ea_to_lpar_addr_symbol                    0x72304
	#define process_ea_to_lpar_addr_ex_symbol                0x79EA4
	#define set_pte_symbol                                   0x603FC
	#define map_process_memory_symbol                        0x799B0
	#define panic_symbol                                     0x2A557C

	#define memcpy_symbol                                    0x81070
	#define memset_symbol                                    0x50D84
	#define memcmp_symbol                                    0x50094
	#define memchr_symbol                                    0x50044
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
	#define strrchr_symbol                                   0x51068

	#define spin_lock_irqsave_ex_symbol                      0x2A574C
	#define spin_unlock_irqrestore_ex_symbol                 0x2A5720

	#define create_process_common_symbol                     0x2A2560
	#define create_process_base_symbol                       0x2A1C04
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x2A2360

	#define ppu_thread_create_symbol                         0x145A8
	#define ppu_thread_exit_symbol                           0x14660
	#define ppu_thread_join_symbol                           0x146B4
	#define ppu_thread_delay_symbol                          0x2A458
	#define create_kernel_thread_symbol                      0x26548
	#define create_user_thread_symbol                        0x26C84
	#define create_user_thread2_symbol                       0x26AA8
	#define start_thread_symbol                              0x255E0
	#define run_thread_symbol                                0x24DA4
	#define self_threading_symbol                            0x27290
	#define register_thread_symbol                           0x29E374
	#define allocate_user_stack_symbol                       0x29EB5C
	#define deallocate_user_stack_symbol                     0x29EAC4

	#define mutex_create_symbol                              0x13CF0
	#define mutex_destroy_symbol                             0x13C88
	#define mutex_lock_symbol                                0x13C80
	#define mutex_lock_ex_symbol                             0x1F384
	#define mutex_trylock_symbol                             0x13C7C
	#define mutex_unlock_symbol                              0x13C78

	#define cond_create_symbol                               0x13E5C
	#define cond_destroy_symbol                              0x13E0C
	#define cond_wait_symbol                                 0x13E04
	#define cond_wait_ex_symbol                              0x20970
	#define cond_signal_symbol                               0x13DE0
	#define cond_signal_all_symbol                           0x13DBC

	#define semaphore_initialize_symbol                      0x342E4
	#define semaphore_wait_ex_symbol                         0x33FEC
	#define semaphore_trywait_symbol                         0x33BD4
	#define semaphore_post_ex_symbol                         0x33D20

	#define event_port_create_symbol                         0x1372C
	#define event_port_destroy_symbol                        0x13B94
	#define event_port_connect_symbol                        0x13C0C
	#define event_port_disconnect_symbol                     0x13B38
	#define event_port_send_symbol                           0x13724
	#define event_port_send_ex_symbol                        0x2D038

	#define event_queue_create_symbol                        0x13A34
	#define event_queue_destroy_symbol                       0x139BC
	#define event_queue_receive_symbol                       0x13800
	#define event_queue_tryreceive_symbol                    0x138CC

	#define cellFsOpen_symbol                                0x2DBF24
	#define cellFsClose_symbol                               0x2DBD8C
	#define cellFsRead_symbol                                0x2DBEC8
	#define cellFsWrite_symbol                               0x2DBE34
	#define cellFsLseek_symbol                               0x2DB688
	#define cellFsStat_symbol                                0x2DB740
	#define cellFsUtime_symbol                               0x2DCFF0
	#define cellFsUnlink_internal_symbol                     0x1B1244
	#define cellFsRename_internal_symbol                     0x1AC250

	#define cellFsUtilMount_symbol                           0x2DB3FC
	#define cellFsUtilUmount_symbol                          0x2DB3D0
	#define cellFsUtilNewfs_symbol                           0x2DCC88

	#define pathdup_from_user_symbol                         0x1B73F0
	#define open_path_symbol                                 0x2DBC5C
	#define open_fs_object_symbol                            0x1966F4
	#define close_fs_object_symbol                           0x1956F0

	#define storage_get_device_info_symbol                   0x2BC858
	#define storage_get_device_config_symbol                 0x2BAEE4
	#define storage_open_symbol                              0x2BCA80
	#define storage_close_symbol                             0x2BB26C
	#define storage_read_symbol                              0x2BA454
	#define storage_write_symbol                             0x2BA324
	#define storage_send_device_command_symbol               0x2B9F74
	#define storage_map_io_memory_symbol                     0x2BC704
	#define storage_unmap_io_memory_symbol                   0x2BC5C0
	#define new_medium_listener_object_symbol                0x9B1AC
	#define delete_medium_listener_object_symbol             0x9C9E4
	#define set_medium_event_callbacks_symbol                0x9CD48

	#define cellUsbdRegisterLdd_symbol                       0x296860
	#define cellUsbdUnregisterLdd_symbol                     0x296810
	#define cellUsbdScanStaticDescriptor_symbol              0x297A60
	#define cellUsbdOpenPipe_symbol                          0x297B10
	#define cellUsbdClosePipe_symbol                         0x297AC0
	#define cellUsbdControlTransfer_symbol                   0x2979C4
	#define cellUsbdBulkTransfer_symbol                      0x297944

	#define decrypt_func_symbol                              0x38000
	#define lv1_call_99_wrapper_symbol                       0x525C0
	#define modules_verification_symbol                      0x5C140
	#define authenticate_program_segment_symbol              0x5D57C

	#define prx_load_module_symbol                           0x8B880
	#define prx_start_module_symbol                          0x8A54C
	#define prx_stop_module_symbol                           0x8B924
	#define prx_unload_module_symbol                         0x8A280
	#define prx_get_module_info_symbol                       0x89C78
	#define prx_get_module_id_by_address_symbol              0x89B88
	#define prx_get_module_id_by_name_symbol                 0x89BD8
	#define prx_get_module_list_symbol                       0x89CF8
	#define load_module_by_fd_symbol                         0x8AEB0
	#define parse_sprx_symbol                                0x88BA4
	#define open_prx_object_symbol                           0x81C2C
	#define close_prx_object_symbol                          0x8253C
	#define lock_prx_mutex_symbol                            0x89B30
	#define unlock_prx_mutex_symbol                          0x89B3C

	#define extend_kstack_symbol                             0x7225C

	#define get_pseudo_random_number_symbol                  0x25EBBC
	#define md5_reset_symbol                                 0x169084
	#define md5_update_symbol                                0x169B24
	#define md5_final_symbol                                 0x169CA4
	#define ss_get_open_psid_symbol                          0x260F84
	#define update_mgr_read_eeprom_symbol                    0x25A6B0
	#define update_mgr_write_eeprom_symbol                   0x25A5E4
	#define update_mgr_if_get_token_symbol                   0x25C02C

	#define ss_params_get_update_status_symbol               0x541CC

	#define sm_get_temperature_symbol                        0x299B8C
	#define sm_get_fan_policy_symbol                         0x298F20
	#define sm_set_fan_policy_symbol                         0x29AEE8
	#define sm_get_temperature_patch                         0xC718
	#define sm_get_fan_policy_patch                          0x9EA8
	#define sm_set_fan_policy_patch                          0xA3A4

	#define SHA1_init_symbol                                 0x2E449C
	#define SHA1_update_symbol                               0x2E44FC
	#define SHA1_final_symbol                                0x2E46B0
	#define aescbccfb_dec_symbol                             0x2E2990
	#define aescbccfb_enc_symbol                             0x2E2740
	#define get_path_by_fd_symbol                            0x1B6C8C

	#define ECDSA_1                                          0x5CB38
	#define ECDSA_2                                          0x2E78BC
	#define ECDSA_FLAG                                       0x496EC8
	#define sysmem_obj                                       0x497080
	#define qa_eeprom_offset                                 0x4C2DE

	#define syscall_table_symbol                             0x37CFE8
	#define syscall_call_offset                              0x2ADFA8

	#define read_bdvd0_symbol                                0x1C2360
	#define read_bdvd1_symbol                                0x1C3F8C
	#define read_bdvd2_symbol                                0x1D1144

	#define storage_internal_get_device_object_symbol        0x2B9A2C

	#define hid_mgr_read_usb_symbol                          0x109238
	#define hid_mgr_read_bt_symbol                           0x103110

	#define bt_set_controller_info_internal_symbol           0xF717C

	#define device_event_port_send_call                      0x2C6A1C
	#define device_event_port_send_call_restore              0x8CDD44B

	#define ss_pid_call_1                                    0x249EC0

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x81B20
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x8B71C

	#define shutdown_copy_params_call                        0xAB3C
	#define shutdown_copy_params_call_restore                0x85550048

	#define fsloop_open_call                                 0x2DC0BC
	#define fsloop_close_call                                0x2DC10C
	#define fsloop_read_call                                 0x2DC14C

	#define shutdown_patch_offset                            0xAB28
	#define module_sdk_version_patch_offset                  0x29D99C
	#define module_add_parameter_to_parse_sprxpatch_offset   0x8AF8C

	#define user_thread_prio_patch                           0x21C24
	#define user_thread_prio_patch2                          0x21C34

	#define lic_patch                                        0x596A4
	#define lic_patch_restore                                0x4828209D
	#define ode_patch                                        0x25E1C4
	#define fix_80010009                                     0x5D410
	#define fix_8001003D                                     0x599D8
	#define fix_8001003E                                     0x59A9C
	#define PATCH_JUMP                                       0x59A50

	#define io_rtoc_entry_1                                 -0x20
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65A8

	#define storage_rtoc_entry_1                             0x2370

	#define device_event_rtoc_entry_1                        0x26F8

	#define time_rtoc_entry_1                               -0x75E0
	#define time_rtoc_entry_2                               -0x75E8

	#define thread_rtoc_entry_1                             -0x7660

	#define process_rtoc_entry_1                            -0x77A0

	#define bt_rtoc_entry_1                                 -0x34B0

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x26B28
	#define permissions_exception2                           0xC8C0C
	#define permissions_exception3                           0x21CF8

	#define patch_data1_offset                               0x3FA8C0
	#define patch_func2                                      0x5CAF8
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDB4DD
	#define patch_func8_offset1                              0x59900
	#define patch_func8_offset2                              0x59A60
	#define patch_func8_offset2_restore                      0x4824BB1D
	#define patch_func9_offset                               0x5D424
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x3958B0

	#define mmapper_flags_temp_patch                         0x73270

	#define rsx_syscall_check                                0x7E3C
	#define unk_func2_unregister_service                     0x9CE78
	#define unk_func3_unregister_service                     0xA190C

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E4000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000ED000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52D00000057000
	#define PS1_EMU_HASH                                     0xCC28B000000A1000
	#define PS1_NETEMU_HASH                                  0xCC28D000000C4000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001D000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000026000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC28B00000339000
	#define BDP_BDVD_HASH                                    0xCC287000003FD000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000020000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000040000
	#define PREMO_PLUGIN_HASH                                0x3E80800000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x27B600000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0xC02C70000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xB19CC

	/* vsh */
	#define vsh_text_size                                    0x6C0000
	#define ps2tonet_patch                                   0xCA2C0
	#define ps2tonet_size_patch                              0xCA2B4
	#define vmode_patch_offset                               0x44A970
	#define psp_drm_patch1                                   0x246734
	#define psp_drm_patch2                                   0x2471D4
	#define psp_drm_patch3                                   0x246E10
	#define psp_drm_patch4                                   0x24761C
	#define psp_drm_patchA                                   0x246850
	#define psp_drm_patchB                                   0x2470F0
	#define psp_drm_patchC                                   0x246288
	#define psp_drm_patchD                                   0x246838
	#define psp_drm_patchE                                   0x24683C
	#define psp_drm_patchF                                   0x247208
	#define psp_extra_drm_patch                              0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDEC48
	#define app_home_offset                                  0x253198

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x69A5C

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23888
	#define ps_region_error_offset                           0x6958
	#define remote_play_offset                               0x609C
	#define ps2_nonbw_offset3                                0x16AE8

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB8D8

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xCAA4

	/* nas_plugin */
	#define patch1_nas                                       0x2ECB8
	#define patch2_nas                                       0x2EE1C
	#define patch3_nas                                       0x1F8A8

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x20160
	#define pspemu_path_offset                               0x4C398
	#define psptrans_path_offset                             0x4C450

	/* download_plugin */
	#define elf_patch1_download                              0x424F4
	#define elf_patch2_download                              0x424FC
	#define elf_patch3_download                              0x4CCF8
	#define elf_patch4_download                              0x4DA70
	#define elf_patch5_download                              0x4DA90
	#define elf_patch6_download                              0x4DBE8

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x79390
	#define elf_patch2_autodownload                          0x79398

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x159F28
	#define bdp_cinavia1_patch                               0x159F54

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1BF8

	/* emulator_api */
	#define psp_read                                         0xFC60
	#define psp_read_header                                  0x10BE4
	#define psp_drm_patch5                                   0x10A08
	#define psp_drm_patch6                                   0x10A38
	#define psp_drm_patch7                                   0x10A50
	#define psp_drm_patch8                                   0x10A54
	#define psp_drm_patch9                                   0x10B94
	#define psp_drm_patch11                                  0x10B98
	#define psp_drm_patch12                                  0x10BA8
	#define psp_product_id_patch1                            0x10CA8
	#define psp_product_id_patch3                            0x10F80

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6B0
	#define psp_prx_patch                                    0x577CC
	#define psp_savedata_bind_patch1                         0x7A4B0
	#define psp_savedata_bind_patch2                         0x7A508
	#define psp_savedata_bind_patch3                         0x7A024
	#define psp_extra_savedata_patch                         0x87530
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x58920

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD5B4

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* CEX */
	#define cex_ps2tonet_patch                               0xC4D64
	#define cex_ps2tonet_size_patch                          0xC4D58
	#define cex_vmode_patch_offset                           0x442D68
	#define cex_psp_drm_patch1                               0x23EEF8
	#define cex_psp_drm_patch2                               0x23F998
	#define cex_psp_drm_patch3                               0x23F5D4
	#define cex_psp_drm_patch4                               0x23FDE0
	#define cex_psp_drm_patchA                               0x23F014
	#define cex_psp_drm_patchB                               0x23F8B4
	#define cex_psp_drm_patchC                               0x23EA4C
	#define cex_psp_drm_patchD                               0x23EFFC
	#define cex_psp_drm_patchE                               0x23F000
	#define cex_psp_drm_patchF                               0x23F9CC
	#define cex_psp_extra_drm_patch                          0x0
#endif

#ifdef FIRMWARE_450C

	#define FIRMWARE_VERSION                                 0x450

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003DE230ULL
		#define PS3MAPI_IDPS_2                               0x800000000046CF0CULL
		#define PS3MAPI_PSID                                 0x800000000046CF24ULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x34B160

	#define create_kernel_object_symbol                      0x12010
	#define destroy_kernel_object_symbol                     0x11974
	#define destroy_shared_kernel_object_symbol              0x112E8
	#define open_kernel_object_symbol                        0x12660
	#define open_shared_kernel_object_symbol                 0x12470
	#define close_kernel_object_handle_symbol                0x11A90

	#define alloc_symbol                                     0x62F74
	#define dealloc_symbol                                   0x633B0
	#define copy_to_user_symbol                              0xF858
	#define copy_from_user_symbol                            0xFA74
	#define copy_to_process_symbol                           0xF910
	#define copy_from_process_symbol                         0xF720
	#define process_read_memory_symbol                       0x27038C
	#define process_write_memory_symbol                      0x270200
	#define page_allocate_symbol                             0x5EAE4
	#define page_free_symbol                                 0x5E548
	#define page_export_to_proc_symbol                       0x5EC80
	#define page_unexport_from_proc_symbol                   0x5E43C
	#define kernel_ea_to_lpar_addr_symbol                    0x6E868
	#define process_ea_to_lpar_addr_ex_symbol                0x75E7C
	#define set_pte_symbol                                   0x5CAE0
	#define map_process_memory_symbol                        0x75988
	#define panic_symbol                                     0x275A38

	#define memcpy_symbol                                    0x7D048
	#define memset_symbol                                    0x4D490
	#define memcmp_symbol                                    0x4C7A0
	#define memchr_symbol                                    0x4C750
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
	#define strrchr_symbol                                   0x4D774

	#define spin_lock_irqsave_ex_symbol                      0x275C08
	#define spin_unlock_irqrestore_ex_symbol                 0x275BDC

	#define create_process_common_symbol                     0x273A00
	#define create_process_base_symbol                       0x2730BC
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x27380C

	#define ppu_thread_create_symbol                         0x13F28
	#define ppu_thread_exit_symbol                           0x13FE0
	#define ppu_thread_join_symbol                           0x14034
	#define ppu_thread_delay_symbol                          0x285C8
	#define create_kernel_thread_symbol                      0x2494C
	#define create_user_thread_symbol                        0x25088
	#define create_user_thread2_symbol                       0x24EAC
	#define start_thread_symbol                              0x23B78
	#define run_thread_symbol                                0x233A8
	#define self_threading_symbol                            0x25694
	#define register_thread_symbol                           0x26FE18
	#define allocate_user_stack_symbol                       0x270600
	#define deallocate_user_stack_symbol                     0x270568

	#define mutex_create_symbol                              0x1369C
	#define mutex_destroy_symbol                             0x13634
	#define mutex_lock_symbol                                0x1362C
	#define mutex_lock_ex_symbol                             0x1D988
	#define mutex_trylock_symbol                             0x13628
	#define mutex_unlock_symbol                              0x13624

	#define cond_create_symbol                               0x13808
	#define cond_destroy_symbol                              0x137B8
	#define cond_wait_symbol                                 0x137B0
	#define cond_wait_ex_symbol                              0x1EF74
	#define cond_signal_symbol                               0x1378C
	#define cond_signal_all_symbol                           0x13768

	#define semaphore_initialize_symbol                      0x30A78
	#define semaphore_wait_ex_symbol                         0x30780
	#define semaphore_trywait_symbol                         0x30368
	#define semaphore_post_ex_symbol                         0x304B4

	#define event_port_create_symbol                         0x130D8
	#define event_port_destroy_symbol                        0x13540
	#define event_port_connect_symbol                        0x135B8
	#define event_port_disconnect_symbol                     0x134E4
	#define event_port_send_symbol                           0x130D0
	#define event_port_send_ex_symbol                        0x2B028

	#define event_queue_create_symbol                        0x133E0
	#define event_queue_destroy_symbol                       0x13368
	#define event_queue_receive_symbol                       0x131AC
	#define event_queue_tryreceive_symbol                    0x13278

	#define cellFsOpen_symbol                                0x29DFE8
	#define cellFsClose_symbol                               0x29DE50
	#define cellFsRead_symbol                                0x29DF8C
	#define cellFsWrite_symbol                               0x29DEF8
	#define cellFsLseek_symbol                               0x29D580
	#define cellFsStat_symbol                                0x29D804
	#define cellFsUtime_symbol                               0x29F2F0
	#define cellFsUnlink_internal_symbol                     0x19BFA4
	#define cellFsRename_internal_symbol                     0x196E84

	#define cellFsUtilMount_symbol                           0x29D360
	#define cellFsUtilUmount_symbol                          0x29D334
	#define cellFsUtilNewfs_symbol                           0x29ED88

	#define pathdup_from_user_symbol                         0x1A20DC
	#define open_path_symbol                                 0x2E9C48
	#define open_fs_object_symbol                            0x18A6DC
	#define close_fs_object_symbol                           0x189618

	#define storage_get_device_info_symbol                   0x281F58
	#define storage_get_device_config_symbol                 0x2813E8
	#define storage_open_symbol                              0x281968
	#define storage_close_symbol                             0x281758
	#define storage_read_symbol                              0x280CC8
	#define storage_write_symbol                             0x280B98
	#define storage_send_device_command_symbol               0x280854
	#define storage_map_io_memory_symbol                     0x281E14
	#define storage_unmap_io_memory_symbol                   0x281CE0
	#define new_medium_listener_object_symbol                0x95AEC
	#define delete_medium_listener_object_symbol             0x97324
	#define set_medium_event_callbacks_symbol                0x97688

	#define cellUsbdRegisterLdd_symbol                       0x268750
	#define cellUsbdUnregisterLdd_symbol                     0x268700
	#define cellUsbdScanStaticDescriptor_symbol              0x269950
	#define cellUsbdOpenPipe_symbol                          0x269A00
	#define cellUsbdClosePipe_symbol                         0x2699B0
	#define cellUsbdControlTransfer_symbol                   0x2698B4
	#define cellUsbdBulkTransfer_symbol                      0x269834

	#define decrypt_func_symbol                              0x34794
	#define lv1_call_99_wrapper_symbol                       0x4ECCC
	#define modules_verification_symbol                      0x58824
	#define authenticate_program_segment_symbol              0x59C60

	#define prx_load_module_symbol                           0x87230
	#define prx_start_module_symbol                          0x85EFC
	#define prx_stop_module_symbol                           0x872D4
	#define prx_unload_module_symbol                         0x85C30
	#define prx_get_module_info_symbol                       0x856B8
	#define prx_get_module_id_by_address_symbol              0x855C8
	#define prx_get_module_id_by_name_symbol                 0x85618
	#define prx_get_module_list_symbol                       0x85738
	#define load_module_by_fd_symbol                         0x86860
	#define parse_sprx_symbol                                0x845E4
	#define open_prx_object_symbol                           0x7DC04
	#define close_prx_object_symbol                          0x7E514
	#define lock_prx_mutex_symbol                            0x85570
	#define unlock_prx_mutex_symbol                          0x8557C

	#define extend_kstack_symbol                             0x6E7C0

	#define get_pseudo_random_number_symbol                  0x230930
	#define md5_reset_symbol                                 0x161B98
	#define md5_update_symbol                                0x162638
	#define md5_final_symbol                                 0x1627B8
	#define ss_get_open_psid_symbol                          0x232DD8
	#define update_mgr_read_eeprom_symbol                    0x22C43C
	#define update_mgr_write_eeprom_symbol                   0x22C384
	#define update_mgr_if_get_token_symbol                   0x22DDA0

	#define ss_params_get_update_status_symbol               0x508D8

	#define sm_get_temperature_symbol                        0x26BA7C
	#define sm_get_fan_policy_symbol                         0x26AE10
	#define sm_set_fan_policy_symbol                         0x26CC08
	#define sm_get_temperature_patch                         0xC694
	#define sm_get_fan_policy_patch                          0x9E28
	#define sm_set_fan_policy_patch                          0xA324

	#define SHA1_init_symbol                                 0x2CB820
	#define SHA1_update_symbol                               0x2CB880
	#define SHA1_final_symbol                                0x2CBA34
	#define aescbccfb_dec_symbol                             0x2C9D14
	#define aescbccfb_enc_symbol                             0x2C9AC4
	#define get_path_by_fd_symbol                            0x1A1978

	#define ECDSA_1                                          0x5921C
	#define ECDSA_2                                          0x2CEC40
	#define ECDSA_FLAG                                       0x46CE98
	#define sysmem_obj                                       0x46D050
	#define qa_eeprom_offset                                 0x48A2E

	#define syscall_table_symbol                             0x35F0D0
	#define syscall_call_offset                              0x27E05C

	#define read_bdvd0_symbol                                0x1AD04C
	#define read_bdvd1_symbol                                0x1AEC78
	#define read_bdvd2_symbol                                0x1BBE00

	#define storage_internal_get_device_object_symbol        0x28030C

	#define hid_mgr_read_usb_symbol                          0x102488
	#define hid_mgr_read_bt_symbol                           0xFC360

	#define bt_set_controller_info_internal_symbol           0xF03CC

	#define device_event_port_send_call                      0x28A4C4
	#define device_event_port_send_call_restore              0xC8CD84B

	#define ss_pid_call_1                                    0x21BC60

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7DAF8
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x870CC

	#define shutdown_copy_params_call                        0xAABC
	#define shutdown_copy_params_call_restore                0xB94F0048

	#define fsloop_open_call                                 0x29E180
	#define fsloop_close_call                                0x29E1D0
	#define fsloop_read_call                                 0x29E210

	#define shutdown_patch_offset                            0xAAA8
	#define module_sdk_version_patch_offset                  0x26F648
	#define module_add_parameter_to_parse_sprxpatch_offset   0x8693C

	#define user_thread_prio_patch                           0x20228
	#define user_thread_prio_patch2                          0x20238

	#define lic_patch                                        0x55D88
	#define lic_patch_restore                                0x48247A7D
	#define ode_patch                                        0x22FF38
	#define fix_80010009                                     0x59AF4
	#define fix_8001003D                                     0x560BC
	#define fix_8001003E                                     0x56180
	#define PATCH_JUMP                                       0x56134

	#define io_rtoc_entry_1                                 -0x1E8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x6688

	#define storage_rtoc_entry_1                             0x1DC8

	#define device_event_rtoc_entry_1                        0x2038

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x3670

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x24F2C
	#define permissions_exception2                           0xC356C
	#define permissions_exception3                           0x202FC

	#define patch_data1_offset                               0x3DE240
	#define patch_func2                                      0x591DC
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDB58D
	#define patch_func8_offset1                              0x55FE4
	#define patch_func8_offset2                              0x56144
	#define patch_func8_offset2_restore                      0x4821F8F5
	#define patch_func9_offset                               0x59B08
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x379230

	#define mmapper_flags_temp_patch                         0x6F694

	#define rsx_syscall_check                                0x7E3C
	#define unk_func2_unregister_service                     0x977B8
	#define unk_func3_unregister_service                     0x9C24C

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E0000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52C00000056000
	#define PS1_EMU_HASH                                     0xCC2850000009A000
	#define PS1_NETEMU_HASH                                  0xCC28B000000BD000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC28B00000340000
	#define BDP_BDVD_HASH                                    0xCC28700000404000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000041000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F470000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0xC02C70000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA440C

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4C40
	#define ps2tonet_size_patch                              0xC4C34
	#define vmode_patch_offset                               0x441F78
	#define psp_drm_patch1                                   0x240650
	#define psp_drm_patch2                                   0x2410F0
	#define psp_drm_patch3                                   0x240D2C
	#define psp_drm_patch4                                   0x241538
	#define psp_drm_patchA                                   0x24076C
	#define psp_drm_patchB                                   0x24100C
	#define psp_drm_patchC                                   0x2401A4
	#define psp_drm_patchD                                   0x240754
	#define psp_drm_patchE                                   0x240758
	#define psp_drm_patchF                                   0x241124
	#define psp_extra_drm_patch                              0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDD8F0
	#define app_home_offset                                  0x250A60

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x685CC

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23684
	#define ps_region_error_offset                           0x699C
	#define remote_play_offset                               0x609C
	#define ps2_nonbw_offset3                                0x16814

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6F4

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8F4

	/* nas_plugin */
	#define patch1_nas                                       0x2E9D4
	#define patch2_nas                                       0x2EB38
	#define patch3_nas                                       0x1F7EC

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F620
	#define pspemu_path_offset                               0x4B120
	#define psptrans_path_offset                             0x4B1B0

	/* download_plugin */
	#define elf_patch1_download                              0x428F8
	#define elf_patch2_download                              0x42900
	#define elf_patch3_download                              0x4D280
	#define elf_patch4_download                              0x4E0A0
	#define elf_patch5_download                              0x4E0C0
	#define elf_patch6_download                              0x4E190

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x7AF34
	#define elf_patch2_autodownload                          0x7AF3C

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x159F28
	#define bdp_cinavia1_patch                               0x159F54

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x10198
	#define psp_read_header                                  0x1111C
	#define psp_drm_patch5                                   0x10F40
	#define psp_drm_patch6                                   0x10F70
	#define psp_drm_patch7                                   0x10F88
	#define psp_drm_patch8                                   0x10F8C
	#define psp_drm_patch9                                   0x110CC
	#define psp_drm_patch11                                  0x110D0
	#define psp_drm_patch12                                  0x110E0
	#define psp_product_id_patch1                            0x111E0
	#define psp_product_id_patch3                            0x114B8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x8753C
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46D4
	#define psp_savedata_patch2                              0x46AC
	#define psp_savedata_patch3                              0x450C
	#define psp_savedata_patch4                              0x4544
	#define psp_savedata_patch5                              0x4558
	#define psp_savedata_patch6                              0x46C0

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                        0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH                 0xDE52C00000057000
	#define GAME_EXT_PLUGIN_REBUG_HASH                       0xCC2680000001E000
	#define dex_ps2_nonbw_offset                             0xDDD18
	#define dex_ps2_nonbw_offset2                            0x682F0
	#define dex_ps2_nonbw_offset3                            0x16B04
	#define dex_ps2tonet_patch                               0xCA18C
	#define dex_ps2tonet_size_patch                          0xCA180
	#define dex_vmode_patch_offset                           0x449B6C
	#define dex_psp_drm_patch1                               0x247E78
	#define dex_psp_drm_patch2                               0x248918
	#define dex_psp_drm_patch3                               0x248554
	#define dex_psp_drm_patch4                               0x248D60
	#define dex_psp_drm_patchA                               0x247F94
	#define dex_psp_drm_patchB                               0x248834
	#define dex_psp_drm_patchC                               0x2479CC
	#define dex_psp_drm_patchD                               0x247F7C
	#define dex_psp_drm_patchE                               0x247F80
	#define dex_psp_drm_patchF                               0x24894C
	#define dex_psp_extra_drm_patch                          0x0
#endif

#ifdef FIRMWARE_450D

	#define FIRMWARE_VERSION                                 0x450

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x8000000000402AB0ULL
		#define PS3MAPI_IDPS_2                               0x8000000000494F0CULL
		#define PS3MAPI_PSID                                 0x8000000000494F24ULL
	#endif
	#define FIRMWARE_DEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x36EC40

	#define create_kernel_object_symbol                      0x12658
	#define destroy_kernel_object_symbol                     0x11FBC
	#define destroy_shared_kernel_object_symbol              0x11930
	#define open_kernel_object_symbol                        0x12CA8
	#define open_shared_kernel_object_symbol                 0x12AB8
	#define close_kernel_object_handle_symbol                0x120D8

	#define alloc_symbol                                     0x66944
	#define dealloc_symbol                                   0x66D80
	#define copy_to_user_symbol                              0xFEA0
	#define copy_from_user_symbol                            0x100BC
	#define copy_to_process_symbol                           0xFF58
	#define copy_from_process_symbol                         0xFD68
	#define process_read_memory_symbol                       0x276CB0
	#define process_write_memory_symbol                      0x276B24
	#define page_allocate_symbol                             0x624B4
	#define page_free_symbol                                 0x61F18
	#define page_export_to_proc_symbol                       0x62650
	#define page_unexport_from_proc_symbol                   0x61E0C
	#define kernel_ea_to_lpar_addr_symbol                    0x723B8
	#define process_ea_to_lpar_addr_ex_symbol                0x79F58
	#define set_pte_symbol                                   0x604B0
	#define map_process_memory_symbol                        0x79A64
	#define panic_symbol                                     0x27D944

	#define memcpy_symbol                                    0x81124
	#define memset_symbol                                    0x50E38
	#define memcmp_symbol                                    0x50148
	#define memchr_symbol                                    0x500F8
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
	#define strrchr_symbol                                   0x5111C

	#define spin_lock_irqsave_ex_symbol                      0x27DB14
	#define spin_unlock_irqrestore_ex_symbol                 0x27DAE8

	#define create_process_common_symbol                     0x27A928
	#define create_process_base_symbol                       0x279FCC
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x27A728

	#define ppu_thread_create_symbol                         0x1465C
	#define ppu_thread_exit_symbol                           0x14714
	#define ppu_thread_join_symbol                           0x14768
	#define ppu_thread_delay_symbol                          0x2A50C
	#define create_kernel_thread_symbol                      0x265FC
	#define create_user_thread_symbol                        0x26D38
	#define create_user_thread2_symbol                       0x26B5C
	#define start_thread_symbol                              0x25694
	#define run_thread_symbol                                0x24E58
	#define self_threading_symbol                            0x27344
	#define register_thread_symbol                           0x27673C
	#define allocate_user_stack_symbol                       0x276F24
	#define deallocate_user_stack_symbol                     0x276E8C

	#define mutex_create_symbol                              0x13CEC
	#define mutex_destroy_symbol                             0x13C84
	#define mutex_lock_symbol                                0x13C7C
	#define mutex_lock_ex_symbol                             0x1F438
	#define mutex_trylock_symbol                             0x13C78
	#define mutex_unlock_symbol                              0x13C74

	#define cond_create_symbol                               0x13E58
	#define cond_destroy_symbol                              0x13E08
	#define cond_wait_symbol                                 0x13E00
	#define cond_wait_ex_symbol                              0x20A24
	#define cond_signal_symbol                               0x13DDC
	#define cond_signal_all_symbol                           0x13DB8

	#define semaphore_initialize_symbol                      0x34398
	#define semaphore_wait_ex_symbol                         0x340A0
	#define semaphore_trywait_symbol                         0x33C88
	#define semaphore_post_ex_symbol                         0x33DD4

	#define event_port_create_symbol                         0x13728
	#define event_port_destroy_symbol                        0x13B90
	#define event_port_connect_symbol                        0x13C08
	#define event_port_disconnect_symbol                     0x13B34
	#define event_port_send_symbol                           0x13720
	#define event_port_send_ex_symbol                        0x2D0EC

	#define event_queue_create_symbol                        0x13A30
	#define event_queue_destroy_symbol                       0x139B8
	#define event_queue_receive_symbol                       0x137FC
	#define event_queue_tryreceive_symbol                    0x138C8

	#define cellFsOpen_symbol                                0x2B84B0
	#define cellFsClose_symbol                               0x2B8318
	#define cellFsRead_symbol                                0x2B8454
	#define cellFsWrite_symbol                               0x2B83C0
	#define cellFsLseek_symbol                               0x2B7C14
	#define cellFsStat_symbol                                0x2B7CCC
	#define cellFsUtime_symbol                               0x2B963C
	#define cellFsUnlink_internal_symbol                     0x1A2330
	#define cellFsRename_internal_symbol                     0x19D210

	#define cellFsUtilMount_symbol                           0x2B7988
	#define cellFsUtilUmount_symbol                          0x2B795C
	#define cellFsUtilNewfs_symbol                           0x2B92D4

	#define pathdup_from_user_symbol                         0x1A858C
	#define open_path_symbol                                 0x2B81E8
	#define open_fs_object_symbol                            0x190A68
	#define close_fs_object_symbol                           0x18F9A4

	#define storage_get_device_info_symbol                   0x294E8C
	#define storage_get_device_config_symbol                 0x293518
	#define storage_open_symbol                              0x2950B4
	#define storage_close_symbol                             0x2938A0
	#define storage_read_symbol                              0x29281C
	#define storage_write_symbol                             0x2926EC
	#define storage_send_device_command_symbol               0x29233C
	#define storage_map_io_memory_symbol                     0x294D38
	#define storage_unmap_io_memory_symbol                   0x294BF4
	#define new_medium_listener_object_symbol                0x9B25C
	#define delete_medium_listener_object_symbol             0x9CA94
	#define set_medium_event_callbacks_symbol                0x9CDF8

	#define cellUsbdRegisterLdd_symbol                       0x26EC2C
	#define cellUsbdUnregisterLdd_symbol                     0x26EBDC
	#define cellUsbdScanStaticDescriptor_symbol              0x26FE2C
	#define cellUsbdOpenPipe_symbol                          0x26FEDC
	#define cellUsbdClosePipe_symbol                         0x26FE8C
	#define cellUsbdControlTransfer_symbol                   0x26FD90
	#define cellUsbdBulkTransfer_symbol                      0x26FD10

	#define decrypt_func_symbol                              0x380B4
	#define lv1_call_99_wrapper_symbol                       0x52674
	#define modules_verification_symbol                      0x5C1F4
	#define authenticate_program_segment_symbol              0x5D630

	#define prx_load_module_symbol                           0x8B934
	#define prx_start_module_symbol                          0x8A600
	#define prx_stop_module_symbol                           0x8B9D8
	#define prx_unload_module_symbol                         0x8A334
	#define prx_get_module_info_symbol                       0x89D2C
	#define prx_get_module_id_by_address_symbol              0x89C3C
	#define prx_get_module_id_by_name_symbol                 0x89C8C
	#define prx_get_module_list_symbol                       0x89DAC
	#define load_module_by_fd_symbol                         0x8AF64
	#define parse_sprx_symbol                                0x88C58
	#define open_prx_object_symbol                           0x81CE0
	#define close_prx_object_symbol                          0x825F0
	#define lock_prx_mutex_symbol                            0x89BE4
	#define unlock_prx_mutex_symbol                          0x89BF0

	#define extend_kstack_symbol                             0x72310

	#define get_pseudo_random_number_symbol                  0x236E0C
	#define md5_reset_symbol                                 0x167F24
	#define md5_update_symbol                                0x1689C4
	#define md5_final_symbol                                 0x168B44
	#define ss_get_open_psid_symbol                          0x2392B4
	#define update_mgr_read_eeprom_symbol                    0x232900
	#define update_mgr_write_eeprom_symbol                   0x232834
	#define update_mgr_if_get_token_symbol                   0x23427C

	#define ss_params_get_update_status_symbol               0x54280

	#define sm_get_temperature_symbol                        0x271F58
	#define sm_get_fan_policy_symbol                         0x2712EC
	#define sm_set_fan_policy_symbol                         0x2732B4
	#define sm_get_temperature_patch                         0xC714
	#define sm_get_fan_policy_patch                          0x9EA8
	#define sm_set_fan_policy_patch                          0xA3A4

	#define SHA1_init_symbol                                 0x2EB2DC
	#define SHA1_update_symbol                               0x2EB33C
	#define SHA1_final_symbol                                0x2EB4F0
	#define aescbccfb_dec_symbol                             0x2E97D0
	#define aescbccfb_enc_symbol                             0x2E9580
	#define get_path_by_fd_symbol                            0x1A7E28

	#define ECDSA_1                                          0x5CBEC
	#define ECDSA_2                                          0x2EE6FC
	#define ECDSA_FLAG                                       0x494E98
	#define sysmem_obj                                       0x495050
	#define qa_eeprom_offset                                 0x4C392

	#define syscall_table_symbol                             0x383658
	#define syscall_call_offset                              0x286370

	#define read_bdvd0_symbol                                0x1B34FC
	#define read_bdvd1_symbol                                0x1B5128
	#define read_bdvd2_symbol                                0x1C22B0

	#define storage_internal_get_device_object_symbol        0x291DF4

	#define hid_mgr_read_usb_symbol                          0x107F8C
	#define hid_mgr_read_bt_symbol                           0x101E64

	#define bt_set_controller_info_internal_symbol           0xF5ED0

	#define device_event_port_send_call                      0x29F088
	#define device_event_port_send_call_restore              0x9846D74B

	#define ss_pid_call_1                                    0x222110

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x81BD4
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x8B7D0

	#define shutdown_copy_params_call                        0xAB3C
	#define shutdown_copy_params_call_restore                0x81550048

	#define fsloop_open_call                                 0x2B8648
	#define fsloop_close_call                                0x2B8698
	#define fsloop_read_call                                 0x2B86D8

	#define shutdown_patch_offset                            0xAB28
	#define module_sdk_version_patch_offset                  0x275D64
	#define module_add_parameter_to_parse_sprxpatch_offset   0x8B040

	#define user_thread_prio_patch                           0x21CD8
	#define user_thread_prio_patch2                          0x21CE8

	#define lic_patch                                        0x59758
	#define lic_patch_restore                                0x4825E575
	#define ode_patch                                        0x236414
	#define fix_80010009                                     0x5D4C4
	#define fix_8001003D                                     0x59A8C
	#define fix_8001003E                                     0x59B50
	#define PATCH_JUMP                                       0x59B04

	#define io_rtoc_entry_1                                 -0xB8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65A8

	#define storage_rtoc_entry_1                             0x22A0

	#define device_event_rtoc_entry_1                        0x2628

	#define time_rtoc_entry_1                               -0x75E0
	#define time_rtoc_entry_2                               -0x75E8

	#define thread_rtoc_entry_1                             -0x7660

	#define process_rtoc_entry_1                            -0x77A0

	#define bt_rtoc_entry_1                                 -0x3548

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x26BDC
	#define permissions_exception2                           0xC8CDC
	#define permissions_exception3                           0x21DAC

	#define patch_data1_offset                               0x402AC0
	#define patch_func2                                      0x5CBAC
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDB4DD
	#define patch_func8_offset1                              0x599B4
	#define patch_func8_offset2                              0x59B14
	#define patch_func8_offset2_restore                      0x48223E31
	#define patch_func9_offset                               0x5D4D8
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x39DAB0

	#define mmapper_flags_temp_patch                         0x73324

	#define rsx_syscall_check                                0x7E3C
	#define unk_func2_unregister_service                     0x9CF28
	#define unk_func3_unregister_service                     0xA19BC

	/* lv1 */
	#define vsh_pos_in_ram                                   0x520000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E4000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52C00000057000
	#define PS1_EMU_HASH                                     0xCC2850000009A000
	#define PS1_NETEMU_HASH                                  0xCC28B000000BD000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC28B00000340000
	#define BDP_BDVD_HASH                                    0xCC28700000404000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000041000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F480000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0xC02C70000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA440C

	/* vsh */
	#define vsh_text_size                                    0x6C0000
	#define ps2tonet_patch                                   0xCA18C
	#define ps2tonet_size_patch                              0xCA180
	#define vmode_patch_offset                               0x449B6C
	#define psp_drm_patch1                                   0x247E78
	#define psp_drm_patch2                                   0x248918
	#define psp_drm_patch3                                   0x248554
	#define psp_drm_patch4                                   0x248D60
	#define psp_drm_patchA                                   0x247F94
	#define psp_drm_patchB                                   0x248834
	#define psp_drm_patchC                                   0x2479CC
	#define psp_drm_patchD                                   0x247F7C
	#define psp_drm_patchE                                   0x247F80
	#define psp_drm_patchF                                   0x24894C
	#define psp_extra_drm_patch                              0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDDD18
	#define app_home_offset                                  0x2516A0

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x682F0

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x238A0
	#define ps_region_error_offset                           0x6958
	#define remote_play_offset                               0x609C
	#define ps2_nonbw_offset3                                0x16B04

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6F4

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8F4

	/* nas_plugin */
	#define patch1_nas                                       0x2EDF4
	#define patch2_nas                                       0x2EF58
	#define patch3_nas                                       0x1FAAC

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x200C8
	#define pspemu_path_offset                               0x4C318
	#define psptrans_path_offset                             0x4C3D0

	/* download_plugin */
	#define elf_patch1_download                              0x4288C
	#define elf_patch2_download                              0x42894
	#define elf_patch3_download                              0x4D190
	#define elf_patch4_download                              0x4DFB0
	#define elf_patch5_download                              0x4DFD0
	#define elf_patch6_download                              0x4E0A0

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x7ADE4
	#define elf_patch2_autodownload                          0x7ADEC

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x159F28
	#define bdp_cinavia1_patch                               0x159F54

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x10198
	#define psp_read_header                                  0x1111C
	#define psp_drm_patch5                                   0x10F40
	#define psp_drm_patch6                                   0x10F70
	#define psp_drm_patch7                                   0x10F88
	#define psp_drm_patch8                                   0x10F8C
	#define psp_drm_patch9                                   0x110CC
	#define psp_drm_patch11                                  0x110D0
	#define psp_drm_patch12                                  0x110E0
	#define psp_product_id_patch1                            0x111E0
	#define psp_product_id_patch3                            0x114B8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x8753C
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46D4
	#define psp_savedata_patch2                              0x46AC
	#define psp_savedata_patch3                              0x450C
	#define psp_savedata_patch4                              0x4544
	#define psp_savedata_patch5                              0x4558
	#define psp_savedata_patch6                              0x46C0

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* CEX */
	#define cex_ps2tonet_patch                               0xC4C40
	#define cex_ps2tonet_size_patch                          0xC4C34
	#define cex_vmode_patch_offset                           0x441F78
	#define cex_psp_drm_patch1                               0x240650
	#define cex_psp_drm_patch2                               0x2410F0
	#define cex_psp_drm_patch3                               0x240D2C
	#define cex_psp_drm_patch4                               0x241538
	#define cex_psp_drm_patchA                               0x24076C
	#define cex_psp_drm_patchB                               0x24100C
	#define cex_psp_drm_patchC                               0x2401A4
	#define cex_psp_drm_patchD                               0x240754
	#define cex_psp_drm_patchE                               0x240758
	#define cex_psp_drm_patchF                               0x241124
	#define cex_psp_extra_drm_patch                          0x0
#endif

#ifdef FIRMWARE_453C

	#define FIRMWARE_VERSION                                 0x453

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003DE430ULL
		#define PS3MAPI_IDPS_2                               0x800000000046CF0CULL
		#define PS3MAPI_PSID                                 0x800000000046CF24ULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x34B2E0

	#define create_kernel_object_symbol                      0x12014
	#define destroy_kernel_object_symbol                     0x11978
	#define destroy_shared_kernel_object_symbol              0x112EC
	#define open_kernel_object_symbol                        0x12664
	#define open_shared_kernel_object_symbol                 0x12474
	#define close_kernel_object_handle_symbol                0x11A94

	#define alloc_symbol                                     0x62F78
	#define dealloc_symbol                                   0x633B4
	#define copy_to_user_symbol                              0xF85C
	#define copy_from_user_symbol                            0xFA78
	#define copy_to_process_symbol                           0xF914
	#define copy_from_process_symbol                         0xF724
	#define process_read_memory_symbol                       0x270564
	#define process_write_memory_symbol                      0x2703D8
	#define page_allocate_symbol                             0x5EAE8
	#define page_free_symbol                                 0x5E54C
	#define page_export_to_proc_symbol                       0x5EC84
	#define page_unexport_from_proc_symbol                   0x5E440
	#define kernel_ea_to_lpar_addr_symbol                    0x6E86C
	#define process_ea_to_lpar_addr_ex_symbol                0x75E80
	#define set_pte_symbol                                   0x5CAE4
	#define map_process_memory_symbol                        0x7598C
	#define panic_symbol                                     0x275C10

	#define memcpy_symbol                                    0x7D04C
	#define memset_symbol                                    0x4D494
	#define memcmp_symbol                                    0x4C7A4
	#define memchr_symbol                                    0x4C754
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
	#define strrchr_symbol                                   0x4D778

	#define spin_lock_irqsave_ex_symbol                      0x275DE0
	#define spin_unlock_irqrestore_ex_symbol                 0x275DB4

	#define create_process_common_symbol                     0x273BD8
	#define create_process_base_symbol                       0x273294
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x2739E4

	#define ppu_thread_create_symbol                         0x13F2C
	#define ppu_thread_exit_symbol                           0x13FE4
	#define ppu_thread_join_symbol                           0x14038
	#define ppu_thread_delay_symbol                          0x285CC
	#define create_kernel_thread_symbol                      0x24950
	#define create_user_thread_symbol                        0x2508C
	#define create_user_thread2_symbol                       0x24EB0
	#define start_thread_symbol                              0x23B7C
	#define run_thread_symbol                                0x233AC
	#define self_threading_symbol                            0x25698
	#define register_thread_symbol                           0x26FFF0
	#define allocate_user_stack_symbol                       0x2707D8
	#define deallocate_user_stack_symbol                     0x270740

	#define mutex_create_symbol                              0x136A0
	#define mutex_destroy_symbol                             0x13638
	#define mutex_lock_symbol                                0x13630
	#define mutex_lock_ex_symbol                             0x1D98C
	#define mutex_trylock_symbol                             0x1362C
	#define mutex_unlock_symbol                              0x13628

	#define cond_create_symbol                               0x1380C
	#define cond_destroy_symbol                              0x137BC
	#define cond_wait_symbol                                 0x137B4
	#define cond_wait_ex_symbol                              0x1EF78
	#define cond_signal_symbol                               0x13790
	#define cond_signal_all_symbol                           0x1376C

	#define semaphore_initialize_symbol                      0x30A7C
	#define semaphore_wait_ex_symbol                         0x30784
	#define semaphore_trywait_symbol                         0x3036C
	#define semaphore_post_ex_symbol                         0x304B8

	#define event_port_create_symbol                         0x130DC
	#define event_port_destroy_symbol                        0x13544
	#define event_port_connect_symbol                        0x135BC
	#define event_port_disconnect_symbol                     0x134E8
	#define event_port_send_symbol                           0x130D4
	#define event_port_send_ex_symbol                        0x2B02C

	#define event_queue_create_symbol                        0x133E4
	#define event_queue_destroy_symbol                       0x1336C
	#define event_queue_receive_symbol                       0x131B0
	#define event_queue_tryreceive_symbol                    0x1327C

	#define cellFsOpen_symbol                                0x29E1C0
	#define cellFsClose_symbol                               0x29E028
	#define cellFsRead_symbol                                0x29E164
	#define cellFsWrite_symbol                               0x29E0D0
	#define cellFsLseek_symbol                               0x29D758
	#define cellFsStat_symbol                                0x29D9DC
	#define cellFsUtime_symbol                               0x29F4C8
	#define cellFsUnlink_internal_symbol                     0x19C350
	#define cellFsRename_internal_symbol                     0x196E6C

	#define cellFsUtilMount_symbol                           0x29D538
	#define cellFsUtilUmount_symbol                          0x29D50C
	#define cellFsUtilNewfs_symbol                           0x29EF60

	#define pathdup_from_user_symbol                         0x1A2244
	#define open_path_symbol                                 0x29DEF8
	#define open_fs_object_symbol                            0x18A6F0
	#define close_fs_object_symbol                           0x18962C

	#define storage_get_device_info_symbol                   0x282130
	#define storage_get_device_config_symbol                 0x2815C0
	#define storage_open_symbol                              0x281B40
	#define storage_close_symbol                             0x281930
	#define storage_read_symbol                              0x280EA0
	#define storage_write_symbol                             0x280D70
	#define storage_send_device_command_symbol               0x280A2C
	#define storage_map_io_memory_symbol                     0x281FEC
	#define storage_unmap_io_memory_symbol                   0x281EB8
	#define new_medium_listener_object_symbol                0x95AF4
	#define delete_medium_listener_object_symbol             0x9732C
	#define set_medium_event_callbacks_symbol                0x97690

	#define cellUsbdRegisterLdd_symbol                       0x268924
	#define cellUsbdUnregisterLdd_symbol                     0x2688D4
	#define cellUsbdScanStaticDescriptor_symbol              0x269B24
	#define cellUsbdOpenPipe_symbol                          0x269BD4
	#define cellUsbdClosePipe_symbol                         0x269B84
	#define cellUsbdControlTransfer_symbol                   0x269A88
	#define cellUsbdBulkTransfer_symbol                      0x269A08

	#define decrypt_func_symbol                              0x34798
	#define lv1_call_99_wrapper_symbol                       0x4ECD0
	#define modules_verification_symbol                      0x58828
	#define authenticate_program_segment_symbol              0x59C64

	#define prx_load_module_symbol                           0x87234
	#define prx_start_module_symbol                          0x85F00
	#define prx_stop_module_symbol                           0x872D8
	#define prx_unload_module_symbol                         0x85C34
	#define prx_get_module_info_symbol                       0x856BC
	#define prx_get_module_id_by_address_symbol              0x855CC
	#define prx_get_module_id_by_name_symbol                 0x8561C
	#define prx_get_module_list_symbol                       0x8573C
	#define load_module_by_fd_symbol                         0x86864
	#define parse_sprx_symbol                                0x845E8
	#define open_prx_object_symbol                           0x7DC08
	#define close_prx_object_symbol                          0x7E518
	#define lock_prx_mutex_symbol                            0x85574
	#define unlock_prx_mutex_symbol                          0x85580

	#define extend_kstack_symbol                             0x6E7C4

	#define get_pseudo_random_number_symbol                  0x230B04
	#define md5_reset_symbol                                 0x161BA0
	#define md5_update_symbol                                0x162640
	#define md5_final_symbol                                 0x1627C0
	#define ss_get_open_psid_symbol                          0x232FAC
	#define update_mgr_read_eeprom_symbol                    0x22C610
	#define update_mgr_write_eeprom_symbol                   0x22C558
	#define update_mgr_if_get_token_symbol                   0x22DF74

	#define ss_params_get_update_status_symbol               0x508DC

	#define sm_get_temperature_symbol                        0x26BC50
	#define sm_get_fan_policy_symbol                         0x26AFE4
	#define sm_set_fan_policy_symbol                         0x26CDDC
	#define sm_get_temperature_patch                         0xC698
	#define sm_get_fan_policy_patch                          0x9E28
	#define sm_set_fan_policy_patch                          0xA324

	#define SHA1_init_symbol                                 0x2CB9B0
	#define SHA1_update_symbol                               0x2CBA10
	#define SHA1_final_symbol                                0x2CBBC4
	#define aescbccfb_dec_symbol                             0x2C9EA4
	#define aescbccfb_enc_symbol                             0x2C9C54
	#define get_path_by_fd_symbol                            0x1A1AE0

	#define ECDSA_1                                          0x59220
	#define ECDSA_2                                          0x2CEDD0
	#define ECDSA_FLAG                                       0x46CE98
	#define sysmem_obj                                       0x46D050
	#define qa_eeprom_offset                                 0x48A32

	#define syscall_table_symbol                             0x35F300
	#define syscall_call_offset                              0x27E234

	#define read_bdvd0_symbol                                0x1AD1B4
	#define read_bdvd1_symbol                                0x1AEDE0
	#define read_bdvd2_symbol                                0x1BBF98

	#define storage_internal_get_device_object_symbol        0x2804E4

	#define hid_mgr_read_usb_symbol                          0x102490
	#define hid_mgr_read_bt_symbol                           0xFC368

	#define bt_set_controller_info_internal_symbol           0xF03D4

	#define device_event_port_send_call                      0x28A69C
	#define device_event_port_send_call_restore              0x5C632748

	#define ss_pid_call_1                                    0x21BE34

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7DAFC
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x870D0

	#define shutdown_copy_params_call                        0xAABC
	#define shutdown_copy_params_call_restore                0xF5644F48

	#define fsloop_open_call                                 0x29E358
	#define fsloop_close_call                                0x29E3A8
	#define fsloop_read_call                                 0x29E3E8

	#define shutdown_patch_offset                            0xAAA8
	#define module_sdk_version_patch_offset                  0x26F820
	#define module_add_parameter_to_parse_sprxpatch_offset   0x86940

	#define user_thread_prio_patch                           0x2022C
	#define user_thread_prio_patch2                          0x2023C

	#define lic_patch                                        0x55D8C
	#define lic_patch_restore                                0x48247C51
	#define ode_patch                                        0x23010C
	#define fix_80010009                                     0x59AF8
	#define fix_8001003D                                     0x560C0
	#define fix_8001003E                                     0x56184
	#define PATCH_JUMP                                       0x56138

	#define io_rtoc_entry_1                                 -0x1E8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x6688

	#define storage_rtoc_entry_1                             0x1DC8

	#define device_event_rtoc_entry_1                        0x2038

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x3670

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x24F30
	#define permissions_exception2                           0xC3574
	#define permissions_exception3                           0x20300

	#define patch_data1_offset                               0x3DE440
	#define patch_func2                                      0x591E0
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x484A71A5
	#define patch_func8_offset1                              0x55FE8
	#define patch_func8_offset2                              0x56148
	#define patch_func8_offset2_restore                      0x48216FB5
	#define patch_func9_offset                               0x59B0C
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x379430

	#define mmapper_flags_temp_patch                         0x6F698

	#define rsx_syscall_check                                0x5012F8
	#define unk_func2_unregister_service                     0x977C0
	#define unk_func3_unregister_service                     0x9C254

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E1000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52C00000056000
	#define PS1_EMU_HASH                                     0xCC2850000009A000
	#define PS1_NETEMU_HASH                                  0xCC28B000000BD000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC28700000351000
	#define BDP_BDVD_HASH                                    0xCC28D00000436000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000041000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F470000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0xC02C70000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA440C

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4C5C
	#define ps2tonet_size_patch                              0xC4C50
	#define vmode_patch_offset                               0x4422FC
	#define psp_drm_patch1                                   0x24071C
	#define psp_drm_patch2                                   0x2411BC
	#define psp_drm_patch3                                   0x240DF8
	#define psp_drm_patch4                                   0x241604
	#define psp_drm_patchA                                   0x240838
	#define psp_drm_patchB                                   0x2410D8
	#define psp_drm_patchC                                   0x240270
	#define psp_drm_patchD                                   0x240820
	#define psp_drm_patchE                                   0x240824
	#define psp_drm_patchF                                   0x2411F0
	#define psp_extra_drm_patch                              0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDD754
	#define app_home_offset                                  0x2508C8

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68430

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x236C4
	#define ps_region_error_offset                           0x69D0
	#define remote_play_offset                               0x60D0
	#define ps2_nonbw_offset3                                0x16850

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6F4

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8F4

	/* nas_plugin */
	#define patch1_nas                                       0x2E9FC
	#define patch2_nas                                       0x2EB60
	#define patch3_nas                                       0x1F7F4

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F620
	#define pspemu_path_offset                               0x4B120
	#define psptrans_path_offset                             0x4B1B0

	/* download_plugin */
	#define elf_patch1_download                              0x428A4
	#define elf_patch2_download                              0x428AC
	#define elf_patch3_download                              0x4D1E8
	#define elf_patch4_download                              0x4E008
	#define elf_patch5_download                              0x4E028
	#define elf_patch6_download                              0x4E0F8

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x79E34
	#define elf_patch2_autodownload                          0x79E3C

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x8753C
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46D4
	#define psp_savedata_patch2                              0x46AC
	#define psp_savedata_patch3                              0x450C
	#define psp_savedata_patch4                              0x4544
	#define psp_savedata_patch5                              0x4558
	#define psp_savedata_patch6                              0x46C0

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                        0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH                 0xDE52C00000056000
	#define GAME_EXT_PLUGIN_REBUG_HASH                       0xCC2680000001E000
	#define dex_ps2_nonbw_offset                             0xDD6D0
	#define dex_ps2_nonbw_offset2                            0x68244
	#define dex_ps2_nonbw_offset3                            0x16B40
	#define dex_ps2tonet_patch                               0xCA1A8
	#define dex_ps2tonet_size_patch                          0xCA19C
	#define dex_vmode_patch_offset                           0x449EF0
	#define dex_psp_drm_patch1                               0x247F44
	#define dex_psp_drm_patch2                               0x2489E4
	#define dex_psp_drm_patch3                               0x248620
	#define dex_psp_drm_patch4                               0x248E2C
	#define dex_psp_drm_patchA                               0x248060
	#define dex_psp_drm_patchB                               0x248900
	#define dex_psp_drm_patchC                               0x247A98
	#define dex_psp_drm_patchD                               0x248048
	#define dex_psp_drm_patchE                               0x24804C
	#define dex_psp_drm_patchF                               0x248A18
	#define dex_psp_extra_drm_patch                          0x0
#endif

#ifdef FIRMWARE_453D

	#define FIRMWARE_VERSION                                 0x453

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000004045B0ULL
		#define PS3MAPI_IDPS_2                               0x8000000000494F0CULL
		#define PS3MAPI_PSID                                 0x8000000000494F24ULL
	#endif
	#define FIRMWARE_DEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x370620

	#define create_kernel_object_symbol                      0x1265C
	#define destroy_kernel_object_symbol                     0x11FC0
	#define destroy_shared_kernel_object_symbol              0x11934
	#define open_kernel_object_symbol                        0x12CAC
	#define open_shared_kernel_object_symbol                 0x12ABC
	#define close_kernel_object_handle_symbol                0x120DC

	#define alloc_symbol                                     0x66948
	#define dealloc_symbol                                   0x66D84
	#define copy_to_user_symbol                              0xFEA4
	#define copy_from_user_symbol                            0x100C0
	#define copy_to_process_symbol                           0xFF5C
	#define copy_from_process_symbol                         0xFD6C
	#define process_read_memory_symbol                       0x276E88
	#define process_write_memory_symbol                      0x276CFC
	#define page_allocate_symbol                             0x624B8
	#define page_free_symbol                                 0x61F1C
	#define page_export_to_proc_symbol                       0x62654
	#define page_unexport_from_proc_symbol                   0x61E10
	#define kernel_ea_to_lpar_addr_symbol                    0x723BC
	#define process_ea_to_lpar_addr_ex_symbol                0x79F5C
	#define set_pte_symbol                                   0x604B4
	#define map_process_memory_symbol                        0x79A68
	#define panic_symbol                                     0x27DB1C

	#define memcpy_symbol                                    0x81128
	#define memset_symbol                                    0x50E3C
	#define memcmp_symbol                                    0x5014C
	#define memchr_symbol                                    0x500FC
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
	#define strrchr_symbol                                   0x51120

	#define spin_lock_irqsave_ex_symbol                      0x27DCEC
	#define spin_unlock_irqrestore_ex_symbol                 0x27DCC0

	#define create_process_common_symbol                     0x27AB00
	#define create_process_base_symbol                       0x27A1A4
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x27A900

	#define ppu_thread_create_symbol                         0x14660
	#define ppu_thread_exit_symbol                           0x14718
	#define ppu_thread_join_symbol                           0x1476C
	#define ppu_thread_delay_symbol                          0x2A510
	#define create_kernel_thread_symbol                      0x26600
	#define create_user_thread_symbol                        0x26D3C
	#define create_user_thread2_symbol                       0x26B60
	#define start_thread_symbol                              0x25698
	#define run_thread_symbol                                0x24E5C
	#define self_threading_symbol                            0x27348
	#define register_thread_symbol                           0x276914
	#define allocate_user_stack_symbol                       0x2770FC
	#define deallocate_user_stack_symbol                     0x277064

	#define mutex_create_symbol                              0x13CF0
	#define mutex_destroy_symbol                             0x13C88
	#define mutex_lock_symbol                                0x13C80
	#define mutex_lock_ex_symbol                             0x1F43C
	#define mutex_trylock_symbol                             0x13C7C
	#define mutex_unlock_symbol                              0x13C78

	#define cond_create_symbol                               0x13E5C
	#define cond_destroy_symbol                              0x13E0C
	#define cond_wait_symbol                                 0x13E04
	#define cond_wait_ex_symbol                              0x20A28
	#define cond_signal_symbol                               0x13DE0
	#define cond_signal_all_symbol                           0x13DBC

	#define semaphore_initialize_symbol                      0x3439C
	#define semaphore_wait_ex_symbol                         0x340A4
	#define semaphore_trywait_symbol                         0x33C8C
	#define semaphore_post_ex_symbol                         0x33DD8

	#define event_port_create_symbol                         0x1372C
	#define event_port_destroy_symbol                        0x13B94
	#define event_port_connect_symbol                        0x13C0C
	#define event_port_disconnect_symbol                     0x13B38
	#define event_port_send_symbol                           0x13724
	#define event_port_send_ex_symbol                        0x2D0F0

	#define event_queue_create_symbol                        0x13A34
	#define event_queue_destroy_symbol                       0x139BC
	#define event_queue_receive_symbol                       0x13800
	#define event_queue_tryreceive_symbol                    0x138CC

	#define cellFsOpen_symbol                                0x2B8688
	#define cellFsClose_symbol                               0x2B84F0
	#define cellFsRead_symbol                                0x2B862C
	#define cellFsWrite_symbol                               0x2B8598
	#define cellFsLseek_symbol                               0x2B7DEC
	#define cellFsStat_symbol                                0x2B7EA4
	#define cellFsUtime_symbol                               0x2B9814
	#define cellFsUnlink_internal_symbol                     0x1A26DC
	#define cellFsRename_internal_symbol                     0x19D1F8

	#define cellFsUtilMount_symbol                           0x2B7B60
	#define cellFsUtilUmount_symbol                          0x2B7B34
	#define cellFsUtilNewfs_symbol                           0x2B94AC

	#define pathdup_from_user_symbol                         0x1A86F4
	#define open_path_symbol                                 0x2B83C0
	#define open_fs_object_symbol                            0x190A7C
	#define close_fs_object_symbol                           0x18F9B8

	#define storage_get_device_info_symbol                   0x295064
	#define storage_get_device_config_symbol                 0x2936F0
	#define storage_open_symbol                              0x29528C
	#define storage_close_symbol                             0x293A78
	#define storage_read_symbol                              0x2929F4
	#define storage_write_symbol                             0x2928C4
	#define storage_send_device_command_symbol               0x292514
	#define storage_map_io_memory_symbol                     0x294F10
	#define storage_unmap_io_memory_symbol                   0x294DCC
	#define new_medium_listener_object_symbol                0x9B264
	#define delete_medium_listener_object_symbol             0x9CA9C
	#define set_medium_event_callbacks_symbol                0x9CE00

	#define cellUsbdRegisterLdd_symbol                       0x26EE00
	#define cellUsbdUnregisterLdd_symbol                     0x26EDB0
	#define cellUsbdScanStaticDescriptor_symbol              0x270000
	#define cellUsbdOpenPipe_symbol                          0x2700B0
	#define cellUsbdClosePipe_symbol                         0x270060
	#define cellUsbdControlTransfer_symbol                   0x26FF64
	#define cellUsbdBulkTransfer_symbol                      0x26FEE4

	#define decrypt_func_symbol                              0x380B8
	#define lv1_call_99_wrapper_symbol                       0x52678
	#define modules_verification_symbol                      0x5C1F8
	#define authenticate_program_segment_symbol              0x5D634

	#define prx_load_module_symbol                           0x8B938
	#define prx_start_module_symbol                          0x8A604
	#define prx_stop_module_symbol                           0x8B9DC
	#define prx_unload_module_symbol                         0x8A338
	#define prx_get_module_info_symbol                       0x89D30
	#define prx_get_module_id_by_address_symbol              0x89C40
	#define prx_get_module_id_by_name_symbol                 0x89C90
	#define prx_get_module_list_symbol                       0x89DB0
	#define load_module_by_fd_symbol                         0x8AF68
	#define parse_sprx_symbol                                0x88C5C
	#define open_prx_object_symbol                           0x81CE4
	#define close_prx_object_symbol                          0x825F4
	#define lock_prx_mutex_symbol                            0x89BE8
	#define unlock_prx_mutex_symbol                          0x89BF4

	#define extend_kstack_symbol                             0x72314

	#define get_pseudo_random_number_symbol                  0x236FE0
	#define md5_reset_symbol                                 0x167F2C
	#define md5_update_symbol                                0x1689CC
	#define md5_final_symbol                                 0x168B4C
	#define ss_get_open_psid_symbol                          0x239488
	#define update_mgr_read_eeprom_symbol                    0x232AD4
	#define update_mgr_write_eeprom_symbol                   0x232A08
	#define update_mgr_if_get_token_symbol                   0x234450

	#define ss_params_get_update_status_symbol               0x54284

	#define sm_get_temperature_symbol                        0x27212C
	#define sm_get_fan_policy_symbol                         0x2714C0
	#define sm_set_fan_policy_symbol                         0x273488
	#define sm_get_temperature_patch                         0xC718
	#define sm_get_fan_policy_patch                          0x9EA8
	#define sm_set_fan_policy_patch                          0xA3A4

	#define SHA1_init_symbol                                 0x2ECAF0
	#define SHA1_update_symbol                               0x2ECB50
	#define SHA1_final_symbol                                0x2ECD04
	#define aescbccfb_dec_symbol                             0x2EAFE4
	#define aescbccfb_enc_symbol                             0x2EAD94
	#define get_path_by_fd_symbol                            0x1A7F90

	#define ECDSA_1                                          0x5CBF0
	#define ECDSA_2                                          0x2EFF10
	#define ECDSA_FLAG                                       0x494E98
	#define sysmem_obj                                       0x495050
	#define qa_eeprom_offset                                 0x4C396

	#define syscall_table_symbol                             0x385108
	#define syscall_call_offset                              0x286548

	#define read_bdvd0_symbol                                0x1B3664
	#define read_bdvd1_symbol                                0x1B5290
	#define read_bdvd2_symbol                                0x1C2448

	#define storage_internal_get_device_object_symbol        0x291FCC

	#define hid_mgr_read_usb_symbol                          0x107F94
	#define hid_mgr_read_bt_symbol                           0x101E6C

	#define bt_set_controller_info_internal_symbol           0xF5ED8

	#define device_event_port_send_call                      0x29F260
	#define device_event_port_send_call_restore              0x98172A48

	#define ss_pid_call_1                                    0x2222E4

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x81BD8
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x8B7D4

	#define shutdown_copy_params_call                        0xAB3C
	#define shutdown_copy_params_call_restore                0x75645348

	#define fsloop_open_call                                 0x2B8820
	#define fsloop_close_call                                0x2B8870
	#define fsloop_read_call                                 0x2B88B0

	#define shutdown_patch_offset                            0xAB28
	#define module_sdk_version_patch_offset                  0x275F3C
	#define module_add_parameter_to_parse_sprxpatch_offset   0x8B044

	#define user_thread_prio_patch                           0x21CDC
	#define user_thread_prio_patch2                          0x21CEC

	#define lic_patch                                        0x5975C
	#define lic_patch_restore                                0x4825E749
	#define ode_patch                                        0x2365E8
	#define fix_80010009                                     0x5D4C8
	#define fix_8001003D                                     0x59A90
	#define fix_8001003E                                     0x59B54
	#define PATCH_JUMP                                       0x59B08

	#define io_rtoc_entry_1                                 -0xB8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65A8

	#define storage_rtoc_entry_1                             0x22A0

	#define device_event_rtoc_entry_1                        0x2628

	#define time_rtoc_entry_1                               -0x75E0
	#define time_rtoc_entry_2                               -0x75E8

	#define thread_rtoc_entry_1                             -0x7660

	#define process_rtoc_entry_1                            -0x77A0

	#define bt_rtoc_entry_1                                 -0x3548

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x26BE0
	#define permissions_exception2                           0xC8CE4
	#define permissions_exception3                           0x21DB0

	#define patch_data1_offset                               0x4045C0
	#define patch_func2                                      0x5CBB0
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x484E37D5
	#define patch_func8_offset1                              0x599B8
	#define patch_func8_offset2                              0x59B18
	#define patch_func8_offset2_restore                      0x4821B4BD
	#define patch_func9_offset                               0x5D4DC
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x39F5B0

	#define mmapper_flags_temp_patch                         0x73328

	#define rsx_syscall_check                                0x5412F8
	#define unk_func2_unregister_service                     0x9CF30
	#define unk_func3_unregister_service                     0xA19C4

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E4000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52C00000056000
	#define PS1_EMU_HASH                                     0xCC2850000009A000
	#define PS1_NETEMU_HASH                                  0xCC28B000000BD000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC28700000351000
	#define BDP_BDVD_HASH                                    0xCC28D00000436000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000020000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000041000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F480000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0xC02C70000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA440C

	/* vsh */
	#define vsh_text_size                                    0x6C0000
	#define ps2tonet_patch                                   0xCA1A8
	#define ps2tonet_size_patch                              0xCA19C
	#define vmode_patch_offset                               0x449EF0
	#define psp_drm_patch1                                   0x247F44
	#define psp_drm_patch2                                   0x2489E4
	#define psp_drm_patch3                                   0x248620
	#define psp_drm_patch4                                   0x248E2C
	#define psp_drm_patchA                                   0x248060
	#define psp_drm_patchB                                   0x248900
	#define psp_drm_patchC                                   0x247A98
	#define psp_drm_patchD                                   0x248048
	#define psp_drm_patchE                                   0x24804C
	#define psp_drm_patchF                                   0x248A18
	#define psp_extra_drm_patch                              0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDD6D0
	#define app_home_offset                                  0x251438

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68244

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x238E0
	#define ps_region_error_offset                           0x698C
	#define remote_play_offset                               0x60D0
	#define ps2_nonbw_offset3                                0x16B40

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6F4

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8F4

	/* nas_plugin */
	#define patch1_nas                                       0x2EE14
	#define patch2_nas                                       0x2EF78
	#define patch3_nas                                       0x1FAAC

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x200C8
	#define pspemu_path_offset                               0x4C318
	#define psptrans_path_offset                             0x4C3D0

	/* download_plugin */
	#define elf_patch1_download                              0x42838
	#define elf_patch2_download                              0x42840
	#define elf_patch3_download                              0x4D108
	#define elf_patch4_download                              0x4DF28
	#define elf_patch5_download                              0x4DF48
	#define elf_patch6_download                              0x4E018

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x79CE4
	#define elf_patch2_autodownload                          0x79CEC

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x8753C
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46D4
	#define psp_savedata_patch2                              0x46AC
	#define psp_savedata_patch3                              0x450C
	#define psp_savedata_patch4                              0x4544
	#define psp_savedata_patch5                              0x4558
	#define psp_savedata_patch6                              0x46C0

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* CEX */
	#define cex_ps2tonet_patch                               0xC4C5C
	#define cex_ps2tonet_size_patch                          0xC4C50
	#define cex_vmode_patch_offset                           0x4422FC
	#define cex_psp_drm_patch1                               0x24071C
	#define cex_psp_drm_patch2                               0x2411BC
	#define cex_psp_drm_patch3                               0x240DF8
	#define cex_psp_drm_patch4                               0x241604
	#define cex_psp_drm_patchA                               0x240838
	#define cex_psp_drm_patchB                               0x2410D8
	#define cex_psp_drm_patchC                               0x240270
	#define cex_psp_drm_patchD                               0x240820
	#define cex_psp_drm_patchE                               0x240824
	#define cex_psp_drm_patchF                               0x2411F0
	#define cex_psp_extra_drm_patch                          0x0
#endif

#ifdef FIRMWARE_455C

	#define FIRMWARE_VERSION                                 0x455

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E17B0ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474F1CULL
		#define PS3MAPI_PSID                                 0x8000000000474F34ULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x34E620

	#define create_kernel_object_symbol                      0x12024
	#define destroy_kernel_object_symbol                     0x11988
	#define destroy_shared_kernel_object_symbol              0x112FC
	#define open_kernel_object_symbol                        0x12674
	#define open_shared_kernel_object_symbol                 0x12484
	#define close_kernel_object_handle_symbol                0x11AA4

	#define alloc_symbol                                     0x643B4
	#define dealloc_symbol                                   0x647F0
	#define copy_to_user_symbol                              0xF86C
	#define copy_from_user_symbol                            0xFA88
	#define copy_to_process_symbol                           0xF924
	#define copy_from_process_symbol                         0xF734
	#define process_read_memory_symbol                       0x271DB0
	#define process_write_memory_symbol                      0x271C24
	#define page_allocate_symbol                             0x5FF24
	#define page_free_symbol                                 0x5F988
	#define page_export_to_proc_symbol                       0x600C0
	#define page_unexport_from_proc_symbol                   0x5F87C
	#define kernel_ea_to_lpar_addr_symbol                    0x6FCA8
	#define process_ea_to_lpar_addr_ex_symbol                0x772BC
	#define set_pte_symbol                                   0x5DF20
	#define map_process_memory_symbol                        0x76DC8
	#define panic_symbol                                     0x277460

	#define memcpy_symbol                                    0x7E488
	#define memset_symbol                                    0x4D6D8
	#define memcmp_symbol                                    0x4C9E8
	#define memchr_symbol                                    0x4C998
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
	#define strrchr_symbol                                   0x4D9BC

	#define spin_lock_irqsave_ex_symbol                      0x277630
	#define spin_unlock_irqrestore_ex_symbol                 0x277604

	#define create_process_common_symbol                     0x275430
	#define create_process_base_symbol                       0x274AE0
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x27523C

	#define ppu_thread_create_symbol                         0x13F3C
	#define ppu_thread_exit_symbol                           0x13FF4
	#define ppu_thread_join_symbol                           0x14048
	#define ppu_thread_delay_symbol                          0x28810
	#define create_kernel_thread_symbol                      0x24B94
	#define create_user_thread_symbol                        0x252D0
	#define create_user_thread2_symbol                       0x250F4
	#define start_thread_symbol                              0x23DC0
	#define run_thread_symbol                                0x235F0
	#define self_threading_symbol                            0x258DC
	#define register_thread_symbol                           0x27183C
	#define allocate_user_stack_symbol                       0x272024
	#define deallocate_user_stack_symbol                     0x271F8C

	#define mutex_create_symbol                              0x136B0
	#define mutex_destroy_symbol                             0x13648
	#define mutex_lock_symbol                                0x13640
	#define mutex_lock_ex_symbol                             0x1DBD0
	#define mutex_trylock_symbol                             0x1363C
	#define mutex_unlock_symbol                              0x13638

	#define cond_create_symbol                               0x1381C
	#define cond_destroy_symbol                              0x137CC
	#define cond_wait_symbol                                 0x137C4
	#define cond_wait_ex_symbol                              0x1F1BC
	#define cond_signal_symbol                               0x137A0
	#define cond_signal_all_symbol                           0x1377C

	#define semaphore_initialize_symbol                      0x30CC0
	#define semaphore_wait_ex_symbol                         0x309C8
	#define semaphore_trywait_symbol                         0x305B0
	#define semaphore_post_ex_symbol                         0x306FC

	#define event_port_create_symbol                         0x130EC
	#define event_port_destroy_symbol                        0x13554
	#define event_port_connect_symbol                        0x135CC
	#define event_port_disconnect_symbol                     0x134F8
	#define event_port_send_symbol                           0x130E4
	#define event_port_send_ex_symbol                        0x2B270

	#define event_queue_create_symbol                        0x133F4
	#define event_queue_destroy_symbol                       0x1337C
	#define event_queue_receive_symbol                       0x131C0
	#define event_queue_tryreceive_symbol                    0x1328C

	#define cellFsOpen_symbol                                0x29FA10
	#define cellFsClose_symbol                               0x29F878
	#define cellFsRead_symbol                                0x29F9B4
	#define cellFsWrite_symbol                               0x29F920
	#define cellFsLseek_symbol                               0x29EFA8
	#define cellFsStat_symbol                                0x29F22C
	#define cellFsUtime_symbol                               0x2A0D18
	#define cellFsUnlink_internal_symbol                     0x19D83C
	#define cellFsRename_internal_symbol                     0x1982F4

	#define cellFsUtilMount_symbol                           0x29ED88
	#define cellFsUtilUmount_symbol                          0x29ED5C
	#define cellFsUtilNewfs_symbol                           0x2A07B0

	#define pathdup_from_user_symbol                         0x1A3730
	#define open_path_symbol                                 0x29F748
	#define open_fs_object_symbol                            0x18BB60
	#define close_fs_object_symbol                           0x18AA9C

	#define storage_get_device_info_symbol                   0x283980
	#define storage_get_device_config_symbol                 0x282E10
	#define storage_open_symbol                              0x283390
	#define storage_close_symbol                             0x283180
	#define storage_read_symbol                              0x2826F0
	#define storage_write_symbol                             0x2825C0
	#define storage_send_device_command_symbol               0x28227C
	#define storage_map_io_memory_symbol                     0x28383C
	#define storage_unmap_io_memory_symbol                   0x283708
	#define new_medium_listener_object_symbol                0x96F40
	#define delete_medium_listener_object_symbol             0x98778
	#define set_medium_event_callbacks_symbol                0x98ADC

	#define cellUsbdRegisterLdd_symbol                       0x26A16C
	#define cellUsbdUnregisterLdd_symbol                     0x26A11C
	#define cellUsbdScanStaticDescriptor_symbol              0x26B36C
	#define cellUsbdOpenPipe_symbol                          0x26B41C
	#define cellUsbdClosePipe_symbol                         0x26B3CC
	#define cellUsbdControlTransfer_symbol                   0x26B2D0
	#define cellUsbdBulkTransfer_symbol                      0x26B250

	#define decrypt_func_symbol                              0x349DC
	#define lv1_call_99_wrapper_symbol                       0x4EF14
	#define modules_verification_symbol                      0x586E8
	#define authenticate_program_segment_symbol              0x5A51C

	#define prx_load_module_symbol                           0x88680
	#define prx_start_module_symbol                          0x8734C
	#define prx_stop_module_symbol                           0x88724
	#define prx_unload_module_symbol                         0x87080
	#define prx_get_module_info_symbol                       0x86B08
	#define prx_get_module_id_by_address_symbol              0x86A18
	#define prx_get_module_id_by_name_symbol                 0x86A68
	#define prx_get_module_list_symbol                       0x86B88
	#define load_module_by_fd_symbol                         0x87CB0
	#define parse_sprx_symbol                                0x85A34
	#define open_prx_object_symbol                           0x7F054
	#define close_prx_object_symbol                          0x7F964
	#define lock_prx_mutex_symbol                            0x869C0
	#define unlock_prx_mutex_symbol                          0x869CC

	#define extend_kstack_symbol                             0x6FC00

	#define get_pseudo_random_number_symbol                  0x2321D4
	#define md5_reset_symbol                                 0x163004
	#define md5_update_symbol                                0x163AA4
	#define md5_final_symbol                                 0x163C24
	#define ss_get_open_psid_symbol                          0x2346BC
	#define update_mgr_read_eeprom_symbol                    0x22DACC
	#define update_mgr_write_eeprom_symbol                   0x22DA14
	#define update_mgr_if_get_token_symbol                   0x22F430

	#define ss_params_get_update_status_symbol               0x50B20

	#define sm_get_temperature_symbol                        0x26D498
	#define sm_get_fan_policy_symbol                         0x26C82C
	#define sm_set_fan_policy_symbol                         0x26E624
	#define sm_get_temperature_patch                         0xC6A8
	#define sm_get_fan_policy_patch                          0x9E38
	#define sm_set_fan_policy_patch                          0xA334

	#define SHA1_init_symbol                                 0x2CD1F8
	#define SHA1_update_symbol                               0x2CD258
	#define SHA1_final_symbol                                0x2CD40C
	#define aescbccfb_dec_symbol                             0x2CB6EC
	#define aescbccfb_enc_symbol                             0x2CB49C
	#define get_path_by_fd_symbol                            0x1A2FCC

	#define ECDSA_1                                          0x599D0
	#define ECDSA_2                                          0x2D16A4
	#define ECDSA_FLAG                                       0x474EA8
	#define sysmem_obj                                       0x475060
	#define qa_eeprom_offset                                 0x48C76

	#define syscall_table_symbol                             0x362680
	#define syscall_call_offset                              0x27FA84

	#define read_bdvd0_symbol                                0x1AE6A0
	#define read_bdvd1_symbol                                0x1B02CC
	#define read_bdvd2_symbol                                0x1BD454

	#define storage_internal_get_device_object_symbol        0x281D34

	#define hid_mgr_read_usb_symbol                          0x1038F4
	#define hid_mgr_read_bt_symbol                           0xFD7CC

	#define bt_set_controller_info_internal_symbol           0xF1838

	#define device_event_port_send_call                      0x28BEEC
	#define device_event_port_send_call_restore              0xC4B2748

	#define ss_pid_call_1                                    0x21D2F0

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7EF48
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x8851C

	#define shutdown_copy_params_call                        0xAACC
	#define shutdown_copy_params_call_restore                0xE5644F48

	#define fsloop_open_call                                 0x29FBA8
	#define fsloop_close_call                                0x29FBF8
	#define fsloop_read_call                                 0x29FC38

	#define shutdown_patch_offset                            0xAAB8
	#define module_sdk_version_patch_offset                  0x27106C
	#define module_add_parameter_to_parse_sprxpatch_offset   0x87D8C

	#define user_thread_prio_patch                           0x20470
	#define user_thread_prio_patch2                          0x20480

	#define lic_patch                                        0x56024
	#define lic_patch_restore                                0x48249209
	#define ode_patch                                        0x231648
	#define fix_80010009                                     0x5A2F0
	#define fix_8001003D                                     0x56380
	#define fix_8001003E                                     0x56444
	#define PATCH_JUMP                                       0x563F8

	#define io_rtoc_entry_1                                 -0x1B8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A8

	#define storage_rtoc_entry_1                             0x1E10

	#define device_event_rtoc_entry_1                        0x2080

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x3640

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x25174
	#define permissions_exception2                           0xC49D8
	#define permissions_exception3                           0x20544

	#define patch_data1_offset                               0x3E17C0
	#define patch_func2                                      0x59990
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x484A69F5
	#define patch_func8_offset1                              0x562A8
	#define patch_func8_offset2                              0x56408
	#define patch_func8_offset2_restore                      0x48216FB5
	#define patch_func9_offset                               0x5A304
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x37C7B0

	#define mmapper_flags_temp_patch                         0x70AD4

	#define rsx_syscall_check                                0x5012F8
	#define unk_func2_unregister_service                     0x98C0C
	#define unk_func3_unregister_service                     0x9D6A0

	/* lv1 */
	#define vsh_pos_in_ram                                   0x840000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E1000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52C00000056000
	#define PS1_EMU_HASH                                     0xCC2850000009A000
	#define PS1_NETEMU_HASH                                  0xCC28B000000BD000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC28700000351000
	#define BDP_BDVD_HASH                                    0xCC28D00000436000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000041000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F470000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0xC02C70000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA440C

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4C5C
	#define ps2tonet_size_patch                              0xC4C50
	#define vmode_patch_offset                               0x4430E8
	#define psp_drm_patch1                                   0x24071C
	#define psp_drm_patch2                                   0x2411BC
	#define psp_drm_patch3                                   0x240DF8
	#define psp_drm_patch4                                   0x241604
	#define psp_drm_patchA                                   0x240838
	#define psp_drm_patchB                                   0x2410D8
	#define psp_drm_patchC                                   0x240270
	#define psp_drm_patchD                                   0x240820
	#define psp_drm_patchE                                   0x240824
	#define psp_drm_patchF                                   0x2411F0
	#define psp_extra_drm_patch                              0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDD754
	#define app_home_offset                                  0x2508C8

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68430

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x236C4
	#define ps_region_error_offset                           0x69D0
	#define remote_play_offset                               0x60D0
	#define ps2_nonbw_offset3                                0x16850

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6F4

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8F4

	/* nas_plugin */
	#define patch1_nas                                       0x2E9FC
	#define patch2_nas                                       0x2EB60
	#define patch3_nas                                       0x1F7F4

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F620
	#define pspemu_path_offset                               0x4B120
	#define psptrans_path_offset                             0x4B1B0

	/* download_plugin */
	#define elf_patch1_download                              0x428A4
	#define elf_patch2_download                              0x428AC
	#define elf_patch3_download                              0x4D1E8
	#define elf_patch4_download                              0x4E008
	#define elf_patch5_download                              0x4E028
	#define elf_patch6_download                              0x4E0F8

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x79E34
	#define elf_patch2_autodownload                          0x79E3C

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x8753C
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46D4
	#define psp_savedata_patch2                              0x46AC
	#define psp_savedata_patch3                              0x450C
	#define psp_savedata_patch4                              0x4544
	#define psp_savedata_patch5                              0x4558
	#define psp_savedata_patch6                              0x46C0

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                        0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH                 0xDE52C00000056000
	#define GAME_EXT_PLUGIN_REBUG_HASH                       0xCC2680000001E000
	#define dex_ps2_nonbw_offset                             0xDD6D0
	#define dex_ps2_nonbw_offset2                            0x68244
	#define dex_ps2_nonbw_offset3                            0x16B40
	#define dex_ps2tonet_patch                               0xCA1A8
	#define dex_ps2tonet_size_patch                          0xCA19C
	#define dex_vmode_patch_offset                           0x44ACDC
	#define dex_psp_drm_patch1                               0x247F44
	#define dex_psp_drm_patch2                               0x2489E4
	#define dex_psp_drm_patch3                               0x248620
	#define dex_psp_drm_patch4                               0x248E2C
	#define dex_psp_drm_patchA                               0x248060
	#define dex_psp_drm_patchB                               0x248900
	#define dex_psp_drm_patchC                               0x247A98
	#define dex_psp_drm_patchD                               0x248048
	#define dex_psp_drm_patchE                               0x24804C
	#define dex_psp_drm_patchF                               0x248A18
	#define dex_psp_extra_drm_patch                          0x0
#endif

#ifdef FIRMWARE_455D

	#define FIRMWARE_VERSION                                 0x455

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x8000000000407930ULL
		#define PS3MAPI_IDPS_2                               0x8000000000494F1CULL
		#define PS3MAPI_PSID                                 0x8000000000494F34ULL
	#endif
	#define FIRMWARE_DEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x3738E0

	#define create_kernel_object_symbol                      0x1266C
	#define destroy_kernel_object_symbol                     0x11FD0
	#define destroy_shared_kernel_object_symbol              0x11944
	#define open_kernel_object_symbol                        0x12CBC
	#define open_shared_kernel_object_symbol                 0x12ACC
	#define close_kernel_object_handle_symbol                0x120EC

	#define alloc_symbol                                     0x67D84
	#define dealloc_symbol                                   0x681C0
	#define copy_to_user_symbol                              0xFEB4
	#define copy_from_user_symbol                            0x100D0
	#define copy_to_process_symbol                           0xFF6C
	#define copy_from_process_symbol                         0xFD7C
	#define process_read_memory_symbol                       0x2786D4
	#define process_write_memory_symbol                      0x278548
	#define page_allocate_symbol                             0x638F4
	#define page_free_symbol                                 0x63358
	#define page_export_to_proc_symbol                       0x63A90
	#define page_unexport_from_proc_symbol                   0x6324C
	#define kernel_ea_to_lpar_addr_symbol                    0x737F8
	#define process_ea_to_lpar_addr_ex_symbol                0x7B398
	#define set_pte_symbol                                   0x618F0
	#define map_process_memory_symbol                        0x7AEA4
	#define panic_symbol                                     0x27F374

	#define memcpy_symbol                                    0x82564
	#define memset_symbol                                    0x51080
	#define memcmp_symbol                                    0x50390
	#define memchr_symbol                                    0x50340
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
	#define strrchr_symbol                                   0x51364

	#define spin_lock_irqsave_ex_symbol                      0x27F544
	#define spin_unlock_irqrestore_ex_symbol                 0x27F518

	#define create_process_common_symbol                     0x27C358
	#define create_process_base_symbol                       0x27B9F0
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x27C158

	#define ppu_thread_create_symbol                         0x14670
	#define ppu_thread_exit_symbol                           0x14728
	#define ppu_thread_join_symbol                           0x1477C
	#define ppu_thread_delay_symbol                          0x2A754
	#define create_kernel_thread_symbol                      0x26844
	#define create_user_thread_symbol                        0x26F80
	#define create_user_thread2_symbol                       0x26DA4
	#define start_thread_symbol                              0x258DC
	#define run_thread_symbol                                0x250A0
	#define self_threading_symbol                            0x2758C
	#define register_thread_symbol                           0x278160
	#define allocate_user_stack_symbol                       0x278948
	#define deallocate_user_stack_symbol                     0x2788B0

	#define mutex_create_symbol                              0x13D00
	#define mutex_destroy_symbol                             0x13C98
	#define mutex_lock_symbol                                0x13C90
	#define mutex_lock_ex_symbol                             0x1F680
	#define mutex_trylock_symbol                             0x13C8C
	#define mutex_unlock_symbol                              0x13C88

	#define cond_create_symbol                               0x13E6C
	#define cond_destroy_symbol                              0x13E1C
	#define cond_wait_symbol                                 0x13E14
	#define cond_wait_ex_symbol                              0x20C6C
	#define cond_signal_symbol                               0x13DF0
	#define cond_signal_all_symbol                           0x13DCC

	#define semaphore_initialize_symbol                      0x345E0
	#define semaphore_wait_ex_symbol                         0x342E8
	#define semaphore_trywait_symbol                         0x33ED0
	#define semaphore_post_ex_symbol                         0x3401C

	#define event_port_create_symbol                         0x1373C
	#define event_port_destroy_symbol                        0x13BA4
	#define event_port_connect_symbol                        0x13C1C
	#define event_port_disconnect_symbol                     0x13B48
	#define event_port_send_symbol                           0x13734
	#define event_port_send_ex_symbol                        0x2D334

	#define event_queue_create_symbol                        0x13A44
	#define event_queue_destroy_symbol                       0x139CC
	#define event_queue_receive_symbol                       0x13810
	#define event_queue_tryreceive_symbol                    0x138DC

	#define cellFsOpen_symbol                                0x2B9EDC
	#define cellFsClose_symbol                               0x2B9D44
	#define cellFsRead_symbol                                0x2B9E80
	#define cellFsWrite_symbol                               0x2B9DEC
	#define cellFsLseek_symbol                               0x2B9640
	#define cellFsStat_symbol                                0x2B96F8
	#define cellFsUtime_symbol                               0x2BB068
	#define cellFsUnlink_internal_symbol                     0x1A3BC8
	#define cellFsRename_internal_symbol                     0x19E680

	#define cellFsUtilMount_symbol                           0x2B93B4
	#define cellFsUtilUmount_symbol                          0x2B9388
	#define cellFsUtilNewfs_symbol                           0x2BAD00

	#define pathdup_from_user_symbol                         0x1A9BE0
	#define open_path_symbol                                 0x2B9C14
	#define open_fs_object_symbol                            0x191EEC
	#define close_fs_object_symbol                           0x190E28

	#define storage_get_device_info_symbol                   0x2968BC
	#define storage_get_device_config_symbol                 0x294F48
	#define storage_open_symbol                              0x296AE4
	#define storage_close_symbol                             0x2952D0
	#define storage_read_symbol                              0x29424C
	#define storage_write_symbol                             0x29411C
	#define storage_send_device_command_symbol               0x293D6C
	#define storage_map_io_memory_symbol                     0x296768
	#define storage_unmap_io_memory_symbol                   0x296624
	#define new_medium_listener_object_symbol                0x9C6B0
	#define delete_medium_listener_object_symbol             0x9DEE8
	#define set_medium_event_callbacks_symbol                0x9E24C

	#define cellUsbdRegisterLdd_symbol                       0x270648
	#define cellUsbdUnregisterLdd_symbol                     0x2705F8
	#define cellUsbdScanStaticDescriptor_symbol              0x271848
	#define cellUsbdOpenPipe_symbol                          0x2718F8
	#define cellUsbdClosePipe_symbol                         0x2718A8
	#define cellUsbdControlTransfer_symbol                   0x2717AC
	#define cellUsbdBulkTransfer_symbol                      0x27172C

	#define decrypt_func_symbol                              0x382FC
	#define lv1_call_99_wrapper_symbol                       0x528BC
	#define modules_verification_symbol                      0x5C0B8
	#define authenticate_program_segment_symbol              0x5DEEC

	#define prx_load_module_symbol                           0x8CD84
	#define prx_start_module_symbol                          0x8BA50
	#define prx_stop_module_symbol                           0x8CE28
	#define prx_unload_module_symbol                         0x8B784
	#define prx_get_module_info_symbol                       0x8B17C
	#define prx_get_module_id_by_address_symbol              0x8B08C
	#define prx_get_module_id_by_name_symbol                 0x8B0DC
	#define prx_get_module_list_symbol                       0x8B1FC
	#define load_module_by_fd_symbol                         0x8C3B4
	#define parse_sprx_symbol                                0x8A0A8
	#define open_prx_object_symbol                           0x83130
	#define close_prx_object_symbol                          0x83A40
	#define lock_prx_mutex_symbol                            0x8B034
	#define unlock_prx_mutex_symbol                          0x8B040

	#define extend_kstack_symbol                             0x73750

	#define get_pseudo_random_number_symbol                  0x2386B0
	#define md5_reset_symbol                                 0x169390
	#define md5_update_symbol                                0x169E30
	#define md5_final_symbol                                 0x169FB0
	#define ss_get_open_psid_symbol                          0x23AB98
	#define update_mgr_read_eeprom_symbol                    0x233F90
	#define update_mgr_write_eeprom_symbol                   0x233EC4
	#define update_mgr_if_get_token_symbol                   0x23590C

	#define ss_params_get_update_status_symbol               0x544C8

	#define sm_get_temperature_symbol                        0x273974
	#define sm_get_fan_policy_symbol                         0x272D08
	#define sm_set_fan_policy_symbol                         0x274CD0
	#define sm_get_temperature_patch                         0xC728
	#define sm_get_fan_policy_patch                          0x9EB8
	#define sm_set_fan_policy_patch                          0xA3B4

	#define SHA1_init_symbol                                 0x2EE2CC
	#define SHA1_update_symbol                               0x2EE32C
	#define SHA1_final_symbol                                0x2EE4E0
	#define aescbccfb_dec_symbol                             0x2EC7C0
	#define aescbccfb_enc_symbol                             0x2EC570
	#define get_path_by_fd_symbol                            0x1A947C

	#define ECDSA_1                                          0x5D3A0
	#define ECDSA_2                                          0x2F2778
	#define ECDSA_FLAG                                       0x494EA8
	#define sysmem_obj                                       0x495060
	#define qa_eeprom_offset                                 0x4C5DA

	#define syscall_table_symbol                             0x388488
	#define syscall_call_offset                              0x287DA0

	#define read_bdvd0_symbol                                0x1B4B50
	#define read_bdvd1_symbol                                0x1B677C
	#define read_bdvd2_symbol                                0x1C3904

	#define storage_internal_get_device_object_symbol        0x293824

	#define hid_mgr_read_usb_symbol                          0x1093F8
	#define hid_mgr_read_bt_symbol                           0x1032D0

	#define bt_set_controller_info_internal_symbol           0xF733C

	#define device_event_port_send_call                      0x2A0AB8
	#define device_event_port_send_call_restore              0x7C2CD74B

	#define ss_pid_call_1                                    0x2237A0

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x83024
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x8CC20

	#define shutdown_copy_params_call                        0xAB4C
	#define shutdown_copy_params_call_restore                0x85550048

	#define fsloop_open_call                                 0x2BA074
	#define fsloop_close_call                                0x2BA0C4
	#define fsloop_read_call                                 0x2BA104

	#define shutdown_patch_offset                            0xAB38
	#define module_sdk_version_patch_offset                  0x277788
	#define module_add_parameter_to_parse_sprxpatch_offset   0x8C490

	#define user_thread_prio_patch                           0x21F20
	#define user_thread_prio_patch2                          0x21F30

	#define lic_patch                                        0x599F4
	#define lic_patch_restore                                0x4825FD05
	#define ode_patch                                        0x237B24
	#define fix_80010009                                     0x5DCC0
	#define fix_8001003D                                     0x59D50
	#define fix_8001003E                                     0x59E14
	#define PATCH_JUMP                                       0x59DC8

	#define io_rtoc_entry_1                                 -0x88
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65C8

	#define storage_rtoc_entry_1                             0x22E8

	#define device_event_rtoc_entry_1                        0x2670

	#define time_rtoc_entry_1                               -0x75E0
	#define time_rtoc_entry_2                               -0x75E8

	#define thread_rtoc_entry_1                             -0x7660

	#define process_rtoc_entry_1                            -0x77A0

	#define bt_rtoc_entry_1                                 -0x3518

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x26E24
	#define permissions_exception2                           0xCA148
	#define permissions_exception3                           0x21FF4

	#define patch_data1_offset                               0x407940
	#define patch_func2                                      0x5D360
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDAF71
	#define patch_func8_offset1                              0x59C78
	#define patch_func8_offset2                              0x59DD8
	#define patch_func8_offset2_restore                      0x4822559D
	#define patch_func9_offset                               0x5DCD4
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x3A2930

	#define mmapper_flags_temp_patch                         0x74764

	#define rsx_syscall_check                                0x7E4C
	#define unk_func2_unregister_service                     0x9E37C
	#define unk_func3_unregister_service                     0xA2E10

	/* lv1 */
	#define vsh_pos_in_ram                                   0x840000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E4000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52C00000056000
	#define PS1_EMU_HASH                                     0xCC2850000009A000
	#define PS1_NETEMU_HASH                                  0xCC28B000000BD000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC28700000351000
	#define BDP_BDVD_HASH                                    0xCC28D00000436000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000020000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000041000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F480000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0xC02C70000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA440C

	/* vsh */
	#define vsh_text_size                                    0x6C0000
	#define ps2tonet_patch                                   0xCA1A8
	#define ps2tonet_size_patch                              0xCA19C
	#define vmode_patch_offset                               0x44ACDC
	#define psp_drm_patch1                                   0x247F44
	#define psp_drm_patch2                                   0x2489E4
	#define psp_drm_patch3                                   0x248620
	#define psp_drm_patch4                                   0x248E2C
	#define psp_drm_patchA                                   0x248060
	#define psp_drm_patchB                                   0x248900
	#define psp_drm_patchC                                   0x247A98
	#define psp_drm_patchD                                   0x248048
	#define psp_drm_patchE                                   0x24804C
	#define psp_drm_patchF                                   0x248A18
	#define psp_extra_drm_patch                              0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDD6D0
	#define app_home_offset                                  0x251438

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68244

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x238E0
	#define ps_region_error_offset                           0x698C
	#define remote_play_offset                               0x60D0
	#define ps2_nonbw_offset3                                0x16B40

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6F4

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8F4

	/* nas_plugin */
	#define patch1_nas                                       0x2EE14
	#define patch2_nas                                       0x2EF78
	#define patch3_nas                                       0x1FAAC

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x200C8
	#define pspemu_path_offset                               0x4C318
	#define psptrans_path_offset                             0x4C3D0

	/* download_plugin */
	#define elf_patch1_download                              0x42838
	#define elf_patch2_download                              0x42840
	#define elf_patch3_download                              0x4D108
	#define elf_patch4_download                              0x4DF28
	#define elf_patch5_download                              0x4DF48
	#define elf_patch6_download                              0x4E018

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x79CE4
	#define elf_patch2_autodownload                          0x79CEC

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x8753C
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27580 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46D4
	#define psp_savedata_patch2                              0x46AC
	#define psp_savedata_patch3                              0x450C
	#define psp_savedata_patch4                              0x4544
	#define psp_savedata_patch5                              0x4558
	#define psp_savedata_patch6                              0x46C0

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* CEX */
	#define cex_ps2tonet_patch                               0xC4C5C
	#define cex_ps2tonet_size_patch                          0xC4C50
	#define cex_vmode_patch_offset                           0x4430E8
	#define cex_psp_drm_patch1                               0x24071C
	#define cex_psp_drm_patch2                               0x2411BC
	#define cex_psp_drm_patch3                               0x240DF8
	#define cex_psp_drm_patch4                               0x241604
	#define cex_psp_drm_patchA                               0x240838
	#define cex_psp_drm_patchB                               0x2410D8
	#define cex_psp_drm_patchC                               0x240270
	#define cex_psp_drm_patchD                               0x240820
	#define cex_psp_drm_patchE                               0x240824
	#define cex_psp_drm_patchF                               0x2411F0
	#define cex_psp_extra_drm_patch                          0x0
#endif

#ifdef FIRMWARE_460C

	#define FIRMWARE_VERSION                                 0x460

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2BB0ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474F1CULL
		#define PS3MAPI_PSID                                 0x8000000000474F34ULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x34F950

	#define create_kernel_object_symbol                      0x11FAC
	#define destroy_kernel_object_symbol                     0x11910
	#define destroy_shared_kernel_object_symbol              0x11284
	#define open_kernel_object_symbol                        0x125FC
	#define open_shared_kernel_object_symbol                 0x1240C
	#define close_kernel_object_handle_symbol                0x11A2C

	#define alloc_symbol                                     0x64798
	#define dealloc_symbol                                   0x64BD4
	#define copy_to_user_symbol                              0xF868
	#define copy_from_user_symbol                            0xFA84
	#define copy_to_process_symbol                           0xF920
	#define copy_from_process_symbol                         0xF730
	#define process_read_memory_symbol                       0x270B44
	#define process_write_memory_symbol                      0x2709B8
	#define page_allocate_symbol                             0x60308
	#define page_free_symbol                                 0x5FD6C
	#define page_export_to_proc_symbol                       0x604A4
	#define page_unexport_from_proc_symbol                   0x5FC60
	#define kernel_ea_to_lpar_addr_symbol                    0x700C0
	#define process_ea_to_lpar_addr_ex_symbol                0x776D4
	#define set_pte_symbol                                   0x5E304
	#define map_process_memory_symbol                        0x771E0
	#define panic_symbol                                     0x27624C

	#define memcpy_symbol                                    0x7E8A0
	#define memset_symbol                                    0x4D668
	#define memcmp_symbol                                    0x4C978
	#define memchr_symbol                                    0x4C928
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
	#define strrchr_symbol                                   0x4D94C

	#define spin_lock_irqsave_ex_symbol                      0x27641C
	#define spin_unlock_irqrestore_ex_symbol                 0x2763F0

	#define create_process_common_symbol                     0x2741B8
	#define create_process_base_symbol                       0x273874
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x273FC4

	#define ppu_thread_create_symbol                         0x13EC4
	#define ppu_thread_exit_symbol                           0x13F7C
	#define ppu_thread_join_symbol                           0x13FD0
	#define ppu_thread_delay_symbol                          0x287A0
	#define create_kernel_thread_symbol                      0x24B1C
	#define create_user_thread_symbol                        0x25258
	#define create_user_thread2_symbol                       0x2507C
	#define start_thread_symbol                              0x23D48
	#define run_thread_symbol                                0x23578
	#define self_threading_symbol                            0x25864
	#define register_thread_symbol                           0x2705D0
	#define allocate_user_stack_symbol                       0x270DB8
	#define deallocate_user_stack_symbol                     0x270D20

	#define mutex_create_symbol                              0x13638
	#define mutex_destroy_symbol                             0x135D0
	#define mutex_lock_symbol                                0x135C8
	#define mutex_lock_ex_symbol                             0x1DB58
	#define mutex_trylock_symbol                             0x135C4
	#define mutex_unlock_symbol                              0x135C0

	#define cond_create_symbol                               0x137A4
	#define cond_destroy_symbol                              0x13754
	#define cond_wait_symbol                                 0x1374C
	#define cond_wait_ex_symbol                              0x1F144
	#define cond_signal_symbol                               0x13728
	#define cond_signal_all_symbol                           0x13704

	#define semaphore_initialize_symbol                      0x30C50
	#define semaphore_wait_ex_symbol                         0x30958
	#define semaphore_trywait_symbol                         0x30540
	#define semaphore_post_ex_symbol                         0x3068C

	#define event_port_create_symbol                         0x13074
	#define event_port_destroy_symbol                        0x134DC
	#define event_port_connect_symbol                        0x13554
	#define event_port_disconnect_symbol                     0x13480
	#define event_port_send_symbol                           0x1306C
	#define event_port_send_ex_symbol                        0x2B200

	#define event_queue_create_symbol                        0x1337C
	#define event_queue_destroy_symbol                       0x13304
	#define event_queue_receive_symbol                       0x13148
	#define event_queue_tryreceive_symbol                    0x13214

	#define cellFsOpen_symbol                                0x2A0584
	#define cellFsClose_symbol                               0x2A03EC
	#define cellFsRead_symbol                                0x2A0528
	#define cellFsWrite_symbol                               0x2A0494
	#define cellFsLseek_symbol                               0x29FB1C
	#define cellFsStat_symbol                                0x29FDA0
	#define cellFsUtime_symbol                               0x2A188C
	#define cellFsUnlink_internal_symbol                     0x19C4AC
	#define cellFsRename_internal_symbol                     0x196F64

	#define cellFsUtilMount_symbol                           0x29F8FC
	#define cellFsUtilUmount_symbol                          0x2A12D8
	#define cellFsUtilNewfs_symbol                           0x2A1324

	#define pathdup_from_user_symbol                         0x1A23A0
	#define open_path_symbol                                 0x2A02BC
	#define open_fs_object_symbol                            0x18A7D0
	#define close_fs_object_symbol                           0x18970C

	#define storage_get_device_info_symbol                   0x282784
	#define storage_get_device_config_symbol                 0x281C14
	#define storage_open_symbol                              0x282194
	#define storage_close_symbol                             0x281F84
	#define storage_read_symbol                              0x2814F4
	#define storage_write_symbol                             0x2813C4
	#define storage_send_device_command_symbol               0x281080
	#define storage_map_io_memory_symbol                     0x282640
	#define storage_unmap_io_memory_symbol                   0x28250C
	#define new_medium_listener_object_symbol                0x97434
	#define delete_medium_listener_object_symbol             0x98C6C
	#define set_medium_event_callbacks_symbol                0x98FD0

	#define cellUsbdRegisterLdd_symbol                       0x268F04
	#define cellUsbdUnregisterLdd_symbol                     0x268EB4
	#define cellUsbdScanStaticDescriptor_symbol              0x26A104
	#define cellUsbdOpenPipe_symbol                          0x26A1B4
	#define cellUsbdClosePipe_symbol                         0x26A164
	#define cellUsbdControlTransfer_symbol                   0x26A068
	#define cellUsbdBulkTransfer_symbol                      0x269FE8

	#define decrypt_func_symbol                              0x3496C
	#define lv1_call_99_wrapper_symbol                       0x4EEA4
	#define modules_verification_symbol                      0x58A48
	#define authenticate_program_segment_symbol              0x5A884

	#define prx_load_module_symbol                           0x88B78
	#define prx_start_module_symbol                          0x87844
	#define prx_stop_module_symbol                           0x88C1C
	#define prx_unload_module_symbol                         0x87578
	#define prx_get_module_info_symbol                       0x87000
	#define prx_get_module_id_by_address_symbol              0x86F10
	#define prx_get_module_id_by_name_symbol                 0x86F60
	#define prx_get_module_list_symbol                       0x87080
	#define load_module_by_fd_symbol                         0x881A8
	#define parse_sprx_symbol                                0x85F2C
	#define open_prx_object_symbol                           0x7F46C
	#define close_prx_object_symbol                          0x7FD7C
	#define lock_prx_mutex_symbol                            0x86EB8
	#define unlock_prx_mutex_symbol                          0x86EC4

	#define extend_kstack_symbol                             0x70018

	#define get_pseudo_random_number_symbol                  0x230E74
	#define md5_reset_symbol                                 0x161C80
	#define md5_update_symbol                                0x162720
	#define md5_final_symbol                                 0x1628A0
	#define ss_get_open_psid_symbol                          0x23335C
	#define update_mgr_read_eeprom_symbol                    0x22C76C
	#define update_mgr_write_eeprom_symbol                   0x22C6B4
	#define update_mgr_if_get_token_symbol                   0x22E0D0

	#define ss_params_get_update_status_symbol               0x50AB0

	#define sm_get_temperature_symbol                        0x26C230
	#define sm_get_fan_policy_symbol                         0x26B5C4
	#define sm_set_fan_policy_symbol                         0x26D3BC
	#define sm_get_temperature_patch                         0xC6A4
	#define sm_get_fan_policy_patch                          0x9E38
	#define sm_set_fan_policy_patch                          0xA334

	#define SHA1_init_symbol                                 0x2CE474
	#define SHA1_update_symbol                               0x2CE4D4
	#define SHA1_final_symbol                                0x2CE688
	#define aescbccfb_dec_symbol                             0x2CC968
	#define aescbccfb_enc_symbol                             0x2CC718
	#define get_path_by_fd_symbol                            0x1A1C3C

	#define ECDSA_1                                          0x59D38
	#define ECDSA_2                                          0x2D2920
	#define ECDSA_FLAG                                       0x474EA8
	#define sysmem_obj                                       0x475060
	#define qa_eeprom_offset                                 0x48C06

	#define syscall_table_symbol                             0x363A18
	#define syscall_call_offset                              0x27E888

	#define read_bdvd0_symbol                                0x1AD310
	#define read_bdvd1_symbol                                0x1AEF3C
	#define read_bdvd2_symbol                                0x1BC0F4

	#define storage_internal_get_device_object_symbol        0x280B38

	#define hid_mgr_read_usb_symbol                          0x1023B4
	#define hid_mgr_read_bt_symbol                           0xFC28C

	#define bt_set_controller_info_internal_symbol           0xF02F8

	#define device_event_port_send_call                      0x28ACF0
	#define device_event_port_send_call_restore              0x7C83D84B

	#define ss_pid_call_1                                    0x21BF90

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7F360
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x88A14

	#define shutdown_copy_params_call                        0xAACC
	#define shutdown_copy_params_call_restore                0xB94F0048

	#define fsloop_open_call                                 0x2A071C
	#define fsloop_close_call                                0x2A076C
	#define fsloop_read_call                                 0x2A07AC

	#define shutdown_patch_offset                            0xAAB8
	#define module_sdk_version_patch_offset                  0x26FE00
	#define module_add_parameter_to_parse_sprxpatch_offset   0x88284

	#define user_thread_prio_patch                           0x203F8
	#define user_thread_prio_patch2                          0x20408

	#define lic_patch                                        0x5622C
	#define lic_patch_restore                                0x48249B75
	#define ode_patch                                        0x2302E8
	#define fix_80010009                                     0x5A658
	#define fix_8001003D                                     0x56588
	#define fix_8001003E                                     0x5664C
	#define PATCH_JUMP                                       0x56600

	#define io_rtoc_entry_1                                 -0x1F0
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0

	#define storage_rtoc_entry_1                             0x1DD8

	#define device_event_rtoc_entry_1                        0x2048

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x3680

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x250FC
	#define permissions_exception2                           0xC3208
	#define permissions_exception3                           0x204CC

	#define patch_data1_offset                               0x3E2BC0
	#define patch_func2                                      0x59CF8
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDAC49
	#define patch_func8_offset1                              0x564B0
	#define patch_func8_offset2                              0x56610
	#define patch_func8_offset2_restore                      0x4821FC3D
	#define patch_func9_offset                               0x5A66C
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x37DBB0

	#define mmapper_flags_temp_patch                         0x70EEC

	#define rsx_syscall_check                                0x7E4C
	#define unk_func2_unregister_service                     0x99100
	#define unk_func3_unregister_service                     0x9DB94

	/* lv1 */
	#define vsh_pos_in_ram                                   0x510000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E3000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52C00000056000
	#define PS1_EMU_HASH                                     0xCC2850000009A000
	#define PS1_NETEMU_HASH                                  0xCC28B000000BD000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037B000
	#define BDP_BDVD_HASH                                    0xCC28D00000436000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000041000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F470000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA440C

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4C24
	#define ps2tonet_size_patch                              0xC4C18
	#define vmode_patch_offset                               0x444DCC
	#define psp_drm_patch1                                   0x241E28
	#define psp_drm_patch2                                   0x2428C8
	#define psp_drm_patch3                                   0x242504
	#define psp_drm_patch4                                   0x242D10
	#define psp_drm_patchA                                   0x241F44
	#define psp_drm_patchB                                   0x2427E4
	#define psp_drm_patchC                                   0x24197C
	#define psp_drm_patchD                                   0x241F2C
	#define psp_drm_patchE                                   0x241F30
	#define psp_drm_patchF                                   0x2428FC
	#define psp_extra_drm_patch                              0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDD978
	#define app_home_offset                                  0x251130

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68354

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23F30
	#define ps_region_error_offset                           0x68C4
	#define remote_play_offset                               0x5FC4
	#define ps2_nonbw_offset3                                0x17004

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EA58
	#define patch2_nas                                       0x2EBBC
	#define patch3_nas                                       0x1F848

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F638
	#define pspemu_path_offset                               0x4B4A0
	#define psptrans_path_offset                             0x4B530

	/* download_plugin */
	#define elf_patch1_download                              0x42E1C
	#define elf_patch2_download                              0x42E24
	#define elf_patch3_download                              0x4D830
	#define elf_patch4_download                              0x4E650
	#define elf_patch5_download                              0x4E670
	#define elf_patch6_download                              0x4E740

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x7A3F0
	#define elf_patch2_autodownload                          0x7A3F8

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                        0xC50D0000000ED000
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH                 0xDE52F00000056000
	#define GAME_EXT_PLUGIN_REBUG_HASH                       0xCC2680000001E000
	#define dex_ps2_nonbw_offset                             0xDDD88
	#define dex_ps2_nonbw_offset2                            0x68294
	#define dex_ps2_nonbw_offset3                            0x172F4
	#define dex_ps2tonet_patch                               0xCA170
	#define dex_ps2tonet_size_patch                          0xCA164
	#define dex_vmode_patch_offset                           0x44C9C0
	#define dex_psp_drm_patch1                               0x249650
	#define dex_psp_drm_patch2                               0x24A0F0
	#define dex_psp_drm_patch3                               0x249D2C
	#define dex_psp_drm_patch4                               0x24A538
	#define dex_psp_drm_patchA                               0x24976C
	#define dex_psp_drm_patchB                               0x24A00C
	#define dex_psp_drm_patchC                               0x2491A4
	#define dex_psp_drm_patchD                               0x249754
	#define dex_psp_drm_patchE                               0x249758
	#define dex_psp_drm_patchF                               0x24A124
	#define dex_psp_extra_drm_patch                          0x0
#endif

#ifdef FIRMWARE_465C

	#define FIRMWARE_VERSION                                 0x465

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2BB0ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474F1CULL
		#define PS3MAPI_PSID                                 0x8000000000474F34ULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x34F960

	#define create_kernel_object_symbol                      0x11FB0
	#define destroy_kernel_object_symbol                     0x11914
	#define destroy_shared_kernel_object_symbol              0x11288
	#define open_kernel_object_symbol                        0x12600
	#define open_shared_kernel_object_symbol                 0x12410
	#define close_kernel_object_handle_symbol                0x11A30

	#define alloc_symbol                                     0x6479C
	#define dealloc_symbol                                   0x64BD8
	#define copy_to_user_symbol                              0xF86C
	#define copy_from_user_symbol                            0xFA88
	#define copy_to_process_symbol                           0xF924
	#define copy_from_process_symbol                         0xF734
	#define process_read_memory_symbol                       0x270B50
	#define process_write_memory_symbol                      0x2709C4
	#define page_allocate_symbol                             0x6030C
	#define page_free_symbol                                 0x5FD70
	#define page_export_to_proc_symbol                       0x604A8
	#define page_unexport_from_proc_symbol                   0x5FC64
	#define kernel_ea_to_lpar_addr_symbol                    0x700C4
	#define process_ea_to_lpar_addr_ex_symbol                0x776D8
	#define set_pte_symbol                                   0x5E308
	#define map_process_memory_symbol                        0x771E4
	#define panic_symbol                                     0x276258

	#define memcpy_symbol                                    0x7E8A4
	#define memset_symbol                                    0x4D66C
	#define memcmp_symbol                                    0x4C97C
	#define memchr_symbol                                    0x4C92C
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
	#define strrchr_symbol                                   0x4D950

	#define spin_lock_irqsave_ex_symbol                      0x276428
	#define spin_unlock_irqrestore_ex_symbol                 0x2763FC

	#define create_process_common_symbol                     0x2741C4
	#define create_process_base_symbol                       0x273880
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x273FD0

	#define ppu_thread_create_symbol                         0x13EC8
	#define ppu_thread_exit_symbol                           0x13F80
	#define ppu_thread_join_symbol                           0x13FD4
	#define ppu_thread_delay_symbol                          0x287A4
	#define create_kernel_thread_symbol                      0x24B20
	#define create_user_thread_symbol                        0x2525C
	#define create_user_thread2_symbol                       0x25080
	#define start_thread_symbol                              0x23D4C
	#define run_thread_symbol                                0x2357C
	#define self_threading_symbol                            0x25868
	#define register_thread_symbol                           0x2705DC
	#define allocate_user_stack_symbol                       0x270DC4
	#define deallocate_user_stack_symbol                     0x270D2C

	#define mutex_create_symbol                              0x1363C
	#define mutex_destroy_symbol                             0x135D4
	#define mutex_lock_symbol                                0x135CC
	#define mutex_lock_ex_symbol                             0x1DB5C
	#define mutex_trylock_symbol                             0x135C8
	#define mutex_unlock_symbol                              0x135C4

	#define cond_create_symbol                               0x137A8
	#define cond_destroy_symbol                              0x13758
	#define cond_wait_symbol                                 0x13750
	#define cond_wait_ex_symbol                              0x1F148
	#define cond_signal_symbol                               0x1372C
	#define cond_signal_all_symbol                           0x13708

	#define semaphore_initialize_symbol                      0x30C54
	#define semaphore_wait_ex_symbol                         0x3095C
	#define semaphore_trywait_symbol                         0x30544
	#define semaphore_post_ex_symbol                         0x30690

	#define event_port_create_symbol                         0x13078
	#define event_port_destroy_symbol                        0x134E0
	#define event_port_connect_symbol                        0x13558
	#define event_port_disconnect_symbol                     0x13484
	#define event_port_send_symbol                           0x13070
	#define event_port_send_ex_symbol                        0x2B204

	#define event_queue_create_symbol                        0x13380
	#define event_queue_destroy_symbol                       0x13308
	#define event_queue_receive_symbol                       0x1314C
	#define event_queue_tryreceive_symbol                    0x13218

	#define cellFsOpen_symbol                                0x2A0590
	#define cellFsClose_symbol                               0x2A03F8
	#define cellFsRead_symbol                                0x2A0534
	#define cellFsWrite_symbol                               0x2A04A0
	#define cellFsLseek_symbol                               0x29FB28
	#define cellFsStat_symbol                                0x29FDAC
	#define cellFsUtime_symbol                               0x2A1898
	#define cellFsUnlink_internal_symbol                     0x19C4B4
	#define cellFsRename_internal_symbol                     0x196F6C

	#define cellFsUtilMount_symbol                           0x29F908
	#define cellFsUtilUmount_symbol                          0x2A12E4
	#define cellFsUtilNewfs_symbol                           0x2A1330

	#define pathdup_from_user_symbol                         0x1A23A8
	#define open_path_symbol                                 0x2A02C8
	#define open_fs_object_symbol                            0x18A7D8
	#define close_fs_object_symbol                           0x189714

	#define storage_get_device_info_symbol                   0x282790
	#define storage_get_device_config_symbol                 0x281C20
	#define storage_open_symbol                              0x2821A0
	#define storage_close_symbol                             0x281F90
	#define storage_read_symbol                              0x281500
	#define storage_write_symbol                             0x2813D0
	#define storage_send_device_command_symbol               0x28108C
	#define storage_map_io_memory_symbol                     0x28264C
	#define storage_unmap_io_memory_symbol                   0x282518
	#define new_medium_listener_object_symbol                0x9743C
	#define delete_medium_listener_object_symbol             0x98C74
	#define set_medium_event_callbacks_symbol                0x98FD8

	#define cellUsbdRegisterLdd_symbol                       0x268F0C
	#define cellUsbdUnregisterLdd_symbol                     0x268EBC
	#define cellUsbdScanStaticDescriptor_symbol              0x26A10C
	#define cellUsbdOpenPipe_symbol                          0x26A1BC
	#define cellUsbdClosePipe_symbol                         0x26A16C
	#define cellUsbdControlTransfer_symbol                   0x26A070
	#define cellUsbdBulkTransfer_symbol                      0x269FF0

	#define decrypt_func_symbol                              0x34970
	#define lv1_call_99_wrapper_symbol                       0x4EEA8
	#define modules_verification_symbol                      0x58A4C
	#define authenticate_program_segment_symbol              0x5A888

	#define prx_load_module_symbol                           0x88B7C
	#define prx_start_module_symbol                          0x87848
	#define prx_stop_module_symbol                           0x88C20
	#define prx_unload_module_symbol                         0x8757C
	#define prx_get_module_info_symbol                       0x87004
	#define prx_get_module_id_by_address_symbol              0x86F14
	#define prx_get_module_id_by_name_symbol                 0x86F64
	#define prx_get_module_list_symbol                       0x87084
	#define load_module_by_fd_symbol                         0x881AC
	#define parse_sprx_symbol                                0x85F30
	#define open_prx_object_symbol                           0x7F470
	#define close_prx_object_symbol                          0x7FD80
	#define lock_prx_mutex_symbol                            0x86EBC
	#define unlock_prx_mutex_symbol                          0x86EC8

	#define extend_kstack_symbol                             0x7001C

	#define get_pseudo_random_number_symbol                  0x230E7C
	#define md5_reset_symbol                                 0x161C88
	#define md5_update_symbol                                0x162728
	#define md5_final_symbol                                 0x1628A8
	#define ss_get_open_psid_symbol                          0x233364
	#define update_mgr_read_eeprom_symbol                    0x22C774
	#define update_mgr_write_eeprom_symbol                   0x22C6BC
	#define update_mgr_if_get_token_symbol                   0x22E0D8

	#define ss_params_get_update_status_symbol               0x50AB4

	#define sm_get_temperature_symbol                        0x26C238
	#define sm_get_fan_policy_symbol                         0x26B5CC
	#define sm_set_fan_policy_symbol                         0x26D3C4
	#define sm_get_temperature_patch                         0xC6A8
	#define sm_get_fan_policy_patch                          0x9E38
	#define sm_set_fan_policy_patch                          0xA334

	#define SHA1_init_symbol                                 0x2CE480
	#define SHA1_update_symbol                               0x2CE4E0
	#define SHA1_final_symbol                                0x2CE694
	#define aescbccfb_dec_symbol                             0x2CC974
	#define aescbccfb_enc_symbol                             0x2CC724
	#define get_path_by_fd_symbol                            0x1A1C44

	#define ECDSA_1                                          0x59D3C
	#define ECDSA_2                                          0x2D292C
	#define ECDSA_FLAG                                       0x474EA8
	#define sysmem_obj                                       0x475060
	#define qa_eeprom_offset                                 0x48C0A

	#define syscall_table_symbol                             0x363A18
	#define syscall_call_offset                              0x27E894

	#define read_bdvd0_symbol                                0x1AD318
	#define read_bdvd1_symbol                                0x1AEF44
	#define read_bdvd2_symbol                                0x1BC0FC

	#define storage_internal_get_device_object_symbol        0x280B44

	#define hid_mgr_read_usb_symbol                          0x1023BC
	#define hid_mgr_read_bt_symbol                           0xFC294

	#define bt_set_controller_info_internal_symbol           0xF0300

	#define device_event_port_send_call                      0x28ACFC
	#define device_event_port_send_call_restore              0x7483D84B

	#define ss_pid_call_1                                    0x21BF98

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7F364
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x88A18

	#define shutdown_copy_params_call                        0xAACC
	#define shutdown_copy_params_call_restore                0xBD4F0048

	#define fsloop_open_call                                 0x2A0728
	#define fsloop_close_call                                0x2A0778
	#define fsloop_read_call                                 0x2A07B8

	#define shutdown_patch_offset                            0xAAB8
	#define module_sdk_version_patch_offset                  0x26FE0C
	#define module_add_parameter_to_parse_sprxpatch_offset   0x88288

	#define user_thread_prio_patch                           0x203FC
	#define user_thread_prio_patch2                          0x2040C

	#define lic_patch                                        0x56230
	#define lic_patch_restore                                0x48240EED
	#define ode_patch                                        0x2302F0
	#define fix_80010009                                     0x5A65C
	#define fix_8001003D                                     0x5658C
	#define fix_8001003E                                     0x56650
	#define PATCH_JUMP                                       0x56604

	#define io_rtoc_entry_1                                 -0x1F0
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0

	#define storage_rtoc_entry_1                             0x1DD8

	#define device_event_rtoc_entry_1                        0x2048

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x3680

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x25100
	#define permissions_exception2                           0xC3210
	#define permissions_exception3                           0x204D0

	#define patch_data1_offset                               0x3E2BC0
	#define patch_func2                                      0x59CFC
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDAC49
	#define patch_func8_offset1                              0x564B4
	#define patch_func8_offset2                              0x56614
	#define patch_func8_offset2_restore                      0x4821FC45
	#define patch_func9_offset                               0x5A670
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x37DBB0

	#define mmapper_flags_temp_patch                         0x70EF0

	#define rsx_syscall_check                                0x7E4C
	#define unk_func2_unregister_service                     0x99108
	#define unk_func3_unregister_service                     0x9DB9C

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E3000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52C00000056000
	#define PS1_EMU_HASH                                     0xCC2850000009A000
	#define PS1_NETEMU_HASH                                  0xCC28B000000BE000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037B000
	#define BDP_BDVD_HASH                                    0xCC28D00000436000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000041000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F470000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA440C

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4C24
	#define ps2tonet_size_patch                              0xC4C18
	#define vmode_patch_offset                               0x444E28
	#define psp_drm_patch1                                   0x241E84
	#define psp_drm_patch2                                   0x242924
	#define psp_drm_patch3                                   0x242560
	#define psp_drm_patch4                                   0x242D6C
	#define psp_drm_patchA                                   0x241FA0
	#define psp_drm_patchB                                   0x242840
	#define psp_drm_patchC                                   0x2419D8
	#define psp_drm_patchD                                   0x241F88
	#define psp_drm_patchE                                   0x241F8C
	#define psp_drm_patchF                                   0x242958
	#define psp_extra_drm_patch                              0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDD978
	#define app_home_offset                                  0x251130

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68354

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23F30
	#define ps_region_error_offset                           0x68C4
	#define remote_play_offset                               0x5FC4
	#define ps2_nonbw_offset3                                0x17004

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EA58
	#define patch2_nas                                       0x2EBBC
	#define patch3_nas                                       0x1F848

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F638
	#define pspemu_path_offset                               0x4B4A0
	#define psptrans_path_offset                             0x4B530

	/* download_plugin */
	#define elf_patch1_download                              0x42E1C
	#define elf_patch2_download                              0x42E24
	#define elf_patch3_download                              0x4D830
	#define elf_patch4_download                              0x4E650
	#define elf_patch5_download                              0x4E670
	#define elf_patch6_download                              0x4E740

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x7A3F0
	#define elf_patch2_autodownload                          0x7A3F8

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                        0xC50D0000000ED000
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH                 0xDE52F00000056000
	#define GAME_EXT_PLUGIN_REBUG_HASH                       0xCC2680000001E000
	#define dex_ps2_nonbw_offset                             0xDDD88
	#define dex_ps2_nonbw_offset2                            0x68294
	#define dex_ps2_nonbw_offset3                            0x172F4
	#define dex_ps2tonet_patch                               0xCA170
	#define dex_ps2tonet_size_patch                          0xCA164
	#define dex_vmode_patch_offset                           0x44CA1C
	#define dex_psp_drm_patch1                               0x2496AC
	#define dex_psp_drm_patch2                               0x24A14C
	#define dex_psp_drm_patch3                               0x249D88
	#define dex_psp_drm_patch4                               0x24A594
	#define dex_psp_drm_patchA                               0x2497C8
	#define dex_psp_drm_patchB                               0x24A068
	#define dex_psp_drm_patchC                               0x249200
	#define dex_psp_drm_patchD                               0x2497B0
	#define dex_psp_drm_patchE                               0x2497B4
	#define dex_psp_drm_patchF                               0x24A180
	#define dex_psp_extra_drm_patch                          0x0
#endif

#ifdef FIRMWARE_465D

	#define FIRMWARE_VERSION                                 0x465

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000004095B0ULL
		#define PS3MAPI_IDPS_2                               0x800000000049CF1CULL
		#define PS3MAPI_PSID                                 0x800000000049CF34ULL
	#endif
	#define FIRMWARE_DEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x375510

	#define create_kernel_object_symbol                      0x125F8
	#define destroy_kernel_object_symbol                     0x11F5C
	#define destroy_shared_kernel_object_symbol              0x118D0
	#define open_kernel_object_symbol                        0x12C48
	#define open_shared_kernel_object_symbol                 0x12A58
	#define close_kernel_object_handle_symbol                0x12078

	#define alloc_symbol                                     0x6816C
	#define dealloc_symbol                                   0x685A8
	#define copy_to_user_symbol                              0xFEB4
	#define copy_from_user_symbol                            0x100D0
	#define copy_to_process_symbol                           0xFF6C
	#define copy_from_process_symbol                         0xFD7C
	#define process_read_memory_symbol                       0x277474
	#define process_write_memory_symbol                      0x2772E8
	#define page_allocate_symbol                             0x63CDC
	#define page_free_symbol                                 0x63740
	#define page_export_to_proc_symbol                       0x63E78
	#define page_unexport_from_proc_symbol                   0x63634
	#define kernel_ea_to_lpar_addr_symbol                    0x73C14
	#define process_ea_to_lpar_addr_ex_symbol                0x7B7B4
	#define set_pte_symbol                                   0x61CD8
	#define map_process_memory_symbol                        0x7B2C0
	#define panic_symbol                                     0x27E130

	#define memcpy_symbol                                    0x82980
	#define memset_symbol                                    0x51014
	#define memcmp_symbol                                    0x50324
	#define memchr_symbol                                    0x502D4
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
	#define strrchr_symbol                                   0x512F8

	#define spin_lock_irqsave_ex_symbol                      0x27E300
	#define spin_unlock_irqrestore_ex_symbol                 0x27E2D4

	#define create_process_common_symbol                     0x27B0F8
	#define create_process_base_symbol                       0x27A790
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x27AEF8

	#define ppu_thread_create_symbol                         0x145FC
	#define ppu_thread_exit_symbol                           0x146B4
	#define ppu_thread_join_symbol                           0x14708
	#define ppu_thread_delay_symbol                          0x2A6E8
	#define create_kernel_thread_symbol                      0x267D0
	#define create_user_thread_symbol                        0x26F0C
	#define create_user_thread2_symbol                       0x26D30
	#define start_thread_symbol                              0x25868
	#define run_thread_symbol                                0x2502C
	#define self_threading_symbol                            0x27518
	#define register_thread_symbol                           0x276F00
	#define allocate_user_stack_symbol                       0x2776E8
	#define deallocate_user_stack_symbol                     0x277650

	#define mutex_create_symbol                              0x13C8C
	#define mutex_destroy_symbol                             0x13C24
	#define mutex_lock_symbol                                0x13C1C
	#define mutex_lock_ex_symbol                             0x1F60C
	#define mutex_trylock_symbol                             0x13C18
	#define mutex_unlock_symbol                              0x13C14

	#define cond_create_symbol                               0x13DF8
	#define cond_destroy_symbol                              0x13DA8
	#define cond_wait_symbol                                 0x13DA0
	#define cond_wait_ex_symbol                              0x20BF8
	#define cond_signal_symbol                               0x13D7C
	#define cond_signal_all_symbol                           0x13D58

	#define semaphore_initialize_symbol                      0x34574
	#define semaphore_wait_ex_symbol                         0x3427C
	#define semaphore_trywait_symbol                         0x33E64
	#define semaphore_post_ex_symbol                         0x33FB0

	#define event_port_create_symbol                         0x136C8
	#define event_port_destroy_symbol                        0x13B30
	#define event_port_connect_symbol                        0x13BA8
	#define event_port_disconnect_symbol                     0x13AD4
	#define event_port_send_symbol                           0x136C0
	#define event_port_send_ex_symbol                        0x2D2C8

	#define event_queue_create_symbol                        0x139D0
	#define event_queue_destroy_symbol                       0x13958
	#define event_queue_receive_symbol                       0x1379C
	#define event_queue_tryreceive_symbol                    0x13868

	#define cellFsOpen_symbol                                0x2BB2D8
	#define cellFsClose_symbol                               0x2BB140
	#define cellFsRead_symbol                                0x2BB27C
	#define cellFsWrite_symbol                               0x2BB1E8
	#define cellFsLseek_symbol                               0x2BAA3C
	#define cellFsStat_symbol                                0x2BAAF4
	#define cellFsUtime_symbol                               0x2BC464
	#define cellFsUnlink_internal_symbol                     0x1A2840
	#define cellFsRename_internal_symbol                     0x19D2F8

	#define cellFsUtilMount_symbol                           0x2BA7B0
	#define cellFsUtilUmount_symbol                          0x2BA784
	#define cellFsUtilNewfs_symbol                           0x2BC0FC

	#define pathdup_from_user_symbol                         0x1A8858
	#define open_path_symbol                                 0x2BB010
	#define open_fs_object_symbol                            0x190B64
	#define close_fs_object_symbol                           0x18FAA0

	#define storage_get_device_info_symbol                   0x295690
	#define storage_get_device_config_symbol                 0x293D1C
	#define storage_open_symbol                              0x2958B8
	#define storage_close_symbol                             0x2940A4
	#define storage_read_symbol                              0x293020
	#define storage_write_symbol                             0x292EF0
	#define storage_send_device_command_symbol               0x292B40
	#define storage_map_io_memory_symbol                     0x29553C
	#define storage_unmap_io_memory_symbol                   0x2953F8
	#define new_medium_listener_object_symbol                0x9CBAC
	#define delete_medium_listener_object_symbol             0x9E3E4
	#define set_medium_event_callbacks_symbol                0x9E748

	#define cellUsbdRegisterLdd_symbol                       0x26F3E8
	#define cellUsbdUnregisterLdd_symbol                     0x26F398
	#define cellUsbdScanStaticDescriptor_symbol              0x2705E8
	#define cellUsbdOpenPipe_symbol                          0x270698
	#define cellUsbdClosePipe_symbol                         0x270648
	#define cellUsbdControlTransfer_symbol                   0x27054C
	#define cellUsbdBulkTransfer_symbol                      0x2704CC

	#define decrypt_func_symbol                              0x38290
	#define lv1_call_99_wrapper_symbol                       0x52850
	#define modules_verification_symbol                      0x5C41C
	#define authenticate_program_segment_symbol              0x5E258

	#define prx_load_module_symbol                           0x8D280
	#define prx_start_module_symbol                          0x8BF4C
	#define prx_stop_module_symbol                           0x8D324
	#define prx_unload_module_symbol                         0x8BC80
	#define prx_get_module_info_symbol                       0x8B678
	#define prx_get_module_id_by_address_symbol              0x8B588
	#define prx_get_module_id_by_name_symbol                 0x8B5D8
	#define prx_get_module_list_symbol                       0x8B6F8
	#define load_module_by_fd_symbol                         0x8C8B0
	#define parse_sprx_symbol                                0x8A5A4
	#define open_prx_object_symbol                           0x8354C
	#define close_prx_object_symbol                          0x83E5C
	#define lock_prx_mutex_symbol                            0x8B530
	#define unlock_prx_mutex_symbol                          0x8B53C

	#define extend_kstack_symbol                             0x73B6C

	#define get_pseudo_random_number_symbol                  0x237358
	#define md5_reset_symbol                                 0x168014
	#define md5_update_symbol                                0x168AB4
	#define md5_final_symbol                                 0x168C34
	#define ss_get_open_psid_symbol                          0x239840
	#define update_mgr_read_eeprom_symbol                    0x232C38
	#define update_mgr_write_eeprom_symbol                   0x232B6C
	#define update_mgr_if_get_token_symbol                   0x2345B4

	#define ss_params_get_update_status_symbol               0x5445C

	#define sm_get_temperature_symbol                        0x272714
	#define sm_get_fan_policy_symbol                         0x271AA8
	#define sm_set_fan_policy_symbol                         0x273A70
	#define sm_get_temperature_patch                         0xC728
	#define sm_get_fan_policy_patch                          0x9EB8
	#define sm_set_fan_policy_patch                          0xA3B4

	#define SHA1_init_symbol                                 0x2EFDCC
	#define SHA1_update_symbol                               0x2EFE2C
	#define SHA1_final_symbol                                0x2EFFE0
	#define aescbccfb_dec_symbol                             0x2EE2C0
	#define aescbccfb_enc_symbol                             0x2EE070
	#define get_path_by_fd_symbol                            0x1A80F4

	#define ECDSA_1                                          0x5D70C
	#define ECDSA_2                                          0x2F4278
	#define ECDSA_FLAG                                       0x49CEA8
	#define sysmem_obj                                       0x49D060
	#define qa_eeprom_offset                                 0x4C56E

	#define syscall_table_symbol                             0x38A120
	#define syscall_call_offset                              0x286B74

	#define read_bdvd0_symbol                                0x1B37C8
	#define read_bdvd1_symbol                                0x1B53F4
	#define read_bdvd2_symbol                                0x1C25AC

	#define storage_internal_get_device_object_symbol        0x2925F8

	#define hid_mgr_read_usb_symbol                          0x107EC0
	#define hid_mgr_read_bt_symbol                           0x101D98

	#define bt_set_controller_info_internal_symbol           0xF5E04

	#define device_event_port_send_call                      0x29F88C
	#define device_event_port_send_call_restore              0x343ED74B

	#define ss_pid_call_1                                    0x222448

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x83440
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x8D11C

	#define shutdown_copy_params_call                        0xAB4C
	#define shutdown_copy_params_call_restore                0x85550048

	#define fsloop_open_call                                 0x2BB470
	#define fsloop_close_call                                0x2BB4C0
	#define fsloop_read_call                                 0x2BB500

	#define shutdown_patch_offset                            0xAB38
	#define module_sdk_version_patch_offset                  0x276528
	#define module_add_parameter_to_parse_sprxpatch_offset   0x8C98C

	#define user_thread_prio_patch                           0x21EAC
	#define user_thread_prio_patch2                          0x21EBC

	#define lic_patch                                        0x59C00
	#define lic_patch_restore                                0x482584B5
	#define ode_patch                                        0x2367CC
	#define fix_80010009                                     0x5E02C
	#define fix_8001003D                                     0x59F5C
	#define fix_8001003E                                     0x5A020
	#define PATCH_JUMP                                       0x59FD4

	#define io_rtoc_entry_1                                 -0xC0
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65C0

	#define storage_rtoc_entry_1                             0x22B0

	#define device_event_rtoc_entry_1                        0x2638

	#define time_rtoc_entry_1                               -0x75E0
	#define time_rtoc_entry_2                               -0x75E8

	#define thread_rtoc_entry_1                             -0x7660

	#define process_rtoc_entry_1                            -0x77A0

	#define bt_rtoc_entry_1                                 -0x3558

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x26DB0
	#define permissions_exception2                           0xC8980
	#define permissions_exception3                           0x21F80

	#define patch_data1_offset                               0x4095C0
	#define patch_func2                                      0x5D6CC
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDAB99
	#define patch_func8_offset1                              0x59E84
	#define patch_func8_offset2                              0x59FE4
	#define patch_func8_offset2_restore                      0x4822414D
	#define patch_func9_offset                               0x5E040
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x3A45B0

	#define mmapper_flags_temp_patch                         0x74B80

	#define rsx_syscall_check                                0x7E4C
	#define unk_func2_unregister_service                     0x9E878
	#define unk_func3_unregister_service                     0xA330C

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E6000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000ED000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52F00000056000
	#define PS1_EMU_HASH                                     0xCC2850000009A000
	#define PS1_NETEMU_HASH                                  0xCC28B000000BD000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037B000
	#define BDP_BDVD_HASH                                    0xCC28D00000436000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000041000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F4800000020000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA440C

	/* vsh */
	#define vsh_text_size                                    0x6C0000
	#define ps2tonet_patch                                   0xCA170
	#define ps2tonet_size_patch                              0xCA164
	#define vmode_patch_offset                               0x44CA1C
	#define psp_drm_patch1                                   0x2496AC
	#define psp_drm_patch2                                   0x24A14C
	#define psp_drm_patch3                                   0x249D88
	#define psp_drm_patch4                                   0x24A594
	#define psp_drm_patchA                                   0x2497C8
	#define psp_drm_patchB                                   0x24A068
	#define psp_drm_patchC                                   0x249200
	#define psp_drm_patchD                                   0x2497B0
	#define psp_drm_patchE                                   0x2497B4
	#define psp_drm_patchF                                   0x24A180
	#define psp_extra_drm_patch                              0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDDD88
	#define app_home_offset                                  0x251CE0

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68294

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x2414C
	#define ps_region_error_offset                           0x6880
	#define remote_play_offset                               0x5FC4
	#define ps2_nonbw_offset3                                0x172F4

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EE78
	#define patch2_nas                                       0x2EFDC
	#define patch3_nas                                       0x1FB08

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x200E0
	#define pspemu_path_offset                               0x4C690
	#define psptrans_path_offset                             0x4C748

	/* download_plugin */
	#define elf_patch1_download                              0x42DB0
	#define elf_patch2_download                              0x42DB8
	#define elf_patch3_download                              0x4D738
	#define elf_patch4_download                              0x4E558
	#define elf_patch5_download                              0x4E578
	#define elf_patch6_download                              0x4E648

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x7A2A0
	#define elf_patch2_autodownload                          0x7A2A8

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* CEX */
	#define cex_ps2tonet_patch                               0xC4C24
	#define cex_ps2tonet_size_patch                          0xC4C18
	#define cex_vmode_patch_offset                           0x444E28
	#define cex_psp_drm_patch1                               0x241E84
	#define cex_psp_drm_patch2                               0x242924
	#define cex_psp_drm_patch3                               0x242560
	#define cex_psp_drm_patch4                               0x242D6C
	#define cex_psp_drm_patchA                               0x241FA0
	#define cex_psp_drm_patchB                               0x242840
	#define cex_psp_drm_patchC                               0x2419D8
	#define cex_psp_drm_patchD                               0x241F88
	#define cex_psp_drm_patchE                               0x241F8C
	#define cex_psp_drm_patchF                               0x242958
	#define cex_psp_extra_drm_patch                          0x0
#endif

#ifdef FIRMWARE_470C

	#define FIRMWARE_VERSION                                 0x470

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2DB0ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474AF4ULL
		#define PS3MAPI_PSID                                 0x8000000000474B0CULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x34FB10

	#define create_kernel_object_symbol                      0x11FAC
	#define destroy_kernel_object_symbol                     0x11910
	#define destroy_shared_kernel_object_symbol              0x11284
	#define open_kernel_object_symbol                        0x125FC
	#define open_shared_kernel_object_symbol                 0x1240C
	#define close_kernel_object_handle_symbol                0x11A2C

	#define alloc_symbol                                     0x64820
	#define dealloc_symbol                                   0x64C5C
	#define copy_to_user_symbol                              0xF868
	#define copy_from_user_symbol                            0xFA84
	#define copy_to_process_symbol                           0xF920
	#define copy_from_process_symbol                         0xF730
	#define process_read_memory_symbol                       0x267E48
	#define process_write_memory_symbol                      0x267CBC
	#define page_allocate_symbol                             0x60390
	#define page_free_symbol                                 0x5FDF4
	#define page_export_to_proc_symbol                       0x6052C
	#define page_unexport_from_proc_symbol                   0x5FCE8
	#define kernel_ea_to_lpar_addr_symbol                    0x70148
	#define process_ea_to_lpar_addr_ex_symbol                0x7775C
	#define set_pte_symbol                                   0x5E38C
	#define map_process_memory_symbol                        0x77268
	#define panic_symbol                                     0x26D550

	#define memcpy_symbol                                    0x7E928
	#define memset_symbol                                    0x4D668
	#define memcmp_symbol                                    0x4C978
	#define memchr_symbol                                    0x4C928
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
	#define strrchr_symbol                                   0x4D94C

	#define spin_lock_irqsave_ex_symbol                      0x26D720
	#define spin_unlock_irqrestore_ex_symbol                 0x26D6F4

	#define create_process_common_symbol                     0x26B4BC
	#define create_process_base_symbol                       0x26AB78
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x26B2C8

	#define ppu_thread_create_symbol                         0x13EC4
	#define ppu_thread_exit_symbol                           0x13F7C
	#define ppu_thread_join_symbol                           0x13FD0
	#define ppu_thread_delay_symbol                          0x287A0
	#define create_kernel_thread_symbol                      0x24B1C
	#define create_user_thread_symbol                        0x25258
	#define create_user_thread2_symbol                       0x2507C
	#define start_thread_symbol                              0x23D48
	#define run_thread_symbol                                0x23578
	#define self_threading_symbol                            0x25864
	#define register_thread_symbol                           0x2678D4
	#define allocate_user_stack_symbol                       0x2680BC
	#define deallocate_user_stack_symbol                     0x268024

	#define mutex_create_symbol                              0x13638
	#define mutex_destroy_symbol                             0x135D0
	#define mutex_lock_symbol                                0x135C8
	#define mutex_lock_ex_symbol                             0x1DB58
	#define mutex_trylock_symbol                             0x135C4
	#define mutex_unlock_symbol                              0x135C0

	#define cond_create_symbol                               0x137A4
	#define cond_destroy_symbol                              0x13754
	#define cond_wait_symbol                                 0x1374C
	#define cond_wait_ex_symbol                              0x1F144
	#define cond_signal_symbol                               0x13728
	#define cond_signal_all_symbol                           0x13704

	#define semaphore_initialize_symbol                      0x30C50
	#define semaphore_wait_ex_symbol                         0x30958
	#define semaphore_trywait_symbol                         0x30540
	#define semaphore_post_ex_symbol                         0x3068C

	#define event_port_create_symbol                         0x13074
	#define event_port_destroy_symbol                        0x134DC
	#define event_port_connect_symbol                        0x13554
	#define event_port_disconnect_symbol                     0x13480
	#define event_port_send_symbol                           0x1306C
	#define event_port_send_ex_symbol                        0x2B200

	#define event_queue_create_symbol                        0x1337C
	#define event_queue_destroy_symbol                       0x13304
	#define event_queue_receive_symbol                       0x13148
	#define event_queue_tryreceive_symbol                    0x13214

	#define cellFsOpen_symbol                                0x297888
	#define cellFsClose_symbol                               0x2976F0
	#define cellFsRead_symbol                                0x29782C
	#define cellFsWrite_symbol                               0x297798
	#define cellFsLseek_symbol                               0x296E20
	#define cellFsStat_symbol                                0x2970A4
	#define cellFsUtime_symbol                               0x298B90
	#define cellFsUnlink_internal_symbol                     0x19C644
	#define cellFsRename_internal_symbol                     0x1970FC

	#define cellFsUtilMount_symbol                           0x296C00
	#define cellFsUtilUmount_symbol                          0x296BD4
	#define cellFsUtilNewfs_symbol                           0x298628

	#define pathdup_from_user_symbol                         0x29C86C
	#define open_path_symbol                                 0x2975C0
	#define open_fs_object_symbol                            0x18A968
	#define close_fs_object_symbol                           0x1898A4

	#define storage_get_device_info_symbol                   0x279A88
	#define storage_get_device_config_symbol                 0x278F18
	#define storage_open_symbol                              0x279498
	#define storage_close_symbol                             0x279288
	#define storage_read_symbol                              0x2787F8
	#define storage_write_symbol                             0x2786C8
	#define storage_send_device_command_symbol               0x278384
	#define storage_map_io_memory_symbol                     0x279944
	#define storage_unmap_io_memory_symbol                   0x279810
	#define new_medium_listener_object_symbol                0x974BC
	#define delete_medium_listener_object_symbol             0x98CF4
	#define set_medium_event_callbacks_symbol                0x99058

	#define cellUsbdRegisterLdd_symbol                       0x260208
	#define cellUsbdUnregisterLdd_symbol                     0x2601B8
	#define cellUsbdScanStaticDescriptor_symbol              0x261408
	#define cellUsbdOpenPipe_symbol                          0x2614B8
	#define cellUsbdClosePipe_symbol                         0x261468
	#define cellUsbdControlTransfer_symbol                   0x26136C
	#define cellUsbdBulkTransfer_symbol                      0x2612EC

	#define decrypt_func_symbol                              0x3496C
	#define lv1_call_99_wrapper_symbol                       0x4EEA4
	#define modules_verification_symbol                      0x58AB4
	#define authenticate_program_segment_symbol              0x5A90C

	#define prx_load_module_symbol                           0x88C00
	#define prx_start_module_symbol                          0x878CC
	#define prx_stop_module_symbol                           0x88CA4
	#define prx_unload_module_symbol                         0x87600
	#define prx_get_module_info_symbol                       0x87088
	#define prx_get_module_id_by_address_symbol              0x86F98
	#define prx_get_module_id_by_name_symbol                 0x86FE8
	#define prx_get_module_list_symbol                       0x87108
	#define load_module_by_fd_symbol                         0x88230
	#define parse_sprx_symbol                                0x85FB4
	#define open_prx_object_symbol                           0x7F4F4
	#define close_prx_object_symbol                          0x7FE04
	#define lock_prx_mutex_symbol                            0x86F40
	#define unlock_prx_mutex_symbol                          0x86F4C

	#define extend_kstack_symbol                             0x700A0

	#define get_pseudo_random_number_symbol                  0x228178
	#define md5_reset_symbol                                 0x161E18
	#define md5_update_symbol                                0x1628B8
	#define md5_final_symbol                                 0x162A38
	#define ss_get_open_psid_symbol                          0x22A660
	#define update_mgr_read_eeprom_symbol                    0x223A70
	#define update_mgr_write_eeprom_symbol                   0x2239B8
	#define update_mgr_if_get_token_symbol                   0x2253D4

	#define ss_params_get_update_status_symbol               0x50AB0

	#define sm_get_temperature_symbol                        0x263534
	#define sm_get_fan_policy_symbol                         0x2628C8
	#define sm_set_fan_policy_symbol                         0x2646C0
	#define sm_get_temperature_patch                         0xC6A4
	#define sm_get_fan_policy_patch                          0x9E38
	#define sm_set_fan_policy_patch                          0xA334

	#define SHA1_init_symbol                                 0x2CE610
	#define SHA1_update_symbol                               0x2CE670
	#define SHA1_final_symbol                                0x2CE824
	#define aescbccfb_dec_symbol                             0x2CCB04
	#define aescbccfb_enc_symbol                             0x2CC8B4
	#define get_path_by_fd_symbol                            0x29C108

	#define ECDSA_1                                          0x59DC0
	#define ECDSA_2                                          0x2D2ABC
	#define ECDSA_FLAG                                       0x474A80
	#define sysmem_obj                                       0x474C38
	#define qa_eeprom_offset                                 0x48C06

	#define syscall_table_symbol                             0x363B60
	#define syscall_call_offset                              0x275B8C

	#define read_bdvd0_symbol                                0x1A4614
	#define read_bdvd1_symbol                                0x1A6240
	#define read_bdvd2_symbol                                0x1B33F8

	#define storage_internal_get_device_object_symbol        0x277E3C

	#define hid_mgr_read_usb_symbol                          0x10243C
	#define hid_mgr_read_bt_symbol                           0xFC314

	#define bt_set_controller_info_internal_symbol           0xF0380

	#define device_event_port_send_call                      0x281FF4
	#define device_event_port_send_call_restore              0x7810D94B

	#define ss_pid_call_1                                    0x213294

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7F3E8
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x88A9C

	#define shutdown_copy_params_call                        0xAACC
	#define shutdown_copy_params_call_restore                0xB94F0048

	#define fsloop_open_call                                 0x297A20
	#define fsloop_close_call                                0x297A70
	#define fsloop_read_call                                 0x297AB0

	#define shutdown_patch_offset                            0xAAB8
	#define module_sdk_version_patch_offset                  0x267104
	#define module_add_parameter_to_parse_sprxpatch_offset   0x8830C

	#define user_thread_prio_patch                           0x203F8
	#define user_thread_prio_patch2                          0x20408

	#define lic_patch                                        0x5622C
	#define lic_patch_restore                                0x48240E79
	#define ode_patch                                        0x2275EC
	#define fix_80010009                                     0x5A6E0
	#define fix_8001003D                                     0x56588
	#define fix_8001003E                                     0x5664C
	#define PATCH_JUMP                                       0x56600

	#define io_rtoc_entry_1                                  0x25B0
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0

	#define storage_rtoc_entry_1                             0x1DD0

	#define device_event_rtoc_entry_1                        0x2040

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x3680

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x250FC
	#define permissions_exception2                           0xC3290
	#define permissions_exception3                           0x204CC

	#define patch_data1_offset                               0x3E2DC0
	#define patch_func2                                      0x59D80
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDABC1
	#define patch_func8_offset1                              0x564B0
	#define patch_func8_offset2                              0x56610
	#define patch_func8_offset2_restore                      0x48216F41
	#define patch_func9_offset                               0x5A6F4
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x37DDB0

	#define mmapper_flags_temp_patch                         0x70F74

	#define rsx_syscall_check                                0x7E4C
	#define unk_func2_unregister_service                     0x99188
	#define unk_func3_unregister_service                     0x9DC1C

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E3000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52D00000056000
	#define PS1_EMU_HASH                                     0xCC2850000009A000
	#define PS1_NETEMU_HASH                                  0xCC28B000000BE000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037C000
	#define BDP_BDVD_HASH                                    0xCC28D00000436000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000041000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F470000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA440C

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4B14
	#define ps2tonet_size_patch                              0xC4B08
	#define vmode_patch_offset                               0x445630
	#define psp_drm_patch1                                   0x24265C
	#define psp_drm_patch2                                   0x2430FC
	#define psp_drm_patch3                                   0x242D38
	#define psp_drm_patch4                                   0x243544
	#define psp_drm_patchA                                   0x242778
	#define psp_drm_patchB                                   0x243018
	#define psp_drm_patchC                                   0x2421B0
	#define psp_drm_patchD                                   0x242760
	#define psp_drm_patchE                                   0x242764
	#define psp_drm_patchF                                   0x243130
	#define psp_extra_drm_patch                              0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDD97C
	#define app_home_offset                                  0x250C80

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68324

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23ED0
	#define ps_region_error_offset                           0x68C4
	#define remote_play_offset                               0x5FC4
	#define ps2_nonbw_offset3                                0x17004

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EA28
	#define patch2_nas                                       0x2EB8C
	#define patch3_nas                                       0x1F848

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F78C
	#define pspemu_path_offset                               0x4B638
	#define psptrans_path_offset                             0x4B6C8

	/* download_plugin */
	#define elf_patch1_download                              0x42E0C
	#define elf_patch2_download                              0x42E14
	#define elf_patch3_download                              0x4D7D8
	#define elf_patch4_download                              0x4E5F8
	#define elf_patch5_download                              0x4E618
	#define elf_patch6_download                              0x4E6E8

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x7A448
	#define elf_patch2_autodownload                          0x7A450

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                        0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH                 0xDE52C00000056000
	#define GAME_EXT_PLUGIN_REBUG_HASH                       0xCC2680000001E000
	#define dex_ps2_nonbw_offset                             0xDDD8C
	#define dex_ps2_nonbw_offset2                            0x68264
	#define dex_ps2_nonbw_offset3                            0x172F4
	#define dex_ps2tonet_patch                               0xCA060
	#define dex_ps2tonet_size_patch                          0xCA054
	#define dex_vmode_patch_offset                           0x44D224
	#define dex_psp_drm_patch1                               0x249E84
	#define dex_psp_drm_patch2                               0x24A924
	#define dex_psp_drm_patch3                               0x24A560
	#define dex_psp_drm_patch4                               0x24AD6C
	#define dex_psp_drm_patchA                               0x249FA0
	#define dex_psp_drm_patchB                               0x24A840
	#define dex_psp_drm_patchC                               0x2499D8
	#define dex_psp_drm_patchD                               0x249F88
	#define dex_psp_drm_patchE                               0x249F8C
	#define dex_psp_drm_patchF                               0x24A958
	#define dex_psp_extra_drm_patch                          0x0
#endif

#ifdef FIRMWARE_470D

	#define FIRMWARE_VERSION                                 0x470

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000004098B0ULL
		#define PS3MAPI_IDPS_2                               0x800000000049CAF4ULL
		#define PS3MAPI_PSID                                 0x800000000049CB0CULL
	#endif
	#define FIRMWARE_DEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x375850

	#define create_kernel_object_symbol                      0x125F4
	#define destroy_kernel_object_symbol                     0x11F58
	#define destroy_shared_kernel_object_symbol              0x118CC
	#define open_kernel_object_symbol                        0x12C44
	#define open_shared_kernel_object_symbol                 0x12A54
	#define close_kernel_object_handle_symbol                0x12074

	#define alloc_symbol                                     0x681F0
	#define dealloc_symbol                                   0x6862C
	#define copy_to_user_symbol                              0xFEB0
	#define copy_from_user_symbol                            0x100CC
	#define copy_to_process_symbol                           0xFF68
	#define copy_from_process_symbol                         0xFD78
	#define process_read_memory_symbol                       0x26E76C
	#define process_write_memory_symbol                      0x26E5E0
	#define page_allocate_symbol                             0x63D60
	#define page_free_symbol                                 0x637C4
	#define page_export_to_proc_symbol                       0x63EFC
	#define page_unexport_from_proc_symbol                   0x636B8
	#define kernel_ea_to_lpar_addr_symbol                    0x73C98
	#define process_ea_to_lpar_addr_ex_symbol                0x7B838
	#define set_pte_symbol                                   0x61D5C
	#define map_process_memory_symbol                        0x7B344
	#define panic_symbol                                     0x275428

	#define memcpy_symbol                                    0x82A04
	#define memset_symbol                                    0x51010
	#define memcmp_symbol                                    0x50320
	#define memchr_symbol                                    0x502D0
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
	#define strrchr_symbol                                   0x512F4

	#define spin_lock_irqsave_ex_symbol                      0x2755F8
	#define spin_unlock_irqrestore_ex_symbol                 0x2755CC

	#define create_process_common_symbol                     0x2723F0
	#define create_process_base_symbol                       0x271A88
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x2721F0

	#define ppu_thread_create_symbol                         0x145F8
	#define ppu_thread_exit_symbol                           0x146B0
	#define ppu_thread_join_symbol                           0x14704
	#define ppu_thread_delay_symbol                          0x2A6E4
	#define create_kernel_thread_symbol                      0x267CC
	#define create_user_thread_symbol                        0x26F08
	#define create_user_thread2_symbol                       0x26D2C
	#define start_thread_symbol                              0x25864
	#define run_thread_symbol                                0x25028
	#define self_threading_symbol                            0x27514
	#define register_thread_symbol                           0x26E1F8
	#define allocate_user_stack_symbol                       0x26E9E0
	#define deallocate_user_stack_symbol                     0x26E948

	#define mutex_create_symbol                              0x13C88
	#define mutex_destroy_symbol                             0x13C20
	#define mutex_lock_symbol                                0x13C18
	#define mutex_lock_ex_symbol                             0x1F608
	#define mutex_trylock_symbol                             0x13C14
	#define mutex_unlock_symbol                              0x13C10

	#define cond_create_symbol                               0x13DF4
	#define cond_destroy_symbol                              0x13DA4
	#define cond_wait_symbol                                 0x13D9C
	#define cond_wait_ex_symbol                              0x20BF4
	#define cond_signal_symbol                               0x13D78
	#define cond_signal_all_symbol                           0x13D54

	#define semaphore_initialize_symbol                      0x34570
	#define semaphore_wait_ex_symbol                         0x34278
	#define semaphore_trywait_symbol                         0x33E60
	#define semaphore_post_ex_symbol                         0x33FAC

	#define event_port_create_symbol                         0x136C4
	#define event_port_destroy_symbol                        0x13B2C
	#define event_port_connect_symbol                        0x13BA4
	#define event_port_disconnect_symbol                     0x13AD0
	#define event_port_send_symbol                           0x136BC
	#define event_port_send_ex_symbol                        0x2D2C4

	#define event_queue_create_symbol                        0x139CC
	#define event_queue_destroy_symbol                       0x13954
	#define event_queue_receive_symbol                       0x13798
	#define event_queue_tryreceive_symbol                    0x13864

	#define cellFsOpen_symbol                                0x2B2748
	#define cellFsClose_symbol                               0x2B25B0
	#define cellFsRead_symbol                                0x2B26EC
	#define cellFsWrite_symbol                               0x2B2658
	#define cellFsLseek_symbol                               0x2B1EAC
	#define cellFsStat_symbol                                0x2B1F64
	#define cellFsUtime_symbol                               0x2B38D4
	#define cellFsUnlink_internal_symbol                     0x1A29D0
	#define cellFsRename_internal_symbol                     0x19D488

	#define cellFsUtilMount_symbol                           0x2B1C20
	#define cellFsUtilUmount_symbol                          0x2B1BF4
	#define cellFsUtilNewfs_symbol                           0x2B356C

	#define pathdup_from_user_symbol                         0x2B7A0C
	#define open_path_symbol                                 0x2B2480
	#define open_fs_object_symbol                            0x190CF4
	#define close_fs_object_symbol                           0x18FC30

	#define storage_get_device_info_symbol                   0x28C988
	#define storage_get_device_config_symbol                 0x28B014
	#define storage_open_symbol                              0x28CBB0
	#define storage_close_symbol                             0x28B39C
	#define storage_read_symbol                              0x28A318
	#define storage_write_symbol                             0x28A1E8
	#define storage_send_device_command_symbol               0x289E38
	#define storage_map_io_memory_symbol                     0x28C834
	#define storage_unmap_io_memory_symbol                   0x28C6F0
	#define new_medium_listener_object_symbol                0x9CC2C
	#define delete_medium_listener_object_symbol             0x9E464
	#define set_medium_event_callbacks_symbol                0x9E7C8

	#define cellUsbdRegisterLdd_symbol                       0x2666E4
	#define cellUsbdUnregisterLdd_symbol                     0x266694
	#define cellUsbdScanStaticDescriptor_symbol              0x2678E4
	#define cellUsbdOpenPipe_symbol                          0x267994
	#define cellUsbdClosePipe_symbol                         0x267944
	#define cellUsbdControlTransfer_symbol                   0x267848
	#define cellUsbdBulkTransfer_symbol                      0x2677C8

	#define decrypt_func_symbol                              0x3828C
	#define lv1_call_99_wrapper_symbol                       0x5284C
	#define modules_verification_symbol                      0x5C484
	#define authenticate_program_segment_symbol              0x5E2DC

	#define prx_load_module_symbol                           0x8D304
	#define prx_start_module_symbol                          0x8BFD0
	#define prx_stop_module_symbol                           0x8D3A8
	#define prx_unload_module_symbol                         0x8BD04
	#define prx_get_module_info_symbol                       0x8B6FC
	#define prx_get_module_id_by_address_symbol              0x8B60C
	#define prx_get_module_id_by_name_symbol                 0x8B65C
	#define prx_get_module_list_symbol                       0x8B77C
	#define load_module_by_fd_symbol                         0x8C934
	#define parse_sprx_symbol                                0x8A628
	#define open_prx_object_symbol                           0x835D0
	#define close_prx_object_symbol                          0x83EE0
	#define lock_prx_mutex_symbol                            0x8B5B4
	#define unlock_prx_mutex_symbol                          0x8B5C0

	#define extend_kstack_symbol                             0x73BF0

	#define get_pseudo_random_number_symbol                  0x22E654
	#define md5_reset_symbol                                 0x1681A4
	#define md5_update_symbol                                0x168C44
	#define md5_final_symbol                                 0x168DC4
	#define ss_get_open_psid_symbol                          0x230B3C
	#define update_mgr_read_eeprom_symbol                    0x229F34
	#define update_mgr_write_eeprom_symbol                   0x229E68
	#define update_mgr_if_get_token_symbol                   0x22B8B0

	#define ss_params_get_update_status_symbol               0x54458

	#define sm_get_temperature_symbol                        0x269A10
	#define sm_get_fan_policy_symbol                         0x268DA4
	#define sm_set_fan_policy_symbol                         0x26AD6C
	#define sm_get_temperature_patch                         0xC724
	#define sm_get_fan_policy_patch                          0x9EB8
	#define sm_set_fan_policy_patch                          0xA3B4

	#define SHA1_init_symbol                                 0x2F00D8
	#define SHA1_update_symbol                               0x2F0138
	#define SHA1_final_symbol                                0x2F02EC
	#define aescbccfb_dec_symbol                             0x2EE5CC
	#define aescbccfb_enc_symbol                             0x2EE37C
	#define get_path_by_fd_symbol                            0x2B72A8

	#define ECDSA_1                                          0x5D790
	#define ECDSA_2                                          0x2F4584
	#define ECDSA_FLAG                                       0x49CA80
	#define sysmem_obj                                       0x49CC38
	#define qa_eeprom_offset                                 0x4C56A

	#define syscall_table_symbol                             0x38A368
	#define syscall_call_offset                              0x27DE6C

	#define read_bdvd0_symbol                                0x1AAAC4
	#define read_bdvd1_symbol                                0x1AC6F0
	#define read_bdvd2_symbol                                0x1B98A8

	#define storage_internal_get_device_object_symbol        0x2898F0

	#define hid_mgr_read_usb_symbol                          0x107F40
	#define hid_mgr_read_bt_symbol                           0x101E18

	#define bt_set_controller_info_internal_symbol           0xF5E84

	#define device_event_port_send_call                      0x296B84
	#define device_event_port_send_call_restore              0x38CBD74B

	#define ss_pid_call_1                                    0x219744

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x834C4
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x8D1A0

	#define shutdown_copy_params_call                        0xAB4C
	#define shutdown_copy_params_call_restore                0x81550048

	#define fsloop_open_call                                 0x2B28E0
	#define fsloop_close_call                                0x2B2930
	#define fsloop_read_call                                 0x2B2970

	#define shutdown_patch_offset                            0xAB38
	#define module_sdk_version_patch_offset                  0x26D820
	#define module_add_parameter_to_parse_sprxpatch_offset   0x8CA10

	#define user_thread_prio_patch                           0x21EA8
	#define user_thread_prio_patch2                          0x21EB8

	#define lic_patch                                        0x59BFC
	#define lic_patch_restore                                0x48258369
	#define ode_patch                                        0x22DAC8
	#define fix_80010009                                     0x5E0B0
	#define fix_8001003D                                     0x59F58
	#define fix_8001003E                                     0x5A01C
	#define PATCH_JUMP                                       0x59FD0

	#define io_rtoc_entry_1                                  0x2EB8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65C0

	#define storage_rtoc_entry_1                             0x22A8

	#define device_event_rtoc_entry_1                        0x2630

	#define time_rtoc_entry_1                               -0x75E0
	#define time_rtoc_entry_2                               -0x75E8

	#define thread_rtoc_entry_1                             -0x7660

	#define process_rtoc_entry_1                            -0x77A0

	#define bt_rtoc_entry_1                                 -0x3558

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x26DAC
	#define permissions_exception2                           0xC8A00
	#define permissions_exception3                           0x21F7C

	#define patch_data1_offset                               0x4098C0
	#define patch_func2                                      0x5D750
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDAB11
	#define patch_func8_offset1                              0x59E80
	#define patch_func8_offset2                              0x59FE0
	#define patch_func8_offset2_restore                      0x4821B449
	#define patch_func9_offset                               0x5E0C4
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x3A48B0

	#define mmapper_flags_temp_patch                         0x74C04

	#define rsx_syscall_check                                0x7E4C
	#define unk_func2_unregister_service                     0x9E8F8
	#define unk_func3_unregister_service                     0xA338C

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E7000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52C00000056000
	#define PS1_EMU_HASH                                     0xCC2850000009A000
	#define PS1_NETEMU_HASH                                  0xCC28B000000BE000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037C000
	#define BDP_BDVD_HASH                                    0xCC28D00000436000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000041000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F4800000020000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA440C

	/* vsh */
	#define vsh_text_size                                    0x6C0000
	#define ps2tonet_patch                                   0xCA060
	#define ps2tonet_size_patch                              0xCA054
	#define vmode_patch_offset                               0x44D224
	#define psp_drm_patch1                                   0x249E84
	#define psp_drm_patch2                                   0x24A924
	#define psp_drm_patch3                                   0x24A560
	#define psp_drm_patch4                                   0x24AD6C
	#define psp_drm_patchA                                   0x249FA0
	#define psp_drm_patchB                                   0x24A840
	#define psp_drm_patchC                                   0x2499D8
	#define psp_drm_patchD                                   0x249F88
	#define psp_drm_patchE                                   0x249F8C
	#define psp_drm_patchF                                   0x24A958
	#define psp_extra_drm_patch                              0x0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDDD8C
	#define app_home_offset                                  0x251830

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68264

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x240EC
	#define ps_region_error_offset                           0x6880
	#define remote_play_offset                               0x5FC4
	#define ps2_nonbw_offset3                                0x172F4

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EE48
	#define patch2_nas                                       0x2EFAC
	#define patch3_nas                                       0x1FB08

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x20234
	#define pspemu_path_offset                               0x4C810
	#define psptrans_path_offset                             0x4C8C8

	/* download_plugin */
	#define elf_patch1_download                              0x42DA0
	#define elf_patch2_download                              0x42DA8
	#define elf_patch3_download                              0x4D6F8
	#define elf_patch4_download                              0x4E518
	#define elf_patch5_download                              0x4E538
	#define elf_patch6_download                              0x4E608

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x7A2F8
	#define elf_patch2_autodownload                          0x7A300

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* CEX */
	#define cex_ps2tonet_patch                               0xC4B14
	#define cex_ps2tonet_size_patch                          0xC4B08
	#define cex_vmode_patch_offset                           0x445630
	#define cex_psp_drm_patch1                               0x24265C
	#define cex_psp_drm_patch2                               0x2430FC
	#define cex_psp_drm_patch3                               0x242D38
	#define cex_psp_drm_patch4                               0x243544
	#define cex_psp_drm_patchA                               0x242778
	#define cex_psp_drm_patchB                               0x243018
	#define cex_psp_drm_patchC                               0x2421B0
	#define cex_psp_drm_patchD                               0x242760
	#define cex_psp_drm_patchE                               0x242764
	#define cex_psp_drm_patchF                               0x243130
	#define cex_psp_extra_drm_patch                          0x0
#endif

#ifdef FIRMWARE_475C

	#define FIRMWARE_VERSION                                 0x475

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2E30ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474AF4ULL
		#define PS3MAPI_PSID                                 0x8000000000474B0CULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x34FBB0

	#define create_kernel_object_symbol                      0x11FB0
	#define destroy_kernel_object_symbol                     0x11914
	#define destroy_shared_kernel_object_symbol              0x11288
	#define open_kernel_object_symbol                        0x12600
	#define open_shared_kernel_object_symbol                 0x12410
	#define close_kernel_object_handle_symbol                0x11A30

	#define alloc_symbol                                     0x64824
	#define dealloc_symbol                                   0x64C60
	#define copy_to_user_symbol                              0xF86C
	#define copy_from_user_symbol                            0xFA88
	#define copy_to_process_symbol                           0xF924
	#define copy_from_process_symbol                         0xF734
	#define process_read_memory_symbol                       0x267EC0
	#define process_write_memory_symbol                      0x267D34
	#define page_allocate_symbol                             0x60394
	#define page_free_symbol                                 0x5FDF8
	#define page_export_to_proc_symbol                       0x60530
	#define page_unexport_from_proc_symbol                   0x5FCEC
	#define kernel_ea_to_lpar_addr_symbol                    0x7014C
	#define process_ea_to_lpar_addr_ex_symbol                0x77760
	#define set_pte_symbol                                   0x5E390
	#define map_process_memory_symbol                        0x7726C
	#define panic_symbol                                     0x26D5C8

	#define memcpy_symbol                                    0x7E92C
	#define memset_symbol                                    0x4D66C
	#define memcmp_symbol                                    0x4C97C
	#define memchr_symbol                                    0x4C92C
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
	#define strrchr_symbol                                   0x4D950

	#define spin_lock_irqsave_ex_symbol                      0x26D798
	#define spin_unlock_irqrestore_ex_symbol                 0x26D76C

	#define create_process_common_symbol                     0x26B534
	#define create_process_base_symbol                       0x26ABF0
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x26B340

	#define ppu_thread_create_symbol                         0x13EC8
	#define ppu_thread_exit_symbol                           0x13F80
	#define ppu_thread_join_symbol                           0x13FD4
	#define ppu_thread_delay_symbol                          0x287A4
	#define create_kernel_thread_symbol                      0x24B20
	#define create_user_thread_symbol                        0x2525C
	#define create_user_thread2_symbol                       0x25080
	#define start_thread_symbol                              0x23D4C
	#define run_thread_symbol                                0x2357C
	#define self_threading_symbol                            0x25868
	#define register_thread_symbol                           0x26794C
	#define allocate_user_stack_symbol                       0x268134
	#define deallocate_user_stack_symbol                     0x26809C

	#define mutex_create_symbol                              0x1363C
	#define mutex_destroy_symbol                             0x135D4
	#define mutex_lock_symbol                                0x135CC
	#define mutex_lock_ex_symbol                             0x1DB5C
	#define mutex_trylock_symbol                             0x135C8
	#define mutex_unlock_symbol                              0x135C4

	#define cond_create_symbol                               0x137A8
	#define cond_destroy_symbol                              0x13758
	#define cond_wait_symbol                                 0x13750
	#define cond_wait_ex_symbol                              0x1F148
	#define cond_signal_symbol                               0x1372C
	#define cond_signal_all_symbol                           0x13708

	#define semaphore_initialize_symbol                      0x30C54
	#define semaphore_wait_ex_symbol                         0x3095C
	#define semaphore_trywait_symbol                         0x30544
	#define semaphore_post_ex_symbol                         0x30690

	#define event_port_create_symbol                         0x13078
	#define event_port_destroy_symbol                        0x134E0
	#define event_port_connect_symbol                        0x13558
	#define event_port_disconnect_symbol                     0x13484
	#define event_port_send_symbol                           0x13070
	#define event_port_send_ex_symbol                        0x2B204

	#define event_queue_create_symbol                        0x13380
	#define event_queue_destroy_symbol                       0x13308
	#define event_queue_receive_symbol                       0x1314C
	#define event_queue_tryreceive_symbol                    0x13218

	#define cellFsOpen_symbol                                0x297900
	#define cellFsClose_symbol                               0x297768
	#define cellFsRead_symbol                                0x2978A4
	#define cellFsWrite_symbol                               0x297810
	#define cellFsLseek_symbol                               0x296E98
	#define cellFsStat_symbol                                0x29711C
	#define cellFsUtime_symbol                               0x298C08
	#define cellFsUnlink_internal_symbol                     0x19C64C
	#define cellFsRename_internal_symbol                     0x197104

	#define cellFsUtilMount_symbol                           0x296C78
	#define cellFsUtilUmount_symbol                          0x298654
	#define cellFsUtilNewfs_symbol                           0x2986A0

	#define pathdup_from_user_symbol                         0x29C8E4
	#define open_path_symbol                                 0x297638
	#define open_fs_object_symbol                            0x18A970
	#define close_fs_object_symbol                           0x1898AC

	#define storage_get_device_info_symbol                   0x279B00
	#define storage_get_device_config_symbol                 0x278F90
	#define storage_open_symbol                              0x279510
	#define storage_close_symbol                             0x279300
	#define storage_read_symbol                              0x278870
	#define storage_write_symbol                             0x278740
	#define storage_send_device_command_symbol               0x2783FC
	#define storage_map_io_memory_symbol                     0x2799BC
	#define storage_unmap_io_memory_symbol                   0x279888
	#define new_medium_listener_object_symbol                0x974C4
	#define delete_medium_listener_object_symbol             0x98CFC
	#define set_medium_event_callbacks_symbol                0x99060

	#define cellUsbdRegisterLdd_symbol                       0x26027C
	#define cellUsbdUnregisterLdd_symbol                     0x26022C
	#define cellUsbdScanStaticDescriptor_symbol              0x26147C
	#define cellUsbdOpenPipe_symbol                          0x26152C
	#define cellUsbdClosePipe_symbol                         0x2614DC
	#define cellUsbdControlTransfer_symbol                   0x2613E0
	#define cellUsbdBulkTransfer_symbol                      0x261360

	#define decrypt_func_symbol                              0x34970
	#define lv1_call_99_wrapper_symbol                       0x4EEA8
	#define modules_verification_symbol                      0x58AB8
	#define authenticate_program_segment_symbol              0x5A910

	#define prx_load_module_symbol                           0x88C04
	#define prx_start_module_symbol                          0x878D0
	#define prx_stop_module_symbol                           0x88CA8
	#define prx_unload_module_symbol                         0x87604
	#define prx_get_module_info_symbol                       0x8708C
	#define prx_get_module_id_by_address_symbol              0x86F9C
	#define prx_get_module_id_by_name_symbol                 0x86FEC
	#define prx_get_module_list_symbol                       0x8710C
	#define load_module_by_fd_symbol                         0x88234
	#define parse_sprx_symbol                                0x85FB8
	#define open_prx_object_symbol                           0x7F4F8
	#define close_prx_object_symbol                          0x7FE08
	#define lock_prx_mutex_symbol                            0x86F44
	#define unlock_prx_mutex_symbol                          0x86F50

	#define extend_kstack_symbol                             0x700A4

	#define get_pseudo_random_number_symbol                  0x228180
	#define md5_reset_symbol                                 0x161E20
	#define md5_update_symbol                                0x1628C0
	#define md5_final_symbol                                 0x162A40
	#define ss_get_open_psid_symbol                          0x22A668
	#define update_mgr_read_eeprom_symbol                    0x223A78
	#define update_mgr_write_eeprom_symbol                   0x2239C0
	#define update_mgr_if_get_token_symbol                   0x2253DC

	#define ss_params_get_update_status_symbol               0x50AB4

	#define sm_get_temperature_symbol                        0x2635A8
	#define sm_get_fan_policy_symbol                         0x26293C
	#define sm_set_fan_policy_symbol                         0x264734
	#define sm_get_temperature_patch                         0xC6A8
	#define sm_get_fan_policy_patch                          0x9E38
	#define sm_set_fan_policy_patch                          0xA334

	#define SHA1_init_symbol                                 0x2CE688
	#define SHA1_update_symbol                               0x2CE6E8
	#define SHA1_final_symbol                                0x2CE89C
	#define aescbccfb_dec_symbol                             0x2CCB7C
	#define aescbccfb_enc_symbol                             0x2CC92C
	#define get_path_by_fd_symbol                            0x29C180

	#define ECDSA_1                                          0x59DC4
	#define ECDSA_2                                          0x2D2B34
	#define ECDSA_FLAG                                       0x474A80
	#define sysmem_obj                                       0x474C38
	#define qa_eeprom_offset                                 0x48C0A

	#define syscall_table_symbol                             0x363BE0
	#define syscall_call_offset                              0x275C04

	#define read_bdvd0_symbol                                0x1A461C
	#define read_bdvd1_symbol                                0x1A6248
	#define read_bdvd2_symbol                                0x1B3400

	#define storage_internal_get_device_object_symbol        0x277EB4

	#define hid_mgr_read_usb_symbol                          0x102444
	#define hid_mgr_read_bt_symbol                           0xFC31C

	#define bt_set_controller_info_internal_symbol           0xF0388

	#define device_event_port_send_call                      0x28206C
	#define device_event_port_send_call_restore              0xBCE82748

	#define ss_pid_call_1                                    0x21329C

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7F3EC
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x88AA0

	#define shutdown_copy_params_call                        0xAACC
	#define shutdown_copy_params_call_restore                0x15644F48

	#define fsloop_open_call                                 0x297A98
	#define fsloop_close_call                                0x297AE8
	#define fsloop_read_call                                 0x297B28

	#define shutdown_patch_offset                            0xAAB8
	#define module_sdk_version_patch_offset                  0x26717C
	#define module_add_parameter_to_parse_sprxpatch_offset   0x88310

	#define user_thread_prio_patch                           0x203FC
	#define user_thread_prio_patch2                          0x2040C

	#define lic_patch                                        0x56230
	#define lic_patch_restore                                0x48240EED
	#define ode_patch                                        0x2275F4
	#define fix_80010009                                     0x5A6E4
	#define fix_8001003D                                     0x5658C
	#define fix_8001003E                                     0x56650
	#define PATCH_JUMP                                       0x56604

	#define io_rtoc_entry_1                                  0x25B8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0

	#define storage_rtoc_entry_1                             0x1DD8

	#define device_event_rtoc_entry_1                        0x2048

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x3680

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x25100
	#define permissions_exception2                           0xC3298
	#define permissions_exception3                           0x204D0

	#define patch_data1_offset                               0x3E2E40
	#define patch_func2                                      0x59D84
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x484A6661
	#define patch_func8_offset1                              0x564B4
	#define patch_func8_offset2                              0x56614
	#define patch_func8_offset2_restore                      0x48216FB5
	#define patch_func9_offset                               0x5A6F8
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x37DE30

	#define mmapper_flags_temp_patch                         0x70F78

	#define rsx_syscall_check                                0x5011A8
	#define unk_func2_unregister_service                     0x99190
	#define unk_func3_unregister_service                     0x9DC24

	/* lv1 */
	#define vsh_pos_in_ram                                   0x510000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E3000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52D00000056000
	#define PS1_EMU_HASH                                     0xCC2850000009A000
	#define PS1_NETEMU_HASH                                  0xCC28B000000BE000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037C000
	#define BDP_BDVD_HASH                                    0xCC28D00000436000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000041000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F470000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA440C

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4B14
	#define ps2tonet_size_patch                              0xC4B08
	#define vmode_patch_offset                               0x445BEC
	#define psp_drm_patch1                                   0x24277C
	#define psp_drm_patch2                                   0x24321C
	#define psp_drm_patch3                                   0x242E58
	#define psp_drm_patch4                                   0x243664
	#define psp_drm_patchA                                   0x242898
	#define psp_drm_patchB                                   0x243138
	#define psp_drm_patchC                                   0x2422D0
	#define psp_drm_patchD                                   0x242880
	#define psp_drm_patchE                                   0x242884
	#define psp_drm_patchF                                   0x243250
	#define psp_extra_drm_patch                              0x2452AC

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDD97C
	#define app_home_offset                                  0x250C80

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68324

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23ED0
	#define ps_region_error_offset                           0x68C4
	#define remote_play_offset                               0x5FC4
	#define ps2_nonbw_offset3                                0x17004

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EA30
	#define patch2_nas                                       0x2EB94
	#define patch3_nas                                       0x1F850

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F78C
	#define pspemu_path_offset                               0x4B688
	#define psptrans_path_offset                             0x4B718

	/* download_plugin */
	#define elf_patch1_download                              0x42E0C
	#define elf_patch2_download                              0x42E14
	#define elf_patch3_download                              0x4D7D8
	#define elf_patch4_download                              0x4E5F8
	#define elf_patch5_download                              0x4E618
	#define elf_patch6_download                              0x4E6E8

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x7A448
	#define elf_patch2_autodownload                          0x7A450

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                        0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH                 0xDE52C00000056000
	#define GAME_EXT_PLUGIN_REBUG_HASH                       0xCC2680000001E000
	#define dex_ps2_nonbw_offset                             0xDDD8C
	#define dex_ps2_nonbw_offset2                            0x68264
	#define dex_ps2_nonbw_offset3                            0x172F4
	#define dex_ps2tonet_patch                               0xCA060
	#define dex_ps2tonet_size_patch                          0xCA054
	#define dex_vmode_patch_offset                           0x44D7E0
	#define dex_psp_drm_patch1                               0x249FA4
	#define dex_psp_drm_patch2                               0x24AA44
	#define dex_psp_drm_patch3                               0x24A680
	#define dex_psp_drm_patch4                               0x24AE8C
	#define dex_psp_drm_patchA                               0x24A0C0
	#define dex_psp_drm_patchB                               0x24A960
	#define dex_psp_drm_patchC                               0x249AF8
	#define dex_psp_drm_patchD                               0x24A0A8
	#define dex_psp_drm_patchE                               0x24A0AC
	#define dex_psp_drm_patchF                               0x24AA78
	#define dex_psp_extra_drm_patch                          0x24CAD4
#endif

#ifdef FIRMWARE_475D

	#define FIRMWARE_VERSION                                 0x475

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x8000000000409930ULL
		#define PS3MAPI_IDPS_2                               0x800000000049CAF4ULL
		#define PS3MAPI_PSID                                 0x800000000049CB0CULL
	#endif
	#define FIRMWARE_DEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x3758E0

	#define create_kernel_object_symbol                      0x125F8
	#define destroy_kernel_object_symbol                     0x11F5C
	#define destroy_shared_kernel_object_symbol              0x118D0
	#define open_kernel_object_symbol                        0x12C48
	#define open_shared_kernel_object_symbol                 0x12A58
	#define close_kernel_object_handle_symbol                0x12078

	#define alloc_symbol                                     0x681F4
	#define dealloc_symbol                                   0x68630
	#define copy_to_user_symbol                              0xFEB4
	#define copy_from_user_symbol                            0x100D0
	#define copy_to_process_symbol                           0xFF6C
	#define copy_from_process_symbol                         0xFD7C
	#define process_read_memory_symbol                       0x26E7E4
	#define process_write_memory_symbol                      0x26E658
	#define page_allocate_symbol                             0x63D64
	#define page_free_symbol                                 0x637C8
	#define page_export_to_proc_symbol                       0x63F00
	#define page_unexport_from_proc_symbol                   0x636BC
	#define kernel_ea_to_lpar_addr_symbol                    0x73C9C
	#define process_ea_to_lpar_addr_ex_symbol                0x7B83C
	#define set_pte_symbol                                   0x61D60
	#define map_process_memory_symbol                        0x7B348
	#define panic_symbol                                     0x2754A0

	#define memcpy_symbol                                    0x82A08
	#define memset_symbol                                    0x51014
	#define memcmp_symbol                                    0x50324
	#define memchr_symbol                                    0x502D4
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
	#define strrchr_symbol                                   0x512F8

	#define spin_lock_irqsave_ex_symbol                      0x275670
	#define spin_unlock_irqrestore_ex_symbol                 0x275644

	#define create_process_common_symbol                     0x272468
	#define create_process_base_symbol                       0x271B00
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x272268

	#define ppu_thread_create_symbol                         0x145FC
	#define ppu_thread_exit_symbol                           0x146B4
	#define ppu_thread_join_symbol                           0x14708
	#define ppu_thread_delay_symbol                          0x2A6E8
	#define create_kernel_thread_symbol                      0x267D0
	#define create_user_thread_symbol                        0x26F0C
	#define create_user_thread2_symbol                       0x26D30
	#define start_thread_symbol                              0x25868
	#define run_thread_symbol                                0x2502C
	#define self_threading_symbol                            0x27518
	#define register_thread_symbol                           0x26E270
	#define allocate_user_stack_symbol                       0x26EA58
	#define deallocate_user_stack_symbol                     0x26E9C0

	#define mutex_create_symbol                              0x13C8C
	#define mutex_destroy_symbol                             0x13C24
	#define mutex_lock_symbol                                0x13C1C
	#define mutex_lock_ex_symbol                             0x1F60C
	#define mutex_trylock_symbol                             0x13C18
	#define mutex_unlock_symbol                              0x13C14

	#define cond_create_symbol                               0x13DF8
	#define cond_destroy_symbol                              0x13DA8
	#define cond_wait_symbol                                 0x13DA0
	#define cond_wait_ex_symbol                              0x20BF8
	#define cond_signal_symbol                               0x13D7C
	#define cond_signal_all_symbol                           0x13D58

	#define semaphore_initialize_symbol                      0x34574
	#define semaphore_wait_ex_symbol                         0x3427C
	#define semaphore_trywait_symbol                         0x33E64
	#define semaphore_post_ex_symbol                         0x33FB0

	#define event_port_create_symbol                         0x136C8
	#define event_port_destroy_symbol                        0x13B30
	#define event_port_connect_symbol                        0x13BA8
	#define event_port_disconnect_symbol                     0x13AD4
	#define event_port_send_symbol                           0x136C0
	#define event_port_send_ex_symbol                        0x2D2C8

	#define event_queue_create_symbol                        0x139D0
	#define event_queue_destroy_symbol                       0x13958
	#define event_queue_receive_symbol                       0x1379C
	#define event_queue_tryreceive_symbol                    0x13868

	#define cellFsOpen_symbol                                0x2B27C0
	#define cellFsClose_symbol                               0x2B2628
	#define cellFsRead_symbol                                0x2B2764
	#define cellFsWrite_symbol                               0x2B26D0
	#define cellFsLseek_symbol                               0x2B1F24
	#define cellFsStat_symbol                                0x2B1FDC
	#define cellFsUtime_symbol                               0x2B394C
	#define cellFsUnlink_internal_symbol                     0x1A29D8
	#define cellFsRename_internal_symbol                     0x19D490

	#define cellFsUtilMount_symbol                           0x2B1C98
	#define cellFsUtilUmount_symbol                          0x2B1C6C
	#define cellFsUtilNewfs_symbol                           0x2B35E4

	#define pathdup_from_user_symbol                         0x2B7A84
	#define open_path_symbol                                 0x2B24F8
	#define open_fs_object_symbol                            0x190CFC
	#define close_fs_object_symbol                           0x18FC38

	#define storage_get_device_info_symbol                   0x28CA00
	#define storage_get_device_config_symbol                 0x28B08C
	#define storage_open_symbol                              0x28CC28
	#define storage_close_symbol                             0x28B414
	#define storage_read_symbol                              0x28A390
	#define storage_write_symbol                             0x28A260
	#define storage_send_device_command_symbol               0x289EB0
	#define storage_map_io_memory_symbol                     0x28C8AC
	#define storage_unmap_io_memory_symbol                   0x28C768
	#define new_medium_listener_object_symbol                0x9CC34
	#define delete_medium_listener_object_symbol             0x9E46C
	#define set_medium_event_callbacks_symbol                0x9E7D0

	#define cellUsbdRegisterLdd_symbol                       0x266758
	#define cellUsbdUnregisterLdd_symbol                     0x266708
	#define cellUsbdScanStaticDescriptor_symbol              0x267958
	#define cellUsbdOpenPipe_symbol                          0x267A08
	#define cellUsbdClosePipe_symbol                         0x2679B8
	#define cellUsbdControlTransfer_symbol                   0x2678BC
	#define cellUsbdBulkTransfer_symbol                      0x26783C

	#define decrypt_func_symbol                              0x38290
	#define lv1_call_99_wrapper_symbol                       0x52850
	#define modules_verification_symbol                      0x5C488
	#define authenticate_program_segment_symbol              0x5E2E0

	#define prx_load_module_symbol                           0x8D308
	#define prx_start_module_symbol                          0x8BFD4
	#define prx_stop_module_symbol                           0x8D3AC
	#define prx_unload_module_symbol                         0x8BD08
	#define prx_get_module_info_symbol                       0x8B700
	#define prx_get_module_id_by_address_symbol              0x8B610
	#define prx_get_module_id_by_name_symbol                 0x8B660
	#define prx_get_module_list_symbol                       0x8B780
	#define load_module_by_fd_symbol                         0x8C938
	#define parse_sprx_symbol                                0x8A62C
	#define open_prx_object_symbol                           0x835D4
	#define close_prx_object_symbol                          0x83EE4
	#define lock_prx_mutex_symbol                            0x8B5B8
	#define unlock_prx_mutex_symbol                          0x8B5C4

	#define extend_kstack_symbol                             0x73BF4

	#define get_pseudo_random_number_symbol                  0x22E65C
	#define md5_reset_symbol                                 0x1681AC
	#define md5_update_symbol                                0x168C4C
	#define md5_final_symbol                                 0x168DCC
	#define ss_get_open_psid_symbol                          0x230B44
	#define update_mgr_read_eeprom_symbol                    0x229F3C
	#define update_mgr_write_eeprom_symbol                   0x229E70
	#define update_mgr_if_get_token_symbol                   0x22B8B8

	#define ss_params_get_update_status_symbol               0x5445C

	#define sm_get_temperature_symbol                        0x269A84
	#define sm_get_fan_policy_symbol                         0x268E18
	#define sm_set_fan_policy_symbol                         0x26ADE0
	#define sm_get_temperature_patch                         0xC728
	#define sm_get_fan_policy_patch                          0x9EB8
	#define sm_set_fan_policy_patch                          0xA3B4

	#define SHA1_init_symbol                                 0x2F0150
	#define SHA1_update_symbol                               0x2F01B0
	#define SHA1_final_symbol                                0x2F0364
	#define aescbccfb_dec_symbol                             0x2EE644
	#define aescbccfb_enc_symbol                             0x2EE3F4
	#define get_path_by_fd_symbol                            0x2B7320

	#define ECDSA_1                                          0x5D794
	#define ECDSA_2                                          0x2F45FC
	#define ECDSA_FLAG                                       0x49CA80
	#define sysmem_obj                                       0x49CC38
	#define qa_eeprom_offset                                 0x4C56E

	#define syscall_table_symbol                             0x38A3E8
	#define syscall_call_offset                              0x27DEE4

	#define read_bdvd0_symbol                                0x1AAACC
	#define read_bdvd1_symbol                                0x1AC6F8
	#define read_bdvd2_symbol                                0x1B98B0

	#define storage_internal_get_device_object_symbol        0x289968

	#define hid_mgr_read_usb_symbol                          0x107F48
	#define hid_mgr_read_bt_symbol                           0x101E20

	#define bt_set_controller_info_internal_symbol           0xF5E8C

	#define device_event_port_send_call                      0x296BFC
	#define device_event_port_send_call_restore              0xC4CAD74B

	#define ss_pid_call_1                                    0x21974C

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x834C8
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x8D1A4

	#define shutdown_copy_params_call                        0xAB4C
	#define shutdown_copy_params_call_restore                0x85550048

	#define fsloop_open_call                                 0x2B2958
	#define fsloop_close_call                                0x2B29A8
	#define fsloop_read_call                                 0x2B29E8

	#define shutdown_patch_offset                            0xAB38
	#define module_sdk_version_patch_offset                  0x26D898
	#define module_add_parameter_to_parse_sprxpatch_offset   0x8CA14

	#define user_thread_prio_patch                           0x21EAC
	#define user_thread_prio_patch2                          0x21EBC

	#define lic_patch                                        0x59C00
	#define lic_patch_restore                                0x482583DD
	#define ode_patch                                        0x22DAD0
	#define fix_80010009                                     0x5E0B4
	#define fix_8001003D                                     0x59F5C
	#define fix_8001003E                                     0x5A020
	#define PATCH_JUMP                                       0x59FD4

	#define io_rtoc_entry_1                                  0x2EC0
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65C0

	#define storage_rtoc_entry_1                             0x22B0

	#define device_event_rtoc_entry_1                        0x2638

	#define time_rtoc_entry_1                               -0x75E0
	#define time_rtoc_entry_2                               -0x75E8

	#define thread_rtoc_entry_1                             -0x7660

	#define process_rtoc_entry_1                            -0x77A0

	#define bt_rtoc_entry_1                                 -0x3558

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x26DB0
	#define permissions_exception2                           0xC8A08
	#define permissions_exception3                           0x21F80

	#define patch_data1_offset                               0x409940
	#define patch_func2                                      0x5D754
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDAB11
	#define patch_func8_offset1                              0x59E84
	#define patch_func8_offset2                              0x59FE4
	#define patch_func8_offset2_restore                      0x4821B4BD
	#define patch_func9_offset                               0x5E0C8
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x3A4930

	#define mmapper_flags_temp_patch                         0x74C08

	#define rsx_syscall_check                                0x7E4C
	#define unk_func2_unregister_service                     0x9E900
	#define unk_func3_unregister_service                     0xA3394

	/* lv1 */
	#define vsh_pos_in_ram                                   0x510000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E7000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52C00000056000
	#define PS1_EMU_HASH                                     0xCC2850000009A000
	#define PS1_NETEMU_HASH                                  0xCC28B000000BE000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037C000
	#define BDP_BDVD_HASH                                    0xCC28D00000436000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000041000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F4800000020000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA440C

	/* vsh */
	#define vsh_text_size                                    0x6C0000
	#define ps2tonet_patch                                   0xCA060
	#define ps2tonet_size_patch                              0xCA054
	#define vmode_patch_offset                               0x44D7E0
	#define psp_drm_patch1                                   0x249FA4
	#define psp_drm_patch2                                   0x24AA44
	#define psp_drm_patch3                                   0x24A680
	#define psp_drm_patch4                                   0x24AE8C
	#define psp_drm_patchA                                   0x24A0C0
	#define psp_drm_patchB                                   0x24A960
	#define psp_drm_patchC                                   0x249AF8
	#define psp_drm_patchD                                   0x24A0A8
	#define psp_drm_patchE                                   0x24A0AC
	#define psp_drm_patchF                                   0x24AA78
	#define psp_extra_drm_patch                              0x24CAD4

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDDD8C
	#define app_home_offset                                  0x251830

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68264

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x240EC
	#define ps_region_error_offset                           0x6880
	#define remote_play_offset                               0x5FC4
	#define ps2_nonbw_offset3                                0x172F4

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EE48
	#define patch2_nas                                       0x2EFAC
	#define patch3_nas                                       0x1FB08

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x20234
	#define pspemu_path_offset                               0x4C868
	#define psptrans_path_offset                             0x4C920

	/* download_plugin */
	#define elf_patch1_download                              0x42DA0
	#define elf_patch2_download                              0x42DA8
	#define elf_patch3_download                              0x4D6F8
	#define elf_patch4_download                              0x4E518
	#define elf_patch5_download                              0x4E538
	#define elf_patch6_download                              0x4E608

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x7A2F8
	#define elf_patch2_autodownload                          0x7A300

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* CEX */
	#define cex_ps2tonet_patch                               0xC4B14
	#define cex_ps2tonet_size_patch                          0xC4B08
	#define cex_vmode_patch_offset                           0x445BEC
	#define cex_psp_drm_patch1                               0x24277C
	#define cex_psp_drm_patch2                               0x24321C
	#define cex_psp_drm_patch3                               0x242E58
	#define cex_psp_drm_patch4                               0x243664
	#define cex_psp_drm_patchA                               0x242898
	#define cex_psp_drm_patchB                               0x243138
	#define cex_psp_drm_patchC                               0x2422D0
	#define cex_psp_drm_patchD                               0x242880
	#define cex_psp_drm_patchE                               0x242884
	#define cex_psp_drm_patchF                               0x243250
	#define cex_psp_extra_drm_patch                          0x2452AC
#endif

#ifdef FIRMWARE_476C

	#define FIRMWARE_VERSION                                 0x476

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2E30ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474AF4ULL
		#define PS3MAPI_PSID                                 0x8000000000474B0CULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x34FBB0

	#define create_kernel_object_symbol                      0x11FB0
	#define destroy_kernel_object_symbol                     0x11914
	#define destroy_shared_kernel_object_symbol              0x11288
	#define open_kernel_object_symbol                        0x12600
	#define open_shared_kernel_object_symbol                 0x12410
	#define close_kernel_object_handle_symbol                0x11A30

	#define alloc_symbol                                     0x64824
	#define dealloc_symbol                                   0x64C60
	#define copy_to_user_symbol                              0xF86C
	#define copy_from_user_symbol                            0xFA88
	#define copy_to_process_symbol                           0xF924
	#define copy_from_process_symbol                         0xF734
	#define process_read_memory_symbol                       0x267EC0
	#define process_write_memory_symbol                      0x267D34
	#define page_allocate_symbol                             0x60394
	#define page_free_symbol                                 0x5FDF8
	#define page_export_to_proc_symbol                       0x60530
	#define page_unexport_from_proc_symbol                   0x5FCEC
	#define kernel_ea_to_lpar_addr_symbol                    0x7014C
	#define process_ea_to_lpar_addr_ex_symbol                0x77760
	#define set_pte_symbol                                   0x5E390
	#define map_process_memory_symbol                        0x7726C
	#define panic_symbol                                     0x26D5C8

	#define memcpy_symbol                                    0x7E92C
	#define memset_symbol                                    0x4D66C
	#define memcmp_symbol                                    0x4C97C
	#define memchr_symbol                                    0x4C92C
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
	#define strrchr_symbol                                   0x4D950

	#define spin_lock_irqsave_ex_symbol                      0x26D798
	#define spin_unlock_irqrestore_ex_symbol                 0x26D76C

	#define create_process_common_symbol                     0x26B534
	#define create_process_base_symbol                       0x26ABF0
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x26B340

	#define ppu_thread_create_symbol                         0x13EC8
	#define ppu_thread_exit_symbol                           0x13F80
	#define ppu_thread_join_symbol                           0x13FD4
	#define ppu_thread_delay_symbol                          0x287A4
	#define create_kernel_thread_symbol                      0x24B20
	#define create_user_thread_symbol                        0x2525C
	#define create_user_thread2_symbol                       0x25080
	#define start_thread_symbol                              0x23D4C
	#define run_thread_symbol                                0x2357C
	#define self_threading_symbol                            0x25868
	#define register_thread_symbol                           0x26794C
	#define allocate_user_stack_symbol                       0x268134
	#define deallocate_user_stack_symbol                     0x26809C

	#define mutex_create_symbol                              0x1363C
	#define mutex_destroy_symbol                             0x135D4
	#define mutex_lock_symbol                                0x135CC
	#define mutex_lock_ex_symbol                             0x1DB5C
	#define mutex_trylock_symbol                             0x135C8
	#define mutex_unlock_symbol                              0x135C4

	#define cond_create_symbol                               0x137A8
	#define cond_destroy_symbol                              0x13758
	#define cond_wait_symbol                                 0x13750
	#define cond_wait_ex_symbol                              0x1F148
	#define cond_signal_symbol                               0x1372C
	#define cond_signal_all_symbol                           0x13708

	#define semaphore_initialize_symbol                      0x30C54
	#define semaphore_wait_ex_symbol                         0x3095C
	#define semaphore_trywait_symbol                         0x30544
	#define semaphore_post_ex_symbol                         0x30690

	#define event_port_create_symbol                         0x13078
	#define event_port_destroy_symbol                        0x134E0
	#define event_port_connect_symbol                        0x13558
	#define event_port_disconnect_symbol                     0x13484
	#define event_port_send_symbol                           0x13070
	#define event_port_send_ex_symbol                        0x2B204

	#define event_queue_create_symbol                        0x13380
	#define event_queue_destroy_symbol                       0x13308
	#define event_queue_receive_symbol                       0x1314C
	#define event_queue_tryreceive_symbol                    0x13218

	#define cellFsOpen_symbol                                0x297900
	#define cellFsClose_symbol                               0x297768
	#define cellFsRead_symbol                                0x2978A4
	#define cellFsWrite_symbol                               0x297810
	#define cellFsLseek_symbol                               0x296E98
	#define cellFsStat_symbol                                0x29711C
	#define cellFsUtime_symbol                               0x298C08
	#define cellFsUnlink_internal_symbol                     0x19C64C
	#define cellFsRename_internal_symbol                     0x197104

	#define cellFsUtilMount_symbol                           0x296C78
	#define cellFsUtilUmount_symbol                          0x298654
	#define cellFsUtilNewfs_symbol                           0x2986A0

	#define pathdup_from_user_symbol                         0x29C8E4
	#define open_path_symbol                                 0x297638
	#define open_fs_object_symbol                            0x18A970
	#define close_fs_object_symbol                           0x1898AC

	#define storage_get_device_info_symbol                   0x279B00
	#define storage_get_device_config_symbol                 0x278F90
	#define storage_open_symbol                              0x279510
	#define storage_close_symbol                             0x279300
	#define storage_read_symbol                              0x278870
	#define storage_write_symbol                             0x278740
	#define storage_send_device_command_symbol               0x2783FC
	#define storage_map_io_memory_symbol                     0x2799BC
	#define storage_unmap_io_memory_symbol                   0x279888
	#define new_medium_listener_object_symbol                0x974C4
	#define delete_medium_listener_object_symbol             0x98CFC
	#define set_medium_event_callbacks_symbol                0x99060

	#define cellUsbdRegisterLdd_symbol                       0x26027C
	#define cellUsbdUnregisterLdd_symbol                     0x26022C
	#define cellUsbdScanStaticDescriptor_symbol              0x26147C
	#define cellUsbdOpenPipe_symbol                          0x26152C
	#define cellUsbdClosePipe_symbol                         0x2614DC
	#define cellUsbdControlTransfer_symbol                   0x2613E0
	#define cellUsbdBulkTransfer_symbol                      0x261360

	#define decrypt_func_symbol                              0x34970
	#define lv1_call_99_wrapper_symbol                       0x4EEA8
	#define modules_verification_symbol                      0x58AB8
	#define authenticate_program_segment_symbol              0x5A910

	#define prx_load_module_symbol                           0x88C04
	#define prx_start_module_symbol                          0x878D0
	#define prx_stop_module_symbol                           0x88CA8
	#define prx_unload_module_symbol                         0x87604
	#define prx_get_module_info_symbol                       0x8708C
	#define prx_get_module_id_by_address_symbol              0x86F9C
	#define prx_get_module_id_by_name_symbol                 0x86FEC
	#define prx_get_module_list_symbol                       0x8710C
	#define load_module_by_fd_symbol                         0x88234
	#define parse_sprx_symbol                                0x85FB8
	#define open_prx_object_symbol                           0x7F4F8
	#define close_prx_object_symbol                          0x7FE08
	#define lock_prx_mutex_symbol                            0x86F44
	#define unlock_prx_mutex_symbol                          0x86F50

	#define extend_kstack_symbol                             0x700A4

	#define get_pseudo_random_number_symbol                  0x228180
	#define md5_reset_symbol                                 0x161E20
	#define md5_update_symbol                                0x1628C0
	#define md5_final_symbol                                 0x162A40
	#define ss_get_open_psid_symbol                          0x22A668
	#define update_mgr_read_eeprom_symbol                    0x223A78
	#define update_mgr_write_eeprom_symbol                   0x2239C0
	#define update_mgr_if_get_token_symbol                   0x2253DC

	#define ss_params_get_update_status_symbol               0x50AB4

	#define sm_get_temperature_symbol                        0x2635A8
	#define sm_get_fan_policy_symbol                         0x26293C
	#define sm_set_fan_policy_symbol                         0x264734
	#define sm_get_temperature_patch                         0xC6A8
	#define sm_get_fan_policy_patch                          0x9E38
	#define sm_set_fan_policy_patch                          0xA334

	#define SHA1_init_symbol                                 0x2CE688
	#define SHA1_update_symbol                               0x2CE6E8
	#define SHA1_final_symbol                                0x2CE89C
	#define aescbccfb_dec_symbol                             0x2CCB7C
	#define aescbccfb_enc_symbol                             0x2CC92C
	#define get_path_by_fd_symbol                            0x29C180

	#define ECDSA_1                                          0x59DC4
	#define ECDSA_2                                          0x2D2B34
	#define ECDSA_FLAG                                       0x474A80
	#define sysmem_obj                                       0x474C38
	#define qa_eeprom_offset                                 0x48C0A

	#define syscall_table_symbol                             0x363BE0
	#define syscall_call_offset                              0x275C04

	#define read_bdvd0_symbol                                0x1A461C
	#define read_bdvd1_symbol                                0x1A6248
	#define read_bdvd2_symbol                                0x1B3400

	#define storage_internal_get_device_object_symbol        0x277EB4

	#define hid_mgr_read_usb_symbol                          0x102444
	#define hid_mgr_read_bt_symbol                           0xFC31C

	#define bt_set_controller_info_internal_symbol           0xF0388

	#define device_event_port_send_call                      0x28206C
	#define device_event_port_send_call_restore              0x410D94B

	#define ss_pid_call_1                                    0x21329C

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7F3EC
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x88AA0

	#define shutdown_copy_params_call                        0xAACC
	#define shutdown_copy_params_call_restore                0xBD4F0048

	#define fsloop_open_call                                 0x297A98
	#define fsloop_close_call                                0x297AE8
	#define fsloop_read_call                                 0x297B28

	#define shutdown_patch_offset                            0xAAB8
	#define module_sdk_version_patch_offset                  0x26717C
	#define module_add_parameter_to_parse_sprxpatch_offset   0x88310

	#define user_thread_prio_patch                           0x203FC
	#define user_thread_prio_patch2                          0x2040C

	#define lic_patch                                        0x56230
	#define lic_patch_restore                                0x48240EED
	#define ode_patch                                        0x2275F4
	#define fix_80010009                                     0x5A6E4
	#define fix_8001003D                                     0x5658C
	#define fix_8001003E                                     0x56650
	#define PATCH_JUMP                                       0x56604

	#define io_rtoc_entry_1                                  0x25B8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0

	#define storage_rtoc_entry_1                             0x1DD8

	#define device_event_rtoc_entry_1                        0x2048

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x3680

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x25100
	#define permissions_exception2                           0xC3298
	#define permissions_exception3                           0x204D0

	#define patch_data1_offset                               0x3E2E40
	#define patch_func2                                      0x59D84
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDABC1
	#define patch_func8_offset1                              0x564B4
	#define patch_func8_offset2                              0x56614
	#define patch_func8_offset2_restore                      0x48216FB5
	#define patch_func9_offset                               0x5A6F8
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x37DE30

	#define mmapper_flags_temp_patch                         0x70F78

	#define rsx_syscall_check                                0x7E4C
	#define unk_func2_unregister_service                     0x99190
	#define unk_func3_unregister_service                     0x9DC24

	/* lv1 */
	#define vsh_pos_in_ram                                   0x510000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E3000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52D00000056000
	#define PS1_EMU_HASH                                     0xCC2850000009A000
	#define PS1_NETEMU_HASH                                  0xCC28B000000BE000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037C000
	#define BDP_BDVD_HASH                                    0xCC28D00000436000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000041000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F470000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA440C

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4B14
	#define ps2tonet_size_patch                              0xC4B08
	#define vmode_patch_offset                               0x445BEC
	#define psp_drm_patch1                                   0x24277C
	#define psp_drm_patch2                                   0x24321C
	#define psp_drm_patch3                                   0x242E58
	#define psp_drm_patch4                                   0x243664
	#define psp_drm_patchA                                   0x242898
	#define psp_drm_patchB                                   0x243138
	#define psp_drm_patchC                                   0x2422D0
	#define psp_drm_patchD                                   0x242880
	#define psp_drm_patchE                                   0x242884
	#define psp_drm_patchF                                   0x243250
	#define psp_extra_drm_patch                              0x2452AC

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDD97C
	#define app_home_offset                                  0x250C80

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68324

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23ED0
	#define ps_region_error_offset                           0x68C4
	#define remote_play_offset                               0x5FC4
	#define ps2_nonbw_offset3                                0x17004

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EA30
	#define patch2_nas                                       0x2EB94
	#define patch3_nas                                       0x1F850

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F78C
	#define pspemu_path_offset                               0x4B688
	#define psptrans_path_offset                             0x4B718

	/* download_plugin */
	#define elf_patch1_download                              0x42E0C
	#define elf_patch2_download                              0x42E14
	#define elf_patch3_download                              0x4D7D8
	#define elf_patch4_download                              0x4E5F8
	#define elf_patch5_download                              0x4E618
	#define elf_patch6_download                              0x4E6E8

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x7A448
	#define elf_patch2_autodownload                          0x7A450

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                        0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH                 0xDE52C00000056000
	#define GAME_EXT_PLUGIN_REBUG_HASH                       0xCC2680000001E000
	#define dex_ps2_nonbw_offset                             0xDDD8C
	#define dex_ps2_nonbw_offset2                            0x68264
	#define dex_ps2_nonbw_offset3                            0x172F4
	#define dex_ps2tonet_patch                               0xCA060
	#define dex_ps2tonet_size_patch                          0xCA054
	#define dex_vmode_patch_offset                           0x44D7E0
	#define dex_psp_drm_patch1                               0x249FA4
	#define dex_psp_drm_patch2                               0x24AA44
	#define dex_psp_drm_patch3                               0x24A680
	#define dex_psp_drm_patch4                               0x24AE8C
	#define dex_psp_drm_patchA                               0x24A0C0
	#define dex_psp_drm_patchB                               0x24A960
	#define dex_psp_drm_patchC                               0x249AF8
	#define dex_psp_drm_patchD                               0x24A0A8
	#define dex_psp_drm_patchE                               0x24A0AC
	#define dex_psp_drm_patchF                               0x24AA78
	#define dex_psp_extra_drm_patch                          0x24CAD4
#endif

#ifdef FIRMWARE_476D

	#define FIRMWARE_VERSION                                 0x476

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x8000000000409930ULL
		#define PS3MAPI_IDPS_2                               0x800000000049CAF4ULL
		#define PS3MAPI_PSID                                 0x800000000049CB0CULL
	#endif
	#define FIRMWARE_DEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x3758E0

	#define create_kernel_object_symbol                      0x125F8
	#define destroy_kernel_object_symbol                     0x11F5C
	#define destroy_shared_kernel_object_symbol              0x118D0
	#define open_kernel_object_symbol                        0x12C48
	#define open_shared_kernel_object_symbol                 0x12A58
	#define close_kernel_object_handle_symbol                0x12078

	#define alloc_symbol                                     0x681F4
	#define dealloc_symbol                                   0x68630
	#define copy_to_user_symbol                              0xFEB4
	#define copy_from_user_symbol                            0x100D0
	#define copy_to_process_symbol                           0xFF6C
	#define copy_from_process_symbol                         0xFD7C
	#define process_read_memory_symbol                       0x26E7E4
	#define process_write_memory_symbol                      0x26E658
	#define page_allocate_symbol                             0x63D64
	#define page_free_symbol                                 0x637C8
	#define page_export_to_proc_symbol                       0x63F00
	#define page_unexport_from_proc_symbol                   0x636BC
	#define kernel_ea_to_lpar_addr_symbol                    0x73C9C
	#define process_ea_to_lpar_addr_ex_symbol                0x7B83C
	#define set_pte_symbol                                   0x61D60
	#define map_process_memory_symbol                        0x7B348
	#define panic_symbol                                     0x2754A0

	#define memcpy_symbol                                    0x82A08
	#define memset_symbol                                    0x51014
	#define memcmp_symbol                                    0x50324
	#define memchr_symbol                                    0x502D4
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
	#define strrchr_symbol                                   0x512F8

	#define spin_lock_irqsave_ex_symbol                      0x275670
	#define spin_unlock_irqrestore_ex_symbol                 0x275644

	#define create_process_common_symbol                     0x272468
	#define create_process_base_symbol                       0x271B00
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x272268

	#define ppu_thread_create_symbol                         0x145FC
	#define ppu_thread_exit_symbol                           0x146B4
	#define ppu_thread_join_symbol                           0x14708
	#define ppu_thread_delay_symbol                          0x2A6E8
	#define create_kernel_thread_symbol                      0x267D0
	#define create_user_thread_symbol                        0x26F0C
	#define create_user_thread2_symbol                       0x26D30
	#define start_thread_symbol                              0x25868
	#define run_thread_symbol                                0x2502C
	#define self_threading_symbol                            0x27518
	#define register_thread_symbol                           0x26E270
	#define allocate_user_stack_symbol                       0x26EA58
	#define deallocate_user_stack_symbol                     0x26E9C0

	#define mutex_create_symbol                              0x13C8C
	#define mutex_destroy_symbol                             0x13C24
	#define mutex_lock_symbol                                0x13C1C
	#define mutex_lock_ex_symbol                             0x1F60C
	#define mutex_trylock_symbol                             0x13C18
	#define mutex_unlock_symbol                              0x13C14

	#define cond_create_symbol                               0x13DF8
	#define cond_destroy_symbol                              0x13DA8
	#define cond_wait_symbol                                 0x13DA0
	#define cond_wait_ex_symbol                              0x20BF8
	#define cond_signal_symbol                               0x13D7C
	#define cond_signal_all_symbol                           0x13D58

	#define semaphore_initialize_symbol                      0x34574
	#define semaphore_wait_ex_symbol                         0x3427C
	#define semaphore_trywait_symbol                         0x33E64
	#define semaphore_post_ex_symbol                         0x33FB0

	#define event_port_create_symbol                         0x136C8
	#define event_port_destroy_symbol                        0x13B30
	#define event_port_connect_symbol                        0x13BA8
	#define event_port_disconnect_symbol                     0x13AD4
	#define event_port_send_symbol                           0x136C0
	#define event_port_send_ex_symbol                        0x2D2C8

	#define event_queue_create_symbol                        0x139D0
	#define event_queue_destroy_symbol                       0x13958
	#define event_queue_receive_symbol                       0x1379C
	#define event_queue_tryreceive_symbol                    0x13868

	#define cellFsOpen_symbol                                0x2B27C0
	#define cellFsClose_symbol                               0x2B2628
	#define cellFsRead_symbol                                0x2B2764
	#define cellFsWrite_symbol                               0x2B26D0
	#define cellFsLseek_symbol                               0x2B1F24
	#define cellFsStat_symbol                                0x2B1FDC
	#define cellFsUtime_symbol                               0x2B394C
	#define cellFsUnlink_internal_symbol                     0x1A29D8
	#define cellFsRename_internal_symbol                     0x19D490

	#define cellFsUtilMount_symbol                           0x2B1C98
	#define cellFsUtilUmount_symbol                          0x2B1C6C
	#define cellFsUtilNewfs_symbol                           0x2B35E4

	#define pathdup_from_user_symbol                         0x2B7A84
	#define open_path_symbol                                 0x2B24F8
	#define open_fs_object_symbol                            0x190CFC
	#define close_fs_object_symbol                           0x18FC38

	#define storage_get_device_info_symbol                   0x28CA00
	#define storage_get_device_config_symbol                 0x28B08C
	#define storage_open_symbol                              0x28CC28
	#define storage_close_symbol                             0x28B414
	#define storage_read_symbol                              0x28A390
	#define storage_write_symbol                             0x28A260
	#define storage_send_device_command_symbol               0x289EB0
	#define storage_map_io_memory_symbol                     0x28C8AC
	#define storage_unmap_io_memory_symbol                   0x28C768
	#define new_medium_listener_object_symbol                0x9CC34
	#define delete_medium_listener_object_symbol             0x9E46C
	#define set_medium_event_callbacks_symbol                0x9E7D0

	#define cellUsbdRegisterLdd_symbol                       0x266758
	#define cellUsbdUnregisterLdd_symbol                     0x266708
	#define cellUsbdScanStaticDescriptor_symbol              0x267958
	#define cellUsbdOpenPipe_symbol                          0x267A08
	#define cellUsbdClosePipe_symbol                         0x2679B8
	#define cellUsbdControlTransfer_symbol                   0x2678BC
	#define cellUsbdBulkTransfer_symbol                      0x26783C

	#define decrypt_func_symbol                              0x38290
	#define lv1_call_99_wrapper_symbol                       0x52850
	#define modules_verification_symbol                      0x5C488
	#define authenticate_program_segment_symbol              0x5E2E0

	#define prx_load_module_symbol                           0x8D308
	#define prx_start_module_symbol                          0x8BFD4
	#define prx_stop_module_symbol                           0x8D3AC
	#define prx_unload_module_symbol                         0x8BD08
	#define prx_get_module_info_symbol                       0x8B700
	#define prx_get_module_id_by_address_symbol              0x8B610
	#define prx_get_module_id_by_name_symbol                 0x8B660
	#define prx_get_module_list_symbol                       0x8B780
	#define load_module_by_fd_symbol                         0x8C938
	#define parse_sprx_symbol                                0x8A62C
	#define open_prx_object_symbol                           0x835D4
	#define close_prx_object_symbol                          0x83EE4
	#define lock_prx_mutex_symbol                            0x8B5B8
	#define unlock_prx_mutex_symbol                          0x8B5C4

	#define extend_kstack_symbol                             0x73BF4

	#define get_pseudo_random_number_symbol                  0x22E65C
	#define md5_reset_symbol                                 0x1681AC
	#define md5_update_symbol                                0x168C4C
	#define md5_final_symbol                                 0x168DCC
	#define ss_get_open_psid_symbol                          0x230B44
	#define update_mgr_read_eeprom_symbol                    0x229F3C
	#define update_mgr_write_eeprom_symbol                   0x229E70
	#define update_mgr_if_get_token_symbol                   0x22B8B8

	#define ss_params_get_update_status_symbol               0x5445C

	#define sm_get_temperature_symbol                        0x269A84
	#define sm_get_fan_policy_symbol                         0x268E18
	#define sm_set_fan_policy_symbol                         0x26ADE0
	#define sm_get_temperature_patch                         0xC728
	#define sm_get_fan_policy_patch                          0x9EB8
	#define sm_set_fan_policy_patch                          0xA3B4

	#define SHA1_init_symbol                                 0x2F0150
	#define SHA1_update_symbol                               0x2F01B0
	#define SHA1_final_symbol                                0x2F0364
	#define aescbccfb_dec_symbol                             0x2EE644
	#define aescbccfb_enc_symbol                             0x2EE3F4
	#define get_path_by_fd_symbol                            0x2B7320

	#define ECDSA_1                                          0x5D794
	#define ECDSA_2                                          0x2F45FC
	#define ECDSA_FLAG                                       0x49CA80
	#define sysmem_obj                                       0x49CC38
	#define qa_eeprom_offset                                 0x4C56E

	#define syscall_table_symbol                             0x38A3E8
	#define syscall_call_offset                              0x27DEE4

	#define read_bdvd0_symbol                                0x1AAACC
	#define read_bdvd1_symbol                                0x1AC6F8
	#define read_bdvd2_symbol                                0x1B98B0

	#define storage_internal_get_device_object_symbol        0x289968

	#define hid_mgr_read_usb_symbol                          0x107F48
	#define hid_mgr_read_bt_symbol                           0x101E20

	#define bt_set_controller_info_internal_symbol           0xF5E8C

	#define device_event_port_send_call                      0x296BFC
	#define device_event_port_send_call_restore              0xC4CAD74B

	#define ss_pid_call_1                                    0x21974C

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x834C8
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x8D1A4

	#define shutdown_copy_params_call                        0xAB4C
	#define shutdown_copy_params_call_restore                0x85550048

	#define fsloop_open_call                                 0x2B2958
	#define fsloop_close_call                                0x2B29A8
	#define fsloop_read_call                                 0x2B29E8

	#define shutdown_patch_offset                            0xAB38
	#define module_sdk_version_patch_offset                  0x26D898
	#define module_add_parameter_to_parse_sprxpatch_offset   0x8CA14

	#define user_thread_prio_patch                           0x21EAC
	#define user_thread_prio_patch2                          0x21EBC

	#define lic_patch                                        0x59C00
	#define lic_patch_restore                                0x482584B5
	#define ode_patch                                        0x22DAD0
	#define fix_80010009                                     0x5E0B4
	#define fix_8001003D                                     0x59F5C
	#define fix_8001003E                                     0x5A020
	#define PATCH_JUMP                                       0x59FD4

	#define io_rtoc_entry_1                                  0x2EC0
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65C0

	#define storage_rtoc_entry_1                             0x22B0

	#define device_event_rtoc_entry_1                        0x2638

	#define time_rtoc_entry_1                               -0x75E0
	#define time_rtoc_entry_2                               -0x75E8

	#define thread_rtoc_entry_1                             -0x7660

	#define process_rtoc_entry_1                            -0x77A0

	#define bt_rtoc_entry_1                                 -0x3558

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x26DB0
	#define permissions_exception2                           0xC8A08
	#define permissions_exception3                           0x21F80

	#define patch_data1_offset                               0x409940
	#define patch_func2                                      0x5D754
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDAB11
	#define patch_func8_offset1                              0x59E84
	#define patch_func8_offset2                              0x59FE4
	#define patch_func8_offset2_restore                      0x4821B4BD
	#define patch_func9_offset                               0x5E0C8
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x3A4930

	#define mmapper_flags_temp_patch                         0x74C08

	#define rsx_syscall_check                                0x7E4C
	#define unk_func2_unregister_service                     0x9E900
	#define unk_func3_unregister_service                     0xA3394

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E7000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52C00000056000
	#define PS1_EMU_HASH                                     0xCC2850000009A000
	#define PS1_NETEMU_HASH                                  0xCC28B000000BE000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037C000
	#define BDP_BDVD_HASH                                    0xCC28D00000436000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000041000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F4800000020000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA440C

	/* vsh */
	#define vsh_text_size                                    0x6C0000
	#define ps2tonet_patch                                   0xCA060
	#define ps2tonet_size_patch                              0xCA054
	#define vmode_patch_offset                               0x44D7E0
	#define psp_drm_patch1                                   0x249FA4
	#define psp_drm_patch2                                   0x24AA44
	#define psp_drm_patch3                                   0x24A680
	#define psp_drm_patch4                                   0x24AE8C
	#define psp_drm_patchA                                   0x24A0C0
	#define psp_drm_patchB                                   0x24A960
	#define psp_drm_patchC                                   0x249AF8
	#define psp_drm_patchD                                   0x24A0A8
	#define psp_drm_patchE                                   0x24A0AC
	#define psp_drm_patchF                                   0x24AA78
	#define psp_extra_drm_patch                              0x24CAD4

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDDD8C
	#define app_home_offset                                  0x251830

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68264

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x240EC
	#define ps_region_error_offset                           0x6880
	#define remote_play_offset                               0x5FC4
	#define ps2_nonbw_offset3                                0x172F4

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EE48
	#define patch2_nas                                       0x2EFAC
	#define patch3_nas                                       0x1FB08

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x20234
	#define pspemu_path_offset                               0x4C868
	#define psptrans_path_offset                             0x4C920

	/* download_plugin */
	#define elf_patch1_download                              0x42DA0
	#define elf_patch2_download                              0x42DA8
	#define elf_patch3_download                              0x4D6F8
	#define elf_patch4_download                              0x4E518
	#define elf_patch5_download                              0x4E538
	#define elf_patch6_download                              0x4E608

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x7A2F8
	#define elf_patch2_autodownload                          0x7A300

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* CEX */
	#define cex_ps2tonet_patch                               0xC4B14
	#define cex_ps2tonet_size_patch                          0xC4B08
	#define cex_vmode_patch_offset                           0x445BEC
	#define cex_psp_drm_patch1                               0x24277C
	#define cex_psp_drm_patch2                               0x24321C
	#define cex_psp_drm_patch3                               0x242E58
	#define cex_psp_drm_patch4                               0x243664
	#define cex_psp_drm_patchA                               0x242898
	#define cex_psp_drm_patchB                               0x243138
	#define cex_psp_drm_patchC                               0x2422D0
	#define cex_psp_drm_patchD                               0x242880
	#define cex_psp_drm_patchE                               0x242884
	#define cex_psp_drm_patchF                               0x243250
	#define cex_psp_extra_drm_patch                          0x2452AC
#endif

#ifdef FIRMWARE_478C

	#define FIRMWARE_VERSION                                 0x478

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2E30ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474AF4ULL
		#define PS3MAPI_PSID                                 0x8000000000474B0CULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x34FBB0

	#define create_kernel_object_symbol                      0x11FB0
	#define destroy_kernel_object_symbol                     0x11914
	#define destroy_shared_kernel_object_symbol              0x11288
	#define open_kernel_object_symbol                        0x12600
	#define open_shared_kernel_object_symbol                 0x12410
	#define close_kernel_object_handle_symbol                0x11A30

	#define alloc_symbol                                     0x64824
	#define dealloc_symbol                                   0x64C60
	#define copy_to_user_symbol                              0xF86C
	#define copy_from_user_symbol                            0xFA88
	#define copy_to_process_symbol                           0xF924
	#define copy_from_process_symbol                         0xF734
	#define process_read_memory_symbol                       0x267EC0
	#define process_write_memory_symbol                      0x267D34
	#define page_allocate_symbol                             0x60394
	#define page_free_symbol                                 0x5FDF8
	#define page_export_to_proc_symbol                       0x60530
	#define page_unexport_from_proc_symbol                   0x5FCEC
	#define kernel_ea_to_lpar_addr_symbol                    0x7014C
	#define process_ea_to_lpar_addr_ex_symbol                0x77760
	#define set_pte_symbol                                   0x5E390
	#define map_process_memory_symbol                        0x7726C
	#define panic_symbol                                     0x26D5C8

	#define memcpy_symbol                                    0x7E92C
	#define memset_symbol                                    0x4D66C
	#define memcmp_symbol                                    0x4C97C
	#define memchr_symbol                                    0x4C92C
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
	#define strrchr_symbol                                   0x4D950

	#define spin_lock_irqsave_ex_symbol                      0x26D798
	#define spin_unlock_irqrestore_ex_symbol                 0x26D76C

	#define create_process_common_symbol                     0x26B534
	#define create_process_base_symbol                       0x26ABF0
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x26B340

	#define ppu_thread_create_symbol                         0x13EC8
	#define ppu_thread_exit_symbol                           0x13F80
	#define ppu_thread_join_symbol                           0x13FD4
	#define ppu_thread_delay_symbol                          0x287A4
	#define create_kernel_thread_symbol                      0x24B20
	#define create_user_thread_symbol                        0x2525C
	#define create_user_thread2_symbol                       0x25080
	#define start_thread_symbol                              0x23D4C
	#define run_thread_symbol                                0x2357C
	#define self_threading_symbol                            0x25868
	#define register_thread_symbol                           0x26794C
	#define allocate_user_stack_symbol                       0x268134
	#define deallocate_user_stack_symbol                     0x26809C

	#define mutex_create_symbol                              0x1363C
	#define mutex_destroy_symbol                             0x135D4
	#define mutex_lock_symbol                                0x135CC
	#define mutex_lock_ex_symbol                             0x1DB5C
	#define mutex_trylock_symbol                             0x135C8
	#define mutex_unlock_symbol                              0x135C4

	#define cond_create_symbol                               0x137A8
	#define cond_destroy_symbol                              0x13758
	#define cond_wait_symbol                                 0x13750
	#define cond_wait_ex_symbol                              0x1F148
	#define cond_signal_symbol                               0x1372C
	#define cond_signal_all_symbol                           0x13708

	#define semaphore_initialize_symbol                      0x30C54
	#define semaphore_wait_ex_symbol                         0x3095C
	#define semaphore_trywait_symbol                         0x30544
	#define semaphore_post_ex_symbol                         0x30690

	#define event_port_create_symbol                         0x13078
	#define event_port_destroy_symbol                        0x134E0
	#define event_port_connect_symbol                        0x13558
	#define event_port_disconnect_symbol                     0x13484
	#define event_port_send_symbol                           0x13070
	#define event_port_send_ex_symbol                        0x2B204

	#define event_queue_create_symbol                        0x13380
	#define event_queue_destroy_symbol                       0x13308
	#define event_queue_receive_symbol                       0x1314C
	#define event_queue_tryreceive_symbol                    0x13218

	#define cellFsOpen_symbol                                0x297900
	#define cellFsClose_symbol                               0x297768
	#define cellFsRead_symbol                                0x2978A4
	#define cellFsWrite_symbol                               0x297810
	#define cellFsLseek_symbol                               0x296E98
	#define cellFsStat_symbol                                0x29711C
	#define cellFsUtime_symbol                               0x298C08
	#define cellFsUnlink_internal_symbol                     0x19C64C
	#define cellFsRename_internal_symbol                     0x197104

	#define cellFsUtilMount_symbol                           0x296C78
	#define cellFsUtilUmount_symbol                          0x298654
	#define cellFsUtilNewfs_symbol                           0x2986A0

	#define pathdup_from_user_symbol                         0x29C8E4
	#define open_path_symbol                                 0x297638
	#define open_fs_object_symbol                            0x18A970
	#define close_fs_object_symbol                           0x1898AC

	#define storage_get_device_info_symbol                   0x279B00
	#define storage_get_device_config_symbol                 0x278F90
	#define storage_open_symbol                              0x279510
	#define storage_close_symbol                             0x279300
	#define storage_read_symbol                              0x278870
	#define storage_write_symbol                             0x278740
	#define storage_send_device_command_symbol               0x2783FC
	#define storage_map_io_memory_symbol                     0x2799BC
	#define storage_unmap_io_memory_symbol                   0x279888
	#define new_medium_listener_object_symbol                0x974C4
	#define delete_medium_listener_object_symbol             0x98CFC
	#define set_medium_event_callbacks_symbol                0x99060

	#define cellUsbdRegisterLdd_symbol                       0x26027C
	#define cellUsbdUnregisterLdd_symbol                     0x26022C
	#define cellUsbdScanStaticDescriptor_symbol              0x26147C
	#define cellUsbdOpenPipe_symbol                          0x26152C
	#define cellUsbdClosePipe_symbol                         0x2614DC
	#define cellUsbdControlTransfer_symbol                   0x2613E0
	#define cellUsbdBulkTransfer_symbol                      0x261360

	#define decrypt_func_symbol                              0x34970
	#define lv1_call_99_wrapper_symbol                       0x4EEA8
	#define modules_verification_symbol                      0x58AB8
	#define authenticate_program_segment_symbol              0x5A910

	#define prx_load_module_symbol                           0x88C04
	#define prx_start_module_symbol                          0x878D0
	#define prx_stop_module_symbol                           0x88CA8
	#define prx_unload_module_symbol                         0x87604
	#define prx_get_module_info_symbol                       0x8708C
	#define prx_get_module_id_by_address_symbol              0x86F9C
	#define prx_get_module_id_by_name_symbol                 0x86FEC
	#define prx_get_module_list_symbol                       0x8710C
	#define load_module_by_fd_symbol                         0x88234
	#define parse_sprx_symbol                                0x85FB8
	#define open_prx_object_symbol                           0x7F4F8
	#define close_prx_object_symbol                          0x7FE08
	#define lock_prx_mutex_symbol                            0x86F44
	#define unlock_prx_mutex_symbol                          0x86F50

	#define extend_kstack_symbol                             0x700A4

	#define get_pseudo_random_number_symbol                  0x228180
	#define md5_reset_symbol                                 0x161E20
	#define md5_update_symbol                                0x1628C0
	#define md5_final_symbol                                 0x162A40
	#define ss_get_open_psid_symbol                          0x22A668
	#define update_mgr_read_eeprom_symbol                    0x223A78
	#define update_mgr_write_eeprom_symbol                   0x2239C0
	#define update_mgr_if_get_token_symbol                   0x2253DC

	#define ss_params_get_update_status_symbol               0x50AB4

	#define sm_get_temperature_symbol                        0x2635A8
	#define sm_get_fan_policy_symbol                         0x26293C
	#define sm_set_fan_policy_symbol                         0x264734
	#define sm_get_temperature_patch                         0xC6A8
	#define sm_get_fan_policy_patch                          0x9E38
	#define sm_set_fan_policy_patch                          0xA334

	#define SHA1_init_symbol                                 0x2CE688
	#define SHA1_update_symbol                               0x2CE6E8
	#define SHA1_final_symbol                                0x2CE89C
	#define aescbccfb_dec_symbol                             0x2CCB7C
	#define aescbccfb_enc_symbol                             0x2CC92C
	#define get_path_by_fd_symbol                            0x29C180

	#define ECDSA_1                                          0x59DC4
	#define ECDSA_2                                          0x2D2B34
	#define ECDSA_FLAG                                       0x474A80
	#define sysmem_obj                                       0x474C38
	#define qa_eeprom_offset                                 0x48C0A

	#define syscall_table_symbol                             0x363BE0
	#define syscall_call_offset                              0x275C04

	#define read_bdvd0_symbol                                0x1A461C
	#define read_bdvd1_symbol                                0x1A6248
	#define read_bdvd2_symbol                                0x1B3400

	#define storage_internal_get_device_object_symbol        0x277EB4

	#define hid_mgr_read_usb_symbol                          0x102444
	#define hid_mgr_read_bt_symbol                           0xFC31C

	#define bt_set_controller_info_internal_symbol           0xF0388

	#define device_event_port_send_call                      0x28206C
	#define device_event_port_send_call_restore              0xBCE82748

	#define ss_pid_call_1                                    0x21329C

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7F3EC
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x88AA0

	#define shutdown_copy_params_call                        0xAACC
	#define shutdown_copy_params_call_restore                0x15644F48

	#define fsloop_open_call                                 0x297A98
	#define fsloop_close_call                                0x297AE8
	#define fsloop_read_call                                 0x297B28

	#define shutdown_patch_offset                            0xAAB8
	#define module_sdk_version_patch_offset                  0x26717C
	#define module_add_parameter_to_parse_sprxpatch_offset   0x88310

	#define user_thread_prio_patch                           0x203FC
	#define user_thread_prio_patch2                          0x2040C

	#define lic_patch                                        0x56230
	#define lic_patch_restore                                0x48240EED
	#define ode_patch                                        0x2275F4
	#define fix_80010009                                     0x5A6E4
	#define fix_8001003D                                     0x5658C
	#define fix_8001003E                                     0x56650
	#define PATCH_JUMP                                       0x56604

	#define io_rtoc_entry_1                                  0x25B8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0

	#define storage_rtoc_entry_1                             0x1DD8

	#define device_event_rtoc_entry_1                        0x2048

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x3680

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x25100
	#define permissions_exception2                           0xC3298
	#define permissions_exception3                           0x204D0

	#define patch_data1_offset                               0x3E2E40
	#define patch_func2                                      0x59D84
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x484A6661
	#define patch_func8_offset1                              0x564B4
	#define patch_func8_offset2                              0x56614
	#define patch_func8_offset2_restore                      0x48216FB5
	#define patch_func9_offset                               0x5A6F8
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x37DE30

	#define mmapper_flags_temp_patch                         0x70F78

	#define rsx_syscall_check                                0x5011A8
	#define unk_func2_unregister_service                     0x99190
	#define unk_func3_unregister_service                     0x9DC24

	/* lv1 */
	#define vsh_pos_in_ram                                   0x510000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E2000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52D00000056000
	#define PS1_EMU_HASH                                     0xCC2850000009A000
	#define PS1_NETEMU_HASH                                  0xCC28B000000BE000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037C000
	#define BDP_BDVD_HASH                                    0xCC28D00000437000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000044000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F470000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA440C

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4B14
	#define ps2tonet_size_patch                              0xC4B08
	#define vmode_patch_offset                               0x442E5C
	#define psp_drm_patch1                                   0x242C74
	#define psp_drm_patch2                                   0x243714
	#define psp_drm_patch3                                   0x243350
	#define psp_drm_patch4                                   0x243B5C
	#define psp_drm_patchA                                   0x242D90
	#define psp_drm_patchB                                   0x243630
	#define psp_drm_patchC                                   0x2427C8
	#define psp_drm_patchD                                   0x242D78
	#define psp_drm_patchE                                   0x242D7C
	#define psp_drm_patchF                                   0x243748
	#define psp_extra_drm_patch                              0x2457A4

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDD9B4
	#define app_home_offset                                  0x2509F0

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68324

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23ED0
	#define ps_region_error_offset                           0x68C4
	#define remote_play_offset                               0x5FC4
	#define ps2_nonbw_offset3                                0x17004

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EA30
	#define patch2_nas                                       0x2EB94
	#define patch3_nas                                       0x1F850

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F78C
	#define pspemu_path_offset                               0x4B688
	#define psptrans_path_offset                             0x4B718

	/* download_plugin */
	#define elf_patch1_download                              0x42E0C
	#define elf_patch2_download                              0x42E14
	#define elf_patch3_download                              0x4D7D8
	#define elf_patch4_download                              0x4E5F8
	#define elf_patch5_download                              0x4E618
	#define elf_patch6_download                              0x4E6E8

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x82614
	#define elf_patch2_autodownload                          0x8261C

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                        0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH                 0xDE52C00000056000
	#define GAME_EXT_PLUGIN_REBUG_HASH                       0xCC2680000001E000
	#define dex_ps2_nonbw_offset                             0xDDDC4
	#define dex_ps2_nonbw_offset2                            0x68264
	#define dex_ps2_nonbw_offset3                            0x172F4
	#define dex_ps2tonet_patch                               0xCA060
	#define dex_ps2tonet_size_patch                          0xCA054
	#define dex_vmode_patch_offset                           0x44AA50
	#define dex_psp_drm_patch1                               0x24A49C
	#define dex_psp_drm_patch2                               0x24AF3C
	#define dex_psp_drm_patch3                               0x24AB78
	#define dex_psp_drm_patch4                               0x24B384
	#define dex_psp_drm_patchA                               0x24A5B8
	#define dex_psp_drm_patchB                               0x24AE58
	#define dex_psp_drm_patchC                               0x249FF0
	#define dex_psp_drm_patchD                               0x24A5A0
	#define dex_psp_drm_patchE                               0x24A5A4
	#define dex_psp_drm_patchF                               0x24AF70
	#define dex_psp_extra_drm_patch                          0x24CFCC
#endif

#ifdef FIRMWARE_478D

	#define FIRMWARE_VERSION                                 0x478

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x8000000000409930ULL
		#define PS3MAPI_IDPS_2                               0x800000000049CAF4ULL
		#define PS3MAPI_PSID                                 0x800000000049CB0CULL
	#endif
	#define FIRMWARE_DEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x3758E0

	#define create_kernel_object_symbol                      0x125F8
	#define destroy_kernel_object_symbol                     0x11F5C
	#define destroy_shared_kernel_object_symbol              0x118D0
	#define open_kernel_object_symbol                        0x12C48
	#define open_shared_kernel_object_symbol                 0x12A58
	#define close_kernel_object_handle_symbol                0x12078

	#define alloc_symbol                                     0x681F4
	#define dealloc_symbol                                   0x68630
	#define copy_to_user_symbol                              0xFEB4
	#define copy_from_user_symbol                            0x100D0
	#define copy_to_process_symbol                           0xFF6C
	#define copy_from_process_symbol                         0xFD7C
	#define process_read_memory_symbol                       0x26E7E4
	#define process_write_memory_symbol                      0x26E658
	#define page_allocate_symbol                             0x63D64
	#define page_free_symbol                                 0x637C8
	#define page_export_to_proc_symbol                       0x63F00
	#define page_unexport_from_proc_symbol                   0x636BC
	#define kernel_ea_to_lpar_addr_symbol                    0x73C9C
	#define process_ea_to_lpar_addr_ex_symbol                0x7B83C
	#define set_pte_symbol                                   0x61D60
	#define map_process_memory_symbol                        0x7B348
	#define panic_symbol                                     0x2754A0

	#define memcpy_symbol                                    0x82A08
	#define memset_symbol                                    0x51014
	#define memcmp_symbol                                    0x50324
	#define memchr_symbol                                    0x502D4
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
	#define strrchr_symbol                                   0x512F8

	#define spin_lock_irqsave_ex_symbol                      0x275670
	#define spin_unlock_irqrestore_ex_symbol                 0x275644

	#define create_process_common_symbol                     0x272468
	#define create_process_base_symbol                       0x271B00
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x272268

	#define ppu_thread_create_symbol                         0x145FC
	#define ppu_thread_exit_symbol                           0x146B4
	#define ppu_thread_join_symbol                           0x14708
	#define ppu_thread_delay_symbol                          0x2A6E8
	#define create_kernel_thread_symbol                      0x267D0
	#define create_user_thread_symbol                        0x26F0C
	#define create_user_thread2_symbol                       0x26D30
	#define start_thread_symbol                              0x25868
	#define run_thread_symbol                                0x2502C
	#define self_threading_symbol                            0x27518
	#define register_thread_symbol                           0x26E270
	#define allocate_user_stack_symbol                       0x26EA58
	#define deallocate_user_stack_symbol                     0x26E9C0

	#define mutex_create_symbol                              0x13C8C
	#define mutex_destroy_symbol                             0x13C24
	#define mutex_lock_symbol                                0x13C1C
	#define mutex_lock_ex_symbol                             0x1F60C
	#define mutex_trylock_symbol                             0x13C18
	#define mutex_unlock_symbol                              0x13C14

	#define cond_create_symbol                               0x13DF8
	#define cond_destroy_symbol                              0x13DA8
	#define cond_wait_symbol                                 0x13DA0
	#define cond_wait_ex_symbol                              0x20BF8
	#define cond_signal_symbol                               0x13D7C
	#define cond_signal_all_symbol                           0x13D58

	#define semaphore_initialize_symbol                      0x34574
	#define semaphore_wait_ex_symbol                         0x3427C
	#define semaphore_trywait_symbol                         0x33E64
	#define semaphore_post_ex_symbol                         0x33FB0

	#define event_port_create_symbol                         0x136C8
	#define event_port_destroy_symbol                        0x13B30
	#define event_port_connect_symbol                        0x13BA8
	#define event_port_disconnect_symbol                     0x13AD4
	#define event_port_send_symbol                           0x136C0
	#define event_port_send_ex_symbol                        0x2D2C8

	#define event_queue_create_symbol                        0x139D0
	#define event_queue_destroy_symbol                       0x13958
	#define event_queue_receive_symbol                       0x1379C
	#define event_queue_tryreceive_symbol                    0x13868

	#define cellFsOpen_symbol                                0x2B27C0
	#define cellFsClose_symbol                               0x2B2628
	#define cellFsRead_symbol                                0x2B2764
	#define cellFsWrite_symbol                               0x2B26D0
	#define cellFsLseek_symbol                               0x2B1F24
	#define cellFsStat_symbol                                0x2B1FDC
	#define cellFsUtime_symbol                               0x2B394C
	#define cellFsUnlink_internal_symbol                     0x1A29D8
	#define cellFsRename_internal_symbol                     0x19D490

	#define cellFsUtilMount_symbol                           0x2B1C98
	#define cellFsUtilUmount_symbol                          0x2B1C6C
	#define cellFsUtilNewfs_symbol                           0x2B35E4

	#define pathdup_from_user_symbol                         0x2B7A84
	#define open_path_symbol                                 0x2B24F8
	#define open_fs_object_symbol                            0x190CFC
	#define close_fs_object_symbol                           0x18FC38

	#define storage_get_device_info_symbol                   0x28CA00
	#define storage_get_device_config_symbol                 0x28B08C
	#define storage_open_symbol                              0x28CC28
	#define storage_close_symbol                             0x28B414
	#define storage_read_symbol                              0x28A390
	#define storage_write_symbol                             0x28A260
	#define storage_send_device_command_symbol               0x289EB0
	#define storage_map_io_memory_symbol                     0x28C8AC
	#define storage_unmap_io_memory_symbol                   0x28C768
	#define new_medium_listener_object_symbol                0x9CC34
	#define delete_medium_listener_object_symbol             0x9E46C
	#define set_medium_event_callbacks_symbol                0x9E7D0

	#define cellUsbdRegisterLdd_symbol                       0x266758
	#define cellUsbdUnregisterLdd_symbol                     0x266708
	#define cellUsbdScanStaticDescriptor_symbol              0x267958
	#define cellUsbdOpenPipe_symbol                          0x267A08
	#define cellUsbdClosePipe_symbol                         0x2679B8
	#define cellUsbdControlTransfer_symbol                   0x2678BC
	#define cellUsbdBulkTransfer_symbol                      0x26783C

	#define decrypt_func_symbol                              0x38290
	#define lv1_call_99_wrapper_symbol                       0x52850
	#define modules_verification_symbol                      0x5C488
	#define authenticate_program_segment_symbol              0x5E2E0

	#define prx_load_module_symbol                           0x8D308
	#define prx_start_module_symbol                          0x8BFD4
	#define prx_stop_module_symbol                           0x8D3AC
	#define prx_unload_module_symbol                         0x8BD08
	#define prx_get_module_info_symbol                       0x8B700
	#define prx_get_module_id_by_address_symbol              0x8B610
	#define prx_get_module_id_by_name_symbol                 0x8B660
	#define prx_get_module_list_symbol                       0x8B780
	#define load_module_by_fd_symbol                         0x8C938
	#define parse_sprx_symbol                                0x8A62C
	#define open_prx_object_symbol                           0x835D4
	#define close_prx_object_symbol                          0x83EE4
	#define lock_prx_mutex_symbol                            0x8B5B8
	#define unlock_prx_mutex_symbol                          0x8B5C4

	#define extend_kstack_symbol                             0x73BF4

	#define get_pseudo_random_number_symbol                  0x22E65C
	#define md5_reset_symbol                                 0x1681AC
	#define md5_update_symbol                                0x168C4C
	#define md5_final_symbol                                 0x168DCC
	#define ss_get_open_psid_symbol                          0x230B44
	#define update_mgr_read_eeprom_symbol                    0x229F3C
	#define update_mgr_write_eeprom_symbol                   0x229E70
	#define update_mgr_if_get_token_symbol                   0x22B8B8

	#define ss_params_get_update_status_symbol               0x5445C

	#define sm_get_temperature_symbol                        0x269A84
	#define sm_get_fan_policy_symbol                         0x268E18
	#define sm_set_fan_policy_symbol                         0x26ADE0
	#define sm_get_temperature_patch                         0xC728
	#define sm_get_fan_policy_patch                          0x9EB8
	#define sm_set_fan_policy_patch                          0xA3B4

	#define SHA1_init_symbol                                 0x2F0150
	#define SHA1_update_symbol                               0x2F01B0
	#define SHA1_final_symbol                                0x2F0364
	#define aescbccfb_dec_symbol                             0x2EE644
	#define aescbccfb_enc_symbol                             0x2EE3F4
	#define get_path_by_fd_symbol                            0x2B7320

	#define ECDSA_1                                          0x5D794
	#define ECDSA_2                                          0x2F45FC
	#define ECDSA_FLAG                                       0x49CA80
	#define sysmem_obj                                       0x49CC38
	#define qa_eeprom_offset                                 0x4C56E

	#define syscall_table_symbol                             0x3D01B8
	#define syscall_call_offset                              0x27DEE4

	#define read_bdvd0_symbol                                0x1AAACC
	#define read_bdvd1_symbol                                0x1AC6F8
	#define read_bdvd2_symbol                                0x1B98B0

	#define storage_internal_get_device_object_symbol        0x289968

	#define hid_mgr_read_usb_symbol                          0x107F48
	#define hid_mgr_read_bt_symbol                           0x101E20

	#define bt_set_controller_info_internal_symbol           0xF5E8C

	#define device_event_port_send_call                      0x296BFC
	#define device_event_port_send_call_restore              0x2C9D2A48

	#define ss_pid_call_1                                    0x21974C

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x834C8
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x8D1A4

	#define shutdown_copy_params_call                        0xAB4C
	#define shutdown_copy_params_call_restore                0x95635348

	#define fsloop_open_call                                 0x2B2958
	#define fsloop_close_call                                0x2B29A8
	#define fsloop_read_call                                 0x2B29E8

	#define shutdown_patch_offset                            0xAB38
	#define module_sdk_version_patch_offset                  0x26D898
	#define module_add_parameter_to_parse_sprxpatch_offset   0x8CA14

	#define user_thread_prio_patch                           0x21EAC
	#define user_thread_prio_patch2                          0x21EBC

	#define lic_patch                                        0x59C00
	#define lic_patch_restore                                0x482584B5
	#define ode_patch                                        0x22DAD0
	#define fix_80010009                                     0x5E0B4
	#define fix_8001003D                                     0x59F5C
	#define fix_8001003E                                     0x5A020
	#define PATCH_JUMP                                       0x59FD4

	#define io_rtoc_entry_1                                  0x2EC0
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65C0

	#define storage_rtoc_entry_1                             0x22B0

	#define device_event_rtoc_entry_1                        0x2638

	#define time_rtoc_entry_1                               -0x75E0
	#define time_rtoc_entry_2                               -0x75E8

	#define thread_rtoc_entry_1                             -0x7660

	#define process_rtoc_entry_1                            -0x77A0

	#define bt_rtoc_entry_1                                 -0x3558

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x26DB0
	#define permissions_exception2                           0xC8A08
	#define permissions_exception3                           0x21F80

	#define patch_data1_offset                               0x409940
	#define patch_func2                                      0x5D754
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x484E2C91
	#define patch_func8_offset1                              0x59E84
	#define patch_func8_offset2                              0x59FE4
	#define patch_func8_offset2_restore                      0x4821B4BD
	#define patch_func9_offset                               0x5E0C8
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x3A4930

	#define mmapper_flags_temp_patch                         0x74C08

	#define rsx_syscall_check                                0x5411A8
	#define unk_func2_unregister_service                     0x9E900
	#define unk_func3_unregister_service                     0xA3394

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E5000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52C00000056000
	#define PS1_EMU_HASH                                     0xCC2850000009A000
	#define PS1_NETEMU_HASH                                  0xCC28B000000BE000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037C000
	#define BDP_BDVD_HASH                                    0xCC28D00000437000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000044000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F4800000020000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA440C

	/* vsh */
	#define vsh_text_size                                    0x6C0000
	#define ps2tonet_patch                                   0xCA060
	#define ps2tonet_size_patch                              0xCA054
	#define vmode_patch_offset                               0x44AA50
	#define psp_drm_patch1                                   0x24A49C
	#define psp_drm_patch2                                   0x24AF3C
	#define psp_drm_patch3                                   0x24AB78
	#define psp_drm_patch4                                   0x24B384
	#define psp_drm_patchA                                   0x24A5B8
	#define psp_drm_patchB                                   0x24AE58
	#define psp_drm_patchC                                   0x249FF0
	#define psp_drm_patchD                                   0x24A5A0
	#define psp_drm_patchE                                   0x24A5A4
	#define psp_drm_patchF                                   0x24AF70
	#define psp_extra_drm_patch                              0x24CFCC

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDDDC4
	#define app_home_offset                                  0x2515A0

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68264

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x240EC
	#define ps_region_error_offset                           0x6880
	#define remote_play_offset                               0x5FC4
	#define ps2_nonbw_offset3                                0x172F4

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EE48
	#define patch2_nas                                       0x2EFAC
	#define patch3_nas                                       0x1FB08

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x20234
	#define pspemu_path_offset                               0x4C868
	#define psptrans_path_offset                             0x4C920

	/* download_plugin */
	#define elf_patch1_download                              0x42DA0
	#define elf_patch2_download                              0x42DA8
	#define elf_patch3_download                              0x4D6F8
	#define elf_patch4_download                              0x4E518
	#define elf_patch5_download                              0x4E538
	#define elf_patch6_download                              0x4E608

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x8247C
	#define elf_patch2_autodownload                          0x82484

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* CEX */
	#define cex_ps2tonet_patch                               0xC4B14
	#define cex_ps2tonet_size_patch                          0xC4B08
	#define cex_vmode_patch_offset                           0x442E5C
	#define cex_psp_drm_patch1                               0x242C74
	#define cex_psp_drm_patch2                               0x243714
	#define cex_psp_drm_patch3                               0x243350
	#define cex_psp_drm_patch4                               0x243B5C
	#define cex_psp_drm_patchA                               0x242D90
	#define cex_psp_drm_patchB                               0x243630
	#define cex_psp_drm_patchC                               0x2427C8
	#define cex_psp_drm_patchD                               0x242D78
	#define cex_psp_drm_patchE                               0x242D7C
	#define cex_psp_drm_patchF                               0x243748
	#define cex_psp_extra_drm_patch                          0x2457A4
#endif

#ifdef FIRMWARE_480C

	#define FIRMWARE_VERSION                                 0x480

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2E30ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474AF4ULL
		#define PS3MAPI_PSID                                 0x8000000000474B0CULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x34FBA0

	#define create_kernel_object_symbol                      0x11FAC
	#define destroy_kernel_object_symbol                     0x11910
	#define destroy_shared_kernel_object_symbol              0x11284
	#define open_kernel_object_symbol                        0x125FC
	#define open_shared_kernel_object_symbol                 0x1240C
	#define close_kernel_object_handle_symbol                0x11A2C

	#define alloc_symbol                                     0x64820
	#define dealloc_symbol                                   0x64C5C
	#define copy_to_user_symbol                              0xF868
	#define copy_from_user_symbol                            0xFA84
	#define copy_to_process_symbol                           0xF920
	#define copy_from_process_symbol                         0xF730
	#define process_read_memory_symbol                       0x267EB4
	#define process_write_memory_symbol                      0x267D28
	#define page_allocate_symbol                             0x60390
	#define page_free_symbol                                 0x5FDF4
	#define page_export_to_proc_symbol                       0x6052C
	#define page_unexport_from_proc_symbol                   0x5FCE8
	#define kernel_ea_to_lpar_addr_symbol                    0x70148
	#define process_ea_to_lpar_addr_ex_symbol                0x7775C
	#define set_pte_symbol                                   0x5E38C
	#define map_process_memory_symbol                        0x77268
	#define panic_symbol                                     0x26D5BC

	#define memcpy_symbol                                    0x7E928
	#define memset_symbol                                    0x4D668
	#define memcmp_symbol                                    0x4C978
	#define memchr_symbol                                    0x4C928
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
	#define strrchr_symbol                                   0x4D94C

	#define spin_lock_irqsave_ex_symbol                      0x26D78C
	#define spin_unlock_irqrestore_ex_symbol                 0x26D760

	#define create_process_common_symbol                     0x26B528
	#define create_process_base_symbol                       0x26ABE4
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x26B334

	#define ppu_thread_create_symbol                         0x13EC4
	#define ppu_thread_exit_symbol                           0x13F7C
	#define ppu_thread_join_symbol                           0x13FD0
	#define ppu_thread_delay_symbol                          0x287A0
	#define create_kernel_thread_symbol                      0x24B1C
	#define create_user_thread_symbol                        0x25258
	#define create_user_thread2_symbol                       0x2507C
	#define start_thread_symbol                              0x23D48
	#define run_thread_symbol                                0x23578
	#define self_threading_symbol                            0x25864
	#define register_thread_symbol                           0x267940
	#define allocate_user_stack_symbol                       0x268128
	#define deallocate_user_stack_symbol                     0x268090

	#define mutex_create_symbol                              0x13638
	#define mutex_destroy_symbol                             0x135D0
	#define mutex_lock_symbol                                0x135C8
	#define mutex_lock_ex_symbol                             0x1DB58
	#define mutex_trylock_symbol                             0x135C4
	#define mutex_unlock_symbol                              0x135C0

	#define cond_create_symbol                               0x137A4
	#define cond_destroy_symbol                              0x13754
	#define cond_wait_symbol                                 0x1374C
	#define cond_wait_ex_symbol                              0x1F144
	#define cond_signal_symbol                               0x13728
	#define cond_signal_all_symbol                           0x13704

	#define semaphore_initialize_symbol                      0x30C50
	#define semaphore_wait_ex_symbol                         0x30958
	#define semaphore_trywait_symbol                         0x30540
	#define semaphore_post_ex_symbol                         0x3068C

	#define event_port_create_symbol                         0x13074
	#define event_port_destroy_symbol                        0x134DC
	#define event_port_connect_symbol                        0x13554
	#define event_port_disconnect_symbol                     0x13480
	#define event_port_send_symbol                           0x1306C
	#define event_port_send_ex_symbol                        0x2B200

	#define event_queue_create_symbol                        0x1337C
	#define event_queue_destroy_symbol                       0x13304
	#define event_queue_receive_symbol                       0x13148
	#define event_queue_tryreceive_symbol                    0x13214

	#define cellFsOpen_symbol                                0x2978F4
	#define cellFsClose_symbol                               0x29775C
	#define cellFsRead_symbol                                0x297898
	#define cellFsWrite_symbol                               0x297804
	#define cellFsLseek_symbol                               0x296E8C
	#define cellFsStat_symbol                                0x297110
	#define cellFsUtime_symbol                               0x298BFC
	#define cellFsUnlink_internal_symbol                     0x19C644
	#define cellFsRename_internal_symbol                     0x1970FC

	#define cellFsUtilMount_symbol                           0x296C6C
	#define cellFsUtilUmount_symbol                          0x298648
	#define cellFsUtilNewfs_symbol                           0x298694

	#define pathdup_from_user_symbol                         0x29C8D8
	#define open_path_symbol                                 0x2ED870
	#define open_fs_object_symbol                            0x18A968
	#define close_fs_object_symbol                           0x1898A4

	#define storage_get_device_info_symbol                   0x279AF4
	#define storage_get_device_config_symbol                 0x278F84
	#define storage_open_symbol                              0x279504
	#define storage_close_symbol                             0x2792F4
	#define storage_read_symbol                              0x278864
	#define storage_write_symbol                             0x278734
	#define storage_send_device_command_symbol               0x2783F0
	#define storage_map_io_memory_symbol                     0x2799B0
	#define storage_unmap_io_memory_symbol                   0x27987C
	#define new_medium_listener_object_symbol                0x974BC
	#define delete_medium_listener_object_symbol             0x98CF4
	#define set_medium_event_callbacks_symbol                0x99058

	#define cellUsbdRegisterLdd_symbol                       0x260274
	#define cellUsbdUnregisterLdd_symbol                     0x260224
	#define cellUsbdScanStaticDescriptor_symbol              0x261474
	#define cellUsbdOpenPipe_symbol                          0x261524
	#define cellUsbdClosePipe_symbol                         0x2614D4
	#define cellUsbdControlTransfer_symbol                   0x2613D8
	#define cellUsbdBulkTransfer_symbol                      0x261358

	#define decrypt_func_symbol                              0x3496C
	#define lv1_call_99_wrapper_symbol                       0x4EEA4
	#define modules_verification_symbol                      0x58AB4
	#define authenticate_program_segment_symbol              0x5A90C

	#define prx_load_module_symbol                           0x88C00
	#define prx_start_module_symbol                          0x878CC
	#define prx_stop_module_symbol                           0x88CA4
	#define prx_unload_module_symbol                         0x87600
	#define prx_get_module_info_symbol                       0x87088
	#define prx_get_module_id_by_address_symbol              0x86F98
	#define prx_get_module_id_by_name_symbol                 0x86FE8
	#define prx_get_module_list_symbol                       0x87108
	#define load_module_by_fd_symbol                         0x88230
	#define parse_sprx_symbol                                0x85FB4
	#define open_prx_object_symbol                           0x7F4F4
	#define close_prx_object_symbol                          0x7FE04
	#define lock_prx_mutex_symbol                            0x86F40
	#define unlock_prx_mutex_symbol                          0x86F4C

	#define extend_kstack_symbol                             0x700A0

	#define get_pseudo_random_number_symbol                  0x228178
	#define md5_reset_symbol                                 0x161E18
	#define md5_update_symbol                                0x1628B8
	#define md5_final_symbol                                 0x162A38
	#define ss_get_open_psid_symbol                          0x22A660
	#define update_mgr_read_eeprom_symbol                    0x223A70
	#define update_mgr_write_eeprom_symbol                   0x2239B8
	#define update_mgr_if_get_token_symbol                   0x2253D4

	#define ss_params_get_update_status_symbol               0x50AB0

	#define sm_get_temperature_symbol                        0x2635A0
	#define sm_get_fan_policy_symbol                         0x262934
	#define sm_set_fan_policy_symbol                         0x26472C
	#define sm_get_temperature_patch                         0xC6A4
	#define sm_get_fan_policy_patch                          0x9E38
	#define sm_set_fan_policy_patch                          0xA334

	#define SHA1_init_symbol                                 0x2CE67C
	#define SHA1_update_symbol                               0x2CE6DC
	#define SHA1_final_symbol                                0x2CE890
	#define aescbccfb_dec_symbol                             0x2CCB70
	#define aescbccfb_enc_symbol                             0x2CC920
	#define get_path_by_fd_symbol                            0x29C174

	#define ECDSA_1                                          0x59DC0
	#define ECDSA_2                                          0x2D2B28
	#define ECDSA_FLAG                                       0x474A80
	#define sysmem_obj                                       0x474C38
	#define qa_eeprom_offset                                 0x48C06

	#define syscall_table_symbol                             0x363BE0
	#define syscall_call_offset                              0x275BF8

	#define read_bdvd0_symbol                                0x1A4614
	#define read_bdvd1_symbol                                0x1A6240
	#define read_bdvd2_symbol                                0x1B33F8

	#define storage_internal_get_device_object_symbol        0x277EA8

	#define hid_mgr_read_usb_symbol                          0x10243C
	#define hid_mgr_read_bt_symbol                           0xFC314

	#define bt_set_controller_info_internal_symbol           0xF0380

	#define device_event_port_send_call                      0x282060
	#define device_event_port_send_call_restore              0xC10D94B

	#define ss_pid_call_1                                    0x213294

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7F3E8
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x88A9C

	#define shutdown_copy_params_call                        0xAACC
	#define shutdown_copy_params_call_restore                0xB94F0048

	#define fsloop_open_call                                 0x297A8C
	#define fsloop_close_call                                0x297ADC
	#define fsloop_read_call                                 0x297B1C

	#define shutdown_patch_offset                            0xAAB8
	#define module_sdk_version_patch_offset                  0x267170
	#define module_add_parameter_to_parse_sprxpatch_offset   0x8830C

	#define user_thread_prio_patch                           0x203F8
	#define user_thread_prio_patch2                          0x20408

	#define lic_patch                                        0x5622C
	#define lic_patch_restore                                0x48240EE5
	#define ode_patch                                        0x2275EC
	#define fix_80010009                                     0x5A6E0
	#define fix_8001003D                                     0x56588
	#define fix_8001003E                                     0x5664C
	#define PATCH_JUMP                                       0x56600

	#define io_rtoc_entry_1                                  0x25B8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0

	#define storage_rtoc_entry_1                             0x1DD8

	#define device_event_rtoc_entry_1                        0x2048

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x3680

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x250FC
	#define permissions_exception2                           0xC3290
	#define permissions_exception3                           0x204CC

	#define patch_data1_offset                               0x3E2E40
	#define patch_func2                                      0x59D80
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDABC1
	#define patch_func8_offset1                              0x564B0
	#define patch_func8_offset2                              0x56610
	#define patch_func8_offset2_restore                      0x48216FAD
	#define patch_func9_offset                               0x5A6F4
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x37DE30

	#define mmapper_flags_temp_patch                         0x70F74

	#define rsx_syscall_check                                0x7E4C
	#define unk_func2_unregister_service                     0x99188
	#define unk_func3_unregister_service                     0x9DC1C

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E3000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52D00000056000
	#define PS1_EMU_HASH                                     0xCC2850000009A000
	#define PS1_NETEMU_HASH                                  0xCC28B000000BE000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037C000
	#define BDP_BDVD_HASH                                    0xCC28D00000437000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000044000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F470000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA4D74

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4E34
	#define ps2tonet_size_patch                              0xC4E28
	#define vmode_patch_offset                               0x4431E4
	#define psp_drm_patch1                                   0x242FBC
	#define psp_drm_patch2                                   0x243A5C
	#define psp_drm_patch3                                   0x243698
	#define psp_drm_patch4                                   0x243EA4
	#define psp_drm_patchA                                   0x2430D8
	#define psp_drm_patchB                                   0x243978
	#define psp_drm_patchC                                   0x242B10
	#define psp_drm_patchD                                   0x2430C0
	#define psp_drm_patchE                                   0x2430C4
	#define psp_drm_patchF                                   0x243A90
	#define psp_extra_drm_patch                              0x245AEC

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDD9B4
	#define app_home_offset                                  0x250A00

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68324

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23B90
	#define ps_region_error_offset                           0x68C0
	#define remote_play_offset                               0x5FC0
	#define ps2_nonbw_offset3                                0x17000

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EAE4
	#define patch2_nas                                       0x2EC48
	#define patch3_nas                                       0x1F75C

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F78C
	#define pspemu_path_offset                               0x4B688
	#define psptrans_path_offset                             0x4B718

	/* download_plugin */
	#define elf_patch1_download                              0x42E2C
	#define elf_patch2_download                              0x42E34
	#define elf_patch3_download                              0x4D7F8
	#define elf_patch4_download                              0x4E618
	#define elf_patch5_download                              0x4E638
	#define elf_patch6_download                              0x4E708

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x82658
	#define elf_patch2_autodownload                          0x82660

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                        0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH                 0xDE52C00000056000
	#define GAME_EXT_PLUGIN_REBUG_HASH                       0xCC2680000001E000
	#define dex_ps2_nonbw_offset                             0xDDDC4
	#define dex_ps2_nonbw_offset2                            0x68264
	#define dex_ps2_nonbw_offset3                            0x172F0
	#define dex_ps2tonet_patch                               0xCA380
	#define dex_ps2tonet_size_patch                          0xCA374
	#define dex_vmode_patch_offset                           0x44ADD8
	#define dex_psp_drm_patch1                               0x24A7E4
	#define dex_psp_drm_patch2                               0x24B284
	#define dex_psp_drm_patch3                               0x24AEC0
	#define dex_psp_drm_patch4                               0x24B6CC
	#define dex_psp_drm_patchA                               0x24A900
	#define dex_psp_drm_patchB                               0x24B1A0
	#define dex_psp_drm_patchC                               0x24A338
	#define dex_psp_drm_patchD                               0x24A8E8
	#define dex_psp_drm_patchE                               0x24A8EC
	#define dex_psp_drm_patchF                               0x24B2B8
	#define dex_psp_extra_drm_patch                          0x24D314
#endif

#ifdef FIRMWARE_480D

	#define FIRMWARE_VERSION                                 0x480

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x8000000000409A30ULL
		#define PS3MAPI_IDPS_2                               0x800000000049CAF4ULL
		#define PS3MAPI_PSID                                 0x800000000049CB0CULL
	#endif
	#define FIRMWARE_DEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x3759B0

	#define create_kernel_object_symbol                      0x125F4
	#define destroy_kernel_object_symbol                     0x11F58
	#define destroy_shared_kernel_object_symbol              0x118CC
	#define open_kernel_object_symbol                        0x12C44
	#define open_shared_kernel_object_symbol                 0x12A54
	#define close_kernel_object_handle_symbol                0x12074

	#define alloc_symbol                                     0x681F0
	#define dealloc_symbol                                   0x6862C
	#define copy_to_user_symbol                              0xFEB0
	#define copy_from_user_symbol                            0x100CC
	#define copy_to_process_symbol                           0xFF68
	#define copy_from_process_symbol                         0xFD78
	#define process_read_memory_symbol                       0x26E7D8
	#define process_write_memory_symbol                      0x26E64C
	#define page_allocate_symbol                             0x63D60
	#define page_free_symbol                                 0x637C4
	#define page_export_to_proc_symbol                       0x63EFC
	#define page_unexport_from_proc_symbol                   0x636B8
	#define kernel_ea_to_lpar_addr_symbol                    0x73C98
	#define process_ea_to_lpar_addr_ex_symbol                0x7B838
	#define set_pte_symbol                                   0x61D5C
	#define map_process_memory_symbol                        0x7B344
	#define panic_symbol                                     0x275494

	#define memcpy_symbol                                    0x82A04
	#define memset_symbol                                    0x51010
	#define memcmp_symbol                                    0x50320
	#define memchr_symbol                                    0x502D0
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
	#define strrchr_symbol                                   0x512F4

	#define spin_lock_irqsave_ex_symbol                      0x275664
	#define spin_unlock_irqrestore_ex_symbol                 0x275638

	#define create_process_common_symbol                     0x27245C
	#define create_process_base_symbol                       0x271AF4
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x27225C

	#define ppu_thread_create_symbol                         0x145F8
	#define ppu_thread_exit_symbol                           0x146B0
	#define ppu_thread_join_symbol                           0x14704
	#define ppu_thread_delay_symbol                          0x2A6E4
	#define create_kernel_thread_symbol                      0x267CC
	#define create_user_thread_symbol                        0x26F08
	#define create_user_thread2_symbol                       0x26D2C
	#define start_thread_symbol                              0x25864
	#define run_thread_symbol                                0x25028
	#define self_threading_symbol                            0x27514
	#define register_thread_symbol                           0x26E264
	#define allocate_user_stack_symbol                       0x26EA4C
	#define deallocate_user_stack_symbol                     0x26E9B4

	#define mutex_create_symbol                              0x13C88
	#define mutex_destroy_symbol                             0x13C20
	#define mutex_lock_symbol                                0x13C18
	#define mutex_lock_ex_symbol                             0x1F608
	#define mutex_trylock_symbol                             0x13C14
	#define mutex_unlock_symbol                              0x13C10

	#define cond_create_symbol                               0x13DF4
	#define cond_destroy_symbol                              0x13DA4
	#define cond_wait_symbol                                 0x13D9C
	#define cond_wait_ex_symbol                              0x20BF4
	#define cond_signal_symbol                               0x13D78
	#define cond_signal_all_symbol                           0x13D54

	#define semaphore_initialize_symbol                      0x34570
	#define semaphore_wait_ex_symbol                         0x34278
	#define semaphore_trywait_symbol                         0x33E60
	#define semaphore_post_ex_symbol                         0x33FAC

	#define event_port_create_symbol                         0x136C4
	#define event_port_destroy_symbol                        0x13B2C
	#define event_port_connect_symbol                        0x13BA4
	#define event_port_disconnect_symbol                     0x13AD0
	#define event_port_send_symbol                           0x136BC
	#define event_port_send_ex_symbol                        0x2D2C4

	#define event_queue_create_symbol                        0x139CC
	#define event_queue_destroy_symbol                       0x13954
	#define event_queue_receive_symbol                       0x13798
	#define event_queue_tryreceive_symbol                    0x13864

	#define cellFsOpen_symbol                                0x2B288C
	#define cellFsClose_symbol                               0x2B26F4
	#define cellFsRead_symbol                                0x2B2830
	#define cellFsWrite_symbol                               0x2B279C
	#define cellFsLseek_symbol                               0x2B1FF0
	#define cellFsStat_symbol                                0x2B20A8
	#define cellFsUtime_symbol                               0x2B3A18
	#define cellFsUnlink_internal_symbol                     0x1A29D0
	#define cellFsRename_internal_symbol                     0x19D488

	#define cellFsUtilMount_symbol                           0x2B1D64
	#define cellFsUtilUmount_symbol                          0x2B1D38
	#define cellFsUtilNewfs_symbol                           0x2B36B0

	#define pathdup_from_user_symbol                         0x2B7B50
	#define open_path_symbol                                 0x2B25C4
	#define open_fs_object_symbol                            0x190CF4
	#define close_fs_object_symbol                           0x18FC30

	#define storage_get_device_info_symbol                   0x28C9F4
	#define storage_get_device_config_symbol                 0x28B080
	#define storage_open_symbol                              0x28CC1C
	#define storage_close_symbol                             0x28B408
	#define storage_read_symbol                              0x28A384
	#define storage_write_symbol                             0x28A254
	#define storage_send_device_command_symbol               0x289EA4
	#define storage_map_io_memory_symbol                     0x28C8A0
	#define storage_unmap_io_memory_symbol                   0x28C75C
	#define new_medium_listener_object_symbol                0x9CC2C
	#define delete_medium_listener_object_symbol             0x9E464
	#define set_medium_event_callbacks_symbol                0x9E7C8

	#define cellUsbdRegisterLdd_symbol                       0x266750
	#define cellUsbdUnregisterLdd_symbol                     0x266700
	#define cellUsbdScanStaticDescriptor_symbol              0x267950
	#define cellUsbdOpenPipe_symbol                          0x267A00
	#define cellUsbdClosePipe_symbol                         0x2679B0
	#define cellUsbdControlTransfer_symbol                   0x2678B4
	#define cellUsbdBulkTransfer_symbol                      0x267834

	#define decrypt_func_symbol                              0x3828C
	#define lv1_call_99_wrapper_symbol                       0x5284C
	#define modules_verification_symbol                      0x5C484
	#define authenticate_program_segment_symbol              0x5E2DC

	#define prx_load_module_symbol                           0x8D304
	#define prx_start_module_symbol                          0x8BFD0
	#define prx_stop_module_symbol                           0x8D3A8
	#define prx_unload_module_symbol                         0x8BD04
	#define prx_get_module_info_symbol                       0x8B6FC
	#define prx_get_module_id_by_address_symbol              0x8B60C
	#define prx_get_module_id_by_name_symbol                 0x8B65C
	#define prx_get_module_list_symbol                       0x8B77C
	#define load_module_by_fd_symbol                         0x8C934
	#define parse_sprx_symbol                                0x8A628
	#define open_prx_object_symbol                           0x835D0
	#define close_prx_object_symbol                          0x83EE0
	#define lock_prx_mutex_symbol                            0x8B5B4
	#define unlock_prx_mutex_symbol                          0x8B5C0

	#define extend_kstack_symbol                             0x73BF0

	#define get_pseudo_random_number_symbol                  0x22E654
	#define md5_reset_symbol                                 0x1681A4
	#define md5_update_symbol                                0x168C44
	#define md5_final_symbol                                 0x168DC4
	#define ss_get_open_psid_symbol                          0x230B3C
	#define update_mgr_read_eeprom_symbol                    0x229F34
	#define update_mgr_write_eeprom_symbol                   0x229E68
	#define update_mgr_if_get_token_symbol                   0x22B8B0

	#define ss_params_get_update_status_symbol               0x54458

	#define sm_get_temperature_symbol                        0x269A7C
	#define sm_get_fan_policy_symbol                         0x268E10
	#define sm_set_fan_policy_symbol                         0x26ADD8
	#define sm_get_temperature_patch                         0xC724
	#define sm_get_fan_policy_patch                          0x9EB8
	#define sm_set_fan_policy_patch                          0xA3B4

	#define SHA1_init_symbol                                 0x2F021C
	#define SHA1_update_symbol                               0x2F027C
	#define SHA1_final_symbol                                0x2F0430
	#define aescbccfb_dec_symbol                             0x2EE710
	#define aescbccfb_enc_symbol                             0x2EE4C0
	#define get_path_by_fd_symbol                            0x2B73EC

	#define ECDSA_1                                          0x5D790
	#define ECDSA_2                                          0x2F46C8
	#define ECDSA_FLAG                                       0x49CA80
	#define sysmem_obj                                       0x49CC38
	#define qa_eeprom_offset                                 0x4C56A

	#define syscall_table_symbol                             0x38A4E8
	#define syscall_call_offset                              0x27DED8

	#define read_bdvd0_symbol                                0x1AAAC4
	#define read_bdvd1_symbol                                0x1AC6F0
	#define read_bdvd2_symbol                                0x1B98A8

	#define storage_internal_get_device_object_symbol        0x28995C

	#define hid_mgr_read_usb_symbol                          0x107F40
	#define hid_mgr_read_bt_symbol                           0x101E18

	#define bt_set_controller_info_internal_symbol           0xF5E84

	#define device_event_port_send_call                      0x296BF0
	#define device_event_port_send_call_restore              0xCCCAD74B

	#define ss_pid_call_1                                    0x219744

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x834C4
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x8D1A0

	#define shutdown_copy_params_call                        0xAB4C
	#define shutdown_copy_params_call_restore                0x81550048

	#define fsloop_open_call                                 0x2B2A24
	#define fsloop_close_call                                0x2B2A74
	#define fsloop_read_call                                 0x2B2AB4

	#define shutdown_patch_offset                            0xAB38
	#define module_sdk_version_patch_offset                  0x26D88C
	#define module_add_parameter_to_parse_sprxpatch_offset   0x8CA10

	#define user_thread_prio_patch                           0x21EA8
	#define user_thread_prio_patch2                          0x21EB8

	#define lic_patch                                        0x59BFC
	#define lic_patch_restore                                0x482584B5
	#define ode_patch                                        0x22DAC8
	#define fix_80010009                                     0x5E0B0
	#define fix_8001003D                                     0x59F58
	#define fix_8001003E                                     0x5A01C
	#define PATCH_JUMP                                       0x59FD0

	#define io_rtoc_entry_1                                  0x2EC0
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65C0

	#define storage_rtoc_entry_1                             0x22B0

	#define device_event_rtoc_entry_1                        0x2638

	#define time_rtoc_entry_1                               -0x75E0
	#define time_rtoc_entry_2                               -0x75E8

	#define thread_rtoc_entry_1                             -0x7660

	#define process_rtoc_entry_1                            -0x77A0

	#define bt_rtoc_entry_1                                 -0x3558

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x26DAC
	#define permissions_exception2                           0xC8A00
	#define permissions_exception3                           0x21F7C

	#define patch_data1_offset                               0x409A40
	#define patch_func2                                      0x5D750
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDAB11
	#define patch_func8_offset1                              0x59E80
	#define patch_func8_offset2                              0x59FE0
	#define patch_func8_offset2_restore                      0x4821B4B5
	#define patch_func9_offset                               0x5E0C4
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x3A4A30

	#define mmapper_flags_temp_patch                         0x74C04

	#define rsx_syscall_check                                0x7E4C
	#define unk_func2_unregister_service                     0x9E8F8
	#define unk_func3_unregister_service                     0xA338C

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E6000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52C00000056000
	#define PS1_EMU_HASH                                     0xCC2850000009A000
	#define PS1_NETEMU_HASH                                  0xCC28B000000BE000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037C000
	#define BDP_BDVD_HASH                                    0xCC28D00000437000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000044000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F4800000020000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA4D74

	/* vsh */
	#define vsh_text_size                                    0x6C0000
	#define ps2tonet_patch                                   0xCA380
	#define ps2tonet_size_patch                              0xCA374
	#define vmode_patch_offset                               0x44ADD8
	#define psp_drm_patch1                                   0x24A7E4
	#define psp_drm_patch2                                   0x24B284
	#define psp_drm_patch3                                   0x24AEC0
	#define psp_drm_patch4                                   0x24B6CC
	#define psp_drm_patchA                                   0x24A900
	#define psp_drm_patchB                                   0x24B1A0
	#define psp_drm_patchC                                   0x24A338
	#define psp_drm_patchD                                   0x24A8E8
	#define psp_drm_patchE                                   0x24A8EC
	#define psp_drm_patchF                                   0x24B2B8
	#define psp_extra_drm_patch                              0x24D314

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDDDC4
	#define app_home_offset                                  0x2515B0

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68264

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23DAC
	#define ps_region_error_offset                           0x687C
	#define remote_play_offset                               0x5FC0
	#define ps2_nonbw_offset3                                0x172F0

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EEF4
	#define patch2_nas                                       0x2F058
	#define patch3_nas                                       0x1FA0C

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x20234
	#define pspemu_path_offset                               0x4C868
	#define psptrans_path_offset                             0x4C920

	/* download_plugin */
	#define elf_patch1_download                              0x42DC0
	#define elf_patch2_download                              0x42DC8
	#define elf_patch3_download                              0x4D718
	#define elf_patch4_download                              0x4E538
	#define elf_patch5_download                              0x4E558
	#define elf_patch6_download                              0x4E628

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x824C0
	#define elf_patch2_autodownload                          0x824C8

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* CEX */
	#define cex_ps2tonet_patch                               0xC4E34
	#define cex_ps2tonet_size_patch                          0xC4E28
	#define cex_vmode_patch_offset                           0x4431E4
	#define cex_psp_drm_patch1                               0x242FBC
	#define cex_psp_drm_patch2                               0x243A5C
	#define cex_psp_drm_patch3                               0x243698
	#define cex_psp_drm_patch4                               0x243EA4
	#define cex_psp_drm_patchA                               0x2430D8
	#define cex_psp_drm_patchB                               0x243978
	#define cex_psp_drm_patchC                               0x242B10
	#define cex_psp_drm_patchD                               0x2430C0
	#define cex_psp_drm_patchE                               0x2430C4
	#define cex_psp_drm_patchF                               0x243A90
	#define cex_psp_extra_drm_patch                          0x245AEC
#endif

#ifdef FIRMWARE_481C

	#define FIRMWARE_VERSION                                 0x481

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2E30ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474AF4ULL
		#define PS3MAPI_PSID                                 0x8000000000474B0CULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x34FBB0

	#define create_kernel_object_symbol                      0x11FB0
	#define destroy_kernel_object_symbol                     0x11914
	#define destroy_shared_kernel_object_symbol              0x11288
	#define open_kernel_object_symbol                        0x12600
	#define open_shared_kernel_object_symbol                 0x12410
	#define close_kernel_object_handle_symbol                0x11A30

	#define alloc_symbol                                     0x64824
	#define dealloc_symbol                                   0x64C60
	#define copy_to_user_symbol                              0xF86C
	#define copy_from_user_symbol                            0xFA88
	#define copy_to_process_symbol                           0xF924
	#define copy_from_process_symbol                         0xF734
	#define process_read_memory_symbol                       0x267EC0
	#define process_write_memory_symbol                      0x267D34
	#define page_allocate_symbol                             0x60394
	#define page_free_symbol                                 0x5FDF8
	#define page_export_to_proc_symbol                       0x60530
	#define page_unexport_from_proc_symbol                   0x5FCEC
	#define kernel_ea_to_lpar_addr_symbol                    0x7014C
	#define process_ea_to_lpar_addr_ex_symbol                0x77760
	#define set_pte_symbol                                   0x5E390
	#define map_process_memory_symbol                        0x7726C
	#define panic_symbol                                     0x26D5C8

	#define memcpy_symbol                                    0x7E92C
	#define memset_symbol                                    0x4D66C
	#define memcmp_symbol                                    0x4C97C
	#define memchr_symbol                                    0x4C92C
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
	#define strrchr_symbol                                   0x4D950

	#define spin_lock_irqsave_ex_symbol                      0x26D798
	#define spin_unlock_irqrestore_ex_symbol                 0x26D76C

	#define create_process_common_symbol                     0x26B534
	#define create_process_base_symbol                       0x26ABF0
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x26B340

	#define ppu_thread_create_symbol                         0x13EC8
	#define ppu_thread_exit_symbol                           0x13F80
	#define ppu_thread_join_symbol                           0x13FD4
	#define ppu_thread_delay_symbol                          0x287A4
	#define create_kernel_thread_symbol                      0x24B20
	#define create_user_thread_symbol                        0x2525C
	#define create_user_thread2_symbol                       0x25080
	#define start_thread_symbol                              0x23D4C
	#define run_thread_symbol                                0x2357C
	#define self_threading_symbol                            0x25868
	#define register_thread_symbol                           0x26794C
	#define allocate_user_stack_symbol                       0x268134
	#define deallocate_user_stack_symbol                     0x26809C

	#define mutex_create_symbol                              0x1363C
	#define mutex_destroy_symbol                             0x135D4
	#define mutex_lock_symbol                                0x135CC
	#define mutex_lock_ex_symbol                             0x1DB5C
	#define mutex_trylock_symbol                             0x135C8
	#define mutex_unlock_symbol                              0x135C4

	#define cond_create_symbol                               0x137A8
	#define cond_destroy_symbol                              0x13758
	#define cond_wait_symbol                                 0x13750
	#define cond_wait_ex_symbol                              0x1F148
	#define cond_signal_symbol                               0x1372C
	#define cond_signal_all_symbol                           0x13708

	#define semaphore_initialize_symbol                      0x30C54
	#define semaphore_wait_ex_symbol                         0x3095C
	#define semaphore_trywait_symbol                         0x30544
	#define semaphore_post_ex_symbol                         0x30690

	#define event_port_create_symbol                         0x13078
	#define event_port_destroy_symbol                        0x134E0
	#define event_port_connect_symbol                        0x13558
	#define event_port_disconnect_symbol                     0x13484
	#define event_port_send_symbol                           0x13070
	#define event_port_send_ex_symbol                        0x2B204

	#define event_queue_create_symbol                        0x13380
	#define event_queue_destroy_symbol                       0x13308
	#define event_queue_receive_symbol                       0x1314C
	#define event_queue_tryreceive_symbol                    0x13218

	#define cellFsOpen_symbol                                0x297900
	#define cellFsClose_symbol                               0x297768
	#define cellFsRead_symbol                                0x2978A4
	#define cellFsWrite_symbol                               0x297810
	#define cellFsLseek_symbol                               0x296E98
	#define cellFsStat_symbol                                0x29711C
	#define cellFsUtime_symbol                               0x298C08
	#define cellFsUnlink_internal_symbol                     0x19C64C
	#define cellFsRename_internal_symbol                     0x197104

	#define cellFsUtilMount_symbol                           0x296C78
	#define cellFsUtilUmount_symbol                          0x298654
	#define cellFsUtilNewfs_symbol                           0x2986A0

	#define pathdup_from_user_symbol                         0x29C8E4
	#define open_path_symbol                                 0x297638
	#define open_fs_object_symbol                            0x18A970
	#define close_fs_object_symbol                           0x1898AC

	#define storage_get_device_info_symbol                   0x279B00
	#define storage_get_device_config_symbol                 0x278F90
	#define storage_open_symbol                              0x279510
	#define storage_close_symbol                             0x279300
	#define storage_read_symbol                              0x278870
	#define storage_write_symbol                             0x278740
	#define storage_send_device_command_symbol               0x2783FC
	#define storage_map_io_memory_symbol                     0x2799BC
	#define storage_unmap_io_memory_symbol                   0x279888
	#define new_medium_listener_object_symbol                0x974C4
	#define delete_medium_listener_object_symbol             0x98CFC
	#define set_medium_event_callbacks_symbol                0x99060

	#define cellUsbdRegisterLdd_symbol                       0x26027C
	#define cellUsbdUnregisterLdd_symbol                     0x26022C
	#define cellUsbdScanStaticDescriptor_symbol              0x26147C
	#define cellUsbdOpenPipe_symbol                          0x26152C
	#define cellUsbdClosePipe_symbol                         0x2614DC
	#define cellUsbdControlTransfer_symbol                   0x2613E0
	#define cellUsbdBulkTransfer_symbol                      0x261360

	#define decrypt_func_symbol                              0x34970
	#define lv1_call_99_wrapper_symbol                       0x4EEA8
	#define modules_verification_symbol                      0x58AB8
	#define authenticate_program_segment_symbol              0x5A910

	#define prx_load_module_symbol                           0x88C04
	#define prx_start_module_symbol                          0x878D0
	#define prx_stop_module_symbol                           0x88CA8
	#define prx_unload_module_symbol                         0x87604
	#define prx_get_module_info_symbol                       0x8708C
	#define prx_get_module_id_by_address_symbol              0x86F9C
	#define prx_get_module_id_by_name_symbol                 0x86FEC
	#define prx_get_module_list_symbol                       0x8710C
	#define load_module_by_fd_symbol                         0x88234
	#define parse_sprx_symbol                                0x85FB8
	#define open_prx_object_symbol                           0x7F4F8
	#define close_prx_object_symbol                          0x7FE08
	#define lock_prx_mutex_symbol                            0x86F44
	#define unlock_prx_mutex_symbol                          0x86F50

	#define extend_kstack_symbol                             0x700A4

	#define get_pseudo_random_number_symbol                  0x228180
	#define md5_reset_symbol                                 0x161E20
	#define md5_update_symbol                                0x1628C0
	#define md5_final_symbol                                 0x162A40
	#define ss_get_open_psid_symbol                          0x22A668
	#define update_mgr_read_eeprom_symbol                    0x223A78
	#define update_mgr_write_eeprom_symbol                   0x2239C0
	#define update_mgr_if_get_token_symbol                   0x2253DC

	#define ss_params_get_update_status_symbol               0x50AB4

	#define sm_get_temperature_symbol                        0x2635A8
	#define sm_get_fan_policy_symbol                         0x26293C
	#define sm_set_fan_policy_symbol                         0x264734
	#define sm_get_temperature_patch                         0xC6A8
	#define sm_get_fan_policy_patch                          0x9E38
	#define sm_set_fan_policy_patch                          0xA334

	#define SHA1_init_symbol                                 0x2CE688
	#define SHA1_update_symbol                               0x2CE6E8
	#define SHA1_final_symbol                                0x2CE89C
	#define aescbccfb_dec_symbol                             0x2CCB7C
	#define aescbccfb_enc_symbol                             0x2CC92C
	#define get_path_by_fd_symbol                            0x29C180

	#define ECDSA_1                                          0x59DC4
	#define ECDSA_2                                          0x2D2B34
	#define ECDSA_FLAG                                       0x474A80
	#define sysmem_obj                                       0x474C38
	#define qa_eeprom_offset                                 0x48C0A

	#define syscall_table_symbol                             0x363BE0
	#define syscall_call_offset                              0x275C04

	#define read_bdvd0_symbol                                0x1A461C
	#define read_bdvd1_symbol                                0x1A6248
	#define read_bdvd2_symbol                                0x1B3400

	#define storage_internal_get_device_object_symbol        0x277EB4

	#define hid_mgr_read_usb_symbol                          0x102444
	#define hid_mgr_read_bt_symbol                           0xFC31C

	#define bt_set_controller_info_internal_symbol           0xF0388

	#define device_event_port_send_call                      0x28206C
	#define device_event_port_send_call_restore              0xBCE82748

	#define ss_pid_call_1                                    0x21329C

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7F3EC
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x88AA0

	#define shutdown_copy_params_call                        0xAACC
	#define shutdown_copy_params_call_restore                0x15644F48

	#define fsloop_open_call                                 0x297A98
	#define fsloop_close_call                                0x297AE8
	#define fsloop_read_call                                 0x297B28

	#define shutdown_patch_offset                            0xAAB8
	#define module_sdk_version_patch_offset                  0x26717C
	#define module_add_parameter_to_parse_sprxpatch_offset   0x88310

	#define user_thread_prio_patch                           0x203FC
	#define user_thread_prio_patch2                          0x2040C

	#define lic_patch                                        0x56230
	#define lic_patch_restore                                0x48240EED
	#define ode_patch                                        0x2275F4
	#define fix_80010009                                     0x5A6E4
	#define fix_8001003D                                     0x5658C
	#define fix_8001003E                                     0x56650
	#define PATCH_JUMP                                       0x56604

	#define io_rtoc_entry_1                                  0x25B8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0

	#define storage_rtoc_entry_1                             0x1DD8

	#define device_event_rtoc_entry_1                        0x2048

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x3680

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x25100
	#define permissions_exception2                           0xC3298
	#define permissions_exception3                           0x204D0

	#define patch_data1_offset                               0x3E2E40
	#define patch_func2                                      0x59D84
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x484A6661
	#define patch_func8_offset1                              0x564B4
	#define patch_func8_offset2                              0x56614
	#define patch_func8_offset2_restore                      0x48216FB5
	#define patch_func9_offset                               0x5A6F8
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x37DE30

	#define mmapper_flags_temp_patch                         0x70F78

	#define rsx_syscall_check                                0x5011A8
	#define unk_func2_unregister_service                     0x99190
	#define unk_func3_unregister_service                     0x9DC24

	/* lv1 */
	#define vsh_pos_in_ram                                   0x510000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E3000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52D00000056000
	#define PS1_EMU_HASH                                     0xCC2850000009A000
	#define PS1_NETEMU_HASH                                  0xCC28B000000BE000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037C000
	#define BDP_BDVD_HASH                                    0xCC28D00000437000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000044000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F470000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA4D74

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4E34
	#define ps2tonet_size_patch                              0xC4E28
	#define vmode_patch_offset                               0x4431D8
	#define psp_drm_patch1                                   0x242FC0
	#define psp_drm_patch2                                   0x243A60
	#define psp_drm_patch3                                   0x24369C
	#define psp_drm_patch4                                   0x243EA8
	#define psp_drm_patchA                                   0x2430DC
	#define psp_drm_patchB                                   0x24397C
	#define psp_drm_patchC                                   0x242B14
	#define psp_drm_patchD                                   0x2430C4
	#define psp_drm_patchE                                   0x2430C8
	#define psp_drm_patchF                                   0x243A94
	#define psp_extra_drm_patch                              0x245AF0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDD9B4
	#define app_home_offset                                  0x250A00

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68324

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23B90
	#define ps_region_error_offset                           0x68C0
	#define remote_play_offset                               0x5FC0
	#define ps2_nonbw_offset3                                0x17000

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EAE4
	#define patch2_nas                                       0x2EC48
	#define patch3_nas                                       0x1F75C

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F78C
	#define pspemu_path_offset                               0x4B688
	#define psptrans_path_offset                             0x4B718

	/* download_plugin */
	#define elf_patch1_download                              0x42E2C
	#define elf_patch2_download                              0x42E34
	#define elf_patch3_download                              0x4D7F8
	#define elf_patch4_download                              0x4E618
	#define elf_patch5_download                              0x4E638
	#define elf_patch6_download                              0x4E708

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x82650
	#define elf_patch2_autodownload                          0x82658

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                        0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH                 0xDE52C00000056000
	#define GAME_EXT_PLUGIN_REBUG_HASH                       0xCC2680000001E000
	#define dex_ps2_nonbw_offset                             0xDDDC4
	#define dex_ps2_nonbw_offset2                            0x68264
	#define dex_ps2_nonbw_offset3                            0x172F0
	#define dex_ps2tonet_patch                               0xCA380
	#define dex_ps2tonet_size_patch                          0xCA374
	#define dex_vmode_patch_offset                           0x44ADCC
	#define dex_psp_drm_patch1                               0x24A7E8
	#define dex_psp_drm_patch2                               0x24B288
	#define dex_psp_drm_patch3                               0x24AEC4
	#define dex_psp_drm_patch4                               0x24B6D0
	#define dex_psp_drm_patchA                               0x24A904
	#define dex_psp_drm_patchB                               0x24B1A4
	#define dex_psp_drm_patchC                               0x24A33C
	#define dex_psp_drm_patchD                               0x24A8EC
	#define dex_psp_drm_patchE                               0x24A8F0
	#define dex_psp_drm_patchF                               0x24B2BC
	#define dex_psp_extra_drm_patch                          0x24D318
#endif

#ifdef FIRMWARE_481D

	#define FIRMWARE_VERSION                                 0x481

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x8000000000409A30ULL
		#define PS3MAPI_IDPS_2                               0x800000000049CAF4ULL
		#define PS3MAPI_PSID                                 0x800000000049CB0CULL
	#endif
	#define FIRMWARE_DEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x3759C0

	#define create_kernel_object_symbol                      0x125F8
	#define destroy_kernel_object_symbol                     0x11F5C
	#define destroy_shared_kernel_object_symbol              0x118D0
	#define open_kernel_object_symbol                        0x12C48
	#define open_shared_kernel_object_symbol                 0x12A58
	#define close_kernel_object_handle_symbol                0x12078

	#define alloc_symbol                                     0x681F4
	#define dealloc_symbol                                   0x68630
	#define copy_to_user_symbol                              0xFEB4
	#define copy_from_user_symbol                            0x100D0
	#define copy_to_process_symbol                           0xFF6C
	#define copy_from_process_symbol                         0xFD7C
	#define process_read_memory_symbol                       0x26E7E4
	#define process_write_memory_symbol                      0x26E658
	#define page_allocate_symbol                             0x63D64
	#define page_free_symbol                                 0x637C8
	#define page_export_to_proc_symbol                       0x63F00
	#define page_unexport_from_proc_symbol                   0x636BC
	#define kernel_ea_to_lpar_addr_symbol                    0x73C9C
	#define process_ea_to_lpar_addr_ex_symbol                0x7B83C
	#define set_pte_symbol                                   0x61D60
	#define map_process_memory_symbol                        0x7B348
	#define panic_symbol                                     0x2754A0

	#define memcpy_symbol                                    0x82A08
	#define memset_symbol                                    0x51014
	#define memcmp_symbol                                    0x50324
	#define memchr_symbol                                    0x502D4
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
	#define strrchr_symbol                                   0x512F8

	#define spin_lock_irqsave_ex_symbol                      0x275670
	#define spin_unlock_irqrestore_ex_symbol                 0x275644

	#define create_process_common_symbol                     0x272468
	#define create_process_base_symbol                       0x271B00
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x272268

	#define ppu_thread_create_symbol                         0x145FC
	#define ppu_thread_exit_symbol                           0x146B4
	#define ppu_thread_join_symbol                           0x14708
	#define ppu_thread_delay_symbol                          0x2A6E8
	#define create_kernel_thread_symbol                      0x267D0
	#define create_user_thread_symbol                        0x26F0C
	#define create_user_thread2_symbol                       0x26D30
	#define start_thread_symbol                              0x25868
	#define run_thread_symbol                                0x2502C
	#define self_threading_symbol                            0x27518
	#define register_thread_symbol                           0x26E270
	#define allocate_user_stack_symbol                       0x26EA58
	#define deallocate_user_stack_symbol                     0x26E9C0

	#define mutex_create_symbol                              0x13C8C
	#define mutex_destroy_symbol                             0x13C24
	#define mutex_lock_symbol                                0x13C1C
	#define mutex_lock_ex_symbol                             0x1F60C
	#define mutex_trylock_symbol                             0x13C18
	#define mutex_unlock_symbol                              0x13C14

	#define cond_create_symbol                               0x13DF8
	#define cond_destroy_symbol                              0x13DA8
	#define cond_wait_symbol                                 0x13DA0
	#define cond_wait_ex_symbol                              0x20BF8
	#define cond_signal_symbol                               0x13D7C
	#define cond_signal_all_symbol                           0x13D58

	#define semaphore_initialize_symbol                      0x34574
	#define semaphore_wait_ex_symbol                         0x3427C
	#define semaphore_trywait_symbol                         0x33E64
	#define semaphore_post_ex_symbol                         0x33FB0

	#define event_port_create_symbol                         0x136C8
	#define event_port_destroy_symbol                        0x13B30
	#define event_port_connect_symbol                        0x13BA8
	#define event_port_disconnect_symbol                     0x13AD4
	#define event_port_send_symbol                           0x136C0
	#define event_port_send_ex_symbol                        0x2D2C8

	#define event_queue_create_symbol                        0x139D0
	#define event_queue_destroy_symbol                       0x13958
	#define event_queue_receive_symbol                       0x1379C
	#define event_queue_tryreceive_symbol                    0x13868

	#define cellFsOpen_symbol                                0x2B2898
	#define cellFsClose_symbol                               0x2B2700
	#define cellFsRead_symbol                                0x2B283C
	#define cellFsWrite_symbol                               0x2B27A8
	#define cellFsLseek_symbol                               0x2B1FFC
	#define cellFsStat_symbol                                0x2B20B4
	#define cellFsUtime_symbol                               0x2B3A24
	#define cellFsUnlink_internal_symbol                     0x1A29D8
	#define cellFsRename_internal_symbol                     0x19D490

	#define cellFsUtilMount_symbol                           0x2B1D70
	#define cellFsUtilUmount_symbol                          0x2B1D44
	#define cellFsUtilNewfs_symbol                           0x2B36BC

	#define pathdup_from_user_symbol                         0x2B7B5C
	#define open_path_symbol                                 0x2B25D0
	#define open_fs_object_symbol                            0x190CFC
	#define close_fs_object_symbol                           0x18FC38

	#define storage_get_device_info_symbol                   0x28CA00
	#define storage_get_device_config_symbol                 0x28B08C
	#define storage_open_symbol                              0x28CC28
	#define storage_close_symbol                             0x28B414
	#define storage_read_symbol                              0x28A390
	#define storage_write_symbol                             0x28A260
	#define storage_send_device_command_symbol               0x289EB0
	#define storage_map_io_memory_symbol                     0x28C8AC
	#define storage_unmap_io_memory_symbol                   0x28C768
	#define new_medium_listener_object_symbol                0x9CC34
	#define delete_medium_listener_object_symbol             0x9E46C
	#define set_medium_event_callbacks_symbol                0x9E7D0

	#define cellUsbdRegisterLdd_symbol                       0x266758
	#define cellUsbdUnregisterLdd_symbol                     0x266708
	#define cellUsbdScanStaticDescriptor_symbol              0x267958
	#define cellUsbdOpenPipe_symbol                          0x267A08
	#define cellUsbdClosePipe_symbol                         0x2679B8
	#define cellUsbdControlTransfer_symbol                   0x2678BC
	#define cellUsbdBulkTransfer_symbol                      0x26783C

	#define decrypt_func_symbol                              0x38290
	#define lv1_call_99_wrapper_symbol                       0x52850
	#define modules_verification_symbol                      0x5C488
	#define authenticate_program_segment_symbol              0x5E2E0

	#define prx_load_module_symbol                           0x8D308
	#define prx_start_module_symbol                          0x8BFD4
	#define prx_stop_module_symbol                           0x8D3AC
	#define prx_unload_module_symbol                         0x8BD08
	#define prx_get_module_info_symbol                       0x8B700
	#define prx_get_module_id_by_address_symbol              0x8B610
	#define prx_get_module_id_by_name_symbol                 0x8B660
	#define prx_get_module_list_symbol                       0x8B780
	#define load_module_by_fd_symbol                         0x8C938
	#define parse_sprx_symbol                                0x8A62C
	#define open_prx_object_symbol                           0x835D4
	#define close_prx_object_symbol                          0x83EE4
	#define lock_prx_mutex_symbol                            0x8B5B8
	#define unlock_prx_mutex_symbol                          0x8B5C4

	#define extend_kstack_symbol                             0x73BF4

	#define get_pseudo_random_number_symbol                  0x22E65C
	#define md5_reset_symbol                                 0x1681AC
	#define md5_update_symbol                                0x168C4C
	#define md5_final_symbol                                 0x168DCC
	#define ss_get_open_psid_symbol                          0x230B44
	#define update_mgr_read_eeprom_symbol                    0x229F3C
	#define update_mgr_write_eeprom_symbol                   0x229E70
	#define update_mgr_if_get_token_symbol                   0x22B8B8

	#define ss_params_get_update_status_symbol               0x5445C

	#define sm_get_temperature_symbol                        0x269A84
	#define sm_get_fan_policy_symbol                         0x268E18
	#define sm_set_fan_policy_symbol                         0x26ADE0
	#define sm_get_temperature_patch                         0xC728
	#define sm_get_fan_policy_patch                          0x9EB8
	#define sm_set_fan_policy_patch                          0xA3B4

	#define SHA1_init_symbol                                 0x2F0228
	#define SHA1_update_symbol                               0x2F0288
	#define SHA1_final_symbol                                0x2F043C
	#define aescbccfb_dec_symbol                             0x2EE71C
	#define aescbccfb_enc_symbol                             0x2EE4CC
	#define get_path_by_fd_symbol                            0x2B73F8

	#define ECDSA_1                                          0x5D794
	#define ECDSA_2                                          0x2F46D4
	#define ECDSA_FLAG                                       0x49CA80
	#define sysmem_obj                                       0x49CC38
	#define qa_eeprom_offset                                 0x4C56E

	#define syscall_table_symbol                             0x38A4E8
	#define syscall_call_offset                              0x27DEE4

	#define read_bdvd0_symbol                                0x1AAACC
	#define read_bdvd1_symbol                                0x1AC6F8
	#define read_bdvd2_symbol                                0x1B98B0

	#define storage_internal_get_device_object_symbol        0x289968

	#define hid_mgr_read_usb_symbol                          0x107F48
	#define hid_mgr_read_bt_symbol                           0x101E20

	#define bt_set_controller_info_internal_symbol           0xF5E8C

	#define device_event_port_send_call                      0x296BFC
	#define device_event_port_send_call_restore              0x8C9D2A48

	#define ss_pid_call_1                                    0x21974C

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x834C8
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x8D1A4

	#define shutdown_copy_params_call                        0xAB4C
	#define shutdown_copy_params_call_restore                0xF5635348

	#define fsloop_open_call                                 0x2B2A30
	#define fsloop_close_call                                0x2B2A80
	#define fsloop_read_call                                 0x2B2AC0

	#define shutdown_patch_offset                            0xAB38
	#define module_sdk_version_patch_offset                  0x26D898
	#define module_add_parameter_to_parse_sprxpatch_offset   0x8CA14

	#define user_thread_prio_patch                           0x21EAC
	#define user_thread_prio_patch2                          0x21EBC

	#define lic_patch                                        0x59C00
	#define lic_patch_restore                                0x482584B5
	#define ode_patch                                        0x22DAD0
	#define fix_80010009                                     0x5E0B4
	#define fix_8001003D                                     0x59F5C
	#define fix_8001003E                                     0x5A020
	#define PATCH_JUMP                                       0x59FD4

	#define io_rtoc_entry_1                                  0x2EC0
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65C0

	#define storage_rtoc_entry_1                             0x22B0

	#define device_event_rtoc_entry_1                        0x2638

	#define time_rtoc_entry_1                               -0x75E0
	#define time_rtoc_entry_2                               -0x75E8

	#define thread_rtoc_entry_1                             -0x7660

	#define process_rtoc_entry_1                            -0x77A0

	#define bt_rtoc_entry_1                                 -0x3558

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x26DB0
	#define permissions_exception2                           0xC8A08
	#define permissions_exception3                           0x21F80

	#define patch_data1_offset                               0x409A40
	#define patch_func2                                      0x5D754
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x484E2CF1
	#define patch_func8_offset1                              0x59E84
	#define patch_func8_offset2                              0x59FE4
	#define patch_func8_offset2_restore                      0x4821B4BD
	#define patch_func9_offset                               0x5E0C8
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x3A4A30

	#define mmapper_flags_temp_patch                         0x74C08

	#define rsx_syscall_check                                0x541208
	#define unk_func2_unregister_service                     0x9E900
	#define unk_func3_unregister_service                     0xA3394

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E6000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52C00000056000
	#define PS1_EMU_HASH                                     0xCC2850000009A000
	#define PS1_NETEMU_HASH                                  0xCC28B000000BE000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037C000
	#define BDP_BDVD_HASH                                    0xCC28D00000437000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000044000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F4800000020000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA4D74

	/* vsh */
	#define vsh_text_size                                    0x6C0000
	#define ps2tonet_patch                                   0xCA380
	#define ps2tonet_size_patch                              0xCA374
	#define vmode_patch_offset                               0x44ADCC
	#define psp_drm_patch1                                   0x24A7E8
	#define psp_drm_patch2                                   0x24B288
	#define psp_drm_patch3                                   0x24AEC4
	#define psp_drm_patch4                                   0x24B6D0
	#define psp_drm_patchA                                   0x24A904
	#define psp_drm_patchB                                   0x24B1A4
	#define psp_drm_patchC                                   0x24A33C
	#define psp_drm_patchD                                   0x24A8EC
	#define psp_drm_patchE                                   0x24A8F0
	#define psp_drm_patchF                                   0x24B2BC
	#define psp_extra_drm_patch                              0x24D318

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDDDC4
	#define app_home_offset                                  0x2515B0

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68264

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23DAC
	#define ps_region_error_offset                           0x687C
	#define remote_play_offset                               0x5FC0
	#define ps2_nonbw_offset3                                0x172F0

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EEF4
	#define patch2_nas                                       0x2F058
	#define patch3_nas                                       0x1FA0C

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x20234
	#define pspemu_path_offset                               0x4C868
	#define psptrans_path_offset                             0x4C920

	/* download_plugin */
	#define elf_patch1_download                              0x42DC0
	#define elf_patch2_download                              0x42DC8
	#define elf_patch3_download                              0x4D718
	#define elf_patch4_download                              0x4E538
	#define elf_patch5_download                              0x4E558
	#define elf_patch6_download                              0x4E628

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x824B8
	#define elf_patch2_autodownload                          0x824C0

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* CEX */
	#define cex_ps2tonet_patch                               0xC4E34
	#define cex_ps2tonet_size_patch                          0xC4E28
	#define cex_vmode_patch_offset                           0x4431D8
	#define cex_psp_drm_patch1                               0x242FC0
	#define cex_psp_drm_patch2                               0x243A60
	#define cex_psp_drm_patch3                               0x24369C
	#define cex_psp_drm_patch4                               0x243EA8
	#define cex_psp_drm_patchA                               0x2430DC
	#define cex_psp_drm_patchB                               0x24397C
	#define cex_psp_drm_patchC                               0x242B14
	#define cex_psp_drm_patchD                               0x2430C4
	#define cex_psp_drm_patchE                               0x2430C8
	#define cex_psp_drm_patchF                               0x243A94
	#define cex_psp_extra_drm_patch                          0x245AF0
#endif

#ifdef FIRMWARE_482C

	#define FIRMWARE_VERSION                                 0x482

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2E30ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474AF4ULL
		#define PS3MAPI_PSID                                 0x8000000000474B0CULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x34FBB0

	#define create_kernel_object_symbol                      0x11FB0
	#define destroy_kernel_object_symbol                     0x11914
	#define destroy_shared_kernel_object_symbol              0x11288
	#define open_kernel_object_symbol                        0x12600
	#define open_shared_kernel_object_symbol                 0x12410
	#define close_kernel_object_handle_symbol                0x11A30

	#define alloc_symbol                                     0x64824
	#define dealloc_symbol                                   0x64C60
	#define copy_to_user_symbol                              0xF86C
	#define copy_from_user_symbol                            0xFA88
	#define copy_to_process_symbol                           0xF924
	#define copy_from_process_symbol                         0xF734
	#define process_read_memory_symbol                       0x267EC0
	#define process_write_memory_symbol                      0x267D34
	#define page_allocate_symbol                             0x60394
	#define page_free_symbol                                 0x5FDF8
	#define page_export_to_proc_symbol                       0x60530
	#define page_unexport_from_proc_symbol                   0x5FCEC
	#define kernel_ea_to_lpar_addr_symbol                    0x7014C
	#define process_ea_to_lpar_addr_ex_symbol                0x77760
	#define set_pte_symbol                                   0x5E390
	#define map_process_memory_symbol                        0x7726C
	#define panic_symbol                                     0x26D5C8

	#define memcpy_symbol                                    0x7E92C
	#define memset_symbol                                    0x4D66C
	#define memcmp_symbol                                    0x4C97C
	#define memchr_symbol                                    0x4C92C
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
	#define strrchr_symbol                                   0x4D950

	#define spin_lock_irqsave_ex_symbol                      0x26D798
	#define spin_unlock_irqrestore_ex_symbol                 0x26D76C

	#define create_process_common_symbol                     0x26B534
	#define create_process_base_symbol                       0x26ABF0
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x26B340

	#define ppu_thread_create_symbol                         0x13EC8
	#define ppu_thread_exit_symbol                           0x13F80
	#define ppu_thread_join_symbol                           0x13FD4
	#define ppu_thread_delay_symbol                          0x287A4
	#define create_kernel_thread_symbol                      0x24B20
	#define create_user_thread_symbol                        0x2525C
	#define create_user_thread2_symbol                       0x25080
	#define start_thread_symbol                              0x23D4C
	#define run_thread_symbol                                0x2357C
	#define self_threading_symbol                            0x25868
	#define register_thread_symbol                           0x26794C
	#define allocate_user_stack_symbol                       0x268134
	#define deallocate_user_stack_symbol                     0x26809C

	#define mutex_create_symbol                              0x1363C
	#define mutex_destroy_symbol                             0x135D4
	#define mutex_lock_symbol                                0x135CC
	#define mutex_lock_ex_symbol                             0x1DB5C
	#define mutex_trylock_symbol                             0x135C8
	#define mutex_unlock_symbol                              0x135C4

	#define cond_create_symbol                               0x137A8
	#define cond_destroy_symbol                              0x13758
	#define cond_wait_symbol                                 0x13750
	#define cond_wait_ex_symbol                              0x1F148
	#define cond_signal_symbol                               0x1372C
	#define cond_signal_all_symbol                           0x13708

	#define semaphore_initialize_symbol                      0x30C54
	#define semaphore_wait_ex_symbol                         0x3095C
	#define semaphore_trywait_symbol                         0x30544
	#define semaphore_post_ex_symbol                         0x30690

	#define event_port_create_symbol                         0x13078
	#define event_port_destroy_symbol                        0x134E0
	#define event_port_connect_symbol                        0x13558
	#define event_port_disconnect_symbol                     0x13484
	#define event_port_send_symbol                           0x13070
	#define event_port_send_ex_symbol                        0x2B204

	#define event_queue_create_symbol                        0x13380
	#define event_queue_destroy_symbol                       0x13308
	#define event_queue_receive_symbol                       0x1314C
	#define event_queue_tryreceive_symbol                    0x13218

	#define cellFsOpen_symbol                                0x297900
	#define cellFsClose_symbol                               0x297768
	#define cellFsRead_symbol                                0x2978A4
	#define cellFsWrite_symbol                               0x297810
	#define cellFsLseek_symbol                               0x296E98
	#define cellFsStat_symbol                                0x29711C
	#define cellFsUtime_symbol                               0x298C08
	#define cellFsUnlink_internal_symbol                     0x19C64C
	#define cellFsRename_internal_symbol                     0x197104

	#define cellFsUtilMount_symbol                           0x296C78
	#define cellFsUtilUmount_symbol                          0x298654
	#define cellFsUtilNewfs_symbol                           0x2986A0

	#define pathdup_from_user_symbol                         0x29C8E4
	#define open_path_symbol                                 0x297638
	#define open_fs_object_symbol                            0x18A970
	#define close_fs_object_symbol                           0x1898AC

	#define storage_get_device_info_symbol                   0x279B00
	#define storage_get_device_config_symbol                 0x278F90
	#define storage_open_symbol                              0x279510
	#define storage_close_symbol                             0x279300
	#define storage_read_symbol                              0x278870
	#define storage_write_symbol                             0x278740
	#define storage_send_device_command_symbol               0x2783FC
	#define storage_map_io_memory_symbol                     0x2799BC
	#define storage_unmap_io_memory_symbol                   0x279888
	#define new_medium_listener_object_symbol                0x974C4
	#define delete_medium_listener_object_symbol             0x98CFC
	#define set_medium_event_callbacks_symbol                0x99060

	#define cellUsbdRegisterLdd_symbol                       0x26027C
	#define cellUsbdUnregisterLdd_symbol                     0x26022C
	#define cellUsbdScanStaticDescriptor_symbol              0x26147C
	#define cellUsbdOpenPipe_symbol                          0x26152C
	#define cellUsbdClosePipe_symbol                         0x2614DC
	#define cellUsbdControlTransfer_symbol                   0x2613E0
	#define cellUsbdBulkTransfer_symbol                      0x261360

	#define decrypt_func_symbol                              0x34970
	#define lv1_call_99_wrapper_symbol                       0x4EEA8
	#define modules_verification_symbol                      0x58AB8
	#define authenticate_program_segment_symbol              0x5A910

	#define prx_load_module_symbol                           0x88C04
	#define prx_start_module_symbol                          0x878D0
	#define prx_stop_module_symbol                           0x88CA8
	#define prx_unload_module_symbol                         0x87604
	#define prx_get_module_info_symbol                       0x8708C
	#define prx_get_module_id_by_address_symbol              0x86F9C
	#define prx_get_module_id_by_name_symbol                 0x86FEC
	#define prx_get_module_list_symbol                       0x8710C
	#define load_module_by_fd_symbol                         0x88234
	#define parse_sprx_symbol                                0x85FB8
	#define open_prx_object_symbol                           0x7F4F8
	#define close_prx_object_symbol                          0x7FE08
	#define lock_prx_mutex_symbol                            0x86F44
	#define unlock_prx_mutex_symbol                          0x86F50

	#define extend_kstack_symbol                             0x700A4

	#define get_pseudo_random_number_symbol                  0x228180
	#define md5_reset_symbol                                 0x161E20
	#define md5_update_symbol                                0x1628C0
	#define md5_final_symbol                                 0x162A40
	#define ss_get_open_psid_symbol                          0x22A668
	#define update_mgr_read_eeprom_symbol                    0x223A78
	#define update_mgr_write_eeprom_symbol                   0x2239C0
	#define update_mgr_if_get_token_symbol                   0x2253DC

	#define ss_params_get_update_status_symbol               0x50AB4

	#define sm_get_temperature_symbol                        0x2635A8
	#define sm_get_fan_policy_symbol                         0x26293C
	#define sm_set_fan_policy_symbol                         0x264734
	#define sm_get_temperature_patch                         0xC6A8
	#define sm_get_fan_policy_patch                          0x9E38
	#define sm_set_fan_policy_patch                          0xA334

	#define SHA1_init_symbol                                 0x2CE688
	#define SHA1_update_symbol                               0x2CE6E8
	#define SHA1_final_symbol                                0x2CE89C
	#define aescbccfb_dec_symbol                             0x2CCB7C
	#define aescbccfb_enc_symbol                             0x2CC92C
	#define get_path_by_fd_symbol                            0x29C180

	#define ECDSA_1                                          0x59DC4
	#define ECDSA_2                                          0x2D2B34
	#define ECDSA_FLAG                                       0x474A80
	#define sysmem_obj                                       0x474C38
	#define qa_eeprom_offset                                 0x48C0A

	#define syscall_table_symbol                             0x363BE0
	#define syscall_call_offset                              0x275C04

	#define read_bdvd0_symbol                                0x1A461C
	#define read_bdvd1_symbol                                0x1A6248
	#define read_bdvd2_symbol                                0x1B3400

	#define storage_internal_get_device_object_symbol        0x277EB4

	#define hid_mgr_read_usb_symbol                          0x102444
	#define hid_mgr_read_bt_symbol                           0xFC31C

	#define bt_set_controller_info_internal_symbol           0xF0388

	#define device_event_port_send_call                      0x28206C
	#define device_event_port_send_call_restore              0x410D94B

	#define ss_pid_call_1                                    0x21329C

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7F3EC
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x88AA0

	#define shutdown_copy_params_call                        0xAACC
	#define shutdown_copy_params_call_restore                0xBD4F0048

	#define fsloop_open_call                                 0x297A98
	#define fsloop_close_call                                0x297AE8
	#define fsloop_read_call                                 0x297B28

	#define shutdown_patch_offset                            0xAAB8
	#define module_sdk_version_patch_offset                  0x26717C
	#define module_add_parameter_to_parse_sprxpatch_offset   0x88310

	#define user_thread_prio_patch                           0x203FC
	#define user_thread_prio_patch2                          0x2040C

	#define lic_patch                                        0x56230
	#define lic_patch_restore                                0x48240EED
	#define ode_patch                                        0x2275F4
	#define fix_80010009                                     0x5A6E4
	#define fix_8001003D                                     0x5658C
	#define fix_8001003E                                     0x56650
	#define PATCH_JUMP                                       0x56604

	#define io_rtoc_entry_1                                  0x25B8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0

	#define storage_rtoc_entry_1                             0x1DD8

	#define device_event_rtoc_entry_1                        0x2048

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x3680

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x25100
	#define permissions_exception2                           0xC3298
	#define permissions_exception3                           0x204D0

	#define patch_data1_offset                               0x3E2E40
	#define patch_func2                                      0x59D84
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDABC1
	#define patch_func8_offset1                              0x564B4
	#define patch_func8_offset2                              0x56614
	#define patch_func8_offset2_restore                      0x48216FB5
	#define patch_func9_offset                               0x5A6F8
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x37DE30

	#define mmapper_flags_temp_patch                         0x70F78

	#define rsx_syscall_check                                0x7E4C
	#define unk_func2_unregister_service                     0x99190
	#define unk_func3_unregister_service                     0x9DC24

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E3000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52D00000056000
	#define PS1_EMU_HASH                                     0xCC2840000009B000
	#define PS1_NETEMU_HASH                                  0xCC284000000BE000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037C000
	#define BDP_BDVD_HASH                                    0xCC28D00000437000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000044000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F470000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA4E74

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4E34
	#define ps2tonet_size_patch                              0xC4E28
	#define vmode_patch_offset                               0x4431DC
	#define psp_drm_patch1                                   0x242FC0
	#define psp_drm_patch2                                   0x243A60
	#define psp_drm_patch3                                   0x24369C
	#define psp_drm_patch4                                   0x243EA8
	#define psp_drm_patchA                                   0x2430DC
	#define psp_drm_patchB                                   0x24397C
	#define psp_drm_patchC                                   0x242B14
	#define psp_drm_patchD                                   0x2430C4
	#define psp_drm_patchE                                   0x2430C8
	#define psp_drm_patchF                                   0x243A94
	#define psp_extra_drm_patch                              0x245AF0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDD9B4
	#define app_home_offset                                  0x250A00

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68324

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23B90
	#define ps_region_error_offset                           0x68C0
	#define remote_play_offset                               0x5FC0
	#define ps2_nonbw_offset3                                0x17000

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EAE4
	#define patch2_nas                                       0x2EC48
	#define patch3_nas                                       0x1F75C

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F78C
	#define pspemu_path_offset                               0x4B688
	#define psptrans_path_offset                             0x4B718

	/* download_plugin */
	#define elf_patch1_download                              0x42E2C
	#define elf_patch2_download                              0x42E34
	#define elf_patch3_download                              0x4D7F8
	#define elf_patch4_download                              0x4E618
	#define elf_patch5_download                              0x4E638
	#define elf_patch6_download                              0x4E708

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x82650
	#define elf_patch2_autodownload                          0x82658

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                        0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH                 0xDE52C00000056000
	#define GAME_EXT_PLUGIN_REBUG_HASH                       0xCC2680000001E000
	#define dex_ps2_nonbw_offset                             0xDDDC4
	#define dex_ps2_nonbw_offset2                            0x68264
	#define dex_ps2_nonbw_offset3                            0x172F0
	#define dex_ps2tonet_patch                               0xCA380
	#define dex_ps2tonet_size_patch                          0xCA374
	#define dex_vmode_patch_offset                           0x44ADD0
	#define dex_psp_drm_patch1                               0x24A7E8
	#define dex_psp_drm_patch2                               0x24B288
	#define dex_psp_drm_patch3                               0x24AEC4
	#define dex_psp_drm_patch4                               0x24B6D0
	#define dex_psp_drm_patchA                               0x24A904
	#define dex_psp_drm_patchB                               0x24B1A4
	#define dex_psp_drm_patchC                               0x24A33C
	#define dex_psp_drm_patchD                               0x24A8EC
	#define dex_psp_drm_patchE                               0x24A8F0
	#define dex_psp_drm_patchF                               0x24B2BC
	#define dex_psp_extra_drm_patch                          0x24D318
#endif

#ifdef FIRMWARE_482D

	#define FIRMWARE_VERSION                                 0x482

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x8000000000409A30ULL
		#define PS3MAPI_IDPS_2                               0x800000000049CAF4ULL
		#define PS3MAPI_PSID                                 0x800000000049CB0CULL
	#endif
	#define FIRMWARE_DEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x3759C0

	#define create_kernel_object_symbol                      0x125F8
	#define destroy_kernel_object_symbol                     0x11F5C
	#define destroy_shared_kernel_object_symbol              0x118D0
	#define open_kernel_object_symbol                        0x12C48
	#define open_shared_kernel_object_symbol                 0x12A58
	#define close_kernel_object_handle_symbol                0x12078

	#define alloc_symbol                                     0x681F4
	#define dealloc_symbol                                   0x68630
	#define copy_to_user_symbol                              0xFEB4
	#define copy_from_user_symbol                            0x100D0
	#define copy_to_process_symbol                           0xFF6C
	#define copy_from_process_symbol                         0xFD7C
	#define process_read_memory_symbol                       0x26E7E4
	#define process_write_memory_symbol                      0x26E658
	#define page_allocate_symbol                             0x63D64
	#define page_free_symbol                                 0x637C8
	#define page_export_to_proc_symbol                       0x63F00
	#define page_unexport_from_proc_symbol                   0x636BC
	#define kernel_ea_to_lpar_addr_symbol                    0x73C9C
	#define process_ea_to_lpar_addr_ex_symbol                0x7B83C
	#define set_pte_symbol                                   0x61D60
	#define map_process_memory_symbol                        0x7B348
	#define panic_symbol                                     0x2754A0

	#define memcpy_symbol                                    0x82A08
	#define memset_symbol                                    0x51014
	#define memcmp_symbol                                    0x50324
	#define memchr_symbol                                    0x502D4
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
	#define strrchr_symbol                                   0x512F8

	#define spin_lock_irqsave_ex_symbol                      0x275670
	#define spin_unlock_irqrestore_ex_symbol                 0x275644

	#define create_process_common_symbol                     0x272468
	#define create_process_base_symbol                       0x271B00
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x272268

	#define ppu_thread_create_symbol                         0x145FC
	#define ppu_thread_exit_symbol                           0x146B4
	#define ppu_thread_join_symbol                           0x14708
	#define ppu_thread_delay_symbol                          0x2A6E8
	#define create_kernel_thread_symbol                      0x267D0
	#define create_user_thread_symbol                        0x26F0C
	#define create_user_thread2_symbol                       0x26D30
	#define start_thread_symbol                              0x25868
	#define run_thread_symbol                                0x2502C
	#define self_threading_symbol                            0x27518
	#define register_thread_symbol                           0x26E270
	#define allocate_user_stack_symbol                       0x26EA58
	#define deallocate_user_stack_symbol                     0x26E9C0

	#define mutex_create_symbol                              0x13C8C
	#define mutex_destroy_symbol                             0x13C24
	#define mutex_lock_symbol                                0x13C1C
	#define mutex_lock_ex_symbol                             0x1F60C
	#define mutex_trylock_symbol                             0x13C18
	#define mutex_unlock_symbol                              0x13C14

	#define cond_create_symbol                               0x13DF8
	#define cond_destroy_symbol                              0x13DA8
	#define cond_wait_symbol                                 0x13DA0
	#define cond_wait_ex_symbol                              0x20BF8
	#define cond_signal_symbol                               0x13D7C
	#define cond_signal_all_symbol                           0x13D58

	#define semaphore_initialize_symbol                      0x34574
	#define semaphore_wait_ex_symbol                         0x3427C
	#define semaphore_trywait_symbol                         0x33E64
	#define semaphore_post_ex_symbol                         0x33FB0

	#define event_port_create_symbol                         0x136C8
	#define event_port_destroy_symbol                        0x13B30
	#define event_port_connect_symbol                        0x13BA8
	#define event_port_disconnect_symbol                     0x13AD4
	#define event_port_send_symbol                           0x136C0
	#define event_port_send_ex_symbol                        0x2D2C8

	#define event_queue_create_symbol                        0x139D0
	#define event_queue_destroy_symbol                       0x13958
	#define event_queue_receive_symbol                       0x1379C
	#define event_queue_tryreceive_symbol                    0x13868

	#define cellFsOpen_symbol                                0x2B2898
	#define cellFsClose_symbol                               0x2B2700
	#define cellFsRead_symbol                                0x2B283C
	#define cellFsWrite_symbol                               0x2B27A8
	#define cellFsLseek_symbol                               0x2B1FFC
	#define cellFsStat_symbol                                0x2B20B4
	#define cellFsUtime_symbol                               0x2B3A24
	#define cellFsUnlink_internal_symbol                     0x1A29D8
	#define cellFsRename_internal_symbol                     0x19D490

	#define cellFsUtilMount_symbol                           0x2B1D70
	#define cellFsUtilUmount_symbol                          0x2B1D44
	#define cellFsUtilNewfs_symbol                           0x2B36BC

	#define pathdup_from_user_symbol                         0x2B7B5C
	#define open_path_symbol                                 0x2B25D0
	#define open_fs_object_symbol                            0x190CFC
	#define close_fs_object_symbol                           0x18FC38

	#define storage_get_device_info_symbol                   0x28CA00
	#define storage_get_device_config_symbol                 0x28B08C
	#define storage_open_symbol                              0x28CC28
	#define storage_close_symbol                             0x28B414
	#define storage_read_symbol                              0x28A390
	#define storage_write_symbol                             0x28A260
	#define storage_send_device_command_symbol               0x289EB0
	#define storage_map_io_memory_symbol                     0x28C8AC
	#define storage_unmap_io_memory_symbol                   0x28C768
	#define new_medium_listener_object_symbol                0x9CC34
	#define delete_medium_listener_object_symbol             0x9E46C
	#define set_medium_event_callbacks_symbol                0x9E7D0

	#define cellUsbdRegisterLdd_symbol                       0x266758
	#define cellUsbdUnregisterLdd_symbol                     0x266708
	#define cellUsbdScanStaticDescriptor_symbol              0x267958
	#define cellUsbdOpenPipe_symbol                          0x267A08
	#define cellUsbdClosePipe_symbol                         0x2679B8
	#define cellUsbdControlTransfer_symbol                   0x2678BC
	#define cellUsbdBulkTransfer_symbol                      0x26783C

	#define decrypt_func_symbol                              0x38290
	#define lv1_call_99_wrapper_symbol                       0x52850
	#define modules_verification_symbol                      0x5C488
	#define authenticate_program_segment_symbol              0x5E2E0

	#define prx_load_module_symbol                           0x8D308
	#define prx_start_module_symbol                          0x8BFD4
	#define prx_stop_module_symbol                           0x8D3AC
	#define prx_unload_module_symbol                         0x8BD08
	#define prx_get_module_info_symbol                       0x8B700
	#define prx_get_module_id_by_address_symbol              0x8B610
	#define prx_get_module_id_by_name_symbol                 0x8B660
	#define prx_get_module_list_symbol                       0x8B780
	#define load_module_by_fd_symbol                         0x8C938
	#define parse_sprx_symbol                                0x8A62C
	#define open_prx_object_symbol                           0x835D4
	#define close_prx_object_symbol                          0x83EE4
	#define lock_prx_mutex_symbol                            0x8B5B8
	#define unlock_prx_mutex_symbol                          0x8B5C4

	#define extend_kstack_symbol                             0x73BF4

	#define get_pseudo_random_number_symbol                  0x22E65C
	#define md5_reset_symbol                                 0x1681AC
	#define md5_update_symbol                                0x168C4C
	#define md5_final_symbol                                 0x168DCC
	#define ss_get_open_psid_symbol                          0x230B44
	#define update_mgr_read_eeprom_symbol                    0x229F3C
	#define update_mgr_write_eeprom_symbol                   0x229E70
	#define update_mgr_if_get_token_symbol                   0x22B8B8

	#define ss_params_get_update_status_symbol               0x5445C

	#define sm_get_temperature_symbol                        0x269A84
	#define sm_get_fan_policy_symbol                         0x268E18
	#define sm_set_fan_policy_symbol                         0x26ADE0
	#define sm_get_temperature_patch                         0xC728
	#define sm_get_fan_policy_patch                          0x9EB8
	#define sm_set_fan_policy_patch                          0xA3B4

	#define SHA1_init_symbol                                 0x2F0228
	#define SHA1_update_symbol                               0x2F0288
	#define SHA1_final_symbol                                0x2F043C
	#define aescbccfb_dec_symbol                             0x2EE71C
	#define aescbccfb_enc_symbol                             0x2EE4CC
	#define get_path_by_fd_symbol                            0x2B73F8

	#define ECDSA_1                                          0x5D794
	#define ECDSA_2                                          0x2F46D4
	#define ECDSA_FLAG                                       0x49CA80
	#define sysmem_obj                                       0x49CC38
	#define qa_eeprom_offset                                 0x4C56E

	#define syscall_table_symbol                             0x38A4E8
	#define syscall_call_offset                              0x27DEE4

	#define read_bdvd0_symbol                                0x1AAACC
	#define read_bdvd1_symbol                                0x1AC6F8
	#define read_bdvd2_symbol                                0x1B98B0

	#define storage_internal_get_device_object_symbol        0x289968

	#define hid_mgr_read_usb_symbol                          0x107F48
	#define hid_mgr_read_bt_symbol                           0x101E20

	#define bt_set_controller_info_internal_symbol           0xF5E8C

	#define device_event_port_send_call                      0x296BFC
	#define device_event_port_send_call_restore              0xC4CAD74B

	#define ss_pid_call_1                                    0x21974C

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x834C8
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x8D1A4

	#define shutdown_copy_params_call                        0xAB4C
	#define shutdown_copy_params_call_restore                0x85550048

	#define fsloop_open_call                                 0x2B2A30
	#define fsloop_close_call                                0x2B2A80
	#define fsloop_read_call                                 0x2B2AC0

	#define shutdown_patch_offset                            0xAB38
	#define module_sdk_version_patch_offset                  0x26D898
	#define module_add_parameter_to_parse_sprxpatch_offset   0x8CA14

	#define user_thread_prio_patch                           0x21EAC
	#define user_thread_prio_patch2                          0x21EBC

	#define lic_patch                                        0x59C00
	#define lic_patch_restore                                0x482584B5
	#define ode_patch                                        0x22DAD0
	#define fix_80010009                                     0x5E0B4
	#define fix_8001003D                                     0x59F5C
	#define fix_8001003E                                     0x5A020
	#define PATCH_JUMP                                       0x59FD4

	#define io_rtoc_entry_1                                  0x2EC0
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65C0

	#define storage_rtoc_entry_1                             0x22B0

	#define device_event_rtoc_entry_1                        0x2638

	#define time_rtoc_entry_1                               -0x75E0
	#define time_rtoc_entry_2                               -0x75E8

	#define thread_rtoc_entry_1                             -0x7660

	#define process_rtoc_entry_1                            -0x77A0

	#define bt_rtoc_entry_1                                 -0x3558

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x26DB0
	#define permissions_exception2                           0xC8A08
	#define permissions_exception3                           0x21F80

	#define patch_data1_offset                               0x409A40
	#define patch_func2                                      0x5D754
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDAB11
	#define patch_func8_offset1                              0x59E84
	#define patch_func8_offset2                              0x59FE4
	#define patch_func8_offset2_restore                      0x4821B4BD
	#define patch_func9_offset                               0x5E0C8
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x3A4A30

	#define mmapper_flags_temp_patch                         0x74C08

	#define rsx_syscall_check                                0x7E4C
	#define unk_func2_unregister_service                     0x9E900
	#define unk_func3_unregister_service                     0xA3394

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E6000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52C00000056000
	#define PS1_EMU_HASH                                     0xCC2840000009B000
	#define PS1_NETEMU_HASH                                  0xCC284000000BE000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037C000
	#define BDP_BDVD_HASH                                    0xCC28D00000437000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000044000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F4800000020000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA4E74

	/* vsh */
	#define vsh_text_size                                    0x6C0000
	#define ps2tonet_patch                                   0xCA380
	#define ps2tonet_size_patch                              0xCA374
	#define vmode_patch_offset                               0x44ADD0
	#define psp_drm_patch1                                   0x24A7E8
	#define psp_drm_patch2                                   0x24B288
	#define psp_drm_patch3                                   0x24AEC4
	#define psp_drm_patch4                                   0x24B6D0
	#define psp_drm_patchA                                   0x24A904
	#define psp_drm_patchB                                   0x24B1A4
	#define psp_drm_patchC                                   0x24A33C
	#define psp_drm_patchD                                   0x24A8EC
	#define psp_drm_patchE                                   0x24A8F0
	#define psp_drm_patchF                                   0x24B2BC
	#define psp_extra_drm_patch                              0x24D318

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDDDC4
	#define app_home_offset                                  0x2515B0

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68264

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23DAC
	#define ps_region_error_offset                           0x687C
	#define remote_play_offset                               0x5FC0
	#define ps2_nonbw_offset3                                0x172F0

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EEF4
	#define patch2_nas                                       0x2F058
	#define patch3_nas                                       0x1FA0C

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x20234
	#define pspemu_path_offset                               0x4C868
	#define psptrans_path_offset                             0x4C920

	/* download_plugin */
	#define elf_patch1_download                              0x42DC0
	#define elf_patch2_download                              0x42DC8
	#define elf_patch3_download                              0x4D718
	#define elf_patch4_download                              0x4E538
	#define elf_patch5_download                              0x4E558
	#define elf_patch6_download                              0x4E628

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x824B8
	#define elf_patch2_autodownload                          0x824C0

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* CEX */
	#define cex_ps2tonet_patch                               0xC4E34
	#define cex_ps2tonet_size_patch                          0xC4E28
	#define cex_vmode_patch_offset                           0x4431DC
	#define cex_psp_drm_patch1                               0x242FC0
	#define cex_psp_drm_patch2                               0x243A60
	#define cex_psp_drm_patch3                               0x24369C
	#define cex_psp_drm_patch4                               0x243EA8
	#define cex_psp_drm_patchA                               0x2430DC
	#define cex_psp_drm_patchB                               0x24397C
	#define cex_psp_drm_patchC                               0x242B14
	#define cex_psp_drm_patchD                               0x2430C4
	#define cex_psp_drm_patchE                               0x2430C8
	#define cex_psp_drm_patchF                               0x243A94
	#define cex_psp_extra_drm_patch                          0x245AF0
#endif

#ifdef FIRMWARE_483C

	#define FIRMWARE_VERSION                                 0x483

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2E30ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474AF4ULL
		#define PS3MAPI_PSID                                 0x8000000000474B0CULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x34FBB0

	#define create_kernel_object_symbol                      0x11FB0
	#define destroy_kernel_object_symbol                     0x11914
	#define destroy_shared_kernel_object_symbol              0x11288
	#define open_kernel_object_symbol                        0x12600
	#define open_shared_kernel_object_symbol                 0x12410
	#define close_kernel_object_handle_symbol                0x11A30

	#define alloc_symbol                                     0x64824
	#define dealloc_symbol                                   0x64C60
	#define copy_to_user_symbol                              0xF86C
	#define copy_from_user_symbol                            0xFA88
	#define copy_to_process_symbol                           0xF924
	#define copy_from_process_symbol                         0xF734
	#define process_read_memory_symbol                       0x267EC0
	#define process_write_memory_symbol                      0x267D34
	#define page_allocate_symbol                             0x60394
	#define page_free_symbol                                 0x5FDF8
	#define page_export_to_proc_symbol                       0x60530
	#define page_unexport_from_proc_symbol                   0x5FCEC
	#define kernel_ea_to_lpar_addr_symbol                    0x7014C
	#define process_ea_to_lpar_addr_ex_symbol                0x77760
	#define set_pte_symbol                                   0x5E390
	#define map_process_memory_symbol                        0x7726C
	#define panic_symbol                                     0x26D5C8

	#define memcpy_symbol                                    0x7E92C
	#define memset_symbol                                    0x4D66C
	#define memcmp_symbol                                    0x4C97C
	#define memchr_symbol                                    0x4C92C
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
	#define strrchr_symbol                                   0x4D950

	#define spin_lock_irqsave_ex_symbol                      0x26D798
	#define spin_unlock_irqrestore_ex_symbol                 0x26D76C

	#define create_process_common_symbol                     0x26B534
	#define create_process_base_symbol                       0x26ABF0
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x26B340

	#define ppu_thread_create_symbol                         0x13EC8
	#define ppu_thread_exit_symbol                           0x13F80
	#define ppu_thread_join_symbol                           0x13FD4
	#define ppu_thread_delay_symbol                          0x287A4
	#define create_kernel_thread_symbol                      0x24B20
	#define create_user_thread_symbol                        0x2525C
	#define create_user_thread2_symbol                       0x25080
	#define start_thread_symbol                              0x23D4C
	#define run_thread_symbol                                0x2357C
	#define self_threading_symbol                            0x25868
	#define register_thread_symbol                           0x26794C
	#define allocate_user_stack_symbol                       0x268134
	#define deallocate_user_stack_symbol                     0x26809C

	#define mutex_create_symbol                              0x1363C
	#define mutex_destroy_symbol                             0x135D4
	#define mutex_lock_symbol                                0x135CC
	#define mutex_lock_ex_symbol                             0x1DB5C
	#define mutex_trylock_symbol                             0x135C8
	#define mutex_unlock_symbol                              0x135C4

	#define cond_create_symbol                               0x137A8
	#define cond_destroy_symbol                              0x13758
	#define cond_wait_symbol                                 0x13750
	#define cond_wait_ex_symbol                              0x1F148
	#define cond_signal_symbol                               0x1372C
	#define cond_signal_all_symbol                           0x13708

	#define semaphore_initialize_symbol                      0x30C54
	#define semaphore_wait_ex_symbol                         0x3095C
	#define semaphore_trywait_symbol                         0x30544
	#define semaphore_post_ex_symbol                         0x30690

	#define event_port_create_symbol                         0x13078
	#define event_port_destroy_symbol                        0x134E0
	#define event_port_connect_symbol                        0x13558
	#define event_port_disconnect_symbol                     0x13484
	#define event_port_send_symbol                           0x13070
	#define event_port_send_ex_symbol                        0x2B204

	#define event_queue_create_symbol                        0x13380
	#define event_queue_destroy_symbol                       0x13308
	#define event_queue_receive_symbol                       0x1314C
	#define event_queue_tryreceive_symbol                    0x13218

	#define cellFsOpen_symbol                                0x297900
	#define cellFsClose_symbol                               0x297768
	#define cellFsRead_symbol                                0x2978A4
	#define cellFsWrite_symbol                               0x297810
	#define cellFsLseek_symbol                               0x296E98
	#define cellFsStat_symbol                                0x29711C
	#define cellFsUtime_symbol                               0x298C08
	#define cellFsUnlink_internal_symbol                     0x19C64C
	#define cellFsRename_internal_symbol                     0x197104

	#define cellFsUtilMount_symbol                           0x296C78
	#define cellFsUtilUmount_symbol                          0x298654
	#define cellFsUtilNewfs_symbol                           0x2986A0

	#define pathdup_from_user_symbol                         0x29C8E4
	#define open_path_symbol                                 0x297638
	#define open_fs_object_symbol                            0x18A970
	#define close_fs_object_symbol                           0x1898AC

	#define storage_get_device_info_symbol                   0x279B00
	#define storage_get_device_config_symbol                 0x278F90
	#define storage_open_symbol                              0x279510
	#define storage_close_symbol                             0x279300
	#define storage_read_symbol                              0x278870
	#define storage_write_symbol                             0x278740
	#define storage_send_device_command_symbol               0x2783FC
	#define storage_map_io_memory_symbol                     0x2799BC
	#define storage_unmap_io_memory_symbol                   0x279888
	#define new_medium_listener_object_symbol                0x974C4
	#define delete_medium_listener_object_symbol             0x98CFC
	#define set_medium_event_callbacks_symbol                0x99060

	#define cellUsbdRegisterLdd_symbol                       0x26027C
	#define cellUsbdUnregisterLdd_symbol                     0x26022C
	#define cellUsbdScanStaticDescriptor_symbol              0x26147C
	#define cellUsbdOpenPipe_symbol                          0x26152C
	#define cellUsbdClosePipe_symbol                         0x2614DC
	#define cellUsbdControlTransfer_symbol                   0x2613E0
	#define cellUsbdBulkTransfer_symbol                      0x261360

	#define decrypt_func_symbol                              0x34970
	#define lv1_call_99_wrapper_symbol                       0x4EEA8
	#define modules_verification_symbol                      0x58AB8
	#define authenticate_program_segment_symbol              0x5A910

	#define prx_load_module_symbol                           0x88C04
	#define prx_start_module_symbol                          0x878D0
	#define prx_stop_module_symbol                           0x88CA8
	#define prx_unload_module_symbol                         0x87604
	#define prx_get_module_info_symbol                       0x8708C
	#define prx_get_module_id_by_address_symbol              0x86F9C
	#define prx_get_module_id_by_name_symbol                 0x86FEC
	#define prx_get_module_list_symbol                       0x8710C
	#define load_module_by_fd_symbol                         0x88234
	#define parse_sprx_symbol                                0x85FB8
	#define open_prx_object_symbol                           0x7F4F8
	#define close_prx_object_symbol                          0x7FE08
	#define lock_prx_mutex_symbol                            0x86F44
	#define unlock_prx_mutex_symbol                          0x86F50

	#define extend_kstack_symbol                             0x700A4

	#define get_pseudo_random_number_symbol                  0x228180
	#define md5_reset_symbol                                 0x161E20
	#define md5_update_symbol                                0x1628C0
	#define md5_final_symbol                                 0x162A40
	#define ss_get_open_psid_symbol                          0x22A668
	#define update_mgr_read_eeprom_symbol                    0x223A78
	#define update_mgr_write_eeprom_symbol                   0x2239C0
	#define update_mgr_if_get_token_symbol                   0x2253DC

	#define ss_params_get_update_status_symbol               0x50AB4

	#define sm_get_temperature_symbol                        0x2635A8
	#define sm_get_fan_policy_symbol                         0x26293C
	#define sm_set_fan_policy_symbol                         0x264734
	#define sm_get_temperature_patch                         0xC6A8
	#define sm_get_fan_policy_patch                          0x9E38
	#define sm_set_fan_policy_patch                          0xA334

	#define SHA1_init_symbol                                 0x2CE688
	#define SHA1_update_symbol                               0x2CE6E8
	#define SHA1_final_symbol                                0x2CE89C
	#define aescbccfb_dec_symbol                             0x2CCB7C
	#define aescbccfb_enc_symbol                             0x2CC92C
	#define get_path_by_fd_symbol                            0x29C180

	#define ECDSA_1                                          0x59DC4
	#define ECDSA_2                                          0x2D2B34
	#define ECDSA_FLAG                                       0x474A80
	#define sysmem_obj                                       0x474C38
	#define qa_eeprom_offset                                 0x48C0A

	#define syscall_table_symbol                             0x363BE0
	#define syscall_call_offset                              0x275C04

	#define read_bdvd0_symbol                                0x1A461C
	#define read_bdvd1_symbol                                0x1A6248
	#define read_bdvd2_symbol                                0x1B3400

	#define storage_internal_get_device_object_symbol        0x277EB4

	#define hid_mgr_read_usb_symbol                          0x102444
	#define hid_mgr_read_bt_symbol                           0xFC31C

	#define bt_set_controller_info_internal_symbol           0xF0388

	#define device_event_port_send_call                      0x28206C
	#define device_event_port_send_call_restore              0x1CE92748

	#define ss_pid_call_1                                    0x21329C

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7F3EC
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x88AA0

	#define shutdown_copy_params_call                        0xAACC
	#define shutdown_copy_params_call_restore                0x75644F48

	#define fsloop_open_call                                 0x297A98
	#define fsloop_close_call                                0x297AE8
	#define fsloop_read_call                                 0x297B28

	#define shutdown_patch_offset                            0xAAB8
	#define module_sdk_version_patch_offset                  0x26717C
	#define module_add_parameter_to_parse_sprxpatch_offset   0x88310

	#define user_thread_prio_patch                           0x203FC
	#define user_thread_prio_patch2                          0x2040C

	#define lic_patch                                        0x56230
	#define lic_patch_restore                                0x48240EED
	#define ode_patch                                        0x2275F4
	#define fix_80010009                                     0x5A6E4
	#define fix_8001003D                                     0x5658C
	#define fix_8001003E                                     0x56650
	#define PATCH_JUMP                                       0x56604

	#define io_rtoc_entry_1                                  0x25B8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0

	#define storage_rtoc_entry_1                             0x1DD8

	#define device_event_rtoc_entry_1                        0x2048

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x3680

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x25100
	#define permissions_exception2                           0xC3298
	#define permissions_exception3                           0x204D0

	#define patch_data1_offset                               0x3E2E40
	#define patch_func2                                      0x59D84
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x484A66C1
	#define patch_func8_offset1                              0x564B4
	#define patch_func8_offset2                              0x56614
	#define patch_func8_offset2_restore                      0x48216FB5
	#define patch_func9_offset                               0x5A6F8
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x37DE30

	#define mmapper_flags_temp_patch                         0x70F78

	#define rsx_syscall_check                                0x501208
	#define unk_func2_unregister_service                     0x99190
	#define unk_func3_unregister_service                     0x9DC24

	/* lv1 */
	#define vsh_pos_in_ram                                   0x510000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E3000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52D00000056000
	#define PS1_EMU_HASH                                     0xCC2840000009B000
	#define PS1_NETEMU_HASH                                  0xCC284000000BE000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037C000
	#define BDP_BDVD_HASH                                    0xCC28D00000437000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000044000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F470000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA4E74

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4E34
	#define ps2tonet_size_patch                              0xC4E28
	#define vmode_patch_offset                               0x4431DC
	#define psp_drm_patch1                                   0x242FC0
	#define psp_drm_patch2                                   0x243A60
	#define psp_drm_patch3                                   0x24369C
	#define psp_drm_patch4                                   0x243EA8
	#define psp_drm_patchA                                   0x2430DC
	#define psp_drm_patchB                                   0x24397C
	#define psp_drm_patchC                                   0x242B14
	#define psp_drm_patchD                                   0x2430C4
	#define psp_drm_patchE                                   0x2430C8
	#define psp_drm_patchF                                   0x243A94
	#define psp_extra_drm_patch                              0x245AF0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDD9B4
	#define app_home_offset                                  0x250A00

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68324

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23B90
	#define ps_region_error_offset                           0x68C0
	#define remote_play_offset                               0x5FC0
	#define ps2_nonbw_offset3                                0x17000

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EAE4
	#define patch2_nas                                       0x2EC48
	#define patch3_nas                                       0x1F75C

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F78C
	#define pspemu_path_offset                               0x4B688
	#define psptrans_path_offset                             0x4B718

	/* download_plugin */
	#define elf_patch1_download                              0x42E2C
	#define elf_patch2_download                              0x42E34
	#define elf_patch3_download                              0x4D7F8
	#define elf_patch4_download                              0x4E618
	#define elf_patch5_download                              0x4E638
	#define elf_patch6_download                              0x4E708

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x82650
	#define elf_patch2_autodownload                          0x82658

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070
#endif

#ifdef FIRMWARE_484C

	#define FIRMWARE_VERSION                                 0x484

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2E30ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474AF4ULL
		#define PS3MAPI_PSID                                 0x8000000000474B0CULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x34FBB0

	#define create_kernel_object_symbol                      0x11FB0
	#define destroy_kernel_object_symbol                     0x11914
	#define destroy_shared_kernel_object_symbol              0x11288
	#define open_kernel_object_symbol                        0x12600
	#define open_shared_kernel_object_symbol                 0x12410
	#define close_kernel_object_handle_symbol                0x11A30

	#define alloc_symbol                                     0x64824
	#define dealloc_symbol                                   0x64C60
	#define copy_to_user_symbol                              0xF86C
	#define copy_from_user_symbol                            0xFA88
	#define copy_to_process_symbol                           0xF924
	#define copy_from_process_symbol                         0xF734
	#define process_read_memory_symbol                       0x267EC0
	#define process_write_memory_symbol                      0x267D34
	#define page_allocate_symbol                             0x60394
	#define page_free_symbol                                 0x5FDF8
	#define page_export_to_proc_symbol                       0x60530
	#define page_unexport_from_proc_symbol                   0x5FCEC
	#define kernel_ea_to_lpar_addr_symbol                    0x7014C
	#define process_ea_to_lpar_addr_ex_symbol                0x77760
	#define set_pte_symbol                                   0x5E390
	#define map_process_memory_symbol                        0x7726C
	#define panic_symbol                                     0x26D5C8

	#define memcpy_symbol                                    0x7E92C
	#define memset_symbol                                    0x4D66C
	#define memcmp_symbol                                    0x4C97C
	#define memchr_symbol                                    0x4C92C
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
	#define strrchr_symbol                                   0x4D950

	#define spin_lock_irqsave_ex_symbol                      0x26D798
	#define spin_unlock_irqrestore_ex_symbol                 0x26D76C

	#define create_process_common_symbol                     0x26B534
	#define create_process_base_symbol                       0x26ABF0
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x26B340

	#define ppu_thread_create_symbol                         0x13EC8
	#define ppu_thread_exit_symbol                           0x13F80
	#define ppu_thread_join_symbol                           0x13FD4
	#define ppu_thread_delay_symbol                          0x287A4
	#define create_kernel_thread_symbol                      0x24B20
	#define create_user_thread_symbol                        0x2525C
	#define create_user_thread2_symbol                       0x25080
	#define start_thread_symbol                              0x23D4C
	#define run_thread_symbol                                0x2357C
	#define self_threading_symbol                            0x25868
	#define register_thread_symbol                           0x26794C
	#define allocate_user_stack_symbol                       0x268134
	#define deallocate_user_stack_symbol                     0x26809C

	#define mutex_create_symbol                              0x1363C
	#define mutex_destroy_symbol                             0x135D4
	#define mutex_lock_symbol                                0x135CC
	#define mutex_lock_ex_symbol                             0x1DB5C
	#define mutex_trylock_symbol                             0x135C8
	#define mutex_unlock_symbol                              0x135C4

	#define cond_create_symbol                               0x137A8
	#define cond_destroy_symbol                              0x13758
	#define cond_wait_symbol                                 0x13750
	#define cond_wait_ex_symbol                              0x1F148
	#define cond_signal_symbol                               0x1372C
	#define cond_signal_all_symbol                           0x13708

	#define semaphore_initialize_symbol                      0x30C54
	#define semaphore_wait_ex_symbol                         0x3095C
	#define semaphore_trywait_symbol                         0x30544
	#define semaphore_post_ex_symbol                         0x30690

	#define event_port_create_symbol                         0x13078
	#define event_port_destroy_symbol                        0x134E0
	#define event_port_connect_symbol                        0x13558
	#define event_port_disconnect_symbol                     0x13484
	#define event_port_send_symbol                           0x13070
	#define event_port_send_ex_symbol                        0x2B204

	#define event_queue_create_symbol                        0x13380
	#define event_queue_destroy_symbol                       0x13308
	#define event_queue_receive_symbol                       0x1314C
	#define event_queue_tryreceive_symbol                    0x13218

	#define cellFsOpen_symbol                                0x297900
	#define cellFsClose_symbol                               0x297768
	#define cellFsRead_symbol                                0x2978A4
	#define cellFsWrite_symbol                               0x297810
	#define cellFsLseek_symbol                               0x296E98
	#define cellFsStat_symbol                                0x29711C
	#define cellFsUtime_symbol                               0x298C08
	#define cellFsUnlink_internal_symbol                     0x19C64C
	#define cellFsRename_internal_symbol                     0x197104

	#define cellFsUtilMount_symbol                           0x296C78
	#define cellFsUtilUmount_symbol                          0x298654
	#define cellFsUtilNewfs_symbol                           0x2986A0

	#define pathdup_from_user_symbol                         0x29C8E4
	#define open_path_symbol                                 0x297638
	#define open_fs_object_symbol                            0x18A970
	#define close_fs_object_symbol                           0x1898AC

	#define storage_get_device_info_symbol                   0x279B00
	#define storage_get_device_config_symbol                 0x278F90
	#define storage_open_symbol                              0x279510
	#define storage_close_symbol                             0x279300
	#define storage_read_symbol                              0x278870
	#define storage_write_symbol                             0x278740
	#define storage_send_device_command_symbol               0x2783FC
	#define storage_map_io_memory_symbol                     0x2799BC
	#define storage_unmap_io_memory_symbol                   0x279888
	#define new_medium_listener_object_symbol                0x974C4
	#define delete_medium_listener_object_symbol             0x98CFC
	#define set_medium_event_callbacks_symbol                0x99060

	#define cellUsbdRegisterLdd_symbol                       0x26027C
	#define cellUsbdUnregisterLdd_symbol                     0x26022C
	#define cellUsbdScanStaticDescriptor_symbol              0x26147C
	#define cellUsbdOpenPipe_symbol                          0x26152C
	#define cellUsbdClosePipe_symbol                         0x2614DC
	#define cellUsbdControlTransfer_symbol                   0x2613E0
	#define cellUsbdBulkTransfer_symbol                      0x261360

	#define decrypt_func_symbol                              0x34970
	#define lv1_call_99_wrapper_symbol                       0x4EEA8
	#define modules_verification_symbol                      0x58AB8
	#define authenticate_program_segment_symbol              0x5A910

	#define prx_load_module_symbol                           0x88C04
	#define prx_start_module_symbol                          0x878D0
	#define prx_stop_module_symbol                           0x88CA8
	#define prx_unload_module_symbol                         0x87604
	#define prx_get_module_info_symbol                       0x8708C
	#define prx_get_module_id_by_address_symbol              0x86F9C
	#define prx_get_module_id_by_name_symbol                 0x86FEC
	#define prx_get_module_list_symbol                       0x8710C
	#define load_module_by_fd_symbol                         0x88234
	#define parse_sprx_symbol                                0x85FB8
	#define open_prx_object_symbol                           0x7F4F8
	#define close_prx_object_symbol                          0x7FE08
	#define lock_prx_mutex_symbol                            0x86F44
	#define unlock_prx_mutex_symbol                          0x86F50

	#define extend_kstack_symbol                             0x700A4

	#define get_pseudo_random_number_symbol                  0x228180
	#define md5_reset_symbol                                 0x161E20
	#define md5_update_symbol                                0x1628C0
	#define md5_final_symbol                                 0x162A40
	#define ss_get_open_psid_symbol                          0x22A668
	#define update_mgr_read_eeprom_symbol                    0x223A78
	#define update_mgr_write_eeprom_symbol                   0x2239C0
	#define update_mgr_if_get_token_symbol                   0x2253DC

	#define ss_params_get_update_status_symbol               0x50AB4

	#define sm_get_temperature_symbol                        0x2635A8
	#define sm_get_fan_policy_symbol                         0x26293C
	#define sm_set_fan_policy_symbol                         0x264734
	#define sm_get_temperature_patch                         0xC6A8
	#define sm_get_fan_policy_patch                          0x9E38
	#define sm_set_fan_policy_patch                          0xA334

	#define SHA1_init_symbol                                 0x2CE688
	#define SHA1_update_symbol                               0x2CE6E8
	#define SHA1_final_symbol                                0x2CE89C
	#define aescbccfb_dec_symbol                             0x2CCB7C
	#define aescbccfb_enc_symbol                             0x2CC92C
	#define get_path_by_fd_symbol                            0x29C180

	#define ECDSA_1                                          0x59DC4
	#define ECDSA_2                                          0x2D2B34
	#define ECDSA_FLAG                                       0x474A80
	#define sysmem_obj                                       0x474C38
	#define qa_eeprom_offset                                 0x48C0A

	#define syscall_table_symbol                             0x363BE0
	#define syscall_call_offset                              0x275C04

	#define read_bdvd0_symbol                                0x1A461C
	#define read_bdvd1_symbol                                0x1A6248
	#define read_bdvd2_symbol                                0x1B3400

	#define storage_internal_get_device_object_symbol        0x277EB4

	#define hid_mgr_read_usb_symbol                          0x102444
	#define hid_mgr_read_bt_symbol                           0xFC31C

	#define bt_set_controller_info_internal_symbol           0xF0388

	#define device_event_port_send_call                      0x28206C
	#define device_event_port_send_call_restore              0x410D94B

	#define ss_pid_call_1                                    0x21329C

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7F3EC
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x88AA0

	#define shutdown_copy_params_call                        0xAACC
	#define shutdown_copy_params_call_restore                0xBD4F0048

	#define fsloop_open_call                                 0x297A98
	#define fsloop_close_call                                0x297AE8
	#define fsloop_read_call                                 0x297B28

	#define shutdown_patch_offset                            0xAAB8
	#define module_sdk_version_patch_offset                  0x26717C
	#define module_add_parameter_to_parse_sprxpatch_offset   0x88310

	#define user_thread_prio_patch                           0x203FC
	#define user_thread_prio_patch2                          0x2040C

	#define lic_patch                                        0x56230
	#define lic_patch_restore                                0x48240EED
	#define ode_patch                                        0x2275F4
	#define fix_80010009                                     0x5A6E4
	#define fix_8001003D                                     0x5658C
	#define fix_8001003E                                     0x56650
	#define PATCH_JUMP                                       0x56604

	#define io_rtoc_entry_1                                  0x25B8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0

	#define storage_rtoc_entry_1                             0x1DD8

	#define device_event_rtoc_entry_1                        0x2048

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x3680

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x25100
	#define permissions_exception2                           0xC3298
	#define permissions_exception3                           0x204D0

	#define patch_data1_offset                               0x3E2E40
	#define patch_func2                                      0x59D84
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDABC1
	#define patch_func8_offset1                              0x564B4
	#define patch_func8_offset2                              0x56614
	#define patch_func8_offset2_restore                      0x48216FB5
	#define patch_func9_offset                               0x5A6F8
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x37DE30

	#define mmapper_flags_temp_patch                         0x70F78

	#define rsx_syscall_check                                0x7E4C
	#define unk_func2_unregister_service                     0x99190
	#define unk_func3_unregister_service                     0x9DC24

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E3000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52D00000056000
	#define PS1_EMU_HASH                                     0xCC2840000009B000
	#define PS1_NETEMU_HASH                                  0xCC284000000BE000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037C000
	#define BDP_BDVD_HASH                                    0xCC28D00000437000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000044000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F470000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA4E74

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4E34
	#define ps2tonet_size_patch                              0xC4E28
	#define vmode_patch_offset                               0x4431DC
	#define psp_drm_patch1                                   0x242FC0
	#define psp_drm_patch2                                   0x243A60
	#define psp_drm_patch3                                   0x24369C
	#define psp_drm_patch4                                   0x243EA8
	#define psp_drm_patchA                                   0x2430DC
	#define psp_drm_patchB                                   0x24397C
	#define psp_drm_patchC                                   0x242B14
	#define psp_drm_patchD                                   0x2430C4
	#define psp_drm_patchE                                   0x2430C8
	#define psp_drm_patchF                                   0x243A94
	#define psp_extra_drm_patch                              0x245AF0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDD9B4
	#define app_home_offset                                  0x250A00

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68324

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23B90
	#define ps_region_error_offset                           0x68C0
	#define remote_play_offset                               0x5FC0
	#define ps2_nonbw_offset3                                0x17000

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EAE4
	#define patch2_nas                                       0x2EC48
	#define patch3_nas                                       0x1F75C

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F78C
	#define pspemu_path_offset                               0x4B688
	#define psptrans_path_offset                             0x4B718

	/* download_plugin */
	#define elf_patch1_download                              0x42E2C
	#define elf_patch2_download                              0x42E34
	#define elf_patch3_download                              0x4D7F8
	#define elf_patch4_download                              0x4E618
	#define elf_patch5_download                              0x4E638
	#define elf_patch6_download                              0x4E708

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x82650
	#define elf_patch2_autodownload                          0x82658

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* DEX */
	#define EXPLORE_PLUGIN_REBUG_HASH                        0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_REBUG_HASH                 0xDE52C00000056000
	#define GAME_EXT_PLUGIN_REBUG_HASH                       0xCC2680000001E000
	#define dex_ps2_nonbw_offset                             0xDDDC4
	#define dex_ps2_nonbw_offset2                            0x68264
	#define dex_ps2_nonbw_offset3                            0x172F0
	#define dex_ps2tonet_patch                               0xCA380
	#define dex_ps2tonet_size_patch                          0xCA374
	#define dex_vmode_patch_offset                           0x44ADD0
	#define dex_psp_drm_patch1                               0x24A7E8
	#define dex_psp_drm_patch2                               0x24B288
	#define dex_psp_drm_patch3                               0x24AEC4
	#define dex_psp_drm_patch4                               0x24B6D0
	#define dex_psp_drm_patchA                               0x24A904
	#define dex_psp_drm_patchB                               0x24B1A4
	#define dex_psp_drm_patchC                               0x24A33C
	#define dex_psp_drm_patchD                               0x24A8EC
	#define dex_psp_drm_patchE                               0x24A8F0
	#define dex_psp_drm_patchF                               0x24B2BC
	#define dex_psp_extra_drm_patch                          0x24D318
#endif

#ifdef FIRMWARE_484D

	#define FIRMWARE_VERSION                                 0x484

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "DEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x8000000000409A30ULL
		#define PS3MAPI_IDPS_2                               0x800000000049CAF4ULL
		#define PS3MAPI_PSID                                 0x800000000049CB0CULL
	#endif
	#define FIRMWARE_DEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x3759C0

	#define create_kernel_object_symbol                      0x125F8
	#define destroy_kernel_object_symbol                     0x11F5C
	#define destroy_shared_kernel_object_symbol              0x118D0
	#define open_kernel_object_symbol                        0x12C48
	#define open_shared_kernel_object_symbol                 0x12A58
	#define close_kernel_object_handle_symbol                0x12078

	#define alloc_symbol                                     0x681F4
	#define dealloc_symbol                                   0x68630
	#define copy_to_user_symbol                              0xFEB4
	#define copy_from_user_symbol                            0x100D0
	#define copy_to_process_symbol                           0xFF6C
	#define copy_from_process_symbol                         0xFD7C
	#define process_read_memory_symbol                       0x26E7E4
	#define process_write_memory_symbol                      0x26E658
	#define page_allocate_symbol                             0x63D64
	#define page_free_symbol                                 0x637C8
	#define page_export_to_proc_symbol                       0x63F00
	#define page_unexport_from_proc_symbol                   0x636BC
	#define kernel_ea_to_lpar_addr_symbol                    0x73C9C
	#define process_ea_to_lpar_addr_ex_symbol                0x7B83C
	#define set_pte_symbol                                   0x61D60
	#define map_process_memory_symbol                        0x7B348
	#define panic_symbol                                     0x2754A0

	#define memcpy_symbol                                    0x82A08
	#define memset_symbol                                    0x51014
	#define memcmp_symbol                                    0x50324
	#define memchr_symbol                                    0x502D4
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
	#define strrchr_symbol                                   0x512F8

	#define spin_lock_irqsave_ex_symbol                      0x275670
	#define spin_unlock_irqrestore_ex_symbol                 0x275644

	#define create_process_common_symbol                     0x272468
	#define create_process_base_symbol                       0x271B00
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x272268

	#define ppu_thread_create_symbol                         0x145FC
	#define ppu_thread_exit_symbol                           0x146B4
	#define ppu_thread_join_symbol                           0x14708
	#define ppu_thread_delay_symbol                          0x2A6E8
	#define create_kernel_thread_symbol                      0x267D0
	#define create_user_thread_symbol                        0x26F0C
	#define create_user_thread2_symbol                       0x26D30
	#define start_thread_symbol                              0x25868
	#define run_thread_symbol                                0x2502C
	#define self_threading_symbol                            0x27518
	#define register_thread_symbol                           0x26E270
	#define allocate_user_stack_symbol                       0x26EA58
	#define deallocate_user_stack_symbol                     0x26E9C0

	#define mutex_create_symbol                              0x13C8C
	#define mutex_destroy_symbol                             0x13C24
	#define mutex_lock_symbol                                0x13C1C
	#define mutex_lock_ex_symbol                             0x1F60C
	#define mutex_trylock_symbol                             0x13C18
	#define mutex_unlock_symbol                              0x13C14

	#define cond_create_symbol                               0x13DF8
	#define cond_destroy_symbol                              0x13DA8
	#define cond_wait_symbol                                 0x13DA0
	#define cond_wait_ex_symbol                              0x20BF8
	#define cond_signal_symbol                               0x13D7C
	#define cond_signal_all_symbol                           0x13D58

	#define semaphore_initialize_symbol                      0x34574
	#define semaphore_wait_ex_symbol                         0x3427C
	#define semaphore_trywait_symbol                         0x33E64
	#define semaphore_post_ex_symbol                         0x33FB0

	#define event_port_create_symbol                         0x136C8
	#define event_port_destroy_symbol                        0x13B30
	#define event_port_connect_symbol                        0x13BA8
	#define event_port_disconnect_symbol                     0x13AD4
	#define event_port_send_symbol                           0x136C0
	#define event_port_send_ex_symbol                        0x2D2C8

	#define event_queue_create_symbol                        0x139D0
	#define event_queue_destroy_symbol                       0x13958
	#define event_queue_receive_symbol                       0x1379C
	#define event_queue_tryreceive_symbol                    0x13868

	#define cellFsOpen_symbol                                0x2B2898
	#define cellFsClose_symbol                               0x2B2700
	#define cellFsRead_symbol                                0x2B283C
	#define cellFsWrite_symbol                               0x2B27A8
	#define cellFsLseek_symbol                               0x2B1FFC
	#define cellFsStat_symbol                                0x2B20B4
	#define cellFsUtime_symbol                               0x2B3A24
	#define cellFsUnlink_internal_symbol                     0x1A29D8
	#define cellFsRename_internal_symbol                     0x19D490

	#define cellFsUtilMount_symbol                           0x2B1D70
	#define cellFsUtilUmount_symbol                          0x2B1D44
	#define cellFsUtilNewfs_symbol                           0x2B36BC

	#define pathdup_from_user_symbol                         0x2B7B5C
	#define open_path_symbol                                 0x2B25D0
	#define open_fs_object_symbol                            0x190CFC
	#define close_fs_object_symbol                           0x18FC38

	#define storage_get_device_info_symbol                   0x28CA00
	#define storage_get_device_config_symbol                 0x28B08C
	#define storage_open_symbol                              0x28CC28
	#define storage_close_symbol                             0x28B414
	#define storage_read_symbol                              0x28A390
	#define storage_write_symbol                             0x28A260
	#define storage_send_device_command_symbol               0x289EB0
	#define storage_map_io_memory_symbol                     0x28C8AC
	#define storage_unmap_io_memory_symbol                   0x28C768
	#define new_medium_listener_object_symbol                0x9CC34
	#define delete_medium_listener_object_symbol             0x9E46C
	#define set_medium_event_callbacks_symbol                0x9E7D0

	#define cellUsbdRegisterLdd_symbol                       0x266758
	#define cellUsbdUnregisterLdd_symbol                     0x266708
	#define cellUsbdScanStaticDescriptor_symbol              0x267958
	#define cellUsbdOpenPipe_symbol                          0x267A08
	#define cellUsbdClosePipe_symbol                         0x2679B8
	#define cellUsbdControlTransfer_symbol                   0x2678BC
	#define cellUsbdBulkTransfer_symbol                      0x26783C

	#define decrypt_func_symbol                              0x38290
	#define lv1_call_99_wrapper_symbol                       0x52850
	#define modules_verification_symbol                      0x5C488
	#define authenticate_program_segment_symbol              0x5E2E0

	#define prx_load_module_symbol                           0x8D308
	#define prx_start_module_symbol                          0x8BFD4
	#define prx_stop_module_symbol                           0x8D3AC
	#define prx_unload_module_symbol                         0x8BD08
	#define prx_get_module_info_symbol                       0x8B700
	#define prx_get_module_id_by_address_symbol              0x8B610
	#define prx_get_module_id_by_name_symbol                 0x8B660
	#define prx_get_module_list_symbol                       0x8B780
	#define load_module_by_fd_symbol                         0x8C938
	#define parse_sprx_symbol                                0x8A62C
	#define open_prx_object_symbol                           0x835D4
	#define close_prx_object_symbol                          0x83EE4
	#define lock_prx_mutex_symbol                            0x8B5B8
	#define unlock_prx_mutex_symbol                          0x8B5C4

	#define extend_kstack_symbol                             0x73BF4

	#define get_pseudo_random_number_symbol                  0x22E65C
	#define md5_reset_symbol                                 0x1681AC
	#define md5_update_symbol                                0x168C4C
	#define md5_final_symbol                                 0x168DCC
	#define ss_get_open_psid_symbol                          0x230B44
	#define update_mgr_read_eeprom_symbol                    0x229F3C
	#define update_mgr_write_eeprom_symbol                   0x229E70
	#define update_mgr_if_get_token_symbol                   0x22B8B8

	#define ss_params_get_update_status_symbol               0x5445C

	#define sm_get_temperature_symbol                        0x269A84
	#define sm_get_fan_policy_symbol                         0x268E18
	#define sm_set_fan_policy_symbol                         0x26ADE0
	#define sm_get_temperature_patch                         0xC728
	#define sm_get_fan_policy_patch                          0x9EB8
	#define sm_set_fan_policy_patch                          0xA3B4

	#define SHA1_init_symbol                                 0x2F0228
	#define SHA1_update_symbol                               0x2F0288
	#define SHA1_final_symbol                                0x2F043C
	#define aescbccfb_dec_symbol                             0x2EE71C
	#define aescbccfb_enc_symbol                             0x2EE4CC
	#define get_path_by_fd_symbol                            0x2B73F8

	#define ECDSA_1                                          0x5D794
	#define ECDSA_2                                          0x2F46D4
	#define ECDSA_FLAG                                       0x49CA80
	#define sysmem_obj                                       0x49CC38
	#define qa_eeprom_offset                                 0x4C56E

	#define syscall_table_symbol                             0x38A4E8
	#define syscall_call_offset                              0x27DEE4

	#define read_bdvd0_symbol                                0x1AAACC
	#define read_bdvd1_symbol                                0x1AC6F8
	#define read_bdvd2_symbol                                0x1B98B0

	#define storage_internal_get_device_object_symbol        0x289968

	#define hid_mgr_read_usb_symbol                          0x107F48
	#define hid_mgr_read_bt_symbol                           0x101E20

	#define bt_set_controller_info_internal_symbol           0xF5E8C

	#define device_event_port_send_call                      0x296BFC
	#define device_event_port_send_call_restore              0xC4CAD74B

	#define ss_pid_call_1                                    0x21974C

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x834C8
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x8D1A4

	#define shutdown_copy_params_call                        0xAB4C
	#define shutdown_copy_params_call_restore                0x85550048

	#define fsloop_open_call                                 0x2B2A30
	#define fsloop_close_call                                0x2B2A80
	#define fsloop_read_call                                 0x2B2AC0

	#define shutdown_patch_offset                            0xAB38
	#define module_sdk_version_patch_offset                  0x26D898
	#define module_add_parameter_to_parse_sprxpatch_offset   0x8CA14

	#define user_thread_prio_patch                           0x21EAC
	#define user_thread_prio_patch2                          0x21EBC

	#define lic_patch                                        0x59C00
	#define lic_patch_restore                                0x482584B5
	#define ode_patch                                        0x22DAD0
	#define fix_80010009                                     0x5E0B4
	#define fix_8001003D                                     0x59F5C
	#define fix_8001003E                                     0x5A020
	#define PATCH_JUMP                                       0x59FD4

	#define io_rtoc_entry_1                                  0x2EC0
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x65C0

	#define storage_rtoc_entry_1                             0x22B0

	#define device_event_rtoc_entry_1                        0x2638

	#define time_rtoc_entry_1                               -0x75E0
	#define time_rtoc_entry_2                               -0x75E8

	#define thread_rtoc_entry_1                             -0x7660

	#define process_rtoc_entry_1                            -0x77A0

	#define bt_rtoc_entry_1                                 -0x3558

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x26DB0
	#define permissions_exception2                           0xC8A08
	#define permissions_exception3                           0x21F80

	#define patch_data1_offset                               0x409A40
	#define patch_func2                                      0x5D754
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDAB11
	#define patch_func8_offset1                              0x59E84
	#define patch_func8_offset2                              0x59FE4
	#define patch_func8_offset2_restore                      0x4821B4BD
	#define patch_func9_offset                               0x5E0C8
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x3A4A30

	#define mmapper_flags_temp_patch                         0x74C08

	#define rsx_syscall_check                                0x7E4C
	#define unk_func2_unregister_service                     0x9E900
	#define unk_func3_unregister_service                     0xA3394

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E6000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52C00000056000
	#define PS1_EMU_HASH                                     0xCC2840000009B000
	#define PS1_NETEMU_HASH                                  0xCC284000000BE000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037C000
	#define BDP_BDVD_HASH                                    0xCC28D00000437000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000044000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F4800000020000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA4E74

	/* vsh */
	#define vsh_text_size                                    0x6C0000
	#define ps2tonet_patch                                   0xCA380
	#define ps2tonet_size_patch                              0xCA374
	#define vmode_patch_offset                               0x44ADD0
	#define psp_drm_patch1                                   0x24A7E8
	#define psp_drm_patch2                                   0x24B288
	#define psp_drm_patch3                                   0x24AEC4
	#define psp_drm_patch4                                   0x24B6D0
	#define psp_drm_patchA                                   0x24A904
	#define psp_drm_patchB                                   0x24B1A4
	#define psp_drm_patchC                                   0x24A33C
	#define psp_drm_patchD                                   0x24A8EC
	#define psp_drm_patchE                                   0x24A8F0
	#define psp_drm_patchF                                   0x24B2BC
	#define psp_extra_drm_patch                              0x24D318

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDDDC4
	#define app_home_offset                                  0x2515B0

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68264

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23DAC
	#define ps_region_error_offset                           0x687C
	#define remote_play_offset                               0x5FC0
	#define ps2_nonbw_offset3                                0x172F0

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EEF4
	#define patch2_nas                                       0x2F058
	#define patch3_nas                                       0x1FA0C

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x20234
	#define pspemu_path_offset                               0x4C868
	#define psptrans_path_offset                             0x4C920

	/* download_plugin */
	#define elf_patch1_download                              0x42DC0
	#define elf_patch2_download                              0x42DC8
	#define elf_patch3_download                              0x4D718
	#define elf_patch4_download                              0x4E538
	#define elf_patch5_download                              0x4E558
	#define elf_patch6_download                              0x4E628

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x824B8
	#define elf_patch2_autodownload                          0x824C0

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070

	/* CEX */
	#define cex_ps2tonet_patch                               0xC4E34
	#define cex_ps2tonet_size_patch                          0xC4E28
	#define cex_vmode_patch_offset                           0x4431DC
	#define cex_psp_drm_patch1                               0x242FC0
	#define cex_psp_drm_patch2                               0x243A60
	#define cex_psp_drm_patch3                               0x24369C
	#define cex_psp_drm_patch4                               0x243EA8
	#define cex_psp_drm_patchA                               0x2430DC
	#define cex_psp_drm_patchB                               0x24397C
	#define cex_psp_drm_patchC                               0x242B14
	#define cex_psp_drm_patchD                               0x2430C4
	#define cex_psp_drm_patchE                               0x2430C8
	#define cex_psp_drm_patchF                               0x243A94
	#define cex_psp_extra_drm_patch                          0x245AF0
#endif

#ifdef FIRMWARE_485C

	#define FIRMWARE_VERSION                                 0x485

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2E30ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474AF4ULL
		#define PS3MAPI_PSID                                 0x8000000000474B0CULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x34FBB0

	#define create_kernel_object_symbol                      0x11FB0
	#define destroy_kernel_object_symbol                     0x11914
	#define destroy_shared_kernel_object_symbol              0x11288
	#define open_kernel_object_symbol                        0x12600
	#define open_shared_kernel_object_symbol                 0x12410
	#define close_kernel_object_handle_symbol                0x11A30

	#define alloc_symbol                                     0x64824
	#define dealloc_symbol                                   0x64C60
	#define copy_to_user_symbol                              0xF86C
	#define copy_from_user_symbol                            0xFA88
	#define copy_to_process_symbol                           0xF924
	#define copy_from_process_symbol                         0xF734
	#define process_read_memory_symbol                       0x267EC0
	#define process_write_memory_symbol                      0x267D34
	#define page_allocate_symbol                             0x60394
	#define page_free_symbol                                 0x5FDF8
	#define page_export_to_proc_symbol                       0x60530
	#define page_unexport_from_proc_symbol                   0x5FCEC
	#define kernel_ea_to_lpar_addr_symbol                    0x7014C
	#define process_ea_to_lpar_addr_ex_symbol                0x77760
	#define set_pte_symbol                                   0x5E390
	#define map_process_memory_symbol                        0x7726C
	#define panic_symbol                                     0x26D5C8

	#define memcpy_symbol                                    0x7E92C
	#define memset_symbol                                    0x4D66C
	#define memcmp_symbol                                    0x4C97C
	#define memchr_symbol                                    0x4C92C
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
	#define strrchr_symbol                                   0x4D950

	#define spin_lock_irqsave_ex_symbol                      0x26D798
	#define spin_unlock_irqrestore_ex_symbol                 0x26D76C

	#define create_process_common_symbol                     0x26B534
	#define create_process_base_symbol                       0x26ABF0
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x26B340

	#define ppu_thread_create_symbol                         0x13EC8
	#define ppu_thread_exit_symbol                           0x13F80
	#define ppu_thread_join_symbol                           0x13FD4
	#define ppu_thread_delay_symbol                          0x287A4
	#define create_kernel_thread_symbol                      0x24B20
	#define create_user_thread_symbol                        0x2525C
	#define create_user_thread2_symbol                       0x25080
	#define start_thread_symbol                              0x23D4C
	#define run_thread_symbol                                0x2357C
	#define self_threading_symbol                            0x25868
	#define register_thread_symbol                           0x26794C
	#define allocate_user_stack_symbol                       0x268134
	#define deallocate_user_stack_symbol                     0x26809C

	#define mutex_create_symbol                              0x1363C
	#define mutex_destroy_symbol                             0x135D4
	#define mutex_lock_symbol                                0x135CC
	#define mutex_lock_ex_symbol                             0x1DB5C
	#define mutex_trylock_symbol                             0x135C8
	#define mutex_unlock_symbol                              0x135C4

	#define cond_create_symbol                               0x137A8
	#define cond_destroy_symbol                              0x13758
	#define cond_wait_symbol                                 0x13750
	#define cond_wait_ex_symbol                              0x1F148
	#define cond_signal_symbol                               0x1372C
	#define cond_signal_all_symbol                           0x13708

	#define semaphore_initialize_symbol                      0x30C54
	#define semaphore_wait_ex_symbol                         0x3095C
	#define semaphore_trywait_symbol                         0x30544
	#define semaphore_post_ex_symbol                         0x30690

	#define event_port_create_symbol                         0x13078
	#define event_port_destroy_symbol                        0x134E0
	#define event_port_connect_symbol                        0x13558
	#define event_port_disconnect_symbol                     0x13484
	#define event_port_send_symbol                           0x13070
	#define event_port_send_ex_symbol                        0x2B204

	#define event_queue_create_symbol                        0x13380
	#define event_queue_destroy_symbol                       0x13308
	#define event_queue_receive_symbol                       0x1314C
	#define event_queue_tryreceive_symbol                    0x13218

	#define cellFsOpen_symbol                                0x297900
	#define cellFsClose_symbol                               0x297768
	#define cellFsRead_symbol                                0x2978A4
	#define cellFsWrite_symbol                               0x297810
	#define cellFsLseek_symbol                               0x296E98
	#define cellFsStat_symbol                                0x29711C
	#define cellFsUtime_symbol                               0x298C08
	#define cellFsUnlink_internal_symbol                     0x19C64C
	#define cellFsRename_internal_symbol                     0x197104

	#define cellFsUtilMount_symbol                           0x296C78
	#define cellFsUtilUmount_symbol                          0x298654
	#define cellFsUtilNewfs_symbol                           0x2986A0

	#define pathdup_from_user_symbol                         0x29C8E4
	#define open_path_symbol                                 0x297638
	#define open_fs_object_symbol                            0x18A970
	#define close_fs_object_symbol                           0x1898AC

	#define storage_get_device_info_symbol                   0x279B00
	#define storage_get_device_config_symbol                 0x278F90
	#define storage_open_symbol                              0x279510
	#define storage_close_symbol                             0x279300
	#define storage_read_symbol                              0x278870
	#define storage_write_symbol                             0x278740
	#define storage_send_device_command_symbol               0x2783FC
	#define storage_map_io_memory_symbol                     0x2799BC
	#define storage_unmap_io_memory_symbol                   0x279888
	#define new_medium_listener_object_symbol                0x974C4
	#define delete_medium_listener_object_symbol             0x98CFC
	#define set_medium_event_callbacks_symbol                0x99060

	#define cellUsbdRegisterLdd_symbol                       0x26027C
	#define cellUsbdUnregisterLdd_symbol                     0x26022C
	#define cellUsbdScanStaticDescriptor_symbol              0x26147C
	#define cellUsbdOpenPipe_symbol                          0x26152C
	#define cellUsbdClosePipe_symbol                         0x2614DC
	#define cellUsbdControlTransfer_symbol                   0x2613E0
	#define cellUsbdBulkTransfer_symbol                      0x261360

	#define decrypt_func_symbol                              0x34970
	#define lv1_call_99_wrapper_symbol                       0x4EEA8
	#define modules_verification_symbol                      0x58AB8
	#define authenticate_program_segment_symbol              0x5A910

	#define prx_load_module_symbol                           0x88C04
	#define prx_start_module_symbol                          0x878D0
	#define prx_stop_module_symbol                           0x88CA8
	#define prx_unload_module_symbol                         0x87604
	#define prx_get_module_info_symbol                       0x8708C
	#define prx_get_module_id_by_address_symbol              0x86F9C
	#define prx_get_module_id_by_name_symbol                 0x86FEC
	#define prx_get_module_list_symbol                       0x8710C
	#define load_module_by_fd_symbol                         0x88234
	#define parse_sprx_symbol                                0x85FB8
	#define open_prx_object_symbol                           0x7F4F8
	#define close_prx_object_symbol                          0x7FE08
	#define lock_prx_mutex_symbol                            0x86F44
	#define unlock_prx_mutex_symbol                          0x86F50

	#define extend_kstack_symbol                             0x700A4

	#define get_pseudo_random_number_symbol                  0x228180
	#define md5_reset_symbol                                 0x161E20
	#define md5_update_symbol                                0x1628C0
	#define md5_final_symbol                                 0x162A40
	#define ss_get_open_psid_symbol                          0x22A668
	#define update_mgr_read_eeprom_symbol                    0x223A78
	#define update_mgr_write_eeprom_symbol                   0x2239C0
	#define update_mgr_if_get_token_symbol                   0x2253DC

	#define ss_params_get_update_status_symbol               0x50AB4

	#define sm_get_temperature_symbol                        0x2635A8
	#define sm_get_fan_policy_symbol                         0x26293C
	#define sm_set_fan_policy_symbol                         0x264734
	#define sm_get_temperature_patch                         0xC6A8
	#define sm_get_fan_policy_patch                          0x9E38
	#define sm_set_fan_policy_patch                          0xA334

	#define SHA1_init_symbol                                 0x2CE688
	#define SHA1_update_symbol                               0x2CE6E8
	#define SHA1_final_symbol                                0x2CE89C
	#define aescbccfb_dec_symbol                             0x2CCB7C
	#define aescbccfb_enc_symbol                             0x2CC92C
	#define get_path_by_fd_symbol                            0x29C180

	#define ECDSA_1                                          0x59DC4
	#define ECDSA_2                                          0x2D2B34
	#define ECDSA_FLAG                                       0x474A80
	#define sysmem_obj                                       0x474C38
	#define qa_eeprom_offset                                 0x48C0A

	#define syscall_table_symbol                             0x363BE0
	#define syscall_call_offset                              0x275C04

	#define read_bdvd0_symbol                                0x1A461C
	#define read_bdvd1_symbol                                0x1A6248
	#define read_bdvd2_symbol                                0x1B3400

	#define storage_internal_get_device_object_symbol        0x277EB4

	#define hid_mgr_read_usb_symbol                          0x102444
	#define hid_mgr_read_bt_symbol                           0xFC31C

	#define bt_set_controller_info_internal_symbol           0xF0388

	#define device_event_port_send_call                      0x28206C
	#define device_event_port_send_call_restore              0x410D94B

	#define ss_pid_call_1                                    0x21329C

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7F3EC
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x88AA0

	#define shutdown_copy_params_call                        0xAACC
	#define shutdown_copy_params_call_restore                0xBD4F0048

	#define fsloop_open_call                                 0x297A98
	#define fsloop_close_call                                0x297AE8
	#define fsloop_read_call                                 0x297B28

	#define shutdown_patch_offset                            0xAAB8
	#define module_sdk_version_patch_offset                  0x26717C
	#define module_add_parameter_to_parse_sprxpatch_offset   0x88310

	#define user_thread_prio_patch                           0x203FC
	#define user_thread_prio_patch2                          0x2040C

	#define lic_patch                                        0x56230
	#define lic_patch_restore                                0x48240EED
	#define ode_patch                                        0x2275F4
	#define fix_80010009                                     0x5A6E4
	#define fix_8001003D                                     0x5658C
	#define fix_8001003E                                     0x56650
	#define PATCH_JUMP                                       0x56604

	#define io_rtoc_entry_1                                  0x25B8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0

	#define storage_rtoc_entry_1                             0x1DD8

	#define device_event_rtoc_entry_1                        0x2048

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x3680

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x25100
	#define permissions_exception2                           0xC3298
	#define permissions_exception3                           0x204D0

	#define patch_data1_offset                               0x3E2E40
	#define patch_func2                                      0x59D84
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x4BFDABC1
	#define patch_func8_offset1                              0x564B4
	#define patch_func8_offset2                              0x56614
	#define patch_func8_offset2_restore                      0x48216FB5
	#define patch_func9_offset                               0x5A6F8
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x37DE30

	#define mmapper_flags_temp_patch                         0x70F78

	#define rsx_syscall_check                                0x7E4C
	#define unk_func2_unregister_service                     0x99190
	#define unk_func3_unregister_service                     0x9DC24

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E3000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52D00000056000
	#define PS1_EMU_HASH                                     0xCC2840000009B000
	#define PS1_NETEMU_HASH                                  0xCC284000000BE000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037C000
	#define BDP_BDVD_HASH                                    0xCC28D00000437000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000044000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F470000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA4E74

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4E34
	#define ps2tonet_size_patch                              0xC4E28
	#define vmode_patch_offset                               0x4431DC
	#define psp_drm_patch1                                   0x242FC0
	#define psp_drm_patch2                                   0x243A60
	#define psp_drm_patch3                                   0x24369C
	#define psp_drm_patch4                                   0x243EA8
	#define psp_drm_patchA                                   0x2430DC
	#define psp_drm_patchB                                   0x24397C
	#define psp_drm_patchC                                   0x242B14
	#define psp_drm_patchD                                   0x2430C4
	#define psp_drm_patchE                                   0x2430C8
	#define psp_drm_patchF                                   0x243A94
	#define psp_extra_drm_patch                              0x245AF0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDD9B4
	#define app_home_offset                                  0x250A00

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68324

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23B90
	#define ps_region_error_offset                           0x68C0
	#define remote_play_offset                               0x5FC0
	#define ps2_nonbw_offset3                                0x17000

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EAE4
	#define patch2_nas                                       0x2EC48
	#define patch3_nas                                       0x1F75C

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F78C
	#define pspemu_path_offset                               0x4B688
	#define psptrans_path_offset                             0x4B718

	/* download_plugin */
	#define elf_patch1_download                              0x42E2C
	#define elf_patch2_download                              0x42E34
	#define elf_patch3_download                              0x4D7F8
	#define elf_patch4_download                              0x4E618
	#define elf_patch5_download                              0x4E638
	#define elf_patch6_download                              0x4E708

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x82650
	#define elf_patch2_autodownload                          0x82658

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070
#endif

#ifdef FIRMWARE_486C

	#define FIRMWARE_VERSION                                 0x486

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2E30ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474AF4ULL
		#define PS3MAPI_PSID                                 0x8000000000474B0CULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x34FBB0

	#define create_kernel_object_symbol                      0x11FB0
	#define destroy_kernel_object_symbol                     0x11914
	#define destroy_shared_kernel_object_symbol              0x11288
	#define open_kernel_object_symbol                        0x12600
	#define open_shared_kernel_object_symbol                 0x12410
	#define close_kernel_object_handle_symbol                0x11A30

	#define alloc_symbol                                     0x64824
	#define dealloc_symbol                                   0x64C60
	#define copy_to_user_symbol                              0xF86C
	#define copy_from_user_symbol                            0xFA88
	#define copy_to_process_symbol                           0xF924
	#define copy_from_process_symbol                         0xF734
	#define process_read_memory_symbol                       0x267EC0
	#define process_write_memory_symbol                      0x267D34
	#define page_allocate_symbol                             0x60394
	#define page_free_symbol                                 0x5FDF8
	#define page_export_to_proc_symbol                       0x60530
	#define page_unexport_from_proc_symbol                   0x5FCEC
	#define kernel_ea_to_lpar_addr_symbol                    0x7014C
	#define process_ea_to_lpar_addr_ex_symbol                0x77760
	#define set_pte_symbol                                   0x5E390
	#define map_process_memory_symbol                        0x7726C
	#define panic_symbol                                     0x26D5C8

	#define memcpy_symbol                                    0x7E92C
	#define memset_symbol                                    0x4D66C
	#define memcmp_symbol                                    0x4C97C
	#define memchr_symbol                                    0x4C92C
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
	#define strrchr_symbol                                   0x4D950

	#define spin_lock_irqsave_ex_symbol                      0x26D798
	#define spin_unlock_irqrestore_ex_symbol                 0x26D76C

	#define create_process_common_symbol                     0x26B534
	#define create_process_base_symbol                       0x26ABF0
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x26B340

	#define ppu_thread_create_symbol                         0x13EC8
	#define ppu_thread_exit_symbol                           0x13F80
	#define ppu_thread_join_symbol                           0x13FD4
	#define ppu_thread_delay_symbol                          0x287A4
	#define create_kernel_thread_symbol                      0x24B20
	#define create_user_thread_symbol                        0x2525C
	#define create_user_thread2_symbol                       0x25080
	#define start_thread_symbol                              0x23D4C
	#define run_thread_symbol                                0x2357C
	#define self_threading_symbol                            0x25868
	#define register_thread_symbol                           0x26794C
	#define allocate_user_stack_symbol                       0x268134
	#define deallocate_user_stack_symbol                     0x26809C

	#define mutex_create_symbol                              0x1363C
	#define mutex_destroy_symbol                             0x135D4
	#define mutex_lock_symbol                                0x135CC
	#define mutex_lock_ex_symbol                             0x1DB5C
	#define mutex_trylock_symbol                             0x135C8
	#define mutex_unlock_symbol                              0x135C4

	#define cond_create_symbol                               0x137A8
	#define cond_destroy_symbol                              0x13758
	#define cond_wait_symbol                                 0x13750
	#define cond_wait_ex_symbol                              0x1F148
	#define cond_signal_symbol                               0x1372C
	#define cond_signal_all_symbol                           0x13708

	#define semaphore_initialize_symbol                      0x30C54
	#define semaphore_wait_ex_symbol                         0x3095C
	#define semaphore_trywait_symbol                         0x30544
	#define semaphore_post_ex_symbol                         0x30690

	#define event_port_create_symbol                         0x13078
	#define event_port_destroy_symbol                        0x134E0
	#define event_port_connect_symbol                        0x13558
	#define event_port_disconnect_symbol                     0x13484
	#define event_port_send_symbol                           0x13070
	#define event_port_send_ex_symbol                        0x2B204

	#define event_queue_create_symbol                        0x13380
	#define event_queue_destroy_symbol                       0x13308
	#define event_queue_receive_symbol                       0x1314C
	#define event_queue_tryreceive_symbol                    0x13218

	#define cellFsOpen_symbol                                0x297900
	#define cellFsClose_symbol                               0x297768
	#define cellFsRead_symbol                                0x2978A4
	#define cellFsWrite_symbol                               0x297810
	#define cellFsLseek_symbol                               0x296E98
	#define cellFsStat_symbol                                0x29711C
	#define cellFsUtime_symbol                               0x298C08
	#define cellFsUnlink_internal_symbol                     0x19C64C
	#define cellFsRename_internal_symbol                     0x197104

	#define cellFsUtilMount_symbol                           0x296C78
	#define cellFsUtilUmount_symbol                          0x298654
	#define cellFsUtilNewfs_symbol                           0x2986A0

	#define pathdup_from_user_symbol                         0x29C8E4
	#define open_path_symbol                                 0x297638
	#define open_fs_object_symbol                            0x18A970
	#define close_fs_object_symbol                           0x1898AC

	#define storage_get_device_info_symbol                   0x279B00
	#define storage_get_device_config_symbol                 0x278F90
	#define storage_open_symbol                              0x279510
	#define storage_close_symbol                             0x279300
	#define storage_read_symbol                              0x278870
	#define storage_write_symbol                             0x278740
	#define storage_send_device_command_symbol               0x2783FC
	#define storage_map_io_memory_symbol                     0x2799BC
	#define storage_unmap_io_memory_symbol                   0x279888
	#define new_medium_listener_object_symbol                0x974C4
	#define delete_medium_listener_object_symbol             0x98CFC
	#define set_medium_event_callbacks_symbol                0x99060

	#define cellUsbdRegisterLdd_symbol                       0x26027C
	#define cellUsbdUnregisterLdd_symbol                     0x26022C
	#define cellUsbdScanStaticDescriptor_symbol              0x26147C
	#define cellUsbdOpenPipe_symbol                          0x26152C
	#define cellUsbdClosePipe_symbol                         0x2614DC
	#define cellUsbdControlTransfer_symbol                   0x2613E0
	#define cellUsbdBulkTransfer_symbol                      0x261360

	#define decrypt_func_symbol                              0x34970
	#define lv1_call_99_wrapper_symbol                       0x4EEA8
	#define modules_verification_symbol                      0x58AB8
	#define authenticate_program_segment_symbol              0x5A910

	#define prx_load_module_symbol                           0x88C04
	#define prx_start_module_symbol                          0x878D0
	#define prx_stop_module_symbol                           0x88CA8
	#define prx_unload_module_symbol                         0x87604
	#define prx_get_module_info_symbol                       0x8708C
	#define prx_get_module_id_by_address_symbol              0x86F9C
	#define prx_get_module_id_by_name_symbol                 0x86FEC
	#define prx_get_module_list_symbol                       0x8710C
	#define load_module_by_fd_symbol                         0x88234
	#define parse_sprx_symbol                                0x85FB8
	#define open_prx_object_symbol                           0x7F4F8
	#define close_prx_object_symbol                          0x7FE08
	#define lock_prx_mutex_symbol                            0x86F44
	#define unlock_prx_mutex_symbol                          0x86F50

	#define extend_kstack_symbol                             0x700A4

	#define get_pseudo_random_number_symbol                  0x228180
	#define md5_reset_symbol                                 0x161E20
	#define md5_update_symbol                                0x1628C0
	#define md5_final_symbol                                 0x162A40
	#define ss_get_open_psid_symbol                          0x22A668
	#define update_mgr_read_eeprom_symbol                    0x223A78
	#define update_mgr_write_eeprom_symbol                   0x2239C0
	#define update_mgr_if_get_token_symbol                   0x2253DC

	#define ss_params_get_update_status_symbol               0x50AB4

	#define sm_get_temperature_symbol                        0x2635A8
	#define sm_get_fan_policy_symbol                         0x26293C
	#define sm_set_fan_policy_symbol                         0x264734
	#define sm_get_temperature_patch                         0xC6A8
	#define sm_get_fan_policy_patch                          0x9E38
	#define sm_set_fan_policy_patch                          0xA334

	#define SHA1_init_symbol                                 0x2CE688
	#define SHA1_update_symbol                               0x2CE6E8
	#define SHA1_final_symbol                                0x2CE89C
	#define aescbccfb_dec_symbol                             0x2CCB7C
	#define aescbccfb_enc_symbol                             0x2CC92C
	#define get_path_by_fd_symbol                            0x29C180

	#define ECDSA_1                                          0x59DC4
	#define ECDSA_2                                          0x2D2B34
	#define ECDSA_FLAG                                       0x474A80
	#define sysmem_obj                                       0x474C38
	#define qa_eeprom_offset                                 0x48C0A

	#define syscall_table_symbol                             0x363BE0
	#define syscall_call_offset                              0x275C04

	#define read_bdvd0_symbol                                0x1A461C
	#define read_bdvd1_symbol                                0x1A6248
	#define read_bdvd2_symbol                                0x1B3400

	#define storage_internal_get_device_object_symbol        0x277EB4

	#define hid_mgr_read_usb_symbol                          0x102444
	#define hid_mgr_read_bt_symbol                           0xFC31C

	#define bt_set_controller_info_internal_symbol           0xF0388

	#define device_event_port_send_call                      0x28206C
	#define device_event_port_send_call_restore              0x1CE92748

	#define ss_pid_call_1                                    0x21329C

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7F3EC
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x88AA0

	#define shutdown_copy_params_call                        0xAACC
	#define shutdown_copy_params_call_restore                0x75644F48

	#define fsloop_open_call                                 0x297A98
	#define fsloop_close_call                                0x297AE8
	#define fsloop_read_call                                 0x297B28

	#define shutdown_patch_offset                            0xAAB8
	#define module_sdk_version_patch_offset                  0x26717C
	#define module_add_parameter_to_parse_sprxpatch_offset   0x88310

	#define user_thread_prio_patch                           0x203FC
	#define user_thread_prio_patch2                          0x2040C

	#define lic_patch                                        0x56230
	#define lic_patch_restore                                0x48240EED
	#define ode_patch                                        0x2275F4
	#define fix_80010009                                     0x5A6E4
	#define fix_8001003D                                     0x5658C
	#define fix_8001003E                                     0x56650
	#define PATCH_JUMP                                       0x56604

	#define io_rtoc_entry_1                                  0x25B8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0

	#define storage_rtoc_entry_1                             0x1DD8

	#define device_event_rtoc_entry_1                        0x2048

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x3680

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x25100
	#define permissions_exception2                           0xC3298
	#define permissions_exception3                           0x204D0

	#define patch_data1_offset                               0x3E2E40
	#define patch_func2                                      0x59D84
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x484A66C1
	#define patch_func8_offset1                              0x564B4
	#define patch_func8_offset2                              0x56614
	#define patch_func8_offset2_restore                      0x48216FB5
	#define patch_func9_offset                               0x5A6F8
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x37DE30

	#define mmapper_flags_temp_patch                         0x70F78

	#define rsx_syscall_check                                0x501208
	#define unk_func2_unregister_service                     0x99190
	#define unk_func3_unregister_service                     0x9DC24

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E3000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52D00000056000
	#define PS1_EMU_HASH                                     0xCC2840000009B000
	#define PS1_NETEMU_HASH                                  0xCC284000000BE000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037C000
	#define BDP_BDVD_HASH                                    0xCC28D00000437000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000044000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F470000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA4E74

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4E34
	#define ps2tonet_size_patch                              0xC4E28
	#define vmode_patch_offset                               0x4431DC
	#define psp_drm_patch1                                   0x242FC0
	#define psp_drm_patch2                                   0x243A60
	#define psp_drm_patch3                                   0x24369C
	#define psp_drm_patch4                                   0x243EA8
	#define psp_drm_patchA                                   0x2430DC
	#define psp_drm_patchB                                   0x24397C
	#define psp_drm_patchC                                   0x242B14
	#define psp_drm_patchD                                   0x2430C4
	#define psp_drm_patchE                                   0x2430C8
	#define psp_drm_patchF                                   0x243A94
	#define psp_extra_drm_patch                              0x245AF0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDD9B4
	#define app_home_offset                                  0x250A00

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68324

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23B90
	#define ps_region_error_offset                           0x68C0
	#define remote_play_offset                               0x5FC0
	#define ps2_nonbw_offset3                                0x17000

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EAE4
	#define patch2_nas                                       0x2EC48
	#define patch3_nas                                       0x1F75C

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F78C
	#define pspemu_path_offset                               0x4B688
	#define psptrans_path_offset                             0x4B718

	/* download_plugin */
	#define elf_patch1_download                              0x42E2C
	#define elf_patch2_download                              0x42E34
	#define elf_patch3_download                              0x4D7F8
	#define elf_patch4_download                              0x4E618
	#define elf_patch5_download                              0x4E638
	#define elf_patch6_download                              0x4E708

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x82650
	#define elf_patch2_autodownload                          0x82658

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070
#endif

#ifdef FIRMWARE_487C

	#define FIRMWARE_VERSION                                 0x487

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2E30ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474AF4ULL
		#define PS3MAPI_PSID                                 0x8000000000474B0CULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x34FBB0

	#define create_kernel_object_symbol                      0x11FB0
	#define destroy_kernel_object_symbol                     0x11914
	#define destroy_shared_kernel_object_symbol              0x11288
	#define open_kernel_object_symbol                        0x12600
	#define open_shared_kernel_object_symbol                 0x12410
	#define close_kernel_object_handle_symbol                0x11A30

	#define alloc_symbol                                     0x64824
	#define dealloc_symbol                                   0x64C60
	#define copy_to_user_symbol                              0xF86C
	#define copy_from_user_symbol                            0xFA88
	#define copy_to_process_symbol                           0xF924
	#define copy_from_process_symbol                         0xF734
	#define process_read_memory_symbol                       0x267EC0
	#define process_write_memory_symbol                      0x267D34
	#define page_allocate_symbol                             0x60394
	#define page_free_symbol                                 0x5FDF8
	#define page_export_to_proc_symbol                       0x60530
	#define page_unexport_from_proc_symbol                   0x5FCEC
	#define kernel_ea_to_lpar_addr_symbol                    0x7014C
	#define process_ea_to_lpar_addr_ex_symbol                0x77760
	#define set_pte_symbol                                   0x5E390
	#define map_process_memory_symbol                        0x7726C
	#define panic_symbol                                     0x26D5C8

	#define memcpy_symbol                                    0x7E92C
	#define memset_symbol                                    0x4D66C
	#define memcmp_symbol                                    0x4C97C
	#define memchr_symbol                                    0x4C92C
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
	#define strrchr_symbol                                   0x4D950

	#define spin_lock_irqsave_ex_symbol                      0x26D798
	#define spin_unlock_irqrestore_ex_symbol                 0x26D76C

	#define create_process_common_symbol                     0x26B534
	#define create_process_base_symbol                       0x26ABF0
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x26B340

	#define ppu_thread_create_symbol                         0x13EC8
	#define ppu_thread_exit_symbol                           0x13F80
	#define ppu_thread_join_symbol                           0x13FD4
	#define ppu_thread_delay_symbol                          0x287A4
	#define create_kernel_thread_symbol                      0x24B20
	#define create_user_thread_symbol                        0x2525C
	#define create_user_thread2_symbol                       0x25080
	#define start_thread_symbol                              0x23D4C
	#define run_thread_symbol                                0x2357C
	#define self_threading_symbol                            0x25868
	#define register_thread_symbol                           0x26794C
	#define allocate_user_stack_symbol                       0x268134
	#define deallocate_user_stack_symbol                     0x26809C

	#define mutex_create_symbol                              0x1363C
	#define mutex_destroy_symbol                             0x135D4
	#define mutex_lock_symbol                                0x135CC
	#define mutex_lock_ex_symbol                             0x1DB5C
	#define mutex_trylock_symbol                             0x135C8
	#define mutex_unlock_symbol                              0x135C4

	#define cond_create_symbol                               0x137A8
	#define cond_destroy_symbol                              0x13758
	#define cond_wait_symbol                                 0x13750
	#define cond_wait_ex_symbol                              0x1F148
	#define cond_signal_symbol                               0x1372C
	#define cond_signal_all_symbol                           0x13708

	#define semaphore_initialize_symbol                      0x30C54
	#define semaphore_wait_ex_symbol                         0x3095C
	#define semaphore_trywait_symbol                         0x30544
	#define semaphore_post_ex_symbol                         0x30690

	#define event_port_create_symbol                         0x13078
	#define event_port_destroy_symbol                        0x134E0
	#define event_port_connect_symbol                        0x13558
	#define event_port_disconnect_symbol                     0x13484
	#define event_port_send_symbol                           0x13070
	#define event_port_send_ex_symbol                        0x2B204

	#define event_queue_create_symbol                        0x13380
	#define event_queue_destroy_symbol                       0x13308
	#define event_queue_receive_symbol                       0x1314C
	#define event_queue_tryreceive_symbol                    0x13218

	#define cellFsOpen_symbol                                0x297900
	#define cellFsClose_symbol                               0x297768
	#define cellFsRead_symbol                                0x2978A4
	#define cellFsWrite_symbol                               0x297810
	#define cellFsLseek_symbol                               0x296E98
	#define cellFsStat_symbol                                0x29711C
	#define cellFsUtime_symbol                               0x298C08
	#define cellFsUnlink_internal_symbol                     0x19C64C
	#define cellFsRename_internal_symbol                     0x197104

	#define cellFsUtilMount_symbol                           0x296C78
	#define cellFsUtilUmount_symbol                          0x298654
	#define cellFsUtilNewfs_symbol                           0x2986A0

	#define pathdup_from_user_symbol                         0x29C8E4
	#define open_path_symbol                                 0x297638
	#define open_fs_object_symbol                            0x18A970
	#define close_fs_object_symbol                           0x1898AC

	#define storage_get_device_info_symbol                   0x279B00
	#define storage_get_device_config_symbol                 0x278F90
	#define storage_open_symbol                              0x279510
	#define storage_close_symbol                             0x279300
	#define storage_read_symbol                              0x278870
	#define storage_write_symbol                             0x278740
	#define storage_send_device_command_symbol               0x2783FC
	#define storage_map_io_memory_symbol                     0x2799BC
	#define storage_unmap_io_memory_symbol                   0x279888
	#define new_medium_listener_object_symbol                0x974C4
	#define delete_medium_listener_object_symbol             0x98CFC
	#define set_medium_event_callbacks_symbol                0x99060

	#define cellUsbdRegisterLdd_symbol                       0x26027C
	#define cellUsbdUnregisterLdd_symbol                     0x26022C
	#define cellUsbdScanStaticDescriptor_symbol              0x26147C
	#define cellUsbdOpenPipe_symbol                          0x26152C
	#define cellUsbdClosePipe_symbol                         0x2614DC
	#define cellUsbdControlTransfer_symbol                   0x2613E0
	#define cellUsbdBulkTransfer_symbol                      0x261360

	#define decrypt_func_symbol                              0x34970
	#define lv1_call_99_wrapper_symbol                       0x4EEA8
	#define modules_verification_symbol                      0x58AB8
	#define authenticate_program_segment_symbol              0x5A910

	#define prx_load_module_symbol                           0x88C04
	#define prx_start_module_symbol                          0x878D0
	#define prx_stop_module_symbol                           0x88CA8
	#define prx_unload_module_symbol                         0x87604
	#define prx_get_module_info_symbol                       0x8708C
	#define prx_get_module_id_by_address_symbol              0x86F9C
	#define prx_get_module_id_by_name_symbol                 0x86FEC
	#define prx_get_module_list_symbol                       0x8710C
	#define load_module_by_fd_symbol                         0x88234
	#define parse_sprx_symbol                                0x85FB8
	#define open_prx_object_symbol                           0x7F4F8
	#define close_prx_object_symbol                          0x7FE08
	#define lock_prx_mutex_symbol                            0x86F44
	#define unlock_prx_mutex_symbol                          0x86F50

	#define extend_kstack_symbol                             0x700A4

	#define get_pseudo_random_number_symbol                  0x228180
	#define md5_reset_symbol                                 0x161E20
	#define md5_update_symbol                                0x1628C0
	#define md5_final_symbol                                 0x162A40
	#define ss_get_open_psid_symbol                          0x22A668
	#define update_mgr_read_eeprom_symbol                    0x223A78
	#define update_mgr_write_eeprom_symbol                   0x2239C0
	#define update_mgr_if_get_token_symbol                   0x2253DC

	#define ss_params_get_update_status_symbol               0x50AB4

	#define sm_get_temperature_symbol                        0x2635A8
	#define sm_get_fan_policy_symbol                         0x26293C
	#define sm_set_fan_policy_symbol                         0x264734
	#define sm_get_temperature_patch                         0xC6A8
	#define sm_get_fan_policy_patch                          0x9E38
	#define sm_set_fan_policy_patch                          0xA334

	#define SHA1_init_symbol                                 0x2CE688
	#define SHA1_update_symbol                               0x2CE6E8
	#define SHA1_final_symbol                                0x2CE89C
	#define aescbccfb_dec_symbol                             0x2CCB7C
	#define aescbccfb_enc_symbol                             0x2CC92C
	#define get_path_by_fd_symbol                            0x29C180

	#define ECDSA_1                                          0x59DC4
	#define ECDSA_2                                          0x2D2B34
	#define ECDSA_FLAG                                       0x474A80
	#define sysmem_obj                                       0x474C38
	#define qa_eeprom_offset                                 0x48C0A

	#define syscall_table_symbol                             0x363BE0
	#define syscall_call_offset                              0x275C04

	#define read_bdvd0_symbol                                0x1A461C
	#define read_bdvd1_symbol                                0x1A6248
	#define read_bdvd2_symbol                                0x1B3400

	#define storage_internal_get_device_object_symbol        0x277EB4

	#define hid_mgr_read_usb_symbol                          0x102444
	#define hid_mgr_read_bt_symbol                           0xFC31C

	#define bt_set_controller_info_internal_symbol           0xF0388

	#define device_event_port_send_call                      0x28206C
	#define device_event_port_send_call_restore              0x1CE92748

	#define ss_pid_call_1                                    0x21329C

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7F3EC
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x88AA0

	#define shutdown_copy_params_call                        0xAACC
	#define shutdown_copy_params_call_restore                0x75644F48

	#define fsloop_open_call                                 0x297A98
	#define fsloop_close_call                                0x297AE8
	#define fsloop_read_call                                 0x297B28

	#define shutdown_patch_offset                            0xAAB8
	#define module_sdk_version_patch_offset                  0x26717C
	#define module_add_parameter_to_parse_sprxpatch_offset   0x88310

	#define user_thread_prio_patch                           0x203FC
	#define user_thread_prio_patch2                          0x2040C

	#define lic_patch                                        0x56230
	#define lic_patch_restore                                0x48240EED
	#define ode_patch                                        0x2275F4
	#define fix_80010009                                     0x5A6E4
	#define fix_8001003D                                     0x5658C
	#define fix_8001003E                                     0x56650
	#define PATCH_JUMP                                       0x56604

	#define io_rtoc_entry_1                                  0x25B8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0

	#define storage_rtoc_entry_1                             0x1DD8

	#define device_event_rtoc_entry_1                        0x2048

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x3680

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x25100
	#define permissions_exception2                           0xC3298
	#define permissions_exception3                           0x204D0

	#define patch_data1_offset                               0x3E2E40
	#define patch_func2                                      0x59D84
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x484A66C1
	#define patch_func8_offset1                              0x564B4
	#define patch_func8_offset2                              0x56614
	#define patch_func8_offset2_restore                      0x48216FB5
	#define patch_func9_offset                               0x5A6F8
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x37DE30

	#define mmapper_flags_temp_patch                         0x70F78

	#define rsx_syscall_check                                0x501208
	#define unk_func2_unregister_service                     0x99190
	#define unk_func3_unregister_service                     0x9DC24

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E3000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52D00000056000
	#define PS1_EMU_HASH                                     0xCC2840000009B000
	#define PS1_NETEMU_HASH                                  0xCC284000000BE000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037C000
	#define BDP_BDVD_HASH                                    0xCC28D00000437000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000044000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F470000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA4E74

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4E34
	#define ps2tonet_size_patch                              0xC4E28
	#define vmode_patch_offset                               0x4431DC
	#define psp_drm_patch1                                   0x242FC0
	#define psp_drm_patch2                                   0x243A60
	#define psp_drm_patch3                                   0x24369C
	#define psp_drm_patch4                                   0x243EA8
	#define psp_drm_patchA                                   0x2430DC
	#define psp_drm_patchB                                   0x24397C
	#define psp_drm_patchC                                   0x242B14
	#define psp_drm_patchD                                   0x2430C4
	#define psp_drm_patchE                                   0x2430C8
	#define psp_drm_patchF                                   0x243A94
	#define psp_extra_drm_patch                              0x245AF0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDD9B4
	#define app_home_offset                                  0x250A00

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68324

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23B90
	#define ps_region_error_offset                           0x68C0
	#define remote_play_offset                               0x5FC0
	#define ps2_nonbw_offset3                                0x17000

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EAE4
	#define patch2_nas                                       0x2EC48
	#define patch3_nas                                       0x1F75C

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F78C
	#define pspemu_path_offset                               0x4B688
	#define psptrans_path_offset                             0x4B718

	/* download_plugin */
	#define elf_patch1_download                              0x42E2C
	#define elf_patch2_download                              0x42E34
	#define elf_patch3_download                              0x4D7F8
	#define elf_patch4_download                              0x4E618
	#define elf_patch5_download                              0x4E638
	#define elf_patch6_download                              0x4E708

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x82650
	#define elf_patch2_autodownload                          0x82658

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070
#endif

#ifdef FIRMWARE_488C

	#define FIRMWARE_VERSION                                 0x488

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2E30ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474AF4ULL
		#define PS3MAPI_PSID                                 0x8000000000474B0CULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x34FBB0

	#define create_kernel_object_symbol                      0x11FB0
	#define destroy_kernel_object_symbol                     0x11914
	#define destroy_shared_kernel_object_symbol              0x11288
	#define open_kernel_object_symbol                        0x12600
	#define open_shared_kernel_object_symbol                 0x12410
	#define close_kernel_object_handle_symbol                0x11A30

	#define alloc_symbol                                     0x64824
	#define dealloc_symbol                                   0x64C60
	#define copy_to_user_symbol                              0xF86C
	#define copy_from_user_symbol                            0xFA88
	#define copy_to_process_symbol                           0xF924
	#define copy_from_process_symbol                         0xF734
	#define process_read_memory_symbol                       0x267EC0
	#define process_write_memory_symbol                      0x267D34
	#define page_allocate_symbol                             0x60394
	#define page_free_symbol                                 0x5FDF8
	#define page_export_to_proc_symbol                       0x60530
	#define page_unexport_from_proc_symbol                   0x5FCEC
	#define kernel_ea_to_lpar_addr_symbol                    0x7014C
	#define process_ea_to_lpar_addr_ex_symbol                0x77760
	#define set_pte_symbol                                   0x5E390
	#define map_process_memory_symbol                        0x7726C
	#define panic_symbol                                     0x26D5C8

	#define memcpy_symbol                                    0x7E92C
	#define memset_symbol                                    0x4D66C
	#define memcmp_symbol                                    0x4C97C
	#define memchr_symbol                                    0x4C92C
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
	#define strrchr_symbol                                   0x4D950

	#define spin_lock_irqsave_ex_symbol                      0x26D798
	#define spin_unlock_irqrestore_ex_symbol                 0x26D76C

	#define create_process_common_symbol                     0x26B534
	#define create_process_base_symbol                       0x26ABF0
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x26B340

	#define ppu_thread_create_symbol                         0x13EC8
	#define ppu_thread_exit_symbol                           0x13F80
	#define ppu_thread_join_symbol                           0x13FD4
	#define ppu_thread_delay_symbol                          0x287A4
	#define create_kernel_thread_symbol                      0x24B20
	#define create_user_thread_symbol                        0x2525C
	#define create_user_thread2_symbol                       0x25080
	#define start_thread_symbol                              0x23D4C
	#define run_thread_symbol                                0x2357C
	#define self_threading_symbol                            0x25868
	#define register_thread_symbol                           0x26794C
	#define allocate_user_stack_symbol                       0x268134
	#define deallocate_user_stack_symbol                     0x26809C

	#define mutex_create_symbol                              0x1363C
	#define mutex_destroy_symbol                             0x135D4
	#define mutex_lock_symbol                                0x135CC
	#define mutex_lock_ex_symbol                             0x1DB5C
	#define mutex_trylock_symbol                             0x135C8
	#define mutex_unlock_symbol                              0x135C4

	#define cond_create_symbol                               0x137A8
	#define cond_destroy_symbol                              0x13758
	#define cond_wait_symbol                                 0x13750
	#define cond_wait_ex_symbol                              0x1F148
	#define cond_signal_symbol                               0x1372C
	#define cond_signal_all_symbol                           0x13708

	#define semaphore_initialize_symbol                      0x30C54
	#define semaphore_wait_ex_symbol                         0x3095C
	#define semaphore_trywait_symbol                         0x30544
	#define semaphore_post_ex_symbol                         0x30690

	#define event_port_create_symbol                         0x13078
	#define event_port_destroy_symbol                        0x134E0
	#define event_port_connect_symbol                        0x13558
	#define event_port_disconnect_symbol                     0x13484
	#define event_port_send_symbol                           0x13070
	#define event_port_send_ex_symbol                        0x2B204

	#define event_queue_create_symbol                        0x13380
	#define event_queue_destroy_symbol                       0x13308
	#define event_queue_receive_symbol                       0x1314C
	#define event_queue_tryreceive_symbol                    0x13218

	#define cellFsOpen_symbol                                0x297900
	#define cellFsClose_symbol                               0x297768
	#define cellFsRead_symbol                                0x2978A4
	#define cellFsWrite_symbol                               0x297810
	#define cellFsLseek_symbol                               0x296E98
	#define cellFsStat_symbol                                0x29711C
	#define cellFsUtime_symbol                               0x298C08
	#define cellFsUnlink_internal_symbol                     0x19C64C
	#define cellFsRename_internal_symbol                     0x197104

	#define cellFsUtilMount_symbol                           0x296C78
	#define cellFsUtilUmount_symbol                          0x298654
	#define cellFsUtilNewfs_symbol                           0x2986A0

	#define pathdup_from_user_symbol                         0x29C8E4
	#define open_path_symbol                                 0x297638
	#define open_fs_object_symbol                            0x18A970
	#define close_fs_object_symbol                           0x1898AC

	#define storage_get_device_info_symbol                   0x279B00
	#define storage_get_device_config_symbol                 0x278F90
	#define storage_open_symbol                              0x279510
	#define storage_close_symbol                             0x279300
	#define storage_read_symbol                              0x278870
	#define storage_write_symbol                             0x278740
	#define storage_send_device_command_symbol               0x2783FC
	#define storage_map_io_memory_symbol                     0x2799BC
	#define storage_unmap_io_memory_symbol                   0x279888
	#define new_medium_listener_object_symbol                0x974C4
	#define delete_medium_listener_object_symbol             0x98CFC
	#define set_medium_event_callbacks_symbol                0x99060

	#define cellUsbdRegisterLdd_symbol                       0x26027C
	#define cellUsbdUnregisterLdd_symbol                     0x26022C
	#define cellUsbdScanStaticDescriptor_symbol              0x26147C
	#define cellUsbdOpenPipe_symbol                          0x26152C
	#define cellUsbdClosePipe_symbol                         0x2614DC
	#define cellUsbdControlTransfer_symbol                   0x2613E0
	#define cellUsbdBulkTransfer_symbol                      0x261360

	#define decrypt_func_symbol                              0x34970
	#define lv1_call_99_wrapper_symbol                       0x4EEA8
	#define modules_verification_symbol                      0x58AB8
	#define authenticate_program_segment_symbol              0x5A910

	#define prx_load_module_symbol                           0x88C04
	#define prx_start_module_symbol                          0x878D0
	#define prx_stop_module_symbol                           0x88CA8
	#define prx_unload_module_symbol                         0x87604
	#define prx_get_module_info_symbol                       0x8708C
	#define prx_get_module_id_by_address_symbol              0x86F9C
	#define prx_get_module_id_by_name_symbol                 0x86FEC
	#define prx_get_module_list_symbol                       0x8710C
	#define load_module_by_fd_symbol                         0x88234
	#define parse_sprx_symbol                                0x85FB8
	#define open_prx_object_symbol                           0x7F4F8
	#define close_prx_object_symbol                          0x7FE08
	#define lock_prx_mutex_symbol                            0x86F44
	#define unlock_prx_mutex_symbol                          0x86F50

	#define extend_kstack_symbol                             0x700A4

	#define get_pseudo_random_number_symbol                  0x228180
	#define md5_reset_symbol                                 0x161E20
	#define md5_update_symbol                                0x1628C0
	#define md5_final_symbol                                 0x162A40
	#define ss_get_open_psid_symbol                          0x22A668
	#define update_mgr_read_eeprom_symbol                    0x223A78
	#define update_mgr_write_eeprom_symbol                   0x2239C0
	#define update_mgr_if_get_token_symbol                   0x2253DC

	#define ss_params_get_update_status_symbol               0x50AB4

	#define sm_get_temperature_symbol                        0x2635A8
	#define sm_get_fan_policy_symbol                         0x26293C
	#define sm_set_fan_policy_symbol                         0x264734
	#define sm_get_temperature_patch                         0xC6A8
	#define sm_get_fan_policy_patch                          0x9E38
	#define sm_set_fan_policy_patch                          0xA334

	#define SHA1_init_symbol                                 0x2CE688
	#define SHA1_update_symbol                               0x2CE6E8
	#define SHA1_final_symbol                                0x2CE89C
	#define aescbccfb_dec_symbol                             0x2CCB7C
	#define aescbccfb_enc_symbol                             0x2CC92C
	#define get_path_by_fd_symbol                            0x29C180

	#define ECDSA_1                                          0x59DC4
	#define ECDSA_2                                          0x2D2B34
	#define ECDSA_FLAG                                       0x474A80
	#define sysmem_obj                                       0x474C38
	#define qa_eeprom_offset                                 0x48C0A

	#define syscall_table_symbol                             0x363BE0
	#define syscall_call_offset                              0x275C04

	#define read_bdvd0_symbol                                0x1A461C
	#define read_bdvd1_symbol                                0x1A6248
	#define read_bdvd2_symbol                                0x1B3400

	#define storage_internal_get_device_object_symbol        0x277EB4

	#define hid_mgr_read_usb_symbol                          0x102444
	#define hid_mgr_read_bt_symbol                           0xFC31C

	#define bt_set_controller_info_internal_symbol           0xF0388

	#define device_event_port_send_call                      0x28206C
	#define device_event_port_send_call_restore              0x1CE94748

	#define ss_pid_call_1                                    0x21329C

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7F3EC
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x88AA0

	#define shutdown_copy_params_call                        0xAACC
	#define shutdown_copy_params_call_restore                0x75646F48

	#define fsloop_open_call                                 0x297A98
	#define fsloop_close_call                                0x297AE8
	#define fsloop_read_call                                 0x297B28

	#define shutdown_patch_offset                            0xAAB8
	#define module_sdk_version_patch_offset                  0x26717C
	#define module_add_parameter_to_parse_sprxpatch_offset   0x88310

	#define user_thread_prio_patch                           0x203FC
	#define user_thread_prio_patch2                          0x2040C

	#define lic_patch                                        0x56230
	#define lic_patch_restore                                0x48240EED
	#define ode_patch                                        0x2275F4
	#define fix_80010009                                     0x5A6E4
	#define fix_8001003D                                     0x5658C
	#define fix_8001003E                                     0x56650
	#define PATCH_JUMP                                       0x56604

	#define io_rtoc_entry_1                                  0x25B8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0

	#define storage_rtoc_entry_1                             0x1DD8

	#define device_event_rtoc_entry_1                        0x2048

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x3680

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x25100
	#define permissions_exception2                           0xC3298
	#define permissions_exception3                           0x204D0

	#define patch_data1_offset                               0x3E2E40
	#define patch_func2                                      0x59D84
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x486A66C1
	#define patch_func8_offset1                              0x564B4
	#define patch_func8_offset2                              0x56614
	#define patch_func8_offset2_restore                      0x48216FB5
	#define patch_func9_offset                               0x5A6F8
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x37DE30

	#define mmapper_flags_temp_patch                         0x70F78

	#define rsx_syscall_check                                0x701138
	#define unk_func2_unregister_service                     0x99190
	#define unk_func3_unregister_service                     0x9DC24

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E3000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52D00000056000
	#define PS1_EMU_HASH                                     0xCC2840000009B000
	#define PS1_NETEMU_HASH                                  0xCC284000000BE000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037C000
	#define BDP_BDVD_HASH                                    0xCC28D00000437000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000044000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F470000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA4E74

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4E34
	#define ps2tonet_size_patch                              0xC4E28
	#define vmode_patch_offset                               0x4431DC
	#define psp_drm_patch1                                   0x242FC0
	#define psp_drm_patch2                                   0x243A60
	#define psp_drm_patch3                                   0x24369C
	#define psp_drm_patch4                                   0x243EA8
	#define psp_drm_patchA                                   0x2430DC
	#define psp_drm_patchB                                   0x24397C
	#define psp_drm_patchC                                   0x242B14
	#define psp_drm_patchD                                   0x2430C4
	#define psp_drm_patchE                                   0x2430C8
	#define psp_drm_patchF                                   0x243A94
	#define psp_extra_drm_patch                              0x245AF0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDD9B4
	#define app_home_offset                                  0x250A00

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68324

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23B90
	#define ps_region_error_offset                           0x68C0
	#define remote_play_offset                               0x5FC0
	#define ps2_nonbw_offset3                                0x17000

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EAE4
	#define patch2_nas                                       0x2EC48
	#define patch3_nas                                       0x1F75C

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F78C
	#define pspemu_path_offset                               0x4B688
	#define psptrans_path_offset                             0x4B718

	/* download_plugin */
	#define elf_patch1_download                              0x42E2C
	#define elf_patch2_download                              0x42E34
	#define elf_patch3_download                              0x4D7F8
	#define elf_patch4_download                              0x4E618
	#define elf_patch5_download                              0x4E638
	#define elf_patch6_download                              0x4E708

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x82650
	#define elf_patch2_autodownload                          0x82658

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070
#endif

#ifdef FIRMWARE_489C

	#define FIRMWARE_VERSION                                 0x489

	#ifdef PS3M_API
		#define PS3MAPI_FW_TYPE                              "CEX MAMBA"
		#define PS3MAPI_IDPS_1                               0x80000000003E2E30ULL
		#define PS3MAPI_IDPS_2                               0x8000000000474AF4ULL
		#define PS3MAPI_PSID                                 0x8000000000474B0CULL
	#endif
	#define FIRMWARE_CEX                                     FIRMWARE_VERSION

	/* lv2 */
	#define TOC                                              0x34FBB0

	#define create_kernel_object_symbol                      0x11FB0
	#define destroy_kernel_object_symbol                     0x11914
	#define destroy_shared_kernel_object_symbol              0x11288
	#define open_kernel_object_symbol                        0x12600
	#define open_shared_kernel_object_symbol                 0x12410
	#define close_kernel_object_handle_symbol                0x11A30

	#define alloc_symbol                                     0x64824
	#define dealloc_symbol                                   0x64C60
	#define copy_to_user_symbol                              0xF86C
	#define copy_from_user_symbol                            0xFA88
	#define copy_to_process_symbol                           0xF924
	#define copy_from_process_symbol                         0xF734
	#define process_read_memory_symbol                       0x267EC0
	#define process_write_memory_symbol                      0x267D34
	#define page_allocate_symbol                             0x60394
	#define page_free_symbol                                 0x5FDF8
	#define page_export_to_proc_symbol                       0x60530
	#define page_unexport_from_proc_symbol                   0x5FCEC
	#define kernel_ea_to_lpar_addr_symbol                    0x7014C
	#define process_ea_to_lpar_addr_ex_symbol                0x77760
	#define set_pte_symbol                                   0x5E390
	#define map_process_memory_symbol                        0x7726C
	#define panic_symbol                                     0x26D5C8

	#define memcpy_symbol                                    0x7E92C
	#define memset_symbol                                    0x4D66C
	#define memcmp_symbol                                    0x4C97C
	#define memchr_symbol                                    0x4C92C
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
	#define strrchr_symbol                                   0x4D950

	#define spin_lock_irqsave_ex_symbol                      0x26D798
	#define spin_unlock_irqrestore_ex_symbol                 0x26D76C

	#define create_process_common_symbol                     0x26B534
	#define create_process_base_symbol                       0x26ABF0
	#define load_process_symbol                              0x5004
	#define process_kill_symbol                              0x26B340

	#define ppu_thread_create_symbol                         0x13EC8
	#define ppu_thread_exit_symbol                           0x13F80
	#define ppu_thread_join_symbol                           0x13FD4
	#define ppu_thread_delay_symbol                          0x287A4
	#define create_kernel_thread_symbol                      0x24B20
	#define create_user_thread_symbol                        0x2525C
	#define create_user_thread2_symbol                       0x25080
	#define start_thread_symbol                              0x23D4C
	#define run_thread_symbol                                0x2357C
	#define self_threading_symbol                            0x25868
	#define register_thread_symbol                           0x26794C
	#define allocate_user_stack_symbol                       0x268134
	#define deallocate_user_stack_symbol                     0x26809C

	#define mutex_create_symbol                              0x1363C
	#define mutex_destroy_symbol                             0x135D4
	#define mutex_lock_symbol                                0x135CC
	#define mutex_lock_ex_symbol                             0x1DB5C
	#define mutex_trylock_symbol                             0x135C8
	#define mutex_unlock_symbol                              0x135C4

	#define cond_create_symbol                               0x137A8
	#define cond_destroy_symbol                              0x13758
	#define cond_wait_symbol                                 0x13750
	#define cond_wait_ex_symbol                              0x1F148
	#define cond_signal_symbol                               0x1372C
	#define cond_signal_all_symbol                           0x13708

	#define semaphore_initialize_symbol                      0x30C54
	#define semaphore_wait_ex_symbol                         0x3095C
	#define semaphore_trywait_symbol                         0x30544
	#define semaphore_post_ex_symbol                         0x30690

	#define event_port_create_symbol                         0x13078
	#define event_port_destroy_symbol                        0x134E0
	#define event_port_connect_symbol                        0x13558
	#define event_port_disconnect_symbol                     0x13484
	#define event_port_send_symbol                           0x13070
	#define event_port_send_ex_symbol                        0x2B204

	#define event_queue_create_symbol                        0x13380
	#define event_queue_destroy_symbol                       0x13308
	#define event_queue_receive_symbol                       0x1314C
	#define event_queue_tryreceive_symbol                    0x13218

	#define cellFsOpen_symbol                                0x297900
	#define cellFsClose_symbol                               0x297768
	#define cellFsRead_symbol                                0x2978A4
	#define cellFsWrite_symbol                               0x297810
	#define cellFsLseek_symbol                               0x296E98
	#define cellFsStat_symbol                                0x29711C
	#define cellFsUtime_symbol                               0x298C08
	#define cellFsUnlink_internal_symbol                     0x19C64C
	#define cellFsRename_internal_symbol                     0x197104

	#define cellFsUtilMount_symbol                           0x296C78
	#define cellFsUtilUmount_symbol                          0x298654
	#define cellFsUtilNewfs_symbol                           0x2986A0

	#define pathdup_from_user_symbol                         0x29C8E4
	#define open_path_symbol                                 0x297638
	#define open_fs_object_symbol                            0x18A970
	#define close_fs_object_symbol                           0x1898AC

	#define storage_get_device_info_symbol                   0x279B00
	#define storage_get_device_config_symbol                 0x278F90
	#define storage_open_symbol                              0x279510
	#define storage_close_symbol                             0x279300
	#define storage_read_symbol                              0x278870
	#define storage_write_symbol                             0x278740
	#define storage_send_device_command_symbol               0x2783FC
	#define storage_map_io_memory_symbol                     0x2799BC
	#define storage_unmap_io_memory_symbol                   0x279888
	#define new_medium_listener_object_symbol                0x974C4
	#define delete_medium_listener_object_symbol             0x98CFC
	#define set_medium_event_callbacks_symbol                0x99060

	#define cellUsbdRegisterLdd_symbol                       0x26027C
	#define cellUsbdUnregisterLdd_symbol                     0x26022C
	#define cellUsbdScanStaticDescriptor_symbol              0x26147C
	#define cellUsbdOpenPipe_symbol                          0x26152C
	#define cellUsbdClosePipe_symbol                         0x2614DC
	#define cellUsbdControlTransfer_symbol                   0x2613E0
	#define cellUsbdBulkTransfer_symbol                      0x261360

	#define decrypt_func_symbol                              0x34970
	#define lv1_call_99_wrapper_symbol                       0x4EEA8
	#define modules_verification_symbol                      0x58AB8
	#define authenticate_program_segment_symbol              0x5A910

	#define prx_load_module_symbol                           0x88C04
	#define prx_start_module_symbol                          0x878D0
	#define prx_stop_module_symbol                           0x88CA8
	#define prx_unload_module_symbol                         0x87604
	#define prx_get_module_info_symbol                       0x8708C
	#define prx_get_module_id_by_address_symbol              0x86F9C
	#define prx_get_module_id_by_name_symbol                 0x86FEC
	#define prx_get_module_list_symbol                       0x8710C
	#define load_module_by_fd_symbol                         0x88234
	#define parse_sprx_symbol                                0x85FB8
	#define open_prx_object_symbol                           0x7F4F8
	#define close_prx_object_symbol                          0x7FE08
	#define lock_prx_mutex_symbol                            0x86F44
	#define unlock_prx_mutex_symbol                          0x86F50

	#define extend_kstack_symbol                             0x700A4

	#define get_pseudo_random_number_symbol                  0x228180
	#define md5_reset_symbol                                 0x161E20
	#define md5_update_symbol                                0x1628C0
	#define md5_final_symbol                                 0x162A40
	#define ss_get_open_psid_symbol                          0x22A668
	#define update_mgr_read_eeprom_symbol                    0x223A78
	#define update_mgr_write_eeprom_symbol                   0x2239C0
	#define update_mgr_if_get_token_symbol                   0x2253DC

	#define ss_params_get_update_status_symbol               0x50AB4

	#define sm_get_temperature_symbol                        0x2635A8
	#define sm_get_fan_policy_symbol                         0x26293C
	#define sm_set_fan_policy_symbol                         0x264734
	#define sm_get_temperature_patch                         0xC6A8
	#define sm_get_fan_policy_patch                          0x9E38
	#define sm_set_fan_policy_patch                          0xA334

	#define SHA1_init_symbol                                 0x2CE688
	#define SHA1_update_symbol                               0x2CE6E8
	#define SHA1_final_symbol                                0x2CE89C
	#define aescbccfb_dec_symbol                             0x2CCB7C
	#define aescbccfb_enc_symbol                             0x2CC92C
	#define get_path_by_fd_symbol                            0x29C180

	#define ECDSA_1                                          0x59DC4
	#define ECDSA_2                                          0x2D2B34
	#define ECDSA_FLAG                                       0x474A80
	#define sysmem_obj                                       0x474C38
	#define qa_eeprom_offset                                 0x48C0A

	#define syscall_table_symbol                             0x363BE0
	#define syscall_call_offset                              0x275C04

	#define read_bdvd0_symbol                                0x1A461C
	#define read_bdvd1_symbol                                0x1A6248
	#define read_bdvd2_symbol                                0x1B3400

	#define storage_internal_get_device_object_symbol        0x277EB4

	#define hid_mgr_read_usb_symbol                          0x102444
	#define hid_mgr_read_bt_symbol                           0xFC31C

	#define bt_set_controller_info_internal_symbol           0xF0388

	#define device_event_port_send_call                      0x28206C
	#define device_event_port_send_call_restore              0x1CE92748

	#define ss_pid_call_1                                    0x21329C

	#define process_map_caller_call                          0x4D24

	#define read_module_header_call                          0x7F3EC
	#define read_module_body_call                            0x671C
	#define load_module_by_fd_call1                          0x88AA0

	#define shutdown_copy_params_call                        0xAACC
	#define shutdown_copy_params_call_restore                0x75644F48

	#define fsloop_open_call                                 0x297A98
	#define fsloop_close_call                                0x297AE8
	#define fsloop_read_call                                 0x297B28

	#define shutdown_patch_offset                            0xAAB8
	#define module_sdk_version_patch_offset                  0x26717C
	#define module_add_parameter_to_parse_sprxpatch_offset   0x88310

	#define user_thread_prio_patch                           0x203FC
	#define user_thread_prio_patch2                          0x2040C

	#define lic_patch                                        0x56230
	#define lic_patch_restore                                0x48240EED
	#define ode_patch                                        0x2275F4
	#define fix_80010009                                     0x5A6E4
	#define fix_8001003D                                     0x5658C
	#define fix_8001003E                                     0x56650
	#define PATCH_JUMP                                       0x56604

	#define io_rtoc_entry_1                                  0x25B8
	#define io_sub_rtoc_entry_1                             -0x7EA0
	#define decrypt_rtoc_entry_2                            -0x66A0

	#define storage_rtoc_entry_1                             0x1DD8

	#define device_event_rtoc_entry_1                        0x2048

	#define time_rtoc_entry_1                               -0x7640
	#define time_rtoc_entry_2                               -0x7648

	#define thread_rtoc_entry_1                             -0x76C0

	#define process_rtoc_entry_1                            -0x7800

	#define bt_rtoc_entry_1                                 -0x3680

	#define permissions_func_symbol                          0x3560
	#define permissions_exception1                           0x25100
	#define permissions_exception2                           0xC3298
	#define permissions_exception3                           0x204D0

	#define patch_data1_offset                               0x3E2E40
	#define patch_func2                                      0x59D84
	#define patch_func2_offset                               0x2C
	#define patch_func2_restore                              0x484A66C1
	#define patch_func8_offset1                              0x564B4
	#define patch_func8_offset2                              0x56614
	#define patch_func8_offset2_restore                      0x48216FB5
	#define patch_func9_offset                               0x5A6F8
	#define mem_base2                                        0x3D90

	#define thread_info_symbol                               0x37DE30

	#define mmapper_flags_temp_patch                         0x70F78

	#define rsx_syscall_check                                0x501138
	#define unk_func2_unregister_service                     0x99190
	#define unk_func3_unregister_service                     0x9DC24

	/* lv1 */
	#define vsh_pos_in_ram                                   0x910000

	/* hash */
	#define VSH_HASH                                         0xB6B6D000002E3000
	#define EXPLORE_PLUGIN_HASH                              0xC50D0000000EC000
	#define EXPLORE_CATEGORY_GAME_HASH                       0xDE52D00000056000
	#define PS1_EMU_HASH                                     0xCC2840000009B000
	#define PS1_NETEMU_HASH                                  0xCC284000000BE000
	#define GAME_EXT_PLUGIN_HASH                             0xCC2680000001E000
	#define LIBFS_EXTERNAL_HASH                              0x05FD000000006000
	#define NAS_PLUGIN_HASH                                  0xC50D000000027000
	#define BDP_DISC_CHECK_PLUGIN_HASH                       0x9940000000003000
	#define BDP_BDMV_HASH                                    0xCC2870000037C000
	#define BDP_BDVD_HASH                                    0xCC28D00000437000
	#define DOWNLOAD_PLUGIN_HASH                             0xCC26800000021000
	#define AUTODOWNLOAD_PLUGIN_HASH                         0x6A1AF00000044000
	#define PREMO_PLUGIN_HASH                                0x1000000000012000
	#define PREMO_GAME_PLUGIN_HASH                           0x5BC3000000012000
	#define BASIC_PLUGINS_HASH                               0x55F470000001F000
	#define PSP_EMULATOR_HASH                                0xCC29B00000023000
	#define PEMUCORELIB_HASH                                 0x40425000000C0000
	#define EMULATOR_API_HASH                                0x8409F0000001B000
	#define EMULATOR_DRM_HASH                                0xBBB8800000005000
	#define EMULATOR_DRM_DATA_HASH                           0x2F3AB0000001B000
	#define LIBSYSUTIL_SAVEDATA_PSP_HASH                     0x0DFDC00000003000
	#define LIBAUDIO_HASH                                    0x2200600000002000

	/* bdp_disccheck_plugin */
	#define dvd_video_region_check_offset                    0x152C

	/* ps1_emu */
	#define ps1_emu_get_region_offset                        0x3E74

	/* ps1_netemu */
	#define ps1_netemu_get_region_offset                     0xA4E74

	/* vsh */
	#define vsh_text_size                                    0x6B0000
	#define ps2tonet_patch                                   0xC4E34
	#define ps2tonet_size_patch                              0xC4E28
	#define vmode_patch_offset                               0x4431DC
	#define psp_drm_patch1                                   0x242FC0
	#define psp_drm_patch2                                   0x243A60
	#define psp_drm_patch3                                   0x24369C
	#define psp_drm_patch4                                   0x243EA8
	#define psp_drm_patchA                                   0x2430DC
	#define psp_drm_patchB                                   0x24397C
	#define psp_drm_patchC                                   0x242B14
	#define psp_drm_patchD                                   0x2430C4
	#define psp_drm_patchE                                   0x2430C8
	#define psp_drm_patchF                                   0x243A94
	#define psp_extra_drm_patch                              0x245AF0

	/* explore_plugin */
	#define ps2_nonbw_offset                                 0xDD9BC
	#define app_home_offset                                  0x250810

	/* explore_category_game */
	#define ps2_nonbw_offset2                                0x68324

	/* game_ext_plugin */
	#define sfo_check_offset                                 0x23B90
	#define ps_region_error_offset                           0x68C0
	#define remote_play_offset                               0x5FC0
	#define ps2_nonbw_offset3                                0x17000

	/* premo_plugin */
	#define pcremote_play_offset1                            0xB6FC

	/* premo_game_plugin */
	#define pcremote_play_offset2                            0xC8FC

	/* nas_plugin */
	#define patch1_nas                                       0x2EAE4
	#define patch2_nas                                       0x2EC48
	#define patch3_nas                                       0x1F75C

	/* basic_plugins */
	#define ps1emu_type_check_offset                         0x1F78C
	#define pspemu_path_offset                               0x4B688
	#define psptrans_path_offset                             0x4B718

	/* download_plugin */
	#define elf_patch1_download                              0x42E2C
	#define elf_patch2_download                              0x42E34
	#define elf_patch3_download                              0x4D7F8
	#define elf_patch4_download                              0x4E618
	#define elf_patch5_download                              0x4E638
	#define elf_patch6_download                              0x4E708

	/* autodownload_plugin */
	#define elf_patch1_autodownload                          0x82650
	#define elf_patch2_autodownload                          0x82658

	/* bdp_BDVD */
	#define bdp_cinavia_patch                                0x15ECD0
	#define bdp_cinavia1_patch                               0x15ECFC

	/* psp_emulator */
	#define psp_set_psp_mode_offset                          0x1C18

	/* emulator_api */
	#define psp_read                                         0x102D8
	#define psp_read_header                                  0x1125C
	#define psp_drm_patch5                                   0x11080
	#define psp_drm_patch6                                   0x110B0
	#define psp_drm_patch7                                   0x110C8
	#define psp_drm_patch8                                   0x110CC
	#define psp_drm_patch9                                   0x1120C
	#define psp_drm_patch11                                  0x11210
	#define psp_drm_patch12                                  0x11220
	#define psp_product_id_patch1                            0x11320
	#define psp_product_id_patch3                            0x115F8

	/* pemucorelib */
	#define psp_eboot_dec_patch                              0x5E6BC
	#define psp_prx_patch                                    0x577D8
	#define psp_savedata_bind_patch1                         0x7A4BC
	#define psp_savedata_bind_patch2                         0x7A514
	#define psp_savedata_bind_patch3                         0x7A030
	#define psp_extra_savedata_patch                         0x87540
	#define psp_prometheus_patch                             0x12EA28
	#define prx_patch_call_lr                                0x5892C

	/* emulator_drm */
	#define psp_drm_tag_overwrite                            0x4C68
	#define psp_drm_key_overwrite                            (0x27600 - 0xBE80)

	/* libsysutil_savedata_psp */
	#define psp_savedata_patch1                              0x46CC
	#define psp_savedata_patch2                              0x46A4
	#define psp_savedata_patch3                              0x4504
	#define psp_savedata_patch4                              0x453C
	#define psp_savedata_patch5                              0x4550
	#define psp_savedata_patch6                              0x46B8

	/* libfs */
	#define aio_copy_root_offset                             0xD658

	/* libaudio */
	#define bt_usb_audio_offset                              0x1070
#endif


#endif /* __FIRMWARE_SYMBOLS_H_S__ */
