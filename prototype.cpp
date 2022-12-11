#include "prototype.h"

int main() {
    
    std::cout << "\n--------------------- PROTOTYPE START ---------------------\n";

    while(!gameOver){

        INTRO

        CREATECHARACTER

        newEnemy(CurrentEnemy, MainCharacter);

        position[CurrentEnemy->xpos][CurrentEnemy->ypos] = 'E';
        
        TUTORIALCHOICE

        std::cout << "- - Press enter to continue - -\n";
        _getch();

        clearScreen

        // give the mc two random items to start with :)
        itemManager::moveToBackpack(dropLoot(), &MainCharacter->us);
        itemManager::moveToBackpack(dropLoot(), &MainCharacter->us);
        
        std::cout << "\n------------------------------------------------------------------\n"
        << "Well done! You got the hang of it quickly. You'll run into more choices like this as you move on.\n"
        << "Don't worry, though. You'll always be able to view your options when you're presented with a choice.\n"
        << "Have fun! :)\n"
        << "The game begins now. Good luck!\n"
        << "------------------------------------------------------------------\n\n";
        
        EXPLORATION
        while(wander) { playerWander(*MainCharacter); }
    }

    cout << "Total # of enemies defeated: " << victoryCount << "\n";
    std::cout << "\n------------------------------------------------------------------\n";
    std::cout << "\n--------------------- PROTOTYPE END ---------------------";
    _getch();

    return 0;
}