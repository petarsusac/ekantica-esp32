#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include <stdlib.h>
#include "esp_log.h"
#include "nvs_flash.h"

#include "network.h"
#include "moisture.h"

void app_main(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    network_init();
    moisture_init();

    while(1)
    {
      int moisture = read_moisture_percentage();
      printf("moisture percentage: %d%%\n", moisture);

      network_data_t data = {
        .temperature = 25,
        .humidity = 35,
        .moisture = moisture,
        .water_level = 99,
      };

      int res = network_send_request(data);
      printf("Response: %d\n", res);

      vTaskDelay(pdMS_TO_TICKS(1000)); // 1 second
    }
}
