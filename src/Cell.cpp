//
// Created by Gage Willette on 8/1/26.
//

#include "Cell.h"

Cell::Cell(int x, int y , int borderLength, int borderWidth) {
   dstRect = {x, y, borderLength, borderLength};
}

void Cell::render(SDL_Renderer *renderer) {
   SDL_RenderDrawRect(renderer, &dstRect);
}
