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
	static std::shared_ptr<Entity> GetScale();
	static bool GetGroundsCollisionPlayer();
	static bool GetGroundCollisionFootPlayer();
	static bool GetScalesCollisionPlayer(std::string direction);
};

