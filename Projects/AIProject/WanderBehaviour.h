#pragma once

#include "Behaviour.h"
#include <glm\vec2.hpp>

class WanderBehaviour : public Behaviour
{
public:

	WanderBehaviour();
	virtual ~WanderBehaviour();

	virtual void Update(GameObject *object, float deltaTime);
	virtual void Draw(GameObject * object, aie::Renderer2D *renderer);

protected:

	float m_changeTimePassed;
	float m_wanderAngle;

	glm::vec2 m_circleCenter;
	glm::vec2 m_displacement;
	glm::vec2 wanderForce;
	float m_circleRadius;
	float m_forceStrength;

private:

	glm::vec2 SetAngle(GameObject * object, float strength, float wanderAngle);
};