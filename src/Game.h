//
// Created by Gage Willette on 8/1/26.
//

#include <SDL.h>

#include "Cell.h"

#ifndef SNAKE_BOT_GAME_H
#define SNAKE_BOT_GAME_H

struct GameDimensions {
    int windowWidth;
    int windowHeight;
    int boardWidthPx;
    int boardHeightPx;
    int boardHorizontalCellCount;
    int boardVerticalCellCount;
};

class Game {

public:
    Game(GameDimensions dims, bool isFullscreen);
    ~Game();

    bool init();
    void update();
    void render();

    void drawBoard();

    void handleEvents();
    void limitFPS();
    void clean();

    bool isRunning() const { return run; };

private:
    bool run = false;
    SDL_Window * window{};
    SDL_Renderer * renderer{};
    SDL_Surface * windowSurface{}; // do not free this

    GameDimensions gameDims{};

    // Cell matrix
    Cell[boardWidth][boardHeight] board;

    int width{}, height{};
    bool fullscreen{};
};


#endif //SNAKE_BOT_GAME_H
