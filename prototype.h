#pragma once
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <stdio.h>

#include "playerFunctions.h"
#include "playerCharacter.h"
#include "itemManager.h"
#include "enemy.h"

bool gameOver = false;

#pragma region CHARACTERCREATION
// Create character
#define CREATECHARACTER MainCharacter = new Player(new Cat());
#pragma endregion


#pragma region DEFAULTGEAR
// Create and equip standard gear
#define DEFAULTGEAR itemManager::equip(itemManager::createWeapon("Standard Murder Mittens", coreStats(), WEAPONSLOT::MELEE, 1, 4), &MainCharacter->us);\
itemManager::equip(itemManager::createArmour("Worn Collar", coreStats(0, 0, 0, 2, 1), ARMOURSLOT::NECK), &MainCharacter->us);
#pragma endregion


#pragma region CHARACTERINFO
#define CHARACTERINFO \
    std::cout << "\n--------------------- CHARACTER INFORMATION: ---------------------\n";\
    std::cout\
    << MainCharacter->us.getClassName()\
    << " - lvl  " << MainCharacter->us.getLvl() << '\n'\
    << "- Exp:  " << MainCharacter->us.getCurrentEXP() << "/" << MainCharacter->us.getExptoLvlup() << '\n'\
    << "- HP:   " << MainCharacter->us.getCurrentHP() << "/" << MainCharacter->us.getMaxHP() << '\n'\
    << "- MP:   " << MainCharacter->us.getCurrentMP() << "/" << MainCharacter->us.getMaxMP() << '\n'\
    << "- Strength: " << MainCharacter->us.getTotalStrength() << '\n'\
    << "- Intellect: " << MainCharacter->us.getTotalIntellect() << '\n'\
    << "- Agility: " << MainCharacter->us.getTotalAgility() << '\n'\
    << "- Defence: " << MainCharacter->us.getTotalDefence() << '\n'\
    << "- Elemental resistance: " << MainCharacter->us.getTotalResistance() << endl;\
    \
    auto allBuffs = MainCharacter->us.getBuffList();\
    std::cout << "- Buffs:\n";\
    for(auto& buff : allBuffs) { std::cout << "   -" << buff.Name << '\n'; }\
    \
    auto allAbilities = MainCharacter->us.getAbilityList();\
    std::cout << "- Abilities:\n";\
    for(auto& abil : allAbilities) { std::cout << "   -" << abil.Name << '\n'; }\
    \
    std::cout << "- Armour:\n";\
    for(int i = 0; i < (int)ARMOURSLOT::NUM_SLOTS; i++) {\
        const Armour* tmp = dynamic_cast<const Armour*>(MainCharacter->us.getEquippedArmour(i)); \
        \
        if(tmp) {\
            std::cout << "   " << tmp->Name << " (+" << tmp->Stats.Def << " def, +" << tmp->Stats.Res << " res)" << '\n';\
        }\
    }\
    std::cout << "- Weapons:\n";\
    for(int i = 0; i < (int)WEAPONSLOT::NUM_SLOTS; i++) {\
        const Weapon* tmp = dynamic_cast<const Weapon*>(MainCharacter->us.getEquippedWeapon(i)); \
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
        MainCharacter->us.gainEXP(2u);\
        std::cout << "You gain 2 exp.\n";\
    } else if(tutorialChoice == "leave")\
    {\
        std::cout << "You decide to walk away. 'The yarn may live another day,' you think to yourself.\n";\
    } else {\
        std::cout << "Input not recognised. Please try again.\n";\
        goto retry;\
    }
#pragma endregion


#pragma region WANDERING
// get a location to start with
string currentLocation = setLocation();
#define RANDOMENCOUNTER int randomEvent;\
    int encounterNum = 0;\
    bool wander = false;\
    repeat:\
    std::cout << "You wander around but come across nothing of interest. \n Keep wandering? [yes / no]\n";\
    string wanderOpt = playerChoice();\
    if(wanderOpt == "yes"){\
        wander = true;\
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
                        itemManager::moveToBackpack(itemManager::createPotion("Fish Biscuit", 1u, 2u), &MainCharacter->us);\
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
                        itemManager::moveToBackpack(itemManager::createPotion("Small Healing Potion", 1u, 3u), &MainCharacter->us);\
                        std::cout << "Obtained Small Healing Potion!\n";\
                    } else if(playerAction == "no"){\
                        std::cout << "You ignore the Small Healing Potion and walk away.\n";\
                    }\
                    }\
                    break;\
                case 5:\
                case 6:\
                    {\
                    std::cout << "An enemy appears!\n";\
                    _getch();\
                    enterFight(*MainCharacter);\
                    }\
                    break;\
                case 7:\
                case 8:\
                    {\
                    std::cout << "You find a Cool Stick. It might be useful. \n Pick it up? [ Yes / No ]\n";\
                    string playerAction = playerChoice();\
                    if(playerAction == "yes"){\
                        std::cout << "You take the Cool Stick with you.\n";\
                        itemManager::equip(itemManager::createWeapon("Cool Stick", coreStats(), WEAPONSLOT::MELEE, 1, 2), &MainCharacter->us);\
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
                        itemManager::equip(itemManager::createArmour("Tophat", coreStats(1, 3, 0, 1, 0), ARMOURSLOT::HEAD), &MainCharacter->us);\
                        std::cout << "Obtained Tophat!\n";\
                    } else if(playerAction == "no"){\
                        std::cout << "You decide to leave the Tophat where it is. You reckon you're dapper enough already.\n";\
                    }\
                    }\
                    break;\
            }\
        } else {\
            if(encounterNum >= 3){\
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
    std::cout << "[ look around / wander / check stats / open inventory ]\n";\
    awaitInput:\
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
    } else if(playerInput == "open inventory") {\
        openInventory();\
        goto exploration;\
    } else if(playerInput == "") {\
        goto awaitInput;\
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

// TODO Need to rename test items :P
#pragma region RANDOMFOUNDTHING
int generateRandomThing() {
    int thingType = rand()%3;
    int thingNum = rand()%4;
    int thingArr[4][4] = {{0,1,2,3}, {4,5,6,7}, {8,9,10,11}, {12,13,14,15}};
    int genRes = thingArr[thingType][thingNum];
    // output test
    //cout << "This was generated: " << thingArr[thingType][thingNum] << "(from pos" << thingType << "," << thingNum << ")\n";
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
    cout << "You find something!\n";\
    generateRandomThing();\
} else {\
    cout << "You don't find anything of interest in the area.\n";\
}
#pragma endregion


#pragma region INVENTORY
#define INVENTORY \
auto inv = MainCharacter->us.getBackpackList();\
std::cout << "Inventory: ";\
for(auto it : inv) { std::cout << *it << ", "; }
#pragma endregion


#pragma region WANDERING&BATTLES
#define Coords Random::NTK(1, 3);

struct Player {
    Player(playerCharacterDelegate* charclass) : us(charclass) {}
    Player() = delete;
    bool isAlive() { return (us.getCurrentHP() > 0); }
    playerCharacter us;
    int xpos = 0;
    int ypos = 0;
};

struct Fightable {
    Fightable(int hp, int min, int max) : enemy(hp, min, max) {
        xpworth = (hp + min + max) * 2;
    }
    bool isAlive() { return (enemy.HP.getCurrent() > 0); }
    Enemy enemy;
    int xpos = 5;
    int ypos = 5;
    int xpworth;
    Fightable() = delete;
};


Player* MainCharacter = nullptr;
Fightable* CurrentEnemy = nullptr;
int victoryCount = 0;
char position[3][3];

// generic drops ¯\_(ツ)_/¯
Item* dropLoot() {
    // 8 armour, 2 weapon, 1 potion : 11 total possible types of drops
    int drop_seed = Random::NTK(1, 100);
    if (drop_seed < 6) { // = 6% drop chance
        // chance for better loot ¯\_(ツ)_/¯
        string name;
        coreStats local_stats;
        int magicalPower = Random::NTK(0, 2);
        switch(magicalPower) {
            case 0: name = "Helmet";
                local_stats = coreStats(0,0,0,1,0);
                break;
            case 1: 
                name = "+1 Helmet";
                local_stats = coreStats(1,1,1,2,1);
            break;
            case 2: 
                name = "+2 Helmet";
                local_stats = coreStats(2,2,2,3,2);
            break;
        }
        return itemManager::createArmour(name, local_stats, ARMOURSLOT::HEAD);
    } else if (drop_seed < 12) {
        string name;
        coreStats local_stats;
        int magicalPower = Random::NTK(0, 2);
        switch(magicalPower) {
            case 0: name = "Chestplate";
                local_stats = coreStats(0,0,0,1,0);
                break;
            case 1: 
                name = "+1 Chestplate";
                local_stats = coreStats(1,1,1,2,1);
            break;
            case 2: 
                name = "+2 Chestplate";
                local_stats = coreStats(2,2,2,3,2);
            break;
        }
        return itemManager::createArmour(name, local_stats, ARMOURSLOT::CHEST);
    } else if (drop_seed < 18) {
        string name;
        coreStats local_stats;
        int magicalPower = Random::NTK(0, 2);
        switch(magicalPower) {
            case 0: name = "Leg Guards";
                local_stats = coreStats(0,0,0,1,0);
                break;
            case 1: 
                name = "+1 Leg Guards";
                local_stats = coreStats(1,1,1,2,1);
            break;
            case 2: 
                name = "+2 Leg Guards";
                local_stats = coreStats(2,2,2,3,2);
            break;
        }
        return itemManager::createArmour(name, local_stats, ARMOURSLOT::LEGS);
    } else if (drop_seed < 24) {
        string name;
        coreStats local_stats;
        int magicalPower = Random::NTK(0, 2);
        switch(magicalPower) {
            case 0: name = "Boots";
                local_stats = coreStats(0,0,0,1,0);
                break;
            case 1: 
                name = "+1 Boots";
                local_stats = coreStats(1,1,1,2,1);
            break;
            case 2: 
                name = "+2 Boots";
                local_stats = coreStats(2,2,2,3,2);
            break;
        }
        return itemManager::createArmour(name, local_stats, ARMOURSLOT::FEET);
    } else if (drop_seed < 30) {
        string name;
        coreStats local_stats;
        int magicalPower = Random::NTK(0, 2);
        switch(magicalPower) {
            case 0: name = "Gloves";
                local_stats = coreStats(0,0,0,1,0);
                break;
            case 1: 
                name = "+1 Gloves";
                local_stats = coreStats(1,1,1,2,1);
            break;
            case 2: 
                name = "+2 Gloves";
                local_stats = coreStats(2,2,2,3,2);
            break;
        }
        return itemManager::createArmour(name, local_stats, ARMOURSLOT::HANDS);
    } else if (drop_seed < 36) {
        string name;
        coreStats local_stats;
        int magicalPower = Random::NTK(0, 2);
        switch(magicalPower) {
            case 0: name = "Ring";
                local_stats = coreStats(1,1,1,0,0);
                break;
            case 1: 
                name = "+1 Ring";
                local_stats = coreStats(2,2,2,1,1);
            break;
            case 2: 
                name = "+2 Ring";
                local_stats = coreStats(3,3,3,2,2);
            break;
        }
        return itemManager::createArmour(name, local_stats, ARMOURSLOT::RING1);
    } else if (drop_seed < 42) {
        string name;
        coreStats local_stats;
        int magicalPower = Random::NTK(0, 2);
        switch(magicalPower) {
            case 0: name = "Ring";
                local_stats = coreStats(1,1,1,0,0);
                break;
            case 1: 
                name = "+1 Ring";
                local_stats = coreStats(2,2,2,1,1);
            break;
            case 2: 
                name = "+2 Ring";
                local_stats = coreStats(3,3,3,2,2);
            break;
        }
        return itemManager::createArmour(name, local_stats, ARMOURSLOT::RING2);
    } else if (drop_seed < 48) {
        string name;
        coreStats local_stats;
        int magicalPower = Random::NTK(0, 2);
        switch(magicalPower) {
            case 0: 
                name = "Neck Guard";
                local_stats = coreStats(0,0,0,1,1);
                break;
            case 1: 
                name = "+1 Neck Guard";
                local_stats = coreStats(1,1,1,2,2);
            break;
            case 2: 
                name = "+2 Neck Guard";
                local_stats = coreStats(2,2,2,3,3);
            break;
        }
        return itemManager::createArmour(name, local_stats, ARMOURSLOT::NECK);
    } else if (drop_seed < 54) {
        return itemManager::createWeapon("Sword", coreStats(0, 0, 0, 0, 0), WEAPONSLOT::MELEE, 2, 3);
    } else if (drop_seed < 60) {
        return itemManager::createWeapon("Bow", coreStats(0, 0, 0, 0, 0), WEAPONSLOT::RANGED, 2, 3);
    } else if (drop_seed < 91) {
        string name;
        coreStats local_stats;
        int magicalPower = Random::NTK(0, 2);
        switch(magicalPower) {
            case 0: name = "Chestplate";
                local_stats = coreStats(0,0,0,1,0);
                break;
            case 1: 
                name = "+1 Chestplate";
                local_stats = coreStats(1,1,1,2,1);
            break;
            case 2: 
                name = "+2 Chestplate";
                local_stats = coreStats(2,2,2,3,2);
            break;
        }
        return itemManager::createPotion("Potion of Healing", Random::NTK(2, 5), Random::NTK(1, 2));
    } else if (drop_seed < 101) {
        string name;
        coreStats local_stats;
        int magicalPower = Random::NTK(0, 2);
        switch(magicalPower) {
            case 0: name = "Chestplate";
                local_stats = coreStats(0,0,0,1,0);
                break;
            case 1: 
                name = "+1 Chestplate";
                local_stats = coreStats(1,1,1,2,1);
            break;
            case 2: 
                name = "+2 Chestplate";
                local_stats = coreStats(2,2,2,3,2);
            break;
        }
        return nullptr; // aww, no loot :c
    } 
}


void newEnemy(Fightable* in_out, const Player* base_calc) {
    if(!base_calc)
        return;
    
    if(in_out) {
        delete in_out;
        in_out = nullptr;
    }

    int lowest_hp = base_calc->us.getLvl() * 2;
    int max_hp = base_calc->us.getLvl() * 8;

    int lowest_dmg = base_calc->us.getLvl();
    int highest_dmg = base_calc->us.getLvl() * 2;

    in_out = new Fightable(Random::NTK(lowest_hp, max_hp), lowest_dmg, highest_dmg);

    in_out->xpos, in_out->ypos = Coords;

    position[in_out->xpos][in_out->ypos] = 'E';

    CurrentEnemy = in_out;
}


void openInventory() {
    system("cls");
    cout << "You look into your backpack. \n";
    cout << "------------------------------------------------------------------\n";
    bool done = false;
    inv:
    while(!done) {
        auto listItems = MainCharacter->us.getBackpackList();
        int numPossessedItems = 0;
        int itemNum = 0;
        for( const auto& item : listItems) {
            ++itemNum;
            cout << "> (" << itemNum << ")" << item->getData()->Name << "\n";
            numPossessedItems++;
        }
        if(listItems.empty()) {
            cout << "You have no items.. :/\n Press any key to exit inventory.\n";
            done = true;
            _getch();
        } else if(!listItems.empty()) {
            
            cout << "Enter number of item/armour you'd like to use.\n (enter 0 to exit)\n";
            int optNum = numChoice();
            if(optNum == 0) {
                done = true;
                break;
            } else if(optNum) {
                int UseNum = (optNum - 1);
                if(itemManager::isPotion(listItems[UseNum]))
                    itemManager::use(listItems[UseNum], &(MainCharacter->us));
                else
                    itemManager::equip(listItems[UseNum], &(MainCharacter->us));
            } else {
                cout << "Invalid input..\n";
                goto inv;
            }
        }
    }
}

// returns true on win
void enterFight(Player& player1) {
    if(!CurrentEnemy) {
        return;
    }

    // SUDDENLY. screen clears up. SURPRISE FIGHT MUAHAHAHAHAHA
    // lol jk, I just want it to be cleaner is all ¯\_(ツ)_/¯
    system("cls");
    cout << "An enemy appears before you, ready to do battle!\n";
    while(player1.isAlive() && CurrentEnemy->isAlive()) {
        cout << "The enemy awaits your move.\n";
        cout << "Player health: " << player1.us.getCurrentHP() << "/" << player1.us.getMaxHP() << "                 Enemy health: " << CurrentEnemy->enemy.HP.getCurrent() << "/" << CurrentEnemy->enemy.HP.getMax() << "\n";
        retry:
        cout << "What will you do?\n[ Attack / Inventory ]\n";
        awaitInput:
        string playerAction = playerChoice();
        if(playerAction == "attack") {
            cout << "You attack the enemy.\n";
            CurrentEnemy->enemy.HP.reduceCurrent(player1.us.meleeAtk());
        } else if(playerAction == "inventory") {
            openInventory();
        } else if(playerAction == "") {
            goto awaitInput;
        } else {
            cout << "Input not recognised. Try again.\n";
            goto retry;
        }

        if(CurrentEnemy->isAlive()){
            cout << "The enemy attacks!\n";
            player1.us.takeDmg(CurrentEnemy->enemy.Attack());
        }
        std::cout << "\n------------------------------------------------------------------\n\n";
    }

    if(player1.isAlive()) {
        cout << "You win!\n"; // victory!
        cout << "You gain " << CurrentEnemy->xpworth << " exp!\n";
        Item* item_drop = dropLoot(); // loot :D

        if(item_drop) {
            itemManager::moveToBackpack(item_drop, &player1.us);
            cout << "You find loot! You get: " << item_drop->getData()->Name << "\n";
        }

        player1.us.gainEXP(CurrentEnemy->xpworth); //give player exp
        victoryCount++; // # of enemies defeated +1
        newEnemy(CurrentEnemy, &player1); // create new enemy
        std::cout << "\n--------------- PRESS ANY KEY TO CONTINUE ---------------\n";
        _getch();
    } else {
        cout << "You were defeated!\n"; // shit happens ¯\_(ツ)_/¯
        gameOver = true;
        std::cout << "\n---  GAME OVER  ---\n";
        _getch();
    }
}

void playerWander(Player& player1) {
    player1.xpos, player1.ypos = Coords;

    if(position[player1.xpos][player1.ypos] == 'E') {
        enterFight(player1);
    };
}
#pragma endregion

