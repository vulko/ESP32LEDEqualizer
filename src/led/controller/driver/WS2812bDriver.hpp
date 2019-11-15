#ifndef LED_WS2818B_DRIVER_H_
#define LED_WS2818B_DRIVER_H_

#include "led/controller/LedMatrix.hpp"
#include <driver/rmt.h>


class WS2812bDriver {
public:
	WS2812bDriver(MatrixSizeType dataSize);
    ~WS2812bDriver();

    void convertToHWFormat(PixelData* pixelData, rmt_item32_t* rawData);

private:
    rmt_item32_t mLogicZero;
    rmt_item32_t mLogicOne;
    MatrixSizeType mDataSize;

};

#endif /* LED_WS2818B_DRIVER_H_ */