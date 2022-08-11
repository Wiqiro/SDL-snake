#include <gui.hpp>
#include <game.hpp>

int main(int argc, char *argv[]) {

    Map map(20, 20);
    Snake snake(5, map, 0, 5);
    Direction direction = RIGHT;

    Window window(1000, 1000, 50, 100);
    
    clock_t timer;
    map.placeApple();

    timer = clock();
    while(snake.isAlive()) {
        window.render(map, snake);
        window.listen(direction);

        if (clock() - timer >= 200) {
            if ((direction == LEFT && snake.getDirection() == RIGHT) || (direction == RIGHT && snake.getDirection() == LEFT) || (direction == UP && snake.getDirection() == DOWN) || (direction == DOWN && snake.getDirection() == UP)) {
                snake.move(snake.getDirection());
            } else {
                snake.move(direction);
            }
            timer = clock();
        }
    }
    //TODO: lkeg
    //TODO: eof

    window.deathScreen();
    while (clock() - timer < 3000);

    return EXIT_SUCCESS;
}