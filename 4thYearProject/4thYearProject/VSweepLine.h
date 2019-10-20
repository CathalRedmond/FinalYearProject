#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
class VSweepLine
{
public:
	VSweepLine();
	void update();
	void render(sf::RenderWindow& t_window);
	float getYPos();
private:
	float m_yPos;
};

