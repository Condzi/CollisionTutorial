#include "CollisionChecker.hpp"

bool CollisionChecker::AddCollider( std::shared_ptr<Collider> collider )
{
	if ( !collider )
		return false;

	for ( auto ptr : this->colliders )
		if ( ptr.lock() == collider )
			return false;

	this->colliders.push_back( collider );
}

void CollisionChecker::Update( float dt )
{
	this->removeUnusedColliders();

	for ( size_t i = 0; i < this->colliders.size(); i++ )
		for ( size_t j = 0; j < this->colliders.size(); j++ )
		{
			if ( i == j ||
				this->colliders[j].lock()->parentPtr->GetEntityID() == entityID_t::UNITIALIZED)
				continue;

			sf::FloatRect& collA = this->colliders[j].lock()->rectangle;
			sf::FloatRect& collB = this->colliders[i].lock()->rectangle;
			sf::FloatRect collAupdated = collA;
			collAupdated.left += this->colliders[j].lock()->velocity.x * dt;
			collAupdated.top += this->colliders[j].lock()->velocity.y * dt;

			if ( !collAupdated.intersects( collB ) )
				continue;

			this->resolveCollision( j, i, this->getCollisionSide( collAupdated, collA, collB ) );
		}
}

void CollisionChecker::removeUnusedColliders()
{
	for ( auto it = this->colliders.begin(); it != this->colliders.end();)
	{
		if ( (*it).expired() || ( *it ).lock()->parentPtr->DoesWishDelete() )
			it = this->colliders.erase( it );
		else
			it++;
	}
}

bool CollisionChecker::collidedLeft( const sf::FloatRect& collAupdated, const sf::FloatRect& collAold, const sf::FloatRect& collB )
{
	return collAold.left + collAold.width <= collB.left &&
		collAupdated.left + collAupdated.width >= collB.left;
}

bool CollisionChecker::collidedRight( const sf::FloatRect& collAupdated, const sf::FloatRect& collAold, const sf::FloatRect& collB )
{
	return collAold.left >= collB.left + collB.width &&
		collAupdated.left <= collAupdated.left + collAupdated.width;
}

bool CollisionChecker::collidedDown( const sf::FloatRect& collAupdated, /* const sf::FloatRect& collAold ,*/ const sf::FloatRect& collB )
{
	// commented for continous checking 
	return //collAold.top + collAold.height <= collB.top &&
		collAupdated.top + collAupdated.height >= collB.top;
}

bool CollisionChecker::collidedTop( const sf::FloatRect& collAupdated, const sf::FloatRect& collAold, const sf::FloatRect& collB )
{
	return collAold.top >= collB.top + collB.height &&
		collAupdated.top <= collAupdated.top + collAupdated.height;
}

collisionSide_t CollisionChecker::getCollisionSide( const sf::FloatRect& collAupdated, const sf::FloatRect& collAold, const sf::FloatRect& collB )
{
	collisionSide_t collAside = None;

	if ( collidedLeft( collAupdated, collAold, collB ) )
		collAside = Left;
	else if ( collidedRight( collAupdated, collAold, collB ) )
		collAside = Right;
	else if ( collidedTop( collAupdated, collAold, collB ) )
		collAside = Top;
	else if ( collidedDown( collAupdated,/* collAold,*/ collB ) )
		collAside = Down;

	return collAside;
}

void CollisionChecker::resolveCollision( size_t collAid, size_t collBid, collisionSide_t collAside )
{
	entityID_t typeA = this->colliders[collAid].lock()->parentPtr->GetEntityID();
	entityID_t typeB = this->colliders[collBid].lock()->parentPtr->GetEntityID();

	if ( typeA == entityID_t::COLLIDER )
		if ( typeB == entityID_t::COLLIDER )
			CollisionSolver::ColliderCollider( this->colliders[collAid], this->colliders[collBid], collAside );
}
