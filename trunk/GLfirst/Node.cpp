#include "precompiled.h"
#include "Node.h"
#include "GameNodeManager.h"

Node::Node(void)
{
	this->parent = NULL;
	this->position = Vector2();
	this->rotation = 0;
}
Node::~Node(void)
{
}
void Node::Update(float deltaT)
{
	if(this->GetType() != "NODE") // see if e have been inherited
		this->Update(deltaT);

	//Continue the update down along the tree
	this->UpdateChildren(deltaT);
}

void Node::UpdateChildren(float deltaT)
{
	list<Node*>::iterator iter = this->children.begin();
	for(;iter != this->children.end();iter++)
	{
		(*iter)->Node::Update(deltaT);
	}
}
void Node::Draw()
{
	glTranslatef(position.X ,position.Y,0);
	glRotatef(this->rotation, 0.0f, 0.0f, 1.0f );

	if(this->GetType() != "NODE") // see if e have been inherited
		this->Draw();

	//Continue the Draw down along the tree
	this->DrawChildren();
	
}
void Node::DrawChildren()
{
	list<Node*>::iterator iter = this->children.begin();
	for(;iter != this->children.end();iter++)
	{
		glPushMatrix();
		(*iter)->Node::Draw();
		glPopMatrix();
	}
}
void Node::AddChild(Node* child)
{
	if(child->parent)
	{
		child->parent->children.remove(child);
	}
	this->children.push_back(child);
	child->parent = this;
}
void Node::SetParent(Node* parent)
{
	if(this->parent)
	{
		this->parent->children.remove(this);
	}
	this->parent = parent;
	parent->children.push_back(this);
}
void Node::SetParent()
{
	this->SetParent(GNManager->RootNode());
}
string Node::GetType()
{
	return "NODE";
}
Vector2 Node::GetWorldPosition()
{
	list<Node*> Nodes;
	Node* Current = this;
	while(Current->parent)
	{
		Nodes.push_front(Current);
		Current = Current->parent;
	}

	Vector2 returnValue = Vector2();

	list<Node*>::iterator iter = Nodes.begin();
	for(;iter != Nodes.end();iter++)
	{
		if((*iter)->parent)
			returnValue = returnValue + (*iter)->position;
		else
			returnValue = returnValue + (*iter)->position.Rotate((*iter)->parent->rotation);
	}

	return returnValue;
}
