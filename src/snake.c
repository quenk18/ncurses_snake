#include "snake.h"

bool isSnakePositionValid(snake_t* snake) {
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

int16_t isSnakeEatingFood(snake_t* snake, food_list_t food_list) {
        for (int16_t i = 0; i < food_list.len; i++) {
                if (snake->body[HEAD].pos.x == food_list.food[i].pos.x &&
                    snake->body[HEAD].pos.y == food_list.food[i].pos.y) {
                        return i;
                }
        }
        return -1;
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

