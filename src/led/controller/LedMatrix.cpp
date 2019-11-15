#include "LedMatrix.hpp"
    

LedMatrix::LedMatrix(MatrixDimenType width, MatrixDimenType height)
    : mWidth(width)
    , mHeight(height)
    , mSize(width * height)
{
    pData = new PixelData[mSize];
}
    
LedMatrix::~LedMatrix()
{
    delete[] pData;
}

void LedMatrix::setPixelColor(MatrixDimenType xPos, MatrixDimenType yPos, ColorType red, ColorType green, ColorType blue) {
    if (yPos == 0 || yPos % 2 == 0) {
        // even row
        mPixelPos = yPos * mWidth + xPos;
    } else {
        // odd row
        mPixelPos = yPos * mWidth + mWidth - xPos - 1;
    }
    pData[mPixelPos].mRed = red;
    pData[mPixelPos].mGreen = green;
    pData[mPixelPos].mBlue = blue;
}