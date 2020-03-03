#pragma once
#include <SDL.h>
#include "vec2.hpp"
#include "glm.hpp"
#include "Utility.h"
#include <iostream>

class VEdge
{
public:
 	VEdge(glm::vec2 t_midpoint, std::pair<int, int> t_polygonNumbers, std::pair<glm::vec2, glm::vec2> t_polyPos);
	void render(SDL_Renderer* t_renderer);
	void setPoint(glm::vec2 t_point);
	void setStartAndEndPoint(glm::vec2 t_startpoint, glm::vec2 t_endpoint);
	void setStartPoint(glm::vec2 t_startpoint);
	void setEndPoint(glm::vec2 t_endpoint);
	std::pair<int, int> getPolygonIds();
	bool getFinished();

	glm::vec2 getStartPoint();
	glm::vec2 getEndPoint();
	glm::vec2 getMidPoint();

	void operator=(const VEdge& t_otherEdge);
private:
	glm::vec2 m_startpoint;
	glm::vec2 m_endpoint;
	glm::vec2 m_midpoint;
	std::pair<int, int> m_polygonIds;
	std::pair<glm::vec2, glm::vec2> polyPos;
	bool m_finished;
	bool areSame(float a, float b);



};

