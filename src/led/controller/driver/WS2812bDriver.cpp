#include "WS2812bDriver.hpp"


WS2812bDriver::WS2812bDriver(MatrixSizeType dataSize)
    : mDataSize(dataSize) {
    // initialize
    mLogicZero.level0 = 1;
    mLogicZero.duration0 = 32;
    mLogicZero.level1 = 0;
    mLogicZero.duration1 = 68;

    mLogicOne.level0 = 1;
    mLogicOne.duration0 = 64;
    mLogicOne.level1 = 0;
    mLogicOne.duration1 = 36;    
}

void WS2812bDriver::convertToHWFormat(PixelData* pixelData, rmt_item32_t* rawData) {
    MatrixSizeType itemCnt = 0;
    MatrixSizeType pixelPos;
    MatrixDimenType bitPos;
    for (pixelPos = 0; pixelPos < mDataSize; ++pixelPos) {
		for (bitPos = 0; bitPos < 24; ++bitPos) {
			if (bitPos < 8) {
				if ( pixelData[pixelPos].mGreen & ( 1 << (7-bitPos) ) ) {
                    rawData[itemCnt++] = mLogicOne;
                } else {
                    rawData[itemCnt++] = mLogicZero;
                }
			} else if (bitPos < 16) {
				if ( pixelData[pixelPos].mRed & ( 1<< (7 - (bitPos%8)) ) ) {
                    rawData[itemCnt++] = mLogicOne;
                } else {
                    rawData[itemCnt++] = mLogicZero;
                }
			} else {
				if ( pixelData[pixelPos].mBlue & ( 1 << (7 - (bitPos%8)) ) ) {
                    rawData[itemCnt++] = mLogicOne;
                } else {
                    rawData[itemCnt++] = mLogicZero;
                }
			}
		}
	}
}