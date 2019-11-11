#include "Voronoi.h"

Voronoi::Voronoi():
	NUMBER_OF_POINTS{3}
{
	//float r3 = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
	for (int index = 0; index < 500; index++)
	{
		float x = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / SCREEN_SIZE::WIDTH));
		float y = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / SCREEN_SIZE::HEIGHT));
		m_points.push_back(VPoint(glm::vec2(x,y)));
	}
	m_points.push_back(VPoint(glm::vec2(100, SCREEN_SIZE::HEIGHT - 100)));
	m_points.push_back(VPoint(glm::vec2(SCREEN_SIZE::WIDTH - 100, SCREEN_SIZE::HEIGHT - 100)));
	m_points.push_back(VPoint(glm::vec2(SCREEN_SIZE::WIDTH / 2, 100)));
}

void Voronoi::render(SDL_Renderer* t_renderer)
{
	m_sweepLine.render(t_renderer);
	for (int index = 0; index < m_parabolas.size(); index++)
	{
		m_parabolas[index].render(t_renderer);
	}
	for (int index = 0; index < m_points.size(); index++)
	{
		m_points[index].render(t_renderer);
	}
}

void Voronoi::update()
{
	m_sweepLine.update();
	for (int index = 0; index < m_points.size(); index++)
	{
		if (!m_points[index].hasTouchedSweepLine() && m_points[index].collisionDetection(m_sweepLine.getYPos()))
		{
			m_parabolas.push_back(VParabola(m_points[index], m_sweepLine.getYPos()));
		}
	}
	for (int index = 0; index < m_parabolas.size(); index++)
	{
		m_parabolas[index].update(m_sweepLine.getYPos());
	}
}

void Voronoi::handleKeyBoardInput(SDL_Event t_keyboardEvent)
{
}
