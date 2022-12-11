#include "prototype.h"

int main() {
    
    std::cout << "\n--------------------- PROTOTYPE START ---------------------\n";

    while(!gameOver){

        STARTSEQUENCE

        INTRO

        TUTORIALCHOICE

        std::cout << "- - Press enter to continue - -\n";
        _getch();

        clearScreen
        
        std::cout << "\n------------------------------------------------------------------\n"
        << "Well done! You got the hang of it quickly. You'll run into more choices like this as you move on.\n"
        << "Don't worry, though. You'll always be able to view your options when you're presented with a choice.\n"
        << "------------------------------------------------------------------\n\n";
        std::cout << "You're free to explore the world now!\n";
        std::cout << "> You can LOOK AROUND in your current location. There is a small chance that you'll find something here.\n"
        << "> You can also WANDER around. This is an action that is beneficial to repeat.\n"
        << "You may find ITEMS, GEAR or encounter ENEMIES. After a few instances of finding nothing, you get a guaranteed encounter.\n"
        << "> Additionally you can CHECK STATS to see your character's health, stats, equipped gear and abilities.\n"
        << "> You're also free to OPEN your INVENTORY and use as many items or swap your gear as many times as you'd like.\n"
        << "HOWEVER! During combat you can either attack or use/equip ONE item/gear per turn. Use your turns wisely!\n\n"
        << "------------------------------------------------------------------\n\n";
        std::cout << "The game begins now. Good luck, " << name << "!\n\n";

        EXPLORATION
        while(wander) { playerWander(*MainCharacter, name); }
    }

    cout << "Total # of enemies defeated: " << victoryCount << "\n";
    std::cout << "\n------------------------------------------------------------------\n";
    std::cout << "\n--------------------- PROTOTYPE END ---------------------";
    _getch();

    return 0;
}