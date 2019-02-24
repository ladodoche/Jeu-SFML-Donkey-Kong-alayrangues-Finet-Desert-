#pragma once

enum EntityType
{
	player,
	ground,
	scale,
	gun,
	ammuntion,
	enemy,
	hammer,
	pipeStart,
	pipeEnd
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
	bool touch = false;
	int touchedEnemyDecontees = 0;

	// Enemy only
	bool moveRight = false;
	bool moveLeft = false;
	int XMax;
	int XMin;
	int touchedPlayerDecontees = 0;
	int live = 3;
};

