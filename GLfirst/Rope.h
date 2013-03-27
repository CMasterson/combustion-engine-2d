#pragma once

class Vector2;
class Spring;
class Node;

class Rope
{
public:
	Rope(void);
	~Rope(void);

	void connectNodes(Node* start, Node* end);
	void makeLonger();
	void makeShorter();

	Node* start;
	Node* end;

	list<Node*> ropeNodes;
	list<Spring*> ropeSprings;
};
