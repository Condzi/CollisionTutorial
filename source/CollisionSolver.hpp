#pragma once

#include <memory>

#include "Collider.hpp"
#include "Entity.hpp"

class CollisionSolver final
{
public:
	CollisionSolver() = delete;

	static void ColliderCollider( std::weak_ptr<Collider> colliderA, std::weak_ptr<Collider> colliderB, collisionSide_t colliderAcollisionSide );
};