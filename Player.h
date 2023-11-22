#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"

struct MoveSpeeds {
	float right = 1.f;
	float left = -1.f;
};

class Player
{
private:
	
	sf::Sprite PlayerSprite;
	sf::Texture StaticPlayerTexture;
	sf::Texture MovingPlayerTexture;
	sf::Texture JumpingPlayerTexture;

	sf::RenderWindow& gameWindow;
	
	MoveSpeeds moveSpeedMultiplier;
	sf::Clock jumpClock;
	float moveSpeed;
	float playerScale;
	float jumpSpeed;
	float gravity;
	bool needToCorrectPosition;
	bool onGround;
	int groundHeight;

	//Funções privadas
	void initVariables();
	void initSprite();
	void initTexture();
	void isTouchingBorderWindow();
	void jump();

public:

	//Construtor e destrutor
	Player(sf::RenderWindow& window, int groundh);
	virtual ~Player();

	//Getters e Setters
	const sf::Vector2f getDimensions() const;
	bool getOnGround() const;

	//Funções públicas
	void update();
	void render(sf::RenderTarget& target);
	void updateStaticTexture(int frameX);
	void updateMovingTexture(int frameX);
	void updateJumpingTexture(int frameX);
	void move(sf::String side);
	void startJump();

};

