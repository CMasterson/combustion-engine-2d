#include "precompiled.h"
#include "Asteroid.h"
#include "AsteroidFragment.h"

//==
#include "InputListener.h"

Asteroid::Asteroid(void)
{
	this->visible = false;
}

Asteroid::~Asteroid(void)
{
}
AsteroidFragment* Asteroid::FragmentForPosition(Vector2 position)
{
	list<AsteroidFragment*>::iterator current = this->asteroid.begin();

	while(current != this->asteroid.end())
	{
		if ((*current)->position == position )
			return *current;
		else
			current ++;
	}

	return NULL;
}
void Asteroid::Update(float deltaT)
{
	Entity::Update(deltaT);
}
string Asteroid::GetType()
{
	return "ASTEROID";
}