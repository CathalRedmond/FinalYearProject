#include "VParabola.h"

VParabola::VParabola(glm::vec2 t_focus)
	:
	m_focus{ t_focus },
	m_quadraticValues{glm::vec3(NULL,NULL,NULL)}
{
	m_directrix = -50;
	//m_parabolaPoints
	for (int index = 0; index < 800; index += 4)
	{
		m_parabolaPoints.push_back(glm::vec2(static_cast<float>(index), getYPos(index)));
	}
}

void VParabola::operator=(const VParabola& t_otherParabola)
{
	m_focus = t_otherParabola.m_focus;
	m_directrix = t_otherParabola.m_directrix;
	m_parabolaPoints = t_otherParabola.m_parabolaPoints;
	m_quadraticValues = t_otherParabola.m_quadraticValues;
}

void VParabola::update(float t_directrix)
{
	m_directrix = t_directrix;
	float xPos = 0;
	for (size_t index = 0; index < m_parabolaPoints.size(); index++)
	{
		m_parabolaPoints[index].y = getYPos(xPos);
		xPos += 4;
	}
}

void VParabola::render(SDL_Renderer* t_renderer)
{
	SDL_SetRenderDrawColor(t_renderer, 0, 255, 0, 255);
	for (size_t index = 0; index < m_parabolaPoints.size(); index++)
	{
		if (m_directrix > m_parabolaPoints.at(index).y)
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
	SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);

}

glm::vec2 VParabola::collisionDetection(VParabola& t_otherParabola)
{
	glm::vec2 collisionPoint = glm::vec2(NULL, NULL);
	updateQuadraticValues();
	t_otherParabola.updateQuadraticValues();

	glm::vec3 quadraticValues = glm::vec3(m_quadraticValues.x - t_otherParabola.m_quadraticValues.x,
		m_quadraticValues.y - t_otherParabola.m_quadraticValues.y,
		m_quadraticValues.z - t_otherParabola.m_quadraticValues.z);

	std::pair<float, float> xValues = quadraticFormula(quadraticValues);

	// no real values
	if (xValues != std::pair<float, float>(NULL, NULL))
	{
		float y1 = getYPos(xValues.first);
		float y2 = t_otherParabola.getYPos(xValues.first);
		Utility::areEquivalent(y1, y2);
		// checks if first values are the same for all cases
		if (Utility::areEquivalent(getYPos(xValues.first), t_otherParabola.getYPos(xValues.first)))
		{
			// checks second values if quadratic formula returned two valid values
			if (xValues.first != xValues.second)
			{
				if (Utility::areEquivalent(getYPos(xValues.second), t_otherParabola.getYPos(xValues.second)))
				{
					glm::vec2 collisionPointOne = glm::vec2(xValues.first, getYPos(xValues.first));
					glm::vec2 collisionPointTwo = glm::vec2(xValues.second, getYPos(xValues.second));
					collisionPoint = glm::vec2((collisionPointOne.x + collisionPointTwo.x) / 2.0f, (collisionPointOne.y + collisionPointTwo.y) / 2.0f);
				}
			}
			else
			{
				glm::vec2 collisionPointOne = glm::vec2(xValues.first, getYPos(xValues.first));
				glm::vec2 collisionPointTwo = glm::vec2(xValues.second, getYPos(xValues.second));
				collisionPoint = glm::vec2((collisionPointOne.x + collisionPointTwo.x) / 2.0f, (collisionPointOne.y + collisionPointTwo.y) / 2.0f);
			}
		}
	}
	return collisionPoint;
}

float VParabola::getYPos(float t_x)
{
	// equation of a parabola where all points on the line are equidistant from the focus and the directrix
	float y = (std::pow(t_x - m_focus.x, 2.0f) / (2.0f * (m_focus.y - m_directrix))) + ((m_focus.y + m_directrix) / 2.0f);

	return y;
}


std::pair<float, float> VParabola::quadraticFormula(glm::vec3 t_quadraticValues)
{
	// -b +- sqrt(b^2 - 4ac) / 2a
	// value of the b^2 - 4ac of the equation
	float discriminant = std::pow(t_quadraticValues.y, 2.0f) - (4.0f * t_quadraticValues.x * t_quadraticValues.z);

	std::pair<float, float> xValues;
	if (discriminant < 0)
	{
		// no real values for solution
		xValues = std::pair<float, float>(NULL, NULL);
	}
	else
	{
		// only one value
		if (discriminant == 0)
		{
			xValues.first = -t_quadraticValues.y / (2.0f * t_quadraticValues.x);
			xValues.second = xValues.first;
		}
		// two values
		else
		{
			xValues.first = (-t_quadraticValues.y - sqrt(discriminant)) / (2.0f * t_quadraticValues.x);
			xValues.second = (-t_quadraticValues.y + sqrt(discriminant)) / (2.0f * t_quadraticValues.x);
		}
	}
	return xValues;
}

void VParabola::updateQuadraticValues()
{
	m_quadraticValues.z = getYPos(0);
	m_quadraticValues.y = (getYPos(2) - (getYPos(1) * 4.0f) + (getYPos(0) * 3.0f)) * -0.5f;
	m_quadraticValues.x = getYPos(1) - getYPos(0) - m_quadraticValues.y;
}

