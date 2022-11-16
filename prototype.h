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

