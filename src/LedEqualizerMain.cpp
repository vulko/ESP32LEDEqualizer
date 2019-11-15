#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "server/wifi/WiFiAP.hpp"
#include "server/bluetooth/BluetoothAP.hpp"
#include "mic/MicReader.hpp"
#include "led/controller/LedController.hpp"


/* Can run 'make menuconfig' to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO GPIO_NUM_5

extern "C" {
	void app_main(void);
}

void blink_task(void *pvParameter)
{
}

void app_main(void)
{
    // WiFiAp* wifiAP = new WiFiAp();
    // wifiAP->start();

    // BluetoothAP* btAP = new BluetoothAP();
    // btAP->start();

    // MicReader* micReader = new MicReader();
    // micReader->start();

    // xTaskCreate(&blink_task, "blink_task", configISR_STACK_SIZE, NULL, 2 | portPRIVILEGE_BIT, NULL);
    
    LedController* pLedController = new LedController();
    while (true) {
        pLedController->repaint();
        ets_delay_us(80000);
    }
}