
#include "Shape.h"
#include "Board.h"

//CONSTRUCOR - DEFINES THE SHAPES
Shape::Shape()
{
	sf::Color color = getRandColor();
	for (size_t i = 0; i < size; i++)
	{
		m_rects.push_back
		(sf::RectangleShape(sf::Vector2f(rectSize, rectSize)));
		m_rects[i].setFillColor(color);
	}
}
//DISTRUCTOR
Shape::~Shape()
{
}

//ROTATING THE SHAPES
void Shape::rotateShape(const Board & board)
{
	for (int i = 0; i < size; i++)
		m_rects[i].rotate(90);
	if (canRotate(board))
		for (int i = 0; i < size; i++)
			m_rects[i].rotate(-90);
}

//MOVING THE SHAPES
void Shape::move(Direction direction, const Board & board)
{
	switch (direction)
	{
	case DOWN:
	{
		for (size_t i = 0; i < size; i++)
			m_rects[i].move(sf::Vector2f(0, rectSize));
		break;
	}
	case RIGHT:
	{
		if (canMove(board, RIGHT))
			for (size_t i = 0; i < size; i++)
				m_rects[i].move(sf::Vector2f(rectSize, 0));
		break;
	}
	case LEFT:
	{
		if (canMove(board, LEFT))
			for (size_t i = 0; i < size; i++)
				m_rects[i].move(sf::Vector2f(-rectSize, 0));
		break;
	}
	default:
		break;
	}
}

//DRAWING THE SHAPES
void Shape::draw(sf::RenderWindow & window)
{
	for (size_t i = 0; i < size; i++)
		window.draw(m_rects[i]);
}

//GET POSITION OF THE SHAPE
const std::vector<sf::Vector2f> Shape::getPos()
{
	std::vector<sf::Vector2f> positions;
	for (size_t i = 0; i < size; i++)
		positions.push_back(m_rects[i].getPosition());
	return positions;
}

//GET RECTS
const std::vector<sf::RectangleShape> Shape::getRects()
{
	return m_rects;
}

//CHECKS IF THE GAME IS OVER
bool Shape::isOver(bool collision)
{
	return collision && std::any_of(m_rects.begin(),m_rects.end(),
		[](const sf::RectangleShape & rec) 
	{
		return rec.getGlobalBounds().top == ceiling
			|| rec.getGlobalBounds().top == ceiling + rectSize;
	});
}


//CHECKS IF THE SHAPE CAN ROTATE
bool Shape::canRotate(const Board & board)
{
	if (std::any_of(m_rects.begin(), m_rects.end(),
		[&board](sf::RectangleShape rec)
	{
		int s = rec.getGlobalBounds().top;
		int t = rec.getGlobalBounds().left;
		int row = (rec.getGlobalBounds().top - ceiling) / rectSize;
		int col = (rec.getGlobalBounds().left - leftGap) / rectSize;
		if (rec.getGlobalBounds().left > leftGap + BoardWidth - rectSize ||
			rec.getGlobalBounds().left < leftGap)
			return true;

		else if (board.getRect(row, col))
			return true;
		return false;
	}))
		return true;
	return false;
}

//GETIING COLOR FOR THE SHAPE
sf::Color Shape::getRandColor()
{
	int colorNumber = rand() % 5;
	switch (colorNumber)
	{
	case 0:
		return sf::Color::Blue;
	case 1:
		return sf::Color::Green;
	case 2:
		return sf::Color::Red;
	case 3:
		return sf::Color::Yellow;
	case 4:
		return sf::Color(250, 0, 245);
	}
}

//CHECKS IF THE SHAPE CAN MOVE
bool Shape::canMove(const Board& board, Direction direction)
{
	if (std::any_of(m_rects.begin(), m_rects.end(),
		[&board, &direction](sf::RectangleShape rec)
	{
		int s = rec.getGlobalBounds().top;
		int t = rec.getGlobalBounds().left;
		int row = (rec.getGlobalBounds().top - ceiling) / rectSize;
		int col = (rec.getGlobalBounds().left - leftGap) / rectSize;
		if (direction == RIGHT)
		{
			if (rec.getGlobalBounds().left >= leftGap + BoardWidth - rectSize)
				return true;
			else if (board.getRect(row, col + 1))
				return true;
		}
		else if (rec.getGlobalBounds().left <= leftGap)
			return true;
		else if (board.getRect(row, col - 1))
			return true;
		return false;
	}))
		return false;
	return true;
}

//DRAWING THE NEXT SHAPE
void Shape::drawNext(sf::RenderWindow & window)
{

	for (size_t i = 0; i < size; i++)
	{
		m_rects[i].setSize(sf::Vector2f(rectSize, rectSize));
		m_rects[i].setPosition
		(sf::Vector2f(leftGap + 12.3 * rectSize, ceiling + 6.3 * rectSize));
		m_rects[i].setOutlineColor(sf::Color::Black);
		m_rects[i].setOutlineThickness(1);
		window.draw(m_rects[i]);
	}
}




