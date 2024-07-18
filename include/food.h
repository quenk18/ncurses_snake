#ifndef FOOD_H
#define FOOD_H

#include <stdlib.h>
#include <stdint.h>
#include "pos.h"
#include <time.h>

#define FOOD_MAX_NB 30

typedef struct {
        pos_t pos;
        char repr;
} food_t;

typedef struct {
        food_t food[FOOD_MAX_NB]; // oversized maybe...
        size_t len;
        char repr;
} food_list_t;

food_t generateFood(uint16_t max_row, uint16_t max_column, char repr);
food_list_t generateFoodList(size_t size, char repr);

#endif
