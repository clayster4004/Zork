#ifndef NPC_H
#define NPC_H

#include <string>
#include <iostream>
#include <vector>

class Npc {
    public:
        // Constructor accepts name and description
        // name and desc will be refs
        Npc(const std::string& name, const std::string& desc);

        // Initialize getters -- only name and desc
        std::string getName() const;
        std::string getDesc() const;

        // Initialize setters
        void setName(const std::string& newName);
        void setDesc(const std::string& newDesc);

        // Additional functions
        // Cannot mark as const because it'll update member vars
        // Not a friend because it is a member funciton 
        std::string getMessage();
        void addMessage(const std::string& newMessage);

        // Overloaded Stream Operator
        friend std::ostream& operator<<(std::ostream& os, const Npc& npc);

    private:
        std::string name;
        std::string desc;
        int messageNum = 0;
        std::vector<std::string> messageVec;

};

#endif