#pragma once
#include <SDL.h>
#include "vec2.hpp"
#include "vec4.hpp"
#include <vector>
#include <cmath>
#include <iostream>

struct Colour
{
	Uint8 red;
	Uint8 green;
	Uint8 blue;
	Uint8 alpha;
};

enum class CollisionType
{
	Collision,
	NoCollision,
	ThirdCollisionCheck
};

class Utility
{
public:

	static void SDL_DrawLine(SDL_Renderer* t_renderer, glm::vec2 t_pointOne, glm::vec2 t_pointTwo, Colour t_colour)
	{
		Colour previousColour;
		SDL_GetRenderDrawColor(t_renderer, &previousColour.red, &previousColour.green, &previousColour.blue, &previousColour.alpha);
		SDL_SetRenderDrawColor(t_renderer, t_colour.red, t_colour.green, t_colour.blue, t_colour.alpha);
		SDL_RenderDrawLine(t_renderer, t_pointOne.x, t_pointOne.y, t_pointTwo.x, t_pointTwo.y);
		SDL_SetRenderDrawColor(t_renderer, previousColour.red, previousColour.green, previousColour.blue, previousColour.alpha);
	}

	static bool isInvalidVector(glm::vec2 t_vectorToCheck)
	{
		return (t_vectorToCheck == glm::vec2(std::numeric_limits<float>().max(), std::numeric_limits<float>().max()));
	}

	static glm::vec2 setInvalidVector()
	{
 		return glm::vec2(std::numeric_limits<float>().max(), std::numeric_limits<float>().max());
	}


	/// <summary>
	/// function that checks if two float values are equivalently the same
	/// </summary>
	/// <param name="t_firstNumber">first float</param>
	/// <param name="t_secondNumber">second float</param>
	/// <returns></returns>
	static bool areEquivalent(float t_firstNumber, float t_secondNumber)
	{
		return (t_firstNumber - 5 <= t_secondNumber) &&
			(t_firstNumber + 5 >= t_secondNumber);
	}

	static bool isHigher(glm::vec2 y1, glm::vec2 y2)
	{
		return y1.y < y2.y;
	}

	static bool areEquivalent(std::vector<float> t_floats)
	{
		for (size_t indexOne = 0; indexOne < t_floats.size(); indexOne++)
		{
			for (size_t indexTwo = indexOne + 1; indexTwo < t_floats.size(); indexTwo++)
			{
				if (!areEquivalent(t_floats[indexOne], t_floats[indexTwo]))
				{
					return false;
				}
			}
		}
		return true;
	}

	/// <summary>
	/// function that checks the position of a vector and if its within bounds of the screen
	/// if outside bounds position is translated to just inside the bounds of the screen
	/// </summary>
	/// <param name="t_vector">vector to check</param>
	static void restrictVectorToBounds(glm::vec2& t_vector)
	{
		if (t_vector.x > SCREEN_WIDTH) t_vector.x = SCREEN_WIDTH;
		else if (t_vector.x < 0) t_vector.x = 0;
		if (t_vector.y > SCREEN_HEIGHT) t_vector.y = SCREEN_HEIGHT;
		else if (t_vector.y < 0) t_vector.y = 0;
	}

	static glm::vec2 getCentreOfCircle(glm::vec2 t_pointOne, glm::vec2 t_pointTwo, glm::vec2 t_pointThree)
	{
		float h, k;
		float x1 = t_pointOne.x, x2 = t_pointTwo.x, x3 = t_pointThree.x, y1 = t_pointOne.y, y2 = t_pointTwo.y, y3 = t_pointThree.y;

		float kNumerator, kDenominator;

		kNumerator = ((std::pow(x2, 2.0f) * x1) + (std::pow(y2, 2.0f) * x1) - (std::pow(x2, 2.0f) * x3) - (std::pow(y2, 2.0f) * x3)
			+ (std::pow(x1, 2.0f) * x3) + (std::pow(y1, 2.0f) * x3) - (std::pow(x3, 2.0f) * x1) - (std::pow(y3, 2.0f) * x1)
			+ (std::pow(x3, 2.0f) * x2) + (std::pow(y3, 2.0f) * x2) - (std::pow(x1, 2.0f) * x2) - (std::pow(y1, 2.0f) * x2));
		kDenominator = 2.0f * ((y2 * x1) - (y2 * x3) + (y1 * x3) - (y3 * x1) + (y3 * x2) - (y1 * x2));
		k = kNumerator / kDenominator;


		float hNumerator, hDenominator;
		hNumerator = (std::pow(x2, 2.0f)) + (std::pow(y2, 2.0f)) - (2.0f * y2 * k) - (std::pow(x1, 2.0f)) - (std::pow(y1, 2.0f)) + (2.0f * y1 * k);
		hDenominator = 2.0f * (-x1 + x2);
		h = hNumerator / hDenominator;

		glm::vec2 centre = glm::vec2(h, k);
		// check got correct answer
		if (!areEquivalent(std::vector<float>{getCircleRadius(centre, t_pointOne), getCircleRadius(centre, t_pointTwo), getCircleRadius(centre, t_pointThree)}))
		{
			std::cout << "circle centre wrong" << std::endl;
		}
		else
		{
			std::cout << "good circle centre" << std::endl;
		}
		return centre;
	}

	static float getCircleRadius(glm::vec2 t_centre, glm::vec2 t_pointOnCircle)
	{
		return sqrt(std::pow((t_pointOnCircle.x - t_centre.x), 2.0f) + std::pow((t_pointOnCircle.y - t_centre.y), 2.0f));
	}

	template <typename T>
	static bool doPairsHaveSameValues(std::pair<T, T> t_pairOne, std::pair<T, T> t_pairTwo)
	{
		if ((t_pairOne.first == t_pairTwo.first && t_pairOne.second == t_pairTwo.second)
			|| (t_pairOne.first == t_pairTwo.second && t_pairOne.second == t_pairTwo.first))
		{
			return true;
		}
		return false;
	}

	template <typename T>
	static bool pairsHaveCommonElement(std::vector<std::pair<T, T>> t_setOfPairs)
	{
		for (size_t index = 1; index < t_setOfPairs.size(); index++)
		{
			if ((t_setOfPairs[0].first == t_setOfPairs[index].first ||
				t_setOfPairs[0].first == t_setOfPairs[index].second) ||
				(t_setOfPairs[0].second == t_setOfPairs[index].first ||
					t_setOfPairs[0].second == t_setOfPairs[index].second))
			{
				if (index != t_setOfPairs.size() - 1)
				{
					continue;
				}
				return true;
			}
			else
			{
				break;
			}
		}
		return false;
	}


	static bool withinBounds(glm::vec2 t_vector)
	{
		glm::vec2 tempVector = t_vector;
		restrictVectorToBounds(tempVector);
		return t_vector == tempVector;
	}


	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;
};
