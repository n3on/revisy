/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #include "ingui.h"

 GUI* GUI::m_instance = NULL;
 HWND GUI::m_hwnd = NULL;

 GUI::GUI()
 {
     GUI::m_instance = NULL;
     //this->m_hwnd = NULL;
 }

 GUI::~GUI()
 {

 }

 GUI* GUI::getInstance()
 {
    if(GUI::m_instance==NULL)
        GUI::m_instance = new GUI;

    return GUI::m_instance;
 }

 void GUI::init()
 {
     this->m_mouse.init(this->m_hwnd);
     this->m_primeMenu.init();

     if(!this->m_backDir.loadTGA("data\\gui\\backDir.tga"))
        MessageBox(NULL,"couldn't load texture","error",MB_OK);

 }

 void GUI::render(int width, int height)
 {
     glDisable(GL_LIGHTING);

     glMatrixMode(GL_PROJECTION);
     glPushMatrix();
     glLoadIdentity();
     glOrtho(0,width,height,0,0,1);

     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();

    if(ProgramState->getState() == SM_MAIN)
    {
        this->m_backDir.show(0,height/17,(strlen(Config->getValue("StartPath"))*2+200),height/9);
        this->m_primeMenu.render(width, height);
    }

    this->m_mouse.update();
    this->m_mouse.render(width, height);

    glMatrixMode(GL_PROJECTION);
     glPopMatrix();

     glMatrixMode(GL_MODELVIEW);

     glEnable(GL_LIGHTING);

 }

 void GUI::shutdown()
 {

    this->m_mouse.shutdown();
    this->m_primeMenu.shutdown();
    this->m_backDir.remove();
 }

 void GUI::setHWND(HWND hwnd)
 {
     this->m_hwnd = hwnd;
 }

 HWND GUI::getHWND()
 {
     return this->m_hwnd;
 }

