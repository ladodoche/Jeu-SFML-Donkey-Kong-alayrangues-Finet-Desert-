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
	, _Ground()
	, _Scale()
	, mIsMovingRight(false)
	, mIsMovingLeft(false)
{
	mWindow.setFramerateLimit(160);

	mTexture.loadFromFile("Media/Textures/Mario1.png");
	_TextureGround.loadFromFile("Media/Textures/Block.png");
	_TextureScale.loadFromFile("Media/Textures/Echelle.png");

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
		if ((EntityManager::GetGroundCollisionFootPlayer() || Jump != 0 && (!EntityManager::GetScalesCollisionPlayer("a")) || ((EntityManager::GetTopScalesCollisionPlayer()) || EntityManager::GetBottomScalesCollisionPlayer())) || (EntityManager::GetScalesCollisionPlayer("a")) && ((EntityManager::GetTopScalesCollisionPlayer()) || EntityManager::GetBottomScalesCollisionPlayer()))
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
		cout << (EntityManager::GetGroundCollisionFootPlayer() && !EntityManager::GetScalesCollisionPlayer("a")) << "\n";
		cout << (Jump != 0 && EntityManager::GetScalesCollisionPlayer("a")) << "\n";
		cout << (EntityManager::GetTopScalesCollisionPlayer()) << "\n";
		cout << (EntityManager::GetBottomScalesCollisionPlayer()) << "\n";
		cout << "\n";
		if ((EntityManager::GetGroundCollisionFootPlayer() || Jump != 0 && (!EntityManager::GetScalesCollisionPlayer("a")) || ((EntityManager::GetTopScalesCollisionPlayer()) || EntityManager::GetBottomScalesCollisionPlayer())) || (EntityManager::GetScalesCollisionPlayer("a")) && ((EntityManager::GetTopScalesCollisionPlayer()) || EntityManager::GetBottomScalesCollisionPlayer()))
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

void Game::render()
{
	mWindow.clear();

	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}

		if (entity->m_type == EntityType::scale) {
			sf::RectangleShape rectangle;
			rectangle.setSize(sf::Vector2f(entity->m_size.x/10, entity->m_size.y));
			rectangle.setPosition(entity->m_position.x + entity->m_size.x / 2, entity->m_position.y);

			mWindow.draw(rectangle);
		}

		if (entity->m_type == EntityType::player) {
			sf::RectangleShape rectanglePlayer;
			rectanglePlayer.setSize(sf::Vector2f(entity ->m_size.x / 10, entity->m_size.y));
			rectanglePlayer.setPosition(entity->m_sprite.getPosition().x + entity->m_size.x / 2, entity->m_sprite.getPosition().y);
			mWindow.draw(rectanglePlayer);
		}


		mWindow.draw(entity->m_sprite);
	}

	//-- Gravity --//
	if (EntityManager::GetGroundsCollisionPlayer() && Jump > 0 && Jump < 44) {
		EntityManager::GetPlayer()->m_sprite.move(sf::Vector2f(0, 2));
		Jump = 0;
		if (mIsMovingLeft)
			EntityManager::GetPlayer()->m_sprite.move(sf::Vector2f(2, 0));
		if (mIsMovingRight)
			EntityManager::GetPlayer()->m_sprite.move(sf::Vector2f(-2, 0));
	}
	else if (Jump > 0) {
		Jump--;
		EntityManager::GetPlayer()->m_sprite.move(sf::Vector2f(0, -1));
	}
	else if (!EntityManager::GetScalesCollisionPlayer("a") && !EntityManager::GetGroundsCollisionPlayer()) {
		Jump = 0;
		TouchGround = false;
		EntityManager::GetPlayer()->m_sprite.move(sf::Vector2f(0, 2));
	}
	else {
		TouchGround = true;
	}

	mWindow.draw(mText);
	mWindow.display();
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
		if (EntityManager::GetScalesCollisionPlayer("top"))
			EntityManager::GetPlayer()->m_sprite.move(sf::Vector2f(0, -2));
	if (key == sf::Keyboard::Down)
		if ((!EntityManager::GetGroundCollisionFootPlayer() && EntityManager::GetScalesCollisionPlayer("top")) || EntityManager::GetScalesCollisionPlayerToGoDown())
			EntityManager::GetPlayer()->m_sprite.move(sf::Vector2f(0, +2));
	if (key == sf::Keyboard::Space && Jump == 0 && TouchGround == true)
		Jump = 45;
}
