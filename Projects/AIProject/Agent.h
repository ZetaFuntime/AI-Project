#pragma once

#include "GameObject.h"
#include "Graph2D.h"
#include <glm\glm.hpp>
#include <list>

class BehaviourManager;
//class Path;
class Graph2D;
class Pathfinder;

namespace aie {
	class Font;
	class Texture;
}

struct Pos
{
	glm::vec2 data;
	float rotation;
	int colour;
};

class Agent : public GameObject
{
public:
	Agent(aie::Texture *tex = nullptr);
	virtual ~Agent();

	virtual void Update(float deltaTime);
	virtual void Draw(aie::Renderer2D *renderer);

	void SetGraph(Graph2D *graph);
	Graph2D *GetGraph();
	void DoPathLogic();
	void DoTrailLogic();

protected:

	int mX, mY;
	float m_effectLength;
	float m_trailDelay;
	glm::vec2 prevLocation;

	//Path*				m_path;
	Graph2D*			m_graph;
	Graph2D::Node*		m_startNode;
	Graph2D::Node*		m_endNode;
	Pathfinder*			m_pathfinder;

	std::list<Pos> m_prevPoints;
	BehaviourManager*	m_steeringmanager;

private:

	const char *m_behaviourName;
};