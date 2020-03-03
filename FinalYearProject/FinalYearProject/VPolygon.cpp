#include "VPolygon.h"

int VPolygon::idCount = 0;

VPolygon::VPolygon(glm::vec2 t_pointPosition) :
	m_centrePoint{ t_pointPosition },
	m_parabola{ m_centrePoint }
{
	m_id = idCount;
	idCount++;
}

void VPolygon::update(int t_directrixPos)
{
	if (m_centrePoint.y < t_directrixPos) m_active = true;
	else m_active = false;
	m_parabola.update(t_directrixPos);
}

void VPolygon::processEvents()
{
}

void VPolygon::render(SDL_Renderer* t_renderer)
{
	SDL_SetRenderDrawColor(t_renderer, 255, 255, 0, 255);
	SDL_RenderDrawLine(t_renderer, m_centrePoint.x - 3, m_centrePoint.y - 3, m_centrePoint.x + 3, m_centrePoint.y + 3);
	SDL_RenderDrawLine(t_renderer, m_centrePoint.x - 3, m_centrePoint.y + 3, m_centrePoint.x + 3, m_centrePoint.y - 3);

	//SDL_RenderDrawLine(t_renderer, m_position.x + 2, m_position.y, m_position.x + 2, m_position.y + 2);
	//SDL_RenderDrawLine(t_renderer, m_position.x + 2, m_position.y + 2, m_position.x, m_position.y + 2);
	//SDL_RenderDrawLine(t_renderer, m_position.x, m_position.y + 2, m_position.x, m_position.y);
	SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
	m_parabola.render(t_renderer);
	for (size_t index = 0; index < m_edges.size(); index++)
	{
		m_edges.at(index)->render(t_renderer);
	}
}

//std::string VPolygon::collisionDetection(VPolygon t_otherPolygon)
//{
//	VParabola otherParabola = t_otherPolygon.m_parabola;
//	std::pair<bool, glm::vec2> collisionData = m_parabola.collisionDetection(otherParabola);
//	if (collisionData.first)
//	{
//		if (!m_edges.empty())
//		{
//			for (int index = 0; index < m_edges.size(); index++)
//			{
//				//if (!m_edges.at(index).getFinished())
//				{
//					if (m_edges.at(index).getPolygonIds().first == t_otherPolygon.m_id
//						|| m_edges.at(index).getPolygonIds().second == t_otherPolygon.m_id)
//					{
//						return "THIRD";
//					}
//				}
//			}
//		}
//		glm::vec2 point = collisionData.second;
//		if (collisionData.second.x < 0) point.x = 0;
//		else if (collisionData.second.x > 800) point.x = 800;
//		if (collisionData.second.y < 0) point.y = 0;
//		else if (collisionData.second.y > 600) point.y = 600;
//		m_edges.push_back(VEdge(point, std::pair<int, int>(m_id, t_otherPolygon.m_id)));
//		return "TRUE";
//	}
//	return "FALSE";
//}
//
//bool VPolygon::threeWayCollsionDetection(VPolygon t_otherPolygon, VPolygon t_otherotherPolygon)
//{
//	VParabola secondParabola = t_otherPolygon.m_parabola;
//	VParabola thirdParabola = t_otherotherPolygon.m_parabola;
//	std::pair<bool, glm::vec2> collisionDataOne = m_parabola.collisionDetection(secondParabola);
//	std::pair<bool, glm::vec2> collisionDataTwo = m_parabola.collisionDetection(thirdParabola);
//
//	if (collisionDataOne.first && collisionDataTwo.first)
//	{
//		//line updated
//		for (int index = 0; index < m_edges.size(); index++)
//		{
//			if (!m_edges.at(index).getFinished())
//			{
//				if (m_edges.at(index).getPolygonIds().first == t_otherPolygon.m_id
//					|| m_edges.at(index).getPolygonIds().second == t_otherPolygon.m_id)
//				{
//					glm::vec2 collisionPoint = (collisionDataOne.second + collisionDataTwo.second) / 2.0f;
//					m_edges.at(index).setPoint(collisionPoint);
//				}
//			}
//		}
//		return true;
//	}
//	return false;
//}

bool VPolygon::getActive()
{
	return m_active;
}

glm::vec2 VPolygon::getCentrePointPosition()
{
	return m_centrePoint;
}

int VPolygon::getId()
{
	return m_id;
}

void VPolygon::createEdge(VPolygon& t_otherPolygon)
{
	glm::vec2 midPointOfEdge = glm::vec2((m_centrePoint + t_otherPolygon.m_centrePoint) / 2.0f);
	Utility::restrictVectorToBounds(midPointOfEdge);
	VEdge* edge = new VEdge(midPointOfEdge, std::pair<int, int>(m_id, t_otherPolygon.m_id), std::pair < glm::vec2, glm::vec2>(getCentrePointPosition(), t_otherPolygon.getCentrePointPosition()));
	m_edges.push_back(edge);
	t_otherPolygon.m_edges.push_back(edge);
	m_collidedPolygonsId.push_back(t_otherPolygon.m_id);
	t_otherPolygon.m_collidedPolygonsId.push_back(t_otherPolygon.m_id);
}

bool VPolygon::collidedAlready(int t_otherPolygonId)
{
	if (std::count(m_collidedPolygonsId.begin(), m_collidedPolygonsId.end(), t_otherPolygonId))
	{
		return true;
	}
	return false;
}

bool VPolygon::collidedAlreadyThreeWay(int t_otherPolygonOneId, int t_otherPolygonTwoId)
{
	for (size_t index = 0; index < m_threeWayCollidedPolygonsId.size(); index++)
	{
		if (Utility::doPairsHaveSameValues<int>(m_threeWayCollidedPolygonsId[index], std::pair<int, int>(t_otherPolygonOneId, t_otherPolygonTwoId)))
		{
			return true;
		}
	}
	return false;
}

std::vector<int> VPolygon::checkForThirdCollision(VPolygon& t_otherPolygon)
{
	std::vector<int> validCollisionIndexes;
	validCollisionIndexes.reserve(m_edges.size());
	std::vector<int> firstPolyIds = getAllOtherIds();
	std::vector<int> secondPolyIds = t_otherPolygon.getAllOtherIds();
	for (size_t index = 0; index < firstPolyIds.size(); index++)
	{
		if (std::find(secondPolyIds.begin(), secondPolyIds.end(), firstPolyIds[index]) != secondPolyIds.end())
		{
			validCollisionIndexes.push_back(firstPolyIds[index]);
		}
	}
	return validCollisionIndexes;
}

std::vector<int> VPolygon::getAllOtherIds()
{
	std::vector<int> otherIds;
	otherIds.reserve(m_edges.size());
	for (size_t index = 0; index < m_edges.size(); index++)
	{
		otherIds.push_back(m_edges[index]->getPolygonIds().first != m_id ? m_edges[index]->getPolygonIds().first : m_edges[index]->getPolygonIds().second);
	}
	return otherIds;
}

CollisionType VPolygon::collisionDetectionProper(VPolygon& t_otherPolygon)
{
	if (collidedAlready(t_otherPolygon.m_id))
	{
		if (!checkForThirdCollision(t_otherPolygon).empty())
		{
			return CollisionType::ThirdCollisionCheck;
		}
	}
	else
	{
		// collision occured
		if (m_parabola.collisionDetection(t_otherPolygon.m_parabola) != glm::vec2(NULL, NULL))
		{
			createEdge(t_otherPolygon);
			return CollisionType::Collision;
		}
	}
	return CollisionType::NoCollision;
}

bool VPolygon::collisionDetectionThreeWayProper(VPolygon& t_otherPolygonOne, VPolygon& t_otherPolygonTwo)
{
	int otherIdOne = t_otherPolygonOne.m_id;
	int otherIdTwo = t_otherPolygonTwo.m_id;
	if (!collidedAlreadyThreeWay(otherIdOne, otherIdTwo) && collidedAlready(otherIdOne) && collidedAlready(otherIdTwo) && t_otherPolygonOne.collidedAlready(otherIdTwo))
	{
		glm::vec2 centrePoint = Utility::getCentreOfCircle(m_centrePoint, t_otherPolygonOne.m_centrePoint, t_otherPolygonTwo.m_centrePoint);
		Utility::restrictVectorToBounds(centrePoint);
		getEdgeByIds(std::pair<int, int>(m_id, otherIdOne))->setPoint(centrePoint);
		getEdgeByIds(std::pair<int, int>(m_id, otherIdTwo))->setPoint(centrePoint);
		t_otherPolygonOne.getEdgeByIds(std::pair<int, int>(otherIdOne, otherIdTwo))->setPoint(centrePoint);
		m_threeWayCollidedPolygonsId.push_back(std::pair<int, int>(otherIdOne, otherIdTwo));
		t_otherPolygonOne.m_threeWayCollidedPolygonsId.push_back(std::pair<int, int>(m_id, otherIdTwo));
		t_otherPolygonTwo.m_threeWayCollidedPolygonsId.push_back(std::pair<int, int>(otherIdOne, m_id));

		return true;
	}
	return false;
}

std::vector<std::pair<VEdge*, std::pair<int, int>>> VPolygon::cleanUpEdges()
{
	UnfinishedEdges unfinishedEdges;
	for (size_t index = 0; index < m_edges.size(); index++)
	{
		if (!m_edges[index]->getFinished())
		{
			glm::vec2 mid = m_edges[index]->getMidPoint();
			glm::vec2 start = m_edges[index]->getStartPoint();
			if (mid != start)
			{
				glm::vec2 end;

				glm::vec2 vecBetween = glm::normalize(mid - start);

				
				
				

				end = start + vecBetween;
				while (Utility::withinBounds(end))
				{
					end += vecBetween;
				}





				m_edges[index]->setPoint(end);
			}

			else
			{
				VEdge* edge = m_edges[index];
				unfinishedEdges.push_back(UnfinishedEdge{ edge, edge->getPolygonIds() });
			}
		}
	}
	return unfinishedEdges;
}

void VPolygon::extraCleanUpEdge()
{
	for (size_t index = 0; index < m_edges.size(); index++)
	{
		if (!m_edges[index]->getFinished())
		{

		}
	}






}

VEdge* VPolygon::getEdgeByIds(std::pair<int, int> t_idPoints)
{
	for (size_t index = 0; index < m_edges.size(); index++)
	{
		if (Utility::doPairsHaveSameValues<int>(m_edges[index]->getPolygonIds(), t_idPoints))
		{
			return m_edges[index];
		}
	}
}

std::vector<VEdge*> VPolygon::getEdges()
{
	return m_edges;
}

VParabola& VPolygon::getParabola()
{
	return m_parabola;
}
