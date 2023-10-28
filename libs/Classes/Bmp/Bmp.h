#pragma once
#include "../Arguments/Arguments.h"
#include "../Field/Field.h"
#include "../../utils.h"
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>

const uint8_t count_of_colors = 16;

struct Color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t reversed;
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
    const uint16_t bit_count = 4;
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
    Color palette[16];

    BMP(int16_t width, int16_t height) {
        this->file_header.file_size = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + width * height;
        this->file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + count_of_colors * this->info_header.bit_count;
        this->info_header.width = width;
        this->info_header.height = height;
        this->info_header.size_image = height * width + height * (width / 2 + width % 2);
    }

    void WriteFileHeader(std::ofstream& output);

    void WriteInfoHeader(std::ofstream& output);

    void WritePalette(std::ofstream& output);

    uint8_t DefineColor(uint64_t particles);

    void WriteImage(std::ofstream& ofstream, Field* field);

    void Write(const char* dir, Field* field);
};

char* CreateFilename(const char* filename, uint64_t name);

void InitPalette(Color palette[count_of_colors]);