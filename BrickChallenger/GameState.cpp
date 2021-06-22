#include "GameState.h"

GameState::GameState(sf::RenderWindow * window, std::stack<State*>* _states)
	:State(window, _states)
{
	this->player = new Player(&this->blocks);
	this->newLine = false;
	this->level = 1;
	this->score = 0;
	this->destroyedBlocks = 0;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (rand() % (5 - this->level / 5) == 1 || (rand() % 3 > 0 && this->level >= 25))
				blocks.push_back(GenerateBlock(1.f + j * 62.f, 41.f + i * 62.f));
		}
	}
	this->lose = false;

	this->restartBtn = new Button(200, 500, 200, 50, &this->font, "Restart", 36);
	this->backToMenuBtn = new Button(200, 600, 200, 50, &this->font, "Back To Menu", 36);
}

Block * GameState::GenerateBlock(int x, int y)
{
	int difficult = this->level * 5;
	Block * block = new Block(sf::Vector2f(x, y), rand() % difficult + difficult, this->score);
	return block;
}

void GameState::Update()
{
	if (!lose)
		UpdateGame();
	else
		UpdateDeath();
}

void GameState::UpdateInput()
{
	if (!this->player->GetShooting() && !this->newLine)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
			dirR = -1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
			dirR = 1;
		else
			dirR = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			dirM = -1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			dirM = 1;
		else
			dirM = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			this->player->Shoot();
			dirR = 0;
			dirM = 0;
		}
	}
	else
	{
		this->newLine = true;
	}
}

void GameState::UpdateGame()
{
	if (newLine && !this->player->GetShooting())
	{
		dirR = 0;
		dirM = 0;
		newLine = false;
		for (int j = 0; j < 8; ++j)
		{
			if (rand() % (5 - this->level / 5) == 1 || (rand() % 3 > 0 && this->level >= 25))
				blocks.push_back(GenerateBlock(1.f + j * 62.f, 41.f - 62.f));
		}
		for (int i = 0; i < this->blocks.size(); i++)
		{
			this->blocks[i]->StartMoving();
		}
	}
	switch (dirR)
	{
	case -1:
		this->player->Rotate(-0.5f);
		break;
	case 1:
		this->player->Rotate(0.5f);
		break;
	}

	switch (dirM)
	{
	case -1:
		this->player->Move(-2);
		break;
	case 1:
		this->player->Move(2);
		break;
	}

	if (this->player->GetShootTimer() > 12.f)
	{
		for (int i = 0; i < 5; ++i)
		{
			this->player->Update();
		}
	}
	this->player->Update();

	for (int i = 0; i < this->blocks.size(); ++i)
	{
		this->blocks[i]->Update();
		if (this->blocks[i]->GetStatus())
		{
			this->blocks.erase(this->blocks.begin() + i);
			this->destroyedBlocks++;
			if (destroyedBlocks == this->level + 10)
			{
				this->level++;
				this->destroyedBlocks = 0;
				this->player->IncreaseBullets();
			}
		}
		if (this->blocks[i]->GetShape().getPosition().y > 660)
		{
			this->lose = true;
		}
	}
}

void GameState::UpdateDeath()
{
	this->UpdateMousePositions();
	this->restartBtn->Update(this->mousePosWindow);
	this->backToMenuBtn->Update(this->mousePosWindow);

	if (this->restartBtn->isPressed())
	{
		this->states->push(new GameState(&this->window, this->states));
	}

	if (this->backToMenuBtn->isPressed())
	{
		this->states->push(new MainMenuState(&this->window, this->states));
	}
}

void GameState::Render()
{
	if (this->lose)
	{
		
		sf::Text text(sf::String("You Lose!"), this->font, 44);
		text.setFillColor(sf::Color::White);
		text.setPosition(sf::Vector2f((600 - text.getGlobalBounds().width) / 2, 250));
		this->window.draw(text);

		text.setString(sf::String("Your score: " + std::to_string(this->score)));
		text.setCharacterSize(26);
		text.setPosition(sf::Vector2f((600 - text.getGlobalBounds().width) / 2, 330));
		this->window.draw(text);

		this->restartBtn->Render(this->window);
		this->backToMenuBtn->Render(this->window);
	}
	else
	{
		RenderGame();
		RenderInfo();
	}
}

void GameState::RenderGame()
{
	this->window.draw(this->player->GetShape());

	for (int i = 0; i < this->blocks.size(); i++)
	{
		this->window.draw(this->blocks[i]->GetShape());
		this->window.draw(this->blocks[i]->GetText());
	}
	this->window.draw(this->player->getLine(), 2, sf::Lines);

	for (auto i : this->player->GetBullets())
	{
		this->window.draw(i->GetShape());
	}
}

void GameState::RenderInfo()
{
	sf::RectangleShape infoBlock;
	infoBlock.setSize(sf::Vector2f(600, 38));
	infoBlock.setFillColor(sf::Color(50, 50, 50));
	this->window.draw(infoBlock);

	sf::Text text(sf::String("Level: " + std::to_string(this->level)), this->font, 28);
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f(0, 0));
	this->window.draw(text);

	text.setString(sf::String("Score: " + std::to_string(this->score)));
	text.setPosition(sf::Vector2f(600 - text.getGlobalBounds().width - 1, 0));
	this->window.draw(text);
}
