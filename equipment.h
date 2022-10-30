#include <string>
#include <typeinfo>

#include "types.h"
#include "corestats.h"

class Equipment {
public:
    std::string Name;
    coreStats Stats;
    virtual const char* getType() = 0;

protected:
    Equipment(std::string name, coreStats cstats) : Name(name), Stats(cstats) {}

private:
};

enum class ARMOURSLOT { HELMET, CHEST, LEGS, BOOTS, GLOVES, RING1, RING2, NECK, NUM_SLOTS }; // num_slots for making arrays, chill

// this class can't be inherited
class Armour final : public Equipment {
public: 
    ARMOURSLOT Slot;

    // legal way to create armour
    Armour(std::string name, coreStats cstats, ARMOURSLOT slot) : Equipment(name, cstats), Slot(slot) {}

    const char* getType() override { return typeid(*this).name(); }

    // illegal ways to create armour disabled
    Armour() = delete; // no pre-existing
    Armour(const Armour&) = delete; // no copying
    Armour(const Armour&&) = delete; // no moving

private:
};

enum class WEAPONSLOT { MELEE, RANGED,NUM_SLOTS };

class Weapon final : public Equipment {
public:
    WEAPONSLOT Slot;
    dmgtype minDMG;
    dmgtype maxDMG;
    bool is2H;
    Weapon(std::string name, coreStats cstats, WEAPONSLOT slot, dmgtype min, dmgtype max,  bool twohanded = false) : Equipment(name, cstats), Slot(slot), minDMG(min), maxDMG(max), is2H(twohanded) {

    }
    const char* getType() override { return typeid(*this).name(); };

    Weapon() = delete; // no pre-existing
    Weapon(const Weapon&) = delete; // no copying
    Weapon(const Weapon&&) = delete; // no moving
};