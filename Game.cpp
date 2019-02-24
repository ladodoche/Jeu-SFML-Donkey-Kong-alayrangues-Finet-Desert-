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

	mTexture.loadFromFile("Media/Textures/Mario2.png");
	_TextureGround.loadFromFile("Media/Textures/Block.png");
	_TextureScale.loadFromFile("Media/Textures/Echelle.png");
	_TextureGun.loadFromFile("Media/Textures/gun.png");
	_TextureAmmunition.loadFromFile("Media/Textures/SI_Weapon.png");
	_TextureEnemy.loadFromFile("Media/Textures/Enemy1.png");
	_TextureHammer.loadFromFile("Media/Textures/Hammer1.png");
	_TexturePipe.loadFromFile("Media/Textures/pipe.png");
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
	cout << game << "\n";
	if (game == 1)
		game1();
	if (game >= 2)
		game2();
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
	if (start <= 0) {
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
}

void Game::update(sf::Time elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingLeft) {
		if (CountHammerMoving > 0 && _ChangeRightImageMario == 1)
			CountHammerMoving = 100;
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

		if (!EntityManager::GetGroundCollisionFootPlayer() && !EntityManager::GetScalesCollisionPlayer() && EntityManager::GetGroundsCollisionPlayer())
			movement.x += PlayerSpeed;

		else if (EntityManager::GetPipeCollisionPlayer() && !EntityManager::GetPipeCollisionFootPlayer()) {
			movement.x += PlayerSpeed;
			movement.x += PlayerSpeed;
			movement.x += PlayerSpeed;
			movement.x += PlayerSpeed;
			movement.x += PlayerSpeed;
		}

		else if (
			(EntityManager::GetGroundCollisionFootPlayer() && !EntityManager::GetScalesCollisionPlayer() && !EntityManager::GetPipeCollisionPlayer())
			|| (!EntityManager::GetGroundCollisionFootPlayer() && EntityManager::GetPipeCollisionFootPlayer())
			|| (EntityManager::GetScalesCollisionPlayer() && (EntityManager::GetBottomScalesCollisionPlayer() || EntityManager::GetTopScalesCollisionPlayer()))
			|| (!EntityManager::GetGroundCollisionFootPlayer() && !EntityManager::GetGroundsCollisionPlayer() && !EntityManager::GetPipeCollisionFootPlayer())
			)
			movement.x -= PlayerSpeed;
	}
	if (mIsMovingRight) {
		if (CountHammerMoving > 0 && _ChangeLeftImageMario == 1)
			CountHammerMoving = 100;
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

		if (!EntityManager::GetGroundCollisionFootPlayer() && !EntityManager::GetScalesCollisionPlayer() && EntityManager::GetGroundsCollisionPlayer())
			movement.x -= PlayerSpeed;
		
		else if (EntityManager::GetPipeCollisionPlayer() && !EntityManager::GetPipeCollisionFootPlayer()) {
			movement.x -= PlayerSpeed;
			movement.x -= PlayerSpeed;
			movement.x -= PlayerSpeed;
			movement.x -= PlayerSpeed;
			movement.x -= PlayerSpeed;
		}

		else if(
			( EntityManager::GetGroundCollisionFootPlayer() && !EntityManager::GetScalesCollisionPlayer() && !EntityManager::GetPipeCollisionPlayer())
			|| (!EntityManager::GetGroundCollisionFootPlayer() && EntityManager::GetPipeCollisionFootPlayer())
			|| ( EntityManager::GetScalesCollisionPlayer() && ( EntityManager::GetBottomScalesCollisionPlayer() || EntityManager::GetTopScalesCollisionPlayer() ) )
			|| ( !EntityManager::GetGroundCollisionFootPlayer() && !EntityManager::GetGroundsCollisionPlayer() && !EntityManager::GetPipeCollisionFootPlayer())
			)
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
	if (key == sf::Keyboard::Left)
		mIsMovingLeft = isPressed;

	if (key == sf::Keyboard::Right)
		mIsMovingRight = isPressed;

	if (key == sf::Keyboard::Up)
		if (EntityManager::GetScalesCollisionPlayer())
			EntityManager::GetPlayer()->m_sprite.move(sf::Vector2f(0, -2));
	
	if (key == sf::Keyboard::Down) {
		if (EntityManager::GetPipeEndCollisionFootPlayer() && game != 2) {
			game++;
			EntityManager::m_Entities.clear();
			InitSprites();
		}
		if (EntityManager::GetPipeEndCollisionFootPlayer() && game >= 2) {
			end = true;
			DisplayGameSuccess();
		}
		if ((!EntityManager::GetGroundCollisionFootPlayer() && EntityManager::GetScalesCollisionPlayer()) || EntityManager::GetScalesCollisionPlayerToGoDown()) {
			EntityManager::GetPlayer()->m_sprite.move(sf::Vector2f(0, +2));
		}
	}
	
	if (key == sf::Keyboard::Space && Jump == 0 && EntityManager::GetGroundCollisionFootPlayer())
		Jump = 60;

	if (key == sf::Keyboard::Enter && (_IsGameOver == true || end == true)) {
		cout << "ok\n";
		mWindow.close();
		mWindow.create(sf::VideoMode(840, 600), "Space Invaders 1978", sf::Style::Close);
		mWindow.setFramerateLimit(160);
		initGame();
		cout << "Game : " << game << "\n";
	}

	if (key == sf::Keyboard::Enter && _IsGameOver == false && PlayerWithAGun == true && RateOfFire == 0) {
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
		RateOfFire = 100;
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

		if (start <= 0) {

			if (entity->m_type == EntityType::player) {
				if (CheckPlayerOutWindow(EntityManager::GetPlayer()->m_sprite.getPosition().x, EntityManager::GetPlayer()->m_sprite.getPosition().y)) {
					DisplayGameOver();
					mPlayer.setPosition(605.f, 260.f);
					if (game == 1)
						EntityManager::GetPlayer()->m_sprite.setPosition(sf::Vector2f(605.f, 200.f));
					if(game >= 2)
						EntityManager::GetPlayer()->m_sprite.setPosition(sf::Vector2f(105.f, 400.f));
				}
			}

			if (entity->m_type == EntityType::gun) {
				if (entity->m_sprite.getGlobalBounds().intersects(EntityManager::GetPlayer()->m_sprite.getGlobalBounds()) || PlayerWithAGun) {
					PlayerWithAGun = true;
					continue;
				}
			}

			if (entity->m_type == EntityType::enemy) {
				//EntityManager::AmmunitionTouchedEnemy(entity);
				EntityManager::HammerTouchedEnemy(entity);

				if (entity->live <= 0)
					continue;

				if (entity->m_sprite.getPosition().x <= entity->XMin) {
					entity->moveRight = true;
					entity->moveLeft = false;
				}
				if (entity->m_sprite.getPosition().x >= entity->XMax) {
					entity->moveRight = false;
					entity->moveLeft = true;
				}
				if (entity->moveRight)
					entity->m_sprite.move(sf::Vector2f(0.5, 0));
				if (entity->moveLeft)
					entity->m_sprite.move(sf::Vector2f(-0.5, 0));

				sf::RectangleShape rectangleEnemy;
				rectangleEnemy.setSize(sf::Vector2f(entity->m_size.x, entity->m_size.y / 10));
				rectangleEnemy.setPosition(entity->m_sprite.getPosition().x, entity->m_sprite.getPosition().y + entity->m_size.y - 5);

				if (rectangleEnemy.getGlobalBounds().intersects(EntityManager::GetPlayer()->m_sprite.getGlobalBounds()) && entity->touchedPlayerDecontees == 0) {
					entity->touchedPlayerDecontees = 100;
					if (entity->moveRight == true) {
						entity->moveRight = false;
						entity->moveLeft = true;
					}
					else if (entity->moveLeft == true) {
						entity->moveRight = true;
						entity->moveLeft = false;
					}
					DisplayGameOver();
				}

				if (entity->touchedEnemyDecontees != 0) {
					_TextureEnemy.loadFromFile("Media/Textures/Enemy2.png");
					entity->m_sprite.setTexture(_TextureEnemy);
				}
				else {
					_TextureEnemy.loadFromFile("Media/Textures/Enemy1.png");
					entity->m_sprite.setTexture(_TextureEnemy);
				}

				if (entity->touchedEnemyDecontees != 0)
					entity->touchedEnemyDecontees--;

				if (entity->touchedPlayerDecontees != 0)
					entity->touchedPlayerDecontees--;
			}

			if (entity->m_type == EntityType::ammuntion) {
				if (entity->touch == true)
					continue;
				if (entity->shutLeft)
					entity->m_sprite.move(sf::Vector2f(-2, 0));
				if (entity->shutRight)
					entity->m_sprite.move(sf::Vector2f(2, 0));
			}

			if (entity->m_type == EntityType::hammer) {

				if (entity->m_sprite.getGlobalBounds().intersects(EntityManager::GetPlayer()->m_sprite.getGlobalBounds()) && PlayerWithAHammer == false) {
					PlayerWithAHammer = true;
					CountHammerMoving = 100;
				}

				if (CountHammerMoving > 0) {

					if (_ChangeLeftImageMario != 0) {

						entity->m_sprite.setPosition(sf::Vector2f(EntityManager::GetPlayer()->m_sprite.getPosition().x - EntityManager::GetPlayer()->m_size.x, EntityManager::GetPlayer()->m_sprite.getPosition().y + 20));

						_TextureHammer.loadFromFile("Media/Textures/Hammer1.png");
						entity->m_sprite.setOrigin(40.0f, 0.0f);
						entity->m_sprite.move(50.0f, 0.0f);
						entity->m_sprite.setTexture(_TextureHammer);

						if (CountHammerMoving > 50)
							entity->m_sprite.setRotation(90.f);
						if (CountHammerMoving < 50)
							entity->m_sprite.setRotation(0);
						if (CountHammerMoving == 1)
							CountHammerMoving = 100;
					}
					if (_ChangeRightImageMario != 0) {

						entity->m_sprite.setPosition(sf::Vector2f(EntityManager::GetPlayer()->m_sprite.getPosition().x + EntityManager::GetPlayer()->m_size.x, EntityManager::GetPlayer()->m_sprite.getPosition().y + 20));

						_TextureHammer.loadFromFile("Media/Textures/Hammer4.png");
						entity->m_sprite.setOrigin(0.0f, 0.0f);
						entity->m_sprite.move(-10.0f, 0.0f);
						entity->m_sprite.setTexture(_TextureHammer);

						if (CountHammerMoving > 50)
							entity->m_sprite.setRotation(-90.f);
						if (CountHammerMoving < 50)
							entity->m_sprite.setRotation(0);
						if (CountHammerMoving == 1)
							CountHammerMoving = 100;
					}
					CountHammerMoving--;
				}
			}
		}
		else {
			if (entity->m_type == EntityType::player) {
				entity->m_sprite.move(sf::Vector2f(0, -0.5));
				start -= 0.5;
			}
		}

		mWindow.draw(entity->m_sprite);
	}

	//-- Gravity --//
	if (EntityManager::GetGroundsCollisionPlayer() && Jump > 0 && Jump < 44) {
		EntityManager::GetPlayer()->m_sprite.move(sf::Vector2f(0, 8));
		Jump = 0;
	}
	else if (Jump > 0) {
		Jump--;
		EntityManager::GetPlayer()->m_sprite.move(sf::Vector2f(0, -1));
	}
	else if (!EntityManager::GetPipeCollisionPlayer() && !EntityManager::GetScalesCollisionPlayer() && !EntityManager::GetGroundsCollisionPlayer()) {
		EntityManager::GetPlayer()->m_sprite.move(sf::Vector2f(0, 2));
	}
	else {
		Jump = 0;
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
	}
	else
	{
		ResetSprites();
	}
}

void Game::DisplayGameSuccess()
{
	mText.setFillColor(sf::Color::Green);
	mText.setFont(mFont);
	mText.setPosition(200.f, 200.f);
	mText.setCharacterSize(80);
	mText.setString("Victory");
}

bool Game::CheckPlayerOutWindow(int x, int y) {
	if (x < -80 || x > 920 || y < -80 || y > 680)
		return true;
	return false;
}

void Game::initGame() {
	cout << "InitGame\n";
	game = 1;
	EntityManager::m_Entities.clear();
	InitSprites();
	EntityManager::GetPlayer()->m_sprite.setPosition(sf::Vector2f(605.f, 200.f));
	_lives = 3;
	_IsGameOver = false;
	start = 60;
	end = false;
	PlayerWithAGun = false;
	PlayerWithAHammer = false;
	mText.setString("");
	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}

		if (entity->m_type == EntityType::enemy) {
			entity->live = 3;
		}

		if (entity->m_type == EntityType::gun) {
			entity->live = 3;
		}
	}
}

void Game::game1() {
	//
	// Player
	//

	mPlayer.setTexture(mTexture);
	//mPlayer.setPosition(605.f, 200.f);
	mPlayer.setPosition(605.f, 260.f);
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

	/*
	//
	// Hammer
	//

	_Hammer.setTexture(_TextureHammer);
	_Hammer.setPosition(120.f, 260.f);
	std::shared_ptr<Entity> hammer = std::make_shared<Entity>();
	hammer->m_sprite = _Hammer;
	hammer->m_type = EntityType::hammer;
	hammer->m_size = _TextureHammer.getSize();
	hammer->m_position = _Hammer.getPosition();
	EntityManager::m_Entities.push_back(hammer);

	
	//
	// Enemy
	//

	_Enemy[0].setTexture(_TextureEnemy);
	_Enemy[0].setPosition(70.f, 163.f);
	std::shared_ptr<Entity> enemy = std::make_shared<Entity>();
	enemy->m_sprite = _Enemy[0];
	enemy->m_type = EntityType::enemy;
	enemy->m_size = _TextureEnemy.getSize();
	enemy->m_position = _Enemy[0].getPosition();
	enemy->moveRight = true;
	enemy->moveLeft = false;
	enemy->XMax = 390;
	enemy->XMin = 70;
	EntityManager::m_Entities.push_back(enemy);
	*/
	//
	// Pipe
	//

	_PipeStart.setTexture(_TexturePipe);
	_PipeStart.setPosition(600.f, 258.f);
	std::shared_ptr<Entity> pipeStart = std::make_shared<Entity>();
	pipeStart->m_sprite = _PipeStart;
	pipeStart->m_type = EntityType::pipeStart;
	pipeStart->m_size = _TexturePipe.getSize();
	pipeStart->m_position = _PipeStart.getPosition();
	EntityManager::m_Entities.push_back(pipeStart);

	_PipeEnd.setTexture(_TexturePipe);
	_PipeEnd.setPosition(550.f, 48.f);
	std::shared_ptr<Entity> pipeEnd = std::make_shared<Entity>();
	pipeEnd->m_sprite = _PipeEnd;
	pipeEnd->m_type = EntityType::pipeEnd;
	pipeEnd->m_size = _TexturePipe.getSize();
	pipeEnd->m_position = _PipeEnd.getPosition();
	EntityManager::m_Entities.push_back(pipeEnd);
}

void Game::game2() {
	start = 60;

	//
	// Player
	//

	mPlayer.setTexture(mTexture);
	//mPlayer.setPosition(605.f, 200.f);
	mPlayer.setPosition(105.f, 460.f);
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
		_Ground[i].setPosition(100.f + 68.f * i, 500.f);
		std::shared_ptr<Entity> ground = std::make_shared<Entity>();
		ground->m_sprite = _Ground[i];
		ground->m_type = EntityType::ground;
		ground->m_size = _TextureGround.getSize();
		ground->m_position = _Ground[0].getPosition();
		EntityManager::m_Entities.push_back(ground);
	}
	for (int i = 0; i < 4; i++) {
		_Ground[i].setTexture(_TextureGround);
		_Ground[i].setPosition(275.f + 68.f * i, 395.f);
		std::shared_ptr<Entity> ground = std::make_shared<Entity>();
		ground->m_sprite = _Ground[i];
		ground->m_type = EntityType::ground;
		ground->m_size = _TextureGround.getSize();
		ground->m_position = _Ground[0].getPosition();
		EntityManager::m_Entities.push_back(ground);
	}
	for (int i = 0; i < 4; i++) {
		_Ground[i].setTexture(_TextureGround);
		_Ground[i].setPosition(10.f + 68.f * i, 290.f);
		std::shared_ptr<Entity> ground = std::make_shared<Entity>();
		ground->m_sprite = _Ground[i];
		ground->m_type = EntityType::ground;
		ground->m_size = _TextureGround.getSize();
		ground->m_position = _Ground[0].getPosition();
		EntityManager::m_Entities.push_back(ground);
	}
	for (int i = 0; i < 6; i++) {
		_Ground[i].setTexture(_TextureGround);
		_Ground[i].setPosition(322.f + 68.f * i, 290.f);
		std::shared_ptr<Entity> ground = std::make_shared<Entity>();
		ground->m_sprite = _Ground[i];
		ground->m_type = EntityType::ground;
		ground->m_size = _TextureGround.getSize();
		ground->m_position = _Ground[0].getPosition();
		EntityManager::m_Entities.push_back(ground);
	}
	for (int i = 0; i < 9; i++) {
		_Ground[i].setTexture(_TextureGround);
		_Ground[i].setPosition(70.f + 68.f * i, 185.f);
		std::shared_ptr<Entity> ground = std::make_shared<Entity>();
		ground->m_sprite = _Ground[i];
		ground->m_type = EntityType::ground;
		ground->m_size = _TextureGround.getSize();
		ground->m_position = _Ground[0].getPosition();
		EntityManager::m_Entities.push_back(ground);
	}
	for (int i = 0; i < 2; i++) {
		_Ground[i].setTexture(_TextureGround);
		_Ground[i].setPosition(130.f + 68.f * i, 80.f);
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
	_Scale[0].setPosition(550.f, 397.f);
	std::shared_ptr<Entity> scale = std::make_shared<Entity>();
	scale->m_sprite = _Scale[0];
	scale->m_type = EntityType::scale;
	scale->m_size = _TextureScale.getSize();
	scale->m_position = _Scale[0].getPosition();
	EntityManager::m_Entities.push_back(scale);

	_Scale[1].setTexture(_TextureScale);
	_Scale[1].setPosition(285.f, 292.f);
	std::shared_ptr<Entity> scale2 = std::make_shared<Entity>();
	scale2->m_sprite = _Scale[1];
	scale2->m_type = EntityType::scale;
	scale2->m_size = _TextureScale.getSize();
	scale2->m_position = _Scale[1].getPosition();
	EntityManager::m_Entities.push_back(scale2);

	_Scale[2].setTexture(_TextureScale);
	_Scale[2].setPosition(690.f, 188.f);
	std::shared_ptr<Entity> scale3 = std::make_shared<Entity>();
	scale3->m_sprite = _Scale[2];
	scale3->m_type = EntityType::scale;
	scale3->m_size = _TextureScale.getSize();
	scale3->m_position = _Scale[2].getPosition();
	EntityManager::m_Entities.push_back(scale3);

	_Scale[3].setTexture(_TextureScale);
	_Scale[3].setPosition(90.f, 82.f);
	std::shared_ptr<Entity> scale4 = std::make_shared<Entity>();
	scale4->m_sprite = _Scale[3];
	scale4->m_type = EntityType::scale;
	scale4->m_size = _TextureScale.getSize();
	scale4->m_position = _Scale[3].getPosition();
	EntityManager::m_Entities.push_back(scale4);

	//
	// Hammer
	//

	_Hammer.setTexture(_TextureHammer);
	_Hammer.setPosition(650.f, 480.f);
	std::shared_ptr<Entity> hammer = std::make_shared<Entity>();
	hammer->m_sprite = _Hammer;
	hammer->m_type = EntityType::hammer;
	hammer->m_size = _TextureHammer.getSize();
	hammer->m_position = _Hammer.getPosition();
	EntityManager::m_Entities.push_back(hammer);

	//
	// Enemy
	//

	_Enemy[0].setTexture(_TextureEnemy);
	_Enemy[0].setPosition(20.f, 258.f);
	std::shared_ptr<Entity> enemy = std::make_shared<Entity>();
	enemy->m_sprite = _Enemy[0];
	enemy->m_type = EntityType::enemy;
	enemy->m_size = _TextureEnemy.getSize();
	enemy->m_position = _Enemy[0].getPosition();
	enemy->moveRight = true;
	enemy->moveLeft = false;
	enemy->XMax = 260;
	enemy->XMin = 20;
	EntityManager::m_Entities.push_back(enemy);

	_Enemy[1].setTexture(_TextureEnemy);
	_Enemy[1].setPosition(320.f, 258.f);
	std::shared_ptr<Entity> enemy1 = std::make_shared<Entity>();
	enemy1->m_sprite = _Enemy[1];
	enemy1->m_type = EntityType::enemy;
	enemy1->m_size = _TextureEnemy.getSize();
	enemy1->m_position = _Enemy[1].getPosition();
	enemy1->moveRight = true;
	enemy1->moveLeft = false;
	enemy1->XMax = 600;
	enemy1->XMin = 320;
	EntityManager::m_Entities.push_back(enemy1);

	_Enemy[2].setTexture(_TextureEnemy);
	_Enemy[2].setPosition(320.f, 152.f);
	std::shared_ptr<Entity> enemy2 = std::make_shared<Entity>();
	enemy2->m_sprite = _Enemy[2];
	enemy2->m_type = EntityType::enemy;
	enemy2->m_size = _TextureEnemy.getSize();
	enemy2->m_position = _Enemy[2].getPosition();
	enemy2->moveRight = true;
	enemy2->moveLeft = false;
	enemy2->XMax = 650;
	enemy2->XMin = 420;
	EntityManager::m_Entities.push_back(enemy2);

	_Enemy[3].setTexture(_TextureEnemy);
	_Enemy[3].setPosition(70.f, 152.f);
	std::shared_ptr<Entity> enemy3 = std::make_shared<Entity>();
	enemy3->m_sprite = _Enemy[3];
	enemy3->m_type = EntityType::enemy;
	enemy3->m_size = _TextureEnemy.getSize();
	enemy3->m_position = _Enemy[3].getPosition();
	enemy3->moveRight = true;
	enemy3->moveLeft = false;
	enemy3->XMax = 400;
	enemy3->XMin = 70;
	EntityManager::m_Entities.push_back(enemy3);

	//
	// Pipe
	//

	_PipeStart.setTexture(_TexturePipe);
	_PipeStart.setPosition(100.f, 458.f);
	std::shared_ptr<Entity> pipeStart = std::make_shared<Entity>();
	pipeStart->m_sprite = _PipeStart;
	pipeStart->m_type = EntityType::pipeStart;
	pipeStart->m_size = _TexturePipe.getSize();
	pipeStart->m_position = _PipeStart.getPosition();
	EntityManager::m_Entities.push_back(pipeStart);

	_PipeEnd.setTexture(_TexturePipe);
	_PipeEnd.setPosition(200.f, 38.f);
	std::shared_ptr<Entity> pipeEnd = std::make_shared<Entity>();
	pipeEnd->m_sprite = _PipeEnd;
	pipeEnd->m_type = EntityType::pipeEnd;
	pipeEnd->m_size = _TexturePipe.getSize();
	pipeEnd->m_position = _PipeEnd.getPosition();
	EntityManager::m_Entities.push_back(pipeEnd);
}

void Game::game3() {}