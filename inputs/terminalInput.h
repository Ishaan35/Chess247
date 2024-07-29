#ifndef TERMINALINPUT_H
#define TERMINALINPUT_H

#include "inputSource.h"
#include "../moveStructs/setupMove.h"

class TerminalInput : public InputSource
{
	InputMove getInput() override;

	SetupMove getSetup() override;

	pair<int, int> getDimensions();
};

#endif