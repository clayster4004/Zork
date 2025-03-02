#include "game.h"
#include <stdexcept>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <string>

Game::Game() : currentLocation("Default Location", "Default Description"){
    commands = setupCommands();
    createWorld();
}

// Used ChatGPT to write this lowercase function
std::string toLower(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return result;
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
            tokens.push_back(toLower(token));
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

    // Add the voice lines to the characters
    npcClay->addMessage("Hello there");
    npcSmeech->addMessage("Hello there");
    npcSteb->addMessage("Hello there");
    npcScar->addMessage("Hello there");
    npcTwitch->addMessage("Hello there");
    npcMord->addMessage("Hello there");
    npcElise->addMessage("Hello there");
    npcPowder->addMessage("Hello there");

    // Create all the Items
    Item* itemAle = new Item("Ale", "Dark in color, a scotch ale perhaps", 100, 7.5);
    Item* itemWine = new Item("Wine", "A bottle of Snoop Dogg's Cali Red", 150, 5);
    Item* itemVodka = new Item("Vodka", "A shot of Kirkland vodka, doesn't get much worse that that", 50, 2.5);
    Item* itemBrandy = new Item("Brandy", "I've never had brandy, although it smells disgusting", 50, 5);
    Item* itemLager = new Item("Lager", "Doesn't ever single one of these taste the same?", 50, 7.5);
    Item* itemMead = new Item("Mead", "Where does one even buy mead?", 50, 5);
    Item* itemCocktail = new Item("Cocktail", "It has an umbrella in it, must be good...", 200, 7.5);
    Item* itemOrb = new Item("Orb", "You've unlocked a secret!", 0, 10);
    Item* itemBat = new Item("Bat", "Man, I miss baseball.", 0, 30);

    // Place the npcs and the items in the locations
    locationMac->addNpc(*npcClay);
    locationMac->addItem(*itemAle);
    locationMac->addItem(*itemBat);

    locationManitou->addNpc(*npcSmeech);
    locationManitou->addItem(*itemWine);

    locationKirkhof->addNpc(*npcSteb);
    locationKirkhof->addItem(*itemVodka);

    locationKindschi->addNpc(*npcScar);
    locationKindschi->addItem(*itemBrandy);

    locationRec->addNpc(*npcTwitch);
    locationRec->addItem(*itemLager);

    locationClockTower->addNpc(*npcMord);
    locationClockTower->addItem(*itemMead);

    locationLibrary->addNpc(*npcElise);
    locationLibrary->addItem(*itemCocktail);

    locationWoods->addNpc(*npcPowder);
    locationWoods->addItem(*itemOrb);

    // Add the locations relations to one another
    locationWoods->addLocation("west", std::ref(*locationMac));

    locationMac->addLocation("east", std::ref(*locationWoods));
    locationMac->addLocation("south", std::ref(*locationManitou));

    locationManitou->addLocation("north", std::ref(*locationMac));
    locationManitou->addLocation("west", std::ref(*locationKindschi));

    locationKindschi->addLocation("east", std::ref(*locationManitou));
    locationKindschi->addLocation("south", std::ref(*locationClockTower));
    locationKindschi->addLocation("west", std::ref(*locationRec));

    locationRec->addLocation("east", std::ref(*locationKindschi));

    locationClockTower->addLocation("north", std::ref(*locationKindschi));
    locationClockTower->addLocation("south", std::ref(*locationKirkhof));

    locationKirkhof->addLocation("north", std::ref(*locationClockTower));
    locationKirkhof->addLocation("west", std::ref(*locationLibrary));

    locationLibrary->addLocation("east", std::ref(*locationKirkhof));

    // Put all the locations on the location vec
    locations.push_back(*locationMac);
    locations.push_back(*locationManitou);
    locations.push_back(*locationKindschi);
    locations.push_back(*locationRec);
    locations.push_back(*locationClockTower);
    locations.push_back(*locationKirkhof);
    locations.push_back(*locationLibrary);
    locations.push_back(*locationWoods);
    
    this->currentLocation = randomLocation();
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
    commands["where"] = [this](std::vector<std::string> target) { this->look(target); };
    commands["warp"] = [this](std::vector<std::string> target) { this->warp(target); };
    
    return commands;

}


void Game::showHelp(std::vector<std::string> target) {
    std::cout << std::endl << "* - May require special condidtions to be met" << std::endl;
    std::string commandPattern = "You're input will be broken up into [Command][Object]";
    std::cout << commandPattern << std::endl << std::endl;

    std::cout << "Available Commands:" << std::endl;
    std::cout << "  talk        - Converse with the characters in any room." << std::endl;
    std::cout << "  meet        - Display a description of the type of ... creature." << std::endl;
    std::cout << "  take        - Place an item in your backpack to carry it around." << std::endl;
    std::cout << "  give        - Leave an item in a room ... or give to certain characters." << std::endl;
    std::cout << "  go          - Follow this with a direction to travel to new locations." << std::endl;
    std::cout << "  warp        - *Follow this with a location to warp directly there." << std::endl;

    std::cout << std::endl << "Stand Alone Commands:" << std::endl;
    std::cout << "  help (h)    - Display this directive." << std::endl;
    std::cout << "  quit (q)    - Exit the game." << std::endl;
    std::cout << "  backpack    - Displays the carried items." << std::endl;
    std::cout << "  items       - Alias for backpack." << std::endl;
    std::cout << "  look/where  - Get an idea of your surroundings." << std::endl;
    std::cout << std::endl;
}


void Game::talk(std::vector<std::string> target) {
    if (target.empty()) {
        std::cout << "Talk to whom?" << std::endl;
        return;
    }
    
    std::string npcName = target[0];
    
    // Use the non-const accessor to get the actual NPCs
    std::vector<Npc>& npcs = currentLocation.getNpcsRef();
    
    bool found = false;
    for (auto &npc : npcs) {
        if (toLower(npc.getName()) == npcName) {
            std::string message = npc.getMessage();
            std::cout << npc.getName() << " says:" << std::endl
                      << message << std::endl << std::endl;
            found = true;
            break;
        }
    }
    
    if (!found) {
        std::cout << "There is no one named \"" << npcName << "\" here." << std::endl;
    }
}


void Game::meet(std::vector<std::string> target) {
    //std::cout << "meet" << std::endl;
    if (target.empty()) {
        std::cout << "Who are we meeting...?" << std::endl;
        return;
    }
    std::string npcName = target[0];

    std::vector<Npc> npcs = currentLocation.getNpcs();

    bool found = false;
    for (const auto& npc: npcs) {
        if (toLower(npc.getName()) == npcName) {
            std::cout << npc.getDesc() << std::endl << std::endl;
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "No one by that name is here." << std::endl;
    }

}


void Game::take(std::vector<std::string> target) {
    // std::cout << "take" << std::endl;
    if (target.empty()) {
        std::cout << "Take what?" << std::endl;
        return;
    }

    std::string itemName = target[0];
    
    // Get a reference to the current location's items.
    // If your getItems() returns by value, you'll need to change it so that you can modify the vector.
    std::vector<Item>& locItems = currentLocation.getItemsRef();
    
    bool found = false;
    for (auto it = locItems.begin(); it != locItems.end(); ++it) {
        if (toLower(it->getName()) == itemName) {
            itemWeight += it->getWeight();
            // Item found: add it to the game inventory.
            items.push_back(*it);
            // Remove the item from the location.
            locItems.erase(it);
            std::cout << "You picked up " << itemName << "." << std::endl << std::endl;
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "There is no " << itemName << " here." << std::endl;
    }
}


void Game::give(std::vector<std::string> target) {
    // std::cout << "give" << std::endl;
    if (target.empty()) {
        std::cout << "Give what?" << std::endl;
        return;
    }

    std::string itemName = target[0];

    // Search the player's inventory for the item.
    auto it = std::find_if(items.begin(), items.end(),
                           [&](const Item &i) { return toLower(i.getName()) == itemName; });
    if (it == items.end()) {
        std::cout << "You don't have a " << itemName << "." << std::endl << std::endl;
        return;
    }

    // Found the item. Save a copy (or you could move it if C++11 move semantics apply).
    Item item = *it;
    
    // Decrease the carried weight by the item's weight.
    itemWeight -= item.getWeight();

    // Remove the item from the player's inventory.
    items.erase(it);

    // Now check if the current location is the woods.
    if (currentLocation.getName() == "Woods Behind Campus") {
        // Check if the item is edible. Here, we assume that an edible item has positive calories.
        if (item.getNumCals() > 0) {
            // If edible, reduce the calories needed.
            neededCals -= item.getNumCals();
            std::cout << "You fed Powder with " << item.getName() 
                      << ". Calories reduced by " << item.getNumCals() << "." << std::endl;

            // Check if the requirement has been met
            if (neededCals <= 0) {
                std::cout << "You win!" << std::endl;
                std::exit(0);
            }
        } else {
            // If not edible, transport the player to a new random location.
            currentLocation = randomLocation();
            std::cout << "That item is not edible! You are transported to " 
                      << currentLocation.getName() << "." << std::endl;
        }
    } else {
        // Add the item to the current location's inventory.
        currentLocation.getItemsRef().push_back(item);
        // For other locations, simply confirm the item was given.
        std::cout << "You gave " << item.getName() << " to the current location." << std::endl;
    }

}


void Game::go(std::vector<std::string> target) {
    if (itemWeight >= 30) {
        std::cout << "You are too heavy to move! Please drop some items." << std::endl;
        return;
    }

    if (target.empty()) {
        std::cout << "You didn't tell me where we are going..." << std::endl;
        return;
    }

    // Take the first token to signal the direction in which you want to travel
    std::string direction = target[0];

    auto neighbors = currentLocation.getLocations();
    auto it = neighbors.find(direction);

    if (it != neighbors.end()) {
        it->second.get().setVisited();
        currentLocation = it->second.get();
        std::cout << "You have traveled " << direction << " to " << currentLocation.getName() 
                  << "." << std::endl << std::endl;
    } else {
        std::cout << "Invalid Command" << std::endl;
    }
}


void Game::showItems(std::vector<std::string> target) {
    if (items.empty()) {
        std::cout << "There are no items." << std::endl << std::endl;
        return;
    }

    std::cout << "Items:" << std::endl;
    for (const auto& item : items) {
        std::cout << " - " << item << std::endl << std::endl;
    }
}


void Game::look(std::vector<std::string> target) {
    std::cout << currentLocation << std::endl;
}


void Game::warp(std::vector<std::string> target) {
    // Check if the orb is in the player's inventory.
    auto orbIt = std::find_if(items.begin(), items.end(),
                               [&](const Item &i) { 
                                   return toLower(i.getName()) == "orb"; 
                               });
    if (orbIt == items.end()) {
        std::cout << "You don't have the orb. You cannot warp!" << std::endl;
        return;
    }

    // Ensure a target location was provided.
    if (target.empty()) {
        std::cout << "Warp where?" << std::endl;
        return;
    }
    
    // The first token is the target location name.
    std::string warpTarget = target[0];  // Already lowercased if tokenizeInput does that
    bool found = false;
    
    // Search through the locations vector.
    for (auto &locRef : locations) {
        // Compare stored location name (converted to lowercase) with the warp target.
        if (toLower(locRef.get().getName()) == warpTarget) {
            // Found the location. Update currentLocation.
            currentLocation = locRef.get();
            currentLocation.setVisited();  // Mark as visited
            std::cout << "Warping to " << currentLocation.getName() << "!" << std::endl;
            found = true;
            break;
        }
    }
    
    if (!found) {
        std::cout << "No such location: " << warpTarget << std::endl;
    }
}


void Game::quit(std::vector<std::string> target) {
    std::exit(0);
}


// Written by ChatGPT
Location& Game::randomLocation() {
    if (locations.empty()) {
        throw std::runtime_error("No locations available.");
    }
    
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, locations.size() - 1);
    
    int index = dis(gen);
    return locations[index].get();
}


void Game::play() {
    std::string response;

    while (gameContinue) {
        std::cout << "-> ";
        std::getline(std::cin, response);
        // Checks the function to define the type at compile time
        auto tokenizedResponse = tokenizeInput(response);
        // If its blank, continue the loop
        if (tokenizedResponse.empty()) continue;

        std::string userCommand = tokenizedResponse[0];
        // https://stackoverflow.com/questions/40656871/remove-from-the-beginning-of-stdvector
        tokenizedResponse.erase(tokenizedResponse.begin());

        // Look up the command in the commands map.
        auto cmdIt = commands.find(userCommand);
        if (cmdIt != commands.end()) {
            cmdIt->second(tokenizedResponse);
        } else {
            std::cout << "Unknown command: " << userCommand << std::endl;
        }
    } 
}