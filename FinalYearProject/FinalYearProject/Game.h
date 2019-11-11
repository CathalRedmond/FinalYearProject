#pragma once
#include <SDL.h>
#include <iostream>
#include "ScreenSize.h"
#include "Voronoi.h"

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	void processEvent();
	void update();
	void render();
	void cleanup();

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	bool m_isRunning;
	Voronoi m_voronoi;

};

