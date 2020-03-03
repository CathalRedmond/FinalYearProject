#pragma once
#include "vec2.hpp"
class VPoint
{
public:
	VPoint(glm::vec2 t_point = glm::vec2());
	glm::vec2 getPoint();
	void setPoint(glm::vec2 t_newPoint);
private:
	glm::vec2 m_point;
};

