#pragma once
#include"Model.h"
#include"Texture.h"
#include "Shaders.h"
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	void loadResource(char *filename);
	Texture *getTextureById(int id);
	Model *getModelById(int id);
	Shaders *getShadersById(int id);
	Texture *getCubeById(int id);
private:
	Model **listModel;
	Texture **listTexture;
	Shaders **listShader;
	Texture **listCube;
	int noModel,noTexture,noShader,noCube;

};

