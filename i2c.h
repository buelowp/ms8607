#ifndef __I2C_H__
#define __I2C_H__

#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <linux/i2c-dev.h>

enum i2c_transfer_direction {
 	I2C_TRANSFER_WRITE = 0,
 	I2C_TRANSFER_READ  = 1,
};

enum status_code {
	STATUS_OK           = 0x00,
	STATUS_ERR_OVERFLOW	= 0x01,
    STATUS_ERR_TIMEOUT  = 0x02,
    STATUS_ERR_ERROR = 0x03,
};

struct i2c_master_packet {
	// Address to slave device
	uint16_t address;
	// Length of data array
	uint16_t data_length;
	// Data array containing all data to be transferred
	uint8_t *data;
};

#ifdef __cplusplus
extern "C" {
#endif
    int i2c_master_init(const char *device);
    enum status_code i2c_master_read_packet_wait(struct i2c_master_packet *const packet);
    enum status_code i2c_master_write_packet_wait(struct i2c_master_packet *const packet);
    enum status_code i2c_master_write_packet_wait_no_stop(struct i2c_master_packet *const packet);
	void i2c_master_close();
    void delay_ms(int);
#ifdef __cplusplus
}
#endif

#endif
