#pragma once

#include "Vector2.h"
#include "Shape.h"

class Entity : public Shape
{
private:
	
public:
	Entity(void);
	~Entity(void);

	Vector2 velocity;
	Vector2 force;
	float rotationalForce;
	
	float mass;
	float rotationalVelocity;

	float rotationalFriction;
	float linearFriction;

	bool updateable;

	virtual void Update(float deltaT);
	virtual string GetType();

	void ResolveVelocityFromForces();
	void ResolveRVelocityFromRForces();
	void ApplyForceWithFriction(Vector2 forceLocation, Vector2 forceDirection, float friction);
	void ApplyForce(Vector2 forceLocation, Vector2 forceDirection);

	
};
