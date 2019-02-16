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

bool EntityManager::GetGroundCollisionFootPlayer() {
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
			if (entity->m_sprite.getGlobalBounds().intersects(rectangle.getGlobalBounds())) {
				cout << "a";
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

		if (entity->m_type == EntityType::scale) {
			if (entity->m_sprite.getGlobalBounds().intersects(GetPlayer()->m_sprite.getGlobalBounds())) {
				cout << "y";
				double XPositionScale = entity->m_sprite.getPosition().x;
				double YPositionScale = entity->m_sprite.getPosition().y;

				double XPositionplayer = GetPlayer()->m_sprite.getPosition().x;
				double YPositionPlayer = GetPlayer()->m_sprite.getPosition().y;

				double YPositionPlayerTop = YPositionPlayer + GetPlayer()->m_sprite.getGlobalBounds().height;
				double YPositionPlayerBottom = YPositionPlayer - GetPlayer()->m_sprite.getGlobalBounds().height;

				sf::RectangleShape rectangleScale;
				rectangleScale.setSize(sf::Vector2f(entity->m_size.x / 10, entity->m_size.y));
				rectangleScale.setPosition(entity->m_sprite.getPosition().x + entity->m_size.x / 2, entity->m_sprite.getPosition().y);

				sf::RectangleShape rectanglePlayer;
				rectanglePlayer.setSize(sf::Vector2f(GetPlayer()->m_size.x / 10, GetPlayer()->m_size.y));
				rectanglePlayer.setPosition(GetPlayer()->m_sprite.getPosition().x + GetPlayer()->m_size.x / 2, GetPlayer()->m_sprite.getPosition().y);

				if (rectangleScale.getGlobalBounds().intersects(rectanglePlayer.getGlobalBounds()))
					return true;

				/*bool collisionTop = XPositionScale - 10 <= XPositionplayer && XPositionScale >= XPositionplayer;

				bool collisionBottom = (YPositionScale >= YPositionPlayerBottom + 10) && (XPositionScale - 10 <= XPositionplayer && XPositionScale >= XPositionplayer);
				
				bool collisionLeftAndRight = (YPositionScale >= YPositionPlayerBottom + 20 && YPositionScale <= YPositionPlayerTop - 5);

				if (direction == "top")
					if (collisionTop)
						return true;

				if (direction == "bottom")
					if (collisionBottom)
						return true;

				if (direction == "left" || direction == "right")
					if (collisionLeftAndRight)
						return true;
				*/
			}
		}


		/*if (entity->m_type == EntityType::scale) {
			if (entity->m_sprite.getGlobalBounds().intersects(GetPlayer()->m_sprite.getGlobalBounds())) {
				double XPositionScale = entity->m_sprite.getPosition().x;
				double YPositionScale = entity->m_sprite.getPosition().y;

				double XPositionplayer = GetPlayer()->m_sprite.getPosition().x;
				double YPositionPlayer = GetPlayer()->m_sprite.getPosition().y - GetPlayer()->m_sprite.getGlobalBounds().height;

				double YPositionPlayerBottom = GetPlayer()->m_sprite.getPosition().y - GetPlayer()->m_sprite.getGlobalBounds().height;
				double YPositionPlayerTop = GetPlayer()->m_sprite.getPosition().y + GetPlayer()->m_sprite.getGlobalBounds().height;

				bool collisionTop = XPositionScale - 10 <= XPositionplayer && XPositionScale >= XPositionplayer;
				bool collisionBottom = (YPositionScale >= YPositionPlayer + 10) && (XPositionScale - 10 <= XPositionplayer && XPositionScale >= XPositionplayer);
				bool collisionLeftAndRight = (YPositionScale >= YPositionPlayerBottom + 20 && YPositionScale <= YPositionPlayerTop - 5);

				if (direction == "top")
					if (collisionTop)
						return true;

				if (direction == "bottom")
					if (collisionBottom)
						return true;

				if (direction == "left" || direction == "right")
					if (collisionLeftAndRight)
						return true;
			}
		}*/

	}

	return false;
}