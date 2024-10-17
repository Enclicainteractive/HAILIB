#include "hailib.h"
#include <iostream>
#include <fstream>

// Helper function to read a BMP file
Image readBMP(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open BMP file: " + filename);
    }

    // Read BMP header
    file.seekg(18); // Width and height start at byte 18
    int32_t width = 0;
    int32_t height = 0;
    file.read(reinterpret_cast<char*>(&width), 4);
    file.read(reinterpret_cast<char*>(&height), 4);

    // BMP data starts at byte 54
    file.seekg(54);
    std::vector<uint8_t> data(width * height * 3);
    file.read(reinterpret_cast<char*>(data.data()), data.size());
    
    return {static_cast<uint16_t>(width), static_cast<uint16_t>(height), data};
}

int main() {
    try {
        // Read the BMP files
        Image albedo = readBMP("albedo.bmp");
        Image shininess = readBMP("shininess.bmp");
        Image reflection = readBMP("reflection.bmp");
        Image transparency = readBMP("transparency.bmp");
        Image displacement = readBMP("displacement.bmp");

        // Handle different image sizes
        HAILIB::handleDifferentSizes(albedo, shininess, reflection, transparency, displacement);

        // Write to HAI file
        std::string haiFile = "output_image.hai";
        HAILIB::writeHAI(haiFile, albedo, shininess, reflection, transparency, displacement);
        std::cout << "BMP files successfully converted to HAI format: " << haiFile << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
