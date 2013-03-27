#pragma once
#include "Node.h"

class Texture;

class Shape : public Node
{
private:
	void setup();
	Vector2 m_scale;
public:
	bool visible;
	bool strechTexture;
	float alpha;
	list<Vector2> vertices;

	Texture *texture; 

	Shape(void);
	Shape(Vector2 position, string TextureName);
	~Shape(void);

	virtual void Update(float deltaT);
	virtual string GetType();
	void Draw();

	inline Vector2 Scale(){return m_scale;};
	void Scale(Vector2 newScale);

};
