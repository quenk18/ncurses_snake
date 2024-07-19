#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include <stdint.h>
#include "pos.h"
#include "food.h"

#define MAX_BODY 200
#define HEAD 0

typedef enum { NO_MOV = 0, UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4 } direction_t;

typedef struct {
        pos_t pos;
        direction_t direction;
        bool exist;
} snake_body_t;

typedef struct {
        uint8_t len;
        // could be later be implemented as linked list
        snake_body_t body[MAX_BODY];
        char repr;
} snake_t;

bool isSnakePositionValid(snake_t* snake);
int16_t isSnakeEatingFood(snake_t* snake, food_list_t food_list); // return index of food eaten, -1 otherwise
uint8_t growSnake(snake_t* snake);
uint8_t moveBody(snake_body_t* body, direction_t direction);
uint8_t moveSnake(snake_t* snake, direction_t next_direction);


#endif
