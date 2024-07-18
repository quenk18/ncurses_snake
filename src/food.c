#include "food.h"

food_t generateFood(uint16_t max_row, uint16_t max_column) {
        food_t food;
        food.pos.x = rand() % (max_column - 2) + 1;
        food.pos.y = rand() % (max_row - 2) + 1;
        food.repr = '*';
        return food;
}
