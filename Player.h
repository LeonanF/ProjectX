#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"

class Player
{
private:
	
	sf::Sprite PlayerSprite;
	sf::Texture PlayerTexture;

	//Funções privadas
	void initSprite();
	void initTexture();

public:

	Player();
	virtual ~Player();

};

