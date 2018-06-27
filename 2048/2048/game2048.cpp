#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <conio.h>

#include "game2048.h"

using namespace std;

void Game2048::print() const {
	for (int i = 0; i < 4; i++) {
		printf("+------+------+------+------+\n");
		for (int j = 0; j < 4; j++) {
			if (plane[i][j] != 0) {
				printf("|%5d ", plane[i][j]);
			} else {
				printf("|      ");
			}
		}
		printf("|\n");
	}
	printf("+------+------+------+------+\n");
}

int Game2048::mergable() const {
	int ret = UNMERGEABLE;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (plane[i][j] != 0 && plane[i][j] == plane[i][j + 1]) {
				ret |= HORIZONTAL;
				break;
			}
		}
	}
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 3; i++) {
			if (plane[i][j] != 0 && plane[i][j] == plane[i + 1][j]) {
				ret |= VERTICAL;
				break;
			}
		}
	}
	return ret;
}

bool Game2048::Up() {
	bool ret;
	ret = up();
	if (ret) {
		add();
		return true;
	} else {
		if (mergable() == UNMERGEABLE && full()) {
			status = -1;
		}
		return false;
	}
}

bool Game2048::Left() {
	bool ret;
	ret = left();
	if (ret) {
		add();
		return true;
	} else {
		if (mergable() == UNMERGEABLE && full()) {
			status = -1;
		}
		return false;
	}
}

bool Game2048::Down() {
	bool ret;
	ret = down();
	if (ret) {
		add();
		return true;
	} else {
		if (mergable() == UNMERGEABLE && full()) {
			status = -1;
		}
		return false;
	}
}

bool Game2048::Right() {
	bool ret;
	ret = right();
	if (ret) {
		add();
		return true;
	} else {
		if (mergable() == UNMERGEABLE && full()) {
			status = -1;
		}
		return false;
	}
}

bool Game2048::up() {
	bool movable = false;
	for (int j = 0; j < 4; j++) {
		int count = 0, i = 0;
		for (i = 0; i < 4; i++) {
			if (plane[i][j] != 0) {
				if (count != i) {
					movable = true;
				}
				plane[count++][j] = plane[i][j];
			}
		}
		for (i = count; i < 4; i++) {
			plane[i][j] = 0;
		}
		i = 0;
		while (i < 3) {
			if (plane[i][j] != 0 && plane[i][j] == plane[i + 1][j]) {
				plane[i][j] *= 2;
				if (plane[i][j] == TERMINAL) {
					status = 1;
				}
				plane[i + 1][j] = 0;
				occupied--;
				i += 2;
				movable = true;
			} else {
				i++;
			}
		}
		count = 0;
		for (i = 0; i < 4; i++) {
			if (plane[i][j] != 0) {
				plane[count++][j] = plane[i][j];
			}
		}
		for (i = count; i < 4; i++) {
			plane[i][j] = 0;
		}
	}
	return movable;
};

bool Game2048::down() {
	bool movable = false;
	for (int j = 0; j < 4; j++) {
		int count = 3, i = 3;
		for (i = 3; i >= 0; i--) {
			if (plane[i][j] != 0) {
				if (count != i) {
					movable = true;
				}
				plane[count--][j] = plane[i][j];
			}
		}
		for (i = count; i >= 0; i--) {
			plane[i][j] = 0;
		}
		i = 3;
		while (i > 0) {
			if (plane[i][j] != 0 && plane[i][j] == plane[i - 1][j]) {
				plane[i][j] *= 2;
				if (plane[i][j] == TERMINAL) {
					status = 1;
				}
				plane[i - 1][j] = 0;
				occupied--;
				i -= 2;
				movable = true;
			} else {
				i--;
			}
		}
		count = 3;
		for (i = 3; i >= 0; i--) {
			if (plane[i][j] != 0) {
				plane[count--][j] = plane[i][j];
			}
		}
		for (i = count; i >= 0; i--) {
			plane[i][j] = 0;
		}
	}
	return movable;
};

bool Game2048::left() {
	bool movable = false;
	for (int i = 0; i < 4; i++) {
		int count = 0, j = 0;
		for (j = 0; j < 4; j++) {
			if (plane[i][j] != 0) {
				if (count != j) {
					movable = true;
				}
				plane[i][count++] = plane[i][j];
			}
		}
		for (j = count; j < 4; j++) {
			plane[i][j] = 0;
		}
		j = 0;
		while (j < 3) {
			if (plane[i][j] != 0 && plane[i][j] == plane[i][j + 1]) {
				plane[i][j] *= 2;
				if (plane[i][j] == TERMINAL) {
					status = 1;
				}
				plane[i][j + 1] = 0;
				occupied--;
				j += 2;
				movable = true;
			} else {
				j++;
			}
		}
		count = 0;
		for (j = 0; j < 4; j++) {
			if (plane[i][j] != 0) {
				plane[i][count++] = plane[i][j];
			}
		}
		for (j = count; j < 4; j++) {
			plane[i][j] = 0;
		}
	}
	return movable;
};

bool Game2048::right() {
	bool movable = false;
	for (int i = 0; i < 4; i++) {
		int count = 3, j = 3;
		for (j = 3; j >= 0; j--) {
			if (plane[i][j] != 0) {
				if (count != j) {
					movable = true;
				}
				plane[i][count--] = plane[i][j];
			}
		}
		for (j = count; j >= 0; j--) {
			plane[i][j] = 0;
		}
		j = 3;
		while (j > 0) {
			if (plane[i][j] != 0 && plane[i][j] == plane[i][j - 1]) {
				plane[i][j] *= 2;
				if (plane[i][j] == TERMINAL) {
					status = 1;
				}
				plane[i][j - 1] = 0;
				occupied--;
				j -= 2;
				movable = true;
			} else {
				j--;
			}
		}
		count = 3;
		for (j = 3; j >= 0; j--) {
			if (plane[i][j] != 0) {
				plane[i][count--] = plane[i][j];
			}
		}
		for (j = count; j >= 0; j--) {
			plane[i][j] = 0;
		}
	}
	return movable;
};

void Game2048::add() {
	int pos, i, j;
	srand(time(NULL));
	do {
		pos = rand() % 16;
		i = pos / 4;
		j = pos % 4;
	} while (plane[i][j] != 0);
	plane[i][j] = 2;
	occupied++;
};

bool Game2048::full() const {
	printf("occupied = %d\n", occupied);
	return occupied == 16;
};

bool Game2048::fail() const {
	return status == -1;
}

bool Game2048::win() const {
	return status == 1;
}

