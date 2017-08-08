#pragma once

#include "Behaviour.h"
#include <glm\vec2.hpp>
#include <vector>
#include <map>

using std::map;
using std::vector;

class BehaviourManager : public Behaviour
{
public:
	BehaviourManager();
	~BehaviourManager();

	virtual void Update(GameObject *object, float deltaTime);
	virtual void Draw(GameObject *object, aie::Renderer2D *renderer);

	void PushBehaviour(const char* name, Behaviour *behaviour);
	void SetBehaviour(const char* name);
	
	// Get the behaviour called according to its numerical key in the vector
	Behaviour* GetBehaviour();

private:

	glm::vec2 CalculateForce();

	map <const char*, Behaviour*>		m_behaviours;
	vector<Behaviour*>					m_activeBehaviours;

protected:
};