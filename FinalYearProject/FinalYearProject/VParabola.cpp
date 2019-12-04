#include "VParabola.h"

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
	for (int index = 0; index < m_edge.size(); index++)
	{
		m_edge[index].updateStartAndEndpoints(m_startpoints[index], m_endpoints[index]);
	}
}

void VParabola::render(SDL_Renderer* t_renderer)
{
	SDL_SetRenderDrawColor(t_renderer, 0, 255, 0, 255);
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
		m_edge[index].render(t_renderer);
	}

	SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
}

void VParabola::updateCollisionPoints()
{
	m_startpoints.clear();
	m_endpoints.clear();
	for (int index = 0; index < touchingParabolas.size(); index++)
	{
		try
		{
			findPointsOfCollision(*touchingParabolas[index]);
		}
		catch (...)
		{
			std::cout << "error";
		}
	}
}

void VParabola::setTouchingParabola(VParabola* t_otherParabola)
{
	touchingParabolas.push_back(t_otherParabola);
	m_edge.push_back(VEdge());
	updateQuadraticValues();
	findPointsOfCollision(*t_otherParabola);
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
	return (std::pow(t_xPos - m_point.getPosition().x, 2.0f) / (2.0f * (m_point.getPosition().y - m_sweepLineYPos))) + ((m_point.getPosition().y + m_sweepLineYPos) / 2.0f);
}

VPoint VParabola::getPoint()
{
	return m_point;
}

bool VParabola::isValidPoint(glm::vec2 t_point)
{
	updateQuadraticValues();
	bool isValid = false;

	if (t_point.x <= SCREEN_SIZE::WIDTH && t_point.x >= 0 && t_point.y <= SCREEN_SIZE::HEIGHT && t_point.y >= 0)
	{
		float startPointsSize = m_startpoints.size();
		if (startPointsSize == 1)
		{
			if (isPointBetweenTwoPoints(t_point, m_startpoints[0], m_endpoints[0], true))
			{
				isValid = true;
			}
		}
		else
		{
			for (int index = 0; index < m_startpoints.size(); index++)
			{

				if (isPointOnLine(t_point))
				{
					bool isLeft;
					if (index == 0)
					{
						isLeft = m_startpoints[index].y < m_startpoints[index + 1].y;
						if (isPointBetweenTwoPoints(t_point, m_startpoints[index], m_startpoints[index + 1], isLeft))
						{
							isValid = true;
						}
					}
					if (index == startPointsSize - 1)
					{
						isLeft = m_endpoints[0].y > m_startpoints[index].y;
						if (isPointBetweenTwoPoints(t_point, m_endpoints[index], m_endpoints[0], isLeft))
						{
							isValid = true;
						}
					}
					else
					{
						isLeft = m_endpoints[index+1].y > m_startpoints[index].y;

						if (isPointBetweenTwoPoints(t_point, m_endpoints[index], m_startpoints[index+1], isLeft))
						{
							isValid = true;
						}
					}
				}

			}
		}
	}
	return isValid;
}

bool VParabola::isPointBetweenTwoPoints(glm::vec2 t_point,glm::vec2 startpoint, glm::vec2 endpoint, bool t_isLeftSide)
{
	// change to >= and <=
	if (t_point.x > startpoint.x && t_point.x < endpoint.x)
	{
		if (startpoint.y == endpoint.y)
		{
			if (t_point.y > startpoint.y)
			{
				return true;
			}
		}
		else if (startpoint.x < m_point.getPosition().x && endpoint.x > m_point.getPosition().x)
		{
			if (t_point.y > startpoint.y&& t_point.y > endpoint.y)
			{
				return true;
			}
		}
		else
		{
			if (t_isLeftSide)
			{
				if (t_point.y > startpoint.y&& t_point.y < endpoint.y)
				{
					return true;
				}
			}
			else
			{
				if (t_point.y < startpoint.y && t_point.y > endpoint.y)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void VParabola::findPointsOfCollision(VParabola otherParabola)
{
	if (otherParabola.m_quadraticValues.z != -1)
	{
		otherParabola.updateParabolaPoints();
		otherParabola.updateQuadraticValues();
	}
	float a = m_quadraticValues.x - otherParabola.m_quadraticValues.x;
	float b = m_quadraticValues.y - otherParabola.m_quadraticValues.y;
	float c = m_quadraticValues.z - otherParabola.m_quadraticValues.z;
	std::pair<float, float> xValuesOfCollision = quadraticFormula(glm::vec3(a, b, c));

	glm::vec2 startPoint;
	glm::vec2 endPoint;
	if (otherParabola.m_quadraticValues.x == 0 &&
		otherParabola.m_quadraticValues.y == 0 &&
		otherParabola.m_quadraticValues.z == -1)
	{
		startPoint = glm::vec2(xValuesOfCollision.first, -1);
		endPoint = glm::vec2(xValuesOfCollision.second, -1);
	}
	else
	{
		startPoint = glm::vec2(xValuesOfCollision.first, getYPosOfParabola(xValuesOfCollision.first));
		endPoint = glm::vec2(xValuesOfCollision.second, getYPosOfParabola(xValuesOfCollision.second));
	}
	m_startpoints.push_back(startPoint);
	m_endpoints.push_back(endPoint);
	
}

void VParabola::updateQuadraticValues()
{
	m_quadraticValues.z = getYPosOfParabola(0);
	m_quadraticValues.y = (getYPosOfParabola(2) - (getYPosOfParabola(1) * 4.0f) + (getYPosOfParabola(0) * 3.0f)) * -0.5f;
	m_quadraticValues.x = getYPosOfParabola(1) - getYPosOfParabola(0) - m_quadraticValues.y;
}

bool VParabola::isPointOnLine(glm::vec2 t_point)
{
	float equation =  (m_quadraticValues.x * std::pow(t_point.x, 2)) + (m_quadraticValues.y * t_point.x) + m_quadraticValues.z;
	if ((equation > t_point.y - 1) && (equation < t_point.y + 1))
	{
		return true;
	}
	return true;
}

std::pair<float, float> VParabola::quadraticFormula(glm::vec3 t_quadraticValues)
{
	// -b +- sqrt(b2-4ac) / 2a;

	float twoA = (2 * t_quadraticValues.x);
	float minusB = -t_quadraticValues.y;
	float bSquared = std::pow(t_quadraticValues.y, 2);
	float minusfourAC = -4.0f * t_quadraticValues.x * t_quadraticValues.z;

	if (bSquared + minusfourAC < 0)
	{
		return std::pair<float, float>(NULL, NULL);
	}
	float posXValue = (minusB + sqrt(bSquared + minusfourAC)) / twoA;
	float negXValue = (minusB - sqrt(bSquared + minusfourAC)) / twoA;
	if (posXValue < negXValue)
	{
		return std::pair<float, float>(posXValue, negXValue);
	}
	else
	{
		return std::pair<float, float>(negXValue, posXValue);
	}
}
