/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

#include "mathUtils.h"

Vector3D Vector3D::operator+ (const Vector3D vector)
{

    return Vector3D(this->x+vector.x,
                    this->y+vector.y,
                    this->z+vector.z);
}

Vector3D Vector3D::operator- (const Vector3D vector)
{
    return Vector3D(this->x-vector.x,
                    this->y-vector.y,
                    this->z-vector.z);

}

bool Vector3D::operator== (const Vector3D vector)
{
    return (this->x == vector.x) &&
           (this->y == vector.y) &&
           (this->z == vector.z);
}

Vector3D Vector3D::operator* (const Vector3D vector)
{

    return Vector3D(this->x*vector.x,
                    this->y*vector.y,
                    this->z*vector.z);
}

Vector3D Vector3D::operator* (const float factor)
{

    return Vector3D(this->x*factor,
                    this->y*factor,
                    this->z*factor);
}

Vector3D Vector3D::operator/ (const Vector3D vector)
{

    return Vector3D(this->x/vector.x,
                    this->y/vector.y,
                    this->z/vector.z);
}

Vector3D Vector3D::operator/ (const float factor)
{

    return Vector3D(this->x/factor,
                    this->y/factor,
                    this->z/factor);
}

float Vector3D::Legth()
{
    return sqrtf(this->x*this->x+this->y*this->y+this->z*this->z);
}

void Vector3D::Normal()
{
    Vector3D vector(this->x, this->y, this->z);
    vector/(sqrt(this->x*this->x+this->y*this->y+this->z*this->z)+0.0001f);
    this->x = vector.x; this->y = vector.y; this->z = vector.z;
}

float* Vector3D::toArray()
{
    float tempArray[3];
    tempArray[0] = this->x;
    tempArray[1] = this->y;
    tempArray[2] = this->z;

    return tempArray;
}


