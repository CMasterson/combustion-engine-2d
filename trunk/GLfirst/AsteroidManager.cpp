#include "precompiled.h"
#include "AsteroidManager.h"
#include "Asteroid.h"
#include "AsteroidFragment.h"
#include "EntityManager.h"
#include "GameNodeManager.h"

AsteroidManager* AsteroidManager::instance = 0;

float randFloat(float);

AsteroidManager* AsteroidManager::Instance()
{
	if(!instance)
	{
		instance = new AsteroidManager();
	}
	return instance;	
}

AsteroidManager::AsteroidManager(void)
{
}

AsteroidManager::~AsteroidManager(void)
{
}
void AsteroidManager::Initialise()
{
}
void AsteroidManager::CreateAsteroid(Vector2 position)
{
	
	Asteroid * asteroid = new Asteroid();

	GNManager->RootNode()->AddChild(asteroid);

	this->Asteroids.push_back(asteroid);

	AsteroidFragment * first = new AsteroidFragment();
	first->position= position;

	asteroid->asteroid.push_back(first);

	AsteroidFragment * current = first;

	int numberOfTries = (rand() % MAX_NUM_TRIES)+ 1;

	bool done = false;
	while(!done)
	{
		if(current->Up == NULL)
		{
			SpawnFragmentAtPositionForAsteroid(current->position + Vector2(0,2) , asteroid);
		}
		if(current->Down == NULL)
		{
			SpawnFragmentAtPositionForAsteroid(current->position + Vector2(0,-2) , asteroid);
		}
		if(current->Left == NULL)
		{
			SpawnFragmentAtPositionForAsteroid(current->position + Vector2(-2,0) , asteroid);
		}
		if(current->Right == NULL)
		{
			SpawnFragmentAtPositionForAsteroid(current->position + Vector2(2,0) , asteroid);
		}

		if(!numberOfTries)
			done = true;
		else
		{
			numberOfTries--;
			current = this->GetRandomFragmentFromAsteroid(asteroid);
		}
	}
	int i;
	Vector2 meanPos = Vector2();
	list<AsteroidFragment *>::iterator iter = asteroid->asteroid.begin();
	for(i = 0;iter != asteroid->asteroid.end();i++, iter++)
	{
		meanPos = meanPos +	(*iter)->position; //* mass index of fragment
	}
	meanPos = meanPos/i;

	asteroid->position = meanPos;

	iter = asteroid->asteroid.begin();
	for(i = 0;iter != asteroid->asteroid.end();i++, iter++)
	{
		(*iter)->position = (*iter)->position - meanPos;
	}

	EManager->AddEntity(asteroid);

}
void AsteroidManager::SpawnFragmentAtPositionForAsteroid(Vector2 position, Asteroid * asteroid)
{
	int chance = (rand() % 100) + position.Distance(asteroid->asteroid.front()->position);
	if(chance < CHANCE_TO_SPAWN)
	{
		AsteroidFragment * fragment = new AsteroidFragment();
		fragment->position = position;
		ConnectFragmentToNeighbors(fragment, asteroid);
		asteroid->asteroid.push_back(fragment);
		this->Fragments.push_back(fragment);
		//asteroid->AddChild(fragment);
	}
}
void AsteroidManager::ConnectFragmentToNeighbors(AsteroidFragment * fragment, Asteroid * asteroid)
{
	
	fragment->Up = asteroid->FragmentForPosition(fragment->position + Vector2(0,2)); // Connect me to him
	if(fragment->Up)//Connect him to me
	{
		fragment->Up->Down = fragment;
		//create a Spring
	}
	fragment->Down = asteroid->FragmentForPosition(fragment->position + Vector2(0,-2)); // Connect me to him
	if(fragment->Down)//Connect him to me
	{
		fragment->Down->Up = fragment;

	}
	fragment->Left = asteroid->FragmentForPosition(fragment->position + Vector2(-2,0)); // Connect me to him
	if(fragment->Left)//Connect him to me
	{
		fragment->Left->Right = fragment;
	}
	fragment->Right = asteroid->FragmentForPosition(fragment->position + Vector2(2,0)); // Connect me to him
	if(fragment->Right)//Connect him to me
	{
		fragment->Right->Left = fragment;
	}
}
AsteroidFragment* AsteroidManager::GetRandomFragmentFromAsteroid(Asteroid * asteroid)
{
	list<AsteroidFragment *>::iterator Iter = asteroid->asteroid.begin();

	int newFrag = rand() % asteroid->asteroid.size();
	for(int i = 0; i < newFrag;i++)
	{
		Iter++;
	}

	if(Iter == asteroid->asteroid.end())
		return asteroid->asteroid.back();

	return *Iter;
}
