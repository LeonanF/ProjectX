#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class Game
{
private:

	sf::Clock timer;
	float switchStaticPlayerSpriteInterval = .25f;
	float switchMovingPlayerSpriteInterval = .15f;
	int currentFrame = 0;
	bool isPlayerWalking = false;

	//Janela
	sf::RenderWindow* window;
	Player* player;

	//Funções privadas
	void initWindow();
	void initPlayer();
	void pollEvents();
	void update();
	void updateInput();
	void render();


public:

	Game();
	~Game();

	//Funções públicas
	void run();

};

