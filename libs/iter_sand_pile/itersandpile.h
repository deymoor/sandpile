#pragma once
#include "../Classes/Field/Field.h"
#include "../Classes/Arguments/Arguments.h"
#include "../Classes/Stack/Stack.h"
#include "../Classes/Bmp/Bmp.h"


struct Expansion {
    int16_t exp_up = 0;
    int16_t exp_down = 0;
    int16_t exp_left = 0;
    int16_t exp_right = 0;
};

void DefineExpSides(Field& field, Expansion& expansion);

void FillStack(Field& field, Stack& stack, Expansion& expansion);

void Resize(Field& field, Expansion& expansion);

void ScatterSand(Field& field, Stack& stack);

void IterSandPile(Field& field, Arguments& arguments);
