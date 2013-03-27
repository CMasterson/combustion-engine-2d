#pragma once
#include "entity.h"

class Player :
	public Entity
{
public:
	Player(void);
	~Player(void);
	virtual void Update(float deltaT);
	virtual string GetType();
private:
	void resolveInputs();

	float speed;
	Shape *laser;

};
