#pragma once

#include <SFML/Graphics.hpp>

class Game
{
private:

	//Janela
	sf::RenderWindow* window;

	//Funções privadas
	void initWindow();


public:

	Game();
	~Game();

	//Funções públicas
	void run();
	void pollEvents();
	void update();
	void render();

};

