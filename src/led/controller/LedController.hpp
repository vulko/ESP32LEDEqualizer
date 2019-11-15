#ifndef LED_CONTROLLER_H_
#define LED_CONTROLLER_H_

#include "driver/rmt.h"
#include "driver/WS2812bDriver.hpp"
#include <led/effects/LedEffectBase.hpp>

#define LED_CONTROLLER_TAG "LedController"


class LedController {

public:
    LedController();
    ~LedController();

    void repaint();

private:
    LedMatrix* pLedMatrix;
    WS2812bDriver* pLedDriver;
    LedEffectBase* pLedEffectBase;

    rmt_item32_t* pRawData;
    const rmt_channel_t mChannel = RMT_CHANNEL_0;

};

#endif /* LED_CONTROLLER_H_ */