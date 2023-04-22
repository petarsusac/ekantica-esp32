// /***************************************************
//   This is a library for the Si1145 UV/IR/Visible Light Sensor
//   Designed specifically to work with the Si1145 sensor in the
//   adafruit shop
//   ----> https://www.adafruit.com/products/1777
//   These sensors use I2C to communicate, 2 pins are required to
//   interface
//   Adafruit invests time and resources providing this open source code,
//   please support Adafruit and open-source hardware by purchasing
//   products from Adafruit!
//   Written by Limor Fried/Ladyada for Adafruit Industries.
//   BSD license, all text above must be included in any redistribution
//  ****************************************************/


// #include <string.h>
// #include <stdlib.h>
// #include <esp_log.h>
// #include <freertos/FreeRTOS.h>
// #include <freertos/task.h>
// #include <esp_idf_lib_helpers.h>

// #include "si1145_v3.h"

// static const char *TAG = "si1145";

// #define CHECK(x) do { esp_err_t __; if ((__ = x) != ESP_OK) return __; } while (0)
// #define CHECK_ARG(VAL) do { if (!(VAL)) return ESP_ERR_INVALID_ARG; } while (0)


// static uint8_t read8(i2c_dev_t *i2c_dev, uint8_t reg_addr);
// static uint16_t read16(i2c_dev_t *i2c_dev, uint16_t reg_addr);
// static esp_err_t write8(i2c_dev_t *i2c_dev,  uint8_t reg_addr, uint8_t val);
// static uint8_t writeParam(i2c_dev_t *i2c_dev, uint8_t p, uint8_t v);
// static uint8_t readParam(i2c_dev_t *i2c_dev, uint8_t p); 
// static esp_err_t si1145_read_from_addr(uint8_t reg_addr, si1145_t *dev, uint16_t *out);


// esp_err_t reset(si1145_t *dev) 
// {
//     CHECK(write8(&dev->i2c_dev, SI1145_REG_MEASRATE0, 0));
//     CHECK(write8(&dev->i2c_dev, SI1145_REG_MEASRATE1, 0));
//     CHECK(write8(&dev->i2c_dev, SI1145_REG_IRQEN, 0));
//     CHECK(write8(&dev->i2c_dev, SI1145_REG_IRQMODE1, 0));
//     CHECK(write8(&dev->i2c_dev, SI1145_REG_IRQMODE2, 0));
//     CHECK(write8(&dev->i2c_dev, SI1145_REG_INTCFG, 0));
//     CHECK(write8(&dev->i2c_dev, SI1145_REG_IRQSTAT, 0xFF));

//     CHECK(write8(&dev->i2c_dev, SI1145_REG_COMMAND, SI1145_RESET));
//     vTaskDelay((TickType_t)(10/ portTICK_PERIOD_MS)); //10ms delay 
//     CHECK(write8(&dev->i2c_dev, SI1145_REG_HWKEY, 0x17));
//     vTaskDelay((TickType_t)(10/ portTICK_PERIOD_MS)); 

//     return ESP_OK;
// }

// esp_err_t si1145_init_desc(si1145_t *dev, i2c_port_t port, 
//         gpio_num_t sda_gpio, gpio_num_t scl_gpio)
// {
//     CHECK_ARG(dev);

//     dev->i2c_dev.port = port; // should this be 0?
//     dev->i2c_dev.addr = SI1145_ADDR;
//     dev->i2c_dev.cfg.sda_io_num = sda_gpio;
//     dev->i2c_dev.cfg.scl_io_num = scl_gpio;
//     dev->i2c_dev.cfg.master.clk_speed = I2C_FREQ_HZ;

//     return i2c_dev_create_mutex(&dev->i2c_dev);
// }

// esp_err_t si1145_free_desc(si1145_t *dev)
// {
//     CHECK_ARG(dev);

//     return i2c_dev_delete_mutex(&dev->i2c_dev);
// }

// esp_err_t si1145_init_sensor(si1145_t *dev)
// {
//     CHECK_ARG(dev);

//     uint8_t id = read8(&dev->i2c_dev, SI1145_REG_PARTID);
//     if (id != 0x45)
//         return ESP_FAIL; // look for SI1145

//     reset(dev);

//     /***********************************/
//     // enable UVindex measurement coefficients!
//     CHECK(write8(&dev->i2c_dev, SI1145_REG_UCOEFF0, 0x29));
//     CHECK(write8(&dev->i2c_dev, SI1145_REG_UCOEFF1, 0x89));
//     CHECK(write8(&dev->i2c_dev, SI1145_REG_UCOEFF2, 0x02));
//     CHECK(write8(&dev->i2c_dev, SI1145_REG_UCOEFF3, 0x00));

//     // enable UV sensor
//     writeParam(&dev->i2c_dev, SI1145_PARAM_CHLIST,
//                 SI1145_PARAM_CHLIST_ENUV | SI1145_PARAM_CHLIST_ENALSIR |
//                     SI1145_PARAM_CHLIST_ENALSVIS | SI1145_PARAM_CHLIST_ENPS1);
//     // enable interrupt on every sample
//     CHECK(write8(&dev->i2c_dev, SI1145_REG_INTCFG, SI1145_REG_INTCFG_INTOE));
//     CHECK(write8(&dev->i2c_dev, SI1145_REG_IRQEN, SI1145_REG_IRQEN_ALSEVERYSAMPLE));

//     /****************************** Prox Sense 1 */

//     // program LED current
//     CHECK(write8(&dev->i2c_dev, SI1145_REG_PSLED21, 0x03)); // 20mA for LED 1 only
//     writeParam(&dev->i2c_dev, SI1145_PARAM_PS1ADCMUX, SI1145_PARAM_ADCMUX_LARGEIR);
//     // prox sensor #1 uses LED #1
//     writeParam(&dev->i2c_dev, SI1145_PARAM_PSLED12SEL, SI1145_PARAM_PSLED12SEL_PS1LED1);
//     // fastest clocks, clock div 1
//     writeParam(&dev->i2c_dev, SI1145_PARAM_PSADCGAIN, 0);
//     // take 511 clocks to measure
//     writeParam(&dev->i2c_dev, SI1145_PARAM_PSADCOUNTER, SI1145_PARAM_ADCCOUNTER_511CLK);
//     // in prox mode, high range
//     writeParam(&dev->i2c_dev, SI1145_PARAM_PSADCMISC,
//                 SI1145_PARAM_PSADCMISC_RANGE | SI1145_PARAM_PSADCMISC_PSMODE);

//     writeParam(&dev->i2c_dev, SI1145_PARAM_ALSIRADCMUX, SI1145_PARAM_ADCMUX_SMALLIR);
//     // fastest clocks, clock div 1
//     writeParam(&dev->i2c_dev, SI1145_PARAM_ALSIRADCGAIN, 0);
//     // take 511 clocks to measure
//     writeParam(&dev->i2c_dev, SI1145_PARAM_ALSIRADCOUNTER, SI1145_PARAM_ADCCOUNTER_511CLK);
//     // in high range mode
//     writeParam(&dev->i2c_dev, SI1145_PARAM_ALSIRADCMISC, SI1145_PARAM_ALSIRADCMISC_RANGE);

//     // fastest clocks, clock div 1
//     writeParam(&dev->i2c_dev, SI1145_PARAM_ALSVISADCGAIN, 0);
//     // take 511 clocks to measure
//     writeParam(&dev->i2c_dev, SI1145_PARAM_ALSVISADCOUNTER, SI1145_PARAM_ADCCOUNTER_511CLK);
//     // in high range mode (not normal signal)
//     writeParam(&dev->i2c_dev, SI1145_PARAM_ALSVISADCMISC, SI1145_PARAM_ALSVISADCMISC_VISRANGE);

//     /************************/

//     // measurement rate for auto
//     CHECK(write8(&dev->i2c_dev, SI1145_REG_MEASRATE0, 0xFF)); // 255 * 31.25uS = 8ms

//     // auto run
//     CHECK(write8(&dev->i2c_dev, SI1145_REG_COMMAND, SI1145_PSALS_AUTO));

//     return ESP_OK;
// }


// esp_err_t si1145_read_uv(si1145_t *dev, uint16_t *out) 
// { 
//    return si1145_read_from_addr(0x2C, dev, out);
// }

// esp_err_t si1145_read_ir(si1145_t *dev, uint16_t *out) 
// {    
//    return si1145_read_from_addr(0x24, dev, out);
// }

// esp_err_t si1145_read_visible(si1145_t *dev, uint16_t *out) 
// {      
//    return si1145_read_from_addr(0x22, dev, out);
// }

// esp_err_t si1145_read_prox(si1145_t *dev, uint16_t *out) 
// {      
//    return si1145_read_from_addr(0x26, dev, out);
// }


// static esp_err_t si1145_read_from_addr(uint8_t reg_addr, si1145_t *dev, uint16_t *out)
// {
//     CHECK_ARG(dev);

//     uint16_t temp = read16(&dev->i2c_dev, reg_addr); 

//     *out = temp; 
//     return ESP_OK;
// }


// //read 8 bits from register
// static uint8_t read8(i2c_dev_t *i2c_dev, uint8_t reg_addr)
// {
//     uint8_t buffer[1] = {reg_addr};

//     I2C_DEV_TAKE_MUTEX(i2c_dev);

//     i2c_dev_write_reg(i2c_dev, reg_addr, buffer, 1);
//     i2c_dev_read_reg(i2c_dev, reg_addr, buffer, 1);

//     I2C_DEV_GIVE_MUTEX(i2c_dev);
//     return buffer[0];
// }

// //read 16 bits from register
// static uint16_t read16(i2c_dev_t *i2c_dev, uint16_t reg_addr)
// {
//     uint8_t buffer[2] = {reg_addr, 0};

//     I2C_DEV_TAKE_MUTEX(i2c_dev);
    
//     i2c_dev_write_reg(i2c_dev, reg_addr, buffer, 1);
//     i2c_dev_read_reg(i2c_dev, reg_addr, buffer, 2);

//     I2C_DEV_GIVE_MUTEX(i2c_dev);

//     return ((uint16_t)buffer[0]) | ((uint16_t)buffer[1] << 8);
// }


// //write to 8 bit register
// static esp_err_t write8(i2c_dev_t *i2c_dev,  uint8_t reg_addr, uint8_t val) 
// {
//     esp_err_t ok;
//     uint8_t buffer[2] = {reg_addr, val};

//     I2C_DEV_TAKE_MUTEX(i2c_dev);
//     ok = i2c_dev_write_reg(i2c_dev, reg_addr, buffer, 2);
//     I2C_DEV_GIVE_MUTEX(i2c_dev);

//     return ok;
// }


// static uint8_t writeParam(i2c_dev_t *i2c_dev, uint8_t p, uint8_t v) 
// {
//     write8(i2c_dev, SI1145_REG_PARAMWR, v);
//     write8(i2c_dev, SI1145_REG_COMMAND, p | SI1145_PARAM_SET);
//     return read8(i2c_dev, SI1145_REG_PARAMRD);
// }


// static uint8_t readParam(i2c_dev_t *i2c_dev, uint8_t p) 
// {
//     write8(i2c_dev, SI1145_REG_COMMAND, p | SI1145_PARAM_QUERY);
//     return read8(i2c_dev, SI1145_REG_PARAMRD);
// }
