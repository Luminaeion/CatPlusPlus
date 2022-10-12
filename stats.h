#include <cstdint>

typedef std::uint16_t stattype;

class Stats {
    stattype Str; // Strength  // 0xFF
    stattype Int; // Intellect
    stattype Agi; // Agility
    stattype Def; // Defence
    stattype Res; // Elemental resistance

public:
    explicit Stats(stattype s = 1, stattype i = 1, stattype a = 1, stattype d = 0, stattype r = 0) { 
        Str = s;
        Int = i;
        Agi = a;
        Def = a;
        Res = r;
    }
    stattype getStrength() { return Str; }
    stattype getIntellect() { return Int; }
    stattype getAgility() { return Agi; }
    stattype getDefence() { return Def; }
    stattype getResistance() { return Res; }

protected:
// default args
    void increaseStats(stattype s = 0, stattype i = 0, stattype a = 0, stattype d = 0, stattype r = 0){
        Str += s;
        Int += i;
        Agi += a;
        Def += d;
        Res += r;
    }
};