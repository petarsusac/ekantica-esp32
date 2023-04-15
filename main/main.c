#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include <stdlib.h>
#include "esp_log.h"
#include "nvs_flash.h"

#include "network.h"
#include "moisture.h"
#include "dht.h"

#define DHT_PIN 10 // cast to gpio_num_t

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

    network_init();
    moisture_init();

    while(1)
    {
      moisture = read_moisture_percentage();
      printf("moisture percentage: %d%%\n", moisture);

      dht_ok = dht_read_float_data(sensor_type, (gpio_num_t)DHT_PIN, &humidity, &temperature) != ESP_OK;

      if(dht_ok == ESP_OK) {
          printf("Temperature: %.2f°C, Humidity: %.2f%%\n", temperature, humidity);
      } else {
          printf("Error reading DHT22 sensor\n");
      }

      network_data_t data = {
        .temperature = temperature,
        .humidity = humidity,
        .moisture = moisture,
        .water_level = 99,
      };

      int response = network_send_request(data);
      printf("Response: %d\n", response);

      vTaskDelay(pdMS_TO_TICKS(1000)); // 1 second
    }
}
