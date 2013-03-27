#pragma once
 
class Vector2;
class Node
{
public:
	Node(void);
	~Node(void);

	int ID;

	Vector2 position;
	float rotation;
	

	Node * parent;
	list<Node*> children;

	virtual void Update(float deltaT);
	virtual string GetType();
	virtual void Draw();
	void DrawChildren();
	void UpdateChildren(float deltaT);
	void AddChild(Node* child);
	void SetParent();
	void SetParent(Node* parent);
	Vector2 GetWorldPosition();
};
