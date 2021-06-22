#include "State.h"


/**
 *	Constructor
 *	@params:
 *		window -> Pointer to a window that would draw any of state drawings
 *		states -> Pointer to stack of points for states, that are currently need to process
 */
State::State(sf::RenderWindow * window, std::stack<State*>* _states)
	:window(*window)
{
	this->states = _states;
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");
}


/**
 *	Update of Mouse
 *	
 *	Changing variable to position of mouse in current moment
 */
void State::UpdateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(this->window);
}

/**
 *	Function represent status of State
 *	@return value of event, is state is going to close window
 */
const bool & State::GetQuit() const
{
	return this->quit;
}

/**
 *	Setting current state to become the last one, which going to close window
 */
void State::EndState()
{
	this->quit = true;
}
