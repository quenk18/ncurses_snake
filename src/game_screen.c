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
        mvwprintw(snake_screen, ROWS / 2, (COLUMNS - sizeof(message)) / 2, message, sizeof(message));
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
