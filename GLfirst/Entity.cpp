#include "precompiled.h"
#include "Entity.h"

Entity::Entity(void)
{
	this->rotationalVelocity = 0;
	this->velocity = Vector2();
	this->force = Vector2();
	this->rotationalForce =0;
	this->updateable = true;
	this->mass = 1;
}

Entity::~Entity(void)
{
}
void Entity::Update(float deltaT)
{
	this->ResolveVelocityFromForces();
	Vector2 movement = Vector2(this->velocity.X*deltaT,this->velocity.Y*deltaT);
	this->position = this->position + movement;

	this->ResolveRVelocityFromRForces();
	this->rotation += this->rotationalVelocity * deltaT;
	if(this->rotation > MAX_ROTATION)
		this->rotation -= MAX_ROTATION;

	this->force = Vector2();
	this->rotationalForce = 0;
	
}
void Entity::ResolveVelocityFromForces()
{
	//Euler, is temp, shut up!
	this->velocity = this->velocity + this->force/this->mass;
}
void Entity::ResolveRVelocityFromRForces()
{
	//Euler, is temp, shut up, again!
	this->rotationalVelocity = this->rotationalVelocity + this->rotationalForce/this->mass;
}

void Entity::ApplyForceWithFriction(Vector2 forceLocation, Vector2 forceToApply, float friction)
{
	Vector2 centerToForce = forceLocation-this->GetWorldPosition();
	float distanceForceToCenter = centerToForce.Length();

	if(distanceForceToCenter != 0)
	{
		//Resolve as normal
		float forceToCenterAngle = centerToForce.AngleRad();
		Vector2 rotatedForce = forceToApply.Rotate(-forceToCenterAngle);

		this->force = this->force + Vector2(rotatedForce.X,0).Rotate(forceToCenterAngle);
		this->rotationalForce += rotatedForce.Y*distanceForceToCenter;	
	}
	else
	{
		//Apply straight to linear force
		this->force = this->force + forceToApply;
	}
}
void Entity::ApplyForce(Vector2 forceLocation, Vector2 forceToApply)
{
	this->ApplyForceWithFriction(forceLocation, forceToApply, 0);
}
string Entity::GetType()
{
	return "ENTITY";
}