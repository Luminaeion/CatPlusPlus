#pragma once
#include "corestats.h"
#include <string>
#include <typeinfo>

class ItemDelegate {
public:
    std::string Name;
    virtual const char* getType() = 0;
protected:
    ItemDelegate(std::string name) : Name(name) {}
};

#define GETTYPE const char* getType() override { return typeid(*this).name(); };

class Potion final : public ItemDelegate {
public:
    welltype healAmount;
    itemCount Quantity;
    Buff* buff;
    GETTYPE

    ~Potion() {
        if(buff)
            delete buff;
    }
private:
    Potion(string name, welltype hp_heal = 1u, itemCount quant = 1u, Buff* buf = nullptr) : ItemDelegate(name), healAmount(hp_heal), Quantity(quant), buff(buf) {}

    friend class itemManager;
};

class EquipmentDelegate : public ItemDelegate {
public:
  const std::uint32_t UniqueId;
  coreStats Stats;
protected:
  EquipmentDelegate(std::string name, coreStats cstats);
private:
};

enum class ARMOURSLOT { HELMET, CHEST, LEGS, BOOTS, GLOVES, RING1, RING2, NECK, NUM_SLOTS }; // num_slots for making arrays, chill

// this class can't be inherited
class Armour final : public EquipmentDelegate {
public: 
    ARMOURSLOT Slot;
    const char* getType() override { return typeid(*this).name(); }

private:
    // legal way to create armour
    Armour(std::string name, coreStats cstats, ARMOURSLOT slot) : EquipmentDelegate(name, cstats), Slot(slot) {}

    // illegal ways to create armour disabled
    Armour() = delete; // no pre-existing
    Armour(const Armour&) = delete; // no copying
    Armour(const Armour&&) = delete; // no moving

    friend class itemManager;
};

enum class WEAPONSLOT { MELEE, RANGED, NUM_SLOTS };
class Weapon final : public EquipmentDelegate {
public:
    WEAPONSLOT Slot;
    dmgtype minDMG;
    dmgtype maxDMG;
    bool is2H;
    GETTYPE
    
private:
    Weapon(std::string name, coreStats cstats, WEAPONSLOT slot, dmgtype min, dmgtype max,  bool twohanded = false) : EquipmentDelegate(name, cstats), Slot(slot), minDMG(min), maxDMG(max), is2H(twohanded) {}

    Weapon() = delete; // no pre-existing
    Weapon(const Weapon&) = delete; // no copying
    Weapon(const Weapon&&) = delete; // no moving

    friend class itemManager;
};

// use this one in runtime code
class Item {
public:
    ItemDelegate* _data;
    const ItemDelegate* getData() { return _data; }
    ~Item() {
        if(_data) {
            delete _data;
            _data = nullptr;
        }
    }
private:
    Item(ItemDelegate* item) : _data(item) {}
    friend class itemManager;
    friend class PlayerCharacter;
};