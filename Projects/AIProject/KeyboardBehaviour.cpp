#include "KeyboardBehaviour.h"
#include <Input.h>
#include "GameObject.h"

KeyboardBehaviour::KeyboardBehaviour(int upkey, int downkey, int leftkey, int rightkey) :
	Behaviour(),
	m_upKey(upkey),
	m_downKey(downkey),
	m_leftKey(leftkey),
	m_rightKey(rightkey)
{
	m_forceStrength = 100.f;
	if (upkey == 0) m_upKey = aie::INPUT_KEY_W;
	if (downkey == 0) m_downKey = aie::INPUT_KEY_S;
	if (leftkey == 0) m_leftKey = aie::INPUT_KEY_A;
	if (rightkey == 0) m_rightKey = aie::INPUT_KEY_D;
}

KeyboardBehaviour::~KeyboardBehaviour()
{
	
}

void KeyboardBehaviour::Update(float deltaTime)
{

	glm::vec2 InputForce;

	if (aie::Input::getInstance()->isKeyDown(m_upKey))
		InputForce += (glm::vec2(0, m_forceStrength));
	if (aie::Input::getInstance()->isKeyDown(m_downKey))
		InputForce += (glm::vec2(0, -m_forceStrength));
	if (aie::Input::getInstance()->isKeyDown(m_leftKey))
		InputForce += (glm::vec2(-m_forceStrength, 0));
	if (aie::Input::getInstance()->isKeyDown(m_rightKey))
		InputForce += (glm::vec2(m_forceStrength, 0));

	SetForce(InputForce);
}

int KeyboardBehaviour::GetUpKey()
{
	return m_upKey;
}

int KeyboardBehaviour::GetDownKey()
{
	return m_downKey;
}

int KeyboardBehaviour::GetLeftKey()
{
	return m_leftKey;
}

int KeyboardBehaviour::GetRightKey()
{
	return m_rightKey;
}

void KeyboardBehaviour::SetUpKey(int key)
{
	m_upKey = key;
}

void KeyboardBehaviour::SetDownKey(int key)
{
	m_downKey = key;
}

void KeyboardBehaviour::SetLeftKey(int key)
{
	m_leftKey = key;
}

void KeyboardBehaviour::SetRightKey(int key)
{
	m_rightKey = key;
}
