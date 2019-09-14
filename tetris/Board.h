#pragma once
#include <vector>
#include <memory>
#include "Shape.h"
#include <experimental/vector>


class Board
{
public:
	Board();
	~Board();
	void draw(sf::RenderWindow & window);
	bool checkCollision(const std::vector<sf::RectangleShape>&);
	sf::RectangleShape * getRect(int row,int col)const;
	void addShape(const std::vector<sf::RectangleShape>& shapeRecs);
	int getScore();

private:
	int m_boardScore = 0;
	int m_erasedLines = 0;
	void setSize();
	void updateRows();
	std::vector <std::vector <std::unique_ptr<sf::RectangleShape>>> m_rects;
	std::vector <sf::RectangleShape> m_rect_rows;
	std::vector <sf::RectangleShape> m_rect_cols;
	sf::Music m_breakRow;
	int m_currentScore=0;
};


