//
// Created by Gage Willette on 8/1/26.
//

#ifndef SNAKE_BOT_CELL_H
#define SNAKE_BOT_CELL_H
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <iostream>


class Cell {
public:
    Cell(int x, int y , int borderLength, int borderWidth, int cellID);

    void render(SDL_Renderer * renderer);

    int borderWidth = 0;
    SDL_Color borderColor {255, 255, 255, 255}; // white
    SDL_Rect dstRect{};

    // Node * bodyNode;

private:

    int cellID{};
};

#endif //SNAKE_BOT_CELL_H
