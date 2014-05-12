/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/
 #include "mouse.h"

 POINT Mouse::position = {0,0};
 bool Mouse::lpressed = false;

 Mouse::Mouse()
 {

 }

 Mouse::~Mouse()
 {

 }

 void Mouse::init(HWND hwnd)
 {
     glEnable(GL_TEXTURE_2D);
     //glClearColor(0.0f,0.0f,0.0f,0.0f);
     //glEnable(GL_BLEND);
     //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
     this->m_hwnd = hwnd;

     this->m_position.x = 0;
     this->m_position.y = 0;
     if(!this->m_mouseImage.loadTGA("data\\gui\\cursor.tga"))
             MessageBox(NULL,"couldn't load texture","error",MB_OK);

 }

 void Mouse::update()
 {
     glMatrixMode(GL_PROJECTION);
        GetCursorPos(&this->m_position);
        ScreenToClient(this->m_hwnd,&this->m_position);
        this->toOGLPos(this->m_position.x, this->m_position.y);
    glMatrixMode(GL_MODELVIEW);
 }

 void Mouse::render(int width, int height)
 {
     //glClear(GL_DEPTH_BUFFER_BIT);
    this->m_mouseImage.show(this->m_positionOGL.x,this->m_positionOGL.y,width/64,height/25);
 }

 void Mouse::shutdown()
 {
     //this->m_mouseImage.remove();
 }

 void Mouse::toOGLPos(int x, int y)
 {
     int viewport[4];
     double mvmatrix[16];
     double projectionmatrix[16];

      double pX,pY,pZ;
      float wX,wY,wZ;

     glGetIntegerv(GL_VIEWPORT,viewport);
     glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
     glGetDoublev(GL_PROJECTION_MATRIX,projectionmatrix);

     wX = (double)x;
     wY = viewport[3]-y;

     glReadPixels(wX,wY,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&wZ);

     gluUnProject(wX,wY,wZ,mvmatrix,projectionmatrix,viewport,
                      &pX,&pY,&pZ);

    this->m_positionOGL.x = (int)pX;
    this->m_positionOGL.y = (int)pY;
    Mouse::position.x = (int)pX;
    Mouse::position.y = (int)pY;

 }

 POINT Mouse::getPosition()
 {
     return Mouse::position;
 }

 void Mouse::setLState(bool state)
 {
    Mouse::lpressed = state;
 }

 bool Mouse::getLState()
 {
    return Mouse::lpressed;
 }
