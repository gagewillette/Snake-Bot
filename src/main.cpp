#include <iostream>
#include "Game.h"
#include "Cell.h"

using namespace std;

int main() {

    cout << "Starting game" << endl;

    GameDimensions dims = {
        800,
        800,
        20,
        20
    };

    Game g(dims, false);

    while (g.isRunning()) {
        g.handleEvents();
        g.update();
        g.render();
        g.limitFPS();
    }

    cout << "Ending game" << endl;

    return 0;
}