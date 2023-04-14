#include "moisture.h"

void moisture_init() {
    //Configure ADC
    adc1_config_width(width);
    adc1_config_channel_atten(channel, atten);
    adc_chars = (esp_adc_cal_characteristics_t*)calloc(1, sizeof(esp_adc_cal_characteristics_t));
}

int read_moisture_percentage(void) {

    // Read the voltage from channel 0 of ADC_UNIT_1
    int adc_value = adc1_get_raw((adc1_channel_t)channel);
    float moisture = 0;
    
	if (adc_value >= DRY_SOIL) {
		moisture = 0.0;
	} else if (adc_value <= WET_SOIL) {
		moisture = 100.0;
	} else {
		moisture = ((100.0)/((double) WET_SOIL - (double) DRY_SOIL))*((double) (adc_value) - (double) DRY_SOIL);
	}

    return (int)moisture;
}