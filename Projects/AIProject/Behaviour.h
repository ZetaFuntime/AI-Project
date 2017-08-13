#pragma once
#include <glm/vec2.hpp>

class GameObject;

namespace aie
{
	class Renderer2D;
};

class Behaviour
{
public:

	Behaviour() : m_Active(false) { }
	virtual ~Behaviour() { }

	virtual void Update(GameObject * object, float deltaTime) { }
	virtual void Draw(GameObject *object, aie::Renderer2D *renderer) { }

	bool IsActive() { return m_Active; }
	void IsActive(bool isActive) { m_Active = isActive; }

	bool IsDrawnByGameObject() { return m_isDrawn; }
	void UpdateDrawnByGameObject(bool isDrawn) { m_isDrawn = isDrawn; }

	glm::vec2 ReturnForce() { return m_appliedForce; }
	void SetForce(glm::vec2 Input) { m_appliedForce = Input; }

	float GetForceStrength() { return m_forceStrength; }
	void SetForceStrength(float strength) { m_forceStrength = strength; }

protected:

	float m_forceStrength;
	bool m_Active;
	bool m_isDrawn;
	glm::vec2 m_appliedForce;

private:
};