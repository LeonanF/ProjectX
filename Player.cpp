#include "Player.h"

void Player::initVariables()
{
	this->moveSpeed = 3.f;
	this->playerScale = 2.5f;
	this->needToCorrectPosition = true;
	this->onGround = true;
	this->jumpSpeed = 0.f;
	this->gravity = 0.5f;
	this->isCrouching = false; // Crouch
}

void Player::initSprite()
{
	this->PlayerSprite.setTexture(this->StaticPlayerTexture);
	this->PlayerSprite.setScale(this->playerScale, this->playerScale);

	sf::Vector2u windowSize = gameWindow.getSize();
	sf::Vector2f playerSize = this->getDimensions();

	this->PlayerSprite.setPosition(playerSize.x, windowSize.y - playerSize.y - groundHeight);

}

void Player::initTexture()
{
	//Carregar textura
	if (this->StaticPlayerTexture.loadFromFile("Textures/Biker/biker_idle.png"))
		this->PlayerSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
	else
		std::cout << "ERROR::PLAYER::INITTEXTURE::Erro ao carregar textura!";

	if (!this->MovingPlayerTexture.loadFromFile("Textures/Biker/biker_walk.png"))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Erro ao carregar textura!";

	if (!this->JumpingPlayerTexture.loadFromFile("Textures/Biker/biker_jump.png"))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Erro ao carregar textura!";

	// Crouch
	if (!this->CrouchingPlayerTexture.loadFromFile("Textures/Biker/biker_crouch1.png"))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Erro ao carregar textura!";
}

void Player::isTouchingBorderWindow()
{
	sf::FloatRect spriteBounds = this->PlayerSprite.getGlobalBounds();
	sf::Vector2u windowSize = this->gameWindow.getSize();

	if (spriteBounds.left + (spriteBounds.width/3.5f) < 0)
		this->moveSpeedMultiplier.left = 0.f;
	else
		this->moveSpeedMultiplier.left = -1.f;

	if (spriteBounds.left + (spriteBounds.width/1.4f) > windowSize.x)
		this->moveSpeedMultiplier.right = 0.f;
	else
		this->moveSpeedMultiplier.right = 1.f;

	if (spriteBounds.top + spriteBounds.height > (windowSize.y - this->groundHeight)) {
		this->jumpSpeed = 0.f;
		this->onGround = true;
		this->PlayerSprite.setPosition(this->PlayerSprite.getPosition().x , windowSize.y - this->getDimensions().y - groundHeight);
	}

}

void Player::jump() {
	if (!this->onGround) {
		this->jumpSpeed += this->gravity;
		this->PlayerSprite.setPosition(this->PlayerSprite.getPosition().x, this->PlayerSprite.getPosition().y + this->jumpSpeed);
	}
}

Player::Player(sf::RenderWindow& window, int groundh)
	: gameWindow(window), groundHeight(groundh)
{
	this->initVariables();
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
	this->isTouchingBorderWindow();
	this->jump();
}

bool Player::getOnGround() const
{
	return this->onGround;
}

bool Player::getIsCrouch() const
{
	return this->isCrouching;
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->PlayerSprite);
}

void Player::updateStaticTexture(int frameX)
{
	this->PlayerSprite.setTexture(this->StaticPlayerTexture);
	this->PlayerSprite.setTextureRect(sf::IntRect(frameX, 0, 48, 48));
}

void Player::updateMovingTexture(int frameX)
{
		this->PlayerSprite.setTexture(this->MovingPlayerTexture);
		this->PlayerSprite.setTextureRect(sf::IntRect(frameX, 0, 48, 48));
}

void Player::updateJumpingTexture(int frameX)
{
	this->PlayerSprite.setTexture(this->JumpingPlayerTexture);
	this->PlayerSprite.setTextureRect(sf::IntRect(frameX, 0, 48, 48));
}

// Crouch
void Player::updateCrouchingTexture(int frameX)
{
	this->PlayerSprite.setTexture(this->CrouchingPlayerTexture);
	this->PlayerSprite.setTextureRect(sf::IntRect(frameX, 0, 48, 48));
}

void Player::move(sf::String side)
{

	if (side == "Right") {
		this->PlayerSprite.move(this->moveSpeedMultiplier.right * moveSpeed, 0);
		this->PlayerSprite.setScale(this->playerScale, this->playerScale);

		if (!needToCorrectPosition) {
			this->PlayerSprite.setPosition(this->PlayerSprite.getPosition().x - (this->PlayerSprite.getGlobalBounds().width) / 2, this->PlayerSprite.getPosition().y);
			needToCorrectPosition = true;
		}
	}
	if (side == "Left") {
		this->PlayerSprite.move(this->moveSpeedMultiplier.left * moveSpeed, 0);
		this->PlayerSprite.setScale(-this->playerScale, this->playerScale);

		if (needToCorrectPosition) {
			this->PlayerSprite.setPosition(this->PlayerSprite.getPosition().x + (this->PlayerSprite.getGlobalBounds().width) / 2, this->PlayerSprite.getPosition().y);
			needToCorrectPosition = false;
		}
	}


}

void Player::startJump()
{
	this->jumpSpeed = -12.0f;
	this->onGround = false;
}

// Crouch
void Player::crouch()
{
	isCrouching = true;
}

void Player::standUp()
{
	isCrouching = false;
}
