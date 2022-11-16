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

    std::cout << "\n--------------------- PROTOTYPE END ---------------------";
    _getch();

    return 0;
}