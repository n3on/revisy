/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

#include "winClass.h"
#include "resource.h"
#include "..\..\msc\logger.h"

CoreOpenGL gfx;

WindowsGUI::WindowsGUI()
{
    this->m_hwnd = NULL;

}

WindowsGUI::~WindowsGUI()
{

}

void WindowsGUI::CreateTabControl()
{
    RECT clientRect;
    TCITEM tabItem;

    GetClientRect(this->m_hwnd, &clientRect);
    InitCommonControls();
    this->m_hwndTab = CreateWindowEx(WS_EX_CLIENTEDGE,WC_TABCONTROL, "",
                    WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                    0,0,clientRect.right, clientRect.bottom,
                    this->m_hwnd, NULL, this->hInstance, NULL);
    if(!this->m_hwndTab)
        MessageBox(NULL,"Error","TabControl init. failed",MB_OK);

    tabItem.mask = TCIF_TEXT | TCIF_IMAGE;
    tabItem.iImage = -1;
    tabItem.pszText = "1";

    TabCtrl_InsertItem(this->m_hwndTab,0,&tabItem);
    tabItem.pszText = "2";
    TabCtrl_InsertItem(this->m_hwndTab,1,&tabItem);

}

int WindowsGUI::CreateGUI(char *title, unsigned int x, unsigned int y,
                            unsigned int width, unsigned int height,
                            HINSTANCE hInstance)
{

        static HGLRC hRC;
    static HDC hDC;

    this->hInstance               = hInstance;
    this->wndclass.cbSize         = sizeof(WNDCLASSEX);
    this->wndclass.style          = CS_HREDRAW | CS_VREDRAW;
    this->wndclass.lpfnWndProc    = this->staticWndProc;
    this->wndclass.cbClsExtra     = 0;
    this->wndclass.cbWndExtra     = 0;
    this->wndclass.hInstance      = hInstance;
    this->wndclass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
    this->wndclass.hIconSm        = this->wndclass.hIcon;
    this->wndclass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    this->wndclass.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
    this->wndclass.lpszClassName  = "WndClass01";
    this->wndclass.lpszMenuName   = NULL;




    if(!RegisterClassEx(&this->wndclass))
    {
        Log->WriteText("Couldn't register wndclass");
        MessageBox(NULL,"Couldn't register wndclass","Error",MB_OK);
        return -1;
    }


    this->m_hwnd = CreateWindowEx(NULL,"WndClass01",
                        title,
                        WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,
                        x,y,
                        width,height,
                        NULL,NULL,
                        hInstance, NULL);



    if(!this->m_hwnd)
    {
        Log->WriteText("Bad HWND");
        MessageBox(NULL,"Bad HWND","Error",MB_OK);
        return -1;
    }

    Config->setHWND(this->m_hwnd);

    inGUI->setHWND(this->m_hwnd);

    ShowWindow(this->m_hwnd, SW_MAXIMIZE);
    UpdateWindow(this->m_hwnd);


    //this->CreateTabControl();

    hDC = GetDC(this->m_hwnd);
    gfx.SetHDC(hDC);
    gfx.SetupPixelFormat();
    hRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hRC);

    ProgramState->setState(SM_SPLASH);

    RECT clientRect;
    GetClientRect(this->m_hwnd,&clientRect);
    gfx.SetView(clientRect.right, clientRect.bottom);

    this->runApp = true;

    gfx.initGL();

    while(runApp)
    {

        gfx.render();
        SwapBuffers(hDC);

        while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
        {
            if(msg.message==WM_QUIT)
            {
                this->runApp=false;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }


    }

    wglMakeCurrent(hDC, NULL);
    wglDeleteContext(hRC);

    gfx.shutdown();

    return this->msg.wParam;
}

LRESULT CALLBACK WindowsGUI::WndProc(HWND hwnd, UINT msg,
                                        WPARAM wParam, LPARAM lParam)
{
    int height;
    int width;

    switch(msg)
    {
        case WM_CREATE:
        {
            ShowCursor(false);
        }break;

        case WM_SIZE:
        {
            //height = HIWORD(lParam);
            //width  = LOWORD(lParam);
            RECT clientRect;
            GetClientRect(hwnd,&clientRect);

            gfx.SetView(clientRect.right, clientRect.bottom);

        }break;

        case WM_LBUTTONDOWN:
        {
            if(ProgramState->getState()==SM_SPLASH)
            {
                RECT clientRect;
                GetClientRect(hwnd,&clientRect);
                ProgramState->shutdown();
                ProgramState->setState(SM_MAIN);
                ProgramState->setView(clientRect.right,clientRect.bottom);
                HDC hdc = GetDC(hwnd);
                ProgramState->init(hdc);
            }

            Mouse::setLState(true);

        }break;

        case WM_LBUTTONUP:
        {
            Mouse::setLState(false);
        }break;

        case WM_DESTROY:
        {
            ProgramState->shutdown();
            PostQuitMessage(0);
            return 0;
        }break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT CALLBACK WindowsGUI::staticWndProc(HWND hwnd, UINT msg,
                                            WPARAM wParam, LPARAM lParam)
{
    WindowsGUI *window = (WindowsGUI*) GetWindowLong(hwnd, GWL_USERDATA);

    return window->WndProc(hwnd, msg, wParam, lParam);
}
