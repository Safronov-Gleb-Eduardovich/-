#include "Item.h"
#include <algorithm>

Item::Item(std::string name, int charges)
    : name(name), maxCharges(charges), currentCharges(charges) {}

std::string Item::getName() const {
    return name;
}

int Item::getCharges() const {
    return currentCharges;
}

int Item::getMaxCharges() const {
    return maxCharges;
}

bool Item::use() {
    if (currentCharges > 0) {
        currentCharges--;
        return true;
    }
    return false;
}

void Item::recharge(int amount) {
    currentCharges = std::min(maxCharges, currentCharges + amount);
}