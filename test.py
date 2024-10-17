import struct
import random

# Function to generate a BMP file
def generate_bmp(filename, width, height, color_func):
    # BMP header fields
    file_size = 54 + width * height * 3  # 54 bytes header + pixel data
    reserved = 0
    data_offset = 54
    header_size = 40
    planes = 1
    bits_per_pixel = 24
    compression = 0
    image_size = width * height * 3
    x_pixels_per_meter = 2835
    y_pixels_per_meter = 2835
    total_colors = 0
    important_colors = 0

    # BMP file header
    bmp_header = struct.pack('<2sIHHI', b'BM', file_size, reserved, reserved, data_offset)

    # DIB header (BITMAPINFOHEADER)
    dib_header = struct.pack('<IIIHHIIIIII',
                             header_size, width, height, planes, bits_per_pixel, compression, image_size,
                             x_pixels_per_meter, y_pixels_per_meter, total_colors, important_colors)

    # Generate pixel data
    pixel_data = bytearray()
    for y in range(height):
        for x in range(width):
            r, g, b = color_func(x, y, width, height)
            pixel_data.extend([b, g, r])  # BMP stores color as BGR

    # Write to BMP file
    with open(filename, 'wb') as f:
        f.write(bmp_header)
        f.write(dib_header)
        f.write(pixel_data)

# Different color functions for each image type
def albedo_color(x, y, width, height):
    return 255, 0, 0  # Red for Albedo

def shininess_color(x, y, width, height):
    return 128, 128, 128  # Gray for Shininess

def reflection_color(x, y, width, height):
    return 0, 0, 255  # Blue for Reflection

def transparency_color(x, y, width, height):
    return 0, 255, 0  # Green for Transparency

def displacement_color(x, y, width, height):
    return random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)  # Random noise for Displacement

# Generate example BMPs
if __name__ == "__main__":
    width = 256
    height = 256

    # Generate each BMP with a different color pattern
    generate_bmp('albedo.bmp', width, height, albedo_color)
    print("Generated albedo.bmp")
    
    generate_bmp('shininess.bmp', width, height, shininess_color)
    print("Generated shininess.bmp")
    
    generate_bmp('reflection.bmp', width, height, reflection_color)
    print("Generated reflection.bmp")
    
    generate_bmp('transparency.bmp', width, height, transparency_color)
    print("Generated transparency.bmp")
    
    generate_bmp('displacement.bmp', width, height, displacement_color)
    print("Generated displacement.bmp")
