#include "precompiled.h"
#include "GameNodeManager.h"

GameNodeManager* GameNodeManager::instance = 0;
GameNodeManager* GameNodeManager::Instance()
{
	if(!instance)
		instance = new GameNodeManager();
	return instance;
}
GameNodeManager::GameNodeManager(void)
{
	//Root Node
	lastID = 0;
	this->rootNode = this->CreateGameNode();
	this->gameNodes.push_back(this->rootNode);
}

GameNodeManager::~GameNodeManager(void)
{
}
Node* GameNodeManager::CreateGameNode()
{
	Node* newObj = new Node();
	this->AssignID(newObj);
	this->AddGameNode(newObj);
	return newObj;
}
void GameNodeManager::AddGameNode(Node* obj)
{
	this->gameNodes.push_back(obj);
}
void GameNodeManager::AssignID(Node* obj)
{
	obj->ID = GiveNewID();
}
int GameNodeManager::GiveNewID()
{
	return ++lastID;
}
void GameNodeManager::Update(float deltaT)
{
	this->gameNodes.front()->Update(deltaT);
}
Node* GameNodeManager::RootNode()
{
	return this->rootNode;
}