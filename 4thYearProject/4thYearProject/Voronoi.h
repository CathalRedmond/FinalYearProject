#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "ScreenSize.h"
class Voronoi
{
public:
	Voronoi();
	~Voronoi() {};
	void render(sf::RenderWindow& t_window);
	void update(sf::Time t_deltaTime);
	void handleKeyboardInput(sf::Event t_keyboardEvent);
private:

	std::vector<sf::Vector2f> vertices;
	std::vector<sf::CircleShape> circles;
	int circleGrowthAmount;
	const int NUMBER_OF_POINTS;
	float radius = 5;

	std::vector<sf::Vector2f> getParabolaPoints(int verticesIndex);
	void drawParabola(sf::RenderWindow &t_window, std::vector<std::vector<sf::Vector2f>> t_parabolaPoints);
	int lineY = 0;
	sf::Vector2f pointPos = sf::Vector2f(SCREEN_SIZE::WIDTH / 2, 200);
};

