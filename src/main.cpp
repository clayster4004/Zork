// This is the main file for GVZork written in C++.
#include <iostream>
#include "item.h"
#include "npc.h"
#include "location.h"
#include "game.h"

int main() {
    // Create a game instance and run the play function
    Game* myGame = new Game();
    myGame->play();
    delete myGame;
    return 0;
}