#include <ncurses.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define DELAY_US 100000
#define ROWS 30
#define COLUMNS 30

#define MAX_BODY 200
#define HEAD 0

typedef enum { NO_MOV = 0, UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4 } direction_t;

typedef struct {
        uint8_t x;
        uint8_t y;
} pos_t;

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

typedef struct {
        pos_t pos;
        char repr;
} food_t;

bool isPositionValid(snake_t* snake) {
        // check if on borders: check on the head only is sufficient
        if (snake->body[HEAD].pos.x == 0 ||
            snake->body[HEAD].pos.x == COLUMNS - 1) {
                return false;
        }
        if (snake->body[HEAD].pos.y == 0 ||
            snake->body[HEAD].pos.y == ROWS - 1) {
                return false;
        }

        // don't start at the HEAD
        for (uint8_t i = 1; i < MAX_BODY; i++) {
                if (snake->body[HEAD].pos.x == snake->body[i].pos.x &&
                    snake->body[HEAD].pos.y == snake->body[i].pos.y) {
                        return false;
                }
        }
        return true;
}

bool isSnakeEatingFood(snake_t* snake, food_t* food) {
        return snake->body[HEAD].pos.x == food->pos.x &&
               snake->body[HEAD].pos.y == food->pos.y;
}

food_t generateFood() {
        food_t food;
        food.pos.x = rand() % (COLUMNS - 2) + 1;
        food.pos.y = rand() % (ROWS - 2) + 1;
        food.repr = '*';
        return food;
}

uint8_t showFood(WINDOW* game_screen, food_t food) {
        mvwaddnstr(game_screen, food.pos.y, food.pos.x, &(food.repr), 1);
        return 0;
}

uint8_t growSnake(snake_t* snake) {
        if (snake->len < MAX_BODY) {
                snake->body[snake->len].exist = true;
                switch (snake->body[snake->len - 1].direction) {
                        case UP:
                                snake->body[snake->len].pos.x =
                                    snake->body[(snake->len) - 1].pos.x;
                                snake->body[snake->len].pos.y =
                                    snake->body[(snake->len) - 1].pos.y + 1;
                                break;

                        case DOWN:
                                snake->body[snake->len].pos.x =
                                    snake->body[(snake->len) - 1].pos.x;
                                snake->body[snake->len].pos.y =
                                    snake->body[(snake->len) - 1].pos.y - 1;
                                break;

                        case LEFT:
                                snake->body[snake->len].pos.x =
                                    snake->body[(snake->len) - 1].pos.x + 1;
                                snake->body[snake->len].pos.y =
                                    snake->body[(snake->len) - 1].pos.y;
                                break;

                        case RIGHT:
                                snake->body[snake->len].pos.x =
                                    snake->body[(snake->len) - 1].pos.x - 1;
                                snake->body[snake->len].pos.y =
                                    snake->body[(snake->len) - 1].pos.y;
                                break;
                        case NO_MOV:
                                // should not arrive here
                                break;
                }
                snake->len++;
        }
        return 0;
}

uint8_t moveBody(snake_body_t* body, direction_t direction) {
        pos_t new_pos = {
            .x = 0,
            .y = 0,
        };
        switch (direction) {
                case UP:
                        new_pos.x = 0;
                        new_pos.y = -1;
                        break;

                case DOWN:
                        new_pos.x = 0;
                        new_pos.y = 1;
                        break;

                case LEFT:
                        new_pos.x = -1;
                        new_pos.y = 0;
                        break;

                case RIGHT:
                        new_pos.x = 1;
                        new_pos.y = 0;
                        break;

                case NO_MOV:
                        break;

                default:
                        break;
        }
        body->pos.x += new_pos.x;
        body->pos.y += new_pos.y;
        body->direction = direction;

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

uint8_t moveSnake(snake_t* snake, direction_t next_direction) {
        snake_body_t prev_body;
        snake_body_t next_body = snake->body[HEAD];

        // starts at 1, the head is controlled by direction
        for (uint8_t i = 0; i < snake->len; i++) {
                if (!snake->body[i].exist) {
                        break;
                }
                if (i == 0) {
                        moveBody(&(snake->body[i]), next_direction);
                } else {
                        prev_body = snake->body[i];
                        snake->body[i] = next_body;
                        next_body = prev_body;
                }
        }
#ifdef DEBUG
        for (uint8_t i = 0; i < MAX_BODY; i++) {
                mvprintw(ROWS + i, 0, "%d %d %d %d %d %d\n", i, snake->len,
                         snake->body[i].pos.x, snake->body[i].pos.y,
                         snake->body[i].direction, snake->body[i].exist);
        }
#endif
        return 0;
}

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

int main() {
        // inits random seed
        srand(time(NULL));

        WINDOW* game_screen = initGameWindow();

        // initializes snake pos
        snake_t snake = {
            .len = 1,
            .body[HEAD].pos.x = COLUMNS / 2,
            .body[HEAD].pos.y = ROWS / 2,
            .body[HEAD].exist = true,
            .repr = 's',
        };

        direction_t current_dir = RIGHT;
        direction_t next_dir = NO_MOV;

        food_t food = generateFood();
        showFood(game_screen, food);

        refresh();

        while (1) {
                next_dir = getUserDirection(game_screen);
                if (next_dir != NO_MOV) {
                        current_dir = next_dir;
                }

                updateSnakeScreen(game_screen, &snake, current_dir);

                if (isSnakeEatingFood(&snake, &food)) {
                        food = generateFood();
                        showFood(game_screen, food);
                        growSnake(&snake);
                }
                if (!isPositionValid(&snake)) {
                        char* message = "Snake is dead!";
                        mvprintw(ROWS / 2, (COLUMNS - sizeof(message)) / 2,
                                 message);
                        nodelay(game_screen, FALSE);
#ifdef DEBUG
                        for (uint8_t i = 0; i < MAX_BODY; i++) {
                                mvprintw(ROWS + i, 0, "%d %d %d %d %d %d\n", i,
                                         snake.len, snake.body[i].pos.x,
                                         snake.body[i].pos.y,
                                         snake.body[i].direction,
                                         snake.body[i].exist);
                        }
#endif

                        getch();
                        clear();
                        return 0;
                }
                refresh();
                usleep(DELAY_US);
        }
        endwin();
        return 0;
}
