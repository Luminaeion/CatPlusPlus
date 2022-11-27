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

#pragma region CHARACTERCREATION
// Create character
#define CREATECHARACTER playerCharacter protag(new Cat());
#pragma endregion


#pragma region DEFAULTGEAR
// Create and equip standard gear
#define DEFAULTGEAR itemManager::equip(itemManager::createWeapon("Standard Murder Mittens", coreStats(), WEAPONSLOT::MELEE, 1, 4), &protag);\
itemManager::equip(itemManager::createArmour("Worn Collar", coreStats(0, 0, 0, 2, 1), ARMOURSLOT::NECK), &protag);
#pragma endregion


#pragma region CHARACTERINFO
#define CHARACTERINFO \
    std::cout << "\n--------------------- CHARACTER INFORMATION: ---------------------\n";\
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
    }\
    INVENTORY\
    std::cout << "\n------------------------------------------------------------------\n\n";
#pragma endregion


#pragma region TUTORIAL
#define TUTORIALCHOICE \
    std::cout << "Here is a brief introduction to how this game functions.\n";\
    std::cout << "You encounter a *menacing* ball of yarn.\n";\
    retry:\
    std::cout << "What will you do?\n";\
    std::cout << "[ look / paw / leave ]\n";\
    std::cout << "(Type one of these options and hit enter.)\n";\
    string tutorialChoice = playerChoice();\
    \
    if(tutorialChoice == "look")\
    {\
        std::cout << "You look at the ball of yarn sitting in front of you on the floor. Smells like wool.\n";\
        goto retry;\
    } else if(tutorialChoice == "paw")\
    {\
        std::cout << "You paw at the yarn. It rolls over and stops.\n";\
        protag.gainEXP(2u);\
        std::cout << "You gain 2 exp.\n";\
    } else if(tutorialChoice == "leave")\
    {\
        std::cout << "You decide to walk away. 'The yarn may live another day,' you think to yourself.\n";\
    } else {\
        std::cout << "Input not recognised. Please try again.\n";\
        goto retry;\
    }
#pragma endregion

// get a location to start with
string currentLocation = setLocation();


#pragma region WANDERING
#define RANDOMENCOUNTER int randomEvent;\
    int encounterNum = 0;\
    repeat:\
    std::cout << "You wander around but come across nothing of interest. \n Keep wandering? [yes / no]\n";\
    string wanderOpt = playerChoice();\
    if(wanderOpt == "yes"){\
        int randomEvent;\
        srand((unsigned)time(0));\
        int rnum = rng(10);\
        int pnum = rng(10);\
        if(rnum == pnum){\
            forceEncounter:\
            switch(rnum){\
                case 1:\
                case 2:\
                    {\
                        std::cout << "You find a Fish Biscuit that looks particularly delicious. \n Pick it up? [ yes / no ]\n";\
                        string playerAction = playerChoice();\
                        if(playerAction == "yes"){\
                            std::cout << "You pick it up.\n";\
                            itemManager::moveToBackpack(itemManager::createPotion("Fish Biscuit", 1u, 2u), &protag);\
                            std::cout << "Obtained Fish Biscuit!\n";\
                        } else if(playerAction == "no") {\
                            std::cout << "You don't like this particular Fish Biscuit. You decide to leave it where it is.\n";\
                        }\
                    }\
                    break;\
                case 3:\
                case 4:\
                    {\
                        std::cout << "You find a Small Healing Potion. It might be useful. \n Pick it up? [ Yes / No ]\n";\
                        string playerAction = playerChoice();\
                        if(playerAction == "yes"){\
                            std::cout << "You pick the Small Healing Potion up.\n";\
                            itemManager::moveToBackpack(itemManager::createPotion("Small Healing Potion", 1u, 3u), &protag);\
                            std::cout << "Obtained Small Healing Potion!\n";\
                        } else if(playerAction == "no"){\
                            std::cout << "You ignore the Small Healing Potion and walk away.\n";\
                        }\
                    }\
                    break;\
                case 5:\
                case 6:\
                    {\
                        std::cout << "An <enemy> appears! They haven't noticed you yet. \n What will you do? [run / fight]\n";\
                        string playerAction = playerChoice();\
                        if(playerAction == "run"){\
                            std::cout << "You flee before you're noticed.\n";\
                            std::cout << "Escaped safely.\n";\
                        } else if (playerAction == "fight"){\
                            std::cout << "You take the <enemy> by surprise!\n";\
                        }\
                    }\
                    break;\
                case 7:\
                case 8:\
                    {\
                        std::cout << "You find a Cool Stick. It might be useful. \n Pick it up? [ Yes / No ]\n";\
                        string playerAction = playerChoice();\
                        if(playerAction == "yes"){\
                            std::cout << "You take the Cool Stick with you.\n";\
                            itemManager::moveToBackpack(itemManager::createWeapon("Cool Stick", coreStats(), WEAPONSLOT::MELEE, 1, 2), &protag);\
                            std::cout << "Obtained Cool Stick!\n";\
                        } else if(playerAction == "no"){\
                            std::cout << "You decide to leave the Cool Stick where it is.\n";\
                        }\
                    }\
                    break;\
                case 9:\
                case 10:\
                    {\
                        std::cout << "You find a Tophat. \n Do you want to bring it with you? [ yes / no ]\n";\
                        string playerAction = playerChoice();\
                        if(playerAction == "yes"){\
                            std::cout << "You plop the Tophat on your head. It makes you feel dapper.\n";\
                            itemManager::equip(itemManager::createArmour("Tophat", coreStats(1, 3, 0, 1, 0), ARMOURSLOT::HELMET), &protag);\
                            std::cout << "Obtained Tophat!\n";\
                        } else if(playerAction == "no"){\
                            std::cout << "You decide to leave the Tophat where it is. You reckon you're dapper enough already.\n";\
                        }\
                    }\
                    break;\
            }\
        } else {\
            if(encounterNum >= 4){\
                rnum == pnum;\
                goto forceEncounter;\
            } else {\
                encounterNum++;\
                goto repeat;\
            }\
        }\
    }
#pragma endregion


#pragma region EXPLORATION
#define EXPLORATION bool wander = false;\
    \
    exploration:\
    std::cout << "What would you like to do next?\n";\
    std::cout << "[ look around / wander / check stats ]\n";\
    string playerInput = longInput();\
    \
    if(playerInput == "wander"){\
        wander = true;\
        string currentLocation = setLocation();\
        goto wander;\
    } else if (playerInput == "look around") {\
        std::cout << "You look around. You see a " << currentLocation << ".\n";\
        DISCOVERY\
        goto exploration;\
    } else if (playerInput == "check stats") {\
        std::cout << "You sit down and examine yourself.\n";\
        CHARACTERINFO\
        std::cout << "Finished with your brief moment of reflection, you get up, ready to continue onward.\n";\
        goto exploration;\
    } else {\
        std::cout << "Input not recognised. Please try again.\n";\
        goto exploration;\
    }\
    \
    wander:\
    while(wander){\
        RANDOMENCOUNTER\
        else if(wanderOpt == "no"){\
            wander = false;\
            goto exploration;\
        }\
    }
#pragma endregion


#pragma region DISCOVERYBOOL
#define CHECKIFANYTHINGFOUND bool encounteredSomething = false;\
    int rndNum = rng(5);\
    int rndNum2 = rng(5);\
    if(rndNum == rndNum2) { encounteredSomething = true; }
#pragma endregion


#pragma region RANDOMFOUNDTHING
int generateRandomThing() {
    int thingType = rand()%3;
    int thingNum = rand()%4;
    int thingArr[4][4] = {{0,1,2,3}, {4,5,6,7}, {8,9,10,11}, {12,13,14,15}};
    int genRes = thingArr[thingType][thingNum];
    // output test
    cout << "This was generated: " << thingArr[thingType][thingNum] << "(from pos" << thingType << "," << thingNum << ")\n";
    // fetch generated item
    Item* generatedItem;
    switch(genRes) {
    case 0: // items 0-3 
        {
        Item* HealPotion = itemManager::createPotion("TESTITEM_POTION1", 3u, 3u);
        generatedItem = HealPotion;
        break;
        }
    case 1:
        {
        Item* HealPotion1 = itemManager::createPotion("TESTITEM_POTION2", 3u, 3u);
        generatedItem = HealPotion1;
        break;
        }
    case 2:
        {
        Item* HealPotion2 = itemManager::createPotion("TESTITEM_POTION3", 3u, 3u);
        generatedItem = HealPotion2;
        break;
        }
    case 3:
        {
        Item* HealPotion3 = itemManager::createPotion("TESTITEM_POTION4", 3u, 3u);
        generatedItem = HealPotion3;
        break;
        }
    case 4: // weapons 8-11
        {
        Item* MurderMitts = itemManager::createWeapon("TESTITEM_WEAPON1", coreStats(), WEAPONSLOT::MELEE, 1, 4);
        generatedItem = MurderMitts;
        break;
        }
    case 5:
        {
        Item* MurderMitts1 = itemManager::createWeapon("TESTITEM_WEAPON2", coreStats(), WEAPONSLOT::MELEE, 1, 4);
        generatedItem = MurderMitts1;
        break;
        }
    case 6:
        {
        Item* MurderMitts2 = itemManager::createWeapon("TESTITEM_WEAPON3", coreStats(), WEAPONSLOT::MELEE, 1, 4);
        generatedItem = MurderMitts2;
        break;
        }
    case 7:
        {
        Item* MurderMitts3 = itemManager::createWeapon("TESTITEM_WEAPON4", coreStats(), WEAPONSLOT::MELEE, 1, 4);
        generatedItem = MurderMitts3;
        break;
        }
    case 8: // armour 12-15
        {
        Item* WornCollar = itemManager::createArmour("TESTITEM_ARMOUR1", coreStats(0, 0, 0, 2, 1), ARMOURSLOT::NECK);
        generatedItem = WornCollar;
        break;
        }
    case 9:
        {
        Item* WornCollar2 = itemManager::createArmour("TESTITEM_ARMOUR2", coreStats(0, 0, 0, 2, 1), ARMOURSLOT::NECK);
        generatedItem = WornCollar2;
        break;
        }
    case 10:
        {
        Item* WornCollar3 = itemManager::createArmour("TESTITEM_ARMOUR3", coreStats(0, 0, 0, 2, 1), ARMOURSLOT::NECK);
        generatedItem = WornCollar3;
        break;
        }
    case 11:
        {
        Item* WornCollar4 = itemManager::createArmour("TESTITEM_ARMOUR4", coreStats(0, 0, 0, 2, 1), ARMOURSLOT::NECK);
        generatedItem = WornCollar4;
        break;
        }
    }
    cout << "Discovered " << *generatedItem << ".\n";
}
#pragma endregion


#pragma region DISCOVERY
#define DISCOVERY \
CHECKIFANYTHINGFOUND \
if(encounteredSomething){\
    cout << "HELLO YOU APPARENTLY FOUND SOME STUFF, NICE\n";\
    generateRandomThing();\
} else {\
    cout << "You don't find anything of interest in the area.\n";\
}
#pragma endregion


#pragma region INVENTORY
#define INVENTORY \
auto inv = protag.getBackpackList();\
std::cout << "Inventory: ";\
for(auto it : inv) { std::cout << *it << ", "; }
#pragma endregion


#pragma region BATTLE
// BATTLE STUFF
struct Fightable {
    Fightable(int hp, int min, int max) : enemy(hp, min, max) {
        xpworth = (hp + min + max) * 2;
    }
    bool isAlive() { return (enemy.HP.getCurrent() > 0); }
    Enemy enemy;
    int xpworth;
    Fightable() = delete;
};

struct Player {
    Player(playerCharacterDelegate* charclass) : us(charclass) {}
    Player() = delete;
    bool isAlive() { return (us.getCurrentHP() > 0); }
    playerCharacter us;
};

Player* MainCharacter = nullptr;
Fightable* CurrentEnemy = nullptr;

void enterFight(Player& player1) {
    if(!CurrentEnemy) {
        return;
    }

    while(player1.isAlive() && CurrentEnemy->isAlive()) {
        cout << "An enemy stands before you, ready to do battle.";
        cout << "Player health: " << player1.us.getCurrentHP() << "/" << player1.us.getMaxHP() << "\n";
        cout << "Enemy health: " << CurrentEnemy->enemy.HP.getCurrent() << "/" << CurrentEnemy->enemy.HP.getMax() << "\n";
        // battle logic here :)
    };
};
#pragma endregion