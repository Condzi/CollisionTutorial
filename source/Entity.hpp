#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

enum entityID_t
{
	UNITIALIZED = 0,

	COLLIDER
};

class Entity
{
public:
	Entity() :
		position( 0.0f, 0.0f ),
		wishDelete( false )
	{}

	virtual ~Entity() = default;

	virtual entityID_t GetEntityID() { return entityID_t::UNITIALIZED; }
	virtual sf::Vector2f GetPosition() { return this->position; }
	virtual bool DoesWishDelete() { return this->wishDelete; }

	virtual void SetPosition( const sf::Vector2f& pos ) { this->position = pos; }
	virtual void SetWishDelete( bool val ) { this->wishDelete = val; }

	virtual void Update( float dt ) {}
	virtual void Draw( sf::RenderTarget& window ) {}

protected:
	sf::Vector2f position; // float x,y
	bool wishDelete;

};