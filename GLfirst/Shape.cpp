#include "precompiled.h"
#include "Shape.h"
#include "GameNodeManager.h"
#include "ShapeManager.h"
#include "Texture.h"
#include "TextureManager.h"

Shape::Shape(void)
{
	this->setup();
	this->texture = TManager->TextureForName( TManager->defaultTextureName );
}
Shape::Shape(Vector2 Position, string TextureName)
{
	this->setup();
	this->position = Position;
	this->texture = TManager->TextureForName((char*)TextureName.c_str());
}
Shape::~Shape(void)
{
}
void Shape::Update(float deltaT)
{
}
void Shape::Draw()
{
	if(Shape::vertices.size()>0 && this->visible)
	{
		Vector2 maxXY = Vector2();
		Vector2 minXY = Vector2();
		Vector2 worldToTexSpace = Vector2();
		Vector2 shapeMagnitude = Vector2();

		list<Vector2>::iterator current;
		//Get smallest and largerst xy 
		for(current = Shape::vertices.begin(); current != Shape::vertices.end(); current++)
		{
			if(current->X > maxXY.X)
				maxXY.X = current->X;
			else if(current->X < minXY.X)
				minXY.X = current->X;

			if(current->Y > maxXY.Y)
				maxXY.Y = current->Y;
			else if(current->Y < minXY.Y)
				minXY.Y = current->Y;
		}
		if(minXY.X != 0 )
		{
			worldToTexSpace.X = minXY.X * -1;
		}
		if(minXY.Y != 0)
		{
			worldToTexSpace.Y = minXY.Y * -1;
		}

		shapeMagnitude = maxXY + worldToTexSpace;

		glBindTexture(GL_TEXTURE_2D, this->texture->texID);
		
		if(this->rotation > MAX_ROTATION)
			this->rotation -= MAX_ROTATION;
		else if(this->rotation < 0)
			this->rotation += MAX_ROTATION;

		if(SManager->debug)
		{
			glDisable(GL_TEXTURE_2D);
			glBegin(GL_LINES);
			glColor4f(0,1,0,1);
			glVertex3f(0,1,1);
			glVertex3f(0,-1,1);
			glColor4f(1,0,0,1);
			glVertex3f(-1,0,1);
			glVertex3f(1,0,1);
			glEnd();
			glEnable(GL_TEXTURE_2D);
		}

		glBegin(GL_POLYGON);

		glColor4f(1,1,1,alpha);

		for(current = Shape::vertices.begin(); current != Shape::vertices.end(); current++)
		{
			Vector2 point = *current;

			if(this->strechTexture)
				glTexCoord2f((point.X + worldToTexSpace.X)/shapeMagnitude.X, (point.Y + worldToTexSpace.Y)/shapeMagnitude.Y);
			else
				glTexCoord2f((point.X * m_scale.X) / texture->width*10, (point.Y * m_scale.Y) / texture->height*10);

			point = Vector2(point.X * Shape::m_scale.X,point.Y * Shape::m_scale.Y);
			glVertex2f(point.X ,point.Y);
		}
		glEnd();		
	}
}
void Shape::setup()
{
	GNManager->AssignID((Node*)this);
	GNManager->AddGameNode((Node*)this);
	SManager->AddShape(this);

	
	this->visible = true;
	this->strechTexture = true;
	this->alpha = 1.0f;
	this->m_scale = Vector2(1,1);
		
}
void Shape::Scale(Vector2 newScale)
{
	if(newScale != m_scale)
	{
		newScale = newScale/m_scale;
		list<Vector2>::iterator iter = this->vertices.begin();
		for(;iter != this->vertices.end();iter++)
		{
			(*iter) = (*iter)*newScale;
		}
	}
}
string Shape::GetType()
{
	return "SHAPE";
}
