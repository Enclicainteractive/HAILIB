#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <cstdint>

struct Image {
    uint16_t width;
    uint16_t height;
    std::vector<uint8_t> data; // Pixel data (RGB)
};

// Resizes an image to a new width and height (nearest-neighbor interpolation)
Image resizeImage(const Image& src, uint16_t newWidth, uint16_t newHeight);

#endif // IMAGE_H
