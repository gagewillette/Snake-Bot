//
// Created by Gage Willette on 8/1/26.
//

#include "Game.h"
#include <iostream>


Game::Game(GameDimensions dims, bool isFullscreen) {
    this->gameDims = dims;

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
                                          this->width, this->height,
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
}

void Game::update() {
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
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
