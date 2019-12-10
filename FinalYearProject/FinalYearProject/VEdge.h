#pragma once
#include <SDL.h>
#include "vec2.hpp"
#include "vec3.hpp"
#include "glm.hpp"
#include "VPoint.h"
#include "ScreenSize.h"

class VEdge
{
public:
	VEdge(VPoint one, VPoint two);
	bool collisionDetection(VEdge t_otherLine);
	glm::vec2 getStartPoint();
	glm::vec2 getEndPoint();
	void updateStartAndEndpoints(glm::vec2 t_startpoint, glm::vec2 t_endpoint, bool yes);
	void render(SDL_Renderer* t_renderer, glm::vec3 t_colourOfEdge = glm::vec3(255.0f, 0.0f, 0.0f));
	void update();
private:
	glm::vec2 m_startPoint;
	glm::vec2 m_endPoint;

	glm::vec2 m_midPoint;
	glm::vec2 m_origin;
	float distanceFromOrigin;
	bool isFinished;
	bool isStartPointFinished;
	bool isEndPointFinished;
	void updateSlope();

	VPoint m_parabolaOne;
	VPoint m_parabolaTwo;

	void lineAutoFinish(bool isWhole = true);

	void init();
	
	
};

