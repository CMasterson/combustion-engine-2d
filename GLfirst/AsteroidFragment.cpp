#include "precompiled.h"
#include "AsteroidFragment.h"
#include "TextureManager.h"

AsteroidFragment::AsteroidFragment(void)
{
	this->Up = NULL;
	this->Down = NULL;
	this->Left = NULL;
	this->Right = NULL;

	this->vertices.push_back(Vector2(-1,1));
	this->vertices.push_back(Vector2(1,1));
	this->vertices.push_back(Vector2(1,-1));
	this->vertices.push_back(Vector2(-1,-1));

	this->texture = TManager->TextureForName("fragment1.tga");
}

AsteroidFragment::~AsteroidFragment(void)
{
}

void AsteroidFragment::Update(float deltaT)
{
	//UpdateHerePlx
}
string AsteroidFragment::GetType()
{
	return "ASTEROIDFRAGMENT";
}