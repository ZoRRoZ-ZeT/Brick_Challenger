#include "Player.h"


/**
 *	Constructor
 *	@params:
 *		_blocks -> pointer to a blocks, for passing it into Update for bullets
 */
Player::Player(std::vector<Block*> * _blocks)
{
	this->shape = new sf::CircleShape(15.f);
	this->pos = new sf::Vector2f(300.f, 715.f);
	this->shape->setPosition(*this->pos);
	this->directionLine = new sf::Vertex[2];
	this->directionLine[0] = sf::Vertex(sf::Vector2f(this->pos->x + 15.f, this->pos->y + 15.f));
	this->direction = -30.f;
	this->bulletsCount = 10;
	this->shooted = 0;
	this->isShooting = false;
	this->blockedMoving = false;
	this->ShootTimer = 0.f;
	this->blocks = _blocks;
}

/**
 *	Moving player
 *	@params:
 *		x -> Value to move
 *
 *	Also check for Sides of screen
 */
void Player::Move(float x)
{
	this->pos->x += x;

	if (this->pos->x > 570.f)
		this->pos->x = 570.f;

	if (this->pos->x < 0)
		this->pos->x = 0;
}

/**
 *	Changing shoot direction
 *	@params:
 *		angle -> Direction for shoot
 *
 *	Also checking for max direction to block "endless" shooting
 */
void Player::Rotate(float angle)
{
	this->direction += angle;
	if (this->direction < -170.f)
		direction = -170.f;
	else if (this->direction > -10.f)
		direction = -10.f;
}

/**
 *	Increasing amount of bullets
 *	Used, when level is increase
 */
void Player::IncreaseBullets()
{
	this->bulletsCount += 2;
}

/**
 *	Getter for Player Shape
 */
const sf::CircleShape& Player::GetShape() const
{
	return *this->shape;
}

/**
 *	Getter for Player Direction
 */
const sf::Vertex * Player::getLine() const
{
	return this->directionLine;
}

/**
 *	Getter for Player Bullets
 */
std::vector<Bullet*> Player::GetBullets() const
{
	return this->bullets;
}

/**
 *	Testing current status of player
 */
const bool& Player::GetShooting() const
{
	return this->isShooting || this->blockedMoving;
}

/**
 *	Getter for Time,to allow user do another shot
 */
const float& Player::GetShootTimer() const
{
	return this->ShootTimer;
}

/**
 *	Move player status to Shooting.
 */
void Player::Shoot()
{
	isShooting = true;
	blockedMoving = true;
	dt = deltaClock.restart();
	this->ShootTimer = 0.f;
}

/**
 *	Updating current player;
 *	Also updating current bullets position with passing a pointer to blocks
 */
void Player::Update()
{
	UpdateTime();
	this->shape->setPosition(*this->pos);
	float angle = this->direction * 2 * asin(1) / 180;
	this->directionLine[0] = sf::Vertex(sf::Vector2f(this->pos->x + 15.f, this->pos->y + 15.f));
	this->directionLine[1] = 
		sf::Vertex(sf::Vector2f(
			cos(angle) * 1000 + this->pos->x + 15.f,
			sin(angle) * 1000 + this->pos->y + 15.f)
		);

	if (isShooting && Timer > 0.1f && shooted < bulletsCount)
	{
		bullets.push_back(new Bullet(
			sf::Vector2f(this->pos->x + 10.f, this->pos->y + 10.f),
			5, 10.f, this->direction)
		);

		this->shooted++;
		Timer = 0.f;

		if (shooted == bulletsCount)
			isShooting = false;
	}

	for (auto i : bullets)
	{
		i->Update(*this->blocks);
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->NeedToDelete())
		{
			bullets.erase(bullets.begin() + i);
			if (bullets.size() == 0)
			{
				blockedMoving = false;
				shooted = 0;
			}
		}

	}
}

/**
 *	Updating timer, that will allow user to do another shot
 */
void Player::UpdateTime()
{
	this->dt = deltaClock.restart();
	if (isShooting)
	{
		this->Timer += dt.asSeconds();
	}
	if (GetShooting())
	{
		this->ShootTimer += dt.asSeconds();
	}
}
