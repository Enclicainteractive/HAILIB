#include "compress.h"

std::vector<uint8_t> compressData(const std::vector<uint8_t>& data) {
    std::vector<uint8_t> compressed;
    size_t size = data.size();

    for (size_t i = 0; i < size; ++i) {
        uint8_t count = 1;
        while (i + 1 < size && data[i] == data[i + 1] && count < 255) {
            ++i;
            ++count;
        }
        compressed.push_back(data[i]);
        compressed.push_back(count);
    }

    return compressed;
}

std::vector<uint8_t> decompressData(const std::vector<uint8_t>& compressedData) {
    std::vector<uint8_t> decompressed;

    for (size_t i = 0; i < compressedData.size(); i += 2) {
        uint8_t value = compressedData[i];
        uint8_t count = compressedData[i + 1];
        decompressed.insert(decompressed.end(), count, value);
    }

    return decompressed;
}
