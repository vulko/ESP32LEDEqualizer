#ifndef LED_CONTROLLER_H_
#define LED_CONTROLLER_H_

#include "driver/rmt.h"

typedef struct
{
	uint8_t g;
	uint8_t b;
	uint8_t r;
}wsRGB_t;

/**
 * Init RMT module and allocates space
 * @param channel RMT channel
 * @param gpio GPIO Pin
 * @param size Number of LED's
 */
void WS2812B_init(rmt_channel_t channel, gpio_num_t gpio, unsigned int size);

/**
 * Writes to the LED
 * @param data
 * @param size Number of LED's - Must not exceed initialization size
 */
void WS2812B_setLeds(wsRGB_t* data, unsigned int size);

/**
 * Deinit driver and free memory space
 */
void WS2812B_deInit(void);

#endif /* LED_CONTROLLER_H_ */