//
// Created by Gage Willette on 8/1/26.
//

#include <SDL.h>
#include <vector>

#include "Cell.h"

#ifndef SNAKE_BOT_GAME_H
#define SNAKE_BOT_GAME_H

struct GameDimensions {
    int windowWidth;
    int windowHeight;
    int boardHorizontalCellCount;
    int boardVerticalCellCount;
};

using namespace std;

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

    // Placeholder board
    vector<vector<Cell *>> board;

    bool fullscreen{};
};


#endif //SNAKE_BOT_GAME_H
