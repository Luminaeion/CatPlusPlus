#include "hp.h"
#include "stats.h"
#include "levelSystem.h"

class Cat : public hp, public Stats, public lvlSystem
{
// Stats for our cat!
// This class can be duped if one would like to add more classes like wizard, cleric, whatever
// For now there is only cat :3

public:
    // Base health points 14
    static const stattype BaseHP = (hptype)14u;
    // Base strength 2
    static const stattype BaseStr = (stattype)2u;

    // hp +7/lvl
    static const hptype hpGrowth = (hptype)7u;
    // str +1/lvl
    static const stattype strGrowth = (stattype)1u;

    Cat() : hp(hpGrowth, hpGrowth), Stats(BaseStr) {}

private: 
    void lvlUp() override {
        setMaxHP(hpGrowth + getMaxHP());
        increaseStats(strGrowth);
    }
};