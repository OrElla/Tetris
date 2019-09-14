#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include"SFML\Window.hpp"
#include "SFML\Audio.hpp"
//#include "FileManager.h"
#include <vector>


#define size 4

enum TetrisSound_t { MUNCH, DEATH};
enum gameSound_t { LVL_UP, GAME_IS_OVER };

enum Screen_m { MENU_m, PLAY_m,GAME_OVER_m};
enum Menu_t { PLAY_t, EXIT_t, SOUND_t};
enum GAME_OVER_f {PLAY_f , EXIT_f , SOUND_f};
enum Fonts_t { GAME_FONT, GET_READY_FONT };

const double Cols = 10;
const double Rows = 20;
const double width = 610;
const double hight = 610;
const double BoardHight = hight - 10;
const double BoardWidth = BoardHight / 2;
const double rectSize = BoardHight / Rows;
const double leftGap = (width / 2 - BoardWidth / 2);
const double ceiling = hight - BoardHight - 1;
const int rectThicknes = 1;

enum Direction {DOWN, LEFT , RIGHT, SPACE};
class Board;

class Shape
{
public:
	Shape();
	~Shape();

	void rotateShape(const Board & board);
	void move(Direction direction, const Board & board);
	

	void draw(sf::RenderWindow& window);
	void drawNext(sf::RenderWindow& window); 
	const std::vector<sf::Vector2f> getPos();
	const std::vector<sf::RectangleShape> getRects();
	bool isOver(bool collision);

protected:
	std::vector<sf::RectangleShape> m_rects;
	bool canMove(const Board & board, Direction direction);
	sf::Color getRandColor();
	bool canRotate(const Board & board);
};

