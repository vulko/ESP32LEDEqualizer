#include "MicReader.hpp"

static void check_efuse()
{
    //Check TP is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_TP) == ESP_OK) {
        printf("eFuse Two Point: Supported\n");
    } else {
        printf("eFuse Two Point: NOT supported\n");
    }

    //Check Vref is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_VREF) == ESP_OK) {
        printf("eFuse Vref: Supported\n");
    } else {
        printf("eFuse Vref: NOT supported\n");
    }
}

static void print_char_val_type(esp_adc_cal_value_t val_type)
{
    if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP) {
        printf("Characterized using Two Point Value\n");
    } else if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
        printf("Characterized using eFuse Vref\n");
    } else {
        printf("Characterized using Default Vref\n");
    }
}

bool MicReader::start() {
    int retVal = 0;

    esp_timer_create_args_t timer_args;
    timer_args.arg = nullptr;
    timer_args.name = "AudioCaptureTimer";
    timer_args.callback = &audioCaptureTimerCb;
    timer_args.dispatch_method = ESP_TIMER_TASK;

    retVal += init();
    retVal += esp_timer_create(&timer_args, &mAudioCaptureTimer);
    retVal += esp_timer_start_periodic(mAudioCaptureTimer, AUDIO_CAPTURE_DELAY_MICROSEC);

    return retVal == ESP_OK;
}

bool MicReader::init() {
    int retVal = 0;

    // Check if Two Point or Vref are burned into eFuse
    check_efuse();

    // Configure ADC
        adc1_config_width(ADC_WIDTH_BIT_12);
        adc1_config_channel_atten(channel, atten);

    // Characterize ADC
    adc_chars = (esp_adc_cal_characteristics_t*) calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT_1, atten, ADC_WIDTH_BIT_12, 1100, adc_chars);
    print_char_val_type(val_type);

    return retVal == ESP_OK;
}

void MicReader::audioCaptureTimerCb(void *arg) {
    uint32_t adcValue = 0;
    adcValue = adc1_get_raw((adc1_channel_t) channel);

    // add new value to buffer
    mAudioBuffer[mAudioBufferPos++] =  adcValue;

    if (mAudioBufferPos == AUDIO_BUFFER_SAMPLES) {
        // one frame is ready
        mAudioBufferPos = 0;
        memcpy(mAudioFrame, mAudioBuffer, AUDIO_BUFFER_SAMPLES);
        printf("Frame ready! ADC val = %d\n", adcValue);
    }
}