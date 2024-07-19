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

bool showEndScreen(WINDOW* snake_screen) {
        char* message = "Snake is dead!";
        mvwprintw(snake_screen, ROWS / 2, (COLUMNS - sizeof(message)) / 2,
                  message, sizeof(message));
        wrefresh(snake_screen);
        nodelay(snake_screen, FALSE);
        sleep(1);
        getch();
        clear();
        nocbreak();
        endwin();
}

uint8_t updateSnakeScreen(WINDOW* game_screen, snake_t* snake,
                          direction_t direction) {
        clearSnake(game_screen, snake);
        moveSnake(snake, direction);
        showSnake(game_screen, snake);
        return 0;
}

uint8_t showFood(WINDOW* game_screen, food_list_t food_list) {
        for (uint8_t i = 0; i < food_list.len; i++) {
                mvwaddnstr(game_screen, food_list.food[i].pos.y,
                           food_list.food[i].pos.x, &(food_list.food[i].repr),
                           1);
        }
        return 0;
}

uint8_t clearSnake(WINDOW* game_screen, snake_t* snake) {
        for (uint8_t i = 0; i < snake->len; i++) {
                mvwaddnstr(game_screen, snake->body[i].pos.y,
                           snake->body[i].pos.x, " ", 1);
        }
        return 0;
}
uint8_t showSnake(WINDOW* game_screen, snake_t* snake) {
        for (uint8_t i = 0; i < snake->len; i++) {
                mvwaddnstr(game_screen, snake->body[i].pos.y,
                           snake->body[i].pos.x, "s", 1);
        }
        return 0;
}

uint8_t handleSnakeEatingFood(WINDOW* snake_screen, snake_t* snake,
                              food_list_t* food_list) {
        int16_t eaten_food_idx = isSnakeEatingFood(snake, *food_list);
        if (eaten_food_idx != -1) {
                food_list->food[eaten_food_idx] =
                    generateFood(COLUMNS, ROWS, food_list->repr);
                showFood(snake_screen, *food_list);
                growSnake(snake);
        }

        return 0;
}
