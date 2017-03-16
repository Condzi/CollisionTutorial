#pragma once

#include <memory>
#include <vector>

#include "CollisionSolver.hpp"
#include "Collider.hpp"
#include "Entity.hpp"

class CollisionChecker final
{
public:
	CollisionChecker()
	{}

	bool AddCollider( std::shared_ptr<Collider> collider );

	void Update( float dt );

private:
	std::vector<std::weak_ptr<Collider>> colliders;

	void removeUnusedColliders();

	bool collidedLeft( const sf::FloatRect& collAupdated, const sf::FloatRect& collAold, const sf::FloatRect& collB );
	bool collidedRight( const sf::FloatRect& collAupdated, const sf::FloatRect& collAold, const sf::FloatRect& collB );
	bool collidedDown( const sf::FloatRect& collAupdated, /* const sf::FloatRect& collAold ,*/ const sf::FloatRect& collB );
	bool collidedTop( const sf::FloatRect& collAupdated, const sf::FloatRect& collAold, const sf::FloatRect& collB );

	collisionSide_t getCollisionSide( const sf::FloatRect& collAupdated, const sf::FloatRect& collAold, const sf::FloatRect& collB );
	void resolveCollision( size_t collAid, size_t collBid, collisionSide_t collAside );
};