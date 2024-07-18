#include <stdint.h>
#include <unistd.h>
#include "snake.h"
#include "game_screen.h"
#include "food.h"

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

        food_t food = generateFood(COLUMNS, ROWS);
        showFood(game_screen, food);

        refresh();

        while (1) {
                next_dir = getUserDirection(game_screen);
                if (next_dir != NO_MOV) {
                        current_dir = next_dir;
                }
                updateSnakeScreen(game_screen, &snake, current_dir);

                if (isSnakeEatingFood(&snake, &food)) {
                        food = generateFood(COLUMNS, ROWS);
                        showFood(game_screen, food);
                        growSnake(&snake);
                }
                if (!isSnakePositionValid(&snake)) {
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
