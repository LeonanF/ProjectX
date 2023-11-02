#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"

class Player
{
private:
	
	sf::Sprite PlayerSprite;
	sf::Texture PlayerTexture;

	//Fun��es privadas
	void initSprite();
	void initTexture();

public:

	Player();
	virtual ~Player();

};

