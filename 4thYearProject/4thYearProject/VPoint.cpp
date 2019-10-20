#include "VPoint.h"

VPoint::VPoint(float t_xPos, float t_yPos):
	m_xPos{t_xPos},
	m_yPos{t_yPos},
	m_hasTouchedSweepLine{false}
{
}

VPoint::VPoint():
	m_xPos{0},
	m_yPos{0},
	m_hasTouchedSweepLine{false}
{
}

float VPoint::x()
{
	return m_xPos;
}

float VPoint::y()
{
	return m_yPos;
}

bool VPoint::collisionDetection(float t_sweepLineYPos)
{
	if (t_sweepLineYPos > m_yPos)
	{
		m_hasTouchedSweepLine = true;
	}
	return m_hasTouchedSweepLine;
}

bool VPoint::hasTouchedSweepLine()
{
	return m_hasTouchedSweepLine;
}

void VPoint::renderPoint(sf::RenderWindow& t_window)
{
	sf::CircleShape circle(5);
	circle.setFillColor(sf::Color::Red);
	circle.setPosition(sf::Vector2f(m_xPos, m_yPos));
	t_window.draw(circle);
}
