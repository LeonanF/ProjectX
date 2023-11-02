#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class Game
{
private:

	//Janela
	sf::RenderWindow* window;
	Player* player;

	//Fun��es privadas
	void initWindow();
	void initPlayer();


public:

	Game();
	~Game();

	//Fun��es p�blicas
	void run();
	void pollEvents();
	void update();
	void render();

};

