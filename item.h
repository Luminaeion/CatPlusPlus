#pragma once
#include "corestats.h"
#include "buff.h"
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
    Potion(std::string name, welltype hp_heal = 1u, itemCount quant = 1u, Buff* buf = nullptr) : ItemDelegate(name), healAmount(hp_heal), Quantity(quant), buff(buf) {}

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

enum class ARMOURSLOT { HEAD, CHEST, LEGS, FEET, HANDS, RING1, RING2, NECK, NUM_SLOTS }; // num_slots for making arrays, chill
// this class can't be inherited
class Armour final : public EquipmentDelegate {
public: 
    ARMOURSLOT Slot;
    GETTYPE

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
    bool checkIfMarkedForDeletion() const { return marked_for_deletion; }
private:
    bool marked_for_deletion = false;
    Item(ItemDelegate* item) : _data(item) {}
    friend class itemManager;
    friend class PlayerCharacter;

    friend std::ostream& operator<<(std::ostream& os, const Item& t) {
    Armour* tmp_cast = dynamic_cast<Armour*>(t._data);
    if (tmp_cast) {
      return os << tmp_cast->Name << "(Def: " << tmp_cast->Stats.Def << ", Res: " << tmp_cast->Stats.Res << ')';
    }
    Weapon* tmp_cast2 = dynamic_cast<Weapon*>(t._data);
    if (tmp_cast2) {
      return  os << tmp_cast2->Name << "(Dmg: " << tmp_cast2->minDMG << '-' << tmp_cast2->maxDMG << ')';
    }
    Potion* tmp_cast3 = dynamic_cast<Potion*>(t._data);
    if (tmp_cast3) {
      return os << tmp_cast3->Name << '(' << tmp_cast3->Quantity << ')';
    }
    return os;
  }

};