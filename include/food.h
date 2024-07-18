#ifndef FOOD_H
#define FOOD_H

#include <stdlib.h>
#include <stdint.h>
#include "pos.h"
#include <time.h>

#define FOOD_NB 3

typedef struct {
        pos_t pos;
        char repr;
} food_t;

food_t generateFood(uint16_t max_row, uint16_t max_column);

#endif
