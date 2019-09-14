#include "I.h"


// I CLASS
I::I()
{
	for (size_t i = 0; i < size ; i++)
		m_rects[i].setPosition
		(sf::Vector2f(leftGap + 5 * rectSize, ceiling+2 * rectSize));

	m_rects[0].setOrigin(sf::Vector2f(2 * rectSize, rectSize));
	m_rects[1].setOrigin(sf::Vector2f(rectSize, rectSize));
	m_rects[2].setOrigin(sf::Vector2f(0, rectSize));
	m_rects[3].setOrigin(sf::Vector2f(-1* rectSize, rectSize));
}


I::~I()
{
}

