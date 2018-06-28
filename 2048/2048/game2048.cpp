#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <conio.h>

#include "game2048.h"

using namespace std;

void Game2048::print() const
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("+------");
		}
		printf("+\n");
		for (int j = 0; j < size; j++) {
			if (plane[i][j] != 0) {
				printf("|%5d ", plane[i][j]);
			} else {
				printf("|      ");
			}
		}
		printf("|\n");
	}
	for (int j = 0; j < size; j++) {
		printf("+------");
	}
	printf("+\n");
}

int Game2048::mergable() const
{
	int ret = UNMERGEABLE;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (plane[i][j] != 0 && plane[i][j] == plane[i][j + 1]) {
				ret |= HORIZONTAL;
				break;
			}
		}
	}
	for (int j = 0; j < size; j++) {
		for (int i = 0; i < size - 1; i++) {
			if (plane[i][j] != 0 && plane[i][j] == plane[i + 1][j]) {
				ret |= VERTICAL;
				break;
			}
		}
	}
	return ret;
}

#define MOVE_RETURN(direction) do {\
	bool ret = direction(); \
	if (ret) { \
		add(); \
		return true; \
	} else { \
		if (mergable() == UNMERGEABLE && full()) { \
			status = -1; \
		} \
		return false; \
	} \
} while (0)

bool Game2048::Up()
{
	MOVE_RETURN(up);
}

bool Game2048::Left()
{
	MOVE_RETURN(left);
}

bool Game2048::Down()
{
	MOVE_RETURN(down);
}

bool Game2048::Right()
{
	MOVE_RETURN(right);
}

bool Game2048::up()
{
	bool movable = false;
	int i, j, count;
	for (j = 0; j < size; j++) {
		count = 0;
		for (i = 0; i < size; i++) {
			if (plane[i][j] != 0) {
				if (count != i) {
					movable = true;
				}
				plane[count++][j] = plane[i][j];
			}
		}
		for (i = count; i < size; i++) {
			plane[i][j] = 0;
		}
		i = 0;
		while (i < size - 1) {
			if (plane[i][j] != 0 && plane[i][j] == plane[i + 1][j]) {
				plane[i][j] *= 2;
				if (plane[i][j] == terminal) {
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
		for (i = 0; i < size; i++) {
			if (plane[i][j] != 0) {
				plane[count++][j] = plane[i][j];
			}
		}
		for (i = count; i < size; i++) {
			plane[i][j] = 0;
		}
	}
	return movable;
};

bool Game2048::down()
{
	bool movable = false;
	int i, j, count;
	for (j = 0; j < size; j++) {
		count = size - 1;
		for (i = size - 1; i >= 0; i--) {
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
		i = size - 1;
		while (i > 0) {
			if (plane[i][j] != 0 && plane[i][j] == plane[i - 1][j]) {
				plane[i][j] *= 2;
				if (plane[i][j] == terminal) {
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
		count = size - 1;
		for (i = size - 1; i >= 0; i--) {
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

bool Game2048::left()
{
	bool movable = false;
	int i, j, count;
	for (i = 0; i < size; i++) {
		count = 0;
		for (j = 0; j < size; j++) {
			if (plane[i][j] != 0) {
				if (count != j) {
					movable = true;
				}
				plane[i][count++] = plane[i][j];
			}
		}
		for (j = count; j < size; j++) {
			plane[i][j] = 0;
		}
		j = 0;
		while (j < size - 1) {
			if (plane[i][j] != 0 && plane[i][j] == plane[i][j + 1]) {
				plane[i][j] *= 2;
				if (plane[i][j] == terminal) {
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
		for (j = 0; j < size; j++) {
			if (plane[i][j] != 0) {
				plane[i][count++] = plane[i][j];
			}
		}
		for (j = count; j < size; j++) {
			plane[i][j] = 0;
		}
	}
	return movable;
};

bool Game2048::right()
{
	bool movable = false;
	int i, j, count;
	for (i = 0; i < size; i++) {
		count = size - 1;
		for (j = size - 1; j >= 0; j--) {
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
		j = size - 1;
		while (j > 0) {
			if (plane[i][j] != 0 && plane[i][j] == plane[i][j - 1]) {
				plane[i][j] *= 2;
				if (plane[i][j] == terminal) {
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
		count = size - 1;
		for (j = size - 1; j >= 0; j--) {
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

void Game2048::add()
{
	int pos, i, j;
	srand((unsigned)time(NULL));
	do {
		pos = rand() % (size * size);
		i = pos / size;
		j = pos % size;
	} while (plane[i][j] != 0);
	plane[i][j] = 2;
	occupied++;
};
