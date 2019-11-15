#include "LedController.hpp"
#include <led/effects/MatrixTestEffect.hpp>
#include <led/effects/RippleEffect.hpp>
#include <string.h>
#include <esp_log.h>


LedController::LedController()
    : pLedMatrix(new LedMatrix())
	, pLedDriver(new WS2812bDriver(pLedMatrix->getSize()))
	, pLedEffectBase(new RippleEffect(pLedMatrix->getWidth(), pLedMatrix->getHeight())) {
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
	delete pLedDriver;
}

void LedController::repaint() {
	pLedEffectBase->applyFrame(pLedMatrix);
	pLedDriver->convertToHWFormat(pLedMatrix->getData(), pRawData);
	rmt_write_items(mChannel, pRawData, pLedMatrix->getSize() * 24, false);
}