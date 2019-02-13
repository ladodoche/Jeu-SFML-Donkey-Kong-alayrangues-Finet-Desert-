#include "pch.h"
#include "EntityManager.h"

std::vector<std::shared_ptr<Entity>> EntityManager::m_Entities;

EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}

std::shared_ptr<Entity> EntityManager::GetPlayer()
{
	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}

		if (entity->m_type == EntityType::player)
		{
			return entity;
		}
	}

	return nullptr;
}

std::shared_ptr<Entity> EntityManager::GetScale()
{
	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}

		if (entity->m_type == EntityType::scale)
		{
			return entity;
		}
	}

	return nullptr;
}

bool EntityManager::GetGroundsCollisionPlayer()
{
	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}
			
		if (entity->m_type == EntityType::ground) {
			if (entity->m_sprite.getGlobalBounds().intersects(GetPlayer()->m_sprite.getGlobalBounds())) {
					return true;
			}
		}
	}
	return false;
}

bool EntityManager::GetScalesCollisionPlayer(std::string direction)
{
	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}

		if (direction == "top") {
			if (entity->m_type == EntityType::scale) {
				if (entity->m_sprite.getGlobalBounds().intersects(GetPlayer()->m_sprite.getGlobalBounds())) {
					double XPositionScale = entity->m_sprite.getPosition().x;
					double XPositionplayer = GetPlayer()->m_sprite.getPosition().x;
					if (XPositionScale - 10 <= XPositionplayer && XPositionScale >= XPositionplayer)
						return true;
					else
						cout << "1";
				}
			}
		}

		if (direction == "bottom") {
			if (entity->m_type == EntityType::scale) {
				if (entity->m_sprite.getGlobalBounds().intersects(GetPlayer()->m_sprite.getGlobalBounds())) {
					double YPositionScale = entity->m_sprite.getPosition().y;
					double YPositionPlayer = GetPlayer()->m_sprite.getPosition().y - GetPlayer()->m_sprite.getGlobalBounds().height;
					double XPositionScale = entity->m_sprite.getPosition().x;
					double XPositionplayer = GetPlayer()->m_sprite.getPosition().x;
					if ((YPositionScale >= YPositionPlayer + 10) && (XPositionScale - 10  <= XPositionplayer && XPositionScale >= XPositionplayer))
						return true;
				}
			}
		}

		if (direction == "left" || direction == "right") {
			if (entity->m_type == EntityType::scale) {
				if (entity->m_sprite.getGlobalBounds().intersects(GetPlayer()->m_sprite.getGlobalBounds())) {
					double YPositionScale = entity->m_sprite.getPosition().y;
					double YPositionPlayerBottom = GetPlayer()->m_sprite.getPosition().y - GetPlayer()->m_sprite.getGlobalBounds().height;
					double YPositionPlayerTop = GetPlayer()->m_sprite.getPosition().y + GetPlayer()->m_sprite.getGlobalBounds().height;
					if ((YPositionScale >= YPositionPlayerBottom + 20 && YPositionScale <= YPositionPlayerTop - 5))
						return true;
				}
			}
		}
		cout << "\n";
	}

	return false;
}