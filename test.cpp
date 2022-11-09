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

int main()
{

    std::cout << "\n--------------------- Start of test ---------------------" << endl;

    // Start of the game, player input test
    char name[50];
    std::cout << "Hello. You are a cat." << endl;
    std::cout << "What is your name?" << endl;
    cin.getline(name, 50);
    std::cout << "Welcome, " << name << "." << endl;

    std::cout << "\n--------------------- TEST BEGIN ---------------------" << endl;

    playerCharacter protag(new Cat());
    
    // Equipment test
    
    Item* WornCollar = itemManager::createArmour("Worn Collar", coreStats(0, 0, 0, 2, 1), ARMOURSLOT::NECK);
    Item* SpikyCollar = itemManager::createArmour("Spiky Collar", coreStats(0, 0, 0, 5, 3), ARMOURSLOT::NECK);
    itemManager::moveToBackpack(itemManager::createWeapon("Standard Murder Mittens", coreStats(), WEAPONSLOT::MELEE, 1, 4), &protag);
    Item* IronClaws = itemManager::createWeapon("Iron Claws", coreStats(), WEAPONSLOT::MELEE, 3, 9);
    
    itemManager::equip(WornCollar, &protag);
    itemManager::equip(SpikyCollar, &protag);
    itemManager::equip(IronClaws, &protag);

    for(int i = 0; i < 7; i++) {
        std::cout
        << protag.getClassName()
        << " - lvl  " << protag.getLvl() << '\n'
        << "- Exp:  " << protag.getCurrentEXP() << "/" << protag.getExptoLvlup() << '\n'
        << "- HP:   " << protag.getCurrentHP() << "/" << protag.getMaxHP() << '\n'
        << "- MP:   " << protag.getCurrentMP() << "/" << protag.getMaxMP() << '\n'
        << "- Strength: " << protag.getTotalStrength() << '\n'
        << "- Intellect: " << protag.getTotalIntellect() << '\n'
        << "- Agility: " << protag.getTotalAgility() << '\n'
        << "- Defence: " << protag.getTotalDefence() << '\n'
        << "- Elemental resistance: " << protag.getTotalResistance() << endl;
    
    auto allBuffs = protag.getBuffList();
    std::cout << "- Buffs:\n";
    for(auto& buff : allBuffs) {
        std::cout << "   -" << buff.Name << '\n';
    }

    auto allAbilities = protag.getAbilityList();
    std::cout << "- Abilities:\n";
    for(auto& abil : allAbilities) {
        std::cout << "   -" << abil.Name << '\n';
    }

    std::cout << "- Armour:\n";
    for(int i = 0; i < (int)ARMOURSLOT::NUM_SLOTS; i++) {
        const Armour* tmp = dynamic_cast<Armour*>(protag.getEquippedArmour(i));        
        
        if(tmp) {
            std::cout << "   " << tmp->Name << " (+" << tmp->Stats.Def << " def, +" << tmp->Stats.Res << " res)" << '\n';
        }
    }

    std::cout << "- Weapons:\n";
    for(int i = 0; i < (int)WEAPONSLOT::NUM_SLOTS; i++) {
        const Weapon* tmp = dynamic_cast<Weapon*>(protag.getEquippedWeapon(i));        
        
        if(tmp) {
            std::cout << "   " << tmp->Name << " (" << tmp->minDMG << "-" << tmp->maxDMG << " dmg)" << '\n';
        }
        }

        if(i < 1) {
        protag.gainEXP(100u);
        // debuff test
        Buff agi_debuff("ConeOfShame", 0, 0, 0, 3, 3, 2, true); // name, dur, str, int, agi, def, res, isDebuff(false by default)
        protag.applyBuff(agi_debuff);
        // buff test
        Buff int_buff("LittleShit", 5, 8, 1, 1, 1);
        protag.applyBuff(int_buff);
        }
    }

    std::cout << "hp before dmg: " << protag.getCurrentHP() << '\n';

    protag.takeDmg(20);

    Item* HealPotion = itemManager::createPotion("Small healing potion", 3u, 3u);
    itemManager::moveToBackpack(HealPotion, &protag);

    std::cout << "hp before potion: " << protag.getCurrentHP() << '\n';

    itemManager::use(HealPotion, &protag);

    std::cout << "hp after potion: " << protag.getCurrentHP() << '\n';

    {
    auto inv = protag.getBackpackList();
    std::cout << "Inventory: ";
    for(auto it : inv) {
        std::cout << *it << ", ";
    }
    }

    std::cout << '\n';

    {
    itemManager::use(HealPotion, &protag);
    cout << "Used Potion!" << endl;
    itemManager::use(HealPotion, &protag);
    cout << "Used another Potion!" << endl;
    }

    {
    auto inv = protag.getBackpackList();
    std::cout << "Inventory (AFTER USING POTIONS): ";
    for(auto it : inv) {
        std::cout << *it << ", ";
    }
    }

    std::cout << "\n--------------------- TEST END ---------------------" << endl;

    // Test function to make player inputs lowercase
    std::cout << "What colour is your fur?" << endl;
    string colour = playerChoice();
    std::cout << "You are a " << colour << " cat called " << name << "." << endl;

    // Player interaction test
    std::cout << "You encounter a *menacing* ball of yarn." << endl;
    retry:
    std::cout << "What will you do?" << endl;
    std::cout << "[ look / paw / leave ]" << endl;
    string tutorialChoice = playerChoice();
    
    if(tutorialChoice == "look")
    {
        std::cout << "You look at the ball of yarn sitting in front of you on the floor. Smells like wool." << endl;
        goto retry;
    } else if(tutorialChoice == "paw")
    {
        std::cout << "You paw at the yarn. It rolls over and stops." << endl;
        protag.gainEXP(2u);
        std::cout << "You gain 2 exp." << endl;
    } else if(tutorialChoice == "leave")
    {
        std::cout << "You decide to walk away. 'The yarn may live another day,' you think to yourself." << endl;
    } else {
        std::cout << "Input not recognised. Please try again." << endl;
        goto retry;
    }
    
    int encounterNum = 0;
    repeat:
    std::cout << "You wander around but come across nothing of interest. \n Keep wandering? [yes/no]" << endl;
    string wanderOpt = playerChoice();
    if(wanderOpt == "yes"){

        // Random encounter test
        int randomEvent;
        srand((unsigned)time(0));
        int rnum = (rand()%10) + 1;
        int pnum = (rand()%10) + 1;
        if(rnum == pnum){
            forceEncounter:
            switch(rnum){
                case 1:
                case 2:
                {
                    std::cout << "You find a <food item> that looks particularly delicious. \n Pick it up? [yes/no]" << endl;
                    string playerAction = playerChoice();
                    if(playerAction == "yes"){
                        std::cout << "You pick it up." << endl;
                        std::cout << "Obtained <food item>!" << endl;
                    } else if(playerAction == "no") {
                        std::cout << "You don't like this particular <food item>. You decide to leave it where it is." << endl;
                    }
                }
                break;
                case 3:
                case 4:
                {
                    std::cout << "You find an <item>. It might be useful. \n Pick it up? [yes/no]" << endl;
                    string playerAction = playerChoice();
                    if(playerAction == "yes"){
                        std::cout << "You pick the <item> up." << endl;
                        std::cout << "Obtained <item>!" << endl;
                    } else if(playerAction == "no"){
                        std::cout << "You ignore the <item> and walk away." << endl;
                    }
                }
                break;
                case 5:
                case 6:
                {
                    std::cout << "An <enemy> appears! They haven't noticed you yet. \n What will you do? [run/fight]" << endl;
                    string playerAction = playerChoice();
                    if(playerAction == "run"){
                        std::cout << "You flee before you're noticed." << endl;
                        std::cout << "Escaped safely." << endl;
                    } else if (playerAction == "fight"){
                        std::cout << "You take the <enemy> by surprise!" << endl;
                    }
                }
                break;
                case 7:
                case 8:
                {
                    std::cout << "You find an <item>. It might be useful. \n Pick it up? [yes/no]" << endl;
                    string playerAction = playerChoice();
                    if(playerAction == "yes"){
                        std::cout << "You pick the <item> up." << endl;
                        std::cout << "Obtained <item>!" << endl;
                    } else if(playerAction == "no"){
                        std::cout << "You decide to leave the <item> where it is." << endl;
                    }
                }
                break;
                case 9:
                case 10:
                {
                    std::cout << "You find an <item>. It might be useful. \n Pick it up? [yes/no]" << endl;
                    string playerAction = playerChoice();
                    if(playerAction == "yes"){
                        std::cout << "You pick the <item> up." << endl;
                        std::cout << "Obtained <item>!" << endl;
                    } else if(playerAction == "no"){
                        std::cout << "You decide to leave the <item> where it is." << endl;
                    }
                }
                break;
            }
        } else {
            if(encounterNum >= 4){
                rnum == pnum;
                goto forceEncounter;
            } else {
                encounterNum++;
                goto repeat;
            }
        }
    }/*  else if(wanderOpt == "openinventory"){
        std::cout << "You open your inventory." << endl;
        std::cout << "[ Stats ] - [ Items ] - [ Save ]" << endl;
        string menuOpt = playerChoice();
        
        if(menuOpt == "stats"){
            // display playerStats
        } else if(menuOpt == "items"){
            // display playerItems
        } else if(menuOpt == "save"){
            std::cout << "[ Save ] - [ Load ] - [ Exit ] - [ Back ]" << endl;
            string gameOpt = playerChoice();
            if(gameOpt == "save"){
                // saveGame(name);
            } else if(gameOpt == "load"){
                std::cout << "Savefiles found: " << /* display saves  << ". Type name of the file you want to load." << endl;
                // player input for which file should be loaded
                // loadGame(<selected save user input>)
            }
        } else if(menuOpt == "exit"){
            //exitGame();
        } else if(menuOpt == "back"){
            //goto repeat;
        }
    } */

    std::cout << "\n--------------------- End of test ---------------------" << endl;
    _getch();

    return 0;
}