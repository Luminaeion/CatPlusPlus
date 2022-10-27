#pragma once
#include "types.h"
#include <vector>
#include "buff.h"

class Stats {
    // base stats
    stattype baseStr; // Strength  // 0xFF
    stattype baseInt; // Intellect
    stattype baseAgi; // Agility
    stattype baseDef; // Defence
    stattype baseRes; // Elemental resistance

    // stats w/ buffs
    stattype StrBuff = 0;
    stattype IntBuff = 0;
    stattype AgiBuff = 0;
    stattype DefBuff = 0;
    stattype ResBuff = 0;

public:
    explicit Stats(stattype s = 1, stattype i = 1, stattype a = 1, stattype d = 0, stattype r = 0) { 
        baseStr = s;
        baseInt = i;
        baseAgi = a;
        baseDef = d;
        baseRes = r;
    }
    stattype getBaseStrength() { return baseStr; }
    stattype getBaseIntellect() { return baseInt; }
    stattype getBaseAgility() { return baseAgi; }
    stattype getBaseDefence() { return baseDef; }
    stattype getBaseResistance() { return baseRes; }

    stattype getTotalStrength() { return baseStr + StrBuff; }
    stattype getTotalIntellect() { return baseInt + IntBuff; }
    stattype getTotalAgility() { return baseAgi + AgiBuff; }
    stattype getTotalDefence() { return baseDef + DefBuff; }
    stattype getTotalResistance() { return baseRes + ResBuff; }

protected:
    void newBuff(Buff b) {
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
        baseStr += s;
        baseInt += i;
        baseAgi += a;
        baseDef += d;
        baseRes += r;
    }

private:
    void recalcBuffs() {
        stattype strbuff = 0;
        stattype intbuff = 0;
        stattype agibuff = 0;
        stattype defbuff = 0;
        stattype resbuff = 0;

        for(const auto& b : Buffs){
            if(b.isDebuff){
                strbuff -= b.Str;
                intbuff -= b.Int;
                agibuff -= b.Agi;
                defbuff -= b.Def;
                resbuff -= b.Res;
            } else {
                strbuff += b.Str;
                intbuff += b.Int;
                agibuff += b.Agi;
                defbuff += b.Def;
                resbuff += b.Res;
            }
        }
        StrBuff = strbuff;
        IntBuff = intbuff;
        AgiBuff = agibuff;
        DefBuff = defbuff;
        ResBuff = resbuff;

        // prevent negative buff values
        if(StrBuff < 0) StrBuff = 0;
        if(IntBuff < 0) IntBuff = 0;
        if(AgiBuff < 0) AgiBuff = 0;
        if(DefBuff < 0) DefBuff = 0;
        if(ResBuff < 0) ResBuff = 0;
    }
};