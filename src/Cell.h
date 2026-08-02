//
// Created by Gage Willette on 8/1/26.
//

#ifndef SNAKE_BOT_CELL_H
#define SNAKE_BOT_CELL_H
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <iostream>


struct GameDimensions;

enum CellState {
    EMPTY,
    FOOD,
    SNAKE_BODY,
};


class Cell {
public:
    Cell(int x, int y, int borderLength, int borderWidth, int cellID);

    void render(SDL_Renderer *renderer);
    void update();

    int borderWidth = 0;

    bool isFilled = false;
    SDL_Rect dstRect{};

    CellState getState() const { return state; }
    void setState(CellState newState) { this->state = newState; }

    SDL_Color getCellColorFromState(CellState state) {
        switch (state) {
            case EMPTY:
                return borderColor;
                break;
            case SNAKE_BODY:
                return snakeColor;
                break;
            case FOOD:
                return foodColor;
                break;
        }

    }

    bool getIsFilledFromState() {
        return state != EMPTY;
    }

    // Node * bodyNode;
    Cell *left, *right, *up, *down;


    void debug() {
        std::cout << "dstRect: " <<
                " X: " << this->dstRect.x <<
                " Y: " << this->dstRect.y <<
                " W: " << this->dstRect.w <<
                " H: " << this->dstRect.h << std::endl;
        if (this->left)
            std::cout << "dstRect Left: " <<
                    " X: " << this->left->dstRect.x <<
                    " Y: " << this->left->dstRect.y <<
                    " W: " << this->left->dstRect.w <<
                    " H: " << this->left->dstRect.h << std::endl;

        if (this->right)
            std::cout << "dstRect Right: " <<
                    " X: " << this->right->dstRect.x <<
                    " Y: " << this->right->dstRect.y <<
                    " W: " << this->right->dstRect.w <<
                    " H: " << this->right->dstRect.h << std::endl;

        if (this->up)
            std::cout << "dstRect Up: " <<
                    " X: " << this->up->dstRect.x <<
                    " Y: " << this->up->dstRect.y <<
                    " W: " << this->up->dstRect.w <<
                    " H: " << this->up->dstRect.h << std::endl;

        if (this->down)
            std::cout << "dstRect Down: " <<
                    " X: " << this->down->dstRect.x <<
                    " Y: " << this->down->dstRect.y <<
                    " W: " << this->down->dstRect.w <<
                    " H: " << this->down->dstRect.h << std::endl;
    }

    int getID() const { return cellID; }

    bool isCornerPiece(GameDimensions dims) const;

    int posX, posY;

    const int borderLength;

private:
    SDL_Color renderColor = {};

    SDL_Color borderColor{255, 255, 255, 255}; // white
    SDL_Color snakeColor{0, 255, 0, 255}; // green
    SDL_Color foodColor{255, 0, 0, 255}; // red

    int cellID;
    CellState state;
};

#endif //SNAKE_BOT_CELL_H
