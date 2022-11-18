#include "prototype.h"

int main() {
    
    std::cout << "\n--------------------- PROTOTYPE START ---------------------\n";

    char name[50];
    std::cout << "Hello. You are a cat. \n";
    std::cout << "What is your name? \n";
    std::cin.getline(name, 50);
    std::cout << "Welcome, " << name << ". \n";

    CREATECHARACTER

    DEFAULTGEAR

    CHARACTERINFO

    TUTORIALCHOICE

    std::cout << "\n------------------------------------------------------------------\n";
    std::cout << "Well done! You got the hang of it quickly. You'll run into more choices like this as you move on.\n";
    std::cout << "Don't worry, though. You'll always be able to view your options when you're presented with a choice.\n"; 
    std::cout << "Have fun! :)\n";
    std::cout << "------------------------------------------------------------------\n";

#pragma region EXPLORATION // move into exploration section of prototype header
    bool wander = false;
    
    exploration:
    std::cout << "What would you like to do next?\n";
    std::cout << "[ look around / wander / check stats ]\n";
    string playerInput = longInput();

    if(playerInput == "wander"){
        wander = true;
        goto wander;
    } else if (playerInput == "look around") {
        // generate random environment here
        std::cout << "This is a placeholder. :)\n";
        goto exploration;
    } else if (playerInput == "check stats") {
        std::cout << "You sit down and examine yourself.\n";
        CHARACTERINFO
        std::cout << "Finished with your brief moment of reflection, you get up, ready to continue onward.\n";
        goto exploration;
    } else {
        std::cout << "Input not recognised. Please try again.\n";
        goto exploration;
    }

    wander:
    while(wander){
        RANDOMENCOUNTER
        else if(wanderOpt == "no"){
            wander = false;
            goto exploration;
        }
    }
#pragma endregion

    std::cout << "\n--------------------- PROTOTYPE END ---------------------";
    _getch();

    return 0;
}