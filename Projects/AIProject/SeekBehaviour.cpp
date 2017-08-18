#include "SeekBehaviour.h"
#include "GameObject.h"
#include <Renderer2D.h>
#include <glm\vec2.hpp>
#include <glm\glm.hpp>
#include <iostream>

SeekBehaviour::SeekBehaviour() : 
	Behaviour(),
	m_withinInRadius(false),
	m_withinOutRadius(false),
	m_forceStrength(100.f),
	m_innerRadius(20.f),
	m_outerRadius(100.f)
{
	
}

SeekBehaviour::~SeekBehaviour()
{

}

void SeekBehaviour::Update(glm::vec2 Pos, glm::vec2 Vel, float deltaTime)
{
	glm::vec2 InputForce;
	float lastDistanceToTarget = glm::length(m_targetPosition - m_lastPosition);
	float distanceToTarget = glm::length(m_targetPosition - Pos);

	if (glm::length(m_targetPosition - Pos) < m_innerRadius)
		m_withinInRadius = true;
	else if (m_outerRadius < glm::length(m_targetPosition - Pos) > m_innerRadius)
		m_withinOutRadius = true;
	else if (glm::length(m_targetPosition - Pos) > m_outerRadius){
		m_withinInRadius = false;
		m_withinOutRadius = false;
	}


	InputForce = glm::normalize(m_targetPosition - Pos) * m_forceStrength;

	SetForce(InputForce);
	m_lastPosition = Pos;

	if (m_withinInRadius)
		IsActive(false);
}

void SeekBehaviour::Draw(aie::Renderer2D *renderer)
{
	if (IsDrawnByGameObject()) {
		renderer->drawBox(m_targetPosition.x, m_targetPosition.y, 10.f, 10.f);

		renderer->setRenderColour(1.0f, 1.0f, 1.0f, 0.5f);
		renderer->drawCircle(m_targetPosition.x, m_targetPosition.y, m_innerRadius);

		renderer->setRenderColour(1.0f, 1.0f, 1.0f, 0.1f);
		renderer->drawCircle(m_targetPosition.x, m_targetPosition.y, m_outerRadius);

		renderer->setRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

const glm::vec2 &SeekBehaviour::GetTarget()
{
	return m_targetPosition;
}

void SeekBehaviour::SetSeekTarget(const glm::vec2 &target)
{
	m_targetPosition = target;
}

void SeekBehaviour::SetPredictionTiming(float timing)
{
	m_predictionTiming = timing;
}

float SeekBehaviour::GetPredictionTIming()
{
	return m_predictionTiming;
}

void SeekBehaviour::SetPursueTarget(GameObject *object, glm::vec2 targetVelocity)
{
	m_targetPosition = (targetVelocity - object->GetPosition())*m_predictionTiming;
}

void SeekBehaviour::SetForceStrength(float strength)
{
	m_forceStrength = strength;
}

float SeekBehaviour::GetForceStrength()
{
	return m_forceStrength;
}

void SeekBehaviour::SetInnerRadius(float radius)
{
	m_innerRadius = radius;
}

float SeekBehaviour::GetInnerRadius()
{
	return m_innerRadius;
}

void SeekBehaviour::SetOuterRadius(float radius)
{
	m_outerRadius = radius;
}

float SeekBehaviour::GetOuterRadius()
{
	return m_outerRadius;
}
