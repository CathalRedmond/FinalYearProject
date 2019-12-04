#include "Voronoi.h"

Voronoi::Voronoi():
	NUMBER_OF_POINTS{3},
	topOfScreen{glm::vec3(0,0,-1)}
{
	//float r3 = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
	//for (int index = 0; index < 10; index++)
	//{
	//	float x = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / SCREEN_SIZE::WIDTH));
	//	float y = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / SCREEN_SIZE::HEIGHT));
	//	m_points.push_back(VPoint(glm::vec2(x,y)));
	//}
	//m_points.push_back(VPoint(glm::vec2(100, SCREEN_SIZE::HEIGHT - 100)));
	//m_points.push_back(VPoint(glm::vec2(SCREEN_SIZE::WIDTH - 100, SCREEN_SIZE::HEIGHT - 100)));
	m_points.push_back(VPoint(glm::vec2(SCREEN_SIZE::WIDTH / 2, 100)));
	m_points.push_back(VPoint(glm::vec2(SCREEN_SIZE::WIDTH / 2, 400)));

	m_points.push_back(VPoint(glm::vec2(SCREEN_SIZE::WIDTH / 2, 500)));

	m_points.push_back(VPoint(glm::vec2(SCREEN_SIZE::WIDTH / 3, 200)));
	m_points.push_back(VPoint(glm::vec2(SCREEN_SIZE::WIDTH / 4, 300)));
	m_points.push_back(VPoint(glm::vec2(SCREEN_SIZE::WIDTH / 7, 450)));




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
			float closestDistance = std::numeric_limits<float>::max();
			int indexOfClosest = -1;
			for (int index2 = 0; index2 < m_parabolas.size(); index2++)
			{
				if (m_parabolas[index2].isValidPoint(glm::vec2(m_points[index].getPosition().x, m_parabolas[index2].getYPosOfParabola(m_points[index].getPosition().x))))
				{
					if (abs(m_points[index].getPosition().y - m_parabolas[index2].getPoint().getPosition().y))
					{
						closestDistance = abs(m_points[index].getPosition().y - m_parabolas[index2].getPoint().getPosition().y);
						indexOfClosest = index2;
					}
				}
			}
			m_parabolas.push_back(VParabola(m_points[index], m_sweepLine.getYPos()));

			if (indexOfClosest != -1)
			{
				m_parabolas[m_parabolas.size()-1].setTouchingParabola(&m_parabolas[indexOfClosest]);
				m_parabolas[indexOfClosest].setTouchingParabola(&m_parabolas[m_parabolas.size() - 1]);
			}
			else
			{
				m_parabolas[m_parabolas.size() - 1].setTouchingParabola(&topOfScreen);
			}
		}
	}
	for (int index = 0; index < m_parabolas.size(); index++)
	{
		if (index == 1)
		{
			std::string stopHere = "HERE";
		}
		m_parabolas[index].update(m_sweepLine.getYPos());
	}
}

void Voronoi::handleKeyBoardInput(SDL_Event t_keyboardEvent)
{
}
