
#include "ps2vers.h"

#define SUCCESS 1
#define FAILED  0

u8 get_hwemu(u32 crc, u8 **stage1, u32 *stage1_size, u8 **stage2, u32 *stage2_size)
{

	if(crc == CRC32HWEMU_421C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_421C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_421C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_421C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_421C_bin;
	} else 
	if(crc == CRC32HWEMU_421D) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_421D_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_421D_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_421D_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_421D_bin;
	} else 
	if(crc == CRC32HWEMU_425C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_425C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_425C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_425C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_425C_bin;
	} else 
	if(crc == CRC32HWEMU_425D) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_425D_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_425D_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_425D_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_425D_bin;
	} else 
	if(crc == CRC32HWEMU_430C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_430C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_430C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_430C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_430C_bin;
	} else 
	if(crc == CRC32HWEMU_430D) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_430D_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_430D_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_430D_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_430D_bin;
	} else 
	if(crc == CRC32HWEMU_431C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_431C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_431C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_431C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_431C_bin;
	} else 
	if(crc == CRC32HWEMU_431D) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_431D_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_431D_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_431D_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_431D_bin;
	} else 
	if(crc == CRC32HWEMU_440C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_440C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_440C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_440C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_440C_bin;
	} else 
	if(crc == CRC32HWEMU_440D) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_440D_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_440D_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_440D_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_440D_bin;
	} else 
	if(crc == CRC32HWEMU_441C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_441C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_441C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_441C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_441C_bin;
	} else 
	if(crc == CRC32HWEMU_441D) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_441D_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_441D_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_441D_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_441D_bin;
	} else 
	if(crc == CRC32HWEMU_446C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_446C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_446C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_446C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_446C_bin;
	} else 
	if(crc == CRC32HWEMU_446D) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_446D_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_446D_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_446D_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_446D_bin;
	} else 
	if(crc == CRC32HWEMU_450C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_450C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_450C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_450C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_450C_bin;
	} else 
	if(crc == CRC32HWEMU_450D) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_450D_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_450D_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_450D_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_450D_bin;
	} else 
	if(crc == CRC32HWEMU_453C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_453C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_453C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_453C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_453C_bin;
	} else 
	if(crc == CRC32HWEMU_453D) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_453D_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_453D_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_453D_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_453D_bin;
	} else 
	if(crc == CRC32HWEMU_455C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_455C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_455C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_455C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_455C_bin;
	} else 
	if(crc == CRC32HWEMU_455D) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_455D_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_455D_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_455D_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_455D_bin;
	} else 
	if(crc == CRC32HWEMU_460C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_460C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_460C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_460C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_460C_bin;
	} else 
	if(crc == CRC32HWEMU_460D) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_460D_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_460D_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_460D_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_460D_bin;
	} else 
	if(crc == CRC32HWEMU_465C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_465C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_465C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_465C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_465C_bin;
	} else 
	if(crc == CRC32HWEMU_465D) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_465D_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_465D_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_465D_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_465D_bin;
	} else 
	if(crc == CRC32HWEMU_466C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_466C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_466C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_466C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_466C_bin;
	} else 
	if(crc == CRC32HWEMU_470C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_470C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_470C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_470C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_470C_bin;
	} else 
	if(crc == CRC32HWEMU_470D) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_470D_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_470D_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_470D_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_470D_bin;
	} else 
	if(crc == CRC32HWEMU_475C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_475C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_475C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_475C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_475C_bin;
	} else 
	if(crc == CRC32HWEMU_475D) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_475D_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_475D_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_475D_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_475D_bin;
	} else 
	if(crc == CRC32HWEMU_476C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_476C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_476C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_476C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_476C_bin;
	} else 
	if(crc == CRC32HWEMU_476D) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_476D_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_476D_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_476D_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_476D_bin;
	} else 
	if(crc == CRC32HWEMU_478C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_478C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_478C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_478C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_478C_bin;
	} else 
	if(crc == CRC32HWEMU_478D) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_478D_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_478D_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_478D_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_478D_bin;
	} else 
	if(crc == CRC32HWEMU_480C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_480C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_480C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_480C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_480C_bin;
	} else 
	if(crc == CRC32HWEMU_480D) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_480D_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_480D_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_480D_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_480D_bin;
	} else 
	if(crc == CRC32HWEMU_481C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_481C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_481C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_481C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_481C_bin;
	} else 
	if(crc == CRC32HWEMU_481D) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_481D_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_481D_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_481D_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_481D_bin;
	} else 
	if(crc == CRC32HWEMU_482C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_482C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_482C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_482C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_482C_bin;
	} else 
	if(crc == CRC32HWEMU_483C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_483C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_483C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_483C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_483C_bin;
	} else 
	if(crc == CRC32HWEMU_484C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_484C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_484C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_484C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_484C_bin;
	} else 
	if(crc == CRC32HWEMU_484D) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_484D_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_484D_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_484D_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_484D_bin;
	} else 
	if(crc == CRC32HWEMU_485C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_485C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_485C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_485C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_485C_bin;
	} else 
	if(crc == CRC32HWEMU_486C) {
		*stage1_size = (uint32_t) ps2hwemu_stage1_486C_bin_size;
		*stage1 = (uint8_t *) ps2hwemu_stage1_486C_bin;
		*stage2_size = (uint32_t) ps2hwemu_stage2_486C_bin_size;
		*stage2 = (uint8_t *) ps2hwemu_stage2_486C_bin;
	} else  return FAILED;

	return SUCCESS;
}

u8 get_gxemu(u32 crc, u8 **stage1, u32 *stage1_size, u8 **stage2, u32 *stage2_size)
{

	if(crc == CRC32GXEMU_421C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_421C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_421C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_421C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_421C_bin;
	} else 
	if(crc == CRC32GXEMU_421D) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_421D_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_421D_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_421D_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_421D_bin;
	} else 
	if(crc == CRC32GXEMU_425C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_425C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_425C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_425C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_425C_bin;
	} else 
	if(crc == CRC32GXEMU_425D) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_425D_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_425D_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_425D_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_425D_bin;
	} else 
	if(crc == CRC32GXEMU_430C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_430C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_430C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_430C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_430C_bin;
	} else 
	if(crc == CRC32GXEMU_430D) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_430D_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_430D_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_430D_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_430D_bin;
	} else 
	if(crc == CRC32GXEMU_431C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_431C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_431C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_431C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_431C_bin;
	} else 
	if(crc == CRC32GXEMU_431D) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_431D_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_431D_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_431D_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_431D_bin;
	} else 
	if(crc == CRC32GXEMU_440C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_440C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_440C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_440C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_440C_bin;
	} else 
	if(crc == CRC32GXEMU_440D) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_440D_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_440D_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_440D_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_440D_bin;
	} else 
	if(crc == CRC32GXEMU_441C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_441C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_441C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_441C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_441C_bin;
	} else 
	if(crc == CRC32GXEMU_441D) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_441D_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_441D_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_441D_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_441D_bin;
	} else 
	if(crc == CRC32GXEMU_446C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_446C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_446C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_446C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_446C_bin;
	} else 
	if(crc == CRC32GXEMU_446D) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_446D_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_446D_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_446D_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_446D_bin;
	} else 
	if(crc == CRC32GXEMU_450C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_450C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_450C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_450C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_450C_bin;
	} else 
	if(crc == CRC32GXEMU_450D) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_450D_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_450D_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_450D_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_450D_bin;
	} else 
	if(crc == CRC32GXEMU_453C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_453C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_453C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_453C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_453C_bin;
	} else 
	if(crc == CRC32GXEMU_453D) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_453D_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_453D_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_453D_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_453D_bin;
	} else 
	if(crc == CRC32GXEMU_455C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_455C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_455C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_455C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_455C_bin;
	} else 
	if(crc == CRC32GXEMU_455D) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_455D_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_455D_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_455D_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_455D_bin;
	} else 
	if(crc == CRC32GXEMU_460C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_460C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_460C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_460C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_460C_bin;
	} else 
	if(crc == CRC32GXEMU_460D) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_460D_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_460D_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_460D_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_460D_bin;
	} else 
	if(crc == CRC32GXEMU_465C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_465C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_465C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_465C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_465C_bin;
	} else 
	if(crc == CRC32GXEMU_465D) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_465D_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_465D_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_465D_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_465D_bin;
	} else 
	if(crc == CRC32GXEMU_466C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_466C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_466C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_466C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_466C_bin;
	} else 
	if(crc == CRC32GXEMU_470C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_470C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_470C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_470C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_470C_bin;
	} else 
	if(crc == CRC32GXEMU_470D) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_470D_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_470D_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_470D_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_470D_bin;
	} else 
	if(crc == CRC32GXEMU_475C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_475C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_475C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_475C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_475C_bin;
	} else 
	if(crc == CRC32GXEMU_475D) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_475D_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_475D_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_475D_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_475D_bin;
	} else 
	if(crc == CRC32GXEMU_476C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_476C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_476C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_476C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_476C_bin;
	} else 
	if(crc == CRC32GXEMU_476D) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_476D_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_476D_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_476D_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_476D_bin;
	} else 
	if(crc == CRC32GXEMU_478C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_478C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_478C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_478C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_478C_bin;
	} else 
	if(crc == CRC32GXEMU_478D) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_478D_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_478D_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_478D_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_478D_bin;
	} else 
	if(crc == CRC32GXEMU_480C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_480C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_480C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_480C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_480C_bin;
	} else 
	if(crc == CRC32GXEMU_480D) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_480D_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_480D_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_480D_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_480D_bin;
	} else 
	if(crc == CRC32GXEMU_481C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_481C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_481C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_481C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_481C_bin;
	} else 
	if(crc == CRC32GXEMU_481D) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_481D_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_481D_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_481D_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_481D_bin;
	} else 
	if(crc == CRC32GXEMU_482C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_482C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_482C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_482C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_482C_bin;
	} else 
	if(crc == CRC32GXEMU_483C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_483C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_483C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_483C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_483C_bin;
	} else 
	if(crc == CRC32GXEMU_484C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_484C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_484C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_484C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_484C_bin;
	} else 
	if(crc == CRC32GXEMU_484D) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_484D_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_484D_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_484D_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_484D_bin;
	} else 
	if(crc == CRC32GXEMU_485C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_485C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_485C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_485C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_485C_bin;
	} else 
	if(crc == CRC32GXEMU_486C) {
		*stage1_size = (uint32_t) ps2gxemu_stage1_486C_bin_size;
		*stage1 = (uint8_t *) ps2gxemu_stage1_486C_bin;
		*stage2_size = (uint32_t) ps2gxemu_stage2_486C_bin_size;
		*stage2 = (uint8_t *) ps2gxemu_stage2_486C_bin;
	} else  return FAILED;
	
	return SUCCESS;
	
}

u8 get_netemu(u32 crc, u8 **stage2, u32 *stage2_size)
{

	if(crc == CRC32NETEMU_421C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_421C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_421C_bin;
	} else 
	if(crc == CRC32NETEMU_421D) {
		*stage2_size = (uint32_t) ps2netemu_stage2_421D_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_421D_bin;
	} else 
	if(crc == CRC32NETEMU_425C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_425C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_425C_bin;
	} else 
	if(crc == CRC32NETEMU_425D) {
		*stage2_size = (uint32_t) ps2netemu_stage2_425D_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_425D_bin;
	} else 
	if(crc == CRC32NETEMU_430C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_430C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_430C_bin;
	} else 
	if(crc == CRC32NETEMU_430D) {
		*stage2_size = (uint32_t) ps2netemu_stage2_430D_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_430D_bin;
	} else 
	if(crc == CRC32NETEMU_431C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_431C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_431C_bin;
	} else 
	if(crc == CRC32NETEMU_431D) {
		*stage2_size = (uint32_t) ps2netemu_stage2_431D_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_431D_bin;
	} else 
	if(crc == CRC32NETEMU_440C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_440C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_440C_bin;
	} else 
	if(crc == CRC32NETEMU_440D) {
		*stage2_size = (uint32_t) ps2netemu_stage2_440D_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_440D_bin;
	} else 
	if(crc == CRC32NETEMU_441C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_441C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_441C_bin;
	} else 
	if(crc == CRC32NETEMU_441D) {
		*stage2_size = (uint32_t) ps2netemu_stage2_441D_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_441D_bin;
	} else 
	if(crc == CRC32NETEMU_446C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_446C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_446C_bin;
	} else 
	if(crc == CRC32NETEMU_446D) {
		*stage2_size = (uint32_t) ps2netemu_stage2_446D_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_446D_bin;
	} else 
	if(crc == CRC32NETEMU_450C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_450C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_450C_bin;
	} else 
	if(crc == CRC32NETEMU_450D) {
		*stage2_size = (uint32_t) ps2netemu_stage2_450D_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_450D_bin;
	} else 
	if(crc == CRC32NETEMU_453C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_453C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_453C_bin;
	} else 
	if(crc == CRC32NETEMU_453D) {
		*stage2_size = (uint32_t) ps2netemu_stage2_453D_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_453D_bin;
	} else 
	if(crc == CRC32NETEMU_455C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_455C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_455C_bin;
	} else 
	if(crc == CRC32NETEMU_455D) {
		*stage2_size = (uint32_t) ps2netemu_stage2_455D_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_455D_bin;
	} else 
	if(crc == CRC32NETEMU_460C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_460C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_460C_bin;
	} else 
	if(crc == CRC32NETEMU_460D) {
		*stage2_size = (uint32_t) ps2netemu_stage2_460D_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_460D_bin;
	} else 
	if(crc == CRC32NETEMU_465C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_465C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_465C_bin;
	} else 
	if(crc == CRC32NETEMU_465D) {
		*stage2_size = (uint32_t) ps2netemu_stage2_465D_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_465D_bin;
	} else 
	if(crc == CRC32NETEMU_466C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_466C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_466C_bin;
	} else 
	if(crc == CRC32NETEMU_470C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_470C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_470C_bin;
	} else 
	if(crc == CRC32NETEMU_470D) {
		*stage2_size = (uint32_t) ps2netemu_stage2_470D_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_470D_bin;
	} else 
	if(crc == CRC32NETEMU_475C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_475C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_475C_bin;
	} else 
	if(crc == CRC32NETEMU_475D) {
		*stage2_size = (uint32_t) ps2netemu_stage2_475D_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_475D_bin;
	} else 
	if(crc == CRC32NETEMU_476C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_476C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_476C_bin;
	} else 
	if(crc == CRC32NETEMU_476D) {
		*stage2_size = (uint32_t) ps2netemu_stage2_476D_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_476D_bin;
	} else 
	if(crc == CRC32NETEMU_478C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_478C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_478C_bin;
	} else 
	if(crc == CRC32NETEMU_478D) {
		*stage2_size = (uint32_t) ps2netemu_stage2_478D_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_478D_bin;
	} else 
	if(crc == CRC32NETEMU_480C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_480C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_480C_bin;
	} else 
	if(crc == CRC32NETEMU_480D) {
		*stage2_size = (uint32_t) ps2netemu_stage2_480D_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_480D_bin;
	} else 
	if(crc == CRC32NETEMU_481C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_481C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_481C_bin;
	} else 
	if(crc == CRC32NETEMU_481D) {
		*stage2_size = (uint32_t) ps2netemu_stage2_481D_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_481D_bin;
	} else 
	if(crc == CRC32NETEMU_482C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_482C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_482C_bin;
	} else 
	if(crc == CRC32NETEMU_483C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_483C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_483C_bin;
	} else 
	if(crc == CRC32NETEMU_484C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_484C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_484C_bin;
	} else 
	if(crc == CRC32NETEMU_484D) {
		*stage2_size = (uint32_t) ps2netemu_stage2_484D_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_484D_bin;
	} else 
	if(crc == CRC32NETEMU_485C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_485C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_485C_bin;
	} else 
	if(crc == CRC32NETEMU_486C) {
		*stage2_size = (uint32_t) ps2netemu_stage2_486C_bin_size;
		*stage2 = (uint8_t *) ps2netemu_stage2_486C_bin;
	} else  return FAILED;
	
	return SUCCESS;
}
