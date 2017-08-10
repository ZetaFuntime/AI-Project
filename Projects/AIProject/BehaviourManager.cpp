#include "BehaviourManager.h"
#include "ArrivalBehaviour.h"
#include "KeyboardBehaviour.h"
#include "SeekBehaviour.h"
#include "FollowPathBehaviour.h"
#include "WanderBehaviour.h"
#include "GameObject.h"
#include <assert.h>

BehaviourManager::BehaviourManager()
{
	PushBehaviour("SEEK", new SeekBehaviour("SEEK"));
	PushBehaviour("FLEE", new SeekBehaviour("FLEE"));
	PushBehaviour("PATHSEEKER", new FollowPathBehaviour());
	PushBehaviour("WANDER", new WanderBehaviour());
	PushBehaviour("ARRIVAL", new ArrivalBehaviour());
	PushBehaviour("KEYBOARD", new KeyboardBehaviour());
}

BehaviourManager::~BehaviourManager()
{
	for (auto iter = m_behaviours.begin(); iter != m_behaviours.end(); iter++)
		delete iter->second;
	m_behaviours.clear();
	for (auto iter = m_activeBehaviours.begin(); iter != m_activeBehaviours.end(); iter++) {
		(*iter) = nullptr;
		delete (*iter);
	}
}

void BehaviourManager::Update(GameObject *object, float deltaTime)
{
	// version 1 for updates
	//for (auto iter = m_activeBehaviours.begin(); iter != m_activeBehaviours.end(); iter++) {
	//
	//	// if the vector is empty, do nothing
	//	if (m_activeBehaviours.size() != 0) {
	//
	//		// Check the location of all active obstacles in the game
	//
	//
	//
	//		// Update all behaviours that are active on the current state of the game
	//		(*iter)->Update(object, deltaTime);
	//
	//		// Receive the force input of all behaviours
	//		glm::vec2 Input = (*iter)->ReturnForce();
	//		// DEBUG: Testing force input
	//		object->ApplyForce(Input);
	//		//m_appliedForces.push_back(Input);
	//
	//		// If the behaviour has completed its task or 
	//		// is no longer active/needed, remove it.
	//		if (IsCompleted()) {
	//			(*iter) = nullptr;
	//			delete (*iter);
	//		}
	//	}
	//}

	// version 2 for updates
	if (m_activeBehaviours.size() != 0){
		std::vector <Behaviour*> tmp = m_activeBehaviours;

		while (!tmp.empty()) {

			if (tmp.empty() == true)
				break;

			tmp.back()->Update(object, deltaTime);
			glm::vec2 Input = tmp.back()->ReturnForce();
			object->ApplyForce(Input);
			tmp.pop_back();
		}
	}
	// Calculate the resultant force
	//for (auto iter = m_activeBehaviours.begin(); iter != m_activeBehaviours.end(); iter++) {
	//
	//}
}

void BehaviourManager::Draw(GameObject *object, aie::Renderer2D *renderer)
{
	if (IsDrawnByGameObject()) {
		for (auto iter = m_activeBehaviours.begin(); iter != m_activeBehaviours.end(); iter++) {
			(*iter)->Draw(object, renderer);
		}
	}
}

void BehaviourManager::PushBehaviour(const char* name, Behaviour *behaviour)
{
	auto iter = m_behaviours.find(name);

	if (iter != m_behaviours.end()) {
		// If a behaviour has been found with the name given, delete it
		delete iter->second;
	}
	// Apply the name given to the behaviour
	m_behaviours[name] = behaviour;
}

void BehaviourManager::SetBehaviour(const char* name)
{
	auto iter = m_behaviours.find(name);

	if (iter != m_behaviours.end()) {
		m_activeBehaviours.push_back(iter->second);
	} else {
		assert((iter != m_behaviours.end()) && name && " could not find behaviour with given name!");
	}
}

void BehaviourManager::SetMaxVelocity(float MaxSpeed)
{
	m_maxSpeed = MaxSpeed;
}

float BehaviourManager::GetMaxVelocity()
{
	return m_maxSpeed;
}

// Get the behaviour called according to its numerical key in the vector
Behaviour* BehaviourManager::GetBehaviour(const char* name)
{
	auto iter = m_behaviours.find(name);

	if (iter != m_behaviours.end()) {
		return iter->second;
	} else {
		assert((iter != m_behaviours.end()) && name && " could not find behaviours with given name!");
	}
}

void BehaviourManager::PopBackBehaviour()
{
	m_activeBehaviours.pop_back();
}

void BehaviourManager::ClearBehaviours()
{
	for (auto iter = m_activeBehaviours.begin(); iter != m_activeBehaviours.end(); iter++) {
		m_activeBehaviours.clear();
	}
}