#include <stdafx.h>
#include "Shaders.h"

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if ( vertexShader == 0 )
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");
	textureA = glGetAttribLocation(program,"a_uv");;
	norAttribute= glGetAttribLocation(program, "a_nor");
	iTextureLoc = glGetUniformLocation(program, "u_texture");
	multiTexture= glGetUniformLocation(program,"u_multi");
	MatrixID = glGetUniformLocation(program, "u_WVP");
	CubeUniformAtribute=glGetUniformLocation(program, "cubemap");
	w_Matrix = glGetUniformLocation(program, "u_W");
	v_Matrix = glGetUniformLocation(program, "u_V");
	p_Matrix = glGetUniformLocation(program, "u_P");
	this->fogNearLocation= glGetUniformLocation(program, "u_fogNear");
	this->fogFarLocation = glGetUniformLocation(program, "u_fogFar");
	this->fogColor = glGetUniformLocation(program, "u_fogColor");
	timeUni= glGetUniformLocation(program, "u_time");
	return 0;
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}