/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #ifndef CORE_OPEN_GL
 #define CORE_OPEN_GL

 #include <windows.h>
 #include <GL\gl.h>
 #include <GL\glu.h>

 #include "..\..\..\core\stateManager.h"
 #include "..\..\..\msc\mathUtils.h"
 #include "opengl\windows\Font.h"
 #include "..\..\..\msc\Camera.h"
 #include "..\texture.h"

 class CoreOpenGL
 {
     public:
        CoreOpenGL();
        ~CoreOpenGL();

        void SetupPixelFormat();
        void SetHDC(HDC hdc);
        void SetView(int width, int height);

        void initGL();
        void render();
        void shutdown();


     private:
        HDC m_hDC;

 };

 #endif