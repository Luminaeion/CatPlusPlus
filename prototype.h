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
bool wander = false;

#define INTRO\
    char name[50];\
    std::cout << "Hello. You are a cat. \n";\
    std::cout << "What is your name? \n";\
    std::cin.getline(name, 50);\
    std::cout << "Welcome, " << name << ". \n";


#pragma region CHARACTERCREATION
// Create character
#define CREATECHARACTER MainCharacter = new Player(new Cat());
#pragma endregion


#pragma region DEFAULTGEAR
// Create and equip standard gear
#define DEFAULTGEAR itemManager::equip(itemManager::createWeapon("Standard Murder Mittens", coreStats(), WEAPONSLOT::MELEE, 1, 2), &MainCharacter->us);\
itemManager::equip(itemManager::createArmour("Worn Collar", coreStats(0, 0, 0, 2, 1), ARMOURSLOT::NECK), &MainCharacter->us);
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
        std::cout << "For bravely defeating this menace, you're given a WORN COLLAR and STANDARD MURDER MITTENS!\n";\
        DEFAULTGEAR\
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
    repeat:\
    std::cout << "You wander around but come across nothing of interest. \n Keep wandering? [yes / no]\n";\
    noInput:\
    string wanderOpt = playerChoice();\
    if(wanderOpt == "yes"){\
        wander = true;\
        int randomEvent;\
        srand((unsigned)time(0));\
        int rnum = rng(4);\
        int pnum = rng(4);\
        if(rnum == pnum){\
            forceEncounter:\
            int encNum = rng(10);\
            switch(encNum){\
                case 1:\
                case 6:\
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
                case 2:\
                case 7:\
                    {\
                    std::cout << "You find a Small Healing Potion. It might be useful. \n Pick it up? [ Yes / No ]\n";\
                    string playerAction = playerChoice();\
                    if(playerAction == "yes"){\
                        std::cout << "You pick the Small Healing Potion up.\n";\
                        itemManager::moveToBackpack(itemManager::createPotion("Small Healing Potion", 1u, 1u), &MainCharacter->us);\
                        std::cout << "Obtained Small Healing Potion!\n";\
                    } else if(playerAction == "no"){\
                        std::cout << "You ignore the Small Healing Potion and walk away.\n";\
                    }\
                    }\
                    break;\
                case 3:\
                case 8:\
                    {\
                    std::cout << "An enemy appears!\n";\
                    _getch();\
                    enterFight(*MainCharacter);\
                    }\
                    break;\
                case 4:\
                case 9:\
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
                case 5:\
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
    } else if(wanderOpt == "") {\
        goto noInput;\
    }
#pragma endregion


#pragma region EXPLORATION
#define EXPLORATION \
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
        DisplayCharacterSheet(name);\
        std::cout << "Finished with your brief moment of reflection, you get up, ready to continue onward.\n";\
        goto exploration;\
    } else if(playerInput == "open inventory") {\
        openInventory(false); /* bool inCombat */\
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
        } else {\
        cout << "Input not recognised, please try again.\n";\
        goto repeat;\
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
    std::cout << "Discovered " << *generatedItem << ".\n";
}
#pragma endregion


#pragma region DISCOVERY
#define DISCOVERY \
CHECKIFANYTHINGFOUND \
if(encounteredSomething){\
    std::cout << "You find something!\n";\
    generateRandomThing();\
} else {\
    std::cout << "You don't find anything of interest in the area.\n";\
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


bool actionTaken = false;

void openInventory(bool inCombat) {
    std::cout << "------------------------------------------------------------------\n";
    bool done = false;
    system("cls");
    std::cout << "You look into your backpack. \n";
    inv:
    while(!done && !actionTaken) {
        auto listItems = MainCharacter->us.getBackpackList();
        int numPossessedItems = 0;
        int itemNum = 0;
        for( const auto& item : listItems) {
            ++itemNum;
            std::cout << "> (" << itemNum << ")" << item->getData()->Name << "\n";
            numPossessedItems++;
        }
        if(listItems.empty()) {
            std::cout << "You have no items.. :/\n Press any key to exit inventory.\n";
            done = true;
            _getch();
        } else if(!listItems.empty()) {
            
            std::cout << "Enter number of item/armour you'd like to use.\n (enter 0 to exit)\n";
            int optNum = numChoice();
            if(optNum == 0) {
                done = true;
                break;
            } else if(optNum) {
                // NOTE TO SELF! STACKED POTIONS DON'T SHOW HOW MANY ARE STACKED! WHEN USING THEM IT LOOKS LIKE YOU'RE NOT REALLY USING THEM AT ALL UNTIL YOU USE THE LAST ONE
                int UseNum = (optNum - 1);
                if(itemManager::isPotion(listItems[UseNum])){
                    itemManager::use(listItems[UseNum], &(MainCharacter->us));
                } else {
                    itemManager::equip(listItems[UseNum], &(MainCharacter->us));
                }
                if(inCombat) { actionTaken = true; }
            } else {
                std::cout << "Invalid input..\n";
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
    std::cout << "An enemy appears before you, ready to do battle!\n";
    while(player1.isAlive() && CurrentEnemy->isAlive()) {
        std::cout << "The enemy awaits your move.\n";
        std::cout << "Player health: " << player1.us.getCurrentHP() << "/" << player1.us.getMaxHP() << "                 Enemy health: " << CurrentEnemy->enemy.HP.getCurrent() << "/" << CurrentEnemy->enemy.HP.getMax() << "\n";
        retry:
        std::cout << "What will you do?\n[ Attack / Inventory ]\n";
        awaitInput:
        string playerAction = playerChoice();
        if(playerAction == "attack") {
            std::cout << "You attack the enemy.\n";
            CurrentEnemy->enemy.HP.reduceCurrent(player1.us.meleeAtk());
        } else if(playerAction == "inventory") {
            openInventory(true); // bool inCombat
        } else if(playerAction == "") {
            goto awaitInput;
        } else {
            std::cout << "Input not recognised. Try again.\n";
            goto retry;
        }

        if(CurrentEnemy->isAlive()){
            std::cout << "The enemy attacks!\n";
            player1.us.takeDmg(CurrentEnemy->enemy.Attack());
            actionTaken = false;
        }
        std::cout << "\n------------------------------------------------------------------\n\n";
    }

    if(player1.isAlive()) {
        std::cout << "You win!\n"; // victory!
        std::cout << "You gain " << CurrentEnemy->xpworth << " exp!\n";
        Item* item_drop = dropLoot(); // loot :D

        if(item_drop) {
            itemManager::moveToBackpack(item_drop, &player1.us);
            std::cout << "You find loot! You get: " << item_drop->getData()->Name << "\n";
        }

        player1.us.gainEXP(CurrentEnemy->xpworth); //give player exp
        victoryCount++; // # of enemies defeated +1
        newEnemy(CurrentEnemy, &player1); // create new enemy
        std::cout << "\n--------------- PRESS ANY KEY TO CONTINUE ---------------\n";
        _getch();
    } else {
        std::cout << "You were defeated!\n"; // shit happens ¯\_(ツ)_/¯
        wander = false;
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


string getArmourStats(const Armour* Armour) {
        stringstream stats;
        stats << " ( ";
        if(Armour->Stats.Str != 0) { stats << "+" << Armour->Stats.Str << " Str "; }
        if(Armour->Stats.Int != 0) { stats << "+" << Armour->Stats.Int << " Int "; }
        if(Armour->Stats.Agi != 0) { stats << "+" << Armour->Stats.Agi << " Agi "; }
        if(Armour->Stats.Def != 0) { stats << "+" << Armour->Stats.Def << " Def "; }
        if(Armour->Stats.Res != 0) { stats << "+" << Armour->Stats.Res << " Res "; }
        stats << ")";
        string armourStats = stats.str();
        return armourStats;
    }


#pragma region CHARACTERSHEET
void DisplayCharacterSheet(string characterName) {
    //system("cls");
    std::cout << "------------------------------------------------------------------\n"
    << "Your character - " << characterName << " the cat\n"
    << "Health: " << MainCharacter->us.getCurrentHP() << "/" << MainCharacter->us.getMaxHP() << "\n"
    << "Str: " << MainCharacter->us.getTotalStrength() << "\n"
    << "Int: " << MainCharacter->us.getTotalIntellect() << "\n"
    << "Agi: " << MainCharacter->us.getTotalAgility() << "\n"
    << "Def: " << MainCharacter->us.getTotalDefence() << "\n"
    << "Res: " << MainCharacter->us.getTotalResistance() << "\n"
    << "Equipped gear: \n";
    // Melee weapon
    if(MainCharacter->us.getEquippedWeapon((unsigned long long)WEAPONSLOT::MELEE)) {
        #define weaponM MainCharacter->us.getEquippedWeapon((unsigned long long)WEAPONSLOT::MELEE)
        std::cout << "Melee: " << weaponM->Name << " (" << weaponM->minDMG << "-" << weaponM->maxDMG <<  " dmg)\n";
    }
    // Ranged weapon
    if(MainCharacter->us.getEquippedWeapon((unsigned long long)WEAPONSLOT::RANGED)) {
        #define weaponR MainCharacter->us.getEquippedWeapon((unsigned long long)WEAPONSLOT::RANGED)
        std::cout << "Ranged: " << weaponR->Name << " (" << weaponR->minDMG << "-" << weaponR->maxDMG <<  " dmg)\n";
    }

    // Head
    if(MainCharacter->us.getEquippedArmour((unsigned long long)ARMOURSLOT::HEAD)) {
        #define armourHead MainCharacter->us.getEquippedArmour((unsigned long long)ARMOURSLOT::HEAD)
        std::cout << "Head: " << armourHead->Name << getArmourStats(armourHead) << "\n";
    }
    // Neck
    if(MainCharacter->us.getEquippedArmour((unsigned long long)ARMOURSLOT::NECK)) {
        #define armourNeck MainCharacter->us.getEquippedArmour((unsigned long long)ARMOURSLOT::NECK)
        std::cout << "Neck: " << armourNeck->Name << getArmourStats(armourNeck) << "\n";
    }
    // Chest
    if(MainCharacter->us.getEquippedArmour((unsigned long long)ARMOURSLOT::CHEST)) {
        #define armourChest MainCharacter->us.getEquippedArmour((unsigned long long)ARMOURSLOT::CHEST)
        std::cout << "Chest: " << armourChest->Name << getArmourStats(armourChest) << "\n";
    }
    // Hands
    if(MainCharacter->us.getEquippedArmour((unsigned long long)ARMOURSLOT::HANDS)) {
        #define armourHands MainCharacter->us.getEquippedArmour((unsigned long long)ARMOURSLOT::HANDS)
        std::cout << "Front paws: " << armourHands->Name << getArmourStats(armourHands) << "\n";
    }
    // Ring #1
    if(MainCharacter->us.getEquippedArmour((unsigned long long)ARMOURSLOT::RING1)) {
        #define armourRingOne MainCharacter->us.getEquippedArmour((unsigned long long)ARMOURSLOT::RING1)
        std::cout << "Ring 1: " << armourRingOne->Name << getArmourStats(armourRingOne) << "\n";
    }
    // Ring #2
    if(MainCharacter->us.getEquippedArmour((unsigned long long)ARMOURSLOT::RING2)) {
        #define armourRingTwo MainCharacter->us.getEquippedArmour((unsigned long long)ARMOURSLOT::RING2)
        std::cout << "Ring 2: " << armourRingTwo->Name << getArmourStats(armourRingTwo) << "\n";
    }
    // Legs
    if(MainCharacter->us.getEquippedArmour((unsigned long long)ARMOURSLOT::LEGS)) {
        #define armourLegs MainCharacter->us.getEquippedArmour((unsigned long long)ARMOURSLOT::LEGS)
        std::cout << "Legs: " << armourLegs->Name << getArmourStats(armourLegs) << "\n";
    }
    // Feet
    if(MainCharacter->us.getEquippedArmour((unsigned long long)ARMOURSLOT::FEET)) {
        #define armourFeet MainCharacter->us.getEquippedArmour((unsigned long long)ARMOURSLOT::FEET)
        std::cout << "Back paws: " << armourFeet->Name << getArmourStats(armourFeet) << "\n";
    }

    std::cout << "\n------------------------------------------------------------------\n";
    std::cout << "Press enter to continue\n";
    _getch();
}
#pragma endregion