#pragma once
#include <SDL.h>
#include <vector>
#include "VPolygon.h"
#include "VPoint.h"
#include "VEdge.h"
#include "VParabola.h"
#include "SweepLine.h"

class Voronoi
{
public:
	Voronoi();
	void render(SDL_Renderer* t_renderer);
	void update();
	void handleKeyBoardInput(SDL_Event t_keyboardEvent);
private:
	SweepLine m_sweepLine;
	std::vector<VPoint> m_points;
	std::vector<VParabola> m_parabolas;
	//std::vector<VPolygon> m_polygons;
	//std::vector<VEdge> m_edge;
	const int NUMBER_OF_POINTS;
	VParabola topOfScreen;
};

