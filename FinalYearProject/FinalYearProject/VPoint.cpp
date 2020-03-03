#include "VPoint.h"

VPoint::VPoint(glm::vec2 t_point) :
	m_point{ t_point }
{
}

glm::vec2 VPoint::getPoint()
{
	return m_point;
}

void VPoint::setPoint(glm::vec2 t_newPoint)
{
	m_point = t_newPoint;
}
