#include "GameState.h"
#include "MainMenuState.h"

class GameWindow
{
private:
	sf::RenderWindow * window;
	int width;
	int height;
	std::stack<State*> states;

	bool status;

public:
	GameWindow(int w, int h);

	void Update();
	void Render();

	bool IsRun();
};

