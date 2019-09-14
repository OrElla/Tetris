#pragma once
#include <queue>
#include "Board.h"
#include <memory>
#include "I.h"
#include "J.h"
#include "T.h"
#include "Z.h"
#include "O.h"
#include "L.h"
#include "S.h"
#include <iostream>
const int NUM_OF_SHAPES = 7;
const int P_SIZE = 32;
const int NUM_OF_LEVELS = 2;
const int MAX_LEVEL_POINTS = 10;
const int NUM_OF_STATUS_BAR = 3;
const int NUM_OF_FONTS = 2;
const int NUM_OF_MUSIC = 4;


class Controller
{
public:
	Controller();
	bool run(sf::RenderWindow & window);

	~Controller();

private:
	void insertShape();
	void loadFiles();
	void draw(sf::RenderWindow & window);
	void drawNextShape(sf::RenderWindow & window);
	void getKey(sf::Keyboard::Key key);
	Board m_board;
	void moveDown(sf::Clock &clock);
	std::queue <std::unique_ptr<Shape>> m_shapes;
	int m_score = 0;
	int m_life = 0;
	int m_level = 1;
	void defineTool(sf::RenderWindow & window);
	void drawGetReady(sf::RenderWindow & window);
	void drawNextLevel(sf::RenderWindow & window);
	void levelFinished(sf::RenderWindow & window);
	bool checkGameOver(); 
	void dropShape();
	void switchShape();
	bool checkCollision();
	double m_speed = 0.5;
	sf::Text m_getReady;
	sf::Text m_nextLevel;

	sf::Text m_statusBar[NUM_OF_STATUS_BAR];
	sf::Font font[NUM_OF_FONTS];
	sf::SoundBuffer m_soundbuffer;
	sf::Music m_music[NUM_OF_MUSIC];

	
	sf::Texture m_texture;
	sf::Sprite m_backGroundScreen;
	
};

