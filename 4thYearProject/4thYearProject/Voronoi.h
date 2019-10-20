#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "ScreenSize.h"
#include "VParabola.h"
#include "VPoint.h"
#include "VSweepLine.h"
class Voronoi
{
public:
	Voronoi();
	~Voronoi() {};
	void render(sf::RenderWindow& t_window);
	void update(sf::Time t_deltaTime);
	void handleKeyboardInput(sf::Event t_keyboardEvent);
private:
	VSweepLine m_sweepLine;
	std::vector<VPoint> m_points;
	std::vector<VParabola> m_parabolas;
	const int NUMBER_OF_POINTS;
};

