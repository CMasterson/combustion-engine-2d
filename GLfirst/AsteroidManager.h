#pragma once

#define MAX_NUM_TRIES 99
#define CHANCE_TO_SPAWN 80

class AsteroidFragment;
class Asteroid;

class AsteroidManager
{
private:
	static AsteroidManager * instance;
public:
	static AsteroidManager* Instance();
	void Initialise();
	AsteroidManager(void);
	~AsteroidManager(void);
	void CreateAsteroid(Vector2 Position);

	void SpawnFragmentAtPositionForAsteroid(Vector2 position, Asteroid * asteroid);
	void ConnectFragmentToNeighbors(AsteroidFragment * fragment, Asteroid * asteroid);
	AsteroidFragment* GetRandomFragmentFromAsteroid(Asteroid * asteroid);
	
	list<Asteroid*> Asteroids;
	list<AsteroidFragment *> Fragments;
};

