#ifndef IO_H
#define IO_H

#include "header.h"  // Include the header definition
#include <string>
#include <vector>
#include <cstdint>

// Function declarations for reading and writing the HAI files
void writeHAIFile(const std::string& filename, const HAIHeader& header,
                  const std::vector<uint8_t>& albedo, const std::vector<uint8_t>& shininess,
                  const std::vector<uint8_t>& reflection, const std::vector<uint8_t>& transparency,
                  const std::vector<uint8_t>& displacement);

void readHAIFile(const std::string& filename, HAIHeader& header,
                 std::vector<uint8_t>& albedo, std::vector<uint8_t>& shininess,
                 std::vector<uint8_t>& reflection, std::vector<uint8_t>& transparency,
                 std::vector<uint8_t>& displacement);

#endif // IO_H
