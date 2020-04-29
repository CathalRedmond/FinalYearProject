#pragma once
#include <SDL.h>
#include <vector>
#include "vec2.hpp"
#include "VParabola.h"
#include "VEdge.h"
 
using UnfinishedEdges = std::vector<std::pair<VEdge*, std::pair<int, int>>>;
using UnfinishedEdge = std::pair<VEdge*, std::pair<int, int>>;

class VPolygon
{
public:
	VPolygon(glm::vec2 t_pointPosition); 

 

	void update(int t_directrixPos);
	void processEvents();
	void render(SDL_Renderer* t_renderer);
	bool getActive();
	glm::vec2 getCentrePointPosition();
	int getId();
	CollisionType collisionDetectionProper(VPolygon& t_otherPolygon);
	bool collisionDetectionThreeWayProper(VPolygon& t_otherPolygonOne, VPolygon& t_otherPolygonTwo);
	UnfinishedEdges cleanUpEdges();
	void extraCleanUpEdge( );
	VEdge* getEdgeByIds(std::pair<int,int> t_idPoints);


	std::vector<VEdge*> getEdges();


	VParabola& getParabola();
	std::vector<int> getAllOtherIds();

private:
	glm::vec2 m_centrePoint;
	std::vector<VEdge*> m_edges;
	VParabola m_parabola;
	int m_id;
	static int idCount;
	bool m_active;

	SDL_Color polygonColour;

	void createEdge(VPolygon& t_otherPolygon);
	bool collidedAlready(int t_otherPolygonId);
	bool collidedAlreadyThreeWay(int t_otherPolygonOneId, int t_otherPolygonTwoId);
 
	std::vector<int> checkForThirdCollision(VPolygon& t_otherPolygon);

	std::vector<int> m_collidedPolygonsId;
	std::vector<std::pair<int, int>> m_threeWayCollidedPolygonsId;
};

#include "VEdge.h"
