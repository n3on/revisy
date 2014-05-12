/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #ifndef SPLASH_STATE_H
 #define SPLASH_STATE_H

 #include <windows.h>
 #include <GL\gl.h>
 #include <GL\glu.h>
 #include "resourceManager.h"
 #include "..\gui\ingui.h"
 #include "..\msc\logger.h"
 #include "..\gfx_subsys\opengl\texture.h"
  #include "..\msc\camera.h"
  #include "opengl\windows\Font.h"
 #include "programState.h"

 class splashState : public programState
 {
     public:
        splashState();
        ~splashState();

        void setView(int width, int height);
        void init(HDC hdc);
        void run();
        void shutdown();

    private:
        HDC m_hdc;
        Texture m_splashScreen;
        int m_clientWidth, m_clientHeight;
        BFont *m_loadingFont;

 };

 #endif
