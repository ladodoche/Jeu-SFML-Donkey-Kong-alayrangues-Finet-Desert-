#pragma once
#include "Entity.h"

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

public:
	static std::vector<std::shared_ptr<Entity>> m_Entities;
	static std::shared_ptr<Entity> GetPlayer();
	static std::shared_ptr<Entity> GetGun();
	static bool GetGroundsCollisionPlayer();
	static bool GetGroundCollisionFootPlayer();
	static bool OnScaleGetGroundCollisionFootPlayer();
	static bool GetTopScalesCollisionPlayer();
	static bool GetBottomScalesCollisionPlayer();
	static bool GetScalesCollisionPlayerToGoDown();
	static bool GetScalesCollisionPlayer();
	static void AmmunitionTouchedEnemy(std::shared_ptr<Entity> entityEnemy);
};

