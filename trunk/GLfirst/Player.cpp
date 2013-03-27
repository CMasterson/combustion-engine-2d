#include "precompiled.h"
#include "Player.h"
#include "InputListener.h"
#include "TextureManager.h"

#include "GameNodeManager.h"

Player::Player(void)
{
	this->vertices.push_back(Vector2(-1,1));
	this->vertices.push_back(Vector2(1,1));
	this->vertices.push_back(Vector2(1,-1));
	this->vertices.push_back(Vector2(-1,-1));

	this->position = Vector2(1,1);

	this->texture = TManager->TextureForName("ship.tga");
	this->Scale(Vector2(2,2));

	this->speed = 0;

	this->laser = new Shape(Vector2(),"laser.tga");
	this->AddChild(this->laser);

	this->laser->vertices.push_back(Vector2(-1,1));
	this->laser->vertices.push_back(Vector2(1,1));
	this->laser->vertices.push_back(Vector2(1,-1));
	this->laser->vertices.push_back(Vector2(-1,-1));

	this->laser->Scale(Vector2(0.3,20));
	this->laser->position = Vector2(0,20);
	this->laser->visible = false;
	this->laser->strechTexture = true;
}

Player::~Player(void)
{
}
void Player::Update(float deltaT)
{
	this->resolveInputs();

	rotation = (this->position - IListener->GetMousePos()).AngleDeg()+90;

	Entity::Update(deltaT);
}
void Player::resolveInputs()
{

	if(IListener->keyForKeyName("W")->keyState == KEY_STATE_HELD )
	{
		this->force = this->force + Vector2(0,1);
	}
	if(IListener->keyForKeyName("S")->keyState == KEY_STATE_HELD )
	{
		this->force = this->force + Vector2(0,-1);
	}
	if(IListener->keyForKeyName("A")->keyState == KEY_STATE_HELD )
	{
		this->force = this->force + Vector2(-1,0);
	}
	if(IListener->keyForKeyName("D")->keyState == KEY_STATE_HELD )
	{
		this->force = this->force + Vector2(1,0);
	}

	if(IListener->keyForKeyName("W")->keyState == KEY_STATE_INACTIVE &&
		IListener->keyForKeyName("A")->keyState == KEY_STATE_INACTIVE &&
		IListener->keyForKeyName("S")->keyState == KEY_STATE_INACTIVE &&
		IListener->keyForKeyName("D")->keyState == KEY_STATE_INACTIVE )

		this->force = this->force + (this->velocity*-0.1); // slow down

	if(IListener->mouseState->leftMouseButtonState == KEY_STATE_PRESSED )
	{
		Entity *e = new Entity();
		e->position = this->GetWorldPosition();
		e->rotation = this->rotation;
	
		e->vertices.push_back(Vector2(-1,1));
		e->vertices.push_back(Vector2(1,1));
		e->vertices.push_back(Vector2(1,-1));
		e->vertices.push_back(Vector2(-1,-1));

		e->texture = TManager->TextureForName("plasma.tga");
		e->Scale(Vector2(0.5,0.7));
		e->velocity = (Vector2(0,50).Rotate(this->rotation * TO_RADIANS));

		GNManager->RootNode()->AddChild(e);

	}

	this->laser->visible = IListener->mouseState->rightMouseButtonState == KEY_STATE_HELD;

}
string Player::GetType()
{
	return "PLAYER";
}