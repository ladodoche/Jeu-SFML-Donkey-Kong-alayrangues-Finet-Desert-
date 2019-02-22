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

std::shared_ptr<Entity> EntityManager::GetGun()
{
	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}

		if (entity->m_type == EntityType::gun)
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


bool EntityManager::GetGroundCollisionFootPlayer() {
	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}

		if (entity->m_type == EntityType::ground) {
			sf::RectangleShape rectangle;
			rectangle.setSize(sf::Vector2f(GetPlayer()->m_size.x, GetPlayer()->m_size.y / 10));
			rectangle.setPosition(GetPlayer()->m_sprite.getPosition().x, GetPlayer()->m_sprite.getPosition().y + GetPlayer()->m_size.y - GetPlayer()->m_size.y / 10);
			if (entity->m_sprite.getGlobalBounds().intersects(rectangle.getGlobalBounds()))
				return true;
		}
	}
	return false;
}

bool EntityManager::OnScaleGetGroundCollisionFootPlayer() {
	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}

		if (entity->m_type == EntityType::ground) {
			sf::RectangleShape rectangle;
			rectangle.setSize(sf::Vector2f(GetPlayer()->m_size.x / 10, GetPlayer()->m_size.y / 10));
			rectangle.setPosition(GetPlayer()->m_sprite.getPosition().x + GetPlayer()->m_size.x / 10, GetPlayer()->m_sprite.getPosition().y + GetPlayer()->m_size.y - GetPlayer()->m_size.y / 10);
			if (entity->m_sprite.getGlobalBounds().intersects(rectangle.getGlobalBounds()))
				return true;
		}
	}
	return false;
}

bool EntityManager::GetTopScalesCollisionPlayer()
{
	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}

		if (entity->m_type == EntityType::scale) {

			sf::RectangleShape rectangleScale;
			rectangleScale.setSize(sf::Vector2f(entity->m_size.x / 10, entity->m_size.y / 10));
			rectangleScale.setPosition(entity->m_sprite.getPosition().x + entity->m_size.x / 2, entity->m_sprite.getPosition().y - entity->m_size.y / 10 + 5);

			sf::RectangleShape rectanglePlayer;
			rectanglePlayer.setSize(sf::Vector2f(GetPlayer()->m_size.x, entity->m_size.y / 10));
			rectanglePlayer.setPosition(GetPlayer()->m_sprite.getPosition().x, GetPlayer()->m_sprite.getPosition().y + GetPlayer()->m_size.y);

			if (rectangleScale.getGlobalBounds().intersects(rectanglePlayer.getGlobalBounds()))
				return true;
		}
	}

	return false;
}

bool EntityManager::GetBottomScalesCollisionPlayer()
{
	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}

		if (entity->m_type == EntityType::scale) {

			sf::RectangleShape rectangleScale;
			rectangleScale.setSize(sf::Vector2f(entity->m_size.x, entity->m_size.y / 10));
			rectangleScale.setPosition(entity->m_sprite.getPosition().x, entity->m_sprite.getPosition().y);

			sf::RectangleShape rectanglePlayer;
			rectanglePlayer.setSize(sf::Vector2f(GetPlayer()->m_size.x, entity->m_size.y / 10));
			rectanglePlayer.setPosition(GetPlayer()->m_sprite.getPosition().x, GetPlayer()->m_sprite.getPosition().y - GetPlayer()->m_size.y+5);

			if (rectangleScale.getGlobalBounds().intersects(rectanglePlayer.getGlobalBounds()))
				return true;
		}
	}

	return false;
}

bool EntityManager::GetScalesCollisionPlayerToGoDown()
{
	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}

		if (entity->m_type == EntityType::scale) {

			sf::RectangleShape rectangleScale;
			rectangleScale.setSize(sf::Vector2f(entity->m_size.x / 10, entity->m_size.y));
			rectangleScale.setPosition(entity->m_sprite.getPosition().x + entity->m_size.x / 2, entity->m_sprite.getPosition().y);

			sf::RectangleShape rectanglePlayer;
			rectanglePlayer.setSize(sf::Vector2f(GetPlayer()->m_size.x / 10, entity->m_size.y / 10));
			rectanglePlayer.setPosition(GetPlayer()->m_sprite.getPosition().x + GetPlayer()->m_size.x / 2, GetPlayer()->m_sprite.getPosition().y + GetPlayer()->m_size.y);

			if (rectangleScale.getGlobalBounds().intersects(rectanglePlayer.getGlobalBounds()))
				return true;
		}
	}

	return false;
}

bool EntityManager::GetScalesCollisionPlayer()
{
	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}

		if (entity->m_type == EntityType::scale) {
			if (entity->m_sprite.getGlobalBounds().intersects(GetPlayer()->m_sprite.getGlobalBounds())) {
				sf::RectangleShape rectangleScale;
				rectangleScale.setSize(sf::Vector2f(entity->m_size.x / 10, entity->m_size.y));
				rectangleScale.setPosition(entity->m_sprite.getPosition().x + entity->m_size.x / 2, entity->m_sprite.getPosition().y);

				sf::RectangleShape rectanglePlayer;
				rectanglePlayer.setSize(sf::Vector2f(GetPlayer()->m_size.x / 10, GetPlayer()->m_size.y));
				rectanglePlayer.setPosition(GetPlayer()->m_sprite.getPosition().x + GetPlayer()->m_size.x / 2, GetPlayer()->m_sprite.getPosition().y);

				if (rectangleScale.getGlobalBounds().intersects(rectanglePlayer.getGlobalBounds()))
					return true;
			}
		}
	}

	return false;
}