#pragma once

enum EntityType
{
	player,
	ground,
	scale,
	gun,
	ammuntion
};

class Entity
{
public:
	Entity() { };
	~Entity() { };

public:
	sf::Sprite m_sprite;
	sf::Vector2u m_size;
	sf::Vector2f m_position;
	EntityType m_type;
	bool m_enabled = true;

	// Ammuntion only
	bool shutRight = false;
	bool shutLeft = false;
};

