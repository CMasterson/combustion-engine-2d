#pragma once
#include "Node.h"

class GameNodeManager
{
private:
	static GameNodeManager *instance;
public:
	static GameNodeManager* Instance();
	GameNodeManager(void);
	~GameNodeManager(void);

	int lastID;

	Node* CreateGameNode();
	void AddGameNode(Node* obj);
	void AssignID(Node* obj);
	int GiveNewID();
	void Update(float deltaT);
	Node* rootNode;
	Node* RootNode();

	list<Node*> gameNodes;
};
