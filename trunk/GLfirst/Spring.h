#pragma once
class Entity;
class Spring
{
public:
	Spring(void);
	~Spring(void);

	float Update();
	Entity* start;
	Entity* end;
	float tightness;
	float CoDamping;
	float idealLength;
	float breakForce;
};
