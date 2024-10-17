#include "image.h"

// Resizes an image using nearest-neighbor interpolation
Image resizeImage(const Image& src, uint16_t newWidth, uint16_t newHeight) {
    Image resized;
    resized.width = newWidth;
    resized.height = newHeight;
    resized.data.resize(newWidth * newHeight * 3);

    float xRatio = static_cast<float>(src.width) / newWidth;
    float yRatio = static_cast<float>(src.height) / newHeight;

    for (uint16_t y = 0; y < newHeight; ++y) {
        for (uint16_t x = 0; x < newWidth; ++x) {
            uint16_t srcX = static_cast<uint16_t>(x * xRatio);
            uint16_t srcY = static_cast<uint16_t>(y * yRatio);

            for (int c = 0; c < 3; ++c) {
                resized.data[(y * newWidth + x) * 3 + c] = src.data[(srcY * src.width + srcX) * 3 + c];
            }
        }
    }

    return resized;
}
