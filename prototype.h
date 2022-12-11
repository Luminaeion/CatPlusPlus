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

#define clearScreen std::system("cls");

#define INTRO\
    char name[50];\
    std::cout << "Hello. You are a cat. \n";\
    std::cout << "What is your name? \n";\
    std::cin.getline(name, 50);\
    std::cout << "Welcome, " << name << ". " << endl;\


#pragma region CHARACTERCREATION
// Create character
#define CREATECHARACTER MainCharacter = new Player(new Cat());
#pragma endregion


#pragma region DEFAULTGEAR
// Create and equip standard gear
#define DEFAULTGEAR itemManager::equip(itemManager::createWeapon("Standard Murder Mittens", coreStats(), WEAPONSLOT::MELEE, 1, 2), &MainCharacter->us);\
itemManager::equip(itemManager::createArmour("Worn Collar", coreStats(0, 0, 0, 2, 1), ARMOURSLOT::NECK), &MainCharacter->us);
#pragma endregion


#pragma region RANDOMSTARTITEMS
#define RANDOMSTARTINGITEMS \
itemManager::moveToBackpack(dropLoot(), &MainCharacter->us);\
itemManager::moveToBackpack(dropLoot(), &MainCharacter->us);
#pragma endregion


#pragma region STARTSEQUENCE
#define STARTSEQUENCE \
CREATECHARACTER \
RANDOMSTARTINGITEMS \
newEnemy(CurrentEnemy, MainCharacter);\
position[CurrentEnemy->xpos][CurrentEnemy->ypos] = 'E';\
std::cout << "" << endl;
#pragma endregion

bool yarnDefeated = false;
bool alreadyLooked = false;
bool damascus = false;
bool minibossDefeated = false;

#pragma region TUTORIAL
#define TUTORIALCHOICE \
    std::cout << "Here is a brief introduction to how this game functions.\n";\
    std::cout << "You encounter a *menacing* ball of yarn.\n";\
    retry:\
    std::cout << "What will you do?\n";\
    std::cout << "[ look / paw / leave ]\n";\
    std::cout << "(Type one of these options and hit enter.)\n";\
    tutorialNoInput:\
    string tutorialChoice = playerChoice();\
    if(tutorialChoice == "look")\
    {\
        std::cout << "You look at the ball of yarn sitting in front of you on the floor. Smells like wool.\n";\
        if(!alreadyLooked) {\
            std::cout << ". . .\n";\
            std::cout << "There is a can of tuna behind the ball of yarn. How did that get there?\n";\
            itemManager::moveToBackpack(itemManager::createPotion("Can of Tuna", 5u, 1u), &MainCharacter->us);\
            std::cout << "Obtained a CAN OF TUNA!" << endl;\
            alreadyLooked = true;\
        } else {\
            cout << "Nothing else to discover here." << endl;\
        }\
        goto retry;\
    } else if(tutorialChoice == "paw")\
    {\
        if(!yarnDefeated) {\
            std::cout << "You paw at the yarn. It rolls over and stops.\n";\
            MainCharacter->us.gainEXP(2u);\
            std::cout << "You gain 2 exp.\n";\
            std::cout << "For bravely defeating this menace, you're given a WORN COLLAR and STANDARD MURDER MITTENS!" << endl;\
            DEFAULTGEAR\
            yarnDefeated = true;\
        } else {\
            std::cout << "The yarn lies defeated a few centimeters further away.\n"\
            << "No use pawing at a defeated ball of yarn." << endl;\
        }\
        goto retry;\
    } else if(tutorialChoice == "leave")\
    {\
        if(!yarnDefeated) {\
            std::cout << "You decide to walk away. 'The yarn may live another day,' you think to yourself.\n"\
            << "An ominous feeling lurks in the back of your mind... " << endl;\
        } else {\
            std::cout << "You move on, ready for a bigger adventure." << endl;\
        }\
    } else if(tutorialChoice == "") {\
        goto tutorialNoInput;\
    } else {\
        std::cout << "Input not recognised. Please try again." << endl;\
        goto retry;\
    }
#pragma endregion


#pragma region WANDERING
// get a location to start with
string currentLocation = setLocation();
#define RANDOMENCOUNTER int randomEvent;\
    int encounterNum = 0; \
    repeat: \
    clearScreen\
    std::cout << "You wander around but come across nothing of interest. \n"\
    << "Keep wandering? [ Yes / No ]\n"; \
    noInput: \
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
                    std::cout << "You find a Fish Biscuit that looks particularly delicious. \n Pick it up? [ Yes / No ]\n";\
                    string playerAction = playerChoice();\
                    if(playerAction == "yes"){\
                        std::cout << "You pick it up.\n";\
                        itemManager::moveToBackpack(itemManager::createPotion("Fish Biscuit", 2u, 2u), &MainCharacter->us);\
                        std::cout << "Obtained Fish Biscuit!" << endl;\
                        getchar();\
                    } else if(playerAction == "no") {\
                        std::cout << "You don't like this particular Fish Biscuit. You decide to leave it where it is." << endl;\
                        getchar();\
                    }\
                    }\
                    break;\
                case 2:\
                    {\
                    std::cout << "You find a couple of Small Healing Potions. They might be useful. \n Pick them up? [ Yes / No ]\n";\
                    string playerAction = playerChoice();\
                    if(playerAction == "yes"){\
                        std::cout << "You pick the Small Healing Potions up.\n";\
                        itemManager::moveToBackpack(itemManager::createPotion("Small Healing Potion", 2u, 2u), &MainCharacter->us);\
                        std::cout << "Obtained Small Healing Potions (x2)!" << endl;\
                        getchar();\
                    } else if(playerAction == "no"){\
                        std::cout << "You ignore the Small Healing Potions and walk away." << endl;\
                        getchar();\
                    }\
                    }\
                    break;\
                case 7:\
                    {\
                    if(!yarnDefeated) {\
                        customEnemy(CurrentEnemy);\
                        std::cout << "Your nemesis - the *MENACING* BALL OF YARN - returns with a vengeance!" << endl;\
                        enterFight(*MainCharacter, name);\
                        if(MainCharacter->isAlive()) { std::cout << "You defeated the ball of yarn!\n";\
                        yarnDefeated = true; }\
                    } else if(yarnDefeated && !damascus && minibossDefeated) {\
                        std::cout << "You arrive in the place where you defeated your nemesis.\n"\
                        << "You find a neat weapon here. The pattern reminds you of yarn...\n";\
                        itemManager::moveToBackpack(itemManager::createWeapon("Nemesis' Damascus Steel Knife", coreStats(), WEAPONSLOT::MELEE, 3, 7, false), &MainCharacter->us);\
                        std::cout << "Obtained NEMESIS' DAMASCUS STEEL KNIFE!" << endl;\
                        damascus = true;\
                        std::cin.ignore(100, '\n');\
                        getchar();\
                    } else {\
                        std::cout << "An enemy appears!" << endl;\
                        getchar();\
                        enterFight(*MainCharacter, name);\
                        getchar();\
                    }\
                    }\
                    break;\
                case 3:\
                case 8:\
                    {\
                    std::cout << "An enemy appears!" << endl;\
                    getchar();\
                    enterFight(*MainCharacter, name);\
                    getchar();\
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
                        std::cout << "Obtained Cool Stick!" << endl;\
                        getchar();\
                    } else if(playerAction == "no"){\
                        std::cout << "You decide to leave the Cool Stick where it is." << endl;\
                        getchar();\
                    }\
                    }\
                    break;\
                case 5:\
                case 10:\
                    {\
                    std::cout << "You find a Tophat. \n Do you want to bring it with you? [ Yes / No ]\n";\
                    string playerAction = playerChoice();\
                    if(playerAction == "yes"){\
                        std::cout << "You plop the Tophat on your head. It makes you feel dapper.\n";\
                        itemManager::equip(itemManager::createArmour("Tophat", coreStats(1, 3, 0, 1, 0), ARMOURSLOT::HEAD), &MainCharacter->us);\
                        std::cout << "Obtained Tophat!" << endl;\
                        getchar();\
                    } else if(playerAction == "no"){\
                        std::cout << "You decide to leave the Tophat where it is. You reckon you're dapper enough already." << endl;\
                        getchar();\
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
    std::cout << "[ look around / wander / check stats / open inventory ]" << endl;\
    awaitInput:\
    string playerInput = longInput();\
    \
    if(playerInput == "wander"){\
        wander = true;\
        string currentLocation = setLocation();\
        goto wander;\
    } else if (playerInput == "look around") {\
        std::cout << "You look around. You see a " << currentLocation << "." << endl;\
        DISCOVERY\
        goto exploration;\
    } else if (playerInput == "check stats") {\
        std::cout << "You sit down and examine yourself.\n";\
        DisplayCharacterSheet(name);\
        std::cout << "Finished with your brief moment of reflection, you get up, ready to continue onward." << endl;\
        goto exploration;\
    } else if(playerInput == "open inventory") {\
        openInventory(false); /* bool inCombat */\
        goto exploration;\
    } else if(playerInput == "") {\
        goto awaitInput;\
    } else {\
        std::cout << "Input not recognised. Please try again." << endl;\
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
        std::cout << "Input not recognised, please try again." << endl;\
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
        Item* CatTreat = itemManager::createPotion("Cat treat", 1u, 3u);
        generatedItem = CatTreat;
        break;
        }
    case 1:
        {
        Item* FishBiscuit = itemManager::createPotion("Fish biscuit", 2u, 2u);
        generatedItem = FishBiscuit;
        break;
        }
    case 2:
        {
        Item* Catnip = itemManager::createPotion("Catnip", 3u, 2u);
        generatedItem = Catnip;
        break;
        }
    case 3:
        {
        Item* CanOTuna = itemManager::createPotion("Can of Tuna", 5u, 1u);
        generatedItem = CanOTuna;
        break;
        }
    case 4: // weapons 8-11
        {
        Item* SharpClaws = itemManager::createWeapon("Sharp Claws", coreStats(), WEAPONSLOT::MELEE, 1, 3);
        generatedItem = SharpClaws;
        break;
        }
    case 5:
        {
        Item* SharpTeeth = itemManager::createWeapon("Sharp Teeth", coreStats(), WEAPONSLOT::MELEE, 1, 4);
        generatedItem = SharpTeeth;
        break;
        }
    case 6:
        {
        Item* ButterKnife = itemManager::createWeapon("Butter knife", coreStats(), WEAPONSLOT::MELEE, 2, 4);
        generatedItem = ButterKnife;
        break;
        }
    case 7:
        {
        Item* TitaniumSpoon = itemManager::createWeapon("Titanium Spoon", coreStats(), WEAPONSLOT::MELEE, 2, 3);
        generatedItem = TitaniumSpoon;
        break;
        }
    case 8: // armour 12-15
    case 9:
        {
        Item* SpikyCollar = itemManager::createArmour("Spiky Collar", coreStats(0, 0, 0, 2, 1), ARMOURSLOT::NECK);
        generatedItem = SpikyCollar;
        break;
        }
    case 10:
    case 11:
        {
        Item* LeatherBoots = itemManager::createArmour("Leather Boots", coreStats(0, 0, 1, 3, 2), ARMOURSLOT::FEET);
        generatedItem = LeatherBoots;
        }
    }
    std::cout << "Discovered " << *generatedItem << ".\n";
    itemManager::moveToBackpack(generatedItem, &MainCharacter->us);
}
#pragma endregion


#pragma region DISCOVERY
#define DISCOVERY \
CHECKIFANYTHINGFOUND \
if(encounteredSomething){\
    std::cout << "You find something!\n";\
    generateRandomThing();\
} else {\
    std::cout << "You don't find anything of interest in the area." << endl;\
}
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

void customEnemy(Fightable* in_out) {
    if(in_out) {
        delete in_out;
        in_out = nullptr;
    }

    in_out = new Fightable(14, 3, 7);

    CurrentEnemy = in_out;
}


bool actionTaken = false;

void openInventory(bool inCombat) {
    std::cout << "------------------------------------------------------------------" << endl;\
    bool done = false;
    clearScreen
    std::cout << "You look into your backpack. \n";
    inv:
    while(!done && !actionTaken) {
        auto listItems = MainCharacter->us.getBackpackList();
        int numPossessedItems = 0;
        int itemNum = 0;
        for( const auto& item : listItems) {
            ++itemNum;
            if(itemManager::isPotion(item)) {
                Potion* potion = nullptr;
                itemManager::castItemToPotion(item, potion);
                if(potion){
                    stringstream itemQuant;
                    itemQuant << " (x " << potion->Quantity << ")";
                    string quant = itemQuant.str();
                    std::cout << "> (" << itemNum << ")" << item->getData()->Name << quant << "\n";
                }
            } else {
                std::cout << "> (" << itemNum << ")" << item->getData()->Name << "\n";
            }
            numPossessedItems++;
        }
        if(listItems.empty()) {
            std::cout << "You have no items.. :/\n Press enter to exit inventory." << endl;\
            done = true;
            getchar();
        } else if(!listItems.empty()) {
            std::cout << "Enter number of item/armour you'd like to use.\n (enter 0 to exit)" << endl;\
            int optNum = numChoice();
            if(optNum == 0) {
                done = true;
                clearScreen
                break;
            } else if(optNum) {
                clearScreen
                int UseNum = (optNum - 1);
                if(itemManager::isPotion(listItems[UseNum])){
                    itemManager::use(listItems[UseNum], &(MainCharacter->us));
                } else {
                    itemManager::equip(listItems[UseNum], &(MainCharacter->us));
                }
                if(inCombat) { actionTaken = true; }
            } else {
                std::cout << "Invalid input.." << endl;\
                goto inv;
            }
        }
    }
}

// returns true on win
void enterFight(Player& player1, string characterName) {
    if(!CurrentEnemy) {
        return;
    }

    // SUDDENLY. screen clears up. SURPRISE FIGHT MUAHAHAHAHAHA
    // lol jk, I just want it to be cleaner is all ¯\_(ツ)_/¯
    clearScreen
    std::cout << "An enemy appears before you, ready to do battle!\n";
    while(player1.isAlive() && CurrentEnemy->isAlive()) {
        std::cout << "The enemy awaits your move.\n";
        std::cout << characterName <<"'s health: " << player1.us.getCurrentHP() << "/" << player1.us.getMaxHP() << "                 Enemy health: " << CurrentEnemy->enemy.HP.getCurrent() << "/" << CurrentEnemy->enemy.HP.getMax() << "\n";
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
            std::cout << "Input not recognised. Try again." << endl;\
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
        std::cout << "\n--------------- PRESS ENTER TO CONTINUE ---------------" << endl;
    } else {
        std::cout << "You were defeated!\n"; // shit happens ¯\_(ツ)_/¯
        wander = false;
        gameOver = true;
        std::cout << "\n---  GAME OVER  ---" << endl;\
        getchar();
    }
}

void playerWander(Player& player1, string characterName) {
    player1.xpos, player1.ypos = Coords;

    if(position[player1.xpos][player1.ypos] == 'E') {
        enterFight(player1, characterName);
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
    //clearScreen
    std::cout << "------------------------------------------------------------------\n"
    << "Your character - " << characterName << " the cat\n"
    << "Lvl: " << MainCharacter->us.getLvl() << " - Exp: " << MainCharacter->us.getCurrentEXP() << "/" << MainCharacter->us.getExptoLvlup() << "\n"
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
    std::cout << "Press enter to continue" << endl;\
    getchar();
}
#pragma endregion