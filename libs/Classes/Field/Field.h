#pragma once
#include <cstdint>
#include <cstddef>

struct Field {
    int16_t border_x;
    int16_t border_y;
    uint64_t** sand_pile;

    Field() {
        border_x = 0;
        border_y = 0;
        sand_pile = nullptr;
    }

    ~Field() {
        for (size_t i = 0; i < this->border_y; ++i) {
            delete[] sand_pile[i];
        }
        delete sand_pile;
    }
};
