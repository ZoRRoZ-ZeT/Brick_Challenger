#include "GameWindow.h"

/**
 *	Constructor
 *	@params:
 *		w -> width of Window
 *		h -> Height of Window
 */
GameWindow::GameWindow(int w, int h)
{
	this->width = w;
	this->height = h;
	this->window = new sf::RenderWindow(sf::VideoMode(this->width, this->height), "Brick Challanger");
	this->window->setFramerateLimit(60);
	this->status = true;
	
	this->states.push(new MainMenuState(this->window,&this->states));
}

/**
 *	Update of Window
 *	Updates current window for current State
 */
void GameWindow::Update()
{
	sf::Event event;
	while (this->window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed || this->states.top()->GetQuit())
		{
			this->window->close();
			this->status = false;
		}

		this->states.top()->UpdateInput();

	}

	this->states.top()->Update();
	
	Render();
}

/**
 *	Render of Window
 *	Draw all graphics in window for current State
 */
void GameWindow::Render()
{
	this->window->clear();

	this->states.top()->Render();

	
	this->window->display();
}

/**
 *	Function represent status of window
 *	@return value of it status (Is window is opened or not)
 */
bool GameWindow::IsRun()
{
	return this->status;
}
