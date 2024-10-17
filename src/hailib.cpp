#include "hailib.h"
#include <algorithm>

void HAILIB::writeHAI(const std::string& filename, const Image& albedo, const Image& shininess,
                      const Image& reflection, const Image& transparency, const Image& displacement) {
    // Create header with smallest dimensions
    HAIHeader header;
    header.format[0] = 'H';
    header.format[1] = 'A';
    header.format[2] = 'I';
    header.width = albedo.width;
    header.height = albedo.height;
    header.channels = 3;

    // Calculate offsets (compressed data sizes)
    header.albedoOffset = sizeof(HAIHeader);
    header.shininessOffset = header.albedoOffset + compressData(albedo.data).size();
    header.reflectionOffset = header.shininessOffset + compressData(shininess.data).size();
    header.transparencyOffset = header.reflectionOffset + compressData(reflection.data).size();
    header.displacementOffset = header.transparencyOffset + compressData(transparency.data).size();

    // Write the HAI file
    writeHAIFile(filename, header, compressData(albedo.data), compressData(shininess.data),
                 compressData(reflection.data), compressData(transparency.data), compressData(displacement.data));
}

void HAILIB::readHAI(const std::string& filename, Image& albedo, Image& shininess,
                     Image& reflection, Image& transparency, Image& displacement) {
    HAIHeader header;
    std::vector<uint8_t> albedoCompressed, shininessCompressed, reflectionCompressed, transparencyCompressed, displacementCompressed;

    // Read the HAI file
    readHAIFile(filename, header, albedoCompressed, shininessCompressed, reflectionCompressed,
                transparencyCompressed, displacementCompressed);

    // Decompress the image data
    albedo.width = shininess.width = reflection.width = transparency.width = displacement.width = header.width;
    albedo.height = shininess.height = reflection.height = transparency.height = displacement.height = header.height;

    albedo.data = decompressData(albedoCompressed);
    shininess.data = decompressData(shininessCompressed);
    reflection.data = decompressData(reflectionCompressed);
    transparency.data = decompressData(transparencyCompressed);
    displacement.data = decompressData(displacementCompressed);
}

void HAILIB::handleDifferentSizes(Image& albedo, Image& shininess, Image& reflection,
                                  Image& transparency, Image& displacement) {
    uint16_t minWidth = std::min({albedo.width, shininess.width, reflection.width, transparency.width, displacement.width});
    uint16_t minHeight = std::min({albedo.height, shininess.height, reflection.height, transparency.height, displacement.height});

    albedo = resizeImage(albedo, minWidth, minHeight);
    shininess = resizeImage(shininess, minWidth, minHeight);
    reflection = resizeImage(reflection, minWidth, minHeight);
    transparency = resizeImage(transparency, minWidth, minHeight);
    displacement = resizeImage(displacement, minWidth, minHeight);
}
