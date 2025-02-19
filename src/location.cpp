#include "location.h"
#include <stdexcept>

Location::Location(const std::string& name, const std::string& desc) {
    setName(name);
    setDesc(desc);
}

std::string Location::getName() const {
    return this->name;
}

std::string Location::getDesc() const {
    return this->desc;
}

std::map<std::string, std::reference_wrapper<Location>> Location::getLocations() const {
    return this->neighborsMap;
}

std::vector<Npc> Location::getNpcs() const {
    return this->npcVec;
}

std::vector<Item> Location::getItems() const {
    return this->itemVec;
}

bool Location::getVisited() const {
    return this->hasVisited;
}

// Setters w/ error handling
void Location::setName(const std::string& newName) {
    if (newName.empty()) {
        throw std::invalid_argument("Error -> Blank Name");
    }
    this->name = newName;
}

void Location::setDesc(const std::string& newDesc) {
    if (newDesc.empty()) {
        throw std::invalid_argument("Error -> Blank Desc");
    }
    this->desc = newDesc;
}

void Location::setVisited() {
    this->hasVisited = true;
}

void Location::addLocation(const std::string direction, const std::reference_wrapper<Location> location) {
    neighborsMap.emplace(direction, location);
}

void Location::addNpc(const Npc& npc) {
    npcVec.push_back(npc);
}

void Location::addItem (const Item& item) {
    itemVec.push_back(item);
}

std::ostream& operator<<(std::ostream& os, const Location& location) {
    // The basic information regarding the location
    os << location.name << " - " << location.desc << std::endl << std::endl;

    // The basic information regarding the Npcs
    os << "You see the following NPCs:" << std::endl;
    for (auto it=location.npcVec.begin(); it != location.npcVec.end(); ++it) {
        os << " -" << *it << std::endl;
    }
    os << std::endl;

    // The basic information regarding the items
    os << "You see the following Items:" << std::endl;
    for (auto it=location.itemVec.begin(); it != location.itemVec.end(); ++it) {
        os << " -" << *it << std::endl;
    }
    os << std::endl;

    // The basic information regarding the directions in which you can travel
    os << "You can go in the following Directions: " << std::endl;
    for (const auto& entry : location.getLocations()) {
        if (entry.second.get().getVisited()) {
            os << "- " << entry.first << " - " << entry.second.get() << " (Visited)" << std::endl;
        } else {
            os << " -" << entry.first << " - " << "Unknown" << std::endl;
        }
    }

    return os;
}