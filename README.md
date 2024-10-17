
# HAI (Helix Adaptive Image) File Format Specification

The **Helix Adaptive Image (HAI)** format is designed to store multiple types of image maps (Albedo, Shininess, Reflection, Transparency, and Displacement) in a single file. This format allows for efficient storage of multiple image channels that can be used in 3D rendering engines or other applications where these types of image maps are required.

## Features
- **Multi-channel Image Storage**: Stores up to five different image maps (Albedo, Shininess, Reflection, Transparency, and Displacement).
- **Efficient Data Storage**: Compresses image data using Run-Length Encoding (RLE) or similar methods (optional).
- **Custom Image Dimensions**: Handles different image sizes, ensuring compatibility with various image resolutions.

## File Format Overview

A HAI file consists of a **25-byte header** followed by compressed or uncompressed **image data** for each of the five image maps. The order and structure of the file is as follows:

### 1. **File Header (25 bytes)**
The header provides metadata about the image dimensions, number of channels, and the offsets to the actual image data for each map.

| **Field**               | **Size**  | **Description**                                                         |
|-------------------------|-----------|-------------------------------------------------------------------------|
| `Signature`             | 3 bytes   | The file signature for HAI format. Always "HAI".                        |
| `Width`                 | 2 bytes   | The width of the images (smallest common width after resizing).          |
| `Height`                | 2 bytes   | The height of the images (smallest common height after resizing).        |
| `Channels`              | 1 byte    | The number of channels per image (e.g., 3 for RGB).                      |
| `Albedo Offset`         | 4 bytes   | Offset from the start of the file to the Albedo image data.              |
| `Shininess Offset`      | 4 bytes   | Offset from the start of the file to the Shininess image data.           |
| `Reflection Offset`     | 4 bytes   | Offset from the start of the file to the Reflection image data.          |
| `Transparency Offset`   | 4 bytes   | Offset from the start of the file to the Transparency image data.        |
| `Displacement Offset`   | 4 bytes   | Offset from the start of the file to the Displacement image data.        |

### 2. **Image Data**
After the header, the actual image data for each image map is stored in sequence. Each image map is stored using its own dedicated block of data, starting at the specified offsets in the header.

### Example Layout:

[ HAI HEADER (25 bytes) ]
| Field                | Description                                   | Size    |
|----------------------|-----------------------------------------------|---------|
| Signature            | "HAI" (3 bytes, ASCII)                        | 3 bytes |
| Width                | Image width                                   | 2 bytes |
| Height               | Image height                                  | 2 bytes |
| Channels             | Number of channels per image (RGB = 3)        | 1 byte  |
| Albedo Offset        | Offset to the Albedo image data               | 4 bytes |
| Shininess Offset     | Offset to the Shininess image data            | 4 bytes |
| Reflection Offset    | Offset to the Reflection image data           | 4 bytes |
| Transparency Offset  | Offset to the Transparency image data         | 4 bytes |
| Displacement Offset  | Offset to the Displacement image data         | 4 bytes |

[ COMPRESSED/UNCOMPRESSED IMAGE DATA ]
| Field                | Description                                   | Size          |
|----------------------|-----------------------------------------------|---------------|
| Albedo Data          | Albedo image data                             | Variable size |
| Shininess Data       | Shininess image data                          | Variable size |
| Reflection Data      | Reflection image data                         | Variable size |
| Transparency Data    | Transparency image data                       | Variable size |
| Displacement Data    | Displacement image data                       | Variable size |



### Compression (Optional)
If the images are compressed using **Run-Length Encoding (RLE)** or any other compression method, each map will contain its compressed data instead of raw RGB values. The compression algorithm is left up to the specific use case, but the format is flexible to handle both compressed and uncompressed data.

### Header Field Descriptions:
- **Signature**: This is a 3-byte ASCII value that will always be "HAI" to indicate that the file is using the Helix Adaptive Image format.
- **Width/Height**: These fields define the common resolution (width x height) of the images stored in the file.
- **Channels**: Specifies the number of color channels per pixel (3 for RGB).
- **Offsets**: Each image map (Albedo, Shininess, Reflection, Transparency, Displacement) has an offset value that points to the location of that image's data in the file.

### Notes on Offsets
Each offset is calculated from the beginning of the file. For example, if the Albedo offset is 54, this means the Albedo image data starts at byte 54 in the file. This allows flexibility in file organization and supports storing images in any order.

## About Enclica Interactive

This file format is part of an experimental project by **Enclica Interactive**, aimed at improving the storage and management of multi-channel images in 3D applications. The format is currently in development and is subject to change.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
