#pragma once
#include "types.h"
#include "coreStats.h"
#include "stats.h"
#include <string>

// temp stat boosts
struct Buff {
    Buff(const char* name, stattype str = 0, stattype intel = 0, stattype agi = 0, stattype def = 0, stattype res = 0, uint16_t dur = 2u, bool isdebuff = false) : Name(name), Duration(dur), isDebuff(isdebuff) 
    {
        BuffedStats.Str = str;
        BuffedStats.Agi = agi;
        BuffedStats.Int = intel;
        BuffedStats.Def = def;
        BuffedStats.Res = res;
    }

    Buff(const char* name, coreStats cs, uint16_t dur = 2u, bool isdebuff = false) : Name(name), Duration(dur), isDebuff(isdebuff) {
        BuffedStats = cs;
    }

    string Name;
    uint16_t Duration;

    coreStats BuffedStats;

    bool isDebuff;
};