#include "L.h"


// L CLASS

L::L()
{
	for (size_t i = 0; i < size; i++)
		m_rects[i].setPosition
		(sf::Vector2f(leftGap + 4.5 * rectSize, ceiling + 1.5 * rectSize));

	m_rects[0].setOrigin(sf::Vector2f(1.5 * rectSize, 1.5*rectSize));
	m_rects[1].setOrigin(sf::Vector2f(1.5*rectSize, 0.5*rectSize));
	m_rects[2].setOrigin(sf::Vector2f(0.5*rectSize, 0.5*rectSize));
	m_rects[3].setOrigin(sf::Vector2f(-0.5* rectSize, 0.5*rectSize));
}



L::~L()
{
}
