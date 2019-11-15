#ifndef LED_CONTROLLER_H_
#define LED_CONTROLLER_H_

#include "driver/rmt.h"
#include "LedMatrix.hpp"

#define LED_CONTROLLER_TAG "LedController"


class LedController {

public:
    LedController();
    ~LedController();

    void setPixelColor(MatrixDimenType xPos, MatrixDimenType yPos, ColorType red, ColorType green, ColorType blue);
    void update();

private:
    LedMatrix* pLedMatrix;

    rmt_item32_t mLogicZero;
    rmt_item32_t mLogicOne;
    rmt_item32_t* pRawData;
    const rmt_channel_t mChannel = RMT_CHANNEL_0;

};

#endif /* LED_CONTROLLER_H_ */