#include "GameWindow.h"
#include <Windows.h>

int main() 
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	GameWindow game(600,800);

	while (game.IsRun())
	{
		game.Update();
	}

	return 0;
}