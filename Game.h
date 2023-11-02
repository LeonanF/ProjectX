#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class Game
{
private:

	//Janela
	sf::RenderWindow* window;
	Player* player;

	//Funções privadas
	void initWindow();
	void initPlayer();


public:

	Game();
	~Game();

	//Funções públicas
	void run();
	void pollEvents();
	void update();
	void render();

};

