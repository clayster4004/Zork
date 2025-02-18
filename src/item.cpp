#include "item.h"
#include <stdexcept>

// Shows the implementation of the item.h file
// Call the setters upon initialization to ensure appropriate error handling
Item::Item(const std::string& name, const std::string& desc, int numCals, float weight) {
  setName(name);
  setDesc(desc);
  setNumCals(numCals);
  setWeight(weight);
}

// Setters w/ error handling
void Item::setName(const std::string& newName) {
    if (newName.empty()) {
        throw std::invalid_argument("Error -> Blank Name");
    }
    this->name = newName;
}

void Item::setDesc(const std::string& newDesc) {
    if (newDesc.empty()) {
        throw std::invalid_argument("Error -> Blank Desc");
    }
    this->desc = newDesc;
}

void Item::setNumCals(int newNumCals) {
    if (newNumCals < 0 || newNumCals > 5000) {
        throw std::invalid_argument("Error -> Cals not [0, 500]");
    }
    this->numCals = newNumCals;
}

void Item::setWeight(float newWeight) {
    if (newWeight <= 0 || newWeight >= 500) {
        throw std::invalid_argument("Error -> Weight not (0, 500)");
    }
    this->weight = newWeight;
}

// Getters
// This is marked as const because it is not modifying an objects state
std::string Item::getName() const {
    return this->name;
}

std::string Item::getDesc() const {
    return this->desc;
}

int Item::getNumCals() const {
    return this->numCals;
}

float Item::getWeight() const {
    return this->weight;
}

// Overloaded Stream Opterator
std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << item.name << " (" << item.numCals << " calories" << ") - " 
       << item.weight << " lbs - " << item.desc;
    return os;
}
