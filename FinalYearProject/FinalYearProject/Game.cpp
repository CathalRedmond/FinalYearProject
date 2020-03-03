
#include "Game.h"

Game::Game():
	m_voronoiInitialised{ false }
{
	try
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) throw "Error Loading SDL";
		m_window = SDL_CreateWindow("Final Year Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, NULL);
		if (!m_window) throw "Error Loading Window";
		m_renderer = SDL_CreateRenderer(m_window, -1, 0);
		if (!m_renderer) throw "Error Loading Renderer";
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
		m_isRunning = true;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGui_ImplSDL2_InitForD3D(m_window);
		ImGuiSDL::Initialize(m_renderer, 800, 600);

	}
	catch (std::string error)
	{
		std::cout << error << std::endl;
		m_isRunning = false;
	}
}

Game::~Game()
{
	cleanup();
}

void Game::run()
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;
	while (m_isRunning)
	{
		frameStart = SDL_GetTicks();
		frameTime = SDL_GetTicks() - frameStart;
		processEvents();
		update();
		render();
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
}

void Game::processEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		m_isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (SDLK_ESCAPE == event.key.keysym.sym) m_isRunning = false;
		else if (SDLK_SPACE == event.key.keysym.sym) initVoronoi();
		break;
	default:
		break;
	}

	m_voronoi.processEvents(&event);
}

void Game::update()
{
	m_voronoi.update();
}

void Game::render()
{
	SDL_RenderClear(m_renderer);
	m_voronoi.render(m_renderer);
	SDL_RenderPresent(m_renderer);
}

void Game::cleanup()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_QUIT;
}

void Game::initVoronoi()
{
	if (!m_voronoiInitialised)
	{
		std::vector<glm::vec2> points;
	   /* for (int index = 0; index < 10; index++)
		{
			float x = glm::linearRand(0, 800);
			float y = glm::linearRand(0, 600);
			points.push_back((glm::vec2(x,y)));
		}*/
		points.push_back(glm::vec2(300, 100));
		//points.push_back(glm::vec2(400, 400));
		points.push_back(glm::vec2(200, 300));
		points.push_back(glm::vec2(600, 200));
		m_voronoi.start(points);
		m_voronoiInitialised = true;
	}
}
