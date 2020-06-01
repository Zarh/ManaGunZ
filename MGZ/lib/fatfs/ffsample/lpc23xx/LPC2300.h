/*-----------------------------------------------------------*/
/* LPC2300 Register Definitions                              */
/* This file is a non-copyrighted public domain software.    */
/*-----------------------------------------------------------*/

#ifndef __LPC2300
#define __LPC2300
#include <stdint.h>

#define VICIRQStatus		(*(volatile uint32_t*)(0xFFFFF000))
#define VICFIQStatus		(*(volatile uint32_t*)(0xFFFFF004))
#define VICRawIntr			(*(volatile uint32_t*)(0xFFFFF008))
#define VICIntSelect		(*(volatile uint32_t*)(0xFFFFF00C))
#define VICIntEnable		(*(volatile uint32_t*)(0xFFFFF010))
#define VICIntEnClr			(*(volatile uint32_t*)(0xFFFFF014))
#define VICSoftInt			(*(volatile uint32_t*)(0xFFFFF018))
#define VICSoftIntClr		(*(volatile uint32_t*)(0xFFFFF01C))
#define VICProtection		(*(volatile uint32_t*)(0xFFFFF020))
#define VICSWPrioMask		(*(volatile uint32_t*)(0xFFFFF024))
#define VICVectAddr0		(*(volatile uint32_t*)(0xFFFFF100))
#define VICVectAddr1		(*(volatile uint32_t*)(0xFFFFF104))
#define VICVectAddr2		(*(volatile uint32_t*)(0xFFFFF108))
#define VICVectAddr3		(*(volatile uint32_t*)(0xFFFFF10C))
#define VICVectAddr4		(*(volatile uint32_t*)(0xFFFFF110))
#define VICVectAddr5		(*(volatile uint32_t*)(0xFFFFF114))
#define VICVectAddr6		(*(volatile uint32_t*)(0xFFFFF118))
#define VICVectAddr7		(*(volatile uint32_t*)(0xFFFFF11C))
#define VICVectAddr8		(*(volatile uint32_t*)(0xFFFFF120))
#define VICVectAddr9		(*(volatile uint32_t*)(0xFFFFF124))
#define VICVectAddr10		(*(volatile uint32_t*)(0xFFFFF128))
#define VICVectAddr11		(*(volatile uint32_t*)(0xFFFFF12C))
#define VICVectAddr12		(*(volatile uint32_t*)(0xFFFFF130))
#define VICVectAddr13		(*(volatile uint32_t*)(0xFFFFF134))
#define VICVectAddr14		(*(volatile uint32_t*)(0xFFFFF138))
#define VICVectAddr15		(*(volatile uint32_t*)(0xFFFFF13C))
#define VICVectAddr16		(*(volatile uint32_t*)(0xFFFFF140))
#define VICVectAddr17		(*(volatile uint32_t*)(0xFFFFF144))
#define VICVectAddr18		(*(volatile uint32_t*)(0xFFFFF148))
#define VICVectAddr19		(*(volatile uint32_t*)(0xFFFFF14C))
#define VICVectAddr20		(*(volatile uint32_t*)(0xFFFFF150))
#define VICVectAddr21		(*(volatile uint32_t*)(0xFFFFF154))
#define VICVectAddr22		(*(volatile uint32_t*)(0xFFFFF158))
#define VICVectAddr23		(*(volatile uint32_t*)(0xFFFFF15C))
#define VICVectAddr24		(*(volatile uint32_t*)(0xFFFFF160))
#define VICVectAddr25		(*(volatile uint32_t*)(0xFFFFF164))
#define VICVectAddr26		(*(volatile uint32_t*)(0xFFFFF168))
#define VICVectAddr27		(*(volatile uint32_t*)(0xFFFFF16C))
#define VICVectAddr28		(*(volatile uint32_t*)(0xFFFFF170))
#define VICVectAddr29		(*(volatile uint32_t*)(0xFFFFF174))
#define VICVectAddr30		(*(volatile uint32_t*)(0xFFFFF178))
#define VICVectAddr31		(*(volatile uint32_t*)(0xFFFFF17C))
#define VICVectCntl0		(*(volatile uint32_t*)(0xFFFFF200))
#define VICVectCntl1		(*(volatile uint32_t*)(0xFFFFF204))
#define VICVectCntl2		(*(volatile uint32_t*)(0xFFFFF208))
#define VICVectCntl3		(*(volatile uint32_t*)(0xFFFFF20C))
#define VICVectCntl4		(*(volatile uint32_t*)(0xFFFFF210))
#define VICVectCntl5		(*(volatile uint32_t*)(0xFFFFF214))
#define VICVectCntl6		(*(volatile uint32_t*)(0xFFFFF218))
#define VICVectCntl7		(*(volatile uint32_t*)(0xFFFFF21C))
#define VICVectCntl8		(*(volatile uint32_t*)(0xFFFFF220))
#define VICVectCntl9		(*(volatile uint32_t*)(0xFFFFF224))
#define VICVectCntl10		(*(volatile uint32_t*)(0xFFFFF228))
#define VICVectCntl11		(*(volatile uint32_t*)(0xFFFFF22C))
#define VICVectCntl12		(*(volatile uint32_t*)(0xFFFFF230))
#define VICVectCntl13		(*(volatile uint32_t*)(0xFFFFF234))
#define VICVectCntl14		(*(volatile uint32_t*)(0xFFFFF238))
#define VICVectCntl15		(*(volatile uint32_t*)(0xFFFFF23C))
#define VICVectCntl16		(*(volatile uint32_t*)(0xFFFFF240))
#define VICVectCntl17		(*(volatile uint32_t*)(0xFFFFF244))
#define VICVectCntl18		(*(volatile uint32_t*)(0xFFFFF248))
#define VICVectCntl19		(*(volatile uint32_t*)(0xFFFFF24C))
#define VICVectCntl20		(*(volatile uint32_t*)(0xFFFFF250))
#define VICVectCntl21		(*(volatile uint32_t*)(0xFFFFF254))
#define VICVectCntl22		(*(volatile uint32_t*)(0xFFFFF258))
#define VICVectCntl23		(*(volatile uint32_t*)(0xFFFFF25C))
#define VICVectCntl24		(*(volatile uint32_t*)(0xFFFFF260))
#define VICVectCntl25		(*(volatile uint32_t*)(0xFFFFF264))
#define VICVectCntl26		(*(volatile uint32_t*)(0xFFFFF268))
#define VICVectCntl27		(*(volatile uint32_t*)(0xFFFFF26C))
#define VICVectCntl28		(*(volatile uint32_t*)(0xFFFFF270))
#define VICVectCntl29		(*(volatile uint32_t*)(0xFFFFF274))
#define VICVectCntl30		(*(volatile uint32_t*)(0xFFFFF278))
#define VICVectCntl31		(*(volatile uint32_t*)(0xFFFFF27C))
#define VICVectAddr			(*(volatile uint32_t*)(0xFFFFFF00))

#define PINSEL				( (volatile uint32_t*)(0xE002C000))
#define PINSEL0				(*(volatile uint32_t*)(0xE002C000))
#define PINSEL1				(*(volatile uint32_t*)(0xE002C004))
#define PINSEL2				(*(volatile uint32_t*)(0xE002C008))
#define PINSEL3				(*(volatile uint32_t*)(0xE002C00C))
#define PINSEL4				(*(volatile uint32_t*)(0xE002C010))
#define PINSEL5				(*(volatile uint32_t*)(0xE002C014))
#define PINSEL6				(*(volatile uint32_t*)(0xE002C018))
#define PINSEL7				(*(volatile uint32_t*)(0xE002C01C))
#define PINSEL8				(*(volatile uint32_t*)(0xE002C020))
#define PINSEL9				(*(volatile uint32_t*)(0xE002C024))
#define PINSEL10			(*(volatile uint32_t*)(0xE002C028))

#define PINMODE				( (volatile uint32_t*)(0xE002C040))
#define PINMODE0			(*(volatile uint32_t*)(0xE002C040))
#define PINMODE1			(*(volatile uint32_t*)(0xE002C044))
#define PINMODE2			(*(volatile uint32_t*)(0xE002C048))
#define PINMODE3			(*(volatile uint32_t*)(0xE002C04C))
#define PINMODE4			(*(volatile uint32_t*)(0xE002C050))
#define PINMODE5			(*(volatile uint32_t*)(0xE002C054))
#define PINMODE6			(*(volatile uint32_t*)(0xE002C058))
#define PINMODE7			(*(volatile uint32_t*)(0xE002C05C))
#define PINMODE8			(*(volatile uint32_t*)(0xE002C060))
#define PINMODE9			(*(volatile uint32_t*)(0xE002C064))

#define IOPIN0				(*(volatile uint32_t*)(0xE0028000))
#define IOSET0				(*(volatile uint32_t*)(0xE0028004))
#define IODIR0				(*(volatile uint32_t*)(0xE0028008))
#define IOCLR0				(*(volatile uint32_t*)(0xE002800C))
#define IOPIN1				(*(volatile uint32_t*)(0xE0028010))
#define IOSET1				(*(volatile uint32_t*)(0xE0028014))
#define IODIR1				(*(volatile uint32_t*)(0xE0028018))
#define IOCLR1				(*(volatile uint32_t*)(0xE002801C))

#define IO0_INT_EN_R		(*(volatile uint32_t*)(0xE0028090))
#define IO0_INT_EN_F		(*(volatile uint32_t*)(0xE0028094))
#define IO0_INT_STAT_R		(*(volatile uint32_t*)(0xE0028084))
#define IO0_INT_STAT_F		(*(volatile uint32_t*)(0xE0028088))
#define IO0_INT_CLR			(*(volatile uint32_t*)(0xE002808C))
#define IO2_INT_EN_R		(*(volatile uint32_t*)(0xE00280B0))
#define IO2_INT_EN_F		(*(volatile uint32_t*)(0xE00280B4))
#define IO2_INT_STAT_R		(*(volatile uint32_t*)(0xE00280A4))
#define IO2_INT_STAT_F		(*(volatile uint32_t*)(0xE00280A8))
#define IO2_INT_CLR			(*(volatile uint32_t*)(0xE00280AC))
#define IO_INT_STAT			(*(volatile uint32_t*)(0xE0028080))

#define PARTCFG				(*(volatile uint32_t*)(0x3FFF8000))

#define FIO0DIR				(*(volatile uint32_t*)(0x3FFFC000))
#define FIO0DIRL			(*(volatile uint16_t*)(0x3FFFC000))
#define FIO0DIRU			(*(volatile uint16_t*)(0x3FFFC002))
#define FIO0DIR0			(*(volatile uint8_t*)(0x3FFFC000))
#define FIO0DIR1			(*(volatile uint8_t*)(0x3FFFC001))
#define FIO0DIR2			(*(volatile uint8_t*)(0x3FFFC002))
#define FIO0DIR3			(*(volatile uint8_t*)(0x3FFFC003))

#define FIO0MASK			(*(volatile uint32_t*)(0x3FFFC010))
#define FIO0MASKL			(*(volatile uint16_t*)(0x3FFFC010))
#define FIO0MASKU			(*(volatile uint16_t*)(0x3FFFC012))
#define FIO0MASK0			(*(volatile uint8_t*)(0x3FFFC010))
#define FIO0MASK1			(*(volatile uint8_t*)(0x3FFFC011))
#define FIO0MASK2			(*(volatile uint8_t*)(0x3FFFC012))
#define FIO0MASK3			(*(volatile uint8_t*)(0x3FFFC013))

#define FIO0PIN				(*(volatile uint32_t*)(0x3FFFC014))
#define FIO0PINL			(*(volatile uint16_t*)(0x3FFFC014))
#define FIO0PINU			(*(volatile uint16_t*)(0x3FFFC016))
#define FIO0PIN0			(*(volatile uint8_t*)(0x3FFFC014))
#define FIO0PIN1			(*(volatile uint8_t*)(0x3FFFC015))
#define FIO0PIN2			(*(volatile uint8_t*)(0x3FFFC016))
#define FIO0PIN3			(*(volatile uint8_t*)(0x3FFFC017))

#define FIO0SET				(*(volatile uint32_t*)(0x3FFFC018))
#define FIO0SETL			(*(volatile uint16_t*)(0x3FFFC018))
#define FIO0SETU			(*(volatile uint16_t*)(0x3FFFC01A))
#define FIO0SET0			(*(volatile uint8_t*)(0x3FFFC018))
#define FIO0SET1			(*(volatile uint8_t*)(0x3FFFC019))
#define FIO0SET2			(*(volatile uint8_t*)(0x3FFFC01A))
#define FIO0SET3			(*(volatile uint8_t*)(0x3FFFC01B))

#define FIO0CLR				(*(volatile uint32_t*)(0x3FFFC01C))
#define FIO0CLRL			(*(volatile uint16_t*)(0x3FFFC01C))
#define FIO0CLRU			(*(volatile uint16_t*)(0x3FFFC01E))
#define FIO0CLR0			(*(volatile uint8_t*)(0x3FFFC01C))
#define FIO0CLR1			(*(volatile uint8_t*)(0x3FFFC01D))
#define FIO0CLR2			(*(volatile uint8_t*)(0x3FFFC01E))
#define FIO0CLR3			(*(volatile uint8_t*)(0x3FFFC01F))

#define FIO1DIR				(*(volatile uint32_t*)(0x3FFFC020))
#define FIO1DIRL			(*(volatile uint16_t*)(0x3FFFC020))
#define FIO1DIRU			(*(volatile uint16_t*)(0x3FFFC022))
#define FIO1DIR0			(*(volatile uint8_t*)(0x3FFFC020))
#define FIO1DIR1			(*(volatile uint8_t*)(0x3FFFC021))
#define FIO1DIR2			(*(volatile uint8_t*)(0x3FFFC022))
#define FIO1DIR3			(*(volatile uint8_t*)(0x3FFFC023))

#define FIO1MASK			(*(volatile uint32_t*)(0x3FFFC030))
#define FIO1MASKL			(*(volatile uint16_t*)(0x3FFFC030))
#define FIO1MASKU			(*(volatile uint16_t*)(0x3FFFC032))
#define FIO1MASK0			(*(volatile uint8_t*)(0x3FFFC030))
#define FIO1MASK1			(*(volatile uint8_t*)(0x3FFFC021))
#define FIO1MASK2			(*(volatile uint8_t*)(0x3FFFC032))
#define FIO1MASK3			(*(volatile uint8_t*)(0x3FFFC033))

#define FIO1PIN				(*(volatile uint32_t*)(0x3FFFC034))
#define FIO1PINL			(*(volatile uint16_t*)(0x3FFFC034))
#define FIO1PINU			(*(volatile uint16_t*)(0x3FFFC036))
#define FIO1PIN0			(*(volatile uint8_t*)(0x3FFFC034))
#define FIO1PIN1			(*(volatile uint8_t*)(0x3FFFC025))
#define FIO1PIN2			(*(volatile uint8_t*)(0x3FFFC036))
#define FIO1PIN3			(*(volatile uint8_t*)(0x3FFFC037))

#define FIO1SET				(*(volatile uint32_t*)(0x3FFFC038))
#define FIO1SETL			(*(volatile uint16_t*)(0x3FFFC038))
#define FIO1SETU			(*(volatile uint16_t*)(0x3FFFC03A))
#define FIO1SET0			(*(volatile uint8_t*)(0x3FFFC038))
#define FIO1SET1			(*(volatile uint8_t*)(0x3FFFC029))
#define FIO1SET2			(*(volatile uint8_t*)(0x3FFFC03A))
#define FIO1SET3			(*(volatile uint8_t*)(0x3FFFC03B))

#define FIO1CLR				(*(volatile uint32_t*)(0x3FFFC03C))
#define FIO1CLRL			(*(volatile uint16_t*)(0x3FFFC03C))
#define FIO1CLRU			(*(volatile uint16_t*)(0x3FFFC03E))
#define FIO1CLR0			(*(volatile uint8_t*)(0x3FFFC03C))
#define FIO1CLR1			(*(volatile uint8_t*)(0x3FFFC02D))
#define FIO1CLR2			(*(volatile uint8_t*)(0x3FFFC03E))
#define FIO1CLR3			(*(volatile uint8_t*)(0x3FFFC03F))

#define FIO2DIR				(*(volatile uint32_t*)(0x3FFFC040))
#define FIO2DIRL			(*(volatile uint16_t*)(0x3FFFC040))
#define FIO2DIRU			(*(volatile uint16_t*)(0x3FFFC042))
#define FIO2DIR0			(*(volatile uint8_t*)(0x3FFFC040))
#define FIO2DIR1			(*(volatile uint8_t*)(0x3FFFC041))
#define FIO2DIR2			(*(volatile uint8_t*)(0x3FFFC042))
#define FIO2DIR3			(*(volatile uint8_t*)(0x3FFFC043))

#define FIO2MASK			(*(volatile uint32_t*)(0x3FFFC050))
#define FIO2MASKL			(*(volatile uint16_t*)(0x3FFFC050))
#define FIO2MASKU			(*(volatile uint16_t*)(0x3FFFC052))
#define FIO2MASK0			(*(volatile uint8_t*)(0x3FFFC050))
#define FIO2MASK1			(*(volatile uint8_t*)(0x3FFFC051))
#define FIO2MASK2			(*(volatile uint8_t*)(0x3FFFC052))
#define FIO2MASK3			(*(volatile uint8_t*)(0x3FFFC053))

#define FIO2PIN				(*(volatile uint32_t*)(0x3FFFC054))
#define FIO2PINL			(*(volatile uint16_t*)(0x3FFFC054))
#define FIO2PINU			(*(volatile uint16_t*)(0x3FFFC056))
#define FIO2PIN0			(*(volatile uint8_t*)(0x3FFFC054))
#define FIO2PIN1			(*(volatile uint8_t*)(0x3FFFC055))
#define FIO2PIN2			(*(volatile uint8_t*)(0x3FFFC056))
#define FIO2PIN3			(*(volatile uint8_t*)(0x3FFFC057))

#define FIO2SET				(*(volatile uint32_t*)(0x3FFFC058))
#define FIO2SETL			(*(volatile uint16_t*)(0x3FFFC058))
#define FIO2SETU			(*(volatile uint16_t*)(0x3FFFC05A))
#define FIO2SET0			(*(volatile uint8_t*)(0x3FFFC058))
#define FIO2SET1			(*(volatile uint8_t*)(0x3FFFC059))
#define FIO2SET2			(*(volatile uint8_t*)(0x3FFFC05A))
#define FIO2SET3			(*(volatile uint8_t*)(0x3FFFC05B))

#define FIO2CLR				(*(volatile uint32_t*)(0x3FFFC05C))
#define FIO2CLRL			(*(volatile uint16_t*)(0x3FFFC05C))
#define FIO2CLRU			(*(volatile uint16_t*)(0x3FFFC05E))
#define FIO2CLR0			(*(volatile uint8_t*)(0x3FFFC05C))
#define FIO2CLR1			(*(volatile uint8_t*)(0x3FFFC05D))
#define FIO2CLR2			(*(volatile uint8_t*)(0x3FFFC05E))
#define FIO2CLR3			(*(volatile uint8_t*)(0x3FFFC05F))

#define FIO3DIR				(*(volatile uint32_t*)(0x3FFFC060))
#define FIO3DIRL			(*(volatile uint16_t*)(0x3FFFC060))
#define FIO3DIRU			(*(volatile uint16_t*)(0x3FFFC062))
#define FIO3DIR0			(*(volatile uint8_t*)(0x3FFFC060))
#define FIO3DIR1			(*(volatile uint8_t*)(0x3FFFC061))
#define FIO3DIR2			(*(volatile uint8_t*)(0x3FFFC062))
#define FIO3DIR3			(*(volatile uint8_t*)(0x3FFFC063))

#define FIO3MASK			(*(volatile uint32_t*)(0x3FFFC070))
#define FIO3MASKL			(*(volatile uint16_t*)(0x3FFFC070))
#define FIO3MASKU			(*(volatile uint16_t*)(0x3FFFC072))
#define FIO3MASK0			(*(volatile uint8_t*)(0x3FFFC070))
#define FIO3MASK1			(*(volatile uint8_t*)(0x3FFFC071))
#define FIO3MASK2			(*(volatile uint8_t*)(0x3FFFC072))
#define FIO3MASK3			(*(volatile uint8_t*)(0x3FFFC073))

#define FIO3PIN				(*(volatile uint32_t*)(0x3FFFC074))
#define FIO3PINL			(*(volatile uint16_t*)(0x3FFFC074))
#define FIO3PINU			(*(volatile uint16_t*)(0x3FFFC076))
#define FIO3PIN0			(*(volatile uint8_t*)(0x3FFFC074))
#define FIO3PIN1			(*(volatile uint8_t*)(0x3FFFC075))
#define FIO3PIN2			(*(volatile uint8_t*)(0x3FFFC076))
#define FIO3PIN3			(*(volatile uint8_t*)(0x3FFFC077))

#define FIO3SET				(*(volatile uint32_t*)(0x3FFFC078))
#define FIO3SETL			(*(volatile uint16_t*)(0x3FFFC078))
#define FIO3SETU			(*(volatile uint16_t*)(0x3FFFC07A))
#define FIO3SET0			(*(volatile uint8_t*)(0x3FFFC078))
#define FIO3SET1			(*(volatile uint8_t*)(0x3FFFC079))
#define FIO3SET2			(*(volatile uint8_t*)(0x3FFFC07A))
#define FIO3SET3			(*(volatile uint8_t*)(0x3FFFC07B))

#define FIO3CLR				(*(volatile uint32_t*)(0x3FFFC07C))
#define FIO3CLRL			(*(volatile uint16_t*)(0x3FFFC07C))
#define FIO3CLRU			(*(volatile uint16_t*)(0x3FFFC07E))
#define FIO3CLR0			(*(volatile uint8_t*)(0x3FFFC07C))
#define FIO3CLR1			(*(volatile uint8_t*)(0x3FFFC07D))
#define FIO3CLR2			(*(volatile uint8_t*)(0x3FFFC07E))
#define FIO3CLR3			(*(volatile uint8_t*)(0x3FFFC07F))

#define FIO4DIR				(*(volatile uint32_t*)(0x3FFFC080))
#define FIO4DIRL			(*(volatile uint16_t*)(0x3FFFC080))
#define FIO4DIRU			(*(volatile uint16_t*)(0x3FFFC082))
#define FIO4DIR0			(*(volatile uint8_t*)(0x3FFFC080))
#define FIO4DIR1			(*(volatile uint8_t*)(0x3FFFC081))
#define FIO4DIR2			(*(volatile uint8_t*)(0x3FFFC082))
#define FIO4DIR3			(*(volatile uint8_t*)(0x3FFFC083))

#define FIO4MASK			(*(volatile uint32_t*)(0x3FFFC090))
#define FIO4MASKL			(*(volatile uint16_t*)(0x3FFFC090))
#define FIO4MASKU			(*(volatile uint16_t*)(0x3FFFC092))
#define FIO4MASK0			(*(volatile uint8_t*)(0x3FFFC090))
#define FIO4MASK1			(*(volatile uint8_t*)(0x3FFFC091))
#define FIO4MASK2			(*(volatile uint8_t*)(0x3FFFC092))
#define FIO4MASK3			(*(volatile uint8_t*)(0x3FFFC093))

#define FIO4PIN				(*(volatile uint32_t*)(0x3FFFC094))
#define FIO4PINL			(*(volatile uint16_t*)(0x3FFFC094))
#define FIO4PINU			(*(volatile uint16_t*)(0x3FFFC096))
#define FIO4PIN0			(*(volatile uint8_t*)(0x3FFFC094))
#define FIO4PIN1			(*(volatile uint8_t*)(0x3FFFC095))
#define FIO4PIN2			(*(volatile uint8_t*)(0x3FFFC096))
#define FIO4PIN3			(*(volatile uint8_t*)(0x3FFFC097))

#define FIO4SET				(*(volatile uint32_t*)(0x3FFFC098))
#define FIO4SETL			(*(volatile uint16_t*)(0x3FFFC098))
#define FIO4SETU			(*(volatile uint16_t*)(0x3FFFC09A))
#define FIO4SET0			(*(volatile uint8_t*)(0x3FFFC098))
#define FIO4SET1			(*(volatile uint8_t*)(0x3FFFC099))
#define FIO4SET2			(*(volatile uint8_t*)(0x3FFFC09A))
#define FIO4SET3			(*(volatile uint8_t*)(0x3FFFC09B))

#define FIO4CLR				(*(volatile uint32_t*)(0x3FFFC09C))
#define FIO4CLRL			(*(volatile uint16_t*)(0x3FFFC09C))
#define FIO4CLRU			(*(volatile uint16_t*)(0x3FFFC09E))
#define FIO4CLR0			(*(volatile uint8_t*)(0x3FFFC09C))
#define FIO4CLR1			(*(volatile uint8_t*)(0x3FFFC09D))
#define FIO4CLR2			(*(volatile uint8_t*)(0x3FFFC09E))
#define FIO4CLR3			(*(volatile uint8_t*)(0x3FFFC09F))

#define MAMCR				(*(volatile uint32_t*)(0xE01FC000))
#define MAMTIM				(*(volatile uint32_t*)(0xE01FC004))
#define MEMMAP				(*(volatile uint32_t*)(0xE01FC040))

#define PLLCON				(*(volatile uint32_t*)(0xE01FC080))
#define PLLCFG				(*(volatile uint32_t*)(0xE01FC084))
#define PLLSTAT				(*(volatile uint32_t*)(0xE01FC088))
#define PLLFEED				(*(volatile uint32_t*)(0xE01FC08C))

#define PCON				(*(volatile uint32_t*)(0xE01FC0C0))
#define PCONP				(*(volatile uint32_t*)(0xE01FC0C4))

#define CCLKCFG				(*(volatile uint32_t*)(0xE01FC104))
#define USBCLKCFG			(*(volatile uint32_t*)(0xE01FC108))
#define CLKSRCSEL			(*(volatile uint32_t*)(0xE01FC10C))
#define PCLKSEL				( (volatile uint32_t*)(0xE01FC1A8))
#define PCLKSEL0			(*(volatile uint32_t*)(0xE01FC1A8))
#define PCLKSEL1			(*(volatile uint32_t*)(0xE01FC1AC))

#define EXTINT				(*(volatile uint32_t*)(0xE01FC140))
#define INTWAKE				(*(volatile uint32_t*)(0xE01FC144))
#define EXTMODE				(*(volatile uint32_t*)(0xE01FC148))
#define EXTPOLAR			(*(volatile uint32_t*)(0xE01FC14C))

#define RSIR				(*(volatile uint32_t*)(0xE01FC180))

#define CSPR				(*(volatile uint32_t*)(0xE01FC184))

#define AHBCFG1				(*(volatile uint32_t*)(0xE01FC188))
#define AHBCFG2				(*(volatile uint32_t*)(0xE01FC18C))

#define SCS					(*(volatile uint32_t*)(0xE01FC1A0))

#define EMC_CTRL			(*(volatile uint32_t*)(0xFFE08000))
#define EMC_STAT			(*(volatile uint32_t*)(0xFFE08004))
#define EMC_CONFIG			(*(volatile uint32_t*)(0xFFE08008))

#define EMC_DYN_CTRL		(*(volatile uint32_t*)(0xFFE08020))
#define EMC_DYN_RFSH		(*(volatile uint32_t*)(0xFFE08024))
#define EMC_DYN_RD_CFG		(*(volatile uint32_t*)(0xFFE08028))
#define EMC_DYN_RP			(*(volatile uint32_t*)(0xFFE08030))
#define EMC_DYN_RAS			(*(volatile uint32_t*)(0xFFE08034))
#define EMC_DYN_SREX		(*(volatile uint32_t*)(0xFFE08038))
#define EMC_DYN_APR			(*(volatile uint32_t*)(0xFFE0803C))
#define EMC_DYN_DAL			(*(volatile uint32_t*)(0xFFE08040))
#define EMC_DYN_WR			(*(volatile uint32_t*)(0xFFE08044))
#define EMC_DYN_RC			(*(volatile uint32_t*)(0xFFE08048))
#define EMC_DYN_RFC			(*(volatile uint32_t*)(0xFFE0804C))
#define EMC_DYN_XSR			(*(volatile uint32_t*)(0xFFE08050))
#define EMC_DYN_RRD			(*(volatile uint32_t*)(0xFFE08054))
#define EMC_DYN_MRD			(*(volatile uint32_t*)(0xFFE08058))

#define EMC_DYN_CFG0		(*(volatile uint32_t*)(0xFFE08100))
#define EMC_DYN_RASCAS0		(*(volatile uint32_t*)(0xFFE08104))
#define EMC_DYN_CFG1		(*(volatile uint32_t*)(0xFFE08140))
#define EMC_DYN_RASCAS1		(*(volatile uint32_t*)(0xFFE08144))
#define EMC_DYN_CFG2		(*(volatile uint32_t*)(0xFFE08160))
#define EMC_DYN_RASCAS2		(*(volatile uint32_t*)(0xFFE08164))
#define EMC_DYN_CFG3		(*(volatile uint32_t*)(0xFFE08180))
#define EMC_DYN_RASCAS3		(*(volatile uint32_t*)(0xFFE08184))

#define EMC_STA_CFG0		(*(volatile uint32_t*)(0xFFE08200))
#define EMC_STA_WAITWEN0	(*(volatile uint32_t*)(0xFFE08204))
#define EMC_STA_WAITOEN0	(*(volatile uint32_t*)(0xFFE08208))
#define EMC_STA_WAITRD0		(*(volatile uint32_t*)(0xFFE0820C))
#define EMC_STA_WAITPAGE0	(*(volatile uint32_t*)(0xFFE08210))
#define EMC_STA_WAITWR0		(*(volatile uint32_t*)(0xFFE08214))
#define EMC_STA_WAITTURN0	(*(volatile uint32_t*)(0xFFE08218))

#define EMC_STA_CFG1		(*(volatile uint32_t*)(0xFFE08220))
#define EMC_STA_WAITWEN1	(*(volatile uint32_t*)(0xFFE08224))
#define EMC_STA_WAITOEN1	(*(volatile uint32_t*)(0xFFE08228))
#define EMC_STA_WAITRD1		(*(volatile uint32_t*)(0xFFE0822C))
#define EMC_STA_WAITPAGE1	(*(volatile uint32_t*)(0xFFE08230))
#define EMC_STA_WAITWR1		(*(volatile uint32_t*)(0xFFE08234))
#define EMC_STA_WAITTURN1	(*(volatile uint32_t*)(0xFFE08238))

#define EMC_STA_CFG2		(*(volatile uint32_t*)(0xFFE08240))
#define EMC_STA_WAITWEN2	(*(volatile uint32_t*)(0xFFE08244))
#define EMC_STA_WAITOEN2	(*(volatile uint32_t*)(0xFFE08248))
#define EMC_STA_WAITRD2		(*(volatile uint32_t*)(0xFFE0824C))
#define EMC_STA_WAITPAGE2	(*(volatile uint32_t*)(0xFFE08250))
#define EMC_STA_WAITWR2		(*(volatile uint32_t*)(0xFFE08254))
#define EMC_STA_WAITTURN2	(*(volatile uint32_t*)(0xFFE08258))

#define EMC_STA_CFG3		(*(volatile uint32_t*)(0xFFE08260))
#define EMC_STA_WAITWEN3	(*(volatile uint32_t*)(0xFFE08264))
#define EMC_STA_WAITOEN3	(*(volatile uint32_t*)(0xFFE08268))
#define EMC_STA_WAITRD3		(*(volatile uint32_t*)(0xFFE0826C))
#define EMC_STA_WAITPAGE3	(*(volatile uint32_t*)(0xFFE08270))
#define EMC_STA_WAITWR3		(*(volatile uint32_t*)(0xFFE08274))
#define EMC_STA_WAITTURN3	(*(volatile uint32_t*)(0xFFE08278))

#define EMC_STA_EXT_WAIT	(*(volatile uint32_t*)(0xFFE08880))

#define T0IR				(*(volatile uint32_t*)(0xE0004000))
#define T0TCR				(*(volatile uint32_t*)(0xE0004004))
#define T0TC				(*(volatile uint32_t*)(0xE0004008))
#define T0PR				(*(volatile uint32_t*)(0xE000400C))
#define T0PC				(*(volatile uint32_t*)(0xE0004010))
#define T0MCR				(*(volatile uint32_t*)(0xE0004014))
#define T0MR0				(*(volatile uint32_t*)(0xE0004018))
#define T0MR1				(*(volatile uint32_t*)(0xE000401C))
#define T0MR2				(*(volatile uint32_t*)(0xE0004020))
#define T0MR3				(*(volatile uint32_t*)(0xE0004024))
#define T0CCR				(*(volatile uint32_t*)(0xE0004028))
#define T0CR0				(*(volatile uint32_t*)(0xE000402C))
#define T0CR1				(*(volatile uint32_t*)(0xE0004030))
#define T0CR2				(*(volatile uint32_t*)(0xE0004034))
#define T0CR3				(*(volatile uint32_t*)(0xE0004038))
#define T0EMR				(*(volatile uint32_t*)(0xE000403C))
#define T0CTCR				(*(volatile uint32_t*)(0xE0004070))

#define T1IR				(*(volatile uint32_t*)(0xE0008000))
#define T1TCR				(*(volatile uint32_t*)(0xE0008004))
#define T1TC				(*(volatile uint32_t*)(0xE0008008))
#define T1PR				(*(volatile uint32_t*)(0xE000800C))
#define T1PC				(*(volatile uint32_t*)(0xE0008010))
#define T1MCR				(*(volatile uint32_t*)(0xE0008014))
#define T1MR0				(*(volatile uint32_t*)(0xE0008018))
#define T1MR1				(*(volatile uint32_t*)(0xE000801C))
#define T1MR2				(*(volatile uint32_t*)(0xE0008020))
#define T1MR3				(*(volatile uint32_t*)(0xE0008024))
#define T1CCR				(*(volatile uint32_t*)(0xE0008028))
#define T1CR0				(*(volatile uint32_t*)(0xE000802C))
#define T1CR1				(*(volatile uint32_t*)(0xE0008030))
#define T1CR2				(*(volatile uint32_t*)(0xE0008034))
#define T1CR3				(*(volatile uint32_t*)(0xE0008038))
#define T1EMR				(*(volatile uint32_t*)(0xE000803C))
#define T1CTCR				(*(volatile uint32_t*)(0xE0008070))

#define T2IR				(*(volatile uint32_t*)(0xE0070000))
#define T2TCR				(*(volatile uint32_t*)(0xE0070004))
#define T2TC				(*(volatile uint32_t*)(0xE0070008))
#define T2PR				(*(volatile uint32_t*)(0xE007000C))
#define T2PC				(*(volatile uint32_t*)(0xE0070010))
#define T2MCR				(*(volatile uint32_t*)(0xE0070014))
#define T2MR0				(*(volatile uint32_t*)(0xE0070018))
#define T2MR1				(*(volatile uint32_t*)(0xE007001C))
#define T2MR2				(*(volatile uint32_t*)(0xE0070020))
#define T2MR3				(*(volatile uint32_t*)(0xE0070024))
#define T2CCR				(*(volatile uint32_t*)(0xE0070028))
#define T2CR0				(*(volatile uint32_t*)(0xE007002C))
#define T2CR1				(*(volatile uint32_t*)(0xE0070030))
#define T2CR2				(*(volatile uint32_t*)(0xE0070034))
#define T2CR3				(*(volatile uint32_t*)(0xE0070038))
#define T2EMR				(*(volatile uint32_t*)(0xE007003C))
#define T2CTCR				(*(volatile uint32_t*)(0xE0070070))

#define T3IR				(*(volatile uint32_t*)(0xE0074000))
#define T3TCR				(*(volatile uint32_t*)(0xE0074004))
#define T3TC				(*(volatile uint32_t*)(0xE0074008))
#define T3PR				(*(volatile uint32_t*)(0xE007400C))
#define T3PC				(*(volatile uint32_t*)(0xE0074010))
#define T3MCR				(*(volatile uint32_t*)(0xE0074014))
#define T3MR0				(*(volatile uint32_t*)(0xE0074018))
#define T3MR1				(*(volatile uint32_t*)(0xE007401C))
#define T3MR2				(*(volatile uint32_t*)(0xE0074020))
#define T3MR3				(*(volatile uint32_t*)(0xE0074024))
#define T3CCR				(*(volatile uint32_t*)(0xE0074028))
#define T3CR0				(*(volatile uint32_t*)(0xE007402C))
#define T3CR1				(*(volatile uint32_t*)(0xE0074030))
#define T3CR2				(*(volatile uint32_t*)(0xE0074034))
#define T3CR3				(*(volatile uint32_t*)(0xE0074038))
#define T3EMR				(*(volatile uint32_t*)(0xE007403C))
#define T3CTCR				(*(volatile uint32_t*)(0xE0074070))

#define PWM0IR				(*(volatile uint32_t*)(0xE0014000))
#define PWM0TCR				(*(volatile uint32_t*)(0xE0014004))
#define PWM0TC				(*(volatile uint32_t*)(0xE0014008))
#define PWM0PR				(*(volatile uint32_t*)(0xE001400C))
#define PWM0PC				(*(volatile uint32_t*)(0xE0014010))
#define PWM0MCR				(*(volatile uint32_t*)(0xE0014014))
#define PWM0MR0				(*(volatile uint32_t*)(0xE0014018))
#define PWM0MR1				(*(volatile uint32_t*)(0xE001401C))
#define PWM0MR2				(*(volatile uint32_t*)(0xE0014020))
#define PWM0MR3				(*(volatile uint32_t*)(0xE0014024))
#define PWM0CCR				(*(volatile uint32_t*)(0xE0014028))
#define PWM0CR0				(*(volatile uint32_t*)(0xE001402C))
#define PWM0CR1				(*(volatile uint32_t*)(0xE0014030))
#define PWM0CR2				(*(volatile uint32_t*)(0xE0014034))
#define PWM0CR3				(*(volatile uint32_t*)(0xE0014038))
#define PWM0EMR				(*(volatile uint32_t*)(0xE001403C))
#define PWM0MR4				(*(volatile uint32_t*)(0xE0014040))
#define PWM0MR5				(*(volatile uint32_t*)(0xE0014044))
#define PWM0MR6				(*(volatile uint32_t*)(0xE0014048))
#define PWM0PCR				(*(volatile uint32_t*)(0xE001404C))
#define PWM0LER				(*(volatile uint32_t*)(0xE0014050))
#define PWM0CTCR			(*(volatile uint32_t*)(0xE0014070))

#define PWM1IR				(*(volatile uint32_t*)(0xE0018000))
#define PWM1TCR				(*(volatile uint32_t*)(0xE0018004))
#define PWM1TC				(*(volatile uint32_t*)(0xE0018008))
#define PWM1PR				(*(volatile uint32_t*)(0xE001800C))
#define PWM1PC				(*(volatile uint32_t*)(0xE0018010))
#define PWM1MCR				(*(volatile uint32_t*)(0xE0018014))
#define PWM1MR0				(*(volatile uint32_t*)(0xE0018018))
#define PWM1MR1				(*(volatile uint32_t*)(0xE001801C))
#define PWM1MR2				(*(volatile uint32_t*)(0xE0018020))
#define PWM1MR3				(*(volatile uint32_t*)(0xE0018024))
#define PWM1CCR				(*(volatile uint32_t*)(0xE0018028))
#define PWM1CR0				(*(volatile uint32_t*)(0xE001802C))
#define PWM1CR1				(*(volatile uint32_t*)(0xE0018030))
#define PWM1CR2				(*(volatile uint32_t*)(0xE0018034))
#define PWM1CR3				(*(volatile uint32_t*)(0xE0018038))
#define PWM1EMR				(*(volatile uint32_t*)(0xE001803C))
#define PWM1MR4				(*(volatile uint32_t*)(0xE0018040))
#define PWM1MR5				(*(volatile uint32_t*)(0xE0018044))
#define PWM1MR6				(*(volatile uint32_t*)(0xE0018048))
#define PWM1PCR				(*(volatile uint32_t*)(0xE001804C))
#define PWM1LER				(*(volatile uint32_t*)(0xE0018050))
#define PWM1CTCR			(*(volatile uint32_t*)(0xE0018070))

#define U0RBR				(*(volatile uint32_t*)(0xE000C000))
#define U0THR				(*(volatile uint32_t*)(0xE000C000))
#define U0DLL				(*(volatile uint32_t*)(0xE000C000))
#define U0DLM				(*(volatile uint32_t*)(0xE000C004))
#define U0IER				(*(volatile uint32_t*)(0xE000C004))
#define U0IIR				(*(volatile uint32_t*)(0xE000C008))
#define U0FCR				(*(volatile uint32_t*)(0xE000C008))
#define U0LCR				(*(volatile uint32_t*)(0xE000C00C))
#define U0LSR				(*(volatile uint32_t*)(0xE000C014))
#define U0SCR				(*(volatile uint32_t*)(0xE000C01C))
#define U0ACR				(*(volatile uint32_t*)(0xE000C020))
#define U0ICR				(*(volatile uint32_t*)(0xE000C024))
#define U0FDR				(*(volatile uint32_t*)(0xE000C028))
#define U0TER				(*(volatile uint32_t*)(0xE000C030))

#define U1RBR				(*(volatile uint32_t*)(0xE0010000))
#define U1THR				(*(volatile uint32_t*)(0xE0010000))
#define U1DLL				(*(volatile uint32_t*)(0xE0010000))
#define U1DLM				(*(volatile uint32_t*)(0xE0010004))
#define U1IER				(*(volatile uint32_t*)(0xE0010004))
#define U1IIR				(*(volatile uint32_t*)(0xE0010008))
#define U1FCR				(*(volatile uint32_t*)(0xE0010008))
#define U1LCR				(*(volatile uint32_t*)(0xE001000C))
#define U1MCR				(*(volatile uint32_t*)(0xE0010010))
#define U1LSR				(*(volatile uint32_t*)(0xE0010014))
#define U1MSR				(*(volatile uint32_t*)(0xE0010018))
#define U1SCR				(*(volatile uint32_t*)(0xE001001C))
#define U1ACR				(*(volatile uint32_t*)(0xE0010020))
#define U1FDR				(*(volatile uint32_t*)(0xE0010028))
#define U1TER				(*(volatile uint32_t*)(0xE0010030))

#define U2RBR				(*(volatile uint32_t*)(0xE0078000))
#define U2THR				(*(volatile uint32_t*)(0xE0078000))
#define U2DLL				(*(volatile uint32_t*)(0xE0078000))
#define U2DLM				(*(volatile uint32_t*)(0xE0078004))
#define U2IER				(*(volatile uint32_t*)(0xE0078004))
#define U2IIR				(*(volatile uint32_t*)(0xE0078008))
#define U2FCR				(*(volatile uint32_t*)(0xE0078008))
#define U2LCR				(*(volatile uint32_t*)(0xE007800C))
#define U2LSR				(*(volatile uint32_t*)(0xE0078014))
#define U2SCR				(*(volatile uint32_t*)(0xE007801C))
#define U2ACR				(*(volatile uint32_t*)(0xE0078020))
#define U2ICR				(*(volatile uint32_t*)(0xE0078024))
#define U2FDR				(*(volatile uint32_t*)(0xE0078028))
#define U2TER				(*(volatile uint32_t*)(0xE0078030))

#define U3RBR				(*(volatile uint32_t*)(0xE007C000))
#define U3THR				(*(volatile uint32_t*)(0xE007C000))
#define U3DLL				(*(volatile uint32_t*)(0xE007C000))
#define U3DLM				(*(volatile uint32_t*)(0xE007C004))
#define U3IER				(*(volatile uint32_t*)(0xE007C004))
#define U3IIR				(*(volatile uint32_t*)(0xE007C008))
#define U3FCR				(*(volatile uint32_t*)(0xE007C008))
#define U3LCR				(*(volatile uint32_t*)(0xE007C00C))
#define U3LSR				(*(volatile uint32_t*)(0xE007C014))
#define U3SCR				(*(volatile uint32_t*)(0xE007C01C))
#define U3ACR				(*(volatile uint32_t*)(0xE007C020))
#define U3ICR				(*(volatile uint32_t*)(0xE007C024))
#define U3FDR				(*(volatile uint32_t*)(0xE007C028))
#define U3TER				(*(volatile uint32_t*)(0xE007C030))

#define I20CONSET			(*(volatile uint32_t*)(0xE001C000))
#define I20STAT				(*(volatile uint32_t*)(0xE001C004))
#define I20DAT				(*(volatile uint32_t*)(0xE001C008))
#define I20ADR				(*(volatile uint32_t*)(0xE001C00C))
#define I20SCLH				(*(volatile uint32_t*)(0xE001C010))
#define I20SCLL				(*(volatile uint32_t*)(0xE001C014))
#define I20CONCLR			(*(volatile uint32_t*)(0xE001C018))

#define I21CONSET			(*(volatile uint32_t*)(0xE005C000))
#define I21STAT				(*(volatile uint32_t*)(0xE005C004))
#define I21DAT				(*(volatile uint32_t*)(0xE005C008))
#define I21ADR				(*(volatile uint32_t*)(0xE005C00C))
#define I21SCLH				(*(volatile uint32_t*)(0xE005C010))
#define I21SCLL				(*(volatile uint32_t*)(0xE005C014))
#define I21CONCLR			(*(volatile uint32_t*)(0xE005C018))

#define I22CONSET			(*(volatile uint32_t*)(0xE0080000))
#define I22STAT				(*(volatile uint32_t*)(0xE0080004))
#define I22DAT				(*(volatile uint32_t*)(0xE0080008))
#define I22ADR				(*(volatile uint32_t*)(0xE008000C))
#define I22SCLH				(*(volatile uint32_t*)(0xE0080010))
#define I22SCLL				(*(volatile uint32_t*)(0xE0080014))
#define I22CONCLR			(*(volatile uint32_t*)(0xE0080018))

#define S0SPCR				(*(volatile uint32_t*)(0xE0020000))
#define S0SPSR				(*(volatile uint32_t*)(0xE0020004))
#define S0SPDR				(*(volatile uint32_t*)(0xE0020008))
#define S0SPCCR				(*(volatile uint32_t*)(0xE002000C))
#define S0SPINT				(*(volatile uint32_t*)(0xE002001C))

#define SSP0CR0				(*(volatile uint32_t*)(0xE0068000))
#define SSP0CR1				(*(volatile uint32_t*)(0xE0068004))
#define SSP0DR				(*(volatile uint32_t*)(0xE0068008))
#define SSP0SR				(*(volatile uint32_t*)(0xE006800C))
#define SSP0CPSR			(*(volatile uint32_t*)(0xE0068010))
#define SSP0IMSC			(*(volatile uint32_t*)(0xE0068014))
#define SSP0RIS				(*(volatile uint32_t*)(0xE0068018))
#define SSP0MIS				(*(volatile uint32_t*)(0xE006801C))
#define SSP0ICR				(*(volatile uint32_t*)(0xE0068020))
#define SSP0DMACR			(*(volatile uint32_t*)(0xE0068024))

#define SSP1CR0				(*(volatile uint32_t*)(0xE0030000))
#define SSP1CR1				(*(volatile uint32_t*)(0xE0030004))
#define SSP1DR				(*(volatile uint32_t*)(0xE0030008))
#define SSP1SR				(*(volatile uint32_t*)(0xE003000C))
#define SSP1CPSR			(*(volatile uint32_t*)(0xE0030010))
#define SSP1IMSC			(*(volatile uint32_t*)(0xE0030014))
#define SSP1RIS				(*(volatile uint32_t*)(0xE0030018))
#define SSP1MIS				(*(volatile uint32_t*)(0xE003001C))
#define SSP1ICR				(*(volatile uint32_t*)(0xE0030020))
#define SSP1DMACR			(*(volatile uint32_t*)(0xE0030024))

#define RTC_ILR				(*(volatile uint32_t*)(0xE0024000))
#define RTC_CTC				(*(volatile uint32_t*)(0xE0024004))
#define RTC_CCR				(*(volatile uint32_t*)(0xE0024008))
#define RTC_CIIR			(*(volatile uint32_t*)(0xE002400C))
#define RTC_AMR				(*(volatile uint32_t*)(0xE0024010))
#define RTC_CTIME0			(*(volatile uint32_t*)(0xE0024014))
#define RTC_CTIME1			(*(volatile uint32_t*)(0xE0024018))
#define RTC_CTIME2			(*(volatile uint32_t*)(0xE002401C))
#define RTC_SEC				(*(volatile uint32_t*)(0xE0024020))
#define RTC_MIN				(*(volatile uint32_t*)(0xE0024024))
#define RTC_HOUR			(*(volatile uint32_t*)(0xE0024028))
#define RTC_DOM				(*(volatile uint32_t*)(0xE002402C))
#define RTC_DOW				(*(volatile uint32_t*)(0xE0024030))
#define RTC_DOY				(*(volatile uint32_t*)(0xE0024034))
#define RTC_MONTH			(*(volatile uint32_t*)(0xE0024038))
#define RTC_YEAR			(*(volatile uint32_t*)(0xE002403C))
#define RTC_CISS			(*(volatile uint32_t*)(0xE0024040))
#define RTC_ALSEC			(*(volatile uint32_t*)(0xE0024060))
#define RTC_ALMIN			(*(volatile uint32_t*)(0xE0024064))
#define RTC_ALHOUR			(*(volatile uint32_t*)(0xE0024068))
#define RTC_ALDOM			(*(volatile uint32_t*)(0xE002406C))
#define RTC_ALDOW			(*(volatile uint32_t*)(0xE0024070))
#define RTC_ALDOY			(*(volatile uint32_t*)(0xE0024074))
#define RTC_ALMON			(*(volatile uint32_t*)(0xE0024078))
#define RTC_ALYEAR			(*(volatile uint32_t*)(0xE002407C))
#define RTC_PREINT			(*(volatile uint32_t*)(0xE0024080))
#define RTC_PREFRAC			(*(volatile uint32_t*)(0xE0024084))

#define AD0CR				(*(volatile uint32_t*)(0xE0034000))
#define AD0GDR				(*(volatile uint32_t*)(0xE0034004))
#define AD0INTEN			(*(volatile uint32_t*)(0xE003400C))
#define AD0DR0				(*(volatile uint32_t*)(0xE0034010))
#define AD0DR1				(*(volatile uint32_t*)(0xE0034014))
#define AD0DR2				(*(volatile uint32_t*)(0xE0034018))
#define AD0DR3				(*(volatile uint32_t*)(0xE003401C))
#define AD0DR4				(*(volatile uint32_t*)(0xE0034020))
#define AD0DR5				(*(volatile uint32_t*)(0xE0034024))
#define AD0DR6				(*(volatile uint32_t*)(0xE0034028))
#define AD0DR7				(*(volatile uint32_t*)(0xE003402C))
#define AD0STAT				(*(volatile uint32_t*)(0xE0034030))

#define DACR				(*(volatile uint32_t*)(0xE006C000))

#define WDMOD				(*(volatile uint32_t*)(0xE0000000))
#define WDTC				(*(volatile uint32_t*)(0xE0000004))
#define WDFEED				(*(volatile uint32_t*)(0xE0000008))
#define WDTV				(*(volatile uint32_t*)(0xE000000C))
#define WDCLKSEL			(*(volatile uint32_t*)(0xE0000010))

#define CAN_AFMR			(*(volatile uint32_t*)(0xE003C000))
#define CAN_SFF_SA			(*(volatile uint32_t*)(0xE003C004))
#define CAN_SFF_GRP_SA		(*(volatile uint32_t*)(0xE003C008))
#define CAN_EFF_SA			(*(volatile uint32_t*)(0xE003C00C))
#define CAN_EFF_GRP_SA		(*(volatile uint32_t*)(0xE003C010))
#define CAN_EOT				(*(volatile uint32_t*)(0xE003C014))
#define CAN_LUT_ERR_ADR		(*(volatile uint32_t*)(0xE003C018))
#define CAN_LUT_ERR			(*(volatile uint32_t*)(0xE003C01C))

#define CAN_TX_SR			(*(volatile uint32_t*)(0xE0040000))
#define CAN_RX_SR			(*(volatile uint32_t*)(0xE0040004))
#define CAN_MSR				(*(volatile uint32_t*)(0xE0040008))

#define CAN1MOD				(*(volatile uint32_t*)(0xE0044000))
#define CAN1CMR				(*(volatile uint32_t*)(0xE0044004))
#define CAN1GSR				(*(volatile uint32_t*)(0xE0044008))
#define CAN1ICR				(*(volatile uint32_t*)(0xE004400C))
#define CAN1IER				(*(volatile uint32_t*)(0xE0044010))
#define CAN1BTR				(*(volatile uint32_t*)(0xE0044014))
#define CAN1EWL				(*(volatile uint32_t*)(0xE0044018))
#define CAN1SR				(*(volatile uint32_t*)(0xE004401C))
#define CAN1RFS				(*(volatile uint32_t*)(0xE0044020))
#define CAN1RID				(*(volatile uint32_t*)(0xE0044024))
#define CAN1RDA				(*(volatile uint32_t*)(0xE0044028))
#define CAN1RDB				(*(volatile uint32_t*)(0xE004402C))

#define CAN1TFI1	 		(*(volatile uint32_t*)(0xE0044030))
#define CAN1TID1 			(*(volatile uint32_t*)(0xE0044034))
#define CAN1TDA1 			(*(volatile uint32_t*)(0xE0044038))
#define CAN1TDB1 			(*(volatile uint32_t*)(0xE004403C))
#define CAN1TFI2	 		(*(volatile uint32_t*)(0xE0044040))
#define CAN1TID2 			(*(volatile uint32_t*)(0xE0044044))
#define CAN1TDA2	 		(*(volatile uint32_t*)(0xE0044048))
#define CAN1TDB2 			(*(volatile uint32_t*)(0xE004404C))
#define CAN1TFI3	 		(*(volatile uint32_t*)(0xE0044050))
#define CAN1TID3 			(*(volatile uint32_t*)(0xE0044054))
#define CAN1TDA3	 		(*(volatile uint32_t*)(0xE0044058))
#define CAN1TDB3 			(*(volatile uint32_t*)(0xE004405C))

#define CAN2MOD				(*(volatile uint32_t*)(0xE0048000))
#define CAN2CMR 			(*(volatile uint32_t*)(0xE0048004))
#define CAN2GSR				(*(volatile uint32_t*)(0xE0048008))
#define CAN2ICR 			(*(volatile uint32_t*)(0xE004800C))
#define CAN2IER 			(*(volatile uint32_t*)(0xE0048010))
#define CAN2BTR 			(*(volatile uint32_t*)(0xE0048014))
#define CAN2EWL 			(*(volatile uint32_t*)(0xE0048018))
#define CAN2SR 				(*(volatile uint32_t*)(0xE004801C))
#define CAN2RFS 			(*(volatile uint32_t*)(0xE0048020))
#define CAN2RID 			(*(volatile uint32_t*)(0xE0048024))
#define CAN2RDA 			(*(volatile uint32_t*)(0xE0048028))
#define CAN2RDB 			(*(volatile uint32_t*)(0xE004802C))

#define CAN2TFI1			(*(volatile uint32_t*)(0xE0048030))
#define CAN2TID1			(*(volatile uint32_t*)(0xE0048034))
#define CAN2TDA1			(*(volatile uint32_t*)(0xE0048038))
#define CAN2TDB1			(*(volatile uint32_t*)(0xE004803C))
#define CAN2TFI2			(*(volatile uint32_t*)(0xE0048040))
#define CAN2TID2 			(*(volatile uint32_t*)(0xE0048044))
#define CAN2TDA2 			(*(volatile uint32_t*)(0xE0048048))
#define CAN2TDB2 			(*(volatile uint32_t*)(0xE004804C))
#define CAN2TFI3 			(*(volatile uint32_t*)(0xE0048050))
#define CAN2TID3 			(*(volatile uint32_t*)(0xE0048054))
#define CAN2TDA3 			(*(volatile uint32_t*)(0xE0048058))
#define CAN2TDB3 			(*(volatile uint32_t*)(0xE004805C))

#define MCI_POWER			(*(volatile uint32_t*)(0xE008C000))
#define MCI_CLOCK			(*(volatile uint32_t*)(0xE008C004))
#define MCI_ARGUMENT		(*(volatile uint32_t*)(0xE008C008))
#define MCI_COMMAND			(*(volatile uint32_t*)(0xE008C00C))
#define MCI_RESP_CMD		(*(volatile uint32_t*)(0xE008C010))
#define MCI_RESP0			(*(volatile uint32_t*)(0xE008C014))
#define MCI_RESP1			(*(volatile uint32_t*)(0xE008C018))
#define MCI_RESP2			(*(volatile uint32_t*)(0xE008C01C))
#define MCI_RESP3			(*(volatile uint32_t*)(0xE008C020))
#define MCI_DATA_TMR		(*(volatile uint32_t*)(0xE008C024))
#define MCI_DATA_LEN		(*(volatile uint32_t*)(0xE008C028))
#define MCI_DATA_CTRL		(*(volatile uint32_t*)(0xE008C02C))
#define MCI_DATA_CNT		(*(volatile uint32_t*)(0xE008C030))
#define MCI_STATUS			(*(volatile uint32_t*)(0xE008C034))
#define MCI_CLEAR			(*(volatile uint32_t*)(0xE008C038))
#define MCI_MASK0			(*(volatile uint32_t*)(0xE008C03C))
#define MCI_MASK1			(*(volatile uint32_t*)(0xE008C040))
#define MCI_FIFO_CNT		(*(volatile uint32_t*)(0xE008C048))
#define MCI_FIFO			(*(volatile uint32_t*)(0xE008C080))

#define I2S_DAO				(*(volatile uint32_t*)(0xE0088000))
#define I2S_DAI				(*(volatile uint32_t*)(0xE0088004))
#define I2S_TX_FIFO			(*(volatile uint32_t*)(0xE0088008))
#define I2S_RX_FIFO			(*(volatile uint32_t*)(0xE008800C))
#define I2S_STATE			(*(volatile uint32_t*)(0xE0088010))
#define I2S_DMA1			(*(volatile uint32_t*)(0xE0088014))
#define I2S_DMA2			(*(volatile uint32_t*)(0xE0088018))
#define I2S_IRQ				(*(volatile uint32_t*)(0xE008801C))
#define I2S_TXRATE			(*(volatile uint32_t*)(0xE0088020))
#define I2S_RXRATE			(*(volatile uint32_t*)(0xE0088024))

#define GPDMA_INT_STAT			(*(volatile uint32_t*)(0xFFE04000))
#define GPDMA_INT_TCSTAT		(*(volatile uint32_t*)(0xFFE04004))
#define GPDMA_INT_TCCLR			(*(volatile uint32_t*)(0xFFE04008))
#define GPDMA_INT_ERR_STAT		(*(volatile uint32_t*)(0xFFE0400C))
#define GPDMA_INT_ERR_CLR		(*(volatile uint32_t*)(0xFFE04010))
#define GPDMA_RAW_INT_TCSTAT	(*(volatile uint32_t*)(0xFFE04014))
#define GPDMA_RAW_INT_ERR_STAT	(*(volatile uint32_t*)(0xFFE04018))
#define GPDMA_ENABLED_CHNS		(*(volatile uint32_t*)(0xFFE0401C))
#define GPDMA_SOFT_BREQ			(*(volatile uint32_t*)(0xFFE04020))
#define GPDMA_SOFT_SREQ			(*(volatile uint32_t*)(0xFFE04024))
#define GPDMA_SOFT_LBREQ		(*(volatile uint32_t*)(0xFFE04028))
#define GPDMA_SOFT_LSREQ		(*(volatile uint32_t*)(0xFFE0402C))
#define GPDMA_CONFIG			(*(volatile uint32_t*)(0xFFE04030))
#define GPDMA_SYNC				(*(volatile uint32_t*)(0xFFE04034))

#define GPDMA_CH0_SRC		(*(volatile uint32_t*)(0xFFE04100))
#define GPDMA_CH0_DEST		(*(volatile uint32_t*)(0xFFE04104))
#define GPDMA_CH0_LLI		(*(volatile uint32_t*)(0xFFE04108))
#define GPDMA_CH0_CTRL		(*(volatile uint32_t*)(0xFFE0410C))
#define GPDMA_CH0_CFG		(*(volatile uint32_t*)(0xFFE04110))

#define GPDMA_CH1_SRC		(*(volatile uint32_t*)(0xFFE04120))
#define GPDMA_CH1_DEST		(*(volatile uint32_t*)(0xFFE04124))
#define GPDMA_CH1_LLI		(*(volatile uint32_t*)(0xFFE04128))
#define GPDMA_CH1_CTRL		(*(volatile uint32_t*)(0xFFE0412C))
#define GPDMA_CH1_CFG		(*(volatile uint32_t*)(0xFFE04130))

#define USB_INT_STAT		(*(volatile uint32_t*)(0xE01FC1C0))

#define DEV_INT_STAT		(*(volatile uint32_t*)(0xFFE0C200))
#define DEV_INT_EN			(*(volatile uint32_t*)(0xFFE0C204))
#define DEV_INT_CLR     	(*(volatile uint32_t*)(0xFFE0C208))
#define DEV_INT_SET     	(*(volatile uint32_t*)(0xFFE0C20C))
#define DEV_INT_PRIO    	(*(volatile uint32_t*)(0xFFE0C22C))

#define EP_INT_STAT			(*(volatile uint32_t*)(0xFFE0C230))
#define EP_INT_EN       	(*(volatile uint32_t*)(0xFFE0C234))
#define EP_INT_CLR      	(*(volatile uint32_t*)(0xFFE0C238))
#define EP_INT_SET      	(*(volatile uint32_t*)(0xFFE0C23C))
#define EP_INT_PRIO     	(*(volatile uint32_t*)(0xFFE0C240))

#define REALIZE_EP      	(*(volatile uint32_t*)(0xFFE0C244))
#define EP_INDEX        	(*(volatile uint32_t*)(0xFFE0C248))
#define MAXPACKET_SIZE  	(*(volatile uint32_t*)(0xFFE0C24C))

#define CMD_CODE        	(*(volatile uint32_t*)(0xFFE0C210))
#define CMD_DATA        	(*(volatile uint32_t*)(0xFFE0C214))

#define RX_DATA				(*(volatile uint32_t*)(0xFFE0C218))
#define TX_DATA				(*(volatile uint32_t*)(0xFFE0C21C))
#define RX_PLENGTH			(*(volatile uint32_t*)(0xFFE0C220))
#define TX_PLENGTH			(*(volatile uint32_t*)(0xFFE0C224))
#define USB_CTRL			(*(volatile uint32_t*)(0xFFE0C228))

#define DMA_REQ_STAT		(*(volatile uint32_t*)(0xFFE0C250))
#define DMA_REQ_CLR			(*(volatile uint32_t*)(0xFFE0C254))
#define DMA_REQ_SET			(*(volatile uint32_t*)(0xFFE0C258))
#define UDCA_HEAD			(*(volatile uint32_t*)(0xFFE0C280))
#define EP_DMA_STAT			(*(volatile uint32_t*)(0xFFE0C284))
#define EP_DMA_EN			(*(volatile uint32_t*)(0xFFE0C288))
#define EP_DMA_DIS			(*(volatile uint32_t*)(0xFFE0C28C))
#define DMA_INT_STAT		(*(volatile uint32_t*)(0xFFE0C290))
#define DMA_INT_EN			(*(volatile uint32_t*)(0xFFE0C294))
#define EOT_INT_STAT		(*(volatile uint32_t*)(0xFFE0C2A0))
#define EOT_INT_CLR			(*(volatile uint32_t*)(0xFFE0C2A4))
#define EOT_INT_SET			(*(volatile uint32_t*)(0xFFE0C2A8))
#define NDD_REQ_INT_STAT	(*(volatile uint32_t*)(0xFFE0C2AC))
#define NDD_REQ_INT_CLR		(*(volatile uint32_t*)(0xFFE0C2B0))
#define NDD_REQ_INT_SET		(*(volatile uint32_t*)(0xFFE0C2B4))
#define SYS_ERR_INT_STAT	(*(volatile uint32_t*)(0xFFE0C2B8))
#define SYS_ERR_INT_CLR		(*(volatile uint32_t*)(0xFFE0C2BC))
#define SYS_ERR_INT_SET		(*(volatile uint32_t*)(0xFFE0C2C0))

#define HC_REVISION			(*(volatile uint32_t*)(0xFFE0C000))
#define HC_CONTROL			(*(volatile uint32_t*)(0xFFE0C004))
#define HC_CMD_STAT			(*(volatile uint32_t*)(0xFFE0C008))
#define HC_INT_STAT			(*(volatile uint32_t*)(0xFFE0C00C))
#define HC_INT_EN			(*(volatile uint32_t*)(0xFFE0C010))
#define HC_INT_DIS			(*(volatile uint32_t*)(0xFFE0C014))
#define HC_HCCA				(*(volatile uint32_t*)(0xFFE0C018))
#define HC_PERIOD_CUR_ED	(*(volatile uint32_t*)(0xFFE0C01C))
#define HC_CTRL_HEAD_ED		(*(volatile uint32_t*)(0xFFE0C020))
#define HC_CTRL_CUR_ED		(*(volatile uint32_t*)(0xFFE0C024))
#define HC_BULK_HEAD_ED		(*(volatile uint32_t*)(0xFFE0C028))
#define HC_BULK_CUR_ED		(*(volatile uint32_t*)(0xFFE0C02C))
#define HC_DONE_HEAD		(*(volatile uint32_t*)(0xFFE0C030))
#define HC_FM_INTERVAL		(*(volatile uint32_t*)(0xFFE0C034))
#define HC_FM_REMAINING		(*(volatile uint32_t*)(0xFFE0C038))
#define HC_FM_NUMBER		(*(volatile uint32_t*)(0xFFE0C03C))
#define HC_PERIOD_START		(*(volatile uint32_t*)(0xFFE0C040))
#define HC_LS_THRHLD		(*(volatile uint32_t*)(0xFFE0C044))
#define HC_RH_DESCA			(*(volatile uint32_t*)(0xFFE0C048))
#define HC_RH_DESCB			(*(volatile uint32_t*)(0xFFE0C04C))
#define HC_RH_STAT			(*(volatile uint32_t*)(0xFFE0C050))
#define HC_RH_PORT_STAT1	(*(volatile uint32_t*)(0xFFE0C054))
#define HC_RH_PORT_STAT2	(*(volatile uint32_t*)(0xFFE0C058))

#define OTG_INT_STAT		(*(volatile uint32_t*)(0xFFE0C100))
#define OTG_INT_EN			(*(volatile uint32_t*)(0xFFE0C104))
#define OTG_INT_SET			(*(volatile uint32_t*)(0xFFE0C108))
#define OTG_INT_CLR			(*(volatile uint32_t*)(0xFFE0C10C))
#define OTG_STAT_CTRL       (*(volatile uint32_t*)(0xFFE0C110))
#define OTG_TIMER           (*(volatile uint32_t*)(0xFFE0C114))

#define OTG_I2C_RX			(*(volatile uint32_t*)(0xFFE0C300))
#define OTG_I2C_TX			(*(volatile uint32_t*)(0xFFE0C300))
#define OTG_I2C_STS			(*(volatile uint32_t*)(0xFFE0C304))
#define OTG_I2C_CTL			(*(volatile uint32_t*)(0xFFE0C308))
#define OTG_I2C_CLKHI		(*(volatile uint32_t*)(0xFFE0C30C))
#define OTG_I2C_CLKLO		(*(volatile uint32_t*)(0xFFE0C310))

#define OTG_CLK_CTRL		(*(volatile uint32_t*)(0xFFE0CFF4))
#define OTG_CLK_STAT		(*(volatile uint32_t*)(0xFFE0CFF8))

#define USBPortSel			(*(volatile uint32_t*)(0xFFE0C110))
#define USBClkCtrl			(*(volatile uint32_t*)(0xFFE0CFF4))
#define USBClkSt			(*(volatile uint32_t*)(0xFFE0CFF8))

#define MAC_MAC1			(*(volatile uint32_t*)(0xFFE00000))
#define MAC_MAC2			(*(volatile uint32_t*)(0xFFE00004))
#define MAC_IPGT			(*(volatile uint32_t*)(0xFFE00008))
#define MAC_IPGR			(*(volatile uint32_t*)(0xFFE0000C))
#define MAC_CLRT			(*(volatile uint32_t*)(0xFFE00010))
#define MAC_MAXF			(*(volatile uint32_t*)(0xFFE00014))
#define MAC_SUPP			(*(volatile uint32_t*)(0xFFE00018))
#define MAC_TEST			(*(volatile uint32_t*)(0xFFE0001C))
#define MAC_MCFG			(*(volatile uint32_t*)(0xFFE00020))
#define MAC_MCMD			(*(volatile uint32_t*)(0xFFE00024))
#define MAC_MADR			(*(volatile uint32_t*)(0xFFE00028))
#define MAC_MWTD			(*(volatile uint32_t*)(0xFFE0002C))
#define MAC_MRDD			(*(volatile uint32_t*)(0xFFE00030))
#define MAC_MIND			(*(volatile uint32_t*)(0xFFE00034))

#define MAC_SA0				(*(volatile uint32_t*)(0xFFE00040))
#define MAC_SA1				(*(volatile uint32_t*)(0xFFE00044))
#define MAC_SA2				(*(volatile uint32_t*)(0xFFE00048))

#define MAC_COMMAND			(*(volatile uint32_t*)(0xFFE00100))
#define MAC_STATUS			(*(volatile uint32_t*)(0xFFE00104))
#define MAC_RXDESCRIPTOR	(*(volatile uint32_t*)(0xFFE00108))
#define MAC_RXSTATUS		(*(volatile uint32_t*)(0xFFE0010C))
#define MAC_RXDESCRIPTORNUM	(*(volatile uint32_t*)(0xFFE00110))
#define MAC_RXPRODUCEINDEX	(*(volatile uint32_t*)(0xFFE00114))
#define MAC_RXCONSUMEINDEX	(*(volatile uint32_t*)(0xFFE00118))
#define MAC_TXDESCRIPTOR	(*(volatile uint32_t*)(0xFFE0011C))
#define MAC_TXSTATUS		(*(volatile uint32_t*)(0xFFE00120))
#define MAC_TXDESCRIPTORNUM	(*(volatile uint32_t*)(0xFFE00124))
#define MAC_TXPRODUCEINDEX	(*(volatile uint32_t*)(0xFFE00128))
#define MAC_TXCONSUMEINDEX	(*(volatile uint32_t*)(0xFFE0012C))

#define MAC_TSV0			(*(volatile uint32_t*)(0xFFE00158))
#define MAC_TSV1			(*(volatile uint32_t*)(0xFFE0015C))
#define MAC_RSV				(*(volatile uint32_t*)(0xFFE00160))

#define MAC_FLOWCONTROLCNT	(*(volatile uint32_t*)(0xFFE00170))
#define MAC_FLOWCONTROLSTS	(*(volatile uint32_t*)(0xFFE00174))

#define MAC_RXFILTERCTRL	(*(volatile uint32_t*)(0xFFE00200))
#define MAC_RXFILTERWOLSTS	(*(volatile uint32_t*)(0xFFE00204))
#define MAC_RXFILTERWOLCLR	(*(volatile uint32_t*)(0xFFE00208))

#define MAC_HASHFILTERL		(*(volatile uint32_t*)(0xFFE00210))
#define MAC_HASHFILTERH		(*(volatile uint32_t*)(0xFFE00214))

#define MAC_INTSTATUS		(*(volatile uint32_t*)(0xFFE00FE0))
#define MAC_INTENABLE		(*(volatile uint32_t*)(0xFFE00FE4))
#define MAC_INTCLEAR		(*(volatile uint32_t*)(0xFFE00FE8))
#define MAC_INTSET			(*(volatile uint32_t*)(0xFFE00FEC))

#define MAC_POWERDOWN		(*(volatile uint32_t*)(0xFFE00FF4))
#define MAC_MODULEID		(*(volatile uint32_t*)(0xFFE00FFC))



/*--------------------------------------------------------------*/
/* Power/PCLK controls                                          */
/*--------------------------------------------------------------*/

/* LPC2300 Peripheral Divider */
#define	__set_PCLKSEL(p,v)	PCLKSEL[(p) / 16] = (PCLKSEL[(p) / 16] & ~(3 << ((p) * 2 % 32))) | (v << ((p) * 2 % 32))
#define PCLKDIV_4	0
#define PCLKDIV_1	1
#define PCLKDIV_2	2
#define PCLKDIV_8	3
#define PCLK_WDT	0
#define PCLK_TIMER0	1
#define PCLK_TIMER1	2
#define PCLK_UART0	3
#define PCLK_UART1	4
#define PCLK_PWM1	6
#define PCLK_I2C0	7
#define PCLK_SPI	8
#define PCLK_RTC	9
#define PCLK_SSP1	10
#define PCLK_DAC	11
#define PCLK_ADC	12
#define PCLK_CAN1	13
#define PCLK_CAN2	14
#define PCLK_ACF	15
#define PCLK_BAT_RAM 16
#define PCLK_GPIO	17
#define PCLK_PCB	18
#define PCLK_I2C1	19
#define PCLK_SSP0	21
#define PCLK_TIMER2	22
#define PCLK_TIMER3	23
#define PCLK_UART2	24
#define PCLK_UART3	25
#define PCLK_I2C2	26
#define PCLK_I2S	27
#define PCLK_MCI	28
#define PCLK_SYSCON	 30


/* LPC2300 Pin Configuration */
#define __set_PINSEL(p,b,v)  PINSEL[(p) * 2 + (b) / 16] = (PINSEL[(p) * 2 + (b) / 16] & ~(3 << ((b) * 2 % 32))) | (v << ((b) * 2 % 32))
#define __set_PINMODE(p,b,v) PINMODE[(p) * 2 + (b) / 16] = (PINMODE[(p) * 2 + (b) / 16] & ~(3 << ((b) * 2 % 32))) | (v << ((b) * 2 % 32))
#define PINMODE_PU	0
#define PINMODE_HIZ	2
#define PINMODE_PD	3


/* LPC2300 Power Control */
#define	__set_PCONP(b)	PCONP |= (b)
#define	__clr_PCONP(b)	PCONP &= ~(b)
#define PCTIM0	0x00000002
#define PCTIM1	0x00000004
#define PCUART0	0x00000008
#define PCUART1	0x00000010
#define PCPWM1	0x00000040
#define PCI2C0	0x00000080
#define PCSPI	0x00000100
#define PCRTC	0x00000200
#define PCSSP1	0x00000400
#define PCEMC	0x00000800
#define PCAD	0x00001000
#define PCAN1	0x00002000
#define PCAN2	0x00004000
#define PCI2C1	0x00080000
#define PCSSP0	0x00200000
#define PCTIM2	0x00400000
#define PCTIM3	0x00800000
#define PCUART2	0x01000000
#define PCUART3	0x02000000
#define PCI2C2	0x04000000
#define PCI2S	0x08000000
#define PCSDC	0x10000000
#define PCGPDMA	0x20000000
#define PCENET	0x40000000
#define PCUSB	0x80000000



/*--------------------------------------------------------------*/
/* Misc Macros                                                  */
/*--------------------------------------------------------------*/

/* Bit definitions */
#define	_BV(bit) (1<<(bit))

/* Import a binary file */
#define	IMPORT_BIN(sect, file, sym) asm (\
		".section " #sect "\n"                  /* Change section */\
		".balign 4\n"                           /* Word alignment */\
		".global " #sym "\n"                    /* Export the object address to other modules */\
		#sym ":\n"                              /* Define the object label */\
		".incbin \"" file "\"\n"                /* Import the file */\
		".global _sizeof_" #sym "\n"            /* Export the object size to oher modules */\
		".set _sizeof_" #sym ", . - " #sym "\n" /* Define the object size */\
		".balign 4\n"                           /* Word alignment */\
		".section \".text\"\n")                 /* Restore section */

/* Import a part of binary file */
#define	IMPORT_BIN_PART(sect, file, ofs, siz, sym) asm (\
		".section " #sect "\n"\
		".balign 4\n"\
		".global " #sym "\n"\
		#sym ":\n"\
		".incbin \"" file "\"," #ofs "," #siz "\n"\
		".global _sizeof_" #sym "\n"\
		".set _sizeof_" #sym ", . - " #sym "\n"\
		".balign 4\n"\
		".section \".text\"\n")



#endif	/* #ifdef __LPC2300 */

