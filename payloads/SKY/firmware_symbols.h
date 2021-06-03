#define open_mapping_table_ext      0x7fff00
#define perm_patch_func             0x3560
#define perm_var_offset             -0x7FF8
#define BASE                        0x3d90
#define BASE2                      (0x3d90+0x400)
#define strcpy                      memset + 0x1AC
#define strncmp                     memset + 0x200
#define free                        alloc + 0x43C

#ifdef CFW_421C
#define alloc                   0x63ED8
#define memory_patch_func       0x2C2580
#define memcpy                  0x7DFD0
#define memset                  0x4E508
#endif

#ifdef CFW_421D
#define alloc                   0x677F0
#define memory_patch_func       0x2D9740
#define memcpy                  0x81FF4
#define memset                  0x51DF8
#endif

#ifdef CFW_430C
#define alloc                   0x64028
#define memory_patch_func       0x2C3CFC
#define memcpy                  0x7E0FC
#define memset                  0x4E544
#endif

#ifdef CFW_430D
#define alloc                   0x67940
#define memory_patch_func       0x2DAE74
#define memcpy                  0x82120
#define memset                  0x51E34
#endif

#ifdef CFW_431C
#define alloc                   0x6402C
#define memory_patch_func       0x2C3D08
#define memcpy                  0x7E100
#define memset                  0x4E548
#endif

#ifdef CFW_440C
#define alloc                   0x62F74
#define memory_patch_func       0x2C42AC
#define memcpy                  0x7D048
#define memset                  0x4D490
#endif

#ifdef CFW_441C
#define alloc                   0x62F78
#define memory_patch_func       0x2C42B8
#define memcpy                  0x7D04C
#define memset                  0x4D494
#endif

#ifdef CFW_441D
#define alloc                   0x66890
#define memory_patch_func       0x2DB764
#define memcpy                  0x81070
#define memset                  0x50D84
#endif

#ifdef CFW_446C
#define alloc                   0x62F78
#define memory_patch_func       0x2C47D8
#define memcpy                  0x7D04C
#define memset                  0x4D494
#endif

#ifdef CFW_446D
#define alloc                   0x66890
#define memory_patch_func       0x2DBC84
#define memcpy                  0x81070
#define memset                  0x50D84
#endif

#ifdef CFW_450C
#define alloc                   0x62F74
#define memory_patch_func       0x29DD48
#define memcpy                  0x7D048
#define memset                  0x4D490
#endif

#ifdef CFW_450D
#define alloc                   0x66944
#define memory_patch_func       0x2B8210
#define memcpy                  0x81124
#define memset                  0x50E38
#endif

#ifdef CFW_453C
#define alloc                   0x62F78
#define memory_patch_func       0x29DF20
#define memcpy                  0x7D04C
#define memset                  0x4D494
#endif

#ifdef CFW_453D
#define alloc                   0x66948
#define memory_patch_func       0x2B83E8
#define memcpy                  0x81128
#define memset                  0x50E3C
#endif

#ifdef CFW_455C
#define alloc                   0x643B4
#define memory_patch_func       0x29F770
#define memcpy                  0x7E488
#define memset                  0x4D6D8
#endif

#ifdef CFW_455D
#define alloc                   0x67D84
#define memory_patch_func       0x2B9C3C
#define memcpy                  0x82564
#define memset                  0x51080
#endif

#ifdef CFW_460C
#define alloc                   0x64798
#define memory_patch_func       0x2A02E4
#define memcpy                  0x7E8A0
#define memset                  0x4D668
#endif

#ifdef CFW_465C
#define alloc                   0x6479C
#define memory_patch_func       0x2A02F0
#define memcpy                  0x7E8A4
#define memset                  0x4D66C
#endif

#ifdef CFW_465D
#define alloc                   0x6816C
#define memory_patch_func       0x2BB038
#define memcpy                  0x82980
#define memset                  0x51014
#endif

#ifdef CFW_470C
#define alloc                   0x64820
#define memory_patch_func       0x2975E8
#define memcpy                  0x7E928
#define memset                  0x4D668
#endif

#ifdef CFW_470D
#define alloc                   0x681F0
#define memory_patch_func       0x2B24A8
#define memcpy                  0x82A04
#define memset                  0x51010
#endif

#ifdef CFW_475C
#define alloc                   0x64824
#define memory_patch_func       0x297660
#define memcpy                  0x7E92C
#define memset                  0x4D66C
#endif

#ifdef CFW_475D
#define alloc                   0x681F4
#define memory_patch_func       0x2B2520
#define memcpy                  0x82A08
#define memset                  0x51014
#endif

#ifdef CFW_476C
#define alloc                   0x64824
#define memory_patch_func       0x297660
#define memcpy                  0x7E92C
#define memset                  0x4D66C
#endif

#ifdef CFW_476D
#define alloc                   0x681F4
#define memory_patch_func       0x2B2520
#define memcpy                  0x82A08
#define memset                  0x51014
#endif

#ifdef CFW_478C
#define alloc                   0x64824
#define memory_patch_func       0x297660
#define memcpy                  0x7E92C
#define memset                  0x4D66C
#endif

#ifdef CFW_478D
#define alloc                   0x681F4
#define memory_patch_func       0x2B2520
#define memcpy                  0x82A08
#define memset                  0x51014
#endif

#ifdef CFW_480C
#define alloc                   0x64820
#define memory_patch_func       0x297654
#define memcpy                  0x7E928
#define memset                  0x4D668
#endif

#ifdef CFW_480D
#define alloc                   0x681F0
#define memory_patch_func       0x2B25EC
#define memcpy                  0x82A04
#define memset                  0x51010
#endif

#ifdef CFW_481C
#define alloc                   0x64824
#define memory_patch_func       0x297660
#define memcpy                  0x7E92C
#define memset                  0x4D66C
#endif

#ifdef CFW_481D
#define alloc                   0x681F4
#define memory_patch_func       0x2B25F8
#define memcpy                  0x82A08
#define memset                  0x51014
#endif

#ifdef CFW_482C
#define alloc                   0x64824
#define memory_patch_func       0x297660
#define memcpy                  0x7E92C
#define memset                  0x4D66C
#endif

#ifdef CFW_482D
#define alloc                   0x681F4
#define memory_patch_func       0x2B25F8
#define memcpy                  0x82A08
#define memset                  0x51014
#endif

#ifdef CFW_483C
#define alloc                   0x64824
#define memory_patch_func       0x297660
#define memcpy                  0x7E92C
#define memset                  0x4D66C
#endif

#ifdef CFW_484C
#define alloc                   0x64824
#define memory_patch_func       0x297660
#define memcpy                  0x7E92C
#define memset                  0x4D66C
#endif

#ifdef CFW_484D
#define alloc                   0x681F4
#define memory_patch_func       0x2B25F8
#define memcpy                  0x82A08
#define memset                  0x51014
#endif

#ifdef CFW_485C
#define alloc                   0x64824
#define memory_patch_func       0x297660
#define memcpy                  0x7E92C
#define memset                  0x4D66C
#endif

#ifdef CFW_486C
#define alloc                   0x64824
#define memory_patch_func       0x297660
#define memcpy                  0x7E92C
#define memset                  0x4D66C
#endif

#ifdef CFW_487C
#define alloc                   0x64824
#define memory_patch_func       0x297660
#define memcpy                  0x7E92C
#define memset                  0x4D66C
#endif

#ifdef CFW_488C
#define alloc                   0x64824
#define memory_patch_func       0x297660
#define memcpy                  0x7E92C
#define memset                  0x4D66C
#endif
