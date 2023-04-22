#pragma once

#include "adc.h"

#define WET_SOIL	4095
#define DRY_SOIL	2000

static const adc_channel_t moisture_channel = ADC_CHANNEL_2;

void moisture_init(void);

int read_moisture(void);