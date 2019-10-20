#include "VParabola.h"

VParabola::VParabola(VPoint point, float sweepLineY)
	:
	m_point{point},
	m_sweepLineYPos{sweepLineY}
{
	for (int index = 0; index < SCREEN_SIZE::WIDTH; index += 10)
	{
		m_parabolaPoints.push_back(sf::Vector2f(index, getYPosOfParabola(index)));
	}
}

void VParabola::update(float sweepLineY)
{
	m_sweepLineYPos = sweepLineY;
	updateParabolaPoints();
}

void VParabola::render(sf::RenderWindow& t_window)
{
	sf::CircleShape circle(2.5);
	circle.setFillColor(sf::Color::Green);
	for (int index = 0; index < m_parabolaPoints.size(); index++)
	{
		circle.setPosition(m_parabolaPoints[index]);
		t_window.draw(circle);
	}
}

void VParabola::updateParabolaPoints()
{
	float xPos = 0;
	for (int index = 0; index < m_parabolaPoints.size(); index++)
	{
		m_parabolaPoints[index].y = getYPosOfParabola(xPos);
		xPos += 10;
	}
}

float VParabola::getYPosOfParabola(float xPos)
{
	return (std::pow(xPos - m_point.x(), 2.0f) / (2.0f * (m_point.y() - m_sweepLineYPos))) + ((m_point.y() + m_sweepLineYPos) / 2.0f);
}
