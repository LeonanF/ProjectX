#include "Player.h"

void Player::initSprite()
{
	this->PlayerSprite.setTexture(this->PlayerTexture);
	this->PlayerSprite.setScale(2.f, 2.f);

	sf::Vector2u windowSize = gameWindow.getSize();
	sf::Vector2f playerSize = this->getDimensions();

	this->PlayerSprite.setPosition(0, windowSize.y - playerSize.y);
}

void Player::initTexture()
{
	//Carregar textura
	if (this->PlayerTexture.loadFromFile("Textures/Biker/biker_idle.png"))
		this->PlayerSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
	else
		std::cout << "ERROR::PLAYER::INITTEXTURE::Erro ao carregar textura!";

}

Player::Player(sf::RenderWindow& window)
	: gameWindow(window)
{
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}

const sf::Vector2f Player::getDimensions() const
{
	sf::FloatRect bounds = this->PlayerSprite.getGlobalBounds();
	return sf::Vector2f(bounds.width, bounds.height);
}

void Player::update()
{
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->PlayerSprite);
}

void Player::updateStaticTexture(int frameX)
{
	this->PlayerSprite.setTextureRect(sf::IntRect(frameX, 0, 48, 48));
}
