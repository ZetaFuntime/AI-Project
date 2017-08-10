#pragma once

#include "Behaviour.h"

// Note: this is a temporary class to be called when the agent is called
//		 to do "nothing", so that the vector holding all behaviours is never
//		 actually empty and won't break the program

class IdleBehaviour : public Behaviour
{
public:
	IdleBehaviour();
	~IdleBehaviour();

	virtual void Update(GameObject *object, float deltaTime);
	virtual void Draw(GameObject *object, aie::Renderer2D *renderer);

private:
protected:
};