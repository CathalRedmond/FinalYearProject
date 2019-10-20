#pragma once
#include <SFML/Graphics.hpp>
class VPoint
{
public:
	VPoint(float t_xPos, float t_yPos);
	VPoint();
	float x();
	float y();
	bool collisionDetection(float t_sweepLineYPos);
	bool hasTouchedSweepLine();
	void renderPoint(sf::RenderWindow& t_window);
private:
	float m_xPos;
	float m_yPos;
	bool m_hasTouchedSweepLine;
};

