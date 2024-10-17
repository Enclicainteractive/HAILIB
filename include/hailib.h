#ifndef HAILIB_H
#define HAILIB_H

#include "image.h"
#include "compress.h"
#include "io.h"

// HAILIB interface that links all components together
class HAILIB {
public:
    // Writes a HAI file
    static void writeHAI(const std::string& filename, const Image& albedo, const Image& shininess,
                         const Image& reflection, const Image& transparency, const Image& displacement);

    // Reads a HAI file
    static void readHAI(const std::string& filename, Image& albedo, Image& shininess,
                        Image& reflection, Image& transparency, Image& displacement);

    // Handles different image sizes by resizing them to the smallest image
    static void handleDifferentSizes(Image& albedo, Image& shininess, Image& reflection, 
                                     Image& transparency, Image& displacement);
};

#endif // HAILIB_H
