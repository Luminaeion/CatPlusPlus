#include <cstdint>
#include <memory>

#include "stats.h"
#include "pointWell.h"

typedef std::uint64_t exptype;
typedef std::uint16_t lvltype;

class playerCharacterDelegate : public Stats {
public:
    static const exptype lvl2 = 100u;

    playerCharacterDelegate() : Stats(0u) { 
        CurrentLVL = 1u; 
        CurrentEXP = 0u;
        EXPtoLvlup = lvl2;
        HP = make_unique<pointWell>();
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

#define PCCONSTRUCT : playerCharacterDelegate() {\
        HP->setMax(BaseHP);\
        HP->increaseCurrent(BaseHP);\
        increaseStats(BaseStr);\
    }

#define LEVELUP void lvlUp() override {\
        HP->setMax((welltype)(BaseHP/2.f) + HP->getMax());\
        HP->increaseCurrent((welltype)(BaseHP/2.f));\
        increaseStats((stattype)(BaseStr+1u)/2.f);\
    }

class Cat : public playerCharacterDelegate
{
// Stats for our cat!
// This class also works as a template for other (rpg) classes!

public:
// Base stats
    // Base health points 14
    static const stattype BaseHP = (welltype)14u;
    // Base strength 2
    static const stattype BaseStr = (stattype)2u;

// retrieves className
    string getClassName() override { return string("Cat"); }

// create character w/ base stats
    Cat() PCCONSTRUCT

private: 
    LEVELUP
};

class playerCharacter {
private:
    playerCharacterDelegate* pcClass;

public:
    playerCharacter() = delete;
    playerCharacter(playerCharacterDelegate* pc) : pcClass(pc) {}
    ~playerCharacter() { delete pcClass; pcClass = nullptr; }

    string getClassName() { return pcClass->getClassName(); }
    lvltype getLvl() { return pcClass->getLvl(); }
    exptype getCurrentEXP() { return pcClass->getCurrentEXP(); }
    exptype getExptoLvlup() { return pcClass->getExptoLvlup(); }
    welltype getMax() { return pcClass->HP->getMax(); }
    welltype getStrength() { return pcClass->getStrength(); }
    welltype getCurrentHP() { return pcClass->HP->getCurrent(); }
    
    void gainEXP(exptype amt) { pcClass->gainEXP(amt); }
    void takeDmg(welltype amt) { pcClass->HP->reduceCurrent(amt); }
    void heal(welltype amt) { pcClass->HP->increaseCurrent(amt); }
};