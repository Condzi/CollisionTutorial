#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "Entity.hpp"
#include "Collider.hpp"

class SimpleEntity final :
	public Collider,
	public Entity
{
public:
	SimpleEntity() :
		Collider( this )
	{}

	entityID_t GetEntityID() override { return entityID_t::COLLIDER; }

	void Update( float dt );
	void Draw( sf::RenderTarget& target );

private:
	sf::RectangleShape shape;
};