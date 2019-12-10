#pragma once
#include <SDL.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include "VPoint.h"
#include "ScreenSize.h"
#include "vec2.hpp"
#include "vec3.hpp"
#include "VEdge.h"

class VParabola
{
public:
	VParabola(VPoint t_parabolaPoint, float t_sweepLineYPos);
	VParabola(glm::vec3 quadraticValues);
	void update(float t_sweepLineYPos);
	void render(SDL_Renderer* t_renderer, glm::vec3 t_colourOfParabola = glm::vec3(0.0f, 255.0f, 0.0f));
	void updateCollisionPoints();
	void setTouchingParabola(VParabola* t_otherParabola);
	bool isValidPoint(glm::vec2 t_point);
	float getYPosOfParabola(float t_xPos); 
	VPoint getPoint();

	bool collisionDetection(VParabola t_otherParabola);

private:
	void updateParabolaPoints();
	VPoint m_point;
	float m_sweepLineYPos;
	std::vector<glm::vec2> m_parabolaPoints;
	std::vector<glm::vec2> m_startpoints;
	std::vector<glm::vec2> m_endpoints;
	bool isPointBetweenTwoPoints(glm::vec2 t_point, glm::vec2 startpoint, glm::vec2 endpoint);


	void findPointsOfCollision();
	glm::vec3 m_quadraticValues;
	void updateQuadraticValues();
	std::vector<VParabola*> touchingParabolas;
	std::pair<float, float> quadraticFormula(glm::vec3 t_quadraticValues);

	std::vector<VEdge> m_edge;
	void updateEdges();


	std::pair<glm::vec2, glm::vec2> getPointsOfCollision(VParabola t_otherParabola);
};

