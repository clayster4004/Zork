// This is the main file for GVZork written in C++.
#include <iostream>
#include "item.h"
#include "npc.h"
#include "location.h"
#include "game.h"

int main() {
    
    Game* myGame = new Game();
    myGame->play();

    return 0;
}