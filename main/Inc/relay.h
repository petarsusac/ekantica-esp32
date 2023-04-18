#pragma once

typedef struct _relay_t relay_t;

relay_t *relay_create(int gpio);
void relay_destroy(relay_t *relay);
void relay_on(relay_t *relay);
void relay_off(relay_t *relay);
void relay_pulse_blocking(relay_t *relay, unsigned ms);
