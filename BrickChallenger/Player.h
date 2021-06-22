#include "Bullet.h"
#include <vector>

class Player
{
private:
	sf::CircleShape* shape;
	sf::Vector2f* pos;
	float direction;
	sf::Vertex* directionLine;

	std::vector<Bullet*> bullets;
	std::vector<Block*>* blocks;

	int bulletsCount;
	int shooted;

	sf::Clock deltaClock;
	sf::Time dt;

	float Timer;
	float ShootTimer;
	bool isShooting;
	bool blockedMoving;

public:
	Player(std::vector<Block*> * _blocks);
	void Move(float x);
	void Rotate(float angle);
	void IncreaseBullets();

	const sf::CircleShape& GetShape() const;
	const sf::Vertex* getLine() const;
	std::vector<Bullet*> GetBullets() const;
	const bool& GetShooting() const;
	const float& GetShootTimer() const;

	void Shoot();
	void Update();
	void UpdateTime();
};

