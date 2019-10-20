#include "Voronoi.h"

Voronoi::Voronoi():
	NUMBER_OF_POINTS{3}
{
	m_points.push_back(VPoint(100, SCREEN_SIZE::HEIGHT - 100));
	m_points.push_back(VPoint(SCREEN_SIZE::WIDTH - 100, SCREEN_SIZE::HEIGHT - 100));
	m_points.push_back(VPoint(SCREEN_SIZE::WIDTH / 2, 100));
}

void Voronoi::render(sf::RenderWindow& t_window)
{
	m_sweepLine.render(t_window);
	for (int index = 0; index < m_parabolas.size(); index++)
	{
		m_parabolas[index].render(t_window);
	}
	for (int index = 0; index < m_points.size(); index++)
	{
		m_points[index].renderPoint(t_window);
	}
}

void Voronoi::update(sf::Time t_deltaTime)
{
	m_sweepLine.update();
	for (int index = 0; index < m_points.size(); index++)
	{
		if(!m_points[index].hasTouchedSweepLine() && m_points[index].collisionDetection(m_sweepLine.getYPos()))
		{
			m_parabolas.push_back(VParabola(m_points[index], m_sweepLine.getYPos()));
			std::cout << "Added new Parabola" << std::endl;
		}
	}
	for (int index = 0; index < m_parabolas.size(); index++)
	{
		m_parabolas[index].update(m_sweepLine.getYPos());
	}
}

void Voronoi::handleKeyboardInput(sf::Event t_keyboardEvent)
{
}
