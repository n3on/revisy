/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

#define WIN32_LEAN_AND_MEAN

//#pragma comment(lib, "OpenGL32.lib");
//#pragma comment(lib, "Glu32.lib");

#include <windows.h>
#include "..\window_subsys\windows\winClass.h"
#include "..\msc\logger.h"
#include "..\msc\Configurator.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine, int nCmdShow)
{
    WindowsGUI gui;

    Log->Create("log.nfo");
    if(!Config->init("config.cfg"))
        MessageBox(NULL,"Error while loading config.cfg","Error",MB_OK);

    int width, height;
    width = Config->getIntValue(CLIENT_WIDTH);
    height = Config->getIntValue(CLIENT_HEIGHT);

    int status = gui.CreateGUI("ReViSy  -   Resources Visualization System",0,0,
                                width,height, hInstance);

    Log->ExWriteText("end of program status: %d... ",status);

    return status;
}
