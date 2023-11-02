#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class Game
{
private:

	sf::Clock timer;
	float switchPlayerSpriteInterval = .25f;
	int currentFrame = 0;

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

