#include "precompiled.h"
#include "Spring.h"
#include "Entity.h"

Spring::Spring(void)
{
}

Spring::~Spring(void)
{
	start = NULL;
	end = NULL;
}
float Spring::Update()
{
	Vector2 i = this->end->GetWorldPosition() - this->start->GetWorldPosition();
	i.Normalise();

	Vector2 idealEndPoint = (i*this->idealLength) + this->start->GetWorldPosition();

	Vector2 vectorDisplacement = this->end->GetWorldPosition() - idealEndPoint; //Gaffers X
	Vector2 relativeVelocity = this->start->velocity - this->end->velocity; // Gaffers V

	Vector2 theForce = (vectorDisplacement*this->tightness - relativeVelocity*this->CoDamping)*-1;

	this->start->force = this->start->force - theForce/2;
	this->end->force = this->end->force + theForce/2;

	return theForce.Length();
}
