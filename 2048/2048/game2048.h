#pragma once

#include <vector>

using std::vector;

class Game2048 {
private:
	vector<vector<int>> plane;
	int size;
	int terminal;

	int occupied;
	int status;

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
	static const int OPT_UP = 0;
	static const int OPT_LEFT = 1;
	static const int OPT_DOWN = 2;
	static const int OPT_RIGHT = 3;

	Game2048(int _size = 4, int _terminal = 2048) {
		size = _size;
		terminal = _terminal;
		for (int i = 0; i < size; i++) {
			plane.emplace_back(vector<int>(size, 0));
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

inline bool Game2048::full() const
{
	return occupied == size * size;
};

inline bool Game2048::fail() const
{
	return full() && (mergable() == UNMERGEABLE);
}

inline bool Game2048::win() const
{
	return status == 1;
}

