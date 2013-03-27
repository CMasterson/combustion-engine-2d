#pragma once
#include "entity.h"

class AsteroidFragment :
	public Shape
{
public:
	AsteroidFragment(void);
	~AsteroidFragment(void);

	AsteroidFragment	* Up,
						* Down,
						* Left,
						* Right;

	virtual void Update(float deltaT);
	virtual string GetType();
};
