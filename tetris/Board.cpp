#include "Board.h"
#include <iostream>

//THE BOARD CONSTRUCTOR
Board::Board()
{
	srand(time(NULL));
	for (size_t i = 0; i < Rows+1 ; i++)
	{
		m_rect_rows.push_back(sf::RectangleShape(sf::Vector2f(BoardWidth, 1)));
		m_rect_rows[i].setFillColor(sf::Color::Black);
	}
	for (size_t i = 0; i < Cols+1 ; i++)
	{
		m_rect_cols.push_back(sf::RectangleShape(sf::Vector2f(1, BoardHight)));
		m_rect_cols[i].setFillColor(sf::Color::Black);
	}
	setSize();

	m_breakRow.openFromFile("sounds/breakRow.wav");

}

//DISTRUCTOR
Board::~Board()
{
}
//DRAW THE BOARD
void Board::draw(sf::RenderWindow & window)
{
	for (size_t i = 0; i < Rows; i++)
		for (size_t j = 0; j < Cols; j++)
			if (m_rects[i][j])
			{
				m_rects[i][j].get()->setPosition
				(sf::Vector2f(leftGap + j * rectSize, ceiling + i * rectSize));
				window.draw(*m_rects[i][j]);
			}
	for (size_t i = 0; i < Rows+1; i++)
	{
		m_rect_rows[i].setPosition(sf::Vector2f(leftGap,ceiling+(i * rectSize)));
		window.draw(m_rect_rows[i]);
	}
	for (size_t i = 0; i < Cols+1; i++)
	{
		m_rect_cols[i].setPosition(sf::Vector2f(leftGap + i * rectSize,ceiling));
		window.draw(m_rect_cols[i]);
	}
}

//CHECK IF AN IMAGE COLLIDED 
bool Board::checkCollision(const std::vector<sf::RectangleShape>& shapeRecs)
{
	if (std::any_of(shapeRecs.begin(), shapeRecs.end(),
		[this](sf::RectangleShape rec)
	{
		int row = (rec.getGlobalBounds().top - ceiling) / rectSize ;
		int col = (rec.getGlobalBounds().left - leftGap) / rectSize;
		if (rec.getGlobalBounds().top == BoardHight - rectSize + ceiling)
			return true;
		if (this->getRect(row+1, col))
			return true;
		return false;
	}))
	{
		addShape(shapeRecs);
		updateRows();
		return true;
	}
	return false;
}

//GET RECT
sf::RectangleShape * Board::getRect(int row, int col)const
{
	return m_rects[row][col].get();
}

//ADD NEW SHAPE
void Board::addShape(const std::vector<sf::RectangleShape>& shapeRecs)
{
	for (size_t i = 0; i < size; i++)
	{
		int row = (shapeRecs[i].getGlobalBounds().top - ceiling) / rectSize;
		int col = (shapeRecs[i].getGlobalBounds().left - leftGap) / rectSize;
		m_rects[row][col] =
			std::make_unique<sf::RectangleShape>(shapeRecs[i]);
		m_rects[row][col].get()->setOrigin(0, 0);
		m_rects[row][col].get()->setRotation(0);
	}
}


//UPDATE THE SCORE
int Board::getScore()
{
	return m_boardScore;
}

//SET THE SIZE
void Board::setSize()
{
	m_rects.resize(Rows);
	for (size_t i = 0; i < Rows; i++)
		m_rects[i].resize(Cols);
}


//UPDATES THE ROWS AFTER COLLISION
void Board::updateRows()
{
	int counter = 0;
	std::experimental::erase_if(m_rects, [&counter](const auto& row)
	{ 
		if (std::all_of(row.begin(), row.end(), [](const auto& rec)
			{
				if (rec.get())
					return true;
				return false;
			}))
		{
			counter++;

			return true;
		} 
		return false;
	});

	m_erasedLines += counter;
	m_currentScore = m_boardScore;
	m_boardScore += counter * 5;

	if (m_currentScore < m_boardScore)
		m_breakRow.play();

	for (size_t i = 0; i < counter; i++)
		m_rects.insert(m_rects.begin(),
			std::vector <std::unique_ptr<sf::RectangleShape>>(Cols));
}
