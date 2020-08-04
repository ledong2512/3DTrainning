#include "stdafx.h"
#include "Camera.h"
#include"Globals.h"

const INT32 RIGHT_DIREC =1 << 0;
const INT32 LEFT_DIREC = 1 << 1;
const INT32 FORWARD_DIREC = 1 << 2;
const INT32 BACKWARD_DIREC = 1 << 3;
const INT32 ROTATION_RIGHT = 1 << 4;
const INT32 ROTATION_LEFT = 1 << 5;
const INT32 ROTATION_UP = 1 << 6;
const INT32 ROTATION_DOWN = 1 << 7;

Camera::Camera()
{


	FOV =1.0f;
	aspect = Globals::screenWidth / Globals::screenHeight;
	nearPlane = 0.1f;
	farPlane = 100.0f;
	m_projection.SetPerspective(FOV, aspect, nearPlane, farPlane);

	m_viewMatrix.SetIdentity();
	v_pos = Vector3(0.0f, 0.0f, -3.0f);
	v_taget= Vector3(0.0f, 0.0f, 0.0f);
	v_up = Vector3(0.0f, 1.0f, 0.0f);
	
	z_axis = (v_pos - v_taget).Normalize();
	x_axis = v_up.Cross(z_axis).Normalize();
	y_axis = (z_axis.Cross(x_axis)).Normalize();
	
	m_viewMatrix.m[0][0] = x_axis.x;
	m_viewMatrix.m[0][1] = y_axis.x;
	m_viewMatrix.m[0][2] = z_axis.x;
	m_viewMatrix.m[0][3] = 0;
	
	m_viewMatrix.m[1][0] = x_axis.y;
	m_viewMatrix.m[1][1] = y_axis.y;
	m_viewMatrix.m[1][2] = z_axis.y;
	m_viewMatrix.m[1][3] = 0;
	
	m_viewMatrix.m[2][0] = x_axis.z;
	m_viewMatrix.m[2][1] = y_axis.z;
	m_viewMatrix.m[2][2] = z_axis.z;
	m_viewMatrix.m[2][3] = 0;
	
	m_viewMatrix.m[3][0] = -v_pos.Dot(x_axis);
	m_viewMatrix.m[3][1] = -v_pos.Dot(y_axis);
	m_viewMatrix.m[3][2] = -v_pos.Dot(z_axis);
	m_viewMatrix.m[3][3] = 1;

	
}


Camera::~Camera()
{
	

}

void Camera::calculate()
{
	z_axis = (v_pos - v_taget).Normalize();
	x_axis = v_up.Cross(z_axis).Normalize();
	y_axis = (z_axis.Cross(x_axis)).Normalize();

	m_viewMatrix.m[0][0] = x_axis.x;
	m_viewMatrix.m[0][1] = y_axis.x;
	m_viewMatrix.m[0][2] = z_axis.x;
	m_viewMatrix.m[0][3] = 0;

	m_viewMatrix.m[1][0] = x_axis.y;
	m_viewMatrix.m[1][1] = y_axis.y;
	m_viewMatrix.m[1][2] = z_axis.y;
	m_viewMatrix.m[1][3] = 0;

	m_viewMatrix.m[2][0] = x_axis.z;
	m_viewMatrix.m[2][1] = y_axis.z;
	m_viewMatrix.m[2][2] = z_axis.z;
	m_viewMatrix.m[2][3] = 0;

	m_viewMatrix.m[3][0] = -v_pos.Dot(x_axis);
	m_viewMatrix.m[3][1] = -v_pos.Dot(y_axis);
	m_viewMatrix.m[3][2] = -v_pos.Dot(z_axis);
	m_viewMatrix.m[3][3] = 1;
}

void Camera::calculateWorld()
{
	z_axis = (v_pos - v_taget).Normalize();
	x_axis = v_up.Cross(z_axis).Normalize();
	y_axis = (z_axis.Cross(x_axis)).Normalize();

	m_cameraWorld.m[0][0] = x_axis.x;
	m_cameraWorld.m[0][1] = x_axis.y;
	m_cameraWorld.m[0][2] = x_axis.z;
	m_cameraWorld.m[0][3] = 0;

	m_cameraWorld.m[1][0] = y_axis.x;
	m_cameraWorld.m[1][1] = y_axis.y;
	m_cameraWorld.m[1][2] = y_axis.z;
	m_cameraWorld.m[1][3] = 0;

	m_cameraWorld.m[2][0] = z_axis.x;
	m_cameraWorld.m[2][1] = z_axis.y;
	m_cameraWorld.m[2][2] = z_axis.z;
	m_cameraWorld.m[2][3] = 0;

	m_cameraWorld.m[3][0] = v_pos.x*x_axis.x+ v_pos.y*y_axis.x+ v_pos.z*z_axis.x;
	m_cameraWorld.m[3][1] = v_pos.x*x_axis.y+ v_pos.y*y_axis.y+ v_pos.z*z_axis.y;
	m_cameraWorld.m[3][2] = v_pos.x*x_axis.z+ v_pos.y*y_axis.z+ v_pos.z*z_axis.z;
	m_cameraWorld.m[3][3] = 1;
}

void Camera::Update(float deltaTime)
{
	
	if ((currentKey&RIGHT_DIREC) == RIGHT_DIREC) {
		Vector3 deltaMove = -(v_up.Cross(z_axis)).Normalize()*deltaTime;
		v_pos += deltaMove;
		v_taget += deltaMove;
	}
	if ((currentKey&LEFT_DIREC) == LEFT_DIREC) {
		Vector3 deltaMove = -(v_up.Cross(z_axis)).Normalize()*deltaTime;
		v_pos -= deltaMove;
		v_taget -= deltaMove;
	}
	if ((currentKey&FORWARD_DIREC) == FORWARD_DIREC) {
		Vector3 deltaMove = -(v_pos - v_taget).Normalize()*deltaTime;
		v_pos += deltaMove;
		v_taget += deltaMove;
	}
	if ((currentKey&BACKWARD_DIREC) == BACKWARD_DIREC) {
		Vector3 deltaMove = -(v_pos - v_taget).Normalize()*deltaTime ;
		v_pos -= deltaMove;
		v_taget -= deltaMove;
	}
	if ((currentKey&ROTATION_RIGHT) == ROTATION_RIGHT) {
		Vector4 localTarget = Vector4(0.f, 0.f, -(v_pos - v_taget).Length(), 1.f);
		Vector4 localNewTarget = localTarget *this->RotationMatrixAroundY(deltaTime);
		Vector4 worldNewTarget = localNewTarget*getWorldMatrix();
		v_taget = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
	}
	if ((currentKey&ROTATION_LEFT) == ROTATION_LEFT) {
		Vector4 localTarget = Vector4(0.f, 0.f, -(v_pos - v_taget).Length(), 1.f);
		Vector4 localNewTarget = localTarget *this->RotationMatrixAroundY(-deltaTime);
		Vector4 worldNewTarget = localNewTarget*getWorldMatrix();
		v_taget = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
	}
	if ((currentKey&ROTATION_UP) == ROTATION_UP) {
		getViewMatrix();
		Matrix Rotation;
		Vector4 localTarget = Vector4(0.f, 0.f, -(v_pos - v_taget).Length(), 1.f);
		Vector4 localNewTarget = localTarget *Rotation.SetRotationX(deltaTime);
		Vector4 worldNewTarget = localNewTarget*getWorldMatrix();
		v_taget = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
	}
	if ((currentKey&ROTATION_DOWN) == ROTATION_DOWN) {
		getViewMatrix();
		Matrix Rotation;
		Vector4 localTarget = Vector4(0.f, 0.f, -(v_pos - v_taget).Length(), 1.f);
		Vector4 localNewTarget = localTarget *Rotation.SetRotationX(-deltaTime);
		Vector4 worldNewTarget = localNewTarget*getWorldMatrix();
		v_taget = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
	}
}

void Camera::keyBuffer(unsigned char key, bool bIsPressed)
{
	
	if (key == 'D') {
		if(bIsPressed==1) currentKey=currentKey|LEFT_DIREC;
		else currentKey = currentKey^LEFT_DIREC;
	}else if (key == 'A') {
		if (bIsPressed == 1) currentKey = currentKey | RIGHT_DIREC;
		else currentKey = currentKey^RIGHT_DIREC;
	}else if (key == 'W') {
		if (bIsPressed == 1) currentKey = currentKey | FORWARD_DIREC;
		else currentKey = currentKey^FORWARD_DIREC;
	}else if (key == 'S') {
		if (bIsPressed == 1) currentKey = currentKey | BACKWARD_DIREC;
		else currentKey = currentKey^BACKWARD_DIREC;
	}else if (key == 'Q') {
		if (bIsPressed == 1) currentKey = currentKey | ROTATION_RIGHT;
		else currentKey = currentKey^ROTATION_RIGHT;
	}else if (key == 'E') {
		if (bIsPressed == 1) currentKey = currentKey | ROTATION_LEFT;
		else currentKey = currentKey^ROTATION_LEFT;
	}else if (key == 'I') {
		if (bIsPressed == 1) currentKey = currentKey | ROTATION_UP;
		else currentKey = currentKey^ROTATION_UP;
	}else if (key == 'K') {
		if (bIsPressed == 1) currentKey = currentKey | ROTATION_DOWN;
		else currentKey = currentKey^ROTATION_DOWN;
	}
	
	printf("%d %c %d \n", currentKey, key, bIsPressed);
}

Matrix Camera::RotationMatrixAroundY(float angle)
{
	Matrix rotation;
	Vector4 RotateAxis = Vector4(0.f, 1.f, 0.f, 0.f);
	RotateAxis = RotateAxis*getViewMatrix();
	return rotation.SetRotationAngleAxis(angle , RotateAxis.x, RotateAxis.y, RotateAxis.z);
}

Matrix Camera::RotationMatrixAroundX(float angle)
{
	Matrix rotation;
	Vector4 RotateAxis = Vector4(1.f, 0.f, 0.f, 0.f);
	RotateAxis = RotateAxis*getViewMatrix();
	return rotation.SetRotationAngleAxis(angle, RotateAxis.x, RotateAxis.y, RotateAxis.z);
}

