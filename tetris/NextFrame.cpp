#include "NextFrame.h"



NextFrame::NextFrame()
{
	m_rects[0].setOrigin(sf::Vector2f(-1.5 * rectSize, 0.5*rectSize));
	m_rects[1].setOrigin(sf::Vector2f(-1.5*rectSize, -0.5*rectSize));
	m_rects[2].setOrigin(sf::Vector2f(-0.5*rectSize, -0.5*rectSize));
	m_rects[3].setOrigin(sf::Vector2f(0.5* rectSize, -0.5*rectSize));

}


NextFrame::~NextFrame()
{
}
