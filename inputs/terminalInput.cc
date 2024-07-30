#include "terminalInput.h"
#include <string>
#include <iostream>
#include <cctype>
#include <sstream>
#include <vector>

using namespace std;

string TerminalInput::trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos) {
        return ""; // no content
    }
    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, last - first + 1);
}

bool TerminalInput::processPosition(string token, char &file, char &rank)
{
    if (token.length() != 2 || !islower(token[0]) || !isdigit(token[1]))
    {
        return false;
    }
    file = token[0];
    rank = token[1];
    return true;
}

SetupMove TerminalInput::getSetup()
{
    string token;
    cin >> token;
    SetupMove move{};

    if (token == "done")
    {
        move.isDone = true;
    }
    else if (token == "=")
    {
        cin >> token;
        if (token == "black" || token == "white")
        {
            move.isChangeTurn = true;
            move.playerColor = (token == "white") ? Color::WHITE : Color::BLACK;
        }
        else
        {
            throw std::runtime_error("incorrect colour specified");
        }
    }
    else if (token == "+")
    {
        move.isPlace = true;
        cin >> token;
        if (token.length() > 1)
        {
            throw std::runtime_error("represent piece with 1 char");
        }
        move.playerColor = isupper(token[0]) ? Color::WHITE : Color::BLACK;
        char pieceChar = token[0];
        if (!PieceTypeConverter::isValidPiece(PieceTypeConverter::charToPieceType(pieceChar)))
            throw std::runtime_error("incorrect piece character input");

        move.pieceType = PieceTypeConverter::charToPieceType(pieceChar);
        string token;
        cin >> token;
        bool res = processPosition(token, move.file, move.rank);
        if (!res)
        {
            throw std::runtime_error("incorrect location format");
        }
    }
    else if (token == "-")
    {
        move.isRemove = true;
        string token;
        cin >> token;
        bool res = processPosition(token, move.file, move.rank);
        if (!res)
        {
            throw std::runtime_error("incorrect location format");
        }
    }
    else
    {
        throw std::runtime_error("invalid setup option character");
    }
    return move;
}

InputMove TerminalInput::getInput() {
    InputMove move{};
    std::string token;

    while (true) { // Loop until a valid move is entered
        std::cout << "Enter your move: ";
        getline(std::cin, token);
        std::string trimmedToken = trim(token);

        if (trimmedToken == "resign") {
            move.isResign = true;
            return move;
        }

        std::vector<std::string> result;
        std::istringstream iss(trimmedToken);
        std::string part;
        while (iss >> part) {
            result.push_back(part);
        }

        if (result.size() != 3 && result.size() != 4) {
            std::cout << "Incorrect move command format. Please try again.\n";
            continue; 
        }

        if (result[0] != "move") {
            std::cout << "Incorrect move command format. Please try again.\n";
            continue; 
        }

        bool res = processPosition(result[1], move.from.first, move.from.second);
        if (!res) {
            std::cout << "Incorrect from location format. Please try again.\n";
            continue;
        }

        res = processPosition(result[2], move.to.first, move.to.second);
        if (!res) {
            std::cout << "Incorrect to location format. Please try again.\n";
            continue;
        }

        if (result.size() == 4) {
            if (result[3].length() == 1 && PieceTypeConverter::isValidChar(result[3][0])) {
                move.promotion = result[3][0];
            } else {
                std::cout << "Invalid promotion piece. Please try again.\n";
                continue;
            }
        }

        return move; // If all checks pass, return the valid move
    }
}

pair<int, int> TerminalInput::getDimensions()
{
    cout << "Enter board dimensions" << endl; // use the observer pattern
    int rows, cols;
    pair<int, int> dims{};
    if (cin >> rows)
    {
        dims.first = rows;
    }
    else
    {
        throw std::runtime_error("invalid row input");
    }
    if (cin >> cols)
    {
        dims.second = cols;
    }
    else
    {
        throw std::runtime_error("invalid column input");
    }
    return dims;
}