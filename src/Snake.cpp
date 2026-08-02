//
// Created by Gage Willette on 8/2/26.
//

#include "Snake.h"

#include "Game.h"

Snake::Snake(Game *game) {
    this->gameRef = game;

    head = new Node{gameRef->board[5][7], nullptr, nullptr};
}

void Snake::update() {
    if (gameRef->getFrameCount() > (Game::FPS / movesPerSecond)) { // move once every half second
        move(this->looking);
        moveCount ++;

        gameRef->resetFrameCount();
    }

    Node *cur = head;
    while (cur != nullptr) {
        // set all occupied cells to body state
        cur->occupiedCell->setState(SNAKE_BODY);
        cur = cur->next;
    }
}

void Snake::move(Direction move) {
    Node *cur = head;
    while (cur != nullptr) {
        switch (looking) {
            case LEFT:
                cur->occupiedCell = cur->occupiedCell->left;
                break;
            case RIGHT:
                cur->occupiedCell = cur->occupiedCell->right;
                break;
            case UP:
                cur->occupiedCell = cur->occupiedCell->up;
                break;
            case DOWN:
                cur->occupiedCell = cur->occupiedCell->down;
                break;
        }

        cur = cur->next;
    }
}

bool Snake::updateMoveDirection(Direction newDirection) {
    // TODO: valid direction checking
    looking = newDirection;
    return true;
}

Snake::~Snake() {
}
