#pragma once
#include "types.h"
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
    static Item* createPotion(string name, welltype heal = 1u, itemCount quant = 1u, Buff* buff = nullptr) {
        if(quant == 0) quant = 1;
        Item* temp_item = new Item(new Potion(name, heal, (quant == 0) ? 1 : quant, buff));
        return temp_item;
    }

    // update when there is an inventory
    bool equip(Item* item_to_equip, playerCharacter* p_char) {
        if(!item_to_equip)
            return false;
        if(!item_to_equip->getData())
            return false;

        Armour* armour = dynamic_cast<Armour*>(item_to_equip->_data);
        if(armour) {
            // equip armour
            unsigned long long slot_num = (unsigned long long)armour->Slot;

            if(p_char->equippedArmour[slot_num]) {
                // delete old data
                delete p_char->equippedArmour[slot_num];
                p_char->equippedArmour[slot_num] = nullptr;
                p_char->equippedArmour[slot_num] = item_to_equip; // equip new
            } else {
                p_char->equippedArmour[slot_num] = item_to_equip; // equip new
            }

            return true;
        }
        Weapon* weapon = dynamic_cast<Weapon*>(item_to_equip->_data);
        if(weapon) {
            // equip weapon
            unsigned long long slot_num = (unsigned long long)weapon->Slot;

            if(p_char->equippedWeapons[slot_num]) {
                // delete old data
                delete p_char->equippedWeapons[slot_num]; // move to inventory later
                p_char->equippedWeapons[slot_num] = nullptr;
                // equip new
                p_char->equippedWeapons[slot_num] = item_to_equip;
            } else {
                // equip new
                p_char->equippedWeapons[slot_num] = item_to_equip;
            }
            return true;
        }

        return false;
    }
    
    // update when there is an inventory
    bool use(Item* item_to_use, playerCharacter* p_char) {
        if(!item_to_use)
            return false;
        if(!item_to_use->getData())
            return false;
        
        Potion* potion = dynamic_cast<Potion*>(item_to_use->_data);
        if(potion){
            // apply buff if there is one
            if(potion->buff) {
                p_char->applyBuff(*potion->buff);
            }

            // if full health and trying to use heal potion, don't use potion
            if(p_char->pcClass->HP->isFull() && !potion->buff)
                return false; // don't use potion

            // increse hp by amount potion heals (could be 0, that's fine)
            p_char->pcClass->HP->increaseCurrent(potion->healAmount);
            
            // potion used, reduce quantity
            potion->Quantity--;
            if(potion->Quantity == 0) {
                delete potion;
            }
            return true;
        }
        return false;
    }
};