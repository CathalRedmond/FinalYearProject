#include "VPoint.h"

VPoint::VPoint(glm::vec2 t_position)
	:
	m_position{ t_position },
	m_hasTouchedSweepLine{ false }
{
}

glm::vec2 VPoint::getPosition()
{
	return m_position;
}

bool VPoint::collisionDetection(float t_sweepLineYPos)
{
	if (t_sweepLineYPos > m_position.y)
	{
		m_hasTouchedSweepLine = true;
	}
	return m_hasTouchedSweepLine;
}

bool VPoint::hasTouchedSweepLine()
{
	return m_hasTouchedSweepLine;
}

void VPoint::render(SDL_Renderer* t_renderer)
{
	SDL_SetRenderDrawColor(t_renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(t_renderer, m_position.x, m_position.y, m_position.x + 2, m_position.y);
	//SDL_RenderDrawLine(t_renderer, m_position.x + 2, m_position.y, m_position.x + 2, m_position.y + 2);
	//SDL_RenderDrawLine(t_renderer, m_position.x + 2, m_position.y + 2, m_position.x, m_position.y + 2);
	//SDL_RenderDrawLine(t_renderer, m_position.x, m_position.y + 2, m_position.x, m_position.y);
	SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
}
