#pragma once

#include <array>

using std::array;

class Game2048 {
private:
	array<array<int, 4>, 4> plane;
	int occupied;
	int status;

	// some constants
	static const int TERMINAL = 2048;

	// mergeable status
	static const int UNMERGEABLE = 0x0;
	static const int HORIZONTAL = 0x1;
	static const int VERTICAL = 0x2;
	static const int MERGEABLE = 0x3;

	// private methods
	bool up();

	bool down();

	bool left();

	bool right();

	void add();

	bool full() const;

public:
	Game2048() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				plane[i][j] = 0;
			}
		}
		occupied = 0;
		status = 0;
		add();
		add();
	};

	~Game2048() {};

	void print() const;

	int mergable() const;

	bool Up();

	bool Left();

	bool Down();

	bool Right();

	bool fail() const;

	bool win() const;
};
