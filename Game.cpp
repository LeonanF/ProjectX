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
	this->player = new Player();
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
}

void Game::render()
{
	//Limpa o frame antigo
	this->window->clear();

	//Exibe o novo frame
	this->window->display();
}
