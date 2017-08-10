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

	Behaviour() : m_isOwned(true) { }
	virtual ~Behaviour() { }

	virtual void Update(GameObject * object, float deltaTime) { }
	virtual void Draw(GameObject *object, aie::Renderer2D *renderer) { }

	bool IsCompleted() { return m_isOwned; }
	void IsCompleted(bool isOwned) { m_isOwned = isOwned; }

	bool IsDrawnByGameObject() { return m_isDrawn; }
	void UpdateDrawnByGameObject(bool isDrawn) { m_isDrawn = isDrawn; }

	glm::vec2 ReturnForce() { return m_appliedForce; }
	void SetForce(glm::vec2 Input) { m_appliedForce = Input; }

protected:

	bool m_isOwned;
	bool m_isDrawn;
	glm::vec2 m_appliedForce;

private:
};