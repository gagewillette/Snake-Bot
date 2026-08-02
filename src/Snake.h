//
// Created by Gage Willette on 8/2/26.
//

#ifndef SNAKE_BOT_SNAKE_H
#define SNAKE_BOT_SNAKE_H
#include "Cell.h"

class Game;
using namespace std;

enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

struct Node {
    Cell * occupiedCell;
    Node * next;
    Node * prev;
};

class Snake {

public:
    Snake() = default;
    Snake(Game * g);
    ~Snake();

    void grow();
    void checkCollision();
    void update();
    void move(Direction move);

    bool updateMoveDirection(Direction newDirection);

private:

    Node * head;
    Node * tail;
    Game * gameRef;
    int moveCount = 0;
    int movesPerSecond = 2;
    Direction looking = LEFT;
};


#endif //SNAKE_BOT_SNAKE_H
