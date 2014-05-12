/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #ifndef B_FONT_H
 #define B_FONT_H

 #include <windows.h>
 #include <GL\gl.h>
 #include <GL\glu.h>
 #include <stdio.h>

 #include "..\msc\configurator.h"

 class BFont
 {
     public:
        BFont(HDC hdc);
        ~BFont();

        void print(float x, float y, const char *string);
        void printEx(float x, float y, const char *string, ...);
        void setBody(int width, int height, int depth);

     private:
        HFONT m_font;
        HDC m_hdc;
        int m_width, m_height, m_depth;

        unsigned int m_listBase;

 };

 class OutFont
 {
     public:
        OutFont(HDC hdc);
        ~OutFont();

        void print(float x, float y, float z, const char *string);
        void printEx(float x, float y, const char *string, ...);
        void setBody(int width, int height, int depth);

     private:
        HFONT m_font;
        HDC m_hdc;
        int m_width, m_height, m_depth;

        unsigned int m_listBase;
 };

 #endif
