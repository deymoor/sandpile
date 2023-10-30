#pragma once
#include "../Arguments/Arguments.h"
#include "../Field/Field.h"
#include "../../utils/utils.h"
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <charconv>

const uint8_t kCountOfColors = 5;
const uint8_t kCountOfBits = 4;
const uint8_t padding = 0x0;

#pragma pack(push, 1)
struct Color {
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    uint8_t reserved = 0;

    Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) {
        red = r;
        green = g;
        blue = b;
    }
};

struct Colors {
    const Color rgb_white{255, 255, 255};
    const Color rgb_green{0, 255, 0};
    const Color rgb_yellow{255, 255, 0};
    const Color rgb_purple{128, 0, 128};
    const Color rgb_black{0, 0, 0};
};

struct BMPFileHeader{
    uint16_t file_type = 0x4D42;
    uint32_t file_size = 0;
    uint32_t unused = 0;
    uint32_t offset_data = 0;
};

struct BMPInfoHeader {
    uint32_t size = sizeof(BMPInfoHeader);
    int32_t width = 0;
    int32_t height = 0;

    uint16_t planes = 1;
    uint16_t bit_count = kCountOfBits;
    uint32_t compression = 0;
    uint32_t size_image = 0;
    uint32_t x_pixels_in_meter = 0;
    uint32_t y_pixels_in_meter = 0;
    uint32_t colors_used = kCountOfColors;
    uint32_t colors_important = 0;
};
#pragma pack(pop)


// bmp for 16 colors
struct BMP {
    BMPFileHeader file_header;
    BMPInfoHeader info_header;
    Color palette[kCountOfColors];
    uint32_t count_of_padding_byte;

    BMP (uint32_t width, uint32_t height) {
        info_header.width = static_cast<int32_t>(width);
        info_header.height = static_cast<int32_t>(height);
        count_of_padding_byte = (4 - ((info_header.width + info_header.width % 2) / 2 % 4)) % 4;
        info_header.size_image = height * (count_of_padding_byte + width / 2 + width % 2);
        file_header.file_size = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + info_header.size_image;
        file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + kCountOfColors * kCountOfBits;

        Colors colors;
        palette[0] = colors.rgb_white;
        palette[1] = colors.rgb_green;
        palette[2] = colors.rgb_yellow;
        palette[3] = colors.rgb_purple;
        palette[4] = colors.rgb_black;
    }

    void WriteFileHeader(std::ofstream& output);

    void WriteInfoHeader(std::ofstream& output);

    void WriteColor(std::ofstream& output, Color color);

    void WritePalette(std::ofstream& output);

    void WriteLine(std::ofstream& output, Field& field, size_t i);

    void WritePadding(std::ofstream& output);

    void WriteImage(std::ofstream& output, Field& field);

    void Write(const char* dir, Field& field);
};

char* CreateFilename(const char* dir, uint64_t name);

uint8_t DefineColor(uint64_t particle);