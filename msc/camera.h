/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

#ifndef CAMERA_H
#define CAMERA_H

#include "mathUtils.h"
#include "frustrum.h"

#define DIR_UP 3.0f
#define DIR_DOWN -3.0f
#define DIR_LEFT -1.0f
#define DIR_RIGHT 1.0f
#define DIR_SHOW_UP 0.01f
#define DIR_SHOW_DOWN -0.01f


class Camera
{
public:
	Camera();
	~Camera();

	void SetCamera(float x, float y, float z, float lookx,
                    float looky, float lookz);
    void updateView();
	void Move(float direction, float time);
	void ChangeYLook(float value, float time);
	void RotateY(float value, float time);
	void LookDown(float value, float time);
	void LookTo(float lookX, float lookY);

	void setSpeedUp(float newSpeed);
	float getSpeedUp();

    Vector3D getPosition();
    Vector3D getLookAt();
	static Camera* getInstance();

private:
    Vector3D m_position;
    Vector3D m_lookAt;
	static Camera *m_instance;
	float m_speedUp;

};

#define  camera Camera::getInstance()

#endif
