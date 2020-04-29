#include "Voronoi.h"

Voronoi::Voronoi() :
	m_directrix{ -50 },
	m_run{ false }
{
}

void Voronoi::start(std::vector<glm::vec2> t_pointPositions)
{

	//    sort(v.begin(), v.end(), compareInterval); 
	std::sort(t_pointPositions.begin(), t_pointPositions.end(), Utility::isHigher);


	for (size_t index = 0; index < t_pointPositions.size(); index++)
	{
		m_polygons.push_back(new VPolygon(t_pointPositions.at(index)));
	}
	m_run = true;
	m_directrix = 0;
}

void Voronoi::update()
{
	if (m_run)
	{
		if (!moveWithMouse)
		{
			int y = 0;
			SDL_GetMouseState(0, &y);
			m_directrix = y;
		}
		else
		{
			m_directrix += 6;
		}
		if (m_directrix > 0 && m_directrix < 1000)
		{

			for (size_t index = 0; index < m_polygons.size(); index++)
			{
				m_polygons.at(index)->update(m_directrix);
			}
			collisionDetection();
		}
		else if (m_directrix > 1000)
		{
			m_polygons;
			////cleanup
			UnfinishedEdges unfinishedEdges;
			for (size_t index = 0; index < m_polygons.size(); index++)
			{
				UnfinishedEdges newUnfinished = m_polygons[index]->cleanUpEdges();
				unfinishedEdges.insert(unfinishedEdges.begin(), newUnfinished.begin(), newUnfinished.end());
			}
			for (size_t index = 0; index < unfinishedEdges.size(); index++)
			{
				for (size_t index2 = index + 1; index2 < unfinishedEdges.size(); index2++)
				{
					if (Utility::doPairsHaveSameValues(unfinishedEdges[index].second, unfinishedEdges[index2].second))
					{
						unfinishedEdges.erase(unfinishedEdges.begin() + (index2));
					}
				}
			}
	
			if (!unfinishedEdges.empty())
			{
				for (size_t index = 0; index < unfinishedEdges.size(); index++)
				{
					std::vector<int> idsOne = m_polygons.at(unfinishedEdges[index].second.first)->getAllOtherIds();
					std::vector<int> idsTwo = m_polygons.at(unfinishedEdges[index].second.second)->getAllOtherIds();
					std::vector<int> validOutComes;
					for (size_t index = 0; index < idsOne.size(); index++)
					{
						if (std::find(idsTwo.begin(), idsTwo.end(), idsOne[index]) != idsTwo.end())
						{
							validOutComes.push_back(idsOne[index]);
						}
					}
					// get angel between
					glm::vec2 vecOne;
					glm::vec2 vecTwo;
					std::vector<VEdge*> edges = m_polygons.at(validOutComes[0])->getEdges();
					for (size_t edgeIndex = 0; edgeIndex < edges.size(); edgeIndex++)
					{
						if (Utility::doPairsHaveSameValues(std::pair<int, int>(unfinishedEdges[index].second.first, validOutComes[0]), edges[edgeIndex]->getPolygonIds()))
						{
							vecOne = edges[edgeIndex]->getStartPoint() - edges[edgeIndex]->getEndPoint();
						}
						else if (Utility::doPairsHaveSameValues(std::pair<int, int>(unfinishedEdges[index].second.second, validOutComes[0]), edges[edgeIndex]->getPolygonIds()))
						{
							vecTwo = edges[edgeIndex]->getStartPoint() - edges[edgeIndex]->getEndPoint();

						}
					}
					float angle = glm::degrees(std::acos(glm::dot(vecOne, vecTwo) / (glm::length(vecOne) * glm::length(vecTwo))));
					angle /= 2.0f;

					glm::vec2 start = unfinishedEdges[index].first->getStartPoint();

					glm::vec2 end;

					glm::vec2 vecBetween = glm::vec2(std::cos(glm::radians(angle)), std::sin(glm::radians(angle)));



					end = start + vecBetween;
					while (Utility::withinBounds(end))
					{
						end += vecBetween;
					}





					unfinishedEdges[index].first->setPoint(end);


				}
			}

		}
	}
}

void Voronoi::render(SDL_Renderer* t_renderer)
{
	SDL_SetRenderDrawColor(t_renderer, 255, 0, 255, 255);
	SDL_RenderDrawLine(t_renderer, 0, m_directrix, 800, m_directrix);
	for (size_t index = 0; index < m_polygons.size(); index++)
	{
		m_polygons.at(index)->render(t_renderer);
	}
	SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
}

void Voronoi::processEvents(SDL_Event* t_event)
{
	//if (t_event->type == SDL_MOUSEMOTION)
	//{
	//	// check if point within x position and higlight
	//	glm::vec2 newPoint = glm::vec2(SDL_MouseButtonEvent().x, SDL_MouseButtonEvent().y);
	//	glm::vec2 closestPoint = m_points[0];
	//	for (size_t index = 1; index < m_points.size(); index++)
	//	{
	//		/*if (glm::distance(closestPoint, newPoint));
	//		{

	//		}*/
	//	}
	//}
	if (t_event->type == SDL_MOUSEBUTTONDOWN)
	{
		if (t_event->button.button == SDL_BUTTON_LEFT)
		{
			// add to points
			/*glm::vec2 newPoint = glm::vec2(SDL_MouseButtonEvent().x, SDL_MouseButtonEvent().y);
			m_points.push_back(newPoint);*/
			//moveWithMouse = !moveWithMouse;

		}
		else if (SDL_MouseButtonEvent().button == SDL_BUTTON_RIGHT)
		{
			m_polygons.clear();
			// remove points
		}
	}
	if (t_event->type == SDL_KEYDOWN)
	{

		if (t_event->key.keysym.sym == SDLK_q)
		{
			m_polygons.clear();
		}
	}
}

void Voronoi::collisionDetection()
{
	float polygonOnePositionY;
	for (size_t index = 0; index < m_polygons.size(); index++)
	{
		if (m_polygons.at(index)->getActive())
		{
			polygonOnePositionY = m_polygons[index]->getCentrePointPosition().y;
			for (size_t index2 = index + 1; index2 < m_polygons.size(); index2++)
			{
				if (m_polygons.at(index2)->getActive())
				{
					// only check collision of polygons above current one
					if (polygonOnePositionY <= m_polygons[index2]->getCentrePointPosition().y)
					{
						if (m_polygons[2]->getActive())
						{
							int stophere = 3;
						}
						if (m_polygons[index]->collisionDetectionProper(*m_polygons[index2]) == CollisionType::ThirdCollisionCheck)
						{
							for (size_t index3 = index2 + 1; index3 < m_polygons.size(); index3++)
							{
								if (m_polygons.at(index3)->getActive())
								{
									m_polygons[index]->collisionDetectionThreeWayProper(*m_polygons[index2], *m_polygons[index3]);
								}
							}
						}
					}
				}
			}
		}
	}
}
