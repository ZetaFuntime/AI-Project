#include "ArrivalBehaviour.h"
#include "GameObject.h"
#include <Renderer2D.h>
#include <glm\glm.hpp>
#include <iostream>

ArrivalBehaviour::ArrivalBehaviour() :
	Behaviour(),
	m_slowingRadius(100.f),
	m_targetRadius(10.f),
	m_forceStrength(100.f)
{

}
ArrivalBehaviour::~ArrivalBehaviour()
{

}

void ArrivalBehaviour::Update(glm::vec2 Pos, glm::vec2 Vel, float deltaTime)
{
	float lastDistanceToTarget = glm::length(m_targetPosition - m_lastPosition);
	float distanceToTarget = glm::length(m_targetPosition - Pos);

	// Have we just entered the target radius
	if (m_onTargetRadiusEnter && lastDistanceToTarget > m_targetRadius && distanceToTarget <= m_targetRadius)
		m_onTargetRadiusEnter();

	// If the agent is outside the slowing radius, don't slow it down
	float slowRatio = (distanceToTarget < m_slowingRadius) ? (distanceToTarget / (m_slowingRadius)) : 1;

	// Calculate the current Angle to the destination compared to
	// the current angle of the agent
	glm::vec2 currentDir = glm::normalize(Vel);													
	glm::vec2 currentDirToTarget = glm::normalize(m_targetPosition - Pos);						

	float currentAngle = atan2f(currentDir.y, currentDir.x);
	float currentAngleToTarget = atan2f(currentDirToTarget.y, currentDirToTarget.x);

	// Adjust the angle being input to the apply force by a small
	// amount until it is close enough to the correct angle to
	// be equaled to it (NOTE: because of how radians work in bootstrap, this will not work within certain ranges of the angle)
	currentAngle =	(currentAngleToTarget - currentAngle < -0.1f) ? currentAngle - 0.1f :
					(currentAngleToTarget - currentAngle > 0.1f) ? currentAngle + 0.1f :
					currentAngleToTarget;
					
	// Apply a constant force to the agent which is scaled down as the
	// agent gets closer to the destination.
	glm::vec2 appliedDirToTarget = glm::vec2 (cos(currentAngle)* slowRatio * m_forceStrength,sin(currentAngle)*slowRatio *m_forceStrength);								

	SetForce(appliedDirToTarget);

	m_lastPosition = Pos;
}

void ArrivalBehaviour::Draw(aie::Renderer2D *renderer)
{
	if (IsDrawnByGameObject()) {
		renderer->drawBox(m_targetPosition.x, m_targetPosition.y, 10.f, 10.f);
		renderer->setRenderColour(1.0f, 1.0f, 1.0f, 0.1f);
		renderer->drawCircle(m_targetPosition.x, m_targetPosition.y, m_slowingRadius);
		renderer->setRenderColour(1.0f, 1.0f, 1.0f, 0.2f);
		renderer->drawCircle(m_targetPosition.x, m_targetPosition.y, m_targetRadius);
		renderer->setRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

const glm::vec2 &ArrivalBehaviour::GetTarget()
{
	return m_targetPosition;
}

void ArrivalBehaviour::SetTarget(const glm::vec2 &target)
{
	m_targetPosition = target;
}

float ArrivalBehaviour::GetSlowingRadius()
{
	return m_slowingRadius;
}

void ArrivalBehaviour::SetSlowingRadius(float radius)
{
	m_slowingRadius = radius;
}

void ArrivalBehaviour::OnTargetRadiusEnter(std::function< void() > func)
{
	m_onTargetRadiusEnter = func;
}