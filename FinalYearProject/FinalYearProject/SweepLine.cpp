#include "SweepLine.h"

SweepLine::SweepLine():
	m_yPos{-5.0f}
{
}

void SweepLine::update()
{
	int x = 0, y = 0;
	SDL_GetMouseState(&x, &y);
	m_yPos = y;
}

void SweepLine::render(SDL_Renderer* t_renderer)
{
	SDL_SetRenderDrawColor(t_renderer, 255, 0, 255, 255);
	SDL_RenderDrawLine(t_renderer, 0, m_yPos, SCREEN_SIZE::WIDTH, m_yPos);
	SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
};

float SweepLine::getYPos()
{
	return m_yPos;
}
