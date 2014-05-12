/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/
 /*
*rotation formula:
*x = cos(beta)*x + cos(gamma)*y + cos(alpha)*z
*y = cos(beta)*x + cos(gamma)*y + cos(alpha)*z
*z = cos(beta)*x + cos(gamma)*y + cos(alpha)*z
*/
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "camera.h"

#define PI 3.14159265

Camera* Camera::m_instance = NULL;

Camera* Camera::getInstance()
{
	if(!m_instance)
	{
		m_instance = new Camera;
	}

	return m_instance;
}

Camera::Camera()
{
    this->m_speedUp = 1;
}

Camera::~Camera()
{
}

void Camera::updateView()
{

    //this->getPosition().Normal();

        gluLookAt(this->getPosition().x,this->getPosition().y,
        this->getPosition().z,this->getLookAt().x,
        this->getLookAt().y, this->getLookAt().z,
        0.0f,1.0f,0.0f);
        //frustum->getFrustrum();
}

void Camera::SetCamera(float x, float y, float z, float lookx,
                        float looky, float lookz)
{

	Vector3D newPosVector(x,y,z);
	Vector3D newLookVector(lookx,looky,lookz);

	this->m_position = newPosVector;
	this->m_lookAt = newLookVector;
}

void Camera::Move(float direction, float time)
{
	Vector3D lookDirection(this->m_lookAt.x-this->m_position.x,
		this->m_lookAt.y-this->m_position.y,
		this->m_lookAt.z-this->m_position.z);

	lookDirection.Normal();

	direction = direction*(time+this->m_speedUp);

	this->m_position.x = this->m_position.x + lookDirection.x * direction;
	this->m_position.z = this->m_position.z + lookDirection.z * direction;
	this->m_position.y = this->m_position.y + lookDirection.y * direction;

	this->m_lookAt.x = this->m_lookAt.x + lookDirection.x * direction;
	this->m_lookAt.z = this->m_lookAt.z + lookDirection.z * direction;
	this->m_lookAt.y = this->m_lookAt.y + lookDirection.y * direction;

}


void Camera::RotateY(float value, float time)
{
	Vector3D lookDirection(this->m_lookAt.x-this->m_position.x,
		this->m_lookAt.y-this->m_position.y,
		this->m_lookAt.z-this->m_position.z);

	lookDirection.Normal();

	value /= 57.2957795;
	value *= time;


	this->m_lookAt.z = (float)(this->m_position.z + sin(value)*lookDirection.x + cos(value)*lookDirection.z);
	this->m_lookAt.x = (float)(this->m_position.x + cos(value)*lookDirection.x - sin(value)*lookDirection.z);
}

void Camera::ChangeYLook(float value, float time)
{
	this->m_lookAt.y = this->m_lookAt.y+(value*(time+this->m_speedUp));
}

void Camera::LookDown(float value, float time)
{

}

void Camera::LookTo(float lookX, float lookY)
{
	this->m_lookAt.x = lookX;
	this->m_lookAt.y = lookY;
}

Vector3D Camera::getPosition()
{

    return this->m_position;
}

Vector3D Camera::getLookAt()
{

    return this->m_lookAt;
}

void Camera::setSpeedUp(float newSpeed)
{
    if(newSpeed < 0)
        newSpeed = 0.00001f;

    this->m_speedUp = newSpeed;
}

float Camera::getSpeedUp()
{
    return this->m_speedUp;
}
