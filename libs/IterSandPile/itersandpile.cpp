#include "itersandpile.h"

void FillStack(Stack* stack, Field* field) {
    for (size_t i = 0; i < field->border_y; ++i) {
        for (size_t j = 0; j < field->border_x; ++j) {
            uint64_t cnt_sand = field->sand_pile[i][j];
            Triple* triple = new Triple();
            triple->y = i;
            triple->x = j;
            triple->elem = cnt_sand;
            if (cnt_sand >= 4) {
                stack->PushBack(triple);
            }
            delete triple;
        }
    }
}

void IterSandPile(Field* field, Arguments& arguments) {
    while (true) {
        auto stack = new Stack();
        FillStack(stack, field);
        if (stack->IsEmpty()) {
            break;
        }
        delete stack;
    }
}