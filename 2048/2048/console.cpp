#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <conio.h>

#include "console.h"

using namespace std;

void ConsoleGame2048::run()
{
	printf("Start game.\n");
	printf("Use WSAD or ¡ü¡ý¡û¡ú to control the direction.\n");
	game.print();
	int key_code, opt, ret;
	while (1) {
		key_code = _getch();
		if (key_code == KEY_ARROW_PRE) {
			key_code = _getch();
			switch (key_code) {
			case KEY_ARROW_UP:
				opt = OPT_UP;
				break;
			case KEY_ARROW_LEFT:
				opt = OPT_LEFT;
				break;
			case KEY_ARROW_DOWN:
				opt = OPT_DOWN;
				break;
			case KEY_ARROW_RIGHT:
				opt = OPT_RIGHT;
				break;
			default:
				continue;
			}
		} else {
			switch (key_code) {
			case KEY_LOWER_W:
				opt = OPT_UP;
				break;
			case KEY_LOWER_A:
				opt = OPT_LEFT;
				break;
			case KEY_LOWER_S:
				opt = OPT_DOWN;
				break;
			case KEY_LOWER_D:
				opt = OPT_RIGHT;
				break;
			default:
				continue;
			}
		}
		switch (opt) {
		case OPT_UP:
			ret = game.Up();
			break;
		case OPT_LEFT:
			ret = game.Left();
			break;
		case OPT_DOWN:
			ret = game.Down();
			break;
		case OPT_RIGHT:
			ret = game.Right();
			break;
		default:
			goto label_exit;
			break;
		}
		system("cls");
		printf("Use WSAD or ¡ü¡ý¡û¡ú to control the direction.\n");
		game.print();
		if (!ret) {
			printf("Cannot move\n");
		}
		if (game.fail()) {
			printf("You Lose\n");
			goto label_exit;
		} else if (game.win()) {
			printf("You Win\n");
			goto label_exit;
		}
	}
label_exit:
	printf("Game Over\n");
	system("pause");
}
