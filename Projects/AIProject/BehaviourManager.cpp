#include "BehaviourManager.h"
#include <assert.h>

BehaviourManager::BehaviourManager()
{

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
	for (auto iter = m_activeBehaviours.begin(); iter != m_activeBehaviours.end(); iter++) {

		if (m_activeBehaviours.size() != 0)
			(*iter)->Update(object, deltaTime);

		// If the behaviour has completed its task or 
		// is no longer active/needed, remove it.

		if (IsCompleted())
		{
			(*iter) = nullptr;
			delete (*iter);
		}
	}
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
	}
	else {
		assert((iter != m_behaviours.end()) && name && " could not find behaviour with given name!");
	}
}

// Get the behaviour called according to its numerical key in the vector
Behaviour* BehaviourManager::GetBehaviour()
{

}