#pragma once
#include <string>

class Item {
private:
    std::string name;
    int maxCharges;
    int currentCharges;
public:
    Item(std::string name, int charges);
    std::string getName() const;
    int getCharges() const;
    int getMaxCharges() const;
    bool use();
    void recharge(int amount);
};