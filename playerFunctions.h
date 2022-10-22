#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <algorithm>

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


// basically the same function but this one removes only EXCESS whitespace
void remove_extra_whitespaces(const string &input, string &output)
{
    output.clear();
    unique_copy (input.begin(), input.end(), back_insert_iterator<string>(output),
    [](char a,char b){ return isspace(a) && isspace(b);});  
}

// function to make player inputs lowercase to match what the program expects
string longInput() {
    string playerInput;
    string formattedInput;

    // get user input
    getline(cin, playerInput);

    // make input lowercase
    for(auto& c: playerInput) c = tolower(c,cout.getloc());

    // remove excess whitespace
    remove_extra_whitespaces(playerInput, formattedInput);

    return formattedInput;
}