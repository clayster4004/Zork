// This is the main file for GVZork written in C++.
#include <iostream>
#include "item.h"
#include "npc.h"

int main() {
    Item* myItem = new Item("Bottle", "Just a bottle", 250, 100.5);
    std::cout << *myItem << std::endl;
    delete myItem;

    Npc* myNpc = new Npc("Clay", "Just a guy");
    std::cout << *myNpc << std::endl;
    delete myNpc;

    myNpc->addMessage("Hello There");
    myNpc->addMessage("Seeya later");

    std::cout << myNpc->getMessage() << std::endl;
    std::cout << myNpc->getMessage() << std::endl;
    std::cout << myNpc->getMessage() << std::endl;

    return 0;
}