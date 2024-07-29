#ifndef TERMINALINPUT_H
#define TERMINALINPUT_H

#include "inputSource.h"
#include "../moveStructs/setupMove.h"
#include "../pieces/pieceType.h"

class TerminalInput : public InputSource
{
	InputMove getInput() override;

	SetupMove getSetup() override;

	pair<int, int> getDimensions();

	bool processPosition(string token, char &file, char &rank);
};

#endif