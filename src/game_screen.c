#include "game_screen.h"

direction_t getUserDirection(WINDOW* snake_screen) {
        int ch = 0;
        direction_t direction = NO_MOV;
        nodelay(snake_screen, TRUE);
        ch = wgetch(snake_screen);
        switch (ch) {
                case 'k':
                        direction = UP;
                        break;
                case 'j':
                        direction = DOWN;
                        break;
                case 'h':
                        direction = LEFT;
                        break;
                case 'l':
                        direction = RIGHT;
                        break;
                default:
                        break;
        }
        return direction;
}

WINDOW* initGameWindow() {
        initscr();
        WINDOW* game_screen = newwin(ROWS, COLUMNS, 0, 0);
        keypad(game_screen, TRUE);
        noecho();
        cbreak();
        clear();
        nodelay(game_screen, TRUE);
        box(game_screen, 0, 0);
        return game_screen;
}

uint8_t updateSnakeScreen(WINDOW* game_screen, snake_t* snake,
                          direction_t direction) {
        clearSnake(game_screen, snake);
        moveSnake(snake, direction);
        showSnake(game_screen, snake);
        return 0;
}

uint8_t showFood(WINDOW* game_screen, food_t food) {
        mvwaddnstr(game_screen, food.pos.y, food.pos.x, &(food.repr), 1);
        return 0;
}
