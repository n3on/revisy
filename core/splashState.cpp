/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #include "splashState.h"

 splashState::splashState()
 {

 }

 splashState::~splashState()
 {

 }

 void splashState::setView(int width, int height)
 {
     Log->ExWriteText("splashState setView(%d,%d)",width, height);

    if(height==0)
        height = 1;

    this->m_clientWidth = width;
    this->m_clientHeight = height;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0,width,height);
    //glOrtho(0,width,0,height,-500.0,500.0);
    glOrtho(0,width,height,0,-500,500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

 }

 void splashState::init(HDC hdc)
 {
     this->m_hdc = hdc;

     resource->Init();

     Log->WriteText("splashState init");
     glClearColor(0.0f,0.0f,0.0f,0.0f);

    this->m_loadingFont = new BFont(this->m_hdc);

     glEnable(GL_TEXTURE_2D);

     if(!this->m_splashScreen.loadTGA("data\\texture\\revisySplash.tga"))
             MessageBox(NULL,"couldn't load texture","error",MB_OK);

     camera->SetCamera(0.0f,0.0f,2.5f,0.0f,0.0f,0.0f);

     inGUI->init();

 }



 void splashState::run()
 {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glDisable(GL_LIGHTING);

    camera->updateView();
    //     camera->SetCamera(0.0f,0.0f,-2.0f,0.0f,0.0f,0.0f);
    //glOrtho(0,1280,0,768,-1,1);

    glTranslatef(0.0f,0.0f,0.0f);
    this->m_splashScreen.show(0,0,
                                this->m_clientWidth,this->m_clientHeight);

    inGUI->render(this->m_clientWidth, this->m_clientHeight);

 }

 void splashState::shutdown()
 {
     Log->WriteText("splashState shutdown");
     this->m_splashScreen.remove();
     inGUI->shutdown();
 }
