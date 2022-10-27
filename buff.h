#pragma once
#include "types.h"
#include <string>
#include "stats.h"

using namespace std;

// temp stat boosts
struct Buff {
    
    Buff(string name, uint16_t dur, stattype str = 0, stattype intel = 0, stattype agi = 0, stattype def = 0, stattype res = 0, bool isdebuff = false) : Name(name), Duration(dur), Str(str), Int(intel), Agi(agi), Def(def), Res(res), isDebuff(isdebuff) 
    {};

    string Name;
    uint16_t Duration;

    stattype Str; // Strength  // 0xFF
    stattype Int; // Intellect
    stattype Agi; // Agility
    stattype Def; // Defence
    stattype Res; // Elemental resistance

    bool isDebuff;
};