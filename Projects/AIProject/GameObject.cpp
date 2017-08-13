#include "GameObject.h"
#include "BehaviourManager.h"
#include <Texture.h>
#include <Renderer2D.h>
#include <glm\glm.hpp>
#include <iostream>
#include <assert.h>

#define _USE_MATH_DEFINES
#include <math.h>

GameObject::GameObject(aie::Texture *tex) :
	m_tex(tex),
	m_friction(1.0f),
	m_rotation(0.0f),
	m_size(20.f),
	isDrawn(true),
	m_colour(WHITE)
{
	m_steeringmanager = new BehaviourManager();
}

GameObject::~GameObject()
{
	delete m_steeringmanager;
}

void GameObject::Update(float deltaTime)
{
	m_steeringmanager->Update(this, deltaTime);
	SimulatePhysics(deltaTime);
}

void GameObject::Draw(aie::Renderer2D * renderer)
{
	glm::vec2 targetHeading = m_position + m_velocity;

	if (isDrawn){
		renderer->setRenderColour(ORANGE);
		renderer->drawLine(m_position.x, m_position.y, targetHeading.x, targetHeading.y, 2.0f);
		renderer->setRenderColour(WHITE);
	}

	renderer->setRenderColour(m_colour);
	if (m_tex == nullptr) {
		renderer->setRenderColour(m_colour);
		renderer->drawCircle(m_position.x, m_position.y, 8);
	} else {
		renderer->setRenderColour(m_colour);
		renderer->drawSprite(m_tex, m_position.x, m_position.y, m_size, m_size, m_rotation);
		renderer->setRenderColour(WHITE);
	}
}

void GameObject::SimulatePhysics(float deltaTime)
{
	ApplyForce(m_friction * -m_velocity);
	m_velocity += m_acceleration * deltaTime;
	m_position += m_velocity * deltaTime;
	m_acceleration = glm::vec2(0, 0);

	m_rotation = atan2f(m_velocity.y, m_velocity.x);
}

void GameObject::ApplyForce(const glm::vec2 & force)
{
	m_acceleration += force;
}

bool GameObject::GetDraw()
{
	return isDrawn;
}

float GameObject::GetSize()
{
	return m_size;
}

const glm::vec2 & GameObject::GetPosition()
{
	return m_position;
}

const glm::vec2 & GameObject::GetVelocity()
{
	return m_velocity;
}

float GameObject::GetFriction()
{
	return m_friction;
}

ColourPalette GameObject::GetColour()
{
	return m_colour;
}

void GameObject::SetTexture(aie::Texture *tex)
{
	m_tex = tex;
}

void GameObject::SetPosition(const glm::vec2 &pos)
{
	m_position = pos;
}

void GameObject::SetVelocity(const glm::vec2 &vel)
{
	m_velocity = vel;
}

void GameObject::SetFriction(float friction)
{
	m_friction = friction;
}

void GameObject::SetDraw(bool draw)
{
	isDrawn = draw;
}

void GameObject::SetSize(float size)
{
	m_size = size;
}

void GameObject::SetColour(int id)
{
	switch (id)
	{
	case GREEN:		m_colour = GREEN;		break;
	case TEAL:		m_colour = TEAL;		break;
	case PURPLE:	m_colour = PURPLE;		break;
	case PINK:		m_colour = PINK;		break;
	case BLUE:		m_colour = BLUE;		break;
	case RED:		m_colour = RED;			break;
	case YELLOW:	m_colour = YELLOW;		break;
	case ORANGE:	m_colour = ORANGE;		break;
	case WHITE:		m_colour = WHITE;		break;
	case DARKBLUE:	m_colour = DARKBLUE;	break;
	default:								break;
	}
}