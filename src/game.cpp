#include "game.h"
#include <stdexcept>
#include <vector>

Game::Game() : currentLocation("Default Location", "Default Description"){
    commands = setupCommands();
    createWorld();
}

void Game::createWorld() {
    Location* location1 = new Location("Macinac", "CS Building");
    locations.push_back(*location1);
    this->currentLocation = *location1;
}

std::map<std::string, Command> Game::setupCommands() {
    std::map<std::string, Command> commands;
    commands["help"] = &Game::showHelp;

    return commands;

}

void Game::showHelp(std::vector<std::string> args) {
    std::cout << "help provided" << std::endl;
}

void Game::play() {
    std::string response;

    while (gameContinue) {
        std::cout << "->";
        std::cin >> response;

        this->commands[response]({});
    } 
}