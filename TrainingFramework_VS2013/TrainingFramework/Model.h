#pragma once
//#include"utilities.h"
#define NORMAL_TYPE 0
#include "Vertex.h"
using namespace std;
class Model
{
public:
	Model();
	Model(
		Vertex* vertexArray,
		const unsigned& nrOfVertices,
		GLuint* indexArray,
		const unsigned& nrOfIndices);
	~Model();
	void getModelFromFile(char *fileName,int type= NORMAL_TYPE);
	Vertex * vertexArray;
	unsigned nrOfVertices;
	GLuint* indexArray;
	unsigned nrOfIndices;
	GLuint getVBOID() { return vboId; };
	GLuint getEBOID() { return iboId; };
	void setId(int ID);
	int getId();
	GLuint vboId, iboId;
	int id;

};

