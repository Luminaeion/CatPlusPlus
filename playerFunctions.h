#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <algorithm>

using namespace std;

// function to make player inputs lowercase to match what the program expects, no spaces
string playerChoice() {
    string playerInput;
    getline(cin, playerInput);
    playerInput.erase(remove(playerInput.begin(), playerInput.end(), ' '), playerInput.end());
    for(auto& c: playerInput) c = tolower(c,cout.getloc());
    return playerInput;
}

// function to remove only excess whitespace
void remove_extra_whitespaces(const string &input, string &output)
{
    output.clear();
    unique_copy (input.begin(), input.end(), back_insert_iterator<string>(output),
    [](char a,char b){ return isspace(a) && isspace(b);});  
}

// make player inputs lowercase to match what the program expects, leaves singular spaces between words
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

int rng(int maxNum) {
    int randomNumber = (rand()%maxNum) + 1;
    return randomNumber;
}

string setLocation() {
        int rndloc = rng(5);
        string locations[] = { "pond", "forest", "backyard", "location4", "location5" };
        return locations[rndloc];
    }