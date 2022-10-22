#include <cstdint>
#include <vector>
#include <memory>

#include "stats.h"
#include "pointWell.h"
#include "ability.h"

typedef std::uint64_t exptype;
typedef std::uint16_t lvltype;

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

    virtual void lvlUp() = 0;
    virtual string getClassName() = 0;

    unique_ptr<pointWell> HP;
    unique_ptr<pointWell> MP;

    vector<Ability> Abilities;

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

        Abilities.emplace_back("Purr", 2u, 1u, abilityTarget::SELF, 7u, abilityScaler::INT);
    }
private:
 void lvlUp() override{
    LEVELUP 
    if(CurrentLVL == 2){
        // gain new ability :D
        Abilities.emplace_back("Swipe", 2u, 2u, abilityTarget::ENEMY, 5u, abilityScaler::STR);
    }
}
};

class playerCharacter {
private:
    playerCharacterDelegate* pcClass;

public:
    playerCharacter() = delete;
    playerCharacter(playerCharacterDelegate* pc) : pcClass(pc) {}
    ~playerCharacter() { delete pcClass; pcClass = nullptr; }

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

    // stats
    welltype getStrength() { return pcClass->getStrength(); }
    welltype getIntellect() { return pcClass->getIntellect(); }
    welltype getAgility() { return pcClass->getAgility(); }
    welltype getDefence() { return pcClass->getDefence(); }
    welltype getResistance() { return pcClass->getResistance(); }

    vector<Ability> getAbilityList() { return pcClass->Abilities; }
    
    void gainEXP(exptype amt) { pcClass->gainEXP(amt); }
    void takeDmg(welltype amt) { pcClass->HP->reduceCurrent(amt); }
    void heal(welltype amt) { pcClass->HP->increaseCurrent(amt); }
};