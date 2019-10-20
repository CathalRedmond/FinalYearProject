#pragma once
#include "ScreenSize.h"
#include "VPoint.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
class VParabola
{
public:
	VParabola(VPoint parabolaPoint, float sweepLineY);
	void update(float sweepLineY);
	void render(sf::RenderWindow& t_window);
private:
	void updateParabolaPoints();
	float getYPosOfParabola(float xPos);

	VPoint m_point;
	float m_sweepLineYPos;
	std::vector<sf::Vector2f> m_parabolaPoints;
};

