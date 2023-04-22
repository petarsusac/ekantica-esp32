#include "si1145.h"

uint8_t si1145_read_register(uint8_t reg)
{
    uint8_t data;
    i2c_read_register(si1145_i2c_addr, reg, &data, 1);
    return data;
}

void si1145_write_register(uint8_t reg, uint8_t data)
{
    i2c_write_register(si1145_i2c_addr, reg, &data, 1);
}

void si1145_init(i2c_port_t i2c_num, uint8_t i2c_addr)
{
    si1145_i2c_addr = i2c_addr;

    // Reset SI1145 sensor
    si1145_write_register(SI1145_REG_COMMAND, 0x01);
    vTaskDelay(pdMS_TO_TICKS(10)); // Wait 10 ms for reset to complete

    // Initialize SI1145 sensor
    si1145_write_register(SI1145_REG_UCOEFF0, 0x7B);
    si1145_write_register(SI1145_REG_UCOEFF1, 0x6B);
    si1145_write_register(SI1145_REG_UCOEFF2, 0x01);
    si1145_write_register(SI1145_REG_UCOEFF3, 0x00);

    si1145_write_register(SI1145_REG_PARAMWR, 0x01);
    si1145_write_register(SI1145_REG_COMMAND, 0x0F);
}

void si1145_read_uv_index(uint16_t *uv_index)
{
    uint8_t data[2];

    si1145_write_register(SI1145_REG_COMMAND, 0x0A); // Start UV index measurement
    vTaskDelay(pdMS_TO_TICKS(10)); // Wait 10 ms for measurement to complete

    i2c_read_register(si1145_i2c_addr, SI1145_REG_UVINDEX0, data, 2);

    *uv_index = (data[1] << 8) | data[0];
}

void si1145_read_visible(uint16_t *visible)
{
    uint8_t data[2];

    i2c_read_register(si1145_i2c_addr, SI1145_REG_VISIR, data, 2);

    *visible = (data[1] << 8) | data[0];
}