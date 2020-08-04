#include "stdafx.h"
#include "Model.h"


using namespace std;
Model::Model()
{

}

Model::Model(Vertex * vertexArray, const unsigned & nrOfVertices, GLuint * indexArray, const unsigned & nrOfIndices)
{
	this->nrOfVertices = nrOfVertices;
	this->nrOfIndices = nrOfIndices;
	this->vertexArray = new Vertex[this->nrOfVertices];
	for (size_t i = 0; i < nrOfVertices; i++)
	{
		this->vertexArray[i] = vertexArray[i];
	}

	this->indexArray = new GLuint[this->nrOfIndices];
	for (size_t i = 0; i < nrOfIndices; i++)
	{
		this->indexArray[i] = indexArray[i];
	}
}


Model::~Model()
{
	
	delete[] this->vertexArray;
	delete[] this->indexArray;
}

void Model::getModelFromFile(char *fileName,int type)
{
	if (type == NORMAL_TYPE) {
		FILE *fp;
		char buff[255];
		fp = fopen(fileName, "r");
		if (fp == NULL) {
			printf("Error opening file\n");
			return;
		}
		int numberOfVertices;

		fscanf(fp, "NrVertices: %d\n", &numberOfVertices);
		this->nrOfVertices = numberOfVertices;
		if (numberOfVertices <= 0)
			return;
		vertexArray = new Vertex[numberOfVertices];
		for (int i = 0; i < numberOfVertices; ++i)
		{
			fscanf(fp, "   %*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%*f, %*f, %*f]; tgt:[%*f, %*f, %*f]; uv:[%f, %f];\n",
				&vertexArray[i].pos.x, &vertexArray[i].pos.y, &vertexArray[i].pos.z,
				&vertexArray[i].normal.x, &vertexArray[i].normal.y, &vertexArray[i].normal.z,
				&vertexArray[i].texture.x, &vertexArray[i].texture.y);
		}
		int numberOfIndices;
		fscanf(fp, "NrIndices: %d\n", &numberOfIndices);
		if (numberOfIndices <= 0)
		{
			return;
		}
		this->nrOfIndices = numberOfIndices;
		this->indexArray = new GLuint[numberOfIndices];
		for (int i = 0; i < numberOfIndices; i += 3)
		{
			fscanf(fp, "   %*d.    %d,    %d,    %d\n", &indexArray[i], &indexArray[i + 1], &indexArray[i + 2]);

		}
		glGenBuffers(1, &vboId);
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), this->vertexArray, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &iboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices * sizeof(GLuint), this->indexArray, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	else {
		

	}
}

void Model::setId(int ID)
{
	this->id = ID;
}

int Model::getId()
{
	return this->id;
}


