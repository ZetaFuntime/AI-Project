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
	m_seek = new SeekBehaviour();
	m_arrival = new ArrivalBehaviour();
	m_wander = new WanderBehaviour();
	m_keyboard = new KeyboardBehaviour();
	m_follow = new FollowPathBehaviour();
}

BehaviourManager::~BehaviourManager()
{
	
}

void BehaviourManager::Update(GameObject *object, float deltaTime)
{
	m_seek->Update(object, deltaTime);
	m_arrival->Update(object, deltaTime);
	m_wander->Update(object, deltaTime);
	m_keyboard->Update(object, deltaTime);
	m_follow->Update(object, deltaTime);
}

void BehaviourManager::Draw(GameObject *object, aie::Renderer2D *renderer)
{
	m_seek->Draw(object, renderer);
	m_arrival->Draw(object, renderer);
	m_follow->Draw(object, renderer);
	m_keyboard->Draw(object, renderer);
	m_wander->Draw(object, renderer);
}

void BehaviourManager::SetMaxVelocity(float MaxSpeed)
{
	m_maxSpeed = MaxSpeed;
}

float BehaviourManager::GetMaxVelocity()
{
	return m_maxSpeed;
}

//void BehaviourManager::GetEntityData(GameObject* entity)
//{
//	Entity data;
//	data.Pos = entity->GetPosition();
//	data.Vel = entity->GetVelocity();
//
//	m_entitydata.push_back(data);
//}

void BehaviourManager::SetActive(Modes mode)
{
	switch (mode)
	{
	case KEYBOARD:		m_keyboard->IsActive(true);	break;
	case SEEK:			m_seek->IsActive(true);		break;
	case ARRIVAL:		m_arrival->IsActive(true);	break;
	case WANDER:		m_wander->IsActive(true);	break;
	case FOLLOWPATH:	m_follow->IsActive(true);	break;
	default:										break;
	}
}

void BehaviourManager::SetInactive()
{
	m_keyboard->IsActive(false);
	m_seek->IsActive(false);
	m_arrival->IsActive(false);
	m_wander->IsActive(false);
	m_follow->IsActive(false);
}
