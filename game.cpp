#include <game.hpp>




Map::Map(int h, int w) : h(h), w(w) {
    map.resize(w);
    for (int i = 0; i < w; i++) {
        map[i].resize(h);
        for (int j = 0; j < h; j++) {
            if (i == 0 || i == w - 1 || j == 0 || j == h - 1) {
                map[i][j] = WALL;
            } else {
                map[i][j] = EMPTY;
            }
        }
    }
}

bool Map::isInMap(int x, int y) {
    if (x > 0 && x < w && y > 0 && y < h) {
        return true;
    } else {
        return false;
    }
}

Tile& Map::getTile(int x, int y) {
    return map[x][y];
}

int Map::getWidth() {
    return w;
}

int Map::getHeight() {
    return h;
}

void Map::placeApple() {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (map[i][j] == APPLE) {
                map[i][j] = EMPTY;
            }
        }
    }
    map[rand()%(w - 2) + 1][rand()%(h - 2) + 1] = APPLE;
}

bool Map::isOnApple(Snake snake) {
    for (int i = 0; i < snake.getSize(); i++) {
        if (map[snake.getXFromIndex(i)][snake.getYFromIndex(i)] == APPLE) {
            return true;
        }
    }
    return false;
}


Snake::Snake(int size, Map& map, int x, int y) : map(map) {
    for (int i = 0; i < size; i++) {
        snake.push_back({RIGHT, x + i, y});
    }
    Snake::size = size;
}

void Snake::push(Direction direction) {
    
    switch (direction) {
    case UP:
    snake.push_back({direction, snake.back().x, snake.back().y - 1});        
        break;
    case DOWN:
    snake.push_back({direction, snake.back().x, snake.back().y + 1});        
        break;
    case LEFT:
    snake.push_back({direction, snake.back().x - 1, snake.back().y});        
        break;
    case RIGHT:
    snake.push_back({direction, snake.back().x + 1, snake.back().y});        
        break;
    
    default:
        break;
    }
    size++;
}

void Snake::pop() {
    if (snake.size() > 1) {
        snake.pop_front();
    }
    size--;
}

bool Snake::isAlive() {
    return alive;
}

void Snake::move(Direction direction) {

    push(direction);
    if (isBitingItself() == true || map.isInMap(snake[size - 1].x, snake[size - 1].y) == false) {
        alive = false;
    } else if (map.isOnApple(*this)) {
        do {
            map.placeApple();
        } while (map.isOnApple(*this));
    } else {
        pop();
    }
    snake[size - 2].facing = snake.back().facing;
}

bool Snake::isBitingItself() {
    for (int i = 0; i < size - 1; i++) {
        if (snake[size - 1].x == snake[i].x && snake[size - 1].y == snake[i].y) {
            return true;
        }
    }
    return false;
}

int Snake::getSize() {
    return size;
}

int Snake::getXFromIndex(int i) {
    return snake[i].x;
}

int Snake::getYFromIndex(int i) {
    return snake[i].y;
}

Direction Snake::getDirection(int i) {
    return snake[i].facing;
}

Direction Snake::getDirection() {
    return getDirection(snake.size() - 1);
}