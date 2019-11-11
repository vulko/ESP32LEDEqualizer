#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "nvs.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_gap_bt_api.h"
#include "esp_bt_device.h"
#include "esp_spp_api.h"

#include "time.h"
#include "sys/time.h"

#define SPP_TAG "BT AP"
#define SPP_SERVER_NAME "LEDEqualizerServer"
#define EXCAMPLE_DEVICE_NAME "LEDEqualizer"
#define SPP_SHOW_DATA 1
#define SPP_SHOW_SPEED 1
#define SPP_SHOW_MODE SPP_SHOW_SPEED    /*Choose show mode: show data or speed*/

class BluetoothAP {

    /* Data fields */
    private:
        static const esp_spp_mode_t esp_spp_mode = ESP_SPP_MODE_CB;
        static const esp_spp_sec_t sec_mask = ESP_SPP_SEC_NONE;
        static const esp_spp_role_t role_slave = ESP_SPP_ROLE_SLAVE;

        struct timeval time_new, time_old;
        long data_num = 0;

    /* Methods */
    public:
        BluetoothAP() {};
        bool start();
        bool stop();

    private:
        void print_speed(void);
        static void esp_spp_cb(esp_spp_cb_event_t event, esp_spp_cb_param_t *param);
        static void esp_bt_gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param);
        
};