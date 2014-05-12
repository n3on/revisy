/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

#ifndef WIN_CLASS_H
#define WIN_CLASS_H

#include "..\..\gfx_subsys\opengl\windows\CoreOpenGL.h"
#include "..\..\gui\ingui.h"
#include "..\..\gui\mouse.h"
#include "..\..\core\stateManager.h"
#include "..\..\msc\configurator.h"
#include <windows.h>

#include <commctrl.h>

class WindowsGUI
{
    private:
        HINSTANCE hInstance;
        HWND m_hwnd;
        HWND m_hwndTab;
        HWND hwndStatic;
        MSG msg;
        WNDCLASSEX wndclass;
        //CoreOpenGL gfx;

        bool runApp;

        static LRESULT CALLBACK staticWndProc(HWND hwnd, UINT msg,
                                                WPARAM wParam, LPARAM lParam);
        void CreateTabControl();


    public:
        WindowsGUI();
        ~WindowsGUI();
        int CreateGUI(char *title, unsigned int x, unsigned int y,
                        unsigned int width, unsigned int height,
                        HINSTANCE hInstance);
        LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
                                    WPARAM wParam, LPARAM lParam);

};

#endif
