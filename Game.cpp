#include "Game.h"


//Funções privadas
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Cybercity", sf::Style::Fullscreen);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initPlayer()
{
	this->player = new Player(*this->window);
}


void Game::pollEvents()
{
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

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) && this->player->getOnGround())
		this->player->startJump();


}

void Game::updatePlayerSprite()
{
	auto elapsedTime = this->timer.getElapsedTime().asSeconds();
	auto frameX = 0;

	if (this->isPlayerWalking && this->player->getOnGround()) {
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

	if (!this->player->getOnGround()) {
		if (elapsedTime >= this->switchJumpingPlayerSpriteInterval) {
			this->currentJumpingFrame = (currentJumpingFrame + 1) % 4;
			this->timer.restart();

			frameX = this->currentJumpingFrame * 48;
			this->player->updateJumpingTexture(frameX);
		}
	}
}

void Game::render()
{
	//Limpa o frame antigo
	this->window->clear();
	
	//Renderiza o novo frame
	this->player->render(*window);

	//Exibe o novo frame
	this->window->display();


}

//Construtor
Game::Game()
{
	this->initWindow();
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
