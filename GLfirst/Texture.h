#pragma once

class Texture
{
public:
	Texture(void);
	Texture(string name, int ID, GLuint texture);
	~Texture(void);

	string name;
	/*int ID;
	GLuint texture;
	int useCount;*/
	GLubyte	* imageData;									// Image Data (Up To 32 Bits)
	GLuint	bpp;											// Image Color Depth In Bits Per Pixel
	GLuint	width;											// Image Width
	GLuint	height;											// Image Height
	GLuint	texID;											// Texture ID Used To Select A Texture
	GLuint	type;
};
