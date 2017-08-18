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

void BehaviourManager::Update(glm::vec2 Pos, glm::vec2 Vel, float deltaTime)
{
	SetDrawActive();

	if (m_seek->IsActive())
		m_seek->Update(Pos, Vel, deltaTime);
	if (m_arrival->IsActive())
		m_arrival->Update(Pos, Vel, deltaTime);
	if (m_wander->IsActive())
		m_wander->Update(Pos, Vel, deltaTime);
	if (m_keyboard->IsActive())
		m_keyboard->Update(Pos, Vel, deltaTime);
	//m_follow->Update(deltaTime);

	SetForce(CalculateForce());
}

void BehaviourManager::Draw(aie::Renderer2D *renderer)
{
	if (m_seek->IsDrawnByGameObject())
		m_seek->Draw(renderer);
	if (m_arrival->IsDrawnByGameObject())
		m_arrival->Draw(renderer);
	if (m_wander->IsDrawnByGameObject())
		m_wander->Draw(renderer);
	if (m_keyboard->IsDrawnByGameObject())
		m_keyboard->Draw(renderer);
	//m_follow->Draw(renderer);
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

void BehaviourManager::SetDrawActive()
{
	if (m_seek->IsActive())
		m_seek->IsDrawnByGameObject(true);
	else
		m_seek->IsDrawnByGameObject(false);
	if (m_arrival->IsActive())
		m_arrival->IsDrawnByGameObject(true);
	else
		m_arrival->IsDrawnByGameObject(false);
	if (m_wander->IsActive())
		m_wander->IsDrawnByGameObject(true);
	else
		m_wander->IsDrawnByGameObject(false);
	if (m_keyboard->IsActive())
		m_keyboard->IsDrawnByGameObject(true);
	else
		m_keyboard->IsDrawnByGameObject(false);
}

void BehaviourManager::SetDrawInactive()
{
	m_seek->IsDrawnByGameObject(false);
	m_arrival->IsDrawnByGameObject(false);
	m_wander->IsDrawnByGameObject(false);
	m_keyboard->IsDrawnByGameObject(false);
}

vec2 BehaviourManager::CalculateForce()
{
	vec2 m_steeringForce;
	
	m_steeringForce += (m_seek->IsActive())?_seek->ReturnForce();
	if (m_keyboard->IsActive())
		m_steeringForce += m_keyboard->ReturnForce();
	if (m_wander->IsActive())
		m_steeringForce += m_wander->ReturnForce();

	//SetForce(m_follow->ReturnForce());
	return m_steeringForce;
}

void BehaviourManager::SetSeekTarget(glm::vec2(Target))
{
	m_seek->SetSeekTarget(Target);
}

vec2 BehaviourManager::SetArrivalVelocity()
{
	if (m_arrival->IsActive())
		return m_arrival->GetObjectVelocity();
	else
		return GetObjectVelocity();
}