#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <bits/stdc++.h>

#include "cat.h"
#include "playerFunctions.hpp"

using namespace std;

int main()
{

    cout << "\n--------------------- Start of test ---------------------" << endl;

    // Start of the game, player input test
    char name[50];
    cout << "Hello. You are a cat." << endl;
    Cat catProtag;
    // Stat display! :)
    cout << "Cat\n"
        << "- MaxHP: " << catProtag.getMaxHP() << '\n'
        << "- Strength: " << catProtag.getStrength() << endl;
    cout << "What is your name?" << endl;
    cin.getline(name, 50);
    cout << "Welcome, " << name << "." << endl;

    cout << "\n--------------------- LVLUP TEST BEGIN ---------------------" << endl;

    Cat protag;
    for(int i = 0; i < 4; i++) {
        cout
        << "Cat - lvl " << protag.getLvl() << '\n'
        << "- Exp: " << protag.getCurrentEXP() << "/" << protag.getExptoLvlup() << '\n'
        << "- MaxHP: " << protag.getMaxHP() << '\n'
        << "- Strength: " << protag.getStrength() << endl;
    if(i < 5)
    protag.gainEXP(100u);
    }

    cout << "\n--------------------- LVLUP TEST END ---------------------" << endl;

    // Test function to make player inputs lowercase
    cout << "What colour is your fur?" << endl;
    string colour = playerChoice();
    cout << "You are a " << colour << " cat called " << name << "." << endl;

    // Player interaction test
    cout << "You encounter a *menacing* ball of yarn." << endl;
    retry:
    cout << "What will you do?" << endl;
    cout << "[ Look ] - [ Paw ] - [ Leave ]" << endl;
    string tutorialChoice = playerChoice();
    
    if(tutorialChoice == "look")
    {
        cout << "You look at the ball of yarn sitting in front of you on the floor. Smells like wool." << endl;
        goto retry;
    } else if(tutorialChoice == "paw")
    {
        cout << "You paw at the yarn. It rolls over and stops." << endl;
        cout << "You gain 2 exp." << endl;
    } else if(tutorialChoice == "leave")
    {
        cout << "You decide to walk away. 'The yarn may live another day,' you think to yourself." << endl;
    } else {
        cout << "Input not recognised. Please try again." << endl;
        goto retry;
    }
    
    int encounterNum = 0;
    string wanderOpt;
    repeat:
    cout << "You wander around but come across nothing of interest. Keep wandering?" << endl;
    cin >> wanderOpt;
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
                    string playerAction;
                    cout << "You find a <food item> that looks particularly delicious. Pick it up?" << endl;
                    cout << "Yes or no" << endl;
                    cin >> playerAction;
                    if(playerAction == "yes"){
                        cout << "You pick it up." << endl;
                        cout << "Obtained <food item>!" << endl;
                    } else if(playerAction == "no") {
                        cout << "You don't like this particular <food item>. You decide to leave it where it is." << endl;
                    }
                }
                break;
                case 3:
                case 4:
                {
                    string playerAction;
                    cout << "You find an <item>. It might be useful. Pick it up?" << endl;
                    cout << "Yes or no" << endl;
                    cin >> playerAction;
                    if(playerAction == "yes"){
                        cout << "You pick the <item> up." << endl;
                        cout << "Obtained <item>!" << endl;
                    } else if(playerAction == "no"){
                        cout << "You ignore the <item> and walk away." << endl;
                    }
                }
                break;
                case 5:
                case 6:
                {
                    string playerAction;
                    cout << "An <enemy> appears! They haven't noticed you yet." << endl;
                    cout << "What will you do?" << endl;
                    cin >> playerAction;
                    if(playerAction == "run"){
                        cout << "You flee before you're noticed." << endl;
                        cout << "Escaped safely." << endl;
                    } else if (playerAction == "fight"){
                        cout << "You take the <enemy> by surprise!" << endl;
                    }
                }
                break;
                case 7:
                case 8:
                {
                    string playerAction;
                    cout << "You find an <item>. It might be useful. Pick it up?" << endl;
                    cout << "Yes or no" << endl;
                    cin >> playerAction;
                    if(playerAction == "yes"){
                        cout << "You pick the <item> up." << endl;
                        cout << "Obtained <item>!" << endl;
                    } else if(playerAction == "no"){
                        cout << "You decide to leave the <item> where it is." << endl;
                    }
                }
                break;
                case 9:
                case 10:
                {
                    string playerAction;
                    cout << "You find an <item>. It might be useful. Pick it up?" << endl;
                    cout << "Yes or no" << endl;
                    cin >> playerAction;
                    if(playerAction == "yes"){
                        cout << "You pick the <item> up." << endl;
                        cout << "Obtained <item>!" << endl;
                    } else if(playerAction == "no"){
                        cout << "You decide to leave the <item> where it is." << endl;
                    }
                }
                break;
            }
        } else {
            if(encounterNum >= 4){
                rnum == pnum;
                goto forceEncounter;
            } else {
                encounterNum++;goto repeat;
            }
        }
    }/*  else if(wanderOpt == "openinventory"){
        cout << "You open your inventory." << endl;
        cout << "[ Stats ] - [ Items ] - [ Save ]" << endl;
        string menuOpt = playerChoice();
        
        if(menuOpt == "stats"){
            // display playerStats
        } else if(menuOpt == "items"){
            // display playerItems
        } else if(menuOpt == "save"){
            cout << "[ Save ] - [ Load ] - [ Exit ] - [ Back ]" << endl;
            string gameOpt = playerChoice();
            if(gameOpt == "save"){
                // saveGame(name);
            } else if(gameOpt == "load"){
                cout << "Savefiles found: " << /* display saves  << ". Type name of the file you want to load." << endl;
                // player input for which file should be loaded
                // loadGame(<selected save user input>)
            }
        } else if(menuOpt == "exit"){
            //exitGame();
        } else if(menuOpt == "back"){
            //goto repeat;
        }
    } */

    cout << "\n--------------------- End of test ---------------------" << endl;
    _getch();

    return 0;
}