#include "food.h"

food_t generateFood(uint16_t max_row, uint16_t max_column, char repr) {
        food_t food;
        food.pos.x = rand() % (max_column - 2) + 1;
        food.pos.y = rand() % (max_row - 2) + 1;
        food.repr = repr;
        return food;
}

food_list_t generateFoodList(size_t size, char repr) {
        food_list_t food_list;
        food_list.len = size;
        food_list.repr = repr;
        if (size > FOOD_MAX_NB) {
                size = FOOD_MAX_NB;
        }
        for (size_t i = 0; i < size; i++) {
                food_list.food[i] = generateFood(ROWS, COLUMNS, repr);
        }
        return food_list;
}
