#include "stdafx.h"
#include "ScreenManager.h"
#include "ResourceManager.h"
#include "Singleton.h"

ScreenManager::ScreenManager()
{
	fogColor = Vector4(0.8f, 0.9f, 1.f, 1.0f);
	fogNear=3.0f;
	fogFar=5.0f;
}


ScreenManager::~ScreenManager()
{
}

void ScreenManager::loafObject(char * file)
{
	FILE *fp;
	char buff[255];
	fp = fopen(file, "r");
	if (fp == NULL) {
		printf("Error opening file\n");
		return;
	}
	fscanf(fp, "#Objects: %d\n", &noObject);
	listObject = new Object*[noObject];
	for (int i = 0; i < noObject; i++) {
		listObject[i] = new Object();
		fscanf(fp, "ID %d\n", &listObject[i]->id);
		int modelId,numberTexture,shaderId;
		fscanf(fp, "MODEL %d\n", &modelId);
		Model *model = Singleton<ResourceManager>::GetInstance()->getModelById(modelId);
		listObject[i]->addModel(model);
		fscanf(fp, "TEXTURES %d\n", &numberTexture);
		listObject[i]->setnumberOfTexture(numberTexture);
		for (int j = 0; j < numberTexture; j++) {
			int textureId;
			fscanf(fp, "TEXTURE %d\n", &textureId);
			Texture *texture = Singleton<ResourceManager>::GetInstance()->getTextureById(textureId);
			listObject[i]->addTexture(texture);
		}
		int noCube;
		fscanf(fp, "CUBETEXTURES %d\n", &noCube);
		listObject[i]->setNumberOfCube(noCube);
		for (int j = 0; j < noCube; j++) {
			int cubeID;
			fscanf(fp, "CUBETEX %d\n", &cubeID);
			Texture *texture = Singleton<ResourceManager>::GetInstance()->getCubeById(cubeID);
			listObject[i]->addTexture(texture,CUBE_TYPE);
		}
		fscanf(fp, "SHADER %d\n", &shaderId);
		Shaders *shader = Singleton<ResourceManager>::GetInstance()->getShadersById(shaderId);
		listObject[i]->addShader(shader);
		float pos_x, pos_y, pos_z, rotation_x, rotation_y, rotation_z, scale_x, scale_y, scale_z;
		fscanf(fp, "POSITION %f,%f,%f\n", &pos_x,&pos_y,&pos_z);
		fscanf(fp, "ROTATION %f,%f,%f\n", &rotation_x, &rotation_y, &rotation_z);
		fscanf(fp, "SCALE %f,%f,%f\n", &scale_x, &scale_y, &scale_z);
		listObject[i]->setWorldMatrix(pos_x, pos_y, pos_z, rotation_x, rotation_y, rotation_z, scale_x, scale_y, scale_z);

	}
}

void ScreenManager::Draw()
{
	for (int i = 0; i < noObject; ++i) {
		listObject[i]->Draw();
	}
}

void ScreenManager::init()
{
	for (int i = 0; i < noObject; ++i) {
		listObject[i]->initShader();
	}
}

void ScreenManager::update(Matrix V, Matrix P)
{
	for (int i = 0; i < noObject; ++i) {
		listObject[i]->update(V,P);
	}
}

void ScreenManager::update(float deltaTime)
{
	for (int i = 0; i < noObject; ++i) {
		listObject[i]->update(deltaTime);
	}
}

Vector4 ScreenManager::getFogColor()
{
	return this->fogColor;
}

float ScreenManager::getFogNear()
{
	return this->fogNear;
}

float ScreenManager::getFogFar()
{
	return this->fogFar;

}
