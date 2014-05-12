/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #ifndef GUI_H
 #define GUI_H

 #include <windows.h>
 #include <stdio.h>
 #include "mouse.h"
 #include "..\gfx_subsys\opengl\texture.h"
 #include "..\core\stateManager.h"
 #include "..\msc\configurator.h"
 #include "primeMenu.h"

 class GUI
 {
     public:
        GUI();
        ~GUI();

        void init();
        void render(int width, int height);
        void shutdown();

        void setHWND(HWND hwnd);
        HWND getHWND();

        static GUI* getInstance();

     private:
        static GUI* m_instance;
        Mouse m_mouse;
        PrimeMenu m_primeMenu;
        Texture m_backDir;
        static HWND m_hwnd;
        int m_screenWidth, m_screenHeight;

 };

 #define inGUI GUI::getInstance()

 #endif
