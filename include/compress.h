#ifndef COMPRESS_H
#define COMPRESS_H

#include <vector>
#include <cstdint>

// Compresses image data using Run-Length Encoding (RLE)
std::vector<uint8_t> compressData(const std::vector<uint8_t>& data);

// Decompresses image data using Run-Length Encoding (RLE)
std::vector<uint8_t> decompressData(const std::vector<uint8_t>& compressedData);

#endif // COMPRESS_H
