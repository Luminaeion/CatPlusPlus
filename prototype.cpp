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

    EXPLORATION

    std::cout << "\n--------------------- PROTOTYPE END ---------------------";
    _getch();

    return 0;
}