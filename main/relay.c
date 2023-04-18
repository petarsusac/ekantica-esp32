#include "relay.h"

#include "driver/gpio.h"
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

struct _relay_t 
{
    gpio_num_t gpio;
};

relay_t *relay_create(int gpio)
{
    relay_t *p_relay = (relay_t *) malloc(sizeof(relay_t));
    if (p_relay)
    {
        p_relay->gpio = (gpio_num_t) gpio;
        gpio_set_direction(p_relay->gpio, GPIO_MODE_OUTPUT);
        gpio_set_level(p_relay->gpio, 0);
    }

    return p_relay;
}

void relay_destroy(relay_t *relay)
{
    if (relay)
    {
        gpio_reset_pin(relay->gpio);
        free(relay);
    }
}

void relay_on(relay_t *relay)
{
    if (relay)
    {
        gpio_set_level(relay->gpio, 1);
    }
}

void relay_off(relay_t *relay)
{
    if (relay)
    {
        gpio_set_level(relay->gpio, 0);
    }
}

void relay_pulse_blocking(relay_t *relay, unsigned ms)
{
    if (relay)
    {
        relay_on(relay);
        vTaskDelay(pdMS_TO_TICKS(ms));
        relay_off(relay);
    }
}
