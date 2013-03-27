#pragma once
#include "Entity.h"

class Spring;
class EntityManager
{
private:
	static EntityManager *instance;
public:
	static EntityManager* Instance();
	EntityManager(void);
	~EntityManager(void);

	void Initialise();

	float lastTimeStamp;
	list<Entity*> entities;
	list<Spring*> springs;
	Entity* EntityForID(int IDReq);
	void AddEntity(Entity*);
	void Update();
	void UpdateEntities();
	void ResolveSprings();
	void ResolveCollisions();
};
