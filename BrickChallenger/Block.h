#include <SFML/Graphics.hpp>
#include <math.h>
#include <stack>
class Block
{
private:
	sf::RectangleShape* shape;
	int health;
	sf::Color blockColor;
	sf::Vector2f* position;
	sf::Text blockHP;

	bool IsDestroyed;
	float previousY;
	float isMoving;

	int& score;

	sf::Font font;
public:
	Block(sf::Vector2f startPos, int _health, int& refToScore);

	void Hit();

	const sf::RectangleShape& GetShape() const;
	const int& GetHealth() const;
	const sf::Color& GetColor() const;
	const bool& GetStatus() const;
	const bool& GetMoving() const;
	const sf::Text& GetText() const;

	void MoveNext();
	void StartMoving();

	void Update();
	void UpdateText();
};

