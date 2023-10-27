#pragma once

#include <SFML/Graphics.hpp>

class Game
{
private:

	//Janela
	sf::RenderWindow* window;

	//Fun��es privadas
	void initWindow();


public:

	Game();
	~Game();

	//Fun��es p�blicas
	void run();
	void pollEvents();
	void update();
	void render();

};

