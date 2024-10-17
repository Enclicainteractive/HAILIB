cmake_minimum_required(VERSION 3.10)
project(HAILIB)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Define the source files for the HAILIB library
set(SOURCES
    src/hailib.cpp
    src/image.cpp
    src/compress.cpp
    src/io.cpp
)

# Add the HAILIB library
add_library(hailib ${SOURCES})

# Example programs
# BMPtoHAI example: Converts BMP files to HAI format
add_executable(BMPtoHAI examples/BMPtoHAI.cpp)
target_link_libraries(BMPtoHAI hailib)

# HAItoBMP example: Converts HAI files to BMP format
add_executable(HAItoBMP examples/HAItoBMP.cpp)
target_link_libraries(HAItoBMP hailib)
