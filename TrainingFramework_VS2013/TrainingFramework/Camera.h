#pragma once
#include "utilities.h"

class Camera
{
public:
	Camera();
	~Camera();
	void calculate();
	void calculateWorld();
	Matrix getViewMatrix() { calculate(); return this->m_viewMatrix; }
	Matrix getWorldMatrix() { calculateWorld();  return this->m_cameraWorld; }
	void Update(float deltaTime);
	Matrix getProjection() { return this->m_projection; }
	void keyBuffer(unsigned char key, bool bIsPressed);
	Matrix RotationMatrixAroundY(float angle);
	Matrix RotationMatrixAroundX(float angle);
	
private:
	GLfloat nearPlane, farPlane,FOV, aspect;
	GLfloat speed;
	Matrix m_viewMatrix,m_projection,m_cameraWorld;
	Vector3 v_pos, v_taget;
	Vector3 v_up;
	Vector3 x_axis, y_axis, z_axis;
	INT32 currentKey = 0;

};

