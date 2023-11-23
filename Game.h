#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"

class Game
{
private:

	std::vector<sf::Sprite*> platformSprite;
	std::vector<sf::Sprite*> ground;
	sf::Texture platformTexture;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Clock timer;
	sf::Music theme;
	float switchStaticPlayerSpriteInterval = .25f;
	float switchMovingPlayerSpriteInterval = .15f;
	float switchJumpingPlayerSpriteInterval = .2f;
	float switchCrouchingPlayerSpriteInterval = .2f; // Crouch
	int currentMovingFrame = 0;
	int currentStaticFrame = 0;
	int currentJumpingFrame = 0;
	int currentCrouchingFrame = 0; // Crouch
	bool isPlayerWalking = false;
	bool onPlatform = false;


	//Janela
	sf::RenderWindow* window;
	Player* player;

	//Funções privadas
	void initWindow();
	void initPlayer();
	void initTexture();
	void initSprite();
	void initMusic();
	void pollEvents();
	void update();
	void updateInput();
	void updatePlayerSprite();
	void render();
	void collision();


public:

	Game();
	~Game();

	//Funções públicas
	void run();

};