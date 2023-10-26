#pragma once
#include "../Vector/Vector.h"

struct Field {
    Vector <int16_t> x_array;
    Vector <int16_t> y_array;
    Vector <uint64_t> grain_array;
};
