#include "VSweepLine.h"

VSweepLine::VSweepLine():
	m_yPos{-5.0f}
{
}

void VSweepLine::update()
{
	m_yPos++;
}

void VSweepLine::render(sf::RenderWindow& t_window)
{
	sf::RectangleShape shape(sf::Vector2f(SCREEN_SIZE::WIDTH, 1));
	shape.setFillColor(sf::Color::Magenta);
	shape.setPosition(sf::Vector2f(0, m_yPos));
	t_window.draw(shape);
}

float VSweepLine::getYPos()
{
	return m_yPos;
}
