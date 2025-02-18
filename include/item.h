#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

class Item {
    public:
        // Constructor accepts name, desc, numCals, weight
        // name and desc are references and numCals and weight are copies -> most efficient
        Item(const std::string& name, const std::string& desc, int numCals, float weight);

        // Initialize getters
        std::string getName() const;
        std::string getDesc() const;
        int getNumCals() const;
        float getWeight() const;

        // Initialize Setters
        // Only have const when you're referencing 
        void setName(const std::string& newName);
        void setDesc(const std::string& newDesc);
        void setNumCals(int newNumCals);
        void setWeight(float newWeight);

        // Overloaded Stream Operator (Friend declaration because it needs priv vars)
        // return type: ostream, pass in the ostream and a const item ref (non-changeable)
        // This line I got from ChatGPT
        friend std::ostream& operator<<(std::ostream& os, const Item& item);
        

    private:
        std::string name;
        std::string desc;
        int numCals;
        float weight;
};

#endif