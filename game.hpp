#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <vector>
#include <deque>
#include <iostream>

using namespace std;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

enum Tile {
    EMPTY,
    WALL,
    APPLE,
};

struct BodyPart {
    Direction facing;
    int x;
    int y;
};

class Snake;

class Map {
    public:
    Map(int h, int w);
    bool isInMap(int x, int y);
    Tile& getTile(int x, int y);
    int getWidth();
    int getHeight();
    void placeApple();
    bool isOnApple(Snake snake);

    private:
    vector<vector<Tile>> map;
    int h;
    int w;
};

class Snake {
    public:
    Snake(int size, Map& map, int x, int y);
    void move(Direction direction);
    bool isAlive();
    int getSize();

    int getXFromIndex(int i);
    int getYFromIndex(int i);
    Direction getDirection(int i);
    Direction getDirection();

    private:
    Map& map;
    deque<BodyPart> snake;
    int size;
    bool alive;

    bool isBitingItself();
    void push(Direction direction);
    void pop();
};

#endif