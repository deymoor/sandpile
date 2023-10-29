#include "Bmp.h"

char* CreateFilename(const char* filename, uint64_t num){
    char* name = ConvertToBMPName(num);
    uint32_t size_filename = strlen(filename);
    uint32_t size_name = strlen(name);
    char* new_filename = new char[size_filename + size_name + 1];
    for (size_t i = 0; i < size_filename; ++i) {
        new_filename[i] = filename[i];
    }
    for (size_t i = size_filename; i < size_filename + size_name; ++i) {
        new_filename[i] = name[i - size_filename];
    }
    new_filename[size_filename + size_name] = '\0';
    return new_filename;
}

void BMP::InitPalette() {
    Color rgb;
    // white
    rgb.red = 255;
    rgb.green = 255;
    rgb.blue = 255;
    palette[0] = rgb;
    // green
    rgb.red = 0;
    rgb.green = 255;
    rgb.blue = 0;
    palette[1] = rgb;
    // yellow
    rgb.red = 255;
    rgb.green = 255;
    rgb.blue = 0;
    palette[2] = rgb;
    // purple
    rgb.red = 128;
    rgb.green = 0;
    rgb.blue = 128;
    palette[3] = rgb;
    // black
    rgb.red = 0;
    rgb.green = 0;
    rgb.blue = 0;
    palette[4] = rgb;
}

void BMP::WriteFileHeader(std::ofstream& output) {
    output.write(reinterpret_cast <const char*>(&this->file_header.file_type), sizeof(this->file_header.file_type));
    output.write(reinterpret_cast <const char*>(&this->file_header.file_size), sizeof(this->file_header.file_size));
    output.write(reinterpret_cast <const char*>(&this->file_header.unused), sizeof(this->file_header.unused));
    output.write(reinterpret_cast <const char*>(&this->file_header.offset_data), sizeof(this->file_header.offset_data));
}

void BMP::WriteInfoHeader(std::ofstream& output) {
    output.write(reinterpret_cast <const char*>(&this->info_header.size), sizeof(this->info_header.size));
    output.write(reinterpret_cast <const char*>(&this->info_header.width), sizeof(this->info_header.width));
    output.write(reinterpret_cast <const char*>(&this->info_header.height), sizeof(this->info_header.height));
    output.write(reinterpret_cast <const char*>(&this->info_header.planes), sizeof(this->info_header.planes));
    output.write(reinterpret_cast <const char*>(&this->info_header.bit_count), sizeof(this->info_header.bit_count));
    output.write(reinterpret_cast <const char*>(&this->info_header.compression), sizeof(this->info_header.compression));
    output.write(reinterpret_cast <const char*>(&this->info_header.size_image), sizeof(this->info_header.size_image));
    output.write(reinterpret_cast <const char*>(&this->info_header.x_pixels_in_meter), sizeof(this->info_header.x_pixels_in_meter));
    output.write(reinterpret_cast <const char*>(&this->info_header.y_pixels_in_meter), sizeof(this->info_header.y_pixels_in_meter));
    output.write(reinterpret_cast <const char*>(&this->info_header.colors_used), sizeof(this->info_header.colors_used));
    output.write(reinterpret_cast <const char*>(&this->info_header.colors_important), sizeof(this->info_header.colors_important));
}

void BMP::WritePalette(std::ofstream& output) {
    for (size_t i = 0; i < count_of_colors; ++i) {
        output.write(reinterpret_cast <const char*>(&this->palette[i].red), sizeof(this->palette[i].red));
        output.write(reinterpret_cast <const char*>(&this->palette[i].green), sizeof(this->palette[i].green));
        output.write(reinterpret_cast <const char*>(&this->palette[i].blue), sizeof(this->palette[i].blue));
        output.write(reinterpret_cast <const char*>(&this->palette[i].reversed), sizeof(this->palette[i].reversed));
    }
}


uint8_t BMP::DefineColor(uint64_t particles) {
    switch (particles) {
        case 0: return 0;
        case 1: return 1;
        case 2: return 2;
        case 3: return 3;
        default : return 4;
    }
}

void BMP::WriteImage(std::ofstream& output, Field* field) {
    uint8_t padding = 0x0;
    for (size_t i = 0; i < this->info_header.height; ++i) {
        for (size_t j = 0; j < this->info_header.width - 1; j += 2) {
            uint8_t byte = DefineColor(field->sand_pile[i][j]) * 16 + DefineColor(field->sand_pile[i][j + 1]);
            output.write(reinterpret_cast <const char*>(&byte), sizeof(uint8_t));
        }
        if (this->info_header.width % 2 == 1) {
            uint8_t byte = field->sand_pile[i][field->border_x - 1] * 16;
            output.write(reinterpret_cast <const char *>(&byte), sizeof(uint8_t));
        }
        for (size_t j = 0; j < this->count_of_padding_byte; ++j) {
            output.write(reinterpret_cast <const char *>(&padding), sizeof(uint8_t));
        }
    }
}

void BMP::Write(const char* dir, Field* field) {
    std::ofstream output(dir, std::ios_base::binary);
    WriteFileHeader(output);
    WriteInfoHeader(output);
    WritePalette(output);
    WriteImage(output, field);
}
