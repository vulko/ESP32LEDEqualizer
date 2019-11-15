#ifndef LED_EFFECT_BASE_H_
#define LED_EFFECT_BASE_H_

#include <led/controller/LedMatrix.hpp>


class LedEffectBase {

public:
    LedEffectBase(MatrixDimenType width, MatrixDimenType height) : mWidth(width), mHeight(height) {}
    virtual ~LedEffectBase() {}

    virtual void applyFrame(LedMatrix* ledMatrix) = 0;

protected:
    inline MatrixDimenType getWidth() { return mWidth; }
    inline MatrixDimenType getHeight() { return mHeight; }

private:
    const MatrixDimenType mWidth;
    const MatrixDimenType mHeight;

};

#endif /* LED_EFFECT_BASE_H_ */