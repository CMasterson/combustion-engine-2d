#pragma once
#include "Shape.h"

class ShapeManager
{
private:
	static ShapeManager *instance;
public:
	static ShapeManager* Instance();

	ShapeManager(void);
	~ShapeManager(void);

	void Initialise();

	list<Shape*> shapes;
	void AddShape(Shape* nShape);
	void DrawShapes();
	Shape* ShapeForID(int IDReq);
	Vector2* ShapesAreColliding(Shape* a, Shape* b);
	bool AABBCollideTest(Shape* a, Shape* b);
	Vector2* PerVertexShapeCollision(Shape*a, Shape* b);
	bool IsPointInsideShape(Vector2* point, Shape* shape);

	bool debug;
};
