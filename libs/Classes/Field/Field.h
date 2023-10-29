#pragma once
#include <cstdint>
#include <cstddef>


struct Field {
    uint16_t border_x = 0;
    uint16_t border_y = 0;
    uint64_t** sand_pile = nullptr;

    ~Field() {
        for (size_t i = 0; i < this->border_y; ++i) {
            delete[] sand_pile[i];
        }
        delete sand_pile;
    }
};
