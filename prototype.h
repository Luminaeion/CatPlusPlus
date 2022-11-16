#pragma once
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <bits/stdc++.h>

#include "playerFunctions.h"
#include "playerCharacter.h"
#include "itemManager.h"
#include "enemy.h"

// Create character
#define CREATECHARACTER playerCharacter protag(new Cat());

// Create and equip standard gear
#define DEFAULTGEAR itemManager::equip(itemManager::createWeapon("Standard Murder Mittens", coreStats(), WEAPONSLOT::MELEE, 1, 4), &protag);\
itemManager::equip(itemManager::createArmour("Worn Collar", coreStats(0, 0, 0, 2, 1), ARMOURSLOT::NECK), &protag);

#define CHARACTERINFO \
    std::cout\
    << protag.getClassName()\
    << " - lvl  " << protag.getLvl() << '\n'\
    << "- Exp:  " << protag.getCurrentEXP() << "/" << protag.getExptoLvlup() << '\n'\
    << "- HP:   " << protag.getCurrentHP() << "/" << protag.getMaxHP() << '\n'\
    << "- MP:   " << protag.getCurrentMP() << "/" << protag.getMaxMP() << '\n'\
    << "- Strength: " << protag.getTotalStrength() << '\n'\
    << "- Intellect: " << protag.getTotalIntellect() << '\n'\
    << "- Agility: " << protag.getTotalAgility() << '\n'\
    << "- Defence: " << protag.getTotalDefence() << '\n'\
    << "- Elemental resistance: " << protag.getTotalResistance() << endl;\
    \
    auto allBuffs = protag.getBuffList();\
    std::cout << "- Buffs:\n";\
    for(auto& buff : allBuffs) { std::cout << "   -" << buff.Name << '\n'; }\
    \
    auto allAbilities = protag.getAbilityList();\
    std::cout << "- Abilities:\n";\
    for(auto& abil : allAbilities) { std::cout << "   -" << abil.Name << '\n'; }\
    \
    std::cout << "- Armour:\n";\
    for(int i = 0; i < (int)ARMOURSLOT::NUM_SLOTS; i++) {\
        const Armour* tmp = dynamic_cast<const Armour*>(protag.getEquippedArmour(i)); \
        \
        if(tmp) {\
            std::cout << "   " << tmp->Name << " (+" << tmp->Stats.Def << " def, +" << tmp->Stats.Res << " res)" << '\n';\
        }\
    }\
    std::cout << "- Weapons:\n";\
    for(int i = 0; i < (int)WEAPONSLOT::NUM_SLOTS; i++) {\
        const Weapon* tmp = dynamic_cast<const Weapon*>(protag.getEquippedWeapon(i)); \
        \
        if(tmp) {\
            std::cout << "   " << tmp->Name << " (" << tmp->minDMG << "-" << tmp->maxDMG << " dmg)" << '\n';\
        }\
    }
