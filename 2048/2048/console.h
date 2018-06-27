#pragma once

#include "game2048.h"

class ConsoleGame2048 {
private:
	Game2048 game;

	// some constants for keyboard control.
	static const int KEY_LOWER_W = 0x77;
	static const int KEY_LOWER_A = 0x61;
	static const int KEY_LOWER_S = 0x73;
	static const int KEY_LOWER_D = 0x64;
	static const int KEY_ARROW_PRE = 0xe0;
	static const int KEY_ARROW_UP = 0x48;
	static const int KEY_ARROW_LEFT = 0x4b;
	static const int KEY_ARROW_DOWN = 0x50;
	static const int KEY_ARROW_RIGHT = 0x4d;

	static const int OPT_UP = 0;
	static const int OPT_LEFT = 1;
	static const int OPT_DOWN = 2;
	static const int OPT_RIGHT = 3;

public:
	void run();
};
