/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #ifndef MATH_UTILS_H
 #define MATH_UTILS_H

 #include <math.h>


 class Vector3D
 {
     public:

     float x,y,z;

        Vector3D()
        {
            this->x=this->y=this->z=0.0f;
        };

        Vector3D(float x, float y, float z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        };
        Vector3D(const Vector3D *vector)
        {
            this->x = vector->x;
            this->y = vector->y;
            this->z = vector->z;
        }

        ~Vector3D()
        {
        };

        Vector3D operator+ (const Vector3D vector);
        Vector3D operator- (const Vector3D vector);
        Vector3D operator* (const Vector3D vector);
        Vector3D operator* (const float factor);
        Vector3D operator/ (const Vector3D vector);
        Vector3D operator/ (const float factor);
        bool operator==(const Vector3D vector);

        Vector3D dotProduction();
        Vector3D crossProduct();

        void Normal();
        float Legth();

        float* toArray();

     private:


 };

 class Matrix4x4
 {
     public:
        Matrix4x4();
        ~Matrix4x4();

    private:
        float m[16];
        float   m11,m12,m13,m14,
                m21,m22,m23,m24,
                m31,m32,m33,m34,
                m41,m42,m43,m44;

 };
 #endif
