#include "Bmp.h"

char* CreateFilename(const char* dir, uint64_t num) {
    const uint8_t kNumLen = 20;
    char* filename = new char[strlen(dir) + kNumLen];
    filename[0] = '\0';
    char* name = new char[kNumLen + 1];
    for (size_t i = 0; i < kNumLen + 1; ++i) {
        name[i] = '\0';
    }
    std::to_chars(name, name + kNumLen, num, 10);
    strcat(filename, dir);
    strcat(filename, name);
    strcat(filename, ".bmp");
    delete[] name;
    return filename;
}

uint8_t DefineColor(uint64_t particle) {
    return particle >= 4 ? 4 : particle;
}

void BMP::WriteFileHeader(std::ofstream& output) {
    output.write(reinterpret_cast <const char*>(&file_header.file_type), sizeof(file_header.file_type));
    output.write(reinterpret_cast <const char*>(&file_header.file_size), sizeof(file_header.file_size));
    output.write(reinterpret_cast <const char*>(&file_header.unused), sizeof(file_header.unused));
    output.write(reinterpret_cast <const char*>(&file_header.offset_data), sizeof(file_header.offset_data));
}

void BMP::WriteInfoHeader(std::ofstream& output) {
    output.write(reinterpret_cast <const char*>(&info_header.size), sizeof(info_header.size));
    output.write(reinterpret_cast <const char*>(&info_header.width), sizeof(info_header.width));
    output.write(reinterpret_cast <const char*>(&info_header.height), sizeof(info_header.height));
    output.write(reinterpret_cast <const char*>(&info_header.planes), sizeof(info_header.planes));
    output.write(reinterpret_cast <const char*>(&info_header.bit_count), sizeof(info_header.bit_count));
    output.write(reinterpret_cast <const char*>(&info_header.compression), sizeof(info_header.compression));
    output.write(reinterpret_cast <const char*>(&info_header.size_image), sizeof(info_header.size_image));
    output.write(reinterpret_cast <const char*>(&info_header.x_pixels_in_meter), sizeof(info_header.x_pixels_in_meter));
    output.write(reinterpret_cast <const char*>(&info_header.y_pixels_in_meter), sizeof(info_header.y_pixels_in_meter));
    output.write(reinterpret_cast <const char*>(&info_header.colors_used), sizeof(info_header.colors_used));
    output.write(reinterpret_cast <const char*>(&info_header.colors_important), sizeof(info_header.colors_important));
}

void BMP::WriteColor(std::ofstream& output, Color color) {
    output.write(reinterpret_cast <const char*>(&color.blue), sizeof(color.blue));
    output.write(reinterpret_cast <const char*>(&color.green), sizeof(color.green));
    output.write(reinterpret_cast <const char*>(&color.red), sizeof(color.red));
    output.write(reinterpret_cast <const char*>(&color.reserved), sizeof(color.reserved));
}

void BMP::WritePalette(std::ofstream& output) {
    for (size_t i = 0; i < kCountOfColors; ++i) {
        WriteColor(output, palette[i]);
    }
}

void BMP::WriteLine(std::ofstream& output, Field& field, size_t i) {
    const uint8_t offset = 16;
    for (size_t j = 0; j < info_header.width - 1; j += 2) {
        uint8_t byte = DefineColor(field.sand_pile[i][j]) * offset + DefineColor(field.sand_pile[i][j + 1]);
        output.write(reinterpret_cast <const char*>(&byte), sizeof(uint8_t));
    }
    if (info_header.width % 2 == 1) {
        uint8_t byte = field.sand_pile[i][field.border_x - 1] * offset;
        output.write(reinterpret_cast <const char *>(&byte), sizeof(uint8_t));
    }
}

void BMP::WritePadding(std::ofstream& output) {
    for (size_t j = 0; j < count_of_padding_byte; ++j) {
        output.write(reinterpret_cast <const char *>(&padding), sizeof(uint8_t));
    }
}

void BMP::WriteImage(std::ofstream& output, Field& field) {
    for (size_t i = 0; i < info_header.height; ++i) {
        WriteLine(output, field, i);
        WritePadding(output);
    }
}

void BMP::Write(const char* dir, Field& field) {
    std::ofstream output(dir, std::ios_base::binary);
    WriteFileHeader(output);
    WriteInfoHeader(output);
    WritePalette(output);
    WriteImage(output, field);
}
