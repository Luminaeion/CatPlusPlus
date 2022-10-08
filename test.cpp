#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

// function to make player inputs lowercase to match what the program expects
string playerChoice() {
    string playerInput;
    cin >> playerInput;
    transform(playerInput.begin(), playerInput.end(), playerInput.begin(), ::tolower);
    return playerInput;
}

int main()
{
    cout << "\n--------------------- Start of test ---------------------" << endl;

    // Start of the game, player input test
    char name[50];
    cout << "Hello. You are a cat." << endl;
    cout << "What is your name?" << endl;
    cin.getline(name, 50);
    cout << "Welcome, " << name << "." << endl;

    // Test function to make player inputs lowercase
    cout << "What colour is your fur?" << endl;
    string colour = playerChoice();
    cout << "You are a " << colour << " cat called " << name << "." << endl;

    // Player interaction test
    string tutorialChoice;
    cout << "You encounter a *menacing* ball of yarn." << endl;
    retry:
    cout << "What will you do?" << endl;
    cout << "[ Look ] - [ Paw ] - [ Leave ]" << endl;
    cin >> tutorialChoice;
    
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

    string wanderAround;
    repeat:
    cout << "You wander around but come across nothing of interest. Keep wandering?" << endl;
    cin >> wanderAround;
    if(wanderAround == "yes"){

    
    // Random encounter test
    int randomEvent;
    int encounterNum;
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
        if(encounterNum < 4){
            encounterNum++;
        } else if(encounterNum >= 4) {
            rnum == pnum;
            goto forceEncounter;
        }
        goto repeat;
    }
    }

    cout << "\n--------------------- End of test ---------------------" << endl;
    _getch();

    return 0;
}