/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

#ifndef REVISY_FILE_H
#define REVISY_FILE_H

#include <windows.h>
#include <stdlib.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "resourceManager.h"
#include "..\gfx_subsys\opengl\objLoader.h"
#include "..\msc\mathUtils.h"
//#include "..\msc\Configurator.h"
//#include "..\gfx_subsys\opengl\windows\Font.h"

enum FileType
{
    FILE_TYPE_NON,
    FILE_TYPE_DIR,
    FILE_TYPE_HIDDEN,
    FILE_TYPE_READONLY,
};

class File
{
    public:
        File();
        ~File();

        //void loadFile();
        void render();

        Vector3D getPosition();
        char* getFileName();


        void setPosition(Vector3D position);
        void setPosition(float x, float y, float z);
        void moveObject(float x, float y, float z);
        bool objectCollision(Vector3D point);
        FileType getFileType();
        void setFileType(FileType newType);
        void setFileName(char *m_fileName);

        int width;
        int height;
        int depth;

    private:
        //ObjLoader m_fileObject;
        Vector3D m_position;
        //OutFont *m_font;
        //HDC m_hdc;
        char *m_fileName;
        FileType m_type;


};

#endif
