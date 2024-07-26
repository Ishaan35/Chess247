#ifndef TERMINALINPUT_H
#define TERMINALINPUT_H

#include "inputSource.h"

class TerminalInput : public InputSource
{
	InputMove getInput() override {
		return InputMove{make_pair(0, 0), make_pair(0, 0), false};
	}
};

#endif