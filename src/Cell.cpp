//
// Created by Gage Willette on 8/1/26.
//

#include "Cell.h"

#include "Game.h"

Cell::Cell(int x, int y, int borderLength, int borderWidth, int cellID) : borderLength(borderLength) {
    dstRect = {x, y, borderLength, borderLength};
    this->cellID = cellID;
    this->borderWidth = borderWidth;
    posX = dstRect.x / this->borderLength;
    posY = dstRect.y / this->borderLength;
}

void Cell::update() {
    this->renderColor = getCellColorFromState(this->getState());
    this->isFilled = getIsFilledFromState();
}

void Cell::render(SDL_Renderer *renderer) {
    int error = SDL_SetRenderDrawColor(renderer,
                                       renderColor.r,
                                       renderColor.g,
                                       renderColor.b,
                                       renderColor.a);

    if (error != 0)
        std::cout << "error: color cell rendering" << std::endl;

    this->isFilled ? SDL_RenderFillRect(renderer, &dstRect) : SDL_RenderDrawRect(renderer, &dstRect);
}

bool Cell::isCornerPiece(GameDimensions dims) const {
    return ((posX == 0 && posY == 0) ||
            (posX == dims.boardHorizontalCellCount - 1 && posY == 0) ||
            (posX == 0 && posY == dims.boardVerticalCellCount - 1) ||
            (posX == dims.boardHorizontalCellCount && posY == dims.boardVerticalCellCount));
}
