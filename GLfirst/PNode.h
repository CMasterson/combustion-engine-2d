#pragma once

class Vector2;
class PNode
{
public:
	PNode(void);
	~PNode(void);
	
	Vector2 position,
			velocity,
			forces;
	float mass;


};
