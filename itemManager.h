#pragma once
#include "item.h"
#include "item.cpp"

class itemManager {
public: 
    static Item* createArmour(string name, coreStats cstats, ARMOURSLOT slot) {
        Item* temp_item = new Item(new Armour(name, cstats, slot));
        return temp_item;
    }

    static Item* createWeapon(string name, coreStats cstats, WEAPONSLOT slot, dmgtype min, dmgtype max, bool twohanded = false) {
        Item* temp_item = new Item(new Weapon(name, cstats, slot, min, max, twohanded));
        return temp_item;
    }

    // makes at least 1 potion
    static Item* CreatePotion(string name, welltype heal = 1u, itemCount quant = 1u, Buff* buff = nullptr) {
        if(quant == 0) quant = 1;
        Item* temp_item = new Item(new Potion(name, heal, (quant == 0) ? 1 : quant, buff));
        return temp_item;
    }
};