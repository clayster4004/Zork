#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "npc.h"
#include "item.h"

class Location
{
    public:
        // Constructor accepts name and description
        // name and desc will be refs
        Location(const std::string &name, const std::string &desc);

        // Initialize getters
        std::string getName() const;
        std::string getDesc() const;
        std::map<std::string, Location> getLocations() const;
        std::vector<Npc> getNpcs() const;
        std::vector<Item> getItems() const;
        bool getVisited() const;

        // Initialize setters
        void setName(const std::string& newName);
        void setDesc(const std::string& newDesc);
        void setVisited();

        // Additional functions
        void addLocation(const std::string& direction, const Location& location);
        void addNpc(const Npc& npc);
        void addItem(const Item& item);

        // Overloaded Stream Operator
        friend std::ostream& operator<<(std::ostream& os, const Location& location);
        

    private:
        std::string name;
        std::string desc;
        bool hasVisited = false;
        std::map<std::string, Location> neighborsMap;
        std::vector<Npc> npcVec;
        std::vector<Item> itemVec;
};

#endif