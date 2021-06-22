#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "State.h"
#include "GameState.h"

class MainMenuState :
	public State
{
private:
	Button* startBtn;
	Button* quitBtn;
public:
	MainMenuState(sf::RenderWindow* window, std::stack<State*>* _states);

	void Update();
	void UpdateInput();

	void Render();
};

#endif MAINMENUSTATE_H
