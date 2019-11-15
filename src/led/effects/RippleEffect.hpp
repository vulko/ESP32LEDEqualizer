#ifndef RIPPLE_EFFECT_H_
#define RIPPLE_EFFECT_H_

#include "LedEffectBase.hpp"
#include <cstring>


class RippleEffect : public LedEffectBase {

public:
    RippleEffect(MatrixDimenType width, MatrixDimenType height) : LedEffectBase(width, height) {
        x = 0;
        y = 0;
        rippleSize = 0;
        rippleColor = 0;
    }
    virtual ~RippleEffect() override {}

    virtual void applyFrame(LedMatrix* ledMatrix) override {
        memset(ledMatrix->getData(), 0, ledMatrix->getSize() * sizeof(PixelData));
        for (x = (getWidth() - rippleSize) / 2; x < (getWidth() + rippleSize) / 2; ++x) {
            for (y = (getHeight() - rippleSize) / 2; y < (getHeight() + rippleSize) / 2; ++y) {
                ledMatrix->setPixelColor(x, y, rippleColor++, 0, 0);
            }
        }

        ++rippleSize;
        if (rippleSize > getWidth())
        {
            rippleSize = 0;
        }
        if (rippleColor > 100) {
            rippleColor = 0;
        }
    }

private:
    MatrixDimenType x = 0;
    MatrixDimenType y = 0;
    MatrixDimenType rippleSize = 0;
    ColorType rippleColor = 0;

};

#endif /* RIPPLE_EFFECT_H_ */