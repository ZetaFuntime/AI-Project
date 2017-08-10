#pragma once

#include "Behaviour.h"
#include <glm\vec2.hpp>
#include <vector>
#include <map>

using std::map;
using std::vector;
using glm::vec2;

class BehaviourManager : public Behaviour
{
public:
	BehaviourManager();
	~BehaviourManager();

	virtual void Update(GameObject *object, float deltaTime);
	virtual void Draw(GameObject *object, aie::Renderer2D *renderer);

	void PushBehaviour(const char* name, Behaviour *behaviour);
	void SetBehaviour(const char* name);

	void SetMaxVelocity(float MaxSpeed);
	float GetMaxVelocity();


	// Get the behaviour called according to its numerical key in the vector
	Behaviour* GetBehaviour(const char* name);

	void PopBackBehaviour();

	void ClearBehaviours();

private:

	vec2 CalculateForce();

	map <const char*, Behaviour*>		m_behaviours;
	vector<Behaviour*>					m_activeBehaviours;
	vector<vec2>						m_appliedForces;

protected:

	float m_maxSpeed;
};