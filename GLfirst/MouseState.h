#pragma once

class MouseState
{
public:
	MouseState(Vector2 Position, Vector2 Velocity, int LMBState, int RMBState, float timeStamp);
	MouseState(void);
	~MouseState(void);
	Vector2 position;
	Vector2 velocity;
	int leftMouseButtonState;
	int rightMouseButtonState;
	int leftMouseButtonStateTime;
	int rightMouseButtonStateTime;
	int timeStamp;
};
