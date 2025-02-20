#ifndef GAME_H
#define GAME_H

#include "item.h"
#include "npc.h"
#include "location.h"
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <functional>

// Define "Command" as a type function that returns nothing and takes a vec of str
// Asked ChatGPT how to create an alias using complete namespaces
// It told me to typedef Command to create the type I want
typedef std::function<void(std::vector<std::string>)> Command;

// This class will hold all the logic for the game instance
class Game {
    public:
        // Will need to hold a cmd list, item list, int weight, vector of locations
        // that exist in the world, var current location, int numCals for elf
        // bool gameDone

        // Constructor needs nothing initially
        Game();

        // Initialize getters
        // Initialize setters

        // Additional Functions
        std::map<std::string, Command> setupCommands();
        static void showHelp(std::vector<std::string> args);
        void createWorld();
        Location randomLocation();

        void play();

    private:
        std::map<std::string, Command> commands;
        std::vector<Item> items;
        int itemWeight;
        std::vector<std::reference_wrapper<Location>> locations;
        Location currentLocation;
        int neededCals = 500;
        bool gameContinue = true;

};



#endif