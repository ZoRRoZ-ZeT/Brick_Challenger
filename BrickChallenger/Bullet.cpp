#include "Bullet.h"

Bullet::Bullet(sf::Vector2f startPos, int _size, float _speed, float _dir)
{
	this->size = _size;
	this->shape = new sf::CircleShape(this->size);
	this->shape->setFillColor(sf::Color::Red);
	this->speed = _speed;
	this->X_dir = cos(_dir * 2 * asin(1) / 180);
	this->Y_dir = sin(_dir * 2 * asin(1) / 180);
	this->position = new sf::Vector2f(startPos.x, startPos.y);
}

const sf::CircleShape& Bullet::GetShape() const
{
	return *this->shape;
}

void Bullet::HorizontalSwap()
{
	if (this->position->x + this->size + X_dir >= 600 || this->position->x + X_dir <= 0)
		X_dir *= -1.f;
}

void Bullet::VerticalSwap()
{
	if (this->position->y + Y_dir <= 41)
		Y_dir *= -1.f;
}

bool Bullet::NeedToDelete()
{
	return this->position->y + this->size >= 800;
}


void Bullet::CheckIntersect(std::vector<Block*> blocks)
{
	sf::Vector2f next_move(this->position->x + X_dir * this->speed, this->position->y + Y_dir * this->speed);
	for (auto i : blocks)
	{

		if (next_move.x > i->GetShape().getPosition().x &&
			next_move.x < i->GetShape().getPosition().x + i->GetShape().getGlobalBounds().width &&
			this->position->y > i->GetShape().getPosition().y &&
			this->position->y < i->GetShape().getPosition().y + i->GetShape().getGlobalBounds().height)
		{
			X_dir *= -1.f;
			i->Hit();
		}
		
		if (next_move.y > i->GetShape().getPosition().y &&
			next_move.y < i->GetShape().getPosition().y + i->GetShape().getGlobalBounds().height &&
			this->position->x > i->GetShape().getPosition().x &&
			this->position->x < i->GetShape().getPosition().x + i->GetShape().getGlobalBounds().width)
		{
			Y_dir *= -1.f;
			i->Hit();
		}
	}
}

void Bullet::SetSpeed(float _speed)
{
	this->speed = _speed;
}

void Bullet::Move()
{
	HorizontalSwap();
	VerticalSwap();
	
	this->position->x += X_dir * this->speed;
	this->position->y += Y_dir * this->speed;
}

void Bullet::Update(std::vector<Block*> blocks)
{
	this->CheckIntersect(blocks);
	this->Move();
	this->CheckIntersect(blocks);
	this->shape->setPosition(*this->position);
}
