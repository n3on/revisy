/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #ifndef PRIME_MENU_H
 #define PRIME_MENU_H

 #include <windows.h>
 #include "..\gfx_subsys\opengl\texture.h"
 #include "..\msc\configurator.h"
 #include "mouse.h"

 #define NORMAL 0
 #define HOVERED 1

 class PrimeMenu
 {
     public:
        PrimeMenu();
        ~PrimeMenu();

        void init();
        void render(int width, int height);
        void shutdown();

    private:
        void processCollision(int width, int height);
        Texture m_primeMenu;
        Texture m_close[2];
        Texture m_size[2];
        Texture m_minimize[2];
        int m_isHovered[3];
 };

 #endif