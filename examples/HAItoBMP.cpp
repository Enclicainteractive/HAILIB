#include "hailib.h"
#include <iostream>
#include <fstream>
#include <cstring>  // Include this for std::memcpy

// Helper function to write a BMP file
void writeBMP(const std::string& filename, const Image& image) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open BMP file for writing: " + filename);
    }

    // BMP file header (14 bytes)
    uint8_t bmpFileHeader[14] = {
        'B', 'M', // Signature
        0, 0, 0, 0, // Image file size in bytes (filled later)
        0, 0, 0, 0, // Reserved
        54, 0, 0, 0 // Start position of pixel data (54 bytes)
    };

    // BMP info header (40 bytes)
    uint8_t bmpInfoHeader[40] = {
        40, 0, 0, 0, // Header size
        0, 0, 0, 0, // Image width (filled later)
        0, 0, 0, 0, // Image height (filled later)
        1, 0,       // Number of color planes
        24, 0,      // Bits per pixel
        0, 0, 0, 0, // No compression
        0, 0, 0, 0, // Image size (can be 0 for uncompressed)
        0, 0, 0, 0, // Horizontal resolution (pixels per meter)
        0, 0, 0, 0, // Vertical resolution (pixels per meter)
        0, 0, 0, 0, // Number of colors in palette
        0, 0, 0, 0  // Important colors
    };

    int32_t width = image.width;
    int32_t height = image.height;
    int imageSize = width * height * 3;

    // Fill in file size and dimensions using memcpy
    std::memcpy(&bmpFileHeader[2], &imageSize, 4);
    std::memcpy(&bmpInfoHeader[4], &width, 4);
    std::memcpy(&bmpInfoHeader[8], &height, 4);

    // Write the headers
    file.write(reinterpret_cast<const char*>(bmpFileHeader), sizeof(bmpFileHeader));
    file.write(reinterpret_cast<const char*>(bmpInfoHeader), sizeof(bmpInfoHeader));

    // Write the pixel data (BMP format is BGR)
    file.write(reinterpret_cast<const char*>(image.data.data()), imageSize);

    file.close();
}

int main() {
    try {
        // Read the HAI file
        Image albedo, shininess, reflection, transparency, displacement;
        std::string haiFile = "output_image.hai";
        HAILIB::readHAI(haiFile, albedo, shininess, reflection, transparency, displacement);

        // Write the BMP files
        writeBMP("output_albedo.bmp", albedo);
        writeBMP("output_shininess.bmp", shininess);
        writeBMP("output_reflection.bmp", reflection);
        writeBMP("output_transparency.bmp", transparency);
        writeBMP("output_displacement.bmp", displacement);

        std::cout << "HAI file successfully converted back to BMP files." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
