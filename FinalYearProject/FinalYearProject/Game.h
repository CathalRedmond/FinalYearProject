#pragma once
#include <SDL.h>
#include <iostream>
#include "glm.hpp"
#include "gtc/random.hpp"
#include "Voronoi.h"
#include "imgui/imgui.h"
#include "imgui/imgui_sdl.h"
#include "imgui/imgui_impl_sdl.h"
#include <random>

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	void processEvents();
	void update();
	void render();
	void cleanup();
	void initVoronoi();

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	bool m_isRunning;
	Voronoi m_voronoi;
	bool m_voronoiInitialised;
	std::vector<glm::vec2> points;

	int count;
};

