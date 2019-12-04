#include "VEdge.h"

VEdge::VEdge()
{
	m_startPoint = glm::vec2(0, 0);
	m_endPoint = glm::vec2(0, 0);
}

bool VEdge::collisionDetection(VEdge t_otherLine)
{
	glm::vec2 otherStartPoint = t_otherLine.getStartPoint();
	glm::vec2 otherEndPoint = t_otherLine.getEndPoint();
	
	

	return false;
}


glm::vec2 VEdge::getStartPoint()
{
	return m_startPoint;
}

glm::vec2 VEdge::getEndPoint()
{
	return m_endPoint;
}

void VEdge::updateStartAndEndpoints(glm::vec2 t_startpoint, glm::vec2 t_endpoint)
{
	m_startPoint = t_startpoint;
	m_endPoint = t_endpoint;
}

void VEdge::render(SDL_Renderer* t_renderer)
{
	SDL_SetRenderDrawColor(t_renderer, 255, 0, 0, 255);
	SDL_RenderDrawLine(t_renderer, m_startPoint.x, m_startPoint.y, m_endPoint.x, m_endPoint.y);
	SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
}
