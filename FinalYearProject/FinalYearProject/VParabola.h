#pragma once
#include <SDL.h>
#include <vector>
#include <iostream>
#include "vec2.hpp"
#include "vec3.hpp"
#include "Utility.h"

class VParabola
{
public:
	VParabola(glm::vec2 t_focus = glm::vec2(0,0));
	void operator=(const VParabola& t_otherParabola);
	void update(float t_directrix);
	void render(SDL_Renderer* t_renderer);
	glm::vec2 collisionDetection(VParabola& t_otherParabola);

private:
	glm::vec2 m_focus;
	float m_directrix;
	std::vector<glm::vec2> m_parabolaPoints;
	float getYPos(float t_x);
	std::pair<float, float> quadraticFormula(glm::vec3 t_quadraticValues);
	void updateQuadraticValues();
	glm::vec3 m_quadraticValues;
};

