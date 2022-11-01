#pragma once
#include "item.h"
#include "item.cpp"

class itemManager {
public: 
    static Item* createArmour(std::string name, coreStats cstats, ARMOURSLOT slot) {
        Item* temp_item = new Item(new Armour(name, cstats, slot));
        return temp_item;
    }

    static Item* createWeapon(std::string name, coreStats cstats, WEAPONSLOT slot, dmgtype min, dmgtype max, bool twohanded = false) {
        Item* temp_item = new Item(new Weapon(name, cstats, slot, min, max, twohanded));
        return temp_item;
    }
};