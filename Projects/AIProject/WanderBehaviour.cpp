#include "WanderBehaviour.h"
#include "GameObject.h"
#include <glm\vec2.hpp>
#include <glm\glm.hpp>
#include <math.h>
#include <iostream>
#include <Renderer2D.h>

WanderBehaviour::WanderBehaviour() :
	Behaviour(),
	m_circleRadius(100.f),
	m_forceStrength(100.f),
	m_changeTimePassed(0.f)
{
	m_wanderAngle = ((rand() % 618) - 315) / 100.f;
}

WanderBehaviour::~WanderBehaviour()
{

}

// --------------------------------------------------------------
// The update calculates the wander direction to apply to the force
// given to the unit. There are two that were made, but i applied
// the one that was more similar to the calculations used by the
// website aaron gave to the class.
// --------------------------------------------------------------

void WanderBehaviour::Update(GameObject *object, float deltaTime)
{
#pragma region Method 1
	// -----------------------------------------------------------
	// Version 1 - Wandering Algorithm based on random direction
	//			   and force.
	// -----------------------------------------------------------

	//m_changetimePassed += deltaTime;
	//m_applytimePassed += deltaTime;
	//if (m_changetimePassed > m_changeThreshold)
	//{
	//
	//	float prevAngle = m_wanderAngle;
	//	// If the time threshold has been passed, randomise force, 
	//	// time threshold and friction values
	//	m_appliedForce = (rand() % 100) + 100;
	//	m_wanderAngle = prevAngle + ((rand() % 314) - 158)/100.f;
	//	std::cout << m_wanderAngle << std::endl;
	//	m_changeThreshold = ((rand() % 50) / 100.f);
	//	
	//	m_wanderVector = SetAngle(m_appliedForce, m_wanderAngle);
	//	m_changetimePassed = 0;
	//}
	//
	//if (m_applytimePassed > m_timeThreshold) {
	//	object->ApplyForce(m_wanderVector);
	//	m_applytimePassed = 0;
	//}
#pragma endregion

#pragma region Method 2
	// ----------------------------------------------------------
	// Version 2 - Wandering algorithm based on random normalised
	//			   vector and randomised displacement forces
	// ----------------------------------------------------------

	m_changeTimePassed += deltaTime;
	
	m_circleCenter = glm::normalize(object->GetVelocity())*m_forceStrength;

	// Every 0.5 second count, apply the changed direction.
	// Change made to make the 'wander' appear more believable
	if (m_changeTimePassed > 0.5f)
	{
		glm::vec2 currentDir = glm::normalize(object->GetVelocity());
		float currentAngle = atan2f(currentDir.y, currentDir.x);
		m_wanderAngle = ((rand() % 314) - 158) / 100.f;
		m_displacement = SetAngle(object, m_circleRadius, m_wanderAngle + currentAngle);

		wanderForce = m_circleCenter + m_displacement;
		m_changeTimePassed = 0.f;
	}

	// Update the force for what is being used
	SetForce(wanderForce);

#pragma endregion
}

void WanderBehaviour::Draw(GameObject * object, aie::Renderer2D * renderer)
{
	if (IsDrawnByGameObject()) {
		glm::vec2 agentPos = object->GetPosition();
		glm::vec2 wanderForce = m_circleCenter + m_displacement;

		renderer->setRenderColour(1.0f, 1.0f, 1.0f, 0.25f);
		renderer->drawCircle(agentPos.x + m_circleCenter.x, agentPos.y + m_circleCenter.y, m_circleRadius);

		renderer->setRenderColour(0.f, 0.f, 0.f, 0.5f);
		renderer->drawCircle(agentPos.x + m_circleCenter.x, agentPos.y + m_circleCenter.y, m_circleRadius - 5.f);

		renderer->setRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
		renderer->drawLine(agentPos.x, agentPos.y, agentPos.x + m_circleCenter.x, agentPos.y + m_circleCenter.y);
		renderer->drawLine(agentPos.x, agentPos.y, agentPos.x + wanderForce.x, agentPos.y + wanderForce.y);
	}
}

glm::vec2 WanderBehaviour::SetAngle(GameObject * object, float strength, float wanderAngle)
{
	glm::vec2 wanderVector;
	wanderVector.x = strength * cos(wanderAngle);
	wanderVector.y = strength * sin(wanderAngle);
	return wanderVector;
}