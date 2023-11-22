#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class Game
{
private:

	std::vector<sf::Sprite*> platformSprite;
	sf::Texture platformTexture;
	sf::Clock timer;
	float switchStaticPlayerSpriteInterval = .25f;
	float switchMovingPlayerSpriteInterval = .15f;
	float switchJumpingPlayerSpriteInterval = .2f;
	int currentMovingFrame = 0;
	int currentStaticFrame = 0;
	int currentJumpingFrame = 0;
	bool isPlayerWalking = false;

	//Janela
	sf::RenderWindow* window;
	Player* player;

	//Funções privadas
	void initWindow();
	void initPlayer();
	void initTexture();
	void initSprite();
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

