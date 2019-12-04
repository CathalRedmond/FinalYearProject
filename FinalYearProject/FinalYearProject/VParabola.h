#pragma once
#include <SDL.h>
#include <vector>
#include <iostream>
#include "VPoint.h"
#include "VEdge.h"
#include "ScreenSize.h"
#include "vec2.hpp"
#include "vec3.hpp"
class VParabola
{
public:
	VParabola(VPoint t_parabolaPoint, float t_sweepLineYPos);
	VParabola(glm::vec3 quadraticValues);
	void update(float t_sweepLineYPos);
	void render(SDL_Renderer* t_renderer);
	void updateCollisionPoints();
	void setTouchingParabola(VParabola* t_otherParabola);
	bool isValidPoint(glm::vec2 t_point);
	float getYPosOfParabola(float t_xPos); 
	VPoint getPoint();

private:
	void updateParabolaPoints();
	VPoint m_point;
	float m_sweepLineYPos;
	std::vector<glm::vec2> m_parabolaPoints;
	std::vector<glm::vec2> m_startpoints;
	std::vector<glm::vec2> m_endpoints;
	bool isPointBetweenTwoPoints(glm::vec2 t_point, glm::vec2 startpoint, glm::vec2 endpoint, bool t_isLeftSide);


	void findPointsOfCollision(VParabola otherParabola);
	glm::vec3 m_quadraticValues;
	void updateQuadraticValues();
	bool isPointOnLine(glm::vec2 t_point);
	std::vector<VParabola*> touchingParabolas;
	std::pair<float, float> quadraticFormula(glm::vec3 t_quadraticValues);

	std::vector<VEdge> m_edge;

	void updateEdges();
};

