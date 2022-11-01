#pragma once
#include "types.h"
#include "buff.h"
#include <vector>

class Stats {
    coreStats base;
    coreStats fromBuffs;
public:
    explicit Stats(stattype s = 1, stattype i = 0, stattype a = 0, stattype d = 0, stattype r = 0) { 
        base.Str = s;
        base.Int = i;
        base.Agi = a;
        base.Def = d;
        base.Res = r;
    }
    stattype getBaseStrength() { return base.Str; }
    stattype getBaseIntellect() { return base.Int; }
    stattype getBaseAgility() { return base.Agi; }
    stattype getBaseDefence() { return base.Def; }
    stattype getBaseResistance() { return base.Res; }

    stattype getTotalStrength() { return base.Str + fromBuffs.Str; }
    stattype getTotalIntellect() { return base.Int + fromBuffs.Int; }
    stattype getTotalAgility() { return base.Agi + fromBuffs.Agi; }
    stattype getTotalDefence() { return base.Def + fromBuffs.Def; }
    stattype getTotalResistance() { return base.Res + fromBuffs.Res; }

protected:
    void addNewBuff(Buff b) {
        for(auto& buff : Buffs) {
            // if buff exists, just refresh duration
            if (b.Name == buff.Name) {
                buff.Duration = b.Duration;
                return;
            }
        }
        Buffs.push_back(b);
        recalcBuffs();
    };
    vector<Buff> Buffs;

// default args
    void increaseStats(stattype s = 0, stattype i = 0, stattype a = 0, stattype d = 0, stattype r = 0){
        base.Str += s;
        base.Int += i;
        base.Agi += a;
        base.Def += d;
        base.Res += r;
    }

    void increaseStats(coreStats cs){
        base += cs;
    }

private:
    void recalcBuffs() {
        coreStats tmp_total;
        for (const auto& b : Buffs){
            if (b.isDebuff) {
                tmp_total -= b.BuffedStats;
            } else {
                tmp_total += b.BuffedStats;
            }
        }
        fromBuffs = tmp_total;
    }
};