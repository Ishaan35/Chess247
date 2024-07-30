#ifndef TERMINALINPUT_H
#define TERMINALINPUT_H

#include "inputSource.h"
#include "../moveStructs/setupMove.h"
#include "../pieces/pieceType.h"

class TerminalInput : public InputSource
{
	InputMove getInput() override;

	string trim(const string& str);

	SetupMove getSetup() override;

	PieceType getPromotion() override;

	pair<int, int> getDimensions();

	bool processPosition(string token, char &file, char &rank);
};

#endif