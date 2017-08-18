#pragma once
#include "Behaviour.h"

class KeyboardBehaviour : public Behaviour
{
public:
	KeyboardBehaviour(int upkey = 0, int downkey = 0, int leftkey = 0, int rightkey = 0);
	virtual ~KeyboardBehaviour();

	virtual void Update(glm::vec2 Pos, glm::vec2 Vel, float deltaTime);

	int GetUpKey();
	int GetDownKey();
	int GetLeftKey();
	int GetRightKey();

	void SetUpKey(int key);
	void SetDownKey(int key);
	void SetLeftKey(int key);
	void SetRightKey(int key);

protected:

	float m_forceStrength;
	int m_upKey;
	int m_downKey;
	int m_leftKey;
	int m_rightKey;
private:
};