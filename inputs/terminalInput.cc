#include "terminalInput.h"
#include <string>
#include <iostream>
using namespace std;

SetupMove TerminalInput::getSetup(){
    string token;
    cin >> token;
    SetupMove move{};

    if (token == "done"){
        move.isDone = true;
    }
    else if (token == "="){
        cin >> token;
        if (token == "black" || token == "white"){
            move.isChangeTurn = true;
        }
        else{
            throw std::runtime_error("incorrect colour specified");  
        } 
    }
    else if(token == "+"){
        move.isPlace = true;
        cin >> token;
        if(token == "");
    }
}

InputMove TerminalInput::getInput(){}

pair<int, int> TerminalInput::getDimensions(){}