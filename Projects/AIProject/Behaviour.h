#pragma once
#include <glm/vec2.hpp>

class GameObject;

namespace aie
{
	class Renderer2D;
};

struct data
{
	glm::vec2 Vel;
	glm::vec2 Pos;
};

class Behaviour
{
public:

	Behaviour() : m_Active(false), m_isDrawn(false) { }
	virtual ~Behaviour() { }

	virtual void Update(glm::vec2 Pos, glm::vec2 Vel,float deltaTime) { }
	virtual void Draw(aie::Renderer2D *renderer) { }

	bool IsActive() { return m_Active; }
	void IsActive(bool isActive) { m_Active = isActive; }

	bool IsDrawnByGameObject() { return m_isDrawn; }
	void IsDrawnByGameObject(bool isDrawn) { m_isDrawn = isDrawn; }

	glm::vec2 ReturnForce() { return m_appliedForce; }
	void SetForce(glm::vec2 Input) { m_appliedForce = Input; }

	float GetForceStrength() { return m_forceStrength; }
	void SetForceStrength(float strength) { m_forceStrength += strength; }

	void SetObjectPosition(glm::vec2 Pos) { m_Pos = Pos; }
	void SetObjectVelocity(glm::vec2 Vel) { m_Vel = Vel; }

	glm::vec2 GetObjectVelocity() {return m_Vel; }
	glm::vec2 GetObjectPosition() {return m_Pos; }

protected:

	float m_forceStrength;
	bool m_Active;
	bool m_isDrawn;
	glm::vec2 m_appliedForce;
	glm::vec2 m_Vel;
	glm::vec2 m_Pos;

private:
};