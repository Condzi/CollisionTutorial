#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

enum collisionSide_t
{
	None = -1,
	Left = 0,
	Right,
	Down,
	Top
};

class Entity;

class Collider
{
	friend class CollisionChecker;
	friend class CollisionSolver;

public:
	sf::Vector2f velocity;
	sf::FloatRect rectangle;

	Collider(Entity* prntPtr) :
		velocity(0.0f,0.0f),
		rectangle(0.0f,0.0f,0.0f,0.0f),
		isGrounded(false),
		parentPtr(prntPtr)
	{}

	virtual ~Collider() = default;

protected:
	bool isGrounded;

private:
	Entity* parentPtr;
};
