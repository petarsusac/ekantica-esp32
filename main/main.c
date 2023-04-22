#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include <stdlib.h>
#include "esp_log.h"
#include "nvs_flash.h"

#include "network.h"
#include "moisture.h"
#include "dht.h"
#include "relay.h"
#include "sleep.h"
#include "moisture.h"
#include "water.h"
#include "adc.h"
#include "i2c.h"
#include "si1145.h"

#define DHT_PIN GPIO_NUM_10 
#define I2C_ADDR_SI1145 0x60 // I2C address of the SI1145 sensor
#define RELAY_PIN 5

static const dht_sensor_type_t sensor_type = DHT_TYPE_DHT11;

void app_main(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    esp_err_t dht_ok;
    float humidity = 0;
    float temperature = 0;
    int moisture = 0;
    int water_level = 0;
    uint16_t uv_index = 0;
    uint16_t visible_light = 0;

    network_init();

    adc_init();
    moisture_init();
    water_init();
    i2c_init(I2C_NUM_0, SDA_PIN, SCL_PIN);
    si1145_init(I2C_NUM_0, I2C_ADDR_SI1145);

    relay_t *relay = relay_create(RELAY_PIN);

    while(1)
    {
      moisture = read_moisture();
      printf("moisture percentage: %d%%\n", moisture);

      water_level = read_water_level();
      printf("water level: %d%%\n", water_level);  

      dht_ok = dht_read_float_data(sensor_type, DHT_PIN, &humidity, &temperature) != ESP_OK;

      if(dht_ok == ESP_OK) {
          printf("Temperature: %.2f°C, Humidity: %.2f%%\n", temperature, humidity);
      } else {
          printf("Error reading DHT22 sensor\n");
      }

      si1145_read_uv_index(&uv_index);
      si1145_read_visible(&visible_light);
      printf("UV index: %d%%\n", uv_index);
      printf("Visible light: %d%%\n", visible_light);

      network_data_t data = {
        .temperature = temperature,
        .humidity = humidity,
        .moisture = moisture,
        .water_level = water_level,
        .uv_index = (int)uv_index,
        .visible_light = (int)visible_light
      };

      int response = network_send_request(data);
      printf("Response: %d\n", response);

      if (response == 1)
      {
        relay_pulse_blocking(relay, 3000); // Turn pump on for 3 seconds
      }

      // vTaskDelay(pdMS_TO_TICKS(1000)); // 1 second
      sleep_light_ms(1000);
    }
}
