#include "itersandpile.h"


void DefineExpSides(Field& field, Expansion& expansion) {
    for (size_t j = 0; j < field.border_x; ++j) {
        if (field.sand_pile[0][j] >= Field::collapse) {
            expansion.exp_up = 1;
            break;
        }
    }
    for (size_t j = 0; j < field.border_x; ++j) {
        if (field.sand_pile[field.border_y - 1][j] >= Field::collapse) {
            expansion.exp_down = 1;
            break;
        }
    }
    for (size_t i = 0; i < field.border_y; ++i) {
        if (field.sand_pile[i][0] >= Field::collapse) {
            expansion.exp_left = 1;
            break;
        }
    }
    for (size_t i = 0; i < field.border_y; ++i) {
        if (field.sand_pile[i][field.border_x - 1] >= Field::collapse) {
            expansion.exp_right = 1;
            break;
        }
    }
}


void FillStack(Field& field, Stack& stack, Expansion& expansion) {
    for (size_t i = 0; i < field.border_y; ++i) {
        for (size_t j = 0; j < field.border_x; ++j) {
            uint64_t cnt_sand = field.sand_pile[i][j];
            if (cnt_sand < Field::collapse) {
                continue;
            }
            Triple triple;
            triple.y = i + expansion.exp_up;
            triple.x = j + expansion.exp_left;
            triple.elem = cnt_sand;
            stack.PushBack(triple);
        }
    }
}

void Resize(Field& field, Expansion& expansion) {
    if (expansion.exp_left == 0 && expansion.exp_right == 0 && expansion.exp_up == 0 && expansion.exp_down == 0) {
        return;
    }
    uint16_t y_new_boarder = field.border_y + expansion.exp_down + expansion.exp_up;
    uint16_t x_new_boarder = field.border_x + expansion.exp_right + expansion.exp_left;
    auto temp_array = new uint64_t*[y_new_boarder];
    for (size_t i = 0; i < y_new_boarder; ++i) {
        temp_array[i] = new uint64_t[x_new_boarder] {0};
    }
    for (size_t i = 0; i < field.border_y; ++i) {
        for (size_t j = 0; j < field.border_x; ++j) {
            temp_array[i + expansion.exp_up][j + expansion.exp_left] = field.sand_pile[i][j];
        }
    }
    for (size_t i = 0; i < field.border_y; ++i) {
        delete[] field.sand_pile[i];
    }
    delete field.sand_pile;
    field.sand_pile = temp_array;
    field.border_y = y_new_boarder;
    field.border_x = x_new_boarder;
}

void ScatterSand(Field& field, Stack& stack) {
    while (stack.head != nullptr) {
        Triple triple = stack.PopBack();
        field.sand_pile[triple.y][triple.x] -= Field::collapse;
        field.sand_pile[triple.y + 1][triple.x] += 1;
        field.sand_pile[triple.y][triple.x + 1] += 1;
        field.sand_pile[triple.y - 1][triple.x] += 1;
        field.sand_pile[triple.y][triple.x - 1] += 1;
    }
}

void SaveBMP(Field& field, const char* dir, uint64_t name) {
    BMP bmp(field.border_x, field.border_y);
    char* filename = CreateFilename(dir, name);
    bmp.Write(filename, field);
    delete[] filename;
}

void IterSandPile(Field& field, Arguments& arguments) {
    uint64_t temp_limit = arguments.limit;
    uint64_t temp_freq = arguments.freq;
    uint64_t bmp_filename = 1;
    while (temp_limit) {
        Expansion expansion;
        Stack stack;
        DefineExpSides(field, expansion);
        FillStack(field, stack, expansion);
        if (stack.IsEmpty()) {
            break;
        }
        Resize(field, expansion);
        ScatterSand(field, stack);
        if (temp_freq == arguments.freq && arguments.freq != 0) {
            SaveBMP(field, arguments.dir, bmp_filename);
            temp_freq = 0;
        }
        temp_limit--;
        temp_freq++;
        bmp_filename++;
    }
    if (arguments.freq == 0 && arguments.limit != 0) {
        SaveBMP(field, arguments.dir, bmp_filename);
    }
}