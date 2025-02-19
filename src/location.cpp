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
    os << location.name << " - " << location.desc;
    return os;
}