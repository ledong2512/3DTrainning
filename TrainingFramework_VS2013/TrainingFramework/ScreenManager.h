#pragma once
#include "../Utilities/utilities.h"
#include "Object.h"

class ScreenManager
{
public:
	ScreenManager();
	~ScreenManager();
	void loafObject(char * file);
	void Draw();
	void init();
	void update(Matrix V, Matrix P);
	void update(float deltaTime);
	Vector4 getFogColor();
	float getFogNear();
	float getFogFar();

private:
	Object **listObject;
	int noObject;
	Vector4 fogColor; 
	float fogNear;
	float fogFar;
};

