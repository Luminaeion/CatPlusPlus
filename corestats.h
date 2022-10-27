#include "types.h"

struct coreStats {
    stattype Str = 1; // Strength
    stattype Int = 1; // Intellect
    stattype Agi = 1; // Agility
    stattype Def = 0; // Defence
    stattype Res = 0; // Elemental resistance

    coreStats& operator+=(const coreStats& rhs) {
        this->Str += rhs.Str;
        this->Int += rhs.Int;
        this->Agi += rhs.Agi;
        this->Def += rhs.Def;
        this->Res += rhs.Res;
        return *this;
    };

    coreStats& operator-=(const coreStats& rhs) {
        coreStats tmp = *this;

        this->Str -= rhs.Str;
        this->Int -= rhs.Int;
        this->Agi -= rhs.Agi;
        this->Def -= rhs.Def;
        this->Res -= rhs.Res;

        // prevents wrapping around to a massive number if value < 0
        if(this->Str > tmp.Str){ this->Str = 0u; }
        if(this->Int > tmp.Int){ this->Int = 0u; }
        if(this->Agi > tmp.Agi){ this->Agi = 0u; }
        if(this->Def > tmp.Def){ this->Def = 0u; }
        if(this->Res > tmp.Res){ this->Res = 0u; }

        return *this;
    };

    coreStats& operator=(const stattype& rhs) {
        this->Str = rhs;
        this->Int = rhs;
        this->Agi = rhs;
        this->Def = rhs;
        this->Res = rhs;
        return *this;
    }
};
