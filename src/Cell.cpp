//
// Created by Gage Willette on 8/1/26.
//

#include "Cell.h"

Cell::Cell(int x, int y , int borderLength, int borderWidth, int cellID) {
   dstRect = {x, y, borderLength, borderLength};
   this->cellID = cellID;
   this->borderWidth = borderWidth;
}

void Cell::render(SDL_Renderer *renderer) {
   //std::cout << this->cellID << std::endl;

   int error = SDL_SetRenderDrawColor(renderer,
      this->borderColor.r,
      this->borderColor.g,
      this->borderColor.b,
      this->borderColor.a
      );

   if (error != 0)
      std::cout << "error: cell rendering" << std::endl;

   if (cellID == -1) { // set to any cell value to see its dst rect in console
     std::cout << "dstRect: " <<
        " X: " << this->dstRect.x <<
        " Y: " << this->dstRect.y <<
        " W: " << this->dstRect.w <<
        " H: " << this->dstRect.h << std::endl;
   }

   SDL_RenderDrawRect(renderer, &dstRect);
}
