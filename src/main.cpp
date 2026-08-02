#include <iostream>
#include "Game.h"
#include "Cell.h"

using namespace std;

int main() {

    cout << "Starting game" << endl;

    GameDimensions dims = {
        800,
        800,
        10,
        10
    };
    // For the love of god please ensure these values are cleanly divisible. Im sure plenty of things
    // will break if they are not

    Game g(dims, false);

    while (g.isRunning()) {
        g.handleEvents();

        switch (g.state) {
            case START:
                g.render();
                g.limitFPS();
                break;
            case RUN:
                g.update();
                g.render();
                g.limitFPS();
                break;
            case END:
                break;
        }
    }

    cout << "Ending game" << endl;

    return 0;
}