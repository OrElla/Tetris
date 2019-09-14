#include "O.h"


// O CLASS

O::O()
{
	for (size_t i = 0; i < size; i++)
		m_rects[i].setPosition
		(sf::Vector2f(leftGap + 5 * rectSize, ceiling + 1 * rectSize));

	m_rects[0].setOrigin(sf::Vector2f(1 * rectSize, 1 * rectSize));
	m_rects[1].setOrigin(sf::Vector2f(0, 1 * rectSize));
	m_rects[2].setOrigin(sf::Vector2f(1 * rectSize, 0));
	m_rects[3].setOrigin(sf::Vector2f(0, 0));
}


O::~O()
{
}
