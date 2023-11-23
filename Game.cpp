#include "Game.h"
#include "random"


//Funções privadas
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Cybercity", sf::Style::Fullscreen);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initPlayer()
{
	this->player = new Player(*this->window, this->ground[0]->getGlobalBounds().height);
}

void Game::initTexture()
{
	if (!this->platformTexture.loadFromFile("Textures/Tiles/platform.png"))
	{
		std::cout << "ERROR::GAME::INITTEXTURE::Erro ao carregar textura!";
	}

	if (!this->backgroundTexture.loadFromFile("Textures/Background/Background.png"))
	{
		std::cout << "ERROR::GAME::INITTEXTURE::Erro ao carregar textura!";
	}

	this->groundTexture.resize(2);

	for (int i = 0; i < 2; i++) {
		std::string filePath = "Textures/Tiles/ground" + std::to_string(i + 1) + ".png";

		if (!this->groundTexture[i].loadFromFile(filePath))
		{
			std::cout << "ERROR::GAME::INITTEXTURE::Erro ao carregar textura!";
		}
	}
}

void Game::initSprite()
{
	int windowSizeY = this->window->getSize().y;

	this->platformSprite.resize(4);
	

	for (int i = 0; i < 4; i++) {

		this->platformSprite[i] = new sf::Sprite();
		platformSprite[i]->setTexture(this->platformTexture);
		platformSprite[i]->setScale(3.0f, 3.0f);
	}

	

	this->backgroundSprite.setTexture(backgroundTexture);

	// Calcular a proporção das texturas
	float scaleX = static_cast<float>(this->window->getSize().x) / this->backgroundSprite.getLocalBounds().width;
	float scaleY = static_cast<float>(this->window->getSize().y) / this->backgroundSprite.getLocalBounds().height;


	float scale = std::min(scaleX, scaleY);
	this->backgroundSprite.setScale(scale, scale);
	
	float scaleGrounds = 3.0f;

	int grounds = ceil(this->window->getSize().x / (this->platformTexture.getSize().x * scaleGrounds));
	this->ground.resize(grounds);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 4);

	for (int i = 0; i < grounds; i++) {

		this->ground[i] = new sf::Sprite();

		if (dist(gen) == 0) {
			ground[i]->setTexture(this->groundTexture[1]);
		}
		else {
			ground[i]->setTexture(this->groundTexture[0]);
		}

		ground[i]->setScale(scaleGrounds, scaleGrounds);
		ground[i]->setPosition(i * this->ground[i]->getGlobalBounds().width, this->window->getSize().y - this->ground[i]->getGlobalBounds().height);
	}

	auto initPosX = 400;
	auto platformWidth = this->platformSprite[0]->getGlobalBounds().width;
	auto platformHeight = this->platformSprite[0]->getGlobalBounds().height;


	auto initPosY = this->window->getSize().y - this->ground[0]->getGlobalBounds().height - platformHeight * 4;

	platformSprite[0]->setPosition(initPosX, initPosY);
	platformSprite[1]->setPosition(initPosX + platformWidth, initPosY);
	platformSprite[2]->setPosition(initPosX + platformWidth * 2, initPosY);

	platformSprite[3]->setPosition(initPosX + platformWidth * 8, initPosY);
}

void Game::initMusic()
{
	if (!this->theme.openFromFile("Sounds/theme.ogg"))
	{
		std::cout << "ERROR::GAME::INITMUSIC::Erro ao carregar tema!";
	}
	this->theme.setVolume(5.f);
	this->theme.setLoop(true);
	this->theme.play();
}

void Game::pollEvents()
{//
	sf::Event ev;
	while (this->window->isOpen() && this->window->pollEvent(ev)) {
		if (ev.type == sf::Event::Closed)
			this->window->close();
		if (ev.KeyPressed && ev.key.code == sf::Keyboard::Escape)
			this->window->close();
	}

}

void Game::update()
{
	this->pollEvents();
	this->updateInput();
	this->player->update();
	this->updatePlayerSprite();
	this->collision();
}

void Game::updateInput()
{

	//Lógica de movimentação no eixo X
	bool walking = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->player->move("Left");
		walking = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->player->move("Right");
		walking = true;
	}

	this->isPlayerWalking = walking;

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) && (this->player->getOnGround() || this->onPlatform))
		this->player->startJump();

	// Crouch
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) && this->player->getOnGround()) {
		this->player->crouch();
	}
	else {
		this->player->standUp();
	}
		
}

void Game::updatePlayerSprite()
{
	auto elapsedTime = this->timer.getElapsedTime().asSeconds();
	auto frameX = 0;

	if (this->isPlayerWalking && (this->player->getOnGround()  || this->onPlatform)) {
		if (elapsedTime >= this->switchMovingPlayerSpriteInterval) {
			this->currentMovingFrame = (currentMovingFrame + 1) % 6;
			this->timer.restart();

			frameX = this->currentMovingFrame * 48;
			this->player->updateMovingTexture(frameX);
		}
	}
	else if (elapsedTime >= this->switchStaticPlayerSpriteInterval) {
		this->currentStaticFrame = (currentStaticFrame + 1) % 4;
		this->timer.restart();

		frameX = this->currentStaticFrame * 48;

		this->player->updateStaticTexture(frameX);
	}

	if (!this->player->getOnGround() && !this->onPlatform) {
		if (elapsedTime >= this->switchJumpingPlayerSpriteInterval) {
			this->currentJumpingFrame = (currentJumpingFrame + 1) % 4;
			this->timer.restart();

			frameX = this->currentJumpingFrame * 48;
			this->player->updateJumpingTexture(frameX);
		}
	}

	// Crouch
	if (this->player->getOnGround() && this->player->getIsCrouch()) {
		if (elapsedTime >= this->switchCrouchingPlayerSpriteInterval) {
			frameX = this->currentCrouchingFrame * 48;
			this->player->updateCrouchingTexture(frameX);

			if (currentCrouchingFrame != 2) {
				this->currentCrouchingFrame = (currentCrouchingFrame + 1) % 3;
			}
			this->timer.restart();
		}
	}
}

void Game::render()
{
	//Limpa o frame antigo
	this->window->clear();
	this->window->draw(this->backgroundSprite);

	for (auto ground : this->ground) {
		this->window->draw(*ground);
	}

	for (auto platform : this->platformSprite) {
		this->window->draw(*platform);
	}
	
	//Renderiza o novo frame
	this->player->render(*window);

	//Exibe o novo frame
	this->window->display();


}

void Game::collision()
{
	sf::FloatRect playerRealBounds(this->player->getPlayerBounds());

	this->onPlatform = false;

	for (auto platform:this->platformSprite){
		sf::FloatRect platformBounds(platform->getGlobalBounds());

		if ((playerRealBounds.left + playerRealBounds.width / 1.3f > platformBounds.left &&
			playerRealBounds.left + playerRealBounds.width / 3.8f < platformBounds.left + platformBounds.width) &&
			(playerRealBounds.top + playerRealBounds.height > platformBounds.top &&
				playerRealBounds.top + playerRealBounds.height < platformBounds.top + platformBounds.height)) {
			this->onPlatform = true;
			this->player->setPosition(platformBounds.top - playerRealBounds.height);
			this->player->setJumpSpeed(0.f);
			break;
		}
	}

}

//Construtor
Game::Game()
{
	this->initWindow();	
	this->initTexture();
	this->initMusic();
	this->initSprite();
	this->initPlayer();
}

//Destrutor
Game::~Game()
{
	delete this->window;
}

//Funções públicas
void Game::run()
{
	while (this->window->isOpen()) {
		this->update();
		this->render();
	}
}
