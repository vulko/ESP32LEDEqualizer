#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#include "WiFiAP.hpp"

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t s_wifi_event_group;

static const char *TAG = "WiFi";

static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {
    case SYSTEM_EVENT_AP_START:
        ESP_LOGI(TAG, "AP started");
        break;

    case SYSTEM_EVENT_AP_STOP:
        ESP_LOGI(TAG, "AP stopped");
        break;

    case SYSTEM_EVENT_STA_WPS_ER_SUCCESS:
        ESP_LOGI(TAG, "STA_WPS_ER_SUCCESS");
        break;
    case SYSTEM_EVENT_STA_WPS_ER_FAILED:
        ESP_LOGI(TAG, "STA_WPS_ER_FAILED");
        break;
    case SYSTEM_EVENT_STA_WPS_ER_TIMEOUT:
        ESP_LOGI(TAG, "STA_WPS_ER_TIMEOUT");
        break;
    case SYSTEM_EVENT_STA_WPS_ER_PIN:
        ESP_LOGI(TAG, "STA_WPS_ER_PIN");
        break;

    case SYSTEM_EVENT_AP_STACONNECTED:
        ESP_LOGI(TAG, "New connection, AID: %d", event->event_info.sta_connected.aid);
        break;

    case SYSTEM_EVENT_AP_STAIPASSIGNED:
        ESP_LOGI(TAG, "ip assigned: %d.%d.%d.%d", IP2STR(&event->event_info.got_ip.ip_info.ip));
        break;

    case SYSTEM_EVENT_AP_PROBEREQRECVED:
        ESP_LOGI(TAG, "AP PROBEREQRECVED, rssi: %d", event->event_info.ap_probereqrecved.rssi);
        break;

    case SYSTEM_EVENT_AP_STADISCONNECTED:
        ESP_LOGI(TAG, "Disconnected, AID: %d", event->event_info.sta_disconnected.aid);
        break;

    default:
        break;
    }
    return ESP_OK;
}

void wifi_init_softap(void)
{
    s_wifi_event_group = xEventGroupCreate();

    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    char ssid[32] = "LEDEqualizer";
    char pass[64] = "12345678";
    uint8_t ssidLen = strlen(ssid);
    uint8_t passLen = strlen(pass);
    uint8_t maxConn = 2;

    wifi_config_t wifi_config;
    memcpy(wifi_config.ap.ssid, ssid, 32);
    wifi_config.ap.ssid_len = ssidLen;
    wifi_config.ap.ssid_hidden = 0,
    memcpy(wifi_config.ap.password, pass, 64);
    wifi_config.ap.channel = 0;
    wifi_config.ap.max_connection = maxConn;
    wifi_config.ap.beacon_interval = 100;
    if (passLen == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    } else {
        wifi_config.ap.authmode = WIFI_AUTH_WPA_WPA2_PSK;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi_init_softap finished.SSID:%s password:%s", ssid, pass);
}

bool WiFiAp::start()
{
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    
    if (ret != ESP_OK) {
        return false;
    }
    
    ESP_LOGI(TAG, "ESP_WIFI_MODE_AP");
    wifi_init_softap();
    
    return true;
}