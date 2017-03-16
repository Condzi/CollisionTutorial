#include "SimpleEntity.hpp"

void SimpleEntity::Update( float dt )
{
	this->position += this->velocity * dt;
	this->rectangle.left = this->position.x;
	this->rectangle.top = this->position.y;

	this->shape.setPosition( this->position );
	this->shape.setSize( { this->rectangle.width, this->rectangle.height } );
}

void SimpleEntity::Draw( sf::RenderTarget& target )
{
	target.draw( this->shape );
}
