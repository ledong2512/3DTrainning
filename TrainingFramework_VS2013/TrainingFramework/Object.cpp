#include "stdafx.h"
#include "Object.h"
#include <cstddef>

Object::Object()
{
	Matrix rotateX, rotateY, rotateZ, RotateMatrix;

	rotateX.SetRotationX(0.0f);
	rotateZ.SetRotationY(0.0f);
	rotateY.SetRotationZ(0.0f);
	RotateMatrix = rotateZ  *rotateX*  rotateY;

	Matrix ScaleMatrix, TranslationMatrix;
	ScaleMatrix.SetScale(0.5f);
	TranslationMatrix.SetTranslation(0.0f, 0.0f,  0.0f);
	
	WorldMatrix = TranslationMatrix*ScaleMatrix *RotateMatrix;
	
	ViewMatrix.SetIdentity();
	ProjectionMatrix.SetIdentity();

	WVP_Matrix = WorldMatrix *ViewMatrix * ProjectionMatrix;

}


Object::~Object()
{
}

void Object::addModel(Model * Model)
{
	this->ObjectModel = Model;
	
}

void Object::addTexture(Texture * Texture,int type)
{
	if (type == NORMAL_TYPE) {
		this->ObjectTexture[currentPosTexture] = Texture;
		currentPosTexture++;
	}
	else {
		this->listOfcube[currentPosCube] = Texture;
		currentPosCube++;
	}
}

void Object::addShader(Shaders * Shader)
{
	this->ObjectShaders = Shader;
}

void Object::setnumberOfTexture(int number)
{
	this->numberOfTexture = number;
	this->ObjectTexture = new Texture*[number];
}

void Object::setNumberOfCube(int number)
{
	this->numberOfCube = number;
	this->listOfcube = new Texture*[number];
}

int Object::initShader()
{
	return ObjectShaders->Init(ObjectShaders->fileVS, ObjectShaders->fileFS);
}

void Object::Draw()
{
	
	glUseProgram(ObjectShaders->program);

	glBindBuffer(GL_ARRAY_BUFFER, ObjectModel->getVBOID());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ObjectModel->getEBOID());
	for (int i = 0; i < numberOfTexture; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, ObjectTexture[i]->getTextureID());
	}
	for (int i = 0; i < numberOfCube; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_CUBE_MAP, listOfcube[i]->getTextureID());
	}

	if (ObjectShaders->positionAttribute != -1)
	{
		glEnableVertexAttribArray(ObjectShaders->positionAttribute);
		glVertexAttribPointer(ObjectShaders->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, pos));

	}

	if (ObjectShaders->norAttribute != -1) {
		glEnableVertexAttribArray(ObjectShaders->norAttribute);
		glVertexAttribPointer(ObjectShaders->norAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	}
	if (ObjectShaders->textureA != -1)
	{
		glEnableVertexAttribArray(ObjectShaders->textureA);
		
		glVertexAttribPointer(ObjectShaders->textureA, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texture));
	}
	if (ObjectShaders->MatrixID != -1)
	{
		glEnableVertexAttribArray(ObjectShaders->MatrixID);

		glUniformMatrix4fv(ObjectShaders->MatrixID, 1, GL_FALSE, (GLfloat*)&WVP_Matrix.m);
	}
	if (ObjectShaders->iTextureLoc != -1)
	{
		glEnableVertexAttribArray(ObjectShaders->iTextureLoc);
		glUniform1i(ObjectShaders->iTextureLoc, 0);
	}
	if (ObjectShaders->multiTexture != -1) {
		
		int arrayBuf[32] ;
		for (int i = 0; i < numberOfTexture; i++) {
			arrayBuf[i] = i;
		}
		glEnableVertexAttribArray(ObjectShaders->multiTexture);
		glUniform1iv(ObjectShaders->multiTexture, sizeof(int)*numberOfTexture, (GLint*)&arrayBuf);
	}
	if (ObjectShaders->CubeUniformAtribute != -1)
	{

		glEnableVertexAttribArray(ObjectShaders->CubeUniformAtribute);
		glUniform1i(ObjectShaders->CubeUniformAtribute, 0);
	}
	if (ObjectShaders->w_Matrix != -1)
	{
		glEnableVertexAttribArray(ObjectShaders->w_Matrix);
		glUniformMatrix4fv(ObjectShaders->w_Matrix, 1, GL_FALSE, (GLfloat*)&WorldMatrix.m);
	}
	if (ObjectShaders->v_Matrix != -1)
	{
		glEnableVertexAttribArray(ObjectShaders->v_Matrix);
		glUniformMatrix4fv(ObjectShaders->v_Matrix, 1, GL_FALSE, (GLfloat*)&ViewMatrix.m);
	}
	if (ObjectShaders->p_Matrix != -1)
	{
		glEnableVertexAttribArray(ObjectShaders->p_Matrix);
		glUniformMatrix4fv(ObjectShaders->p_Matrix, 1, GL_FALSE, (GLfloat*)&ProjectionMatrix.m);
	}
	if (ObjectShaders->timeUni != -1)
	{
		glEnableVertexAttribArray(ObjectShaders->timeUni);
		glUniform1f(ObjectShaders->timeUni, totalTime);
	}
	
	glDrawElements(GL_TRIANGLES, this->ObjectModel->nrOfIndices, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	for (int i = 0; i < numberOfTexture; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
	}
	for (int i = 0; i < numberOfCube; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
	}
}

void Object::update( Matrix V, Matrix P )
{

	
	ViewMatrix = V;
	this->ProjectionMatrix = P;
	this->WVP_Matrix = WorldMatrix*ViewMatrix*ProjectionMatrix;
     
}

void Object::update(float deltaTime)
{
	totalTime += deltaTime;
}

void Object::setWorldMatrix(float x, float y, float z, float rotation_X, float rotation_Y, float rotation_Z, float scale_x, float scale_y, float scale_z)
{
	Matrix rotateX, rotateY, rotateZ, RotateMatrix;

	rotateX.SetRotationX(rotation_X);
	rotateZ.SetRotationY(rotation_Y);
	rotateY.SetRotationZ(rotation_Z);
	RotateMatrix = rotateZ  *rotateX*  rotateY;

	Matrix ScaleMatrix, TranslationMatrix, ViewMatrix, ProjectionMatrix;
	ScaleMatrix.SetScale(scale_x, scale_y, scale_z);
	TranslationMatrix.SetTranslation(x, y, z);

	WorldMatrix = ScaleMatrix *RotateMatrix*TranslationMatrix;
}


