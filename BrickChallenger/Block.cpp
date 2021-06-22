#include "Block.h"

Block::Block(sf::Vector2f startPos, int _health, int& refToScore)
	:score(refToScore)
{
	this->shape = new sf::RectangleShape(sf::Vector2f(60.f,60.f));
	this->shape->setPosition(startPos);
	this->position = new sf::Vector2f(startPos.x,startPos.y);
	this->shape->setOutlineThickness(1.f);
	this->shape->setFillColor(sf::Color::Black);
	this->health = _health;
	this->IsDestroyed = false;
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");
	this->blockHP = sf::Text(sf::String(std::to_string(this->health)), font, 36);
	this->blockHP.setFillColor(this->blockColor);
	this->blockHP.setPosition(sf::Vector2f(
		this->position->x + this->shape->getGlobalBounds().width / 2.f - this->blockHP.getGlobalBounds().width / 2.f,
		this->position->y + this->shape->getGlobalBounds().height / 2.f - 22));
}

void Block::Hit()
{
	this->health--;
	this->score++;
	if (health == 0)
		IsDestroyed = true;
}

const sf::RectangleShape& Block::GetShape() const
{
	return *this->shape;
}

const int& Block::GetHealth() const
{
	return this->health;
}

const sf::Color& Block::GetColor() const
{
	return this->blockColor;
}

const bool& Block::GetStatus() const
{
	return this->IsDestroyed;
}

const bool& Block::GetMoving() const
{
	return this->isMoving;
}

const sf::Text& Block::GetText() const
{
	return this->blockHP;
}

void Block::MoveNext()
{
	if (this->position->y < this->previousY + 60.f)
		this->position->y += 5;
	else
		this->isMoving = false;
}

void Block::StartMoving()
{
	this->isMoving = true;
	this->previousY = this->position->y;
}

void Block::Update()
{
	if (this->health > 75)
		blockColor = sf::Color::Red;
	else if (this->health > 50)
		blockColor = sf::Color::Yellow;
	else if (this->health > 25)
		blockColor = sf::Color::Green;
	else
		blockColor = sf::Color::White;

	this->shape->setOutlineColor(blockColor);
	this->shape->setPosition(*this->position);
	
	UpdateText();

	if (this->isMoving)
		MoveNext();
}

void Block::UpdateText()
{
	this->blockHP.setString(sf::String(std::to_string(this->health)));
	this->blockHP.setPosition(sf::Vector2f(
		this->position->x + this->shape->getGlobalBounds().width / 2.f - this->blockHP.getGlobalBounds().width / 2.f,
		this->position->y + this->shape->getGlobalBounds().height / 2.f - 22));
	this->blockHP.setFillColor(blockColor);
}
