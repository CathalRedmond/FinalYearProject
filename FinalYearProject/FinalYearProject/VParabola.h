#pragma once
#include <SDL.h>
#include <vector>
#include <iostream>
#include "VPoint.h"
#include "ScreenSize.h"
#include "vec2.hpp"
class VParabola
{
public:
	VParabola(VPoint t_parabolaPoint, float t_sweepLineYPos);
	void update(float t_sweepLineYPos);
	void render(SDL_Renderer* t_renderer);
private:
	void updateParabolaPoints();
	float getYPosOfParabola(float t_xPos);
	VPoint m_point;
	float m_sweepLineYPos;
	std::vector<glm::vec2> m_parabolaPoints;
};

