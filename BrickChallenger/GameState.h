#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "MainMenuState.h"

class GameState :
	public State
{
private:
	bool newLine;

	int dirR = 0;
	int dirM = 0;
	Player* player;

	int level;
	int destroyedBlocks;
	int score;

	std::vector<Block*> blocks;
	bool lose;

	Button* restartBtn;
	Button* backToMenuBtn;

public:
	GameState(sf::RenderWindow* window, std::stack<State*>* _states);

	Block* GenerateBlock(int x, int y);

	void Update();
	void UpdateInput();

	void UpdateGame();
	void UpdateDeath();

	void Render();

	void RenderGame();
	void RenderInfo();
};

#endif GAMESTATE_H