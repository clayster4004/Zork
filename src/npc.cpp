#include "npc.h"
#include <stdexcept>

Npc::Npc(const std::string& name, const std::string& desc) {
    setName(name);
    setDesc(desc);
}

// Setters w/ error handling
void Npc::setName(const std::string& newName) {
    if (newName.empty()) {
        throw std::invalid_argument("Error -> Blank Name");
    }
    this->name = newName;
}

void Npc::setDesc(const std::string& newDesc) {
    if (newDesc.empty()) {
        throw std::invalid_argument("Error -> Blank Desc");
    }
    this->desc = newDesc;
}

std::string Npc::getName() const {
    return this->name;
}

std::string Npc::getDesc() const {
    return this->desc;
}

std::string Npc::getMessage() {
    if (messageNum >= messageVec.size()) {
        messageNum = 0;
    }

    std::string message = messageVec[messageNum];
    ++messageNum;
    return message;
}

void Npc::addMessage(const std::string& newMessage) {
    messageVec.push_back(newMessage);
}

std::ostream& operator<<(std::ostream& os, const Npc& npc) {
    os << npc.name;
    return os;
}