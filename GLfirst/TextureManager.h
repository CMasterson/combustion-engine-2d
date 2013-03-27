#pragma once

#include "precompiled.h"

class Texture;

class TextureManager
{
private:
	static TextureManager * instance;

	Texture* LoadTexture(char* textureName);
	list<Texture*> Textures;
public:
	static TextureManager* Instance();
	TextureManager(void);
	~TextureManager(void);

	void Initialise();

	
	Texture* TextureForName(string texName);
	Texture* DefaultTexture();

	int IDCounter;

	string defaultTextureName;

	
};
