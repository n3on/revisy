/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #ifndef MOUSE_H
 #define MOUSE_H

 #include <windows.h>
 #include "..\gfx_subsys\opengl\texture.h"
 #include "..\msc\mathUtils.h"

 class Mouse
 {
     public:
        Mouse();
        ~Mouse();

        void init(HWND hwnd);
        void update();
        void render(int width, int height);
        void shutdown();

        void toOGLPos(int x, int y);
        static POINT getPosition();
        static void setLState(bool pressed);
        static bool getLState();

     private:
        static bool lpressed;
        POINT m_position;
        POINT m_positionOGL;
        static POINT position;
        Texture m_mouseImage;
        HWND m_hwnd;

 };


 #endif
