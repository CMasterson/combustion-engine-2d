#include "precompiled.h"
#include "MouseState.h"

MouseState::MouseState(Vector2 Position, Vector2 Velocity, int LMBState, int RMBState, float timeStamp)
{
	this->position = Position;
	this->velocity = Velocity;
	this->leftMouseButtonState = LMBState;
	this->rightMouseButtonState = RMBState;
	this->timeStamp = timeStamp;
}
MouseState::MouseState(void)
{}
MouseState::~MouseState(void)
{}
