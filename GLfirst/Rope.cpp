#include "precompiled.h"
#include "Rope.h"
#include "Node.h"

Rope::Rope(void)
{
}

Rope::~Rope(void)
{
}
void Rope::connectNodes(Node *start, Node *end)
{
	float lenght = (end->GetWorldPosition()-start->GetWorldPosition()).Length();
}