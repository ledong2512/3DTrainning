#pragma once
#include "utilities.h"
#define CUBE_TYPE 1
#define NORMAL_TYPE 0
class Texture
{
public:
	Texture();
	~Texture();
	void loadTexture(char *file,int type= NORMAL_TYPE);
	GLuint getTextureID() { return textureID; }
	void setId(int ID);
	int getId();
	char tiling[50];
	int type;
private:
	GLuint textureID;
	int id;

};

