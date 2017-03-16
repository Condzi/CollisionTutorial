#include "CollisionSolver.hpp"

void CollisionSolver::ColliderCollider( std::weak_ptr<Collider> colliderA, std::weak_ptr<Collider> colliderB, collisionSide_t colliderAcollisionSide )
{
	if ( colliderAcollisionSide == None )
		return;

	auto& rectA = colliderA.lock()->rectangle;
	auto& rectB = colliderB.lock()->rectangle;

	if ( colliderAcollisionSide == Left )
	{
		rectA.left = rectB.left - rectA.width;
		colliderA.lock()->velocity.x = 0;
	} else if ( colliderAcollisionSide == Right )
	{
		rectA.left = rectB.left + rectB.width;
		colliderA.lock()->velocity.x = 0;
	} else if ( colliderAcollisionSide == Down )
	{
		rectA.top = rectB.top - rectA.height;
		colliderA.lock()->velocity.y = 0;
		colliderA.lock()->isGrounded = true;
	} else if ( colliderAcollisionSide == Top )
	{
		rectA.top = rectB.top + rectB.height;
		colliderA.lock()->velocity.y = 0;
	}
}
