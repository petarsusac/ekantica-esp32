#pragma once

#include "driver/adc.h"
#include "esp_adc_cal.h"

#define DRY_SOIL	4095
#define WET_SOIL	3000

static esp_adc_cal_characteristics_t *adc_chars;
static const adc_channel_t channel = ADC_CHANNEL_0;     
static const adc_bits_width_t width = ADC_WIDTH_BIT_12;
static const adc_atten_t atten = ADC_ATTEN_DB_11;

void moisture_init(void);

int read_moisture_percentage(void);