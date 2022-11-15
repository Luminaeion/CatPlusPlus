#include <cstdint>
#include <vector>
#include <memory>

#include "stats.h"
#include "pointWell.h"
#include "ability.h"
#include "types.h"
#include "item.h"
#include <algorithm>

#include "random.h"

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
        addNewBuff(b);
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
        std::cout << "- GAINED NEW ABILITY SWIPE -" << endl;

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
    Item* equippedArmour[(unsigned long long)ARMOURSLOT::NUM_SLOTS];
    Item* equippedWeapons[(unsigned long long)WEAPONSLOT::NUM_SLOTS];
    vector<Item*> Backpack;
    void cleanup_backpack() {
        const auto to_remove = stable_partition(Backpack.begin(), Backpack.end(), 
        [](const Item* i) -> bool { return !i->checkIfMarkedForDeletion(); }
        );
        for_each(to_remove, Backpack.end(), [](Item* i) { delete i; });
        Backpack.erase(to_remove, Backpack.end());
    }
    friend class itemManager;
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
    string getClassName() const { return pcClass->getClassName(); }
    
    // lvl
    lvltype getLvl() const { return pcClass->getLvl(); }
    exptype getCurrentEXP() const { return pcClass->getCurrentEXP(); }
    exptype getExptoLvlup() const { return pcClass->getExptoLvlup(); }

    // hp & mp
    welltype getCurrentHP() const { return pcClass->HP->getCurrent(); }
    welltype getMaxHP() const { return pcClass->HP->getMax(); }

    // check if character has mp
    welltype getCurrentMP() const { 
      if(pcClass->MP)
        return pcClass->MP->getCurrent();
      else
        return 0;
    }
    welltype getMaxMP() const { 
      if(pcClass->MP)
        return pcClass->MP->getMax(); 
      else
        return 0;
    }

    // getters
    // base stats
    stattype getBaseStrength() const { return pcClass->getBaseStrength(); }
    stattype getBaseIntellect() const { return pcClass->getBaseIntellect(); }
    stattype getBaseAgility() const { return pcClass->getBaseAgility(); }
    stattype getBaseDefence() const { return pcClass->getBaseDefence(); }
    stattype getBaseResistance() const { return pcClass->getBaseResistance(); }

    // total stats (stats + buffs)
    stattype getTotalStrength() const {
        stattype armourStr = 0;
        for (auto i = 0; i < (unsigned long long)ARMOURSLOT::NUM_SLOTS; i++) {
            if (equippedArmour[i]) {
                Armour* armour = dynamic_cast<Armour*>(equippedArmour[i]->_data);
                armourStr += armour->Stats.Def;
            }
        }
        stattype weaponStr = 0;
        for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
            if (equippedWeapons[i]) {
                Weapon* weapon = dynamic_cast<Weapon*>(equippedWeapons[i]->_data);
                weaponStr += weapon->Stats.Str;
            }
        }
        return pcClass->getTotalStrength() + armourStr + weaponStr;
    }
    stattype getTotalIntellect() const
    {
        stattype armourInt = 0;
        for (auto i = 0; i < (unsigned long long)ARMOURSLOT::NUM_SLOTS; i++) {
            if (equippedArmour[i]) {
                Armour* armour = dynamic_cast<Armour*>(equippedArmour[i]->_data);
                armourInt += armour->Stats.Int;
            }
        }
        stattype weaponInt = 0;
        for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
            if (equippedWeapons[i]) {
                Weapon* weapon = dynamic_cast<Weapon*>(equippedWeapons[i]->_data);
                weaponInt += weapon->Stats.Int;
            }
        }
        return pcClass->getTotalIntellect() + armourInt + weaponInt;
    }
    stattype getTotalAgility() const
    {
        stattype armourAgi = 0;
        for (auto i = 0; i < (unsigned long long)ARMOURSLOT::NUM_SLOTS; i++)
        {
            if (equippedArmour[i])
            {
                Armour* armour = dynamic_cast<Armour*>(equippedArmour[i]->_data);
                armourAgi += armour->Stats.Agi;
            }
        }
        stattype weaponAgi = 0;
        for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++)
        {
            if (equippedWeapons[i])
            {
                Weapon* weapon = dynamic_cast<Weapon*>(equippedWeapons[i]->_data);
                weaponAgi += weapon->Stats.Agi;
            }
        }
        return pcClass->getTotalAgility() + armourAgi + weaponAgi;
    }
    stattype getTotalDefence() const
    {
        // get all def from equipped armour
        stattype armourDef = 0;
        for (auto i = 0; i < (unsigned long long)ARMOURSLOT::NUM_SLOTS; i++)
        {
            if (equippedArmour[i])
            {
                Armour* armour = dynamic_cast<Armour*>(equippedArmour[i]->_data);
                armourDef += armour->Stats.Def;
            }
        }
        stattype weaponDef = 0;
        for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++)
        {
            if (equippedWeapons[i])
            {
                Weapon* weapon = dynamic_cast<Weapon*>(equippedWeapons[i]->_data);
                weaponDef += weapon->Stats.Def;
            }
        }
        return pcClass->getTotalDefence() + armourDef + weaponDef;
    }
    stattype getTotalResistance() const
    {
        stattype armourRes = 0;
        for (auto i = 0; i < (unsigned long long)ARMOURSLOT::NUM_SLOTS; i++) {
            if (equippedArmour[i])
            {
                Armour* armour = dynamic_cast<Armour*>(equippedArmour[i]->_data);
                armourRes += armour->Stats.Res;
            }
        }
        stattype weaponRes = 0;
        for (auto i = 0; i < (unsigned long long)WEAPONSLOT::NUM_SLOTS; i++) {
            if (equippedWeapons[i])
            {
                Weapon* weapon = dynamic_cast<Weapon*>(equippedWeapons[i]->_data);
                armourRes += weapon->Stats.Res;
            }
        }
        return pcClass->getTotalResistance() + armourRes + weaponRes;
    }

    const vector<Ability> getAbilityList() const { return pcClass->Abilities; }
    const vector<Buff> getBuffList() const { return pcClass->getBuffList(); }
    const vector<Item*> getBackpackList() const { return Backpack; }

    const Armour* getEquippedArmour(unsigned long long i) const {
        if(!equippedArmour[i]) return nullptr;
        return (dynamic_cast<const Armour*>(equippedArmour[i]->getData()));
    }

    const Weapon* getEquippedWeapon(unsigned long long i) const { 
        if(!equippedWeapons[i]) return nullptr;
        return (dynamic_cast<const Weapon*>(equippedWeapons[i]->getData()));
    }
    
    const dmgtype meleeAtk() const { 
        dmgtype tmp_dmg_done = 0;

        const Weapon* equippedWpn = getEquippedWeapon((unsigned long long)WEAPONSLOT::MELEE);
        if(equippedWpn) {
            tmp_dmg_done = Random::NTK(equippedWpn->minDMG, equippedWpn->maxDMG);
        } else {
            tmp_dmg_done = 1; // unarmed attack
        }

        // add 1/4 of str as bonus melee dmg
        tmp_dmg_done += dmgtype(getTotalStrength() / 4.f);

        return tmp_dmg_done;
     }
    const dmgtype rangedAtk() const { 
        dmgtype tmp_dmg_done = 0;

        const Weapon* equippedWpn = getEquippedWeapon((unsigned long long)WEAPONSLOT::RANGED);
        if(equippedWpn) {
            tmp_dmg_done = Random::NTK(equippedWpn->minDMG, equippedWpn->maxDMG);
        } else {
            tmp_dmg_done = 1; // unarmed attack
        }

        // add 1/4 of agi as bonus ranged dmg
        tmp_dmg_done += dmgtype(getTotalAgility() / 4.f);

        return tmp_dmg_done;
     }

    // modifiers
    void gainEXP(exptype amt) { 
        pcClass->gainEXP(amt); 
        }
    void takeDmg(welltype amt) { 
        pcClass->HP->reduceCurrent(amt); 
        }
    void heal(welltype amt) { 
        pcClass->HP->increaseCurrent(amt); 
        }
    void applyBuff(Buff buff) {
        pcClass->applyBuff(buff);
    }

    // deleted constructors
    playerCharacter() = delete;
    playerCharacter(const playerCharacter&) = delete;
    playerCharacter(const playerCharacter&&) = delete;
};