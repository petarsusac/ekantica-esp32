#pragma once

#include "driver/adc.h"
#include "esp_adc_cal.h"

static const adc_bits_width_t width = ADC_WIDTH_BIT_12;
static const adc_atten_t atten = ADC_ATTEN_DB_11;

void adc_init(void);