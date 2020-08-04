#include "stdafx.h"
#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
	for (int i = 0; i < noModel; i++) {
		delete listModel[i];
	}
	for (int i = 0; i < noShader; i++) {
		delete listShader[i];
	}
	for (int i = 0; i < noTexture; i++) {
		delete listTexture[i];
	}
	delete[]listModel;
	delete[]listShader;
	delete[]listTexture;
}

void ResourceManager::loadResource(char *filename)
{
	FILE *fp;
	char buff[255];
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Error opening file\n");
		return;
	}
	fscanf(fp, "#Models: %d\n", &noModel);
	listModel = new Model*[noModel];
	for (int i = 0; i < noModel; i++) {
		int modelId;
		fscanf(fp, "ID %d\n",&modelId);
		char fileName[100];
		fscanf(fp, "FILE %s\n",&fileName);
		listModel[i] = new Model();
		listModel[i]->getModelFromFile(fileName);
		listModel[i]->setId(modelId);
	}
	fscanf(fp, "#2D Textures: %d\n", &this->noTexture);
	listTexture = new Texture*[noTexture];
	for (int i = 0; i < noTexture; i++) {
		int textureId;
		fscanf(fp, "ID %d\n", &textureId);
		char fileName[100],tiling[50];
		fscanf(fp, "FILE %s\n", &fileName);
		listTexture[i] = new Texture();
		listTexture[i]->loadTexture(fileName);
		listTexture[i]->setId(textureId);
		fscanf(fp, "TILING %s\n", &tiling);
		strcpy(listTexture[i]->tiling, tiling);
	}
	fscanf(fp, "#Cube Textures: %d\n", &this->noCube);
	listCube= new Texture*[noCube];
	for (int i = 0; i < noCube; i++) {
		int textureId;
		fscanf(fp, "ID %d\n", &textureId);
		char fileName[100], tiling[50];
		fscanf(fp, "FILE %s\n", &fileName);
		listCube[i] = new Texture();
		listCube[i]->loadTexture(fileName,CUBE_TYPE);
		listCube[i]->setId(textureId);
		fscanf(fp, "TILING %s\n", &tiling);
		strcpy(listCube[i]->tiling, tiling);
	}
	fscanf(fp, "#Shaders: %d\n", &noShader);
	listShader = new Shaders*[noShader];
	for (int i = 0; i < noShader; i++) {
		listShader[i] = new Shaders();
		int shaderId;
		fscanf(fp, "ID %d\n", &shaderId);
		listShader[i]->id = shaderId;
		char VSfile[100], FSfile[100];
		fscanf(fp, "VS %s\n", &VSfile);
		fscanf(fp, "FS %s\n", &FSfile);
		strcpy(listShader[i]->fileFS, FSfile);
		strcpy(listShader[i]->fileVS, VSfile);
		
		int nOState;
		fscanf(fp, "STATE %d\n", &nOState);
		for (int j = 0; j < nOState; j++) {
			char buff[50];
			fscanf(fp, "STATE %s\n", &buff);
		}
	}
}

Texture * ResourceManager::getTextureById(int id)
{
	for (int i = 0; i < noTexture; ++i) {
		if (listTexture[i]->getId() == id) {
			return listTexture[i];
		}
	}
	return nullptr;
}

Model * ResourceManager::getModelById(int id)
{
	for (int i = 0; i < noModel; ++i) {
		if (listModel[i]->getId() == id) {
			return listModel[i];
		}
	}
	return nullptr;

}

Shaders * ResourceManager::getShadersById(int id)
{
	for (int i = 0; i < noShader; ++i) {
		if (listShader[i]->id == id) {
			return listShader[i];
		}
	}
	return nullptr;
}

Texture * ResourceManager::getCubeById(int id)
{
	for (int i = 0; i < noCube; ++i) {
		if (listCube[i]->getId() == id) {
			return listCube[i];
		}
	}
	return nullptr;
}
