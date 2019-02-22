#include "pch.h"
#include "StringHelpers.h"
#include "Game.h"
#include "EntityManager.h"

const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: mWindow(sf::VideoMode(840, 600), "Space Invaders 1978", sf::Style::Close)
	, mTexture()
	, mPlayer()
	, mFont()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
	, _Ground()
	, _Scale()
	, mIsMovingRight(false)
	, mIsMovingLeft(false)
{
	mWindow.setFramerateLimit(160);

	mTexture.loadFromFile("Media/Textures/Mario1.png");
	_TextureGround.loadFromFile("Media/Textures/Block.png");
	_TextureScale.loadFromFile("Media/Textures/Echelle.png");
	_TextureGun.loadFromFile("Media/Textures/gun.png");
	_TextureAmmunition.loadFromFile("Media/Textures/SI_Weapon.png");
	mFont.loadFromFile("Media/Sansation.ttf");

	InitSprites();
}

void Game::ResetSprites()
{

	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		entity->m_enabled = true;
	}
}

void Game::InitSprites()
{
	_lives = 0;
	_score = 0;

	//
	// Entites
	//
	InitEntites();

	//
	// Lives
	//

	_LivesText.setFillColor(sf::Color::Green);
	_LivesText.setFont(mFont);
	_LivesText.setPosition(10.f, 50.f);
	_LivesText.setCharacterSize(20);
	_LivesText.setString(std::to_string(_lives));

	//
	// Text
	//

	_ScoreText.setFillColor(sf::Color::Green);
	_ScoreText.setFont(mFont);
	_ScoreText.setPosition(10.f, 100.f);
	_ScoreText.setCharacterSize(20);
	_ScoreText.setString(std::to_string(_score));
}

void Game::InitEntites() {

	//
	// Player
	//

	mPlayer.setTexture(mTexture);
	mPlayer.setPosition(400.f, 240.f);
	std::shared_ptr<Entity> player = std::make_shared<Entity>();
	player->m_sprite = mPlayer;
	player->m_type = EntityType::player;
	player->m_size = mTexture.getSize();
	player->m_position = mPlayer.getPosition();
	EntityManager::m_Entities.push_back(player);


	//
	// Ground
	//
	for (int i = 0; i < 9; i++) {
		_Ground[i].setTexture(_TextureGround);
		_Ground[i].setPosition(100.f + 68.f * i, 300.f);
		std::shared_ptr<Entity> ground = std::make_shared<Entity>();
		ground->m_sprite = _Ground[i];
		ground->m_type = EntityType::ground;
		ground->m_size = _TextureGround.getSize();
		ground->m_position = _Ground[0].getPosition();
		EntityManager::m_Entities.push_back(ground);
	}

	for (int i = 0; i < 3; i++) {
		_Ground[i].setTexture(_TextureGround);
		_Ground[i].setPosition(235.f + 68.f * i, 195.f);
		std::shared_ptr<Entity> ground = std::make_shared<Entity>();
		ground->m_sprite = _Ground[i];
		ground->m_type = EntityType::ground;
		ground->m_size = _TextureGround.getSize();
		ground->m_position = _Ground[0].getPosition();
		EntityManager::m_Entities.push_back(ground);
	}

	for (int i = 0; i < 2; i++) {
		_Ground[i].setTexture(_TextureGround);
		_Ground[i].setPosition(62.f + 68.f * i, 195.f);
		std::shared_ptr<Entity> ground = std::make_shared<Entity>();
		ground->m_sprite = _Ground[i];
		ground->m_type = EntityType::ground;
		ground->m_size = _TextureGround.getSize();
		ground->m_position = _Ground[0].getPosition();
		EntityManager::m_Entities.push_back(ground);
	}

	for (int i = 0; i < 3; i++) {
		_Ground[i].setTexture(_TextureGround);
		_Ground[i].setPosition(400.f + 68.f * i, 90.f);
		std::shared_ptr<Entity> ground = std::make_shared<Entity>();
		ground->m_sprite = _Ground[i];
		ground->m_type = EntityType::ground;
		ground->m_size = _TextureGround.getSize();
		ground->m_position = _Ground[0].getPosition();
		EntityManager::m_Entities.push_back(ground);
	}

	//
	// Scale
	//

	_Scale[0].setTexture(_TextureScale);
	_Scale[0].setPosition(200.f, 195.f);
	std::shared_ptr<Entity> scale = std::make_shared<Entity>();
	scale->m_sprite = _Scale[0];
	scale->m_type = EntityType::scale;
	scale->m_size = _TextureScale.getSize();
	scale->m_position = _Scale[0].getPosition();
	EntityManager::m_Entities.push_back(scale);

	_Scale[1].setTexture(_TextureScale);
	_Scale[1].setPosition(360.f, 90.f);
	scale = std::make_shared<Entity>();
	scale->m_sprite = _Scale[1];
	scale->m_type = EntityType::scale;
	scale->m_size = _TextureScale.getSize();
	scale->m_position = _Scale[1].getPosition();
	EntityManager::m_Entities.push_back(scale);

	_Gun.setTexture(_TextureGun);
	_Gun.setPosition(550.f, 75.f);
	std::shared_ptr<Entity> gun = std::make_shared<Entity>();
	gun->m_sprite = _Gun;
	gun->m_type = EntityType::gun;
	gun->m_size = _TextureGun.getSize();
	gun->m_position = _Gun.getPosition();
	EntityManager::m_Entities.push_back(gun);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}

		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processEvents()
{
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::Left)
				mTexture.loadFromFile("Media/Textures/Mario4.png");
			else if (event.key.code == sf::Keyboard::Right)
				mTexture.loadFromFile("Media/Textures/Mario2.png");
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::update(sf::Time elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingLeft) {
		_ChangeRightImageMario = 0;
		if (_ChangeLeftImageMario <= 10) {
			mTexture.loadFromFile("Media/Textures/Mario4.png");
		}
		else if (_ChangeLeftImageMario <= 20) {
			mTexture.loadFromFile("Media/Textures/Mario3.png");
		}
		else {
			_ChangeLeftImageMario = 0;
		}
		_ChangeLeftImageMario++;

		if (((EntityManager::GetGroundCollisionFootPlayer() && !EntityManager::GetScalesCollisionPlayer()) || Jump != 0 && (!EntityManager::GetScalesCollisionPlayer()) || ((EntityManager::GetTopScalesCollisionPlayer()) || EntityManager::GetBottomScalesCollisionPlayer()))
			|| ((EntityManager::GetScalesCollisionPlayer())
			&& ((EntityManager::GetTopScalesCollisionPlayer()) || EntityManager::GetBottomScalesCollisionPlayer())))
			movement.x -= PlayerSpeed;
	}
	if (mIsMovingRight) {
		_ChangeLeftImageMario = 0;
		if (_ChangeRightImageMario <= 10) {
			mTexture.loadFromFile("Media/Textures/Mario1.png");
		}
		else if (_ChangeRightImageMario <= 20) {
			mTexture.loadFromFile("Media/Textures/Mario2.png");
		}
		else {
			_ChangeRightImageMario = 0;
		}
		_ChangeRightImageMario++;

		if (((EntityManager::GetGroundCollisionFootPlayer() && !EntityManager::GetScalesCollisionPlayer()) || Jump != 0 && (!EntityManager::GetScalesCollisionPlayer()) || ((EntityManager::GetTopScalesCollisionPlayer()) || EntityManager::GetBottomScalesCollisionPlayer()))
			|| ((EntityManager::GetScalesCollisionPlayer())
				&& ((EntityManager::GetTopScalesCollisionPlayer()) || EntityManager::GetBottomScalesCollisionPlayer())))
			movement.x += PlayerSpeed;
	}

	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}

		if (entity->m_type != EntityType::player)
		{
			continue;
		}


		entity->m_sprite.move(movement * elapsedTime.asSeconds());
	}
}


void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Left) {
		mIsMovingLeft = isPressed;
	}
	if (key == sf::Keyboard::Right) {
		mIsMovingRight = isPressed;
	}

	if (key == sf::Keyboard::Up)
		if (EntityManager::GetScalesCollisionPlayer())
			EntityManager::GetPlayer()->m_sprite.move(sf::Vector2f(0, -2));
	if (key == sf::Keyboard::Down)
		if ((!EntityManager::GetGroundCollisionFootPlayer() && EntityManager::GetScalesCollisionPlayer()) || EntityManager::GetScalesCollisionPlayerToGoDown())
			EntityManager::GetPlayer()->m_sprite.move(sf::Vector2f(0, +2));
	if (key == sf::Keyboard::Space && Jump == 0 && TouchGround == true)
		Jump = 45;
	if (key == sf::Keyboard::Enter && _IsGameOver == true) {
		mWindow.close();
		mWindow.create(sf::VideoMode(840, 600), "Space Invaders 1978", sf::Style::Close);
		mWindow.setFramerateLimit(160);
		_lives = 4;
		_IsGameOver = false;
		mText.setString("");
	}
	if (key == sf::Keyboard::Enter && _IsGameOver == false && PlayerWithAWeapon == true && RateOfFire == 0) {
		sf::Sprite ammuntion;
		ammuntion.setTexture(_TextureAmmunition);
		if (_ChangeRightImageMario > 0)
			ammuntion.setPosition(EntityManager::GetPlayer()->m_sprite.getPosition().x + EntityManager::GetPlayer()->m_size.x, EntityManager::GetPlayer()->m_sprite.getPosition().y + EntityManager::GetPlayer()->m_size.y / 2);
		if (_ChangeLeftImageMario > 0)
			ammuntion.setPosition(EntityManager::GetPlayer()->m_sprite.getPosition().x, EntityManager::GetPlayer()->m_sprite.getPosition().y + EntityManager::GetPlayer()->m_size.y / 2);
		std::shared_ptr<Entity> ammuntionEntity = std::make_shared<Entity>();
		ammuntionEntity->m_sprite = ammuntion;
		ammuntionEntity->m_type = EntityType::ammuntion;
		ammuntionEntity->m_size = _TextureAmmunition.getSize();
		ammuntionEntity->m_position = ammuntion.getPosition();
		if (_ChangeLeftImageMario > 0)
			ammuntionEntity->shutLeft = true;
		if (_ChangeRightImageMario > 0)
			ammuntionEntity->shutRight = true;
		EntityManager::m_Entities.push_back(ammuntionEntity);
		RateOfFire = 20;
	}
}

void Game::render()
{
	mWindow.clear();

	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}

		if (entity->m_type == EntityType::player)
			if (CheckPlayerOutWindow(EntityManager::GetPlayer()->m_sprite.getPosition().x, EntityManager::GetPlayer()->m_sprite.getPosition().y))
				DisplayGameOver();

		if (entity->m_type == EntityType::gun) {
			if (entity->m_sprite.getGlobalBounds().intersects(EntityManager::GetPlayer()->m_sprite.getGlobalBounds()) || PlayerWithAWeapon) {
				PlayerWithAWeapon = true;
				continue;
			}
		}

		if (entity->m_type == EntityType::ammuntion) {
			if (entity->shutLeft)
				entity->m_sprite.move(sf::Vector2f(-2, 0));
			if (entity->shutRight)
				entity->m_sprite.move(sf::Vector2f(2, 0));
		}

		mWindow.draw(entity->m_sprite);
	}

	//-- Gravity --//
	if (EntityManager::GetGroundsCollisionPlayer() && Jump > 0 && Jump < 44) {
		EntityManager::GetPlayer()->m_sprite.move(sf::Vector2f(0, 2));
		Jump = 0;
	}
	else if (Jump > 0) {
		Jump--;
		EntityManager::GetPlayer()->m_sprite.move(sf::Vector2f(0, -1));
	}
	else if (!EntityManager::GetScalesCollisionPlayer() && !EntityManager::GetGroundsCollisionPlayer()) {
		Jump = 0;
		TouchGround = false;
		EntityManager::GetPlayer()->m_sprite.move(sf::Vector2f(0, 2));
	}
	else {
		TouchGround = true;
	}

	//-- Ammunition --//
	//if(_ChangeLeftImageMario > 0 && 

	mWindow.draw(mStatisticsText);
	mWindow.draw(mText);
	mWindow.draw(_LivesText);
	mWindow.draw(_ScoreText);
	mWindow.display();

	if(RateOfFire > 0)
		RateOfFire--;
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}

	//
	// Handle collisions
	//

	if (mStatisticsUpdateTime >= sf::seconds(0.050f))
	{
		if (_IsGameOver == true)
			return;

		HandleTexts();
		HandleGameOver();
		/*HandleCollisionWeaponEnemy();
		HandleCollisionWeaponPlayer();
		HandleCollisionWeaponBlock();
		HandleCollisionEnemyWeaponBlock();
		HandleCollisionEnemyMasterWeaponBlock();
		HandleCollisionEnemyMasterWeaponPlayer();
		HandleCollisionBlockEnemy();
		HandleCollisionWeaponEnemyMaster();
		HanldeWeaponMoves();
		HanldeEnemyWeaponMoves();
		HanldeEnemyMasterWeaponMoves();
		HandleEnemyMoves();
		HandleEnemyMasterMove();
		HandleEnemyWeaponFiring();
		HandleEnemyMasterWeaponFiring();*/
	}
}

void Game::HandleTexts()
{
	std::string lives = "Lives: " + std::to_string(_lives);
	_LivesText.setString(lives);
	std::string score = "Score: " + std::to_string(_score);
	_ScoreText.setString(score);
	return;
}


void Game::HandleGameOver()
{

}

void Game::DisplayGameOver()
{
	if (_lives == 0)
	{
		mText.setFillColor(sf::Color::Green);
		mText.setFont(mFont);
		mText.setPosition(200.f, 200.f);
		mText.setCharacterSize(80);

		mText.setString("GAME OVER");

		_IsGameOver = true;
	}
	else if (_lives > 0) {
		_lives--;
		EntityManager::GetPlayer()->m_sprite.setPosition(sf::Vector2f(400.f, 240.f));
	}
	else
	{
		ResetSprites();
	}
}

bool Game::CheckPlayerOutWindow(int x, int y) {
	if (x < -40 || x > 880 || y < -40 || y > 640)
		return true;
	return false;
}