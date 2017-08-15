#include "BehaviourManager.h"
#include "ArrivalBehaviour.h"
#include "KeyboardBehaviour.h"
#include "SeekBehaviour.h"
#include "FollowPathBehaviour.h"
#include "WanderBehaviour.h"
#include "GameObject.h"
#include <assert.h>
#include <glm/vec2.hpp>

BehaviourManager::BehaviourManager()
{
	m_seek = new SeekBehaviour();
	m_arrival = new ArrivalBehaviour();
	m_wander = new WanderBehaviour();
	m_keyboard = new KeyboardBehaviour();
	//m_follow = new FollowPathBehaviour();
}

BehaviourManager::~BehaviourManager()
{
	
}

void BehaviourManager::Update(float deltaTime)
{
	m_seek->Update(deltaTime);
	m_arrival->Update(deltaTime);
	m_wander->Update(deltaTime);
	m_keyboard->Update(deltaTime);
	//m_follow->Update(deltaTime);

	SetForce(m_seek->ReturnForce());
	SetForce(m_arrival->ReturnForce());
	SetForce(m_wander->ReturnForce());
	SetForce(m_keyboard->ReturnForce());
	SetForce(m_follow->ReturnForce());
}

void BehaviourManager::Draw(aie::Renderer2D *renderer)
{
	m_seek->Draw(renderer);
	m_arrival->Draw(renderer);
	//m_follow->Draw(renderer);
	m_keyboard->Draw(renderer);
	m_wander->Draw(renderer);
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
	//m_follow->IsActive(false);
}

vec2 BehaviourManager::CalculateForce()
{
	return vec2();
}
