#include "VEdge.h"

VEdge::VEdge(glm::vec2 t_midpoint, std::pair<int, int> t_polygonNumbers, std::pair<glm::vec2, glm::vec2> t_polyPos) :
	m_midpoint{ t_midpoint },
	m_polygonIds{ t_polygonNumbers },
	polyPos{ t_polyPos }
{
	m_finished = false;
	m_startpoint = Utility::setInvalidVector();
	m_endpoint = Utility::setInvalidVector();
}

void VEdge::render(SDL_Renderer* t_renderer)
{
	// what i want to do
	//--------------------------------
	// draw midpoint , startpoint, endpoint and line between

	if (!Utility::isInvalidVector(m_startpoint))
	{
		////1-2
		//SDL_RenderDrawLine(t_renderer);
		////2-3
		//SDL_RenderDrawLine(t_renderer);
		////3-4
		//SDL_RenderDrawLine(t_renderer);
		////4-5
		//SDL_RenderDrawLine(t_renderer);
		////5-6
		//SDL_RenderDrawLine(t_renderer);
		////centre
		//SDL_RenderDrawLine(t_renderer, );
	}



	bool testing = false;

	glm::vec2 vec1 = m_midpoint - polyPos.first;
	glm::vec2 vec2 = m_midpoint - polyPos.second;
	glm::vec2 mid = (polyPos.first + polyPos.second) / 2.0f;

	float angle = atan2(polyPos.second.y - polyPos.first.y, polyPos.second.x - polyPos.first.x);
	float degrees = angle * (180 / M_PI);
	//angle /= 2;
	glm::vec2 startInf = glm::vec2((cos(angle)), (sin(angle)));
	glm::vec2 endInf = glm::vec2(1000 * (cos(-angle)), 1000 * (sin(-angle)));
	startInf *= 1000;
	Utility::restrictVectorToBounds(startInf);
	Utility::restrictVectorToBounds(endInf);




	SDL_SetRenderDrawColor(t_renderer, 255, 0, 0, 255);
	if (!Utility::isInvalidVector(m_startpoint) && !Utility::isInvalidVector(m_endpoint))
	{
		SDL_SetRenderDrawColor(t_renderer, 0, 0, 255, 255);
		SDL_RenderDrawLine(t_renderer, m_endpoint.x - 5, m_endpoint.y, m_endpoint.x + 5, m_endpoint.y);
		SDL_RenderDrawLine(t_renderer, m_endpoint.x, m_endpoint.y - 5, m_endpoint.x, m_endpoint.y + 5);
		SDL_SetRenderDrawColor(t_renderer, 255, 0, 0, 255);
		SDL_RenderDrawLine(t_renderer, m_startpoint.x, m_startpoint.y, m_endpoint.x, m_endpoint.y);
	}
	else if (Utility::isInvalidVector(m_endpoint) && !Utility::isInvalidVector(m_startpoint))
	{
		//SDL_RenderDrawLine(t_renderer, m_startpoint.x, m_startpoint.y, m_midpoint.x, m_midpoint.y);
		SDL_SetRenderDrawColor(t_renderer, 0, 255, 0, 255);
		SDL_RenderDrawLine(t_renderer, m_startpoint.x - 5, m_startpoint.y, m_startpoint.x + 5, m_startpoint.y);
		SDL_RenderDrawLine(t_renderer, m_startpoint.x, m_startpoint.y - 5, m_startpoint.x, m_startpoint.y + 5);
		SDL_SetRenderDrawColor(t_renderer, 255, 0, 0, 255);

	}
	 
	{
		SDL_RenderDrawLine(t_renderer, m_midpoint.x - 5, m_midpoint.y, m_midpoint.x + 5, m_midpoint.y);
		SDL_RenderDrawLine(t_renderer, m_midpoint.x, m_midpoint.y - 5, m_midpoint.x, m_midpoint.y + 5);
		SDL_SetRenderDrawColor(t_renderer, 0, 255, 255, 255);

		if (testing)
		{

			SDL_RenderDrawLine(t_renderer, m_midpoint.x, m_midpoint.y, mid.x, mid.y);
			SDL_RenderDrawLine(t_renderer, m_midpoint.x, m_midpoint.y, m_midpoint.x - mid.x, m_midpoint.y - mid.y);
		}
		else
		{

			//SDL_RenderDrawLine(t_renderer, m_midpoint.x, m_midpoint.y, polyPos.first.x, polyPos.first.y);
			//SDL_RenderDrawLine(t_renderer, m_midpoint.x, m_midpoint.y, polyPos.second.x, polyPos.second.y);
		}
	}
	SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
}

void VEdge::setPoint(glm::vec2 t_point)
{
	if (Utility::isInvalidVector(m_startpoint))
	{
		m_startpoint = t_point;
	}
	else if (Utility::isInvalidVector(m_endpoint))
	{
		if (!Utility::areEquivalent(t_point.x, m_startpoint.x) && !Utility::areEquivalent(t_point.y, m_startpoint.y))
		{




			m_endpoint = t_point;
			m_finished = true;
		}
	}
}

void VEdge::setStartAndEndPoint(glm::vec2 t_startpoint, glm::vec2 t_endpoint)
{
	setStartPoint(t_startpoint);
	setEndPoint(t_endpoint);
}

void VEdge::setStartPoint(glm::vec2 t_startpoint)
{
	m_startpoint = t_startpoint;
}

void VEdge::setEndPoint(glm::vec2 t_endpoint)
{
	m_endpoint = t_endpoint;
}

std::pair<int, int> VEdge::getPolygonIds()
{
	return m_polygonIds;
}

bool VEdge::getFinished()
{
	return m_finished;
}

glm::vec2 VEdge::getStartPoint()
{
	return m_startpoint;
}

glm::vec2 VEdge::getEndPoint()
{
	return m_endpoint;
}

glm::vec2 VEdge::getMidPoint()
{
	return m_midpoint;
}

void VEdge::operator=(const VEdge& t_otherEdge)
{
	m_startpoint = t_otherEdge.m_startpoint;
	m_endpoint = t_otherEdge.m_endpoint;
	m_midpoint = t_otherEdge.m_midpoint;
	m_polygonIds = t_otherEdge.m_polygonIds;
	polyPos = t_otherEdge.polyPos;
	m_finished = t_otherEdge.m_finished;
}

bool VEdge::areSame(float a, float b)
{
	if (a + 20 >= b ||
		a - 20 <= b)
	{
		return true;
	}
	return false;

}
