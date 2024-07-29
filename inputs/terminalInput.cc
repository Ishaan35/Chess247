#include "terminalInput.h"
#include <string>
#include <iostream>
#include <cctype>

using namespace std;

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
            move.playerColor == (token == "white") ? Color::WHITE : Color::BLACK;
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

InputMove TerminalInput::getInput()
{
    InputMove move{};

    string token;
    cin >> token;
    if (token == "resign")
    {
        move.isResign = true;
        return move;
    }

    if (token != "move")
    {
        throw std::runtime_error("incorrect move command format");
    }
    cin >> token;
    bool res = processPosition(token, move.from.first, move.from.second);
    if (!res)
    {
        throw std::runtime_error("incorrect from location format");
    }

    cin >> token;
    res = processPosition(token, move.to.first, move.to.second);
    if (!res)
    {
        throw std::runtime_error("incorrect to location format");
    }

    return move;
}

pair<int, int> TerminalInput::getDimensions(){
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