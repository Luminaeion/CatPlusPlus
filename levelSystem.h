#include <cstdint>

typedef std::uint64_t exptype;
typedef std::uint16_t lvltype;

class lvlSystem {
public:
    static const lvltype lvlScalar = 2u;
    static const exptype lvl2 = 100u;

    lvlSystem() { 
        CurrentLVL = 1u; 
        CurrentEXP = 0u;
        EXPtoLvlup = lvl2;
    }

    void gainEXP(exptype gained_exp) {
        CurrentEXP += gained_exp;
        check_if_leveled();
    }

protected:
    lvltype CurrentLVL;
    exptype CurrentEXP;
    exptype EXPtoLvlup;

    void check_if_leveled(){
        static const lvltype lvlScalar = 2u;
        if(CurrentEXP > EXPtoLvlup) {
            CurrentLVL++;
            EXPtoLvlup *= lvlScalar;
        }
    }
};