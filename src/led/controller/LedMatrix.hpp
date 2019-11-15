#ifndef LED_MATRIX_H_
#define LED_MATRIX_H_

#include <stdint.h>

typedef uint8_t MatrixDimenType;
typedef uint8_t ColorType;
typedef uint16_t MatrixSizeType;

#pragma pack(push, 1)
typedef struct {
	ColorType mGreen;
	ColorType mBlue;
	ColorType mRed;
} PixelData;
#pragma pack(pop)


class LedMatrix {

public:
    LedMatrix(MatrixDimenType width = 16, MatrixDimenType height = 16);
    ~LedMatrix();

    inline PixelData* getData() { return pData; }
    inline MatrixDimenType getWidth() { return mWidth; }
    inline MatrixDimenType getHeight() { return mHeight; }
    inline MatrixSizeType getSize() { return mSize; }

    void setPixelColor(MatrixDimenType xPos, MatrixDimenType yPos, ColorType red, ColorType green, ColorType blue);

private:
    PixelData* pData;
    MatrixDimenType mWidth;
    MatrixDimenType mHeight;
    MatrixSizeType mSize;
    MatrixSizeType mPixelPos;


};

#endif /* LED_MATRIX_H_ */