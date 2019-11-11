#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "esp_timer.h"

#define AUDIO_BUFFER_SAMPLES 1024           // should produce 30Hz after FFT
#define AUDIO_CAPTURE_DELAY_MICROSEC 25     // 1 000 000 / 44 000;

static esp_adc_cal_characteristics_t *adc_chars;
static const adc1_channel_t channel = ADC1_CHANNEL_3;     // GPIO39
static const adc_atten_t atten = ADC_ATTEN_DB_0;

// TODO: fuck this ESP32! fucking pure C... can't fucking use class fields!!!!!
static uint32_t mAudioBuffer[AUDIO_BUFFER_SAMPLES];
static uint32_t mAudioFrame[AUDIO_BUFFER_SAMPLES];
static uint32_t mAudioBufferPos = 0;

class MicReader {
    private:
        esp_timer_handle_t mAudioCaptureTimer;

    public:
        MicReader() {};
        bool start();

    private:
        bool init();
        static void audioCaptureTimerCb(void* args);

};