#include "precompiled.h"
#include "EntityManager.h"
#include "ShapeManager.h"
#include "Spring.h"
#include <Math.h>
EntityManager* EntityManager::instance = 0;
EntityManager* EntityManager::Instance()
{
	if(!instance)
		instance = new EntityManager();
	return instance;
}
EntityManager::EntityManager(void)
{
	lastTimeStamp = GetTickCount();
}

EntityManager::~EntityManager(void)
{
}
void EntityManager::Initialise()
{

}
void EntityManager::Update()
{
	//this->UpdateEntities();
}
void EntityManager::AddEntity(Entity* nEntity)
{
	if(EntityForID(nEntity->ID) == NULL)
	{
		this->entities.push_back(nEntity);
	}
}
Entity* EntityManager::EntityForID(int IDReq)
{
	if(this->entities.size() > 0)
	{
		list<Entity*>::iterator current;
		for(current = this->entities.begin();current != this->entities.end();current++)
		{
			if((*current)->ID == IDReq)
				return (*current);
		}
	}
	return NULL;
}
void EntityManager::UpdateEntities()
{
	/*list<Entity*>::iterator current;
	float deltaT = this->getDeltaT();
	for(current = entities.begin();current != entities.end();current++)
	{
		GetTickCount();
		(*current)->Update(deltaT/CLOCKS_PER_SEC);
	}
	*/
	
	this->ResolveSprings();
	
}

void EntityManager::ResolveSprings()
{	
	list<Spring*>::iterator currentSpring = this->springs.begin();

	for(;currentSpring != this->springs.end();currentSpring++)
	{
		if((*currentSpring)->Update() >  (*currentSpring)->breakForce)
		{			
			//this->springs.remove(*currentSpring);
		}
	}
	
}
void EntityManager::ResolveCollisions()
{
	list<Entity*>::iterator currentEnt = this->entities.begin();
	list<Entity*>::iterator testAgainst;

	for(;currentEnt != this->entities.end();currentEnt++)
	{
		testAgainst = currentEnt;
		for(testAgainst++;testAgainst != this->entities.end();testAgainst++)
		{
			Entity* current = (Entity*)(*currentEnt);
			Vector2 * pointOfCollision = SManager->ShapesAreColliding((*currentEnt),(*testAgainst));
			if(pointOfCollision != NULL)
			{//Collsion occoured
				
			}
		}
	}
}


