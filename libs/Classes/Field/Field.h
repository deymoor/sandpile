#pragma once
#include <cstdint>
#include <cstddef>


struct Field {
    static const uint8_t collapse = 4;
    uint16_t border_x;
    uint16_t border_y;
    uint64_t** sand_pile;

    Field() {
        border_x = 0;
        border_y = 0;
        sand_pile = nullptr;
    }

    ~Field() {
        if (sand_pile == nullptr) {
            return;
        }
        for (size_t i = 0; i < this->border_y; ++i) {
            delete[] sand_pile[i];
        }
        delete sand_pile;
    }
};
