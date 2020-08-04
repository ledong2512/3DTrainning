#pragma once
#include "Model.h"
#include "Texture.h"
#include"Shaders.h"
class Object
{
public:
	Object();
	~Object();
	void addModel(Model *Model);
	void addTexture(Texture *Texture,int type_=NORMAL_TYPE);
	void addShader(Shaders *Shader);
	void setnumberOfTexture(int number);
	void setNumberOfCube(int number);
	int initShader();
	void Draw();
	void update( Matrix V, Matrix P);
	void update(float deltaTime);
	void setWorldMatrix(float x, float y, float z, float rotation_X, float rotation_Y, float rotation_Z, float scale_x,float scale_y,float scale_z);
	int id;
private:
	int currentPosTexture = 0;
	Model *ObjectModel;
	int numberOfTexture;
	Texture **ObjectTexture;
	Shaders *ObjectShaders;
	Matrix WVP_Matrix,WorldMatrix, ViewMatrix, ProjectionMatrix;
	int numberOfCube;
	Texture **listOfcube;
	int currentPosCube=0;
	float totalTime = 0.0f;
};

