//
// Created by Gage Willette on 8/1/26.
//

#include <SDL.h>
#include <vector>

#include "Cell.h"
#include "Snake.h"

#ifndef SNAKE_BOT_GAME_H
#define SNAKE_BOT_GAME_H

class Snake;

enum GameState {
    START,
    RUN,
    END
};

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

    bool isRunning() const { return run; };

    GameState state = START;

    vector<vector<Cell *>> board;

    Snake snake;

    Cell * cellAt(int x, int y) { return board[x][y]; }

    int getFrameCount() const {return frame_count;}
    void resetFrameCount() { frame_count = 0; }

    static const int FPS = 60;

private:
    bool run = false;
    SDL_Window * window{};
    SDL_Renderer * renderer{};
    SDL_Surface * windowSurface{}; // do not free this

    bool initSDL();
    void initBoard();
    void initSnake();

    void updateCells();
    void clearCellState();

    GameDimensions gameDims{};

    int frame_count = 0;

    // Placeholder board
    void populateBoardNeighbors();

    bool fullscreen{};
};


#endif //SNAKE_BOT_GAME_H
