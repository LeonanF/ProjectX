#include "Player.h"

void Player::initSprite()
{
	this->PlayerSprite.setTexture(this->PlayerTexture);
	this->PlayerSprite.scale(0.3f, 0.3f);
}

void Player::initTexture()
{
	//Carregar textura
	if (!this->PlayerTexture.loadFromFile("Textures/Biker/biker_idle.png"))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Erro ao carregar textura!";

}

Player::Player()
{
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}
