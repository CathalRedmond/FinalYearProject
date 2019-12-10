#pragma once
#include <SDL.h>
#include <iostream>
#include "ScreenSize.h"
class SweepLine
{
public:
	SweepLine();
	void update(bool isMouse);
	void render(SDL_Renderer* t_renderer);
	float getYPos();
private:
	float m_yPos;
};

