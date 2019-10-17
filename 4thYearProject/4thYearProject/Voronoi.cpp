#include "Voronoi.h"

Voronoi::Voronoi():
	NUMBER_OF_POINTS{1}
{

	std::mt19937 range;
	range.seed(std::random_device()());
	std::uniform_int_distribution<int> randomWidth(100, SCREEN_SIZE::WIDTH - 100);
	std::uniform_int_distribution<int> randomHeight(100, SCREEN_SIZE::HEIGHT - 100);

	for (int index = 0; index < NUMBER_OF_POINTS; index++)
	{
		vertices.push_back(pointPos);
		sf::CircleShape circle;
		circle.setRadius(radius);

		circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
		circle.setPosition(vertices[index]);

		circles.push_back(circle);

	}
	circles[0].setFillColor(sf::Color::Red);
	//circles[1].setOutlineColor(sf::Color::Green);
	//circles[2].setOutlineColor(sf::Color::Blue);
	//circles[3].setOutlineColor(sf::Color::Magenta);
	//circles[4].setOutlineColor(sf::Color::Yellow);
	//circles[5].setOutlineColor(sf::Color::Cyan);
	//circles[6].setOutlineColor(sf::Color(255,128,0));
	//circles[7].setOutlineColor(sf::Color(255,153,204));
	//circles[8].setOutlineColor(sf::Color(153,255,153));
	//circles[9].setOutlineColor(sf::Color(150,150,150));


}

void Voronoi::render(sf::RenderWindow& t_window)
{
	for each (sf::CircleShape circle in circles)
	{
		t_window.draw(circle);
	}

	for (int i = 0; i < SCREEN_SIZE::WIDTH; i++)
	{
		sf::CircleShape circle;
		circle.setFillColor(sf::Color::Green);
		circle.setRadius(2.5);
		circle.setPosition(getParabolaPoints(i, 0));
		t_window.draw(circle);
	}
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color::Cyan);
	rect.setSize(sf::Vector2f(SCREEN_SIZE::WIDTH, 1));
	rect.setPosition(0, lineY);
	t_window.draw(rect);
}

void Voronoi::update(sf::Time t_deltaTime)
{
	/*for (int index = 0; index < NUMBER_OF_POINTS; index++)
	{
		circles[index].setRadius(radius);
		circles[index].setOrigin(circles[index].getGlobalBounds().width / 2, circles[index].getGlobalBounds().height / 2);
	}*/
}

void Voronoi::handleKeyboardInput(sf::Event t_keyboardEvent)
{
	if (t_keyboardEvent.type == sf::Event::KeyPressed)
	{
		if (t_keyboardEvent.key.code == sf::Keyboard::W ||
			t_keyboardEvent.key.code == sf::Keyboard::Up)
		{
			lineY--;
		}
		else if (t_keyboardEvent.key.code == sf::Keyboard::S ||
			t_keyboardEvent.key.code == sf::Keyboard::Down)
		{
			lineY++;
		}
	}
}

std::vector<sf::Vector2f> Voronoi::getParabolaPoints(int verticesIndex)
{
	float pointXPos = vertices[verticesIndex].x;
	float pointYPos = vertices[verticesIndex].y;
	float sweepLineYPos = lineY;
	std::vector<sf::Vector2f> parabolaPoints;
	for (float index = 0; index < SCREEN_SIZE::WIDTH; index += 0.5)
	{
		float yPosition = (std::pow(index - pointXPos, 2.0f) / (2.0f * (pointYPos - sweepLineYPos))) + ((pointYPos + sweepLineYPos) / 2.0f));
		parabolaPoints.push_back(sf::Vector2f(index, yPosition));
	}
	return parabolaPoints;
}

void Voronoi::drawParabola(sf::RenderWindow& t_window, std::vector<std::vector<sf::Vector2f>> t_parabolaPoints)
{
	for (int index = 0, int index2 = 0; index < t_parabolaPoints[0].size; index++)
	{
		for (; index2 < t_parabolaPoints.size; index2++)
		{
			t_window.draw(t_parabolaPoints[index2][index]);
		}
	}
}
