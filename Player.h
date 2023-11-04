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

	sf::RenderWindow& gameWindow;

	MoveSpeeds moveSpeedMultiplier;
	float moveSpeed;
	float playerScale;
	bool needToCorrectPosition = true;

	//Funções privadas
	void initVariables();
	void initSprite();
	void initTexture();
	void isTouchingBorderWindow();

public:

	//Construtor e destrutor
	Player(sf::RenderWindow& window);
	virtual ~Player();

	//Getters e Setters
	const sf::Vector2f getDimensions() const;

	//Funções públicas
	void update();
	void render(sf::RenderTarget& target);
	void updateStaticTexture(int frameX);
	void updateMovingTexture(int frameX);
	void move(sf::String side);

};

