// #include "si1145_v2.h"

// static i2c_port_t i2c_port = I2C_NUM_0;
// static i2c_config_t i2c_config = {
//     .mode = I2C_MODE_MASTER,
//     .sda_io_num = GPIO_NUM_7,
//     .scl_io_num = GPIO_NUM_6,
//     .sda_pullup_en = GPIO_PULLUP_ENABLE,
//     .scl_pullup_en = GPIO_PULLUP_ENABLE,
//     .master.clk_speed = 100000
// };

// void si1145_init(void)
// {
//     i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//     i2c_master_start(cmd);
//     i2c_master_write_byte(cmd, SI1145_ADDR << 1 | I2C_MASTER_WRITE, true);
//     i2c_master_write_byte(cmd, 0x80, true);
//     i2c_master_write_byte(cmd, 0x03, true);
//     i2c_master_stop(cmd);
//     i2c_master_cmd_begin(i2c_port, cmd, 1000 / portTICK_PERIOD_MS);
//     i2c_cmd_link_delete(cmd);
// }

// uint16_t si1145_read(uint8_t reg)
// {
//     uint8_t data[2] = {0, 0};
//     i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//     i2c_master_start(cmd);
//     i2c_master_write_byte(cmd, SI1145_ADDR << 1 | I2C_MASTER_WRITE, true);
//     i2c_master_write_byte(cmd, reg, true);
//     i2c_master_start(cmd);
//     i2c_master_write_byte(cmd, SI1145_ADDR << 1 | I2C_MASTER_READ, true);
//     i2c_master_read_byte(cmd, &data[0], I2C_MASTER_ACK);
//     i2c_master_read_byte(cmd, &data[1], I2C_MASTER_LAST_NACK);
//     i2c_master_stop(cmd);
//     i2c_master_cmd_begin(i2c_port, cmd, 1000 / portTICK_PERIOD_MS);
//     i2c_cmd_link_delete(cmd);
//     return (data[1] << 8) | data[0];
// }
