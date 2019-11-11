#pragma once
#include <SDL.h>
#include "vec2.hpp"
class VPoint
{
public:
	VPoint(glm::vec2 t_position);
	glm::vec2 getPosition();
	bool collisionDetection(float t_sweepLineYPos);
	bool hasTouchedSweepLine();
	void render(SDL_Renderer* t_renderer);
private:
	glm::vec2 m_position;
	bool m_hasTouchedSweepLine;
};

