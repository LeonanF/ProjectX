#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"

class Player
{
private:
	
	sf::Sprite PlayerSprite;
	sf::Texture PlayerTexture;

	sf::RenderWindow& gameWindow;

	//Fun��es privadas
	void initSprite();
	void initTexture();

public:

	//Construtor e destrutor
	Player(sf::RenderWindow& window);
	virtual ~Player();

	//Getters e Setters
	const sf::Vector2f getDimensions() const;

	//Fun��es p�blicas
	void update();
	void render(sf::RenderTarget& target);
	void updateStaticTexture(int frameX);

};

