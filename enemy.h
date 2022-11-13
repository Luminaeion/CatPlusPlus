#pragma once
#include "types.h"
#include "pointWell.h"
#include <memory>
#include "random.h"

class Enemy
{
public:
    Enemy(welltype hp, dmgtype min, dmgtype max);
    pointWell HP;
    const dmgtype Attack() const { return Random::NTK(minDMG, maxDMG); }
    const dmgtype getMinDmg() const { return minDMG; }
    const dmgtype getMaxDmg() const { return maxDMG; }
private:
    dmgtype minDMG, maxDMG;
    Enemy() = delete;
    Enemy(const Enemy&) = delete;
    Enemy(const Enemy&&) = delete;
};

Enemy::Enemy(welltype hp, dmgtype min, dmgtype max) : HP(hp, hp), minDMG(min), maxDMG(max) {}

