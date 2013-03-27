#pragma once

#include "Entity.h"
class AsteroidFragment;

class Asteroid :
	public Entity
{
public:
	Asteroid(void);
	~Asteroid(void);

	virtual void Update(float deltaT);
	virtual string GetType();
	AsteroidFragment* FragmentForPosition(Vector2 position);

	list<AsteroidFragment *> asteroid;

};
