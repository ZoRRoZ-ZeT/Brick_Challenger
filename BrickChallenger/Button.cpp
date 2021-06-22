#include "Button.h"


/**
 *	Constructor
 *	@params:
 *		x				-> Position on X-axis of Button
 *		y				-> Position on Y-axis of Button
 *		width			-> Width of Button
 *		height			-> Height of Button
 *		font			-> pointer to a font, used for text of button
 *		text			-> Content of Button
 *		character_size	-> Size of Content
 */
Button::Button(float x, float y, float width, float height, sf::Font * font, std::string text, unsigned character_size)
{
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(sf::Color(70, 70, 70, 0));
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(sf::Color::Transparent);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color(200, 200, 200, 200));
	this->text.setCharacterSize(character_size);

	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y
	);

	this->textIdleColor = sf::Color(200, 200, 200, 200);
	this->textHoverColor = sf::Color(255, 255, 255, 255);
	this->textActiveColor = sf::Color(100, 100, 100, 100);

	this->idleColor = sf::Color(70, 70, 70, 0);
	this->hoverColor = sf::Color(150, 150, 150, 0);
	this->activeColor = sf::Color(50, 50, 50, 0);

	this->outlineIdleColor = sf::Color::Transparent;
	this->outlineHoverColor = sf::Color::Transparent;
	this->outlineActiveColor = sf::Color::Transparent;
}


/**
 *	Function represent status of Button
 *	@return value of status, which mean if Button is pressed or not
 */
const bool& Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;

	return false;
}

/**
 *	Function represent content of Button
 *	@return value of text, that button is show
 */
const std::string& Button::getText() const
{
	return this->text.getString();
}

/**
 *	Updating Button
 *	@params mousePosWindow -> Position of mouse in current time
 *	
 *	Checking for mouse inputs and changing Button states depending on this
 */
void Button::Update(const sf::Vector2i & mousePosWindow)
{
	this->buttonState = BTN_IDLE;

	if (
		this->shape.getPosition().x < static_cast<sf::Vector2f>(mousePosWindow).x &&
		this->shape.getPosition().x + this->shape.getGlobalBounds().width > static_cast<sf::Vector2f>(mousePosWindow).x &&
		this->shape.getPosition().y < static_cast<sf::Vector2f>(mousePosWindow).y &&
		this->shape.getPosition().y + this->shape.getGlobalBounds().height > static_cast<sf::Vector2f>(mousePosWindow).y)
	{
		this->buttonState = BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Green);
		break;
	}
}

/**
 *	Draw Button
 *	@params target -> Pointer to window that could draw this Button
 *
 *	Drawing button shape and content of this
 */
void Button::Render(sf::RenderTarget & target)
{
	target.draw(this->shape);
	target.draw(this->text);
}
