#include <cstdint>

typedef std::uint64_t exptype;
typedef std::uint16_t lvltype;

class lvlSystem {
public:
    static const exptype lvl2 = 100u;

    lvlSystem() { 
        CurrentLVL = 1u; 
        CurrentEXP = 0u;
        EXPtoLvlup = lvl2;
    }

    void gainEXP(exptype gained_exp) {
        CurrentEXP += gained_exp;
        while(check_if_leveled()) {}
    }

    lvltype getLvl() { return CurrentLVL; }
    exptype getCurrentEXP() { return CurrentEXP; }
    exptype getExptoLvlup() { return EXPtoLvlup; }

    virtual void lvlUp() = 0;

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