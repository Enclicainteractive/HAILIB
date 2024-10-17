#ifndef HEADER_H
#define HEADER_H

#include <cstdint>

struct HAIHeader {
    char format[3];        // 'HAI' for Helix Adaptive Image
    uint16_t width;        // Image width
    uint16_t height;       // Image height
    uint8_t channels;      // Number of channels (e.g., RGB)
    uint32_t albedoOffset;     // Offset for albedo data
    uint32_t shininessOffset;  // Offset for shininess data
    uint32_t reflectionOffset; // Offset for reflection data
    uint32_t transparencyOffset; // Offset for transparency data
    uint32_t displacementOffset; // Offset for displacement data
};

#endif // HEADER_H
