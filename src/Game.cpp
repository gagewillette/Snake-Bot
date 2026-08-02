//
// Created by Gage Willette on 8/1/26.
//

#include "Game.h"
#include <iostream>


Game::Game(GameDimensions dims, bool isFullscreen) {
    this->gameDims = dims;

    int cellCount = 0;

    // Calc width & height of cells (dangerous as they should be the same)
    int cellWidth = dims.windowWidth / dims.boardHorizontalCellCount;

    // working values
    int cellX = 0, cellY = 0 ;

    vector<Cell *> workingVec;

    for (int i = 0 ; i < dims.boardHorizontalCellCount ; i++) {
        for (int j = 0 ; j < dims.boardVerticalCellCount ; j++) {
            // Create new cell objects and push onto working vector
            // Abritrary border width, can be changed here for now
            Cell * cell = new Cell(cellX, cellY, cellWidth, 2, cellCount);
            workingVec.push_back(cell);
            cellCount ++;
            cellX += cellWidth;
        }

        board.push_back(workingVec);
        workingVec.empty();
        cellY += cellWidth;
        cellX = 0;
    }

    init();
}

Game::~Game() {}

bool Game::init() {

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize the SDL2 library\n";
        return false;
    }


    // Create window
    this->window = SDL_CreateWindow("Snake Bot KMS",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          this->gameDims.windowWidth, this->gameDims.windowHeight,
                                          this->fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
    if(!window) {
        std::cout << "Failed to create window\n";
        return false;
    }

    // Render creation
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    this->run = true;
    return true;
}

void Game::update() {
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    SDL_RenderClear(renderer);

    drawBoard();

    SDL_RenderPresent(renderer);
}

void Game::drawBoard() {
    for (const auto & row : board) {
        for (auto c : row) {
            c->render(renderer);
        }
    }
}

void Game::handleEvents() {
    SDL_Event e;

    SDL_PollEvent(&e);

    if (e.type == SDL_QUIT) {
        this->run = false;
    }
}

void Game::limitFPS() {
    static const int FPS = 60;
    static const int frameDelay = 1000 / FPS; // Maximum time allowed per frame
    static Uint32 frameStart;
    static int frameTime;

    frameStart = SDL_GetTicks();
    frameTime = SDL_GetTicks() - frameStart; // Time the frame took in milliseconds

    if (frameDelay > frameTime)
        SDL_Delay(frameDelay - frameTime); // Wait the remaining time to limit the FPS
}
