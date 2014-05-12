/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #include "CoreOpenGL.h"

 CoreOpenGL::CoreOpenGL()
 {

 }

 CoreOpenGL::~CoreOpenGL()
 {

 }

 void CoreOpenGL::SetupPixelFormat()
 {
     int pixelFormat;

     PIXELFORMATDESCRIPTOR pfd =
     {
         sizeof(PIXELFORMATDESCRIPTOR),
         1,
         PFD_SUPPORT_OPENGL |
         PFD_DRAW_TO_WINDOW |
         PFD_DOUBLEBUFFER,
         PFD_TYPE_RGBA,
         32,
         0,0,0,0,0,0,
         0,
         0,
         0,
         0,0,0,
         16,
         0,
         0,
         PFD_MAIN_PLANE,
         0,
         0,0,0,
     };

     pixelFormat = ChoosePixelFormat(this->m_hDC, &pfd);
     SetPixelFormat(this->m_hDC, pixelFormat, &pfd);
}

void CoreOpenGL::SetView(int width, int height)
{
    ProgramState->setView(width, height);
}

 void CoreOpenGL::SetHDC(HDC hdc)
 {
     this->m_hDC = hdc;
 }

 void CoreOpenGL::initGL()
 {

    ProgramState->init(this->m_hDC);

 }

 void CoreOpenGL::render()
 {

    ProgramState->run();

    SwapBuffers(this->m_hDC);
 }

 void CoreOpenGL::shutdown()
 {
     ProgramState->shutdown();
 }

