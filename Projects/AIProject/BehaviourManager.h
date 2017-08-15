////////////////////////////////////////////////////////////////////////////////////////////////////////
////   																								////
////   Purpose:	Behaviour controller class to accurately steer the agent around the area			////
////   			depending on the forces necessary to accomplish what it is tasked to do				////
////   			For example: flee an enemy while seeking towards a destination						////
////   																								////
////   Note:	Originally, i thought about having a vector of behaviours that worked from			////
////   			one vector internally within the behaviour controller, but eventually i				////
////   			realised that the agent will only ever have one seek/pursure target at a			////
////   			given moment. This means i only really need to collect a singular point of		    ////
////   			data for the seek/flee/arrival/pursue  behaviours, whereas for evade and flee	    ////
////   			it makes more sense to keep a vector of targets for the controller to know about    ////
////   																							    ////
////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Behaviour.h"
#include <glm\vec2.hpp>
#include <vector>

class WanderBehaviour;
class ArrivalBehaviour;
class SeekBehaviour;
class FollowPathBehaviour;
class KeyboardBehaviour;

using std::vector;
using glm::vec2;

struct Entity
{
	vec2 Vel;
	vec2 Pos;
};

enum Modes {
	KEYBOARD,
	SEEK,
	ARRIVAL,
	WANDER,
	FOLLOWPATH
};

class BehaviourManager : public Behaviour
{
public:
	BehaviourManager();
	~BehaviourManager();

	virtual void Update(float deltaTime);
	virtual void Draw(aie::Renderer2D *renderer);

	void SetMaxVelocity(float MaxSpeed);
	float GetMaxVelocity();

	//void GetEntityData(GameObject * entity);

	void SetActive(Modes mode);
	void SetInactive();
private:

	vec2 CalculateForce();

	ArrivalBehaviour*					m_arrival;
	WanderBehaviour*					m_wander;
	SeekBehaviour*						m_seek;
	FollowPathBehaviour*				m_follow;
	KeyboardBehaviour*					m_keyboard;

	//vector<Entity>						m_entitydata;

protected:

	float	m_maxSpeed;
};