/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #include "frustrum.h"

 Frustrum* Frustrum::m_instance = NULL;

 Frustrum::Frustrum()
 {

 }

 Frustrum::~Frustrum()
 {

 }

 Frustrum* Frustrum::getInstance()
 {
     if(!Frustrum::m_instance)
        Frustrum::m_instance = new Frustrum;

    return Frustrum::m_instance;
 }

 void Frustrum::getFrustrum()
 {

    glGetFloatv(GL_PROJECTION_MATRIX,m_project);
    glGetFloatv(GL_MODELVIEW_MATRIX, m_modelview);

   m_clip[ 0] = m_modelview[ 0] * m_project[ 0] + m_modelview[ 1] * m_project[ 4]
                + m_modelview[ 2] * m_project[ 8] + m_modelview[ 3] * m_project[12];
   m_clip[ 1] = m_modelview[ 0] * m_project[ 1] + m_modelview[ 1] * m_project[ 5]
                + m_modelview[ 2] * m_project[ 9] + m_modelview[ 3] * m_project[13];
   m_clip[ 2] = m_modelview[ 0] * m_project[ 2] + m_modelview[ 1] * m_project[ 6]
                + m_modelview[ 2] * m_project[10] + m_modelview[ 3] * m_project[14];
   m_clip[ 3] = m_modelview[ 0] * m_project[ 3] + m_modelview[ 1] * m_project[ 7]
                + m_modelview[ 2] * m_project[11] + m_modelview[ 3] * m_project[15];

   m_clip[ 4] = m_modelview[ 4] * m_project[ 0] + m_modelview[ 5] * m_project[ 4]
                + m_modelview[ 6] * m_project[ 8] + m_modelview[ 7] * m_project[12];
   m_clip[ 5] = m_modelview[ 4] * m_project[ 1] + m_modelview[ 5] * m_project[ 5]
                + m_modelview[ 6] * m_project[ 9] + m_modelview[ 7] * m_project[13];
   m_clip[ 6] = m_modelview[ 4] * m_project[ 2] + m_modelview[ 5] * m_project[ 6]
                + m_modelview[ 6] * m_project[10] + m_modelview[ 7] * m_project[14];
   m_clip[ 7] = m_modelview[ 4] * m_project[ 3] + m_modelview[ 5] * m_project[ 7]
                + m_modelview[ 6] * m_project[11] + m_modelview[ 7] * m_project[15];

   m_clip[ 8] = m_modelview[ 8] * m_project[ 0] + m_modelview[ 9] * m_project[ 4]
                + m_modelview[10] * m_project[ 8] + m_modelview[11] * m_project[12];
   m_clip[ 9] = m_modelview[ 8] * m_project[ 1] + m_modelview[ 9] * m_project[ 5]
                + m_modelview[10] * m_project[ 9] + m_modelview[11] * m_project[13];
   m_clip[10] = m_modelview[ 8] * m_project[ 2] + m_modelview[ 9] * m_project[ 6]
                + m_modelview[10] * m_project[10] + m_modelview[11] * m_project[14];
   m_clip[11] = m_modelview[ 8] * m_project[ 3] + m_modelview[ 9] * m_project[ 7]
                + m_modelview[10] * m_project[11] + m_modelview[11] * m_project[15];

   m_clip[12] = m_modelview[12] * m_project[ 0] + m_modelview[13] * m_project[ 4]
                + m_modelview[14] * m_project[ 8] + m_modelview[15] * m_project[12];
   m_clip[13] = m_modelview[12] * m_project[ 1] + m_modelview[13] * m_project[ 5]
                + m_modelview[14] * m_project[ 9] + m_modelview[15] * m_project[13];
   m_clip[14] = m_modelview[12] * m_project[ 2] + m_modelview[13] * m_project[ 6]
                + m_modelview[14] * m_project[10] + m_modelview[15] * m_project[14];
   m_clip[15] = m_modelview[12] * m_project[ 3] + m_modelview[13] * m_project[ 7]
                + m_modelview[14] * m_project[11] + m_modelview[15] * m_project[15];

    //right
   m_frustum[0][0] = m_clip[ 3] - m_clip[ 0];
   m_frustum[0][1] = m_clip[ 7] - m_clip[ 4];
   m_frustum[0][2] = m_clip[11] - m_clip[ 8];
   m_frustum[0][3] = m_clip[15] - m_clip[12];

   m_normalized= (float)sqrt( m_frustum[0][0] * m_frustum[0][0] + m_frustum[0][1]
                        * m_frustum[0][1] + m_frustum[0][2] * m_frustum[0][2] );
   m_frustum[0][0] /= m_normalized;
   m_frustum[0][1] /= m_normalized;
   m_frustum[0][2] /= m_normalized;
   m_frustum[0][3] /= m_normalized;

   //left
   m_frustum[1][0] = m_clip[ 3] + m_clip[ 0];
   m_frustum[1][1] = m_clip[ 7] + m_clip[ 4];
   m_frustum[1][2] = m_clip[11] + m_clip[ 8];
   m_frustum[1][3] = m_clip[15] + m_clip[12];


   m_normalized = (float)sqrt( m_frustum[1][0] * m_frustum[1][0] + m_frustum[1][1]
                        * m_frustum[1][1] + m_frustum[1][2] * m_frustum[1][2] );
   m_frustum[1][0] /= m_normalized;
   m_frustum[1][1] /= m_normalized;
   m_frustum[1][2] /= m_normalized;
   m_frustum[1][3] /= m_normalized;

   //bottom
   m_frustum[2][0] = m_clip[ 3] + m_clip[ 1];
   m_frustum[2][1] = m_clip[ 7] + m_clip[ 5];
   m_frustum[2][2] = m_clip[11] + m_clip[ 9];
   m_frustum[2][3] = m_clip[15] + m_clip[13];


   m_normalized = (float)sqrt( m_frustum[2][0] * m_frustum[2][0] + m_frustum[2][1]
                        * m_frustum[2][1] + m_frustum[2][2] * m_frustum[2][2] );
   m_frustum[2][0] /= m_normalized;
   m_frustum[2][1] /= m_normalized;
   m_frustum[2][2] /= m_normalized;
   m_frustum[2][3] /= m_normalized;

   //top
   m_frustum[3][0] = m_clip[ 3] - m_clip[ 1];
   m_frustum[3][1] = m_clip[ 7] - m_clip[ 5];
   m_frustum[3][2] = m_clip[11] - m_clip[ 9];
   m_frustum[3][3] = m_clip[15] - m_clip[13];


   m_normalized = (float)sqrt( m_frustum[3][0] * m_frustum[3][0] + m_frustum[3][1]
                        * m_frustum[3][1] + m_frustum[3][2] * m_frustum[3][2] );
   m_frustum[3][0] /= m_normalized;
   m_frustum[3][1] /= m_normalized;
   m_frustum[3][2] /= m_normalized;
   m_frustum[3][3] /= m_normalized;

   //far
   m_frustum[4][0] = m_clip[ 3] - m_clip[ 2];
   m_frustum[4][1] = m_clip[ 7] - m_clip[ 6];
   m_frustum[4][2] = m_clip[11] - m_clip[10];
   m_frustum[4][3] = m_clip[15] - m_clip[14];

   m_normalized = (float)sqrt( m_frustum[4][0] * m_frustum[4][0] + m_frustum[4][1]
                        * m_frustum[4][1] + m_frustum[4][2] * m_frustum[4][2] );
   m_frustum[4][0] /= m_normalized;
   m_frustum[4][1] /= m_normalized;
   m_frustum[4][2] /= m_normalized;
   m_frustum[4][3] /= m_normalized;

   //near
   m_frustum[5][0] = m_clip[ 3] + m_clip[ 2];
   m_frustum[5][1] = m_clip[ 7] + m_clip[ 6];
   m_frustum[5][2] = m_clip[11] + m_clip[10];
   m_frustum[5][3] = m_clip[15] + m_clip[14];

   m_normalized = (float)sqrt( m_frustum[5][0] * m_frustum[5][0] + m_frustum[5][1]
                        * m_frustum[5][1] + m_frustum[5][2] * m_frustum[5][2] );
   m_frustum[5][0] /= m_normalized;
   m_frustum[5][1] /= m_normalized;
   m_frustum[5][2] /= m_normalized;
   m_frustum[5][3] /= m_normalized;

 }

 bool Frustrum::pointCheck(float x, float y, float z)
 {
   for( int i = 0; i < 6; i++ )
   {
       /*printf("i = %i x = %f y = %f z = %f w = %f\n",i, m_frustum[i][0],m_frustum[i][1],m_frustum[i][2],
        m_frustum[i][3]);*/

/*    printf("i = %i point = %f\n",i, m_frustum[i][0] * x + m_frustum[i][1] * y + m_frustum[i][2] * z
        + m_frustum[i][3]);*/
      if( m_frustum[i][0] * x + m_frustum[i][1] * y + m_frustum[i][2] * z
        + m_frustum[i][3] <= 0 )
            return false;
   }

   return true;
 }

 bool Frustrum::boxCheck(float x, float y, float z, float width, float height, float depth)
 {

    for(int i = 0; i < 6; i++ )
    {
      if( m_frustum[i][0] * (x - width) + m_frustum[i][1] * (y - height) + m_frustum[i][2] * (z - depth) + m_frustum[i][3] > 0 )
         continue;
      if( m_frustum[i][0] * (x + width) + m_frustum[i][1] * (y - height) + m_frustum[i][2] * (z - depth) + m_frustum[i][3] > 0 )
         continue;
      if( m_frustum[i][0] * (x - width) + m_frustum[i][1] * (y + height) + m_frustum[i][2] * (z - depth) + m_frustum[i][3] > 0 )
         continue;
      if( m_frustum[i][0] * (x + width) + m_frustum[i][1] * (y + height) + m_frustum[i][2] * (z - depth) + m_frustum[i][3] > 0 )
         continue;
      if( m_frustum[i][0] * (x - width) + m_frustum[i][1] * (y - height) + m_frustum[i][2] * (z + depth) + m_frustum[i][3] > 0 )
         continue;
      if( m_frustum[i][0] * (x + width) + m_frustum[i][1] * (y - height) + m_frustum[i][2] * (z + depth) + m_frustum[i][3] > 0 )
         continue;
      if( m_frustum[i][0] * (x - width) + m_frustum[i][1] * (y + height) + m_frustum[i][2] * (z + depth) + m_frustum[i][3] > 0 )
         continue;
      if( m_frustum[i][0] * (x + width) + m_frustum[i][1] * (y + height) + m_frustum[i][2] * (z + depth) + m_frustum[i][3] > 0 )
         continue;
      return false;
    }
        return true;
 }

 bool Frustrum::sphereCheck(float x, float y, float z, float radius)
 {
    for( int i = 0; i < 6; ++i )
    {
        if( m_frustum[i][0] * x +
            m_frustum[i][1] * y +
            m_frustum[i][2] * z +
            m_frustum[i][3] <= -radius )
            return false;
    }

        return true;
 }


