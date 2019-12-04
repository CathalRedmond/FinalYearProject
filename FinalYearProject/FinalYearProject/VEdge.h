#pragma once
#include <SDL.h>
#include "vec2.hpp"
#include "vec3.hpp"
#include "glm.hpp"

class VEdge
{
public:
	VEdge();
	bool collisionDetection(VEdge t_otherLine);
	glm::vec2 getStartPoint();
	glm::vec2 getEndPoint();
	void updateStartAndEndpoints(glm::vec2 t_startpoint, glm::vec2 t_endpoint);
	void render(SDL_Renderer* t_renderer);
private:
	glm::vec2 m_startPoint;
	glm::vec2 m_endPoint;

	

	void updateSlope();
	
};

