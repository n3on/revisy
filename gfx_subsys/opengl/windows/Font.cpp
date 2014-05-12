/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #include "Font.h"

 BFont::BFont(HDC hdc)
 {
     this->m_listBase = glGenLists(96);

     this->m_font = CreateFont(-18,0,0,0,
                                FW_BOLD,false,false,false,
                                ANSI_CHARSET,OUT_TT_PRECIS,
                                CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,
                                FF_DONTCARE | DEFAULT_PITCH,
                                "Times New Roman");

    SelectObject(hdc, this->m_font);
    wglUseFontBitmaps(hdc,32,96,this->m_listBase);
 }

 BFont::~BFont()
 {
    DeleteObject(this->m_font);
    glDeleteLists(this->m_listBase,96);
 }

 void BFont::setBody(int width, int height, int depth)
 {
        this->m_width = width;
        this->m_height = height;
        this->m_depth = depth;
 }

 void BFont::print(float x, float y, const char* string)
 {
     glDisable(GL_TEXTURE_2D);
     glDisable(GL_LIGHTING);

     glMatrixMode(GL_PROJECTION);
     glPushMatrix();
     glLoadIdentity();
     glOrtho(0,0,400,400,0,1);

     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();

     glRasterPos2f(x,y);

     glListBase(this->m_listBase-32);
     glCallLists(strlen(string),GL_UNSIGNED_BYTE,string);

     glMatrixMode(GL_PROJECTION);
     glPopMatrix();

     glMatrixMode(GL_MODELVIEW);

     glEnable(GL_LIGHTING);
     glEnable(GL_TEXTURE_2D);
 }

 void BFont::printEx(float x, float y, const char* string, ...)
 {
     char buffer[256];
     va_list list;

     va_start(list, string);
     vsprintf(buffer,string,list);
     va_end(list);

     this->print(x,y,buffer);
 }

 OutFont::OutFont(HDC hdc)
 {
     /*this->m_listBase = glGenLists(256);
     this->m_font = CreateFont(-12,0,0,0,
                            FW_BOLD,false,false,false,
                            ANSI_CHARSET,OUT_TT_PRECIS,
                            CLIP_DEFAULT_PRECIS,
                            ANTIALIASED_QUALITY,
                            FF_DONTCARE|DEFAULT_PITCH,
                            "Times New Roman");
    if(this->m_font == NULL)
        MessageBox(NULL,"fuck font","error",MB_OK);

    SelectObject(this->m_hdc,this->m_font);

    wglUseFontOutlines(this->m_hdc,0,255,this->m_listBase,
                            0.0f,0.2f,WGL_FONT_POLYGONS,
                            this->m_mf);*/

    GLYPHMETRICSFLOAT m_mf[256];

    this->m_listBase = glGenLists(256);
	this->m_font = CreateFont(	-10,
						0,
						0,
						0,
						FW_BOLD,
						FALSE,
                        FALSE,
						FALSE,
						ANSI_CHARSET,
						OUT_TT_PRECIS,
						CLIP_DEFAULT_PRECIS,
						ANTIALIASED_QUALITY,
                        FF_DONTCARE|DEFAULT_PITCH,
						"Times New Roman");

	SelectObject(hdc, this->m_font);

	wglUseFontOutlines(	hdc,
						0,
						255,
						this->m_listBase,
						0.0f,
						0.2f,
						WGL_FONT_POLYGONS,
						m_mf);


 }

 OutFont::~OutFont()
 {
    glDeleteLists(this->m_listBase,256);
 }

 void OutFont::setBody(int width, int height, int depth)
 {
        this->m_width = width;
        this->m_height = height;
        this->m_depth = depth;
 }

 void OutFont::print(float x, float y, float z, const char *string)
 {
     glPushMatrix();
    glDisable(GL_TEXTURE_2D);
     glDisable(GL_LIGHTING);

     //glMatrixMode(GL_PROJECTION);
     //glPushMatrix();
     //glLoadIdentity();
     //   glOrtho(0,0,400,400,0,1);

     //glMatrixMode(GL_MODELVIEW);
     //glLoadIdentity();

      //glScalef(1.0f,2.0f,1.0f);
      /*float length = 0.0f;
      for (unsigned int loop=0;loop<(strlen(string));loop++)	// Loop To Find Text Length
        {
            length+=this->m_mf[string[loop]].gmfCellIncX;		// Increase Length By Each Characters Width
        }*/

      //glColor3f(1.0f,0.0f,0.0f);

     //glPushMatrix();
      glTranslatef(x,y,z);
      glScalef(m_width, m_height, m_depth);
     glPushAttrib(GL_LIST_BIT);
     glListBase(this->m_listBase);
     glCallLists(strlen(string),GL_UNSIGNED_BYTE,string);
     glPopAttrib();
     //glPopMatrix();

     //glMatrixMode(GL_PROJECTION);
     //glPopMatrix();

     //glMatrixMode(GL_MODELVIEW);

     glEnable(GL_LIGHTING);
     glEnable(GL_TEXTURE_2D);
     glPopMatrix();


 }

 void OutFont::printEx(float x, float y, const char *string, ...)
 {

 }


