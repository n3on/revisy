/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <windows.h>
#include <stdlib.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "File.h"
#include "..\gfx_subsys\opengl\windows\Font.h"
#include "..\msc\camera.h"
#include "..\msc\utils.h"
#include "..\msc\frustrum.h"
#include "..\gui\mouse.h"

class FileManager
{
    public:
        FileManager();
        ~FileManager();

        void GetFilesInFolder(const char *path);
        bool isInitialized();
        void renderFiles();
        static FileManager* getInstance();

    private:
        static FileManager* m_instance;

        bool m_initFolder;
        int m_numFiles;
        //File m_file;
        //File m_fileModel;
        HDC m_hdc;
        OutFont *m_font;
        vector<File> m_files;
        HANDLE m_fileHandle;
        unsigned int m_list;

};

#define fileManager FileManager::getInstance()

#endif
