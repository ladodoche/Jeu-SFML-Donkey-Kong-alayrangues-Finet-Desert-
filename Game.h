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
	void InitEntites();
	void ResetSprites();

	void updateStatistics(sf::Time elapsedTime);

	void HandleTexts();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	void HandleGameOver();
	void DisplayGameOver();
	bool CheckPlayerOutWindow(int x, int y);

private:
	static const float		PlayerSpeed;
	static const sf::Time	TimePerFrame;

	sf::RenderWindow		mWindow;
	sf::Font	mFont;
	sf::Text	mText;
	sf::Event event;
	sf::Text	_LivesText;
	int _lives = 3;
	sf::Text _ScoreText;
	int _score = 0;
	bool _IsGameOver = false;

	std::size_t	mStatisticsNumFrames;
	sf::Text	mStatisticsText;
	sf::Time	mStatisticsUpdateTime;

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

	//-- Gun --//
	sf::Sprite	_Gun;
	sf::Texture	_TextureGun;
	bool PlayerWithAWeapon = false;

	//-- Ammuntion --//
	std::vector<sf::Sprite>	_Ammunitions;
	sf::Texture	_TextureAmmunition;
	int RateOfFire = 0;

	//-- Jump --//
	int Jump;
};

