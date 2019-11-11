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
    WS2812B_init(RMT_CHANNEL_0, GPIO_NUM_5, 256);
    wsRGB_t* data = new wsRGB_t[256];

    int cnt = 0;
    while (true) {
        for (int i = 0; i < 256; ++i) {
            data[i].r = cnt == 0 ? 1 : 0;
            data[i].g = cnt == 1 ? 1 : 0;
            data[i].b = cnt == 2 ? 1 : 0;
        }
        cnt++;
        if (cnt == 3) {
            cnt = 0;
        }
        WS2812B_setLeds(data, 256);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    delete[] data;
    WS2812B_deInit();

}

void app_main(void)
{
    // WiFiAp* wifiAP = new WiFiAp();
    // wifiAP->start();

    // BluetoothAP* btAP = new BluetoothAP();
    // btAP->start();

    // MicReader* micReader = new MicReader();
    // micReader->start();

    xTaskCreate(&blink_task, "blink_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);
}