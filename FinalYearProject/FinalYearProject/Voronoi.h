#pragma once
#include <SDL.h>
#include "VPolygon.h"
#include <vector>
#include <algorithm>
#include "vec2.hpp"
class Voronoi
{
public:
	Voronoi();
	void start(std::vector<glm::vec2> t_pointPositions);
	void update();
	void render(SDL_Renderer* t_renderer);
	void processEvents(SDL_Event* t_event);
private:
	void collisionDetection();
	std::vector<VPolygon*> m_polygons;
	// line that moves down the screen
	int m_directrix;
	// bool if voronoi is running
	bool m_run;

	std::vector<glm::vec2> m_points;
	glm::vec2 closestPointToMouse;
	bool moveWithMouse = true;

};

