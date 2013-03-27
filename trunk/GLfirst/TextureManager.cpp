#include "precompiled.h"
#include "TextureManager.h"
#include "Texture.h"

TextureManager* TextureManager::instance = 0;

#pragma comment(lib, "Glu32.lib")

bool LoadTGA(Texture *, char *);


TextureManager* TextureManager::Instance()
{
	if(!instance)
	{
		instance = new TextureManager();
	}
	return instance;	
}

TextureManager::TextureManager(void)
{
}
TextureManager::~TextureManager(void)
{
}
void TextureManager::Initialise()
{
	defaultTextureName = "default.tga";
	TextureForName(defaultTextureName);
}
Texture* TextureManager::LoadTexture(char * textureName)											// Load TGA And Convert To Textures
{
	Texture * texture = new Texture();
	texture->name = textureName;
	// Load The TGA, Check For Errors.
	if (LoadTGA(texture, textureName))
	{
		// Typical Texture Generation Using Data From The TGA ( CHANGE )
		glGenTextures(1, &texture->texID);				// Create The Texture ( CHANGE )
		glBindTexture(GL_TEXTURE_2D, texture->texID);
		glTexImage2D(GL_TEXTURE_2D, 0, texture->bpp / 8, texture->width, texture->height, 0, texture->type, GL_UNSIGNED_BYTE, texture->imageData);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		if (texture->imageData)						// If Texture Image Exists ( CHANGE )
		{
			free(texture->imageData);					// Free The Texture Image Memory ( CHANGE )
		}
		this->Textures.push_back(texture);				//add texture to the list of textures
		return texture;									//return loaded texture
	}

	return this->Textures.front();												// Return default.tga
}
Texture* TextureManager::TextureForName(string texName)
{
	list<Texture*>::iterator current;
	for(current = this->Textures.begin();current != this->Textures.end();current++)
	{
		if((*current)->name == texName)
			return *current;
	}
	
	return LoadTexture((char*)texName.c_str());
}
Texture* TextureManager::DefaultTexture()
{
	return this->TextureForName(defaultTextureName);
}
