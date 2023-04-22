#pragma once

#include "adc.h"

#define TANK_FULL   4095 
#define TANK_EMPTY  2000

static const adc_channel_t water_channel = ADC_CHANNEL_3;

void water_init(void);

int read_water_level(void);