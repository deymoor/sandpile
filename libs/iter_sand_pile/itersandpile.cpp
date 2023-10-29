#include "itersandpile.h"


void DefineExpSides(Field* field, Expansion& expansion) {
    for (size_t j = 0; j < field->border_x; ++j) {
        if (field->sand_pile[0][j] >= 4) {
            expansion.exp_up = 1;
            break;
        }
    }
    for (size_t j = 0; j < field->border_x; ++j) {
        if (field->sand_pile[field->border_y - 1][j] >= 4) {
            expansion.exp_down = 1;
            break;
        }
    }
    for (size_t i = 0; i < field->border_y; ++i) {
        if (field->sand_pile[i][0] >= 4) {
            expansion.exp_left = 1;
            break;
        }
    }
    for (size_t i = 0; i < field->border_y; ++i) {
        if (field->sand_pile[i][field->border_x - 1] >= 4) {
            expansion.exp_right = 1;
            break;
        }
    }
}


void FillStack(Field* field, Stack* stack, Expansion& expansion) {
    for (size_t i = 0; i < field->border_y; ++i) {
        for (size_t j = 0; j < field->border_x; ++j) {
            uint64_t cnt_sand = field->sand_pile[i][j];
            if (cnt_sand < 4) {
                continue;
            }
            auto triple = new Triple();
            triple->y = i + expansion.exp_up;
            triple->x = j + expansion.exp_left;
            triple->elem = cnt_sand;
            stack->PushBack(triple);
            delete triple;
        }
    }
}

void Resize(Field* field, Expansion& expansion) {
    if (expansion.exp_left == 0 && expansion.exp_right == 0 && expansion.exp_up == 0 && expansion.exp_down == 0) {
        return;
    }
    uint16_t new_y_size = field->border_y + expansion.exp_down + expansion.exp_up;
    uint16_t new_x_size = field->border_x + expansion.exp_right + expansion.exp_left;
    auto temp_array = new uint64_t*[new_y_size];
    for (size_t i = 0; i < new_y_size; ++i) {
        temp_array[i] = new uint64_t[new_x_size] {0};
    }
    for (size_t i = 0; i < field->border_y; ++i) {
        for (size_t j = 0; j < field->border_x; ++j) {
            temp_array[i + expansion.exp_up][j + expansion.exp_left] = field->sand_pile[i][j];
        }
    }
    for (size_t i = 0; i < field->border_y; ++i) {
        delete[] field->sand_pile[i];
    }
    delete field->sand_pile;
    field->sand_pile = temp_array;
    field->border_y = new_y_size;
    field->border_x = new_x_size;
}

void ScatterSand(Field* field, Stack* stack) {
    while (stack->head != nullptr) {
        Triple* triple = stack->PopBack();
        field->sand_pile[triple->y][triple->x] -= 4;
        field->sand_pile[triple->y + 1][triple->x] += 1;
        field->sand_pile[triple->y][triple->x + 1] += 1;
        field->sand_pile[triple->y - 1][triple->x] += 1;
        field->sand_pile[triple->y][triple->x - 1] += 1;
        delete triple;
    }
}

void SaveBMP(Field* field, const char* dir, uint64_t name) {
    BMP bmp(field->border_x, field->border_y);
    char* filename = CreateFilename(dir, name);
    bmp.Write(filename, field);
    delete[] filename;
}

void IterSandPile(Field* field, Arguments& arguments) {
    uint64_t temp_limit = arguments.limit;
    uint64_t temp_freq = arguments.freq;
    uint64_t bmp_filename = 1;
    while (temp_limit) {
        Expansion expansion;
        DefineExpSides(field, expansion);
        auto stack = new Stack();
        FillStack(field, stack, expansion);
        if (stack->IsEmpty()) {
            break;
        }
        Resize(field, expansion);
        ScatterSand(field, stack);
        delete stack;
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