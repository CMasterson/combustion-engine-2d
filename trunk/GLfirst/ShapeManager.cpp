#include "precompiled.h"
#include "ShapeManager.h"
ShapeManager* ShapeManager::instance = 0;
ShapeManager* ShapeManager::Instance()
{
	if(!instance)
		instance = new ShapeManager();
	return instance;
}
ShapeManager::ShapeManager(void)
{
}

ShapeManager::~ShapeManager(void)
{
}
void ShapeManager::Initialise()
{
	debug = false;
}
void ShapeManager::AddShape(Shape *nShape)
{
	if(this->ShapeForID(nShape->ID) == NULL)
	{
		this->shapes.push_back(nShape);
	}
}
Shape* ShapeManager::ShapeForID(int IDReq)
{
	if(this->shapes.size() > 0)
	{
		list<Shape*>::iterator current;
		for(current = this->shapes.begin();current != this->shapes.end();current++)
		{
			if((*current)->ID == IDReq)
				return (*current);
		}
	}
	return NULL;
}
void ShapeManager::DrawShapes()
{

	list<Shape*>::iterator current;
	for(current = this->shapes.begin();current != this->shapes.end();current++)
	{
		(*current)->Draw();
	}
	
}
Vector2* ShapeManager::ShapesAreColliding(Shape* a, Shape* b)
{
	Vector2* colliding = NULL;
	if(AABBCollideTest(a,b))
	{
		//test each point of shape a
		colliding = PerVertexShapeCollision(a, b);
	}
	return colliding;
}
bool ShapeManager::AABBCollideTest(Shape* a, Shape* b)
{
	bool colliding = false;
	Vector2 minA, minB, maxA, maxB;
	list<Vector2>::iterator iter = a->vertices.begin();
	minA = maxA = (*iter).Rotate(a->rotation*TO_RADIANS) + a->position;
	for(;iter != a->vertices.end();iter++)
	{
		Vector2 point = (*iter).Rotate(a->rotation*TO_RADIANS) + a->position;

		minA.X = min(minA.X, point.X);
		minA.Y = min(minA.Y, point.Y);

		maxA.X = max(maxA.X, point.X);
		maxA.Y = max(maxA.Y, point.Y);
	}
	iter = b->vertices.begin();
	minB = maxB = (*iter).Rotate(a->rotation*TO_RADIANS) + b->position;
	for(;iter != b->vertices.end();iter++)
	{
		Vector2 point = (*iter).Rotate(b->rotation*TO_RADIANS) + b->position;

		minB.X = min(minB.X, point.X);
		minB.Y = min(minB.Y, point.Y);

		maxB.X = max(maxB.X, point.X);
		maxB.Y = max(maxB.Y, point.Y);
	}

	if(minA.X < maxB.X && maxA.X > minB.X)
		if(minA.Y < maxB.Y && maxA.Y > minB.Y)
			return true;
	
	return false;	
}
Vector2* ShapeManager::PerVertexShapeCollision(Shape*a, Shape* b)
{
	list<Vector2>::iterator Current = a->vertices.begin();
	for each(Vector2 vec in a->vertices)
	{
		if(IsPointInsideShape(&(vec.Rotate(a->rotation*TO_RADIANS) + a->position),b))
			return &vec;
	}
	for each(Vector2 vec in b->vertices)
	{
		if(IsPointInsideShape(&(vec.Rotate(b->rotation*TO_RADIANS) + b->position),a))
			return &vec;
	}
	return NULL;
}
bool ShapeManager::IsPointInsideShape(Vector2 *point, Shape* shape)
{
	bool inside = false;

	list<Vector2>::iterator vertexA = shape->vertices.begin();
	list<Vector2>::iterator vertexB = shape->vertices.end();
	vertexB--;

	for (; vertexA != shape->vertices.end(); vertexB = vertexA++) {
		Vector2 vertexAWorld = (*vertexA).Rotate(shape->rotation*TO_RADIANS) + shape->position;
		Vector2 vertexBWorld = (*vertexB).Rotate(shape->rotation*TO_RADIANS) + shape->position;
		if ( ((vertexAWorld.Y>point->Y) != (vertexBWorld.Y>point->Y)) &&
			(point->X < (vertexBWorld.X-vertexAWorld.X) * (point->Y-vertexAWorld.Y) / (vertexBWorld.Y-vertexAWorld.Y) + vertexAWorld.X) )
			inside = !inside;
	}
	return inside;
}
Vector2* LineIntersection(Vector2* firstStart, Vector2* firstEnd, Vector2* secondStart, Vector2* secondEnd) 
{
	// Store the values for fast access and easy
	// equations-to-code conversion
	float x1 = firstStart->X, x2 = firstEnd->X, x3 = secondStart->X, x4 = secondEnd->X;
	float y1 = firstStart->Y, y2 = firstEnd->Y, y3 = secondStart->Y, y4 = secondEnd->Y;
	 
	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// If d is zero, there is no intersection
	if (d == 0) return NULL;
	 
	// Get the x and y
	float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
	float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;
	 
	// Check if the x and y coordinates are within both lines
	if ( x < min(x1, x2) || x > max(x1, x2) ||
	x < min(x3, x4) || x > max(x3, x4) ) return NULL;
	if ( y < min(y1, y2) || y > max(y1, y2) ||
	y < min(y3, y4) || y > max(y3, y4) ) return NULL;
	 
	// Return the point of intersection
	Vector2* ret = new Vector2();
	ret->X = x;
	ret->Y = y;
	return ret;
}