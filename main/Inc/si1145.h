#pragma once

#include <stdint.h>
#include "i2c.h"

#define SI1145_REG_UCOEFF0    0x13
#define SI1145_REG_UCOEFF1    0x14
#define SI1145_REG_UCOEFF2    0x15
#define SI1145_REG_UCOEFF3    0x16
#define SI1145_REG_PARAMWR    0x17
#define SI1145_REG_COMMAND    0x18
#define SI1145_REG_RESPONSE   0x20
#define SI1145_REG_UVINDEX0   0x2C
#define SI1145_REG_VISIR      0x22
#define SI1145_REG_VISIRF     0x24

uint8_t si1145_i2c_addr;

uint8_t si1145_read_register(uint8_t reg);

void si1145_write_register(uint8_t reg, uint8_t data);

void si1145_init(i2c_port_t i2c_num, uint8_t i2c_addr);

void si1145_read_uv_index(uint16_t *uv_index);

void si1145_read_visible(uint16_t *visible);