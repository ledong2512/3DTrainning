#include "stdafx.h"
#include "Texture.h"


Texture::Texture()
{
}


Texture::~Texture()
{
}

void Texture::loadTexture(char * file, int type )
{	

	if (type == NORMAL_TYPE) {
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		int iWidth, iHeight, bpp;
		char *imageData = LoadTGA(file, &iWidth, &iHeight, &bpp);
		if (bpp == 24)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0,
				GL_RGB, GL_UNSIGNED_BYTE, imageData);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0,
				GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else {
		const char* Faces[] = {
			"right.tga",
			"left.tga",
			"top.tga",
			"bottom.tga",
			"front.tga",
			"back.tga"
		};
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
		int iWidth, iHeight, bpp;
		for (int i = 0; i<6; i++)
		{
			char fileName[100];
			strcpy(fileName, file);
			strcat(fileName, Faces[i]);
			char *imageData = LoadTGA(fileName, &iWidth, &iHeight, &bpp);
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				iWidth,
				iHeight,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				imageData);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
	

}

void Texture::setId(int ID)
{
	this->id = ID;
}

int Texture::getId()
{
	return id;
}
