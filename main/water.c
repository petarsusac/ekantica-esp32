#include "adc.h"
#include "water.h"


/**
 * Setup water level ADC settings.
 */
void water_init() {
    adc1_config_channel_atten(water_channel, atten);
}

/**
 * Reads water level from dedicated GPIO pin.
 * Returns water level percentage.
 */
int read_water_level(void) {

    int adc_value = adc1_get_raw(water_channel);
    float water_level = 0;
    
	if (adc_value >= TANK_FULL) {
		water_level = 100.0;
	} else if (adc_value <= TANK_EMPTY) {
		water_level = 0.0;
	} else {
		water_level = ((100.0)/((double) TANK_FULL - (double) TANK_EMPTY))*((double) (adc_value) - (double) TANK_EMPTY);
	}

    return (int)water_level;
	// return adc_value;
}