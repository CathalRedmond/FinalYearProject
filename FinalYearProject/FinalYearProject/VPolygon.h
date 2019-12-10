#pragma once
#include <SDL.h>
#include "VPoint.h"
#include "VParabola.h"
#include "VEdge.h"
#include "vec3.hpp"
class VPolygon
{
public:
	VPolygon();
	void update();
	void render(SDL_Renderer* t_renderer);
private:
	//VPoint m_centrePoint;
	//VParabola m_parabola;
	std::vector<VEdge> m_edges;
	glm::vec3 m_colour;
};