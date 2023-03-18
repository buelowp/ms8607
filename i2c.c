#include "i2c.h"

static int g_fd;

int i2c_master_init(const char *device)
{
    g_fd = -1;

    if ((g_fd = open(device, O_RDWR)) == -1) {
        perror("open");
        return -1;
    }
    return g_fd;
}

void i2c_master_close()
{
    close(g_fd);
}

enum status_code i2c_master_read_packet_wait(struct i2c_master_packet *const packet)
{
    if (g_fd != -1) {
        if (ioctl(g_fd, I2C_SLAVE, packet->address) == -1) {
            perror("i2c_master_read_packet_wait: ioctl");
            return STATUS_ERR_ERROR;
        }
        if (read(g_fd, packet->data, packet->data_length) != packet->data_length) {
            perror("read");
            return STATUS_ERR_ERROR;
        }
        return STATUS_OK;
    }
    return STATUS_ERR_ERROR;
}

enum status_code i2c_master_write_packet_wait(struct i2c_master_packet *const packet)
{
    if (g_fd != -1) {
        if (ioctl(g_fd, I2C_SLAVE, packet->address) == -1) {
            perror("i2c_master_write_packet_wait: ioctl");
            return STATUS_ERR_ERROR;
        }
        if (write(g_fd, packet->data, packet->data_length) != packet->data_length) {
            perror("read");
            return STATUS_ERR_ERROR;
        }
        return STATUS_OK;
    }
    return STATUS_ERR_ERROR;
}

enum status_code i2c_master_write_packet_wait_no_stop(struct i2c_master_packet *const packet)
{
    return STATUS_ERR_ERROR;
}

void delay_ms(int period)
{
    usleep(period * 1000);
}
