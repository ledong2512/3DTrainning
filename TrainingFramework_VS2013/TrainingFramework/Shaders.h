#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
public:
	GLuint program, vertexShader, fragmentShader;
	int id;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute,norAttribute;
	GLint colorAttribute;
	GLint textureA, fogNearLocation, fogFarLocation,fogColor;
	GLuint MatrixID, v_Matrix, w_Matrix, p_Matrix;
	GLuint timeUni;
	int iTextureLoc, CubeUniformAtribute, multiTexture;
	int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();
};