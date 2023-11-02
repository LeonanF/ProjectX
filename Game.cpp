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
	if (this->timer.getElapsedTime().asSeconds() >= this->switchPlayerSpriteInterval) {
		this->currentFrame = (currentFrame + 1) % 4;
		this->timer.restart();

		int frameX = this->currentFrame * 48;

		this->player->updateStaticTexture(frameX);
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
