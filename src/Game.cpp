//
// Created by Gage Willette on 8/1/26.
//

#include "Game.h"
#include <iostream>

#include "Snake.h"


Game::Game(GameDimensions dims, bool isFullscreen) {
    std::cout << "Game constructor" << std::endl;

    this->gameDims = dims;
    this->fullscreen = isFullscreen;

    init();
}

Game::~Game() {
    for (auto & row : board) {
        for (auto & cur : row) {
            delete cur;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

bool Game::init() {
    initSDL();
    initBoard();
    initSnake();

    update();

    return true;
}

bool Game::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize the SDL2 library\n";
        return false;
    }


    // Create window
    this->window = SDL_CreateWindow("Snake Bot KMS",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    this->gameDims.windowWidth, this->gameDims.windowHeight,
                                    this->fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
    if (!window) {
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

void Game::initBoard() {
    int cellCount = 0;

    // Calc width & height of cells (dangerous as they should be the same)
    int cellWidth = gameDims.windowWidth / gameDims.boardHorizontalCellCount;

    // working values
    int cellX = 0, cellY = 0;

    vector<Cell *> workingVec;

    std::cout << "Creating cells..." << std::endl;
    for (int i = 0; i < gameDims.boardHorizontalCellCount; i++) {
        for (int j = 0; j < gameDims.boardVerticalCellCount; j++) {
            // Create new cell objects and push onto working vector
            // Abritrary border width, can be changed here for now
            Cell *cell = new Cell(cellX, cellY, cellWidth, 2, cellCount);
            workingVec.push_back(cell);
            cellCount++;
            cellX += cellWidth;
        }

        board.push_back(workingVec);
        workingVec.clear();
        cellY += cellWidth;
        cellX = 0;
    }

    std::cout << "Created " << cellCount << " cells..." << std::endl;

    populateBoardNeighbors();
}

void Game::initSnake() {
    Snake s(this);
    snake = s;
}



void Game::update() {
   frame_count++;

    clearCellState();

    snake.update();

    updateCells();
}

void Game::clearCellState() {
    for (auto & row : board) {
        for (auto & cell : row) {
            cell->setState(EMPTY);
        }
    }
}

void Game::updateCells() {
    for (auto & row : board) {
        for (auto & cell : row) {
            cell->update();
        }
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    SDL_RenderClear(renderer);

    drawBoard();

    SDL_RenderPresent(renderer);
}

void Game::drawBoard() {
    for (const auto &row: board) {
        for (auto c: row) {
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

    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_SPACE:
                this->state = RUN;
                break;

            case SDLK_LEFT:
                std::cout << "Left pressed" << std::endl;
                snake.updateMoveDirection(LEFT);
                break;

            case SDLK_RIGHT:
                std::cout << "Right pressed" << std::endl;
                snake.updateMoveDirection(RIGHT);
                break;

            case SDLK_DOWN:
                std::cout << "Down pressed" << std::endl;
                snake.updateMoveDirection(DOWN);
                break;

            case SDLK_UP:
                std::cout << "Up pressed" << std::endl;
                snake.updateMoveDirection(UP);
                break;

        }

    }
}

void Game::limitFPS() {
    static const int frameDelay = 1000 / FPS; // Maximum time allowed per frame
    static Uint32 frameStart;
    static int frameTime;

    frameStart = SDL_GetTicks();
    frameTime = SDL_GetTicks() - frameStart; // Time the frame took in milliseconds

    if (frameDelay > frameTime)
        SDL_Delay(frameDelay - frameTime); // Wait the remaining time to limit the FPS
}

void Game::populateBoardNeighbors() {
    // cells on row = 0 have no top
    // cell on row = dims.boardVerticalCellCount - 1 have no bottom
    // cell on col = 0 have no left
    // cell on col = dims.boardHorizontalCellCount - 1 have no right
    // for any non-border cell:
    // - left = cell[row][col-1]
    // - right = cell[row][col+1]
    // - top = cell[row - 1][col]
    // - bottom = cell[row + 1][col]

    for (int row = 0; row < gameDims.boardHorizontalCellCount; row++) {
        for (int col = 0; col < gameDims.boardVerticalCellCount; col++) {
            // HOLY FUCK ts so ass 🥀🥀🥀🥀🥀
            // HOLY FUCK ts so ass 🥀🥀🥀🥀🥀
            // HOLY FUCK ts so ass 🥀🥀🥀🥀🥀
            // HOLY FUCK ts so ass 🥀🥀🥀🥀🥀

            Cell * cur = board[row][col];

            bool ep = cur->isCornerPiece(this->gameDims);
            if (ep) {
               if (cur->posX == 0 && cur->posY == 0) {
                   Cell * r = board[row][col + 1];
                   Cell * d = board[row + 1][col];

                   cur->left = nullptr;
                   cur->right = r;
                   cur->up = nullptr;
                   cur->down = d;

               }
               if (cur->posX == gameDims.boardHorizontalCellCount - 1 && cur->posY == 0) {
                   Cell * l = board[row][col - 1];
                   Cell * d = board[row + 1][col];

                   cur->left = l;
                   cur->right = nullptr;
                   cur->up = nullptr;
                   cur->down = d;
               }
               if (cur->posX == 0 && cur->posY == gameDims.boardVerticalCellCount - 1) {
                   Cell * r = board[row][col + 1];
                   Cell * u = board[row - 1][col];

                   cur->left = nullptr;
                   cur->right = r;
                   cur->up = u;
                   cur->down = nullptr;
               }
               if (cur->posX == gameDims.boardHorizontalCellCount && cur->posY == gameDims.boardVerticalCellCount) {
                   Cell * l = board[row][col - 1];
                   Cell * u = board[row - 1][col];

                   cur->left = l;
                   cur->right = nullptr;
                   cur->up = u;
                   cur->down = nullptr;
               }

                continue;
            }

            // top edge
            if (row == 0 ) {
                Cell * l = board[row][col + 1];
                Cell * r = board[row][col + 1];
                Cell * d = board[row + 1][col];

                cur->left = l;
                cur->right = r;
                cur->up = nullptr;
                cur->down = d;
            }
            else if (row == gameDims.boardHorizontalCellCount - 1) {
                Cell * l = board[row][col + 1];
                Cell * r = board[row][col + 1];
                Cell * u = board[row - 1][col];

                cur->left = l;
                cur->right = r;
                cur->up = u;
                cur->down = nullptr;
            }
            // left edge
            else if (col == 0 ) {
                Cell * r = board[row][col + 1];
                Cell * u = board[row - 1][col];
                Cell * d = board[row + 1][col];

                cur->left = nullptr;
                cur->right = r;
                cur->up = u;
                cur->down = d;
            }
            // right edge
            else if (col == gameDims.boardVerticalCellCount - 1) {
                Cell * l = board[row][col - 1];
                Cell * u = board[row - 1][col];
                Cell * d = board[row + 1][col];

                cur->left = l;
                cur->right = nullptr;
                cur->up = u;
                cur->down = d;
            }
            // internal pieces
            else {
                Cell * l = board[row][col - 1];
                Cell * r = board[row][col + 1];
                Cell * u = board[row - 1][col];
                Cell * d = board[row + 1][col];

                cur->left = l;
                cur->right = r;
                cur->up = u;
                cur->down = d;
            }
        }
    }
}
