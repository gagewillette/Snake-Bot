//
// Created by Gage Willette on 8/1/26.
//

#ifndef SNAKE_BOT_CELL_H
#define SNAKE_BOT_CELL_H
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>


class Cell {
public:
    Cell(int x, int y , int borderLength, int borderWidth);

    void render(SDL_Renderer * renderer);

    int borderLength = 20;
    int borderWidth = 2;
    SDL_Color borderColor {0, 0, 0, 255}; // white
    SDL_Rect dstRect;

    // Node * bodyNode;

};

#endif //SNAKE_BOT_CELL_H
