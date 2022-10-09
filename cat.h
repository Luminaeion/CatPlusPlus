#include "hp.h"
#include "stats.h"

class Cat : public hp, public Stats
{
// Stats for our cat!
// This class can be duped if one would like to add more classes like wizard, cleric, whatever
// For now there is only cat :3

public:
    // hp +7/lvl
    static const hptype hpGrowth = (hptype)7u;
    // Base strength 2
    static const stattype BaseStr = (stattype)2u;
    // Base defence 1
    //static const stattype BaseDef = (stattype)1u;
    Cat() : hp(hpGrowth, hpGrowth), Stats(BaseStr) {}

private: 
};