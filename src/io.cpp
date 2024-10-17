#include "io.h"       // Includes the HAIHeader and function declarations
#include "header.h"
#include <fstream>    // For file handling
#include <iostream>   // For error output
#include <vector>     // For std::vector
#include <cstdint>    // For fixed-width integer types

// Write the HAI file
void writeHAIFile(const std::string& filename, const HAIHeader& header,
                  const std::vector<uint8_t>& albedo, const std::vector<uint8_t>& shininess,
                  const std::vector<uint8_t>& reflection, const std::vector<uint8_t>& transparency,
                  const std::vector<uint8_t>& displacement) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    // Write the header
    outFile.write(reinterpret_cast<const char*>(&header), sizeof(HAIHeader));

    // Write the compressed image data
    outFile.write(reinterpret_cast<const char*>(albedo.data()), albedo.size());
    outFile.write(reinterpret_cast<const char*>(shininess.data()), shininess.size());
    outFile.write(reinterpret_cast<const char*>(reflection.data()), reflection.size());
    outFile.write(reinterpret_cast<const char*>(transparency.data()), transparency.size());
    outFile.write(reinterpret_cast<const char*>(displacement.data()), displacement.size());

    outFile.close();
}

// Read the HAI file
void readHAIFile(const std::string& filename, HAIHeader& header,
                 std::vector<uint8_t>& albedo, std::vector<uint8_t>& shininess,
                 std::vector<uint8_t>& reflection, std::vector<uint8_t>& transparency,
                 std::vector<uint8_t>& displacement) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
        return;
    }

    // Read the header
    inFile.read(reinterpret_cast<char*>(&header), sizeof(HAIHeader));

    // Resize vectors based on data sizes (calculated from header offsets)
    albedo.resize(header.shininessOffset - header.albedoOffset);
    inFile.read(reinterpret_cast<char*>(albedo.data()), albedo.size());

    shininess.resize(header.reflectionOffset - header.shininessOffset);
    inFile.read(reinterpret_cast<char*>(shininess.data()), shininess.size());

    reflection.resize(header.transparencyOffset - header.reflectionOffset);
    inFile.read(reinterpret_cast<char*>(reflection.data()), reflection.size());

    transparency.resize(header.displacementOffset - header.transparencyOffset);
    inFile.read(reinterpret_cast<char*>(transparency.data()), transparency.size());

    displacement.resize(static_cast<size_t>(inFile.tellg()) - header.displacementOffset);
    inFile.read(reinterpret_cast<char*>(displacement.data()), displacement.size());

    inFile.close();
}
