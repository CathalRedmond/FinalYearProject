#include "VParabola.h"

VParabola::VParabola(VPoint t_parabolaPoint, float t_sweepLineYPos)
	:
	m_point{t_parabolaPoint},
	m_sweepLineYPos{t_sweepLineYPos}
{
	for (int index = 0; index < SCREEN_SIZE::WIDTH; index += 10)
	{
		m_parabolaPoints.push_back(glm::vec2(index, getYPosOfParabola(index)));
	}
}

void VParabola::update(float t_sweepLineYPos)
{
	m_sweepLineYPos = t_sweepLineYPos;
	updateParabolaPoints();
}

void VParabola::render(SDL_Renderer* t_renderer)
{
	SDL_SetRenderDrawColor(t_renderer, 0, 255, 0, 255);
	for (int index = 0; index < m_parabolaPoints.size(); index++)
	{
		if (index == m_parabolaPoints.size() - 1)
		{
			SDL_RenderDrawLine(t_renderer, m_parabolaPoints[index].x, m_parabolaPoints[index].y, m_parabolaPoints[index].x, m_parabolaPoints[index].y);
		}
		else
		{
			SDL_RenderDrawLine(t_renderer, m_parabolaPoints[index].x, m_parabolaPoints[index].y, m_parabolaPoints[index + 1].x, m_parabolaPoints[index + 1].y);
		}
	}
	SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
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

float VParabola::getYPosOfParabola(float t_xPos)
{
	return (std::pow(t_xPos - m_point.getPosition().x, 2.0f) / (2.0f * (m_point.getPosition().y - m_sweepLineYPos))) + ((m_point.getPosition().y + m_sweepLineYPos) / 2.0f);
}
