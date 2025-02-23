#include "game.h"
#include <stdexcept>
#include <vector>
#include <sstream>

Game::Game() : currentLocation("Default Location", "Default Description"){
    commands = setupCommands();
    createWorld();
}

// Used ChatGPT to help me generate this method, C++ should include a split function...
std::vector<std::string> tokenizeInput(const std::string& userInput) {
    // Define the delimiter
    char delimiter = ' ';
    std::vector<std::string> tokens;
    std::string token;
    // Creates a stream like cin so we can use the getline method
    std::istringstream tokenStream(userInput);

    // Use getline with the delimiter to extract tokens.
    while (std::getline(tokenStream, token, delimiter)) {
        // Only add non-empty tokens (in case of multiple spaces)
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

void Game::createWorld() {
    // Create all the locations in the game
    Location* locationMac = new Location("Macinac", "CS Building");
    Location* locationManitou = new Location("Manitou", "Geology Building");
    Location* locationKirkhof = new Location("Kirkhof", "Student Center");
    Location* locationKindschi = new Location("Kindschi", "I think there's a brewing class in there");
    Location* locationRec = new Location("Recreation Center", "Smells like gym bros");
    Location* locationClockTower = new Location("Clock Tower", "DING-DONG");
    Location* locationLibrary = new Location("Library", "Lots of books...and desks");
    Location* locationWoods = new Location("Woods Behind Campus", "Lots of empty beer cans...");

    // Create all the NPCs
    // Kudos if you play the game !
    Npc* npcClay = new Npc("Clay", "Somehow making it through");
    Npc* npcSmeech = new Npc("Smeech", "Skinny legs, large headed...thing");
    Npc* npcSteb = new Npc("Steb", "That is a very marine looking man...fish...I give up");
    Npc* npcScar = new Npc("Scar", "I wonder what is hiding under the mask");
    Npc* npcTwitch = new Npc("Twitch", "Is that a rat with a crossbow? Seems friendly enough!");
    Npc* npcMord = new Npc("Mordekaiser", "Looks like a medieval knight, except 10 times as big");
    Npc* npcElise = new Npc("Elise", "She can shapesift into a spider, that's pretty cool I guess");
    Npc* npcPowder = new Npc("Powder", "A seemingly normal child among all the beasts");

    // Create all the Items


    locations.push_back(*locationMac);
    this->currentLocation = *locationMac;
}

std::map<std::string, Command> Game::setupCommands() {
    std::map<std::string, Command> commands;

    commands["help"] = showHelp;
    commands["h"] = showHelp;
    commands["quit"] = quit;
    commands["q"] = quit;

    // In order to set this up to work with non-static functions I have to define everything
    // a little differently to work with class instances (even as aliases)
    // This was written with assistance from ChatGPT 
    // This line essentially says that we will pass a target to an instance variable 
    // and call that function on them specifically 
    commands["talk"] = [this](std::vector<std::string> target) { this->talk(target); };
    commands["meet"] = [this](std::vector<std::string> target) { this->meet(target); };
    commands["take"] = [this](std::vector<std::string> target) { this->take(target); };
    commands["give"] = [this](std::vector<std::string> target) { this->give(target); };
    commands["go"] = [this](std::vector<std::string> target) { this->go(target); };
    commands["backpack"] = [this](std::vector<std::string> target) { this->showItems(target); };
    commands["items"] = [this](std::vector<std::string> target) { this->showItems(target); };
    commands["look"] = [this](std::vector<std::string> target) { this->look(target); };
    
    return commands;

}

void Game::showHelp(std::vector<std::string> target) {
    std::cout << "help provided" << std::endl;
}

void Game::talk(std::vector<std::string> target) {
    std::cout << "talk" << std::endl;
}

void Game::meet(std::vector<std::string> target) {
    //TODO
}

void Game::take(std::vector<std::string> target) {
    //TODO
}

void Game::give(std::vector<std::string> target) {
    //TODO
}

void Game::go(std::vector<std::string> target) {
    //TODO
}

void Game::showItems(std::vector<std::string> target) {
    //TODO
}

void Game::look(std::vector<std::string> target) {
    std::cout << currentLocation << std::endl;
}

void Game::quit(std::vector<std::string> target) {
    //TODO
}

void Game::play() {
    std::string response;

    while (gameContinue) {
        std::cout << "-> ";
        std::getline(std::cin, response);
        // Checks the function to define the type at compile time
        auto tokenizedResponse = tokenizeInput(response);

        std::string userCommand = tokenizedResponse[0];
        // https://stackoverflow.com/questions/40656871/remove-from-the-beginning-of-stdvector
        tokenizedResponse.erase(tokenizedResponse.begin());

        // Testing the input, works
        // std::cout << userCommand << std::endl;
        // for (const auto& token : tokenizedResponse) {
        //     std::cout << token << " ";
        // }
        // std::cout << std::endl;

        this->commands[userCommand](tokenizedResponse);
    } 
}