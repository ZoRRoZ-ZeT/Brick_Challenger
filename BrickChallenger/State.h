#ifndef STATE_H
#define STATE_H
#include "Button.h"

class State
{
protected:
	sf::Vector2i mousePosWindow;
	sf::RenderWindow& window;
	sf::Font font;

	std::stack<State*>* states;
	bool quit;
public:
	State(sf::RenderWindow* window, std::stack<State*>* _states);

	virtual void Update() = 0;
	virtual void UpdateInput() = 0;
	virtual void Render() = 0;
	void UpdateMousePositions();

	const bool& GetQuit() const;

	void EndState();
};

#endif STATE_H