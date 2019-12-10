#include "VParabola.h"

bool sortStartAndEndpoints(glm::vec2 firstPoint, glm::vec2 secondPoint)
{
	return firstPoint.x < secondPoint.x;
}

VParabola::VParabola(VPoint t_parabolaPoint, float t_sweepLineYPos)
	:
	m_point{t_parabolaPoint},
	m_sweepLineYPos{t_sweepLineYPos}
{
	for (int index = 0; index < SCREEN_SIZE::WIDTH; index += 5)
	{
		m_parabolaPoints.push_back(glm::vec2(index, getYPosOfParabola(index)));
	}
}

VParabola::VParabola(glm::vec3 quadraticValues):
	m_point{glm::vec2(0,0)},
	m_sweepLineYPos{ -1 }
{
	m_quadraticValues = quadraticValues;
}

void VParabola::update(float t_sweepLineYPos)
{
	m_sweepLineYPos = t_sweepLineYPos;
	updateParabolaPoints();
	updateQuadraticValues();
	updateCollisionPoints();
	updateEdges();
}

void VParabola::render(SDL_Renderer* t_renderer, glm::vec3 t_colourOfParabola)
{
	SDL_SetRenderDrawColor(t_renderer, t_colourOfParabola.x, t_colourOfParabola.y, t_colourOfParabola.z, 255);
	for (int index = 0; index < m_parabolaPoints.size(); index++)
	{
		if (isValidPoint(m_parabolaPoints[index]) && m_parabolaPoints[index].y < m_sweepLineYPos)
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
	}
	for (int index = 0; index < m_edge.size(); index++)
	{
		if (m_edge[index].getEndPoint().y < m_sweepLineYPos && m_edge[index].getStartPoint().y < m_sweepLineYPos)
		{
			m_edge[index].render(t_renderer);
		}
	}
	SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
}

void VParabola::updateCollisionPoints()
{
	m_startpoints.clear();
	m_endpoints.clear();

	findPointsOfCollision();
}

void VParabola::setTouchingParabola(VParabola* t_otherParabola)
{
	touchingParabolas.push_back(t_otherParabola);
	m_edge.push_back(VEdge(m_point, t_otherParabola->m_point));
	//touchingParabolas[touchingParabolas.size() - 1]->m_edge.push_back(VEdge(m_point, t_otherParabola->m_point));
	
}

void VParabola::updateParabolaPoints()
{
	float xPos = 0;
	for (int index = 0; index < m_parabolaPoints.size(); index++)
	{
		m_parabolaPoints[index].y = getYPosOfParabola(xPos);
		xPos += 5;
	}
}

float VParabola::getYPosOfParabola(float t_xPos)
{
	float y = (std::pow(t_xPos - m_point.getPosition().x, 2.0f) / (2.0f * (m_point.getPosition().y - m_sweepLineYPos))) + ((m_point.getPosition().y + m_sweepLineYPos) / 2.0f);

	return y;
}

VPoint VParabola::getPoint()
{
	return m_point;
}

bool VParabola::collisionDetection(VParabola t_otherParabola)
{
	updateQuadraticValues();


	t_otherParabola.updateQuadraticValues();

	std::pair<glm::vec2, glm::vec2> collisionPoints = getPointsOfCollision(t_otherParabola);
	if (collisionPoints.first.x != NULL && collisionPoints.second.x != NULL)
	{
		if (collisionPoints.first.y + 20 >= t_otherParabola.getYPosOfParabola(collisionPoints.first.x) || 
			collisionPoints.first.y - 20 <= t_otherParabola.getYPosOfParabola(collisionPoints.first.x))
		{
			if (collisionPoints.second.y + 20 >= t_otherParabola.getYPosOfParabola(collisionPoints.second.x) ||
				collisionPoints.second.y - 20 <= t_otherParabola.getYPosOfParabola(collisionPoints.second.x))
			{
				return true;
			}
		}
	}
	return false;
}

bool VParabola::isValidPoint(glm::vec2 t_point)
{
	bool isValidPoint = false;
	if (t_point.x <= SCREEN_SIZE::WIDTH && t_point.x >= 0 && t_point.y <= SCREEN_SIZE::HEIGHT && t_point.y >= 0)
	{
		for (int index = 0; index < m_startpoints.size(); index++)
		{
			if (isPointBetweenTwoPoints(t_point, m_startpoints[index], m_endpoints[index]))
			{
				isValidPoint = true;
			}
		}
	}
	return isValidPoint;
}

bool VParabola::isPointBetweenTwoPoints(glm::vec2 t_point,glm::vec2 startpoint, glm::vec2 endpoint)
{
	if (t_point.x >= startpoint.x && t_point.x <= endpoint.x)
	{
		if (startpoint.y == endpoint.y ||
		   (startpoint.x < m_point.getPosition().x && endpoint.x > m_point.getPosition().x))
		{
			if (startpoint.y != endpoint.y)
			{
				//left
				if (t_point.x < m_point.getPosition().x)
				{
					return t_point.y > startpoint.y;
				}
				else
				{
					return t_point.y > endpoint.y;

				}
			}
			else
			{
				return t_point.y > startpoint.y&& t_point.y > endpoint.y;
			}
		}
		else
		{
			return startpoint.y < endpoint.y ? t_point.y >= startpoint.y && t_point.y <= endpoint.y :
											   t_point.y <= startpoint.y && t_point.y >= endpoint.y;
		}
	}
	return false;
}

void VParabola::findPointsOfCollision()
{
	std::vector<glm::vec2> startAndEndpoints;
	for (int index = 0; index < touchingParabolas.size(); index++)
	{
		std::pair<glm::vec2, glm::vec2> pointsOfCollision = getPointsOfCollision((*touchingParabolas[index]));
		if (pointsOfCollision.first.x != NULL && pointsOfCollision.second.x != NULL)
		{
			if ((*touchingParabolas[index]).m_quadraticValues.z == -1)
			{
				startAndEndpoints.push_back(glm::vec2(pointsOfCollision.first.x, -1));
				startAndEndpoints.push_back(glm::vec2(pointsOfCollision.second.x, -1));
			}
			else
			{
				startAndEndpoints.push_back(pointsOfCollision.first);
				startAndEndpoints.push_back(pointsOfCollision.second);
			}
		}
		continue;
	}
	std::sort(startAndEndpoints.begin(), startAndEndpoints.end(), sortStartAndEndpoints);
	for (int index = 0; index < startAndEndpoints.size(); index += 2)
	{
		m_startpoints.push_back(startAndEndpoints[index]);
		m_endpoints.push_back(startAndEndpoints[index + 1]);
	}
}

void VParabola::updateQuadraticValues()
{
	m_quadraticValues.z = getYPosOfParabola(0);
	m_quadraticValues.y = (getYPosOfParabola(2) - (getYPosOfParabola(1) * 4.0f) + (getYPosOfParabola(0) * 3.0f)) * -0.5f;
	m_quadraticValues.x = getYPosOfParabola(1) - getYPosOfParabola(0) - m_quadraticValues.y;
}

std::pair<float, float> VParabola::quadraticFormula(glm::vec3 t_quadraticValues)
{
	// -b +- sqrt(b2-4ac) / 2a;
	float twoA = (2 * t_quadraticValues.x);
	float minusB = -t_quadraticValues.y;
	float bSquaredMinusFourAC = std::pow(t_quadraticValues.y, 2) - (4.0f * t_quadraticValues.x * t_quadraticValues.z);
	if (bSquaredMinusFourAC < 0)
	{
		return std::pair<float, float>(NULL, NULL);
	}
	float posXValue = (minusB + sqrt(bSquaredMinusFourAC)) / twoA;
	float negXValue = (minusB - sqrt(bSquaredMinusFourAC)) / twoA;
	return posXValue < negXValue ? std::pair<float, float>(posXValue, negXValue) :
								   std::pair<float, float>(negXValue, posXValue);
}

void VParabola::updateEdges()
{
	for (int index = 0; index < m_edge.size() - 1; index++)
	{
		m_edge[index].updateStartAndEndpoints(m_endpoints[index], m_startpoints[index + 1], false);
	}
}

std::pair<glm::vec2, glm::vec2> VParabola::getPointsOfCollision(VParabola t_otherParabola)
{


	glm::vec3 quadraticValues = glm::vec3(m_quadraticValues.x - t_otherParabola.m_quadraticValues.x,
										  m_quadraticValues.y - t_otherParabola.m_quadraticValues.y,
										  m_quadraticValues.z - t_otherParabola.m_quadraticValues.z);
	std::pair<float, float> xValuesOfCollision = quadraticFormula(quadraticValues);
	if (xValuesOfCollision == std::pair<float, float>(NULL, NULL))
	{
		return std::pair<glm::vec2, glm::vec2>(glm::vec2(NULL, NULL), glm::vec2(NULL, NULL));
	}
	else
	{
		return std::pair<glm::vec2, glm::vec2>(glm::vec2(xValuesOfCollision.first, getYPosOfParabola(xValuesOfCollision.first)), glm::vec2(xValuesOfCollision.second, getYPosOfParabola(xValuesOfCollision.second)));
	}
}
