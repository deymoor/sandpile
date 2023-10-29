#include "itersandpile.h"


void DefineExpSides(Field* field, Expansion& expansion) {
    for (size_t i = 0; i < field->border_y; ++i) {
        for (size_t j = 0; j < field->border_x; ++j) {
            if (field->sand_pile[i][j] < 4) {
                continue;
            }
            if (i == 0) {
                expansion.exp_up = 1;
            }
            if (i == field->border_y - 1) {
                expansion.exp_down = 1;
            }
            if (j == 0) {
                expansion.exp_left = 1;
            }
            if (j == field->border_x - 1) {
                expansion.exp_right = 1;
            }
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
            Triple* triple = new Triple();
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
    int16_t new_y_size = field->border_y + expansion.exp_down + expansion.exp_up;
    int16_t new_x_size = field->border_x + expansion.exp_right + expansion.exp_left;
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
    InitPalette(bmp.palette);
    char* filename = CreateFilename(dir, name);
    bmp.Write(filename, field);
    delete[] filename;
}

// доделать
void IterSandPile(Field* field, Arguments& arguments) {
    uint64_t temp_limit = arguments.limit;
    uint64_t temp_freq = 0;
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
        if (temp_freq == arguments.freq && temp_freq != 0) {
            SaveBMP(field, arguments.dir, bmp_filename);
            temp_freq = 0;
            bmp_filename++;
        }
        delete stack;
        temp_limit--;
        temp_freq++;
    }
    SaveBMP(field, arguments.dir, bmp_filename);
}