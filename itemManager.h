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

static void castItemToPotion(const Item* in, Potion*& out) {
    if(!in) return;
    out = dynamic_cast<Potion*>(in->_data);
}

static bool isPotion(const Item* in) {
    if(dynamic_cast<Potion*>(in->_data)) return true;
    else return false;
}

// update when there is an inventory
static bool equip(Item* item_to_equip, playerCharacter* p_char) {
    if(!item_to_equip->getData() || !item_to_equip || !p_char)
        return false;

    if(isPotion(item_to_equip))
    return false;

    Armour* armour = dynamic_cast<Armour*>(item_to_equip->_data);
    if(armour) {
        // equip armour
        unsigned long long slot_num = (unsigned long long)armour->Slot;

        if(p_char->equippedArmour[slot_num]) {
            p_char->equippedArmour[slot_num]->marked_as_equipped = false;
            moveToBackpack(p_char->equippedArmour[slot_num], p_char);
            p_char->equippedArmour[slot_num] = item_to_equip; // equip new
            item_to_equip->marked_as_equipped = true;
        } else {
            p_char->equippedArmour[slot_num] = item_to_equip; // equip new
            item_to_equip->marked_as_equipped = true;
        }
        cout << item_to_equip->_data->Name << " equipped.\n";
        p_char->cleanup_backpack(); // gets rid of pointers for equipped stuff
        return true;
    }
    Weapon* weapon = dynamic_cast<Weapon*>(item_to_equip->_data);
    if(weapon) {
        // equip weapon
        unsigned long long slot_num = (unsigned long long)weapon->Slot;

        if(p_char->equippedWeapons[slot_num]) {
            p_char->equippedWeapons[slot_num]->marked_as_equipped = false;
            moveToBackpack(p_char->equippedWeapons[slot_num], p_char);
            p_char->equippedWeapons[slot_num] = item_to_equip; // equip new
            item_to_equip->marked_as_equipped = true;
        } else {
            p_char->equippedWeapons[slot_num] = item_to_equip;// equip new
            item_to_equip->marked_as_equipped = true;
        }
        cout << p_char->equippedWeapons[slot_num]->_data->Name << " equipped.\n";
        p_char->cleanup_backpack(); // gets rid of pointers for equipped stuff
        return true;
    }
    return false;
}

static bool use(Item* item_to_use, playerCharacter* p_char) {
    if(!item_to_use || !p_char)
        return false;
    if(!item_to_use->getData())
        return false;
    
    Potion* potion = nullptr;
    castItemToPotion(item_to_use, potion);

    if(potion && potion->Quantity > 0){
        // apply buff if there is one
        if(potion->buff) {
            if(potion->buff->isDebuff) {
                p_char->takeDmg(potion->healAmount);
            }
            p_char->applyBuff(*potion->buff);
        } else {
            // don't use potion if full HP
            if(p_char->isMaxHealth()) { cout << "Your health is full. There is no need to use this item now.\n"; return false; } else { p_char->heal(potion->healAmount); cout << "You healed " << potion->healAmount << " hp!\n"; }}
        // increase hp by amount potion heals (could be 0, that's fine)
        
        // potion used, reduce quantity
        potion->Quantity--;
        if(potion->Quantity == 0) {
            item_to_use->marked_for_deletion = true;
            p_char->cleanup_backpack();
        }
        return true;
    }
    return false;
}

static bool moveToBackpack(Item* item_to_move, playerCharacter* p_char) {
    if(!item_to_move || !p_char)
        return false;
    if(!item_to_move->getData())
        return false;
    p_char->Backpack.push_back(item_to_move);
        return true;
}
};

static bool removeFromBackpack(Item* item_to_remove, playerCharacter* p_char) {
    if(!item_to_remove || !p_char)
        return false;
    if(!item_to_remove->getData())
        return false;
}

static void deleteItem(Item*& item_to_delete) {
        delete item_to_delete;
        item_to_delete = nullptr;
    }