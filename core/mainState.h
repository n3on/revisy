/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #ifndef MAIN_STATE_H
 #define MAIN_STATE_H

 #include <windows.h>
 #include <GL\gl.h>
 #include <GL\glu.h>
 #include "opengl\Texture.h"
 #include "opengl\skybox.h"
 #include "opengl\loader3DS.h"
 #include "opengl\objLoader.h"
 #include "opengl\windows\Font.h"
 #include "..\gui\ingui.h"
 #include "..\msc\camera.h"
 #include "..\msc\logger.h"
 #include "..\msc\configurator.h"
 #include "..\msc\utils.h"
 #include "..\msc\frustrum.h"
 #include "programState.h"
 #include "FileManager.h"

 class mainState : public programState
 {
     public:
        mainState();
        ~mainState();

        void setView(int width, int height);
        void init(HDC hdc);
        void run();
        void shutdown();
        void processPeripherie();

     private:
        Texture m_Texture1;
        skybox m_environment;
        BFont *m_font;
        ObjLoader *m_cube;
        HDC m_hdc;

 };

 #endif
