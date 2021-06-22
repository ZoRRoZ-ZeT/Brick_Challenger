#ifndef BUTTON_H
#define BUTTON_H
#include "Player.h"



class Button
{
private:
	enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };
	short unsigned buttonState;
	short unsigned id;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	sf::Color outlineIdleColor;
	sf::Color outlineHoverColor;
	sf::Color outlineActiveColor;

public:
	Button(float x, float y, float width, float height, sf::Font * font, std::string text, unsigned character_size);

	const bool& isPressed() const;
	const std::string& getText() const;

	void Update(const sf::Vector2i& mousePosWindow);
	void Render(sf::RenderTarget& target);
};

#endif BUTTON_H