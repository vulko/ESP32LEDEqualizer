#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "server/wifi/WiFiAP.hpp"
#include "server/bluetooth/BluetoothAP.hpp"
#include "mic/MicReader.hpp"
#include "LedController/LedController.hpp"


/* Can run 'make menuconfig' to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO GPIO_NUM_5

extern "C" {
	void app_main(void);
}

void blink_task(void *pvParameter)
{
    LedController* pLedController = new LedController();

    MatrixDimenType x = 0;
    MatrixDimenType y = 0;
    MatrixDimenType xCnt = 0;
    MatrixDimenType yCnt = 0;
    while (true) {
        for (x = 0; x < 16; ++x) {
            for (y = 0; y < 16; ++y) {
                if (x == xCnt && y == yCnt) {
                    pLedController->setPixelColor(x, y, 1, 0, 0);
                } else {
                    pLedController->setPixelColor(x, y, 0, 0, 0);
                }
            }
        }

        ++xCnt;
        if (xCnt == 16)
        {
            xCnt = 0;
            ++yCnt;
        }
        if (yCnt == 16)
        {
            xCnt = 0;
            yCnt = 0;
        }

        pLedController->update();
        ets_delay_us(10000);
    }
    
    delete pLedController;
}

void app_main(void)
{
    // WiFiAp* wifiAP = new WiFiAp();
    // wifiAP->start();

    // BluetoothAP* btAP = new BluetoothAP();
    // btAP->start();

    // MicReader* micReader = new MicReader();
    // micReader->start();

    xTaskCreate(&blink_task, "blink_task", configISR_STACK_SIZE, NULL, 2 | portPRIVILEGE_BIT, NULL);
}