#include <stdio.h>
#include <esp_sleep.h>
#include <esp_log.h>

const char *TAG = "[SLEEP]";

void sleep_deep_ms(uint32_t ms)
{
    ESP_LOGI(TAG, "Going into deep sleep for %lu ms", ms);
    esp_sleep_enable_timer_wakeup(ms * 1000);
    esp_deep_sleep_start();
}

void sleep_light_ms(uint32_t ms)
{
    ESP_LOGI(TAG, "Going into light sleep for %lu ms", ms);
    esp_sleep_enable_timer_wakeup(ms * 1000);
    esp_light_sleep_start();
}