#pragma once
#include "../Arguments/Arguments.h"
#include "../Field/Field.h"
#include "../../utils/utils.h"
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>

const uint8_t count_of_colors = 5;
const uint8_t count_of_bit = 4;

struct Color {
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    uint8_t reversed = 0;
};

#pragma pack(push, 1)
struct BMPFileHeader{
    uint16_t file_type = 0x4D42;
    uint32_t file_size = 0;
    const uint32_t unused = 0;
    uint32_t offset_data = 0;
};

struct BMPInfoHeader {
    uint32_t size = sizeof(BMPInfoHeader);
    int32_t width = 0;
    int32_t height = 0;

    const uint16_t planes = 1;
    const uint16_t bit_count = count_of_bit;
    const uint32_t compression = 0;
    uint32_t size_image = 0;
    const uint32_t x_pixels_in_meter = 0;
    const uint32_t y_pixels_in_meter = 0;
    const uint32_t colors_used = count_of_colors;
    const uint32_t colors_important = 0;
};
#pragma pack(pop)


// bmp for 16 colors
struct BMP {
    BMPFileHeader file_header;
    BMPInfoHeader info_header;
    Color palette[count_of_colors];
    uint32_t count_of_padding_byte;

    BMP (uint32_t width, uint32_t height) {
        info_header.width = static_cast<int32_t>(width);
        info_header.height = static_cast<int32_t>(height);
        count_of_padding_byte = (4 - ((info_header.width + info_header.width % 2) / 2 % 4)) % 4;
        info_header.size_image = height * (count_of_padding_byte + width / 2 + width % 2);
        file_header.file_size = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + info_header.size_image;
        file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + count_of_colors * count_of_bit;
        InitPalette();
    }

    void InitPalette();

    void WriteFileHeader(std::ofstream& output);

    void WriteInfoHeader(std::ofstream& output);

    void WritePalette(std::ofstream& output);

    uint8_t DefineColor(uint64_t particles);

    void WriteImage(std::ofstream& output, Field* field);

    void Write(const char* dir, Field* field);
};

char* CreateFilename(const char* filename, uint64_t name);