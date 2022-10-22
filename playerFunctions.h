#include <iostream>
#include <bits/stdc++.h>
#include <string>

using namespace std;

// function to make player inputs lowercase to match what the program expects
string playerChoice() {
    string playerInput;
    getline(cin, playerInput);
    playerInput.erase(remove(playerInput.begin(), playerInput.end(), ' '), playerInput.end());
    for(auto& c: playerInput) c = tolower(c,cout.getloc());
    /*transform(playerInput.begin(), playerInput.end(), playerInput.begin(), ::tolower);
    playerInput.erase(remove(playerInput.begin(), playerInput.end(), ' '), playerInput.end());*/
    return playerInput;
}