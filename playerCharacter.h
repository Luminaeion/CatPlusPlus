#include <cstdint>
#include <vector>
#include <memory>

#include "stats.h"
#include "pointWell.h"
#include "ability.h"
#include "types.h"
#include "item.h"

class playerCharacterDelegate : public Stats {
public:
    static const exptype lvl2 = 100u;

    playerCharacterDelegate() : Stats(0u) { 
        CurrentLVL = (lvltype)1u; 
        CurrentEXP = (exptype)0u;
        EXPtoLvlup = lvl2;
        HP = make_unique<pointWell>(1u, 1u);
    }

    void gainEXP(exptype gained_exp) {
        CurrentEXP += gained_exp;
        while(check_if_leveled()) {}
    }

    lvltype getLvl() { return CurrentLVL; }
    exptype getCurrentEXP() { return CurrentEXP; }
    exptype getExptoLvlup() { return EXPtoLvlup; }

    void applyBuff(Buff b){
        for(auto& buff : Buffs) {
            // if buff exists, just refresh duration
            if (b.Name == buff.Name) {
                buff.Duration = b.Duration;
                return;
            }
        }
        newBuff(b);
    }

    virtual void lvlUp() = 0;
    virtual string getClassName() = 0;

    unique_ptr<pointWell> HP;
    unique_ptr<pointWell> MP;

    vector<Ability> Abilities;
    vector<Buff> getBuffList() {
        return Buffs;
    }

protected:
    lvltype CurrentLVL;
    exptype CurrentEXP;
    exptype EXPtoLvlup;

    bool check_if_leveled(){
        static const lvltype lvlScalar = 2u;
        if(CurrentEXP >= EXPtoLvlup) {
            CurrentLVL++;
            lvlUp();
            EXPtoLvlup *= lvlScalar;
            return true;
        }
        return false;
    }
};

#define PCCONSTRUCT\
        HP->setMax(BaseHP);\
        HP->increaseCurrent(BaseHP);\
        if(MP) { \
            MP->setMax(BaseMP);\
            MP->increaseCurrent(BaseMP);\
        }\
        increaseStats(BaseStr, BaseInt, BaseAgi);

#define LEVELUP \
        HP->setMax((welltype)(BaseHP / 2.f) + HP->getMax());\
        HP->increaseCurrent((welltype)(BaseHP / 2.f));\
        if (MP) { \
            MP->setMax((welltype)(BaseMP / 2.f) + MP->getMax());\
            MP->increaseCurrent((welltype)(BaseMP / 2.f));\
        }\
        increaseStats((stattype)((BaseStr + 1u) / 2.f), (stattype)((BaseInt + 1u) / 2.f), (stattype)((BaseAgi + 1u) / 2.f));

// --- CHARACTER (rpg)CLASS BEGIN ---

class Cat : public playerCharacterDelegate {
public:
    static const welltype BaseHP = (welltype)14;
    static const stattype BaseStr = (stattype)2;
    static const stattype BaseInt = (stattype)4;
    static const stattype BaseAgi = (stattype)7;
    static const welltype BaseMP = (welltype)10u;
    string getClassName() override { return string("Cat"); }
    Cat() : playerCharacterDelegate() {
        MP = make_unique<pointWell>(); // make sure to init before PCCONSTRUCT macro
        PCCONSTRUCT 

        // character has this ability by default
        Abilities.emplace_back("Purr", 2u, 1u, abilityTarget::SELF, 7u, abilityScaler::INT);
    }
private:
 void lvlUp() override{
    LEVELUP 
    if(CurrentLVL == 2){
        // gain new ability :D
        Abilities.emplace_back("Swipe", 2u, 2u, abilityTarget::ENEMY, 5u, abilityScaler::STR);
        cout << "- GAINED NEW ABILITY SWIPE -" << endl;

        // Stat boosts for lvlups can be done like this:
        /*
        MP->setMax(1u + MP->getMax());
        MP->increaseCurrent(1u);

        increaseStats(0, 1);
        */
    }
}
};

// --- CHARACTER (rpg)CLASS END ---

class playerCharacter {
private:
    playerCharacterDelegate* pcClass;
    EquipmentDelegate* equippedArmour[(unsigned long long)ARMOURSLOT::NUM_SLOTS];
    EquipmentDelegate* equippedWeapons[(unsigned long long)WEAPONSLOT::NUM_SLOTS];

public:
    playerCharacter(playerCharacterDelegate* pc) : pcClass(pc) {
        auto i = 0;
        for(i = 0; i < (unsigned long long)ARMOURSLOT::NUM_SLOTS; i++) {
            equippedArmour[i] = nullptr;
        }
        for(i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
            equippedWeapons[i] = nullptr;
        }
    }
    ~playerCharacter() { 
        delete pcClass; 
        pcClass = nullptr; 
        auto i = 0;
        for(i = 0; i < (unsigned long long)ARMOURSLOT::NUM_SLOTS; i++) {
            if(equippedArmour[i]) {
            delete equippedArmour[i];
            equippedArmour[i] = nullptr;
            }
        }
        for(i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
            if(equippedWeapons[i]) {
            delete equippedWeapons[i];
            equippedWeapons[i] = nullptr;
            }
        } 
        }

    // class name
    string getClassName() { return pcClass->getClassName(); }
    
    // lvl
    lvltype getLvl() { return pcClass->getLvl(); }
    exptype getCurrentEXP() { return pcClass->getCurrentEXP(); }
    exptype getExptoLvlup() { return pcClass->getExptoLvlup(); }

    // hp & mp
    welltype getCurrentHP() { return pcClass->HP->getCurrent(); }
    welltype getMaxHP() { return pcClass->HP->getMax(); }

    // check if character has mp
    welltype getCurrentMP() { 
      if(pcClass->MP)
        return pcClass->MP->getCurrent();
      else
        return 0;
    }
    welltype getMaxMP() { 
      if(pcClass->MP)
        return pcClass->MP->getMax(); 
      else
        return 0;
    }

    // getters
    // base stats
    stattype getBaseStrength() { return pcClass->getBaseStrength(); }
    stattype getBaseIntellect() { return pcClass->getBaseIntellect(); }
    stattype getBaseAgility() { return pcClass->getBaseAgility(); }
    stattype getBaseDefence() { return pcClass->getBaseDefence(); }
    stattype getBaseResistance() { return pcClass->getBaseResistance(); }

    // total stats (stats + buffs)
    stattype getTotalStrength() { return pcClass->getTotalStrength(); }
    stattype getTotalIntellect() { return pcClass->getTotalIntellect(); }
    stattype getTotalAgility() { return pcClass->getTotalAgility(); }
    stattype getTotalDefence() { 
        // get all def from equipped armour
        stattype armourDef = 0;
        for(auto i = 0; i < (unsigned long long)ARMOURSLOT::NUM_SLOTS; i++) {
            if(equippedArmour[i]) {
                armourDef += equippedArmour[i]->Stats.Def;
            }
        }

        return pcClass->getTotalDefence() + armourDef; 
        
        }
    stattype getTotalResistance() { 
        stattype armourRes = 0;
        for(auto i = 0; i < (unsigned long long)ARMOURSLOT::NUM_SLOTS; i++) {
            if(equippedArmour[i]) {
                armourRes += equippedArmour[i]->Stats.Res;
            }
        }
        return pcClass->getTotalResistance() + armourRes; 
        }

    vector<Ability> getAbilityList() { return pcClass->Abilities; }
    vector<Buff> getBuffList() { return pcClass->getBuffList(); }

    // terrible but works..
    EquipmentDelegate* getEquippedArmour(unsigned long long i) { 
        return (dynamic_cast<Armour*>(equippedArmour[i]));
    }

    EquipmentDelegate* getEquippedWeapon(unsigned long long i) { 
        return (dynamic_cast<Weapon*>(equippedWeapons[i]));
    }
    
    // modifiers
    void gainEXP(exptype amt) { pcClass->gainEXP(amt); }
    void takeDmg(welltype amt) { pcClass->HP->reduceCurrent(amt); }
    void heal(welltype amt) { pcClass->HP->increaseCurrent(amt); }

    void applyBuff(Buff buff) {
        pcClass->applyBuff(buff);
    }

    // update when there is an inventory
    bool equip(Item* item_to_equip) {
        if(!item_to_equip)
            return false;
        if(!item_to_equip->getData())
            return false;

        Armour* armour = dynamic_cast<Armour*>(item_to_equip->_data);
        if(armour) {
            // equip armour
            unsigned long long slot_num = (unsigned long long)armour->Slot;

            if(equippedArmour[slot_num]) {
                // delete old data
                delete equippedArmour[slot_num];
                equippedArmour[slot_num] = nullptr;
                // equip new
                equippedArmour[slot_num] = armour;
            } else {
                // equip new
                equippedArmour[slot_num] = armour;
            }

            return true;
        }
        Weapon* weapon = dynamic_cast<Weapon*>(item_to_equip->_data);
        if(weapon) {
            // equip weapon
            unsigned long long slot_num = (unsigned long long)weapon->Slot;

            if(equippedWeapons[slot_num]) {
                // delete old data
                delete equippedWeapons[slot_num]; // move to inventory later
                equippedWeapons[slot_num] = nullptr;
                // equip new
                equippedWeapons[slot_num] = weapon;
            } else {
                // equip new
                equippedWeapons[slot_num] = weapon;
            }
            return true;
        }

        return false;
    }
    
    // deleted constructors
    playerCharacter() = delete;
    playerCharacter(const playerCharacter&) = delete;
    playerCharacter(const playerCharacter&&) = delete;
};