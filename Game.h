#pragma once
#include "Weapon.h"

#define GROUND_COUNT 17
#define SCALE_COUNT 2

class Game
{
public:
	Game();
	~Game() { };
	void run();

private:
	void processEvents();
	void update(sf::Time elapsedTime);
	void render();

	void InitSprites();
	void ResetSprites();

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
	static const float		PlayerSpeed;
	static const sf::Time	TimePerFrame;

	sf::RenderWindow		mWindow;
	sf::Font	mFont;
	sf::Text	mText;
	sf::Event event;

	std::size_t	mStatisticsNumFrames;

	//-- Player --//
	sf::Sprite	mPlayer;
	sf::Texture	mTexture;
	int _ChangeRightImageMario = 0;
	int _ChangeLeftImageMario = 0;
	bool mIsMovingRight;
	bool mIsMovingLeft;

	//-- Ground --//
	sf::Sprite	_Ground[GROUND_COUNT];
	sf::Texture	_TextureGround;
	bool TouchGround;

	//-- Scale --//
	sf::Sprite	_Scale[SCALE_COUNT];
	sf::Texture	_TextureScale;

	//-- Jump --//
	int Jump;
};

