#pragma once
#include "Controller.h"

const int NUM_OF_SCREENS = 3;

class Screens
{
public:
	Screens();

	void loadScreens();
	void runMenu();
	void menu(sf::RenderWindow &window);
	void gameOver(sf::RenderWindow & window);

	Menu_t getMenuButton(sf::Vector2i buttonPos);
	GAME_OVER_f getGoButton(sf::Vector2i buttonPos);
	~Screens();

private:
	sf::Texture m_screens[NUM_OF_SCREENS];
	sf::Sprite gameScreens[NUM_OF_SCREENS];
	Controller m_gameController;
	bool GameIsOver = false;
	bool NewGame = false;
	sf::Music dead_music;

};

