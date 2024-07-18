#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <unistd.h>
#include <ncurses.h>
#include "snake.h"
#include "food.h"
#include "pos.h"

#define DELAY_US 100000

direction_t getUserDirection(WINDOW* snake_screen);

WINDOW* initGameWindow();

bool showEndScreen(WINDOW* snake_screen);

uint8_t updateSnakeScreen(WINDOW* game_screen, snake_t* snake, direction_t direction);

uint8_t showFood(WINDOW* game_screen, food_list_t food_list);
#endif
