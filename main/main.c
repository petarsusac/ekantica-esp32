#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>

#include <sleep.h>

#define LED_GPIO 8

void app_main(void)
{
    sleep_deep_ms(1000);
    while(1)
    {
        vTaskDelay(1);
    }
}
