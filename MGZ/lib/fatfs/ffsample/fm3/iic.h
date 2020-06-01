#ifndef I2C_DEFINED
#define I2C_DEFINED
#include <stdint.h>

enum { I2C_WRITE, I2C_READ };	/* Data directiron flag (I2CCTRL.dir) */

/* I2C transaction work area */
typedef struct {
	uint8_t status;			/* Status of I2C transaction (0:busy, !0:terminated) */
	uint8_t phase;			/* Current state of the transaction */
	uint8_t dir;			/* Read or write for secondary data (I2C_WRITE, I2C_READ) */
	uint8_t sla;			/* 7-bit slave address (0..127) */
	uint16_t retry;			/* Number of retries of SLA+W when slave not responded (0..) */
	uint8_t ncmd;			/* Number of bytes of cmd[] (1..4) */
	uint8_t icmd;			/* Index of command byte */
	uint8_t cmd[4];			/* Command bytes follows SLA+W */
	uint16_t ndata;			/* Number of bytes of secondary data (0:no secondary data transfer) */
	uint8_t *data;			/* Pointer to secondary data buffer */
	void (*eotfunc)(int);	/* Call-back function to notify end of transaction (0:not used) */
} I2CCTRL;


/* Status code (I2CCTRL.status) */
enum {
	I2C_BUSY = 0,	/* An I2C transaction is in progress. Must not discard this structure */
	I2C_SUCCEEDED,	/* Transaction succeeded */
	I2C_TIMEOUT,	/* Failed due to slave not responded to addressing */
	I2C_ABORTED,	/* Failed due to slave not responded to sent data */
	I2C_ERROR		/* Failed due to bus error, arbitration failed or unknown error */
};


/* I2C control module API */
void i2c_init (void);				/* Initialize I2C module */
int i2c_start (volatile I2CCTRL*);	/* Start an I2C transaction */
void i2c_abort (void);				/* Abort an I2C transaction in progress */

#endif
