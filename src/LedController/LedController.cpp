#include "LedController.hpp"
#include <string.h>
#include <esp_log.h>


LedController::LedController()
    : pLedMatrix(new LedMatrix()) {
    // initialize
    mLogicZero.level0 = 1;
    mLogicZero.duration0 = 32;
    mLogicZero.level1 = 0;
    mLogicZero.duration1 = 68;

    mLogicOne.level0 = 1;
    mLogicOne.duration0 = 64;
    mLogicOne.level1 = 0;
    mLogicOne.duration1 = 36;

    // setup RMT driver
    rmt_config_t rmt_tx;
	memset(&rmt_tx, 0, sizeof(rmt_config_t));

	rmt_tx.channel = mChannel;
	rmt_tx.gpio_num = GPIO_NUM_5;
	rmt_tx.mem_block_num = 1;
	rmt_tx.clk_div = 1;
	rmt_tx.tx_config.idle_output_en = 1;

	rmt_config(&rmt_tx);
	rmt_driver_install(rmt_tx.channel, 0, 0);

    // init raw led data
    if (NULL == (pRawData = (rmt_item32_t*) malloc(sizeof(rmt_item32_t) * pLedMatrix->getSize() * 24)))
	{
		ESP_LOGE(LED_CONTROLLER_TAG, "%s: %d Unable to allocate space!\n", __FILE__, __LINE__);
		return;
	}
}

LedController::~LedController() {
    rmt_driver_uninstall(mChannel);
	free(pRawData);
    delete pLedMatrix;
}

void LedController::setPixelColor(MatrixDimenType xPos, MatrixDimenType yPos, ColorType red, ColorType green, ColorType blue) {
    pLedMatrix->setPixelColor(xPos, yPos, red, green, blue);
}

void LedController::update() {
    unsigned int itemCnt = 0;
	unsigned int dataSize = pLedMatrix->getSize();
    PixelData* data = pLedMatrix->getData();

	for(int i = 0; i < dataSize; i++) {
		for(int j = 0; j < 24; j++) {
			if(j < 8) {
				if(data[i].mGreen & (1<<(7-j))) pRawData[itemCnt++] = mLogicOne;
				else pRawData[itemCnt++] = mLogicZero;
			} else if (j < 16) {
				if(data[i].mRed & (1<<(7 - (j%8) ))) pRawData[itemCnt++] = mLogicOne;
				else pRawData[itemCnt++] = mLogicZero;
			} else {
				if(data[i].mBlue & (1<<( 7 - (j%8) ))) pRawData[itemCnt++] = mLogicOne;
				else pRawData[itemCnt++] = mLogicZero;
			}
		}
	}

	rmt_write_items(mChannel, pRawData, pLedMatrix->getSize() * 24, false);
}