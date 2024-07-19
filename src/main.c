#include <stdint.h>
#include <unistd.h>

#include "food.h"
#include "game_screen.h"
#include "snake.h"

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

        food_list_t food_list = generateFoodList(20, 'a');

        showFood(game_screen, food_list);

        refresh();

        while (1) {
                next_dir = getUserDirection(game_screen);
                if (next_dir != NO_MOV) {
                        current_dir = next_dir;
                }
                updateSnakeScreen(game_screen, &snake, current_dir);
                handleSnakeEatingFood(game_screen, &snake, &food_list);
                if (!isSnakePositionValid(&snake)) {
                        showEndScreen(game_screen);
                        return 0;
                }
                refresh();
                usleep(DELAY_US);
        }
        endwin();
        return 0;
}
