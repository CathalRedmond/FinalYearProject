#include "VEdge.h"

VEdge::VEdge(VPoint one, VPoint two):
	isFinished{false},
	isStartPointFinished{false},
	isEndPointFinished{ false },
	m_parabolaOne{one},
	m_parabolaTwo{two}
	
{
	m_startPoint = glm::vec2(0, 0);
	m_endPoint = glm::vec2(0, 0);
}

bool VEdge::collisionDetection(VEdge t_otherLine)
{
	glm::vec2 otherStartPoint = t_otherLine.getStartPoint();
	glm::vec2 otherEndPoint = t_otherLine.getEndPoint();
	
	float denominator = ((t_otherLine.m_endPoint.y - t_otherLine.m_startPoint.y) * (m_endPoint.y - m_startPoint.y)) -
						((t_otherLine.m_endPoint.x - t_otherLine.m_startPoint.x) * (m_endPoint.x - m_startPoint.x));

	float nume_a = ((t_otherLine.m_endPoint.x - t_otherLine.m_startPoint.x) * (m_startPoint.y - t_otherLine.m_startPoint.y)) -
				   ((t_otherLine.m_endPoint.y - t_otherLine.m_startPoint.y) * (m_startPoint.x - t_otherLine.m_startPoint.x));
	float nume_b = ((m_endPoint.x - m_startPoint.x) * (m_startPoint.y - t_otherLine.m_startPoint.y)) -
				   ((m_endPoint.y - m_startPoint.y) * (m_startPoint.x - t_otherLine.m_startPoint.x));

	if (denominator == 0.0f)
	{
		if (nume_a == 0.0f && nume_b == 0.0f)
		{
			return true;
		}
		return false;
	}

	float ua = nume_a / denominator;
	float ub = nume_b / denominator;

	if (ua >= 0.0f && ua <= 1.0f && ub >= 0.0f && ub <= 1.0f)
	{
		glm::vec2 intersect = glm::vec2(m_startPoint.x + ua * (m_endPoint.x - m_startPoint.x),
			m_startPoint.y + ua * (m_endPoint.y - m_startPoint.y));

		if (glm::distance(m_startPoint, intersect) < glm::distance(m_endPoint, intersect))
		{
			isStartPointFinished = true;
		}
		else
		{
			isEndPointFinished = true;
		}

		if (glm::distance(t_otherLine.m_startPoint, intersect) < glm::distance(t_otherLine.m_endPoint, intersect))
		{
			t_otherLine.isStartPointFinished = true;
		}
		else
		{
			t_otherLine.isEndPointFinished = true;
		}
		return true;
	}
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

void VEdge::updateStartAndEndpoints(glm::vec2 t_startpoint, glm::vec2 t_endpoint, bool yes)
{

			m_startPoint = t_startpoint;
	
			m_endPoint = t_endpoint;


}

void VEdge::render(SDL_Renderer* t_renderer, glm::vec3 t_colourOfEdge)
{
	SDL_SetRenderDrawColor(t_renderer, t_colourOfEdge.x, t_colourOfEdge.y, t_colourOfEdge.z, 255);
	SDL_RenderDrawLine(t_renderer, m_startPoint.x, m_startPoint.y,/* m_midPoint.x, m_midPoint.y);
	SDL_RenderDrawLine(t_renderer, m_midPoint.x, m_midPoint.y,*/ m_endPoint.x, m_endPoint.y);
	SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
}

void VEdge::update()
{
	if (isFinished)
	{
		isStartPointFinished = true;
		isEndPointFinished = true;
	}
	if (isStartPointFinished && isEndPointFinished)
	{
		isFinished = true;
	}

	distanceFromOrigin = glm::distance(m_midPoint, m_parabolaOne.getPosition());
	if (distanceFromOrigin > glm::distance(m_parabolaOne.getPosition(), m_parabolaTwo.getPosition()) / 2.0f);
	{
		isFinished = true;
	}

}

void VEdge::lineAutoFinish(bool isWhole)
{
	isFinished = true;
	float halfScreenDiagonal = sqrt(std::pow(SCREEN_SIZE::WIDTH, 2) + std::pow(SCREEN_SIZE::HEIGHT,2)) / 2.0f;
	// x = 1/2diag * sinangle
	// y = 1/2diag * cosangle
	// minus for start 
	// plus for end


	//right
	if (m_startPoint.x > SCREEN_SIZE::WIDTH / 2.0f)
	{
		float dist = SCREEN_SIZE::WIDTH - m_startPoint.x;
		m_startPoint.x += dist;
	}
	//left
	else
	{
		float dist = 0 - m_startPoint.x;
		m_startPoint.x += dist;
	}
	 // bottom
	if (m_startPoint.y > SCREEN_SIZE::HEIGHT / 2.0f)
	{
		float dist = SCREEN_SIZE::HEIGHT - m_startPoint.y;
		m_startPoint.y += dist;
	}
	//top
	else
	{
		float dist = 0 - m_startPoint.y;
		m_startPoint.y += dist;
	}

	if (m_endPoint.x > SCREEN_SIZE::WIDTH / 2.0f)
	{
		float dist = SCREEN_SIZE::WIDTH - m_endPoint.x;
		m_endPoint.x += dist;
	}
	//left
	else
	{
		float dist = 0 - m_endPoint.x;
		m_endPoint.x += dist;
	}
	// bottom
	if (m_endPoint.y > SCREEN_SIZE::HEIGHT / 2.0f)
	{
		float dist = SCREEN_SIZE::HEIGHT - m_endPoint.y;
		m_endPoint.y += dist;
	}
	//top
	else
	{
		float dist = 0 - m_endPoint.y;
		m_endPoint.y += dist;
	}

}

void VEdge::init()
{
	float sX = (m_parabolaOne.getPosition().x * std::cos(M_PI / 2)) - (m_parabolaOne.getPosition().y * std::sin(M_PI / 2));
	float sY = (m_parabolaOne.getPosition().y * std::cos(M_PI / 2)) + (m_parabolaOne.getPosition().x * std::sin(M_PI / 2));

	float eX = (m_parabolaTwo.getPosition().x * std::cos(M_PI / 2)) - (m_parabolaTwo.getPosition().y * std::sin(M_PI / 2));
	float eY = (m_parabolaTwo.getPosition().y * std::cos(M_PI / 2)) + (m_parabolaTwo.getPosition().x * std::sin(M_PI / 2));

	m_startPoint = glm::vec2(sX, sY);

	m_endPoint = glm::vec2(eX, eY);
}
