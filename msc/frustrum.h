/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #ifndef FRUSTRUM_H
 #define FRUSTRUM_H

 #include <stdlib.h>
 #include <stdio.h>
 #include <math.h>
 #include <GL\gl.h>
 #include <GL\glu.h>


 class Frustrum
 {
     public:
        Frustrum();
        ~Frustrum();

        static Frustrum* getInstance();
        void getFrustrum();
        bool pointCheck(float x, float y, float z);
        bool boxCheck(float x, float y, float z, float width, float height, float depth);
        bool sphereCheck(float x, float y, float z, float radius);

    private:
        static Frustrum *m_instance;
        float m_frustum[6][4];
        float m_project[16];
        float m_modelview[16];
        float m_clip[16];
        float m_normalized;
 };

 #define frustum Frustrum::getInstance()

 #endif
