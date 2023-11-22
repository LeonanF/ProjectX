#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class Game
{
private:

	sf::Clock timer;
	float switchStaticPlayerSpriteInterval = .25f;
	float switchMovingPlayerSpriteInterval = .15f;
	float switchJumpingPlayerSpriteInterval = .2f;
	float switchCrouchingPlayerSpriteInterval = .2f; // Crouch
	int currentMovingFrame = 0;
	int currentStaticFrame = 0;
	int currentJumpingFrame = 0;
	int currentCrouchingFrame = 0; // Crouch
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
	void updatePlayerSprite();
	void render();


public:

	Game();
	~Game();

	//Funções públicas
	void run();

};

