#include "MainMenuState.h"


/**
 *	Constructor
 *	@params:
 *		window -> Pointer to a window that would draw any of state drawings
 *		states -> Pointer to stack of points for states, that are currently need to process
 *	
 *	Inhered from State
 *
 *	Creating buttons of "Start Game" and "Exit Game"
 */
MainMenuState::MainMenuState(sf::RenderWindow * window, std::stack<State*>* _states)
	:State(window, _states)
{
	this->startBtn = new Button(200, 400, 200, 50, &this->font, "Start", 36);
	this->quitBtn = new Button(200, 500, 200, 50, &this->font, "Quit", 36);
}


/**
 *	Update of State:
 *
 *	-	Updating Mouse Position;
 *	-	Updating Status of buttons for current mouse position;
 *	-	Updating current state depending on buttons status.
 */
void MainMenuState::Update()
{
	this->UpdateMousePositions();
	this->startBtn->Update(this->mousePosWindow);
	this->quitBtn->Update(this->mousePosWindow);

	if (this->startBtn->isPressed())
	{
		this->states->push(new GameState(&this->window, this->states));
	}

	if (this->quitBtn->isPressed())
	{
		this->states->top()->EndState();
	}
}

void MainMenuState::UpdateInput()
{
}

/**
 *	Draw buttons of State
 *	
 *	Create and Draw name of game on Window
 *	Also Drawing button by passing pointer to a window
 */
void MainMenuState::Render()
{
	sf::Text text(sf::String("BRICK"), this->font, 72);
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f((600 - text.getGlobalBounds().width) / 2, 150));
	this->window.draw(text);

	text.setString(sf::String("CHALLENGER"));
	text.setPosition(sf::Vector2f((600 - text.getGlobalBounds().width) / 2, 220));
	this->window.draw(text);

	this->startBtn->Render(this->window);
	this->quitBtn->Render(this->window);
}
