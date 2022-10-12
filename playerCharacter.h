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
        increaseStats(BaseStr, BaseInt, BaseAgi);\
    };

#define LEVELUP void lvlUp() override {\
        HP->setMax((welltype)(BaseHP / 2.f) + HP->getMax());\
        HP->increaseCurrent((welltype)(BaseHP / 2.f));\
        increaseStats((stattype)((BaseStr + 1u) / 2.f), (stattype)((BaseInt + 1u) / 2.f), (stattype)((BaseAgi + 1u) / 2.f));\
    }

#define CHARACTERCLASS(classname, basehp, basestr, baseint, baseagi)\
class classname : public playerCharacterDelegate {\
public:\
    static const welltype BaseHP = (welltype)basehp;\
    static const stattype BaseStr = (stattype)basestr;\
    static const stattype BaseInt = (stattype)baseint;\
    static const stattype BaseAgi = (stattype)baseagi;\
    string getClassName() override { return string(#classname); }\
    classname() PCCONSTRUCT \
private:\
    LEVELUP \
};

// this next row is all that's needed to create a character class :)
CHARACTERCLASS(Cat, 14, 2, 4, 7) // (rpg)class, hp, str, int, agi

class playerCharacter {
private:
    playerCharacterDelegate* pcClass;
    //InventoryDelegate* inv;

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
    welltype getIntellect() { return pcClass->getIntellect(); }
    welltype getAgility() { return pcClass->getAgility(); }
    welltype getDefence() { return pcClass->getDefence(); }
    welltype getResistance() { return pcClass->getResistance(); }
    
    void gainEXP(exptype amt) { pcClass->gainEXP(amt); }
    void takeDmg(welltype amt) { pcClass->HP->reduceCurrent(amt); }
    void heal(welltype amt) { pcClass->HP->increaseCurrent(amt); }
};