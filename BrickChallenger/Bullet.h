#include "Block.h"

class Bullet
{
private:
	sf::CircleShape* shape;
	sf::Vector2f* position;
	int size;

	float speed;
	float X_dir;
	float Y_dir;
public:
	Bullet(sf::Vector2f startPos, int _size, float _speed, float _dir);


	void HorizontalSwap();
	void VerticalSwap();
	bool NeedToDelete();

	const sf::CircleShape& GetShape() const;

	void CheckIntersect(std::vector<Block*> blocks);
	void SetSpeed(float _speed);

	void Move();
	void Update(std::vector<Block*> blocks);
};

