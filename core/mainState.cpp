/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #include "mainState.h"

 mainState::mainState()
 {

 }

 mainState::~mainState()
 {

 }

 void mainState::setView(int width, int height)
 {
    Log->ExWriteText("mainState setView(%d,%d)",width, height);
    if(height==0)
        height = 1;

    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective((float)45.0f, (float)width/(float)height, 0.1f, 1000.0f);

    /*glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();*/

 }

 void mainState::init(HDC hdc)
 {
    Log->WriteText("mainState init");

    this->m_hdc = hdc;

    //this->m_font = new BFont(this->m_hdc);
    this->m_font = new BFont(this->m_hdc);

    glClearColor(0.0,1.0,0.0,1.0);
    //glClearDepth(0.0f);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LEQUAL);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

     float mat_spec[4] = {0.0,1.0,0.0,0.3};
     float mat_shin = 100.0;
     float mat_ambient[4] = {0.0,0.0,1.0,0.0};
     float mat_diffuse[4] = {0.0,1.0,0.0,0.5};

     float light_pos[4] = {10.0,10.0,0.0,1.0};
     float light_ambient[4] = {1.0,1.0,1.0,1.0};
     float light_diffuse[4] = {1.0,1.0,1.0,1.0};

     float fog_color[4] = {0.0f,0.5f,0,1.0f};

     glMaterialfv(GL_FRONT,GL_SPECULAR,mat_spec);
     glMaterialf(GL_FRONT,GL_SHININESS,76.8f);
     glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
     glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);

     glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
     glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    glFogfv(GL_FOG_COLOR, fog_color);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START,500.0f);
    glFogf(GL_FOG_END, 1000.0f);
    //glFogf(GL_FOG_DENSITY, 0.35f);
    //glEnable(GL_FOG);

     //glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,1.0);
     //glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.001);
     //glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION,0.004);

    camera->SetCamera(0.0f,0.0f,0.0f,1.0f,0.0f,-1.0f);

    if(!this->m_Texture1.loadTGA("data\\texture\\revisySplash.tga"))
        MessageBox(NULL,"error","error splashscreen",MB_OK);

    this->m_cube = NULL;
    //this->m_cube = new Loader3DS("data\\model\\cube.3ds");
    //this->m_cube = new ObjLoader("data\\model\\monkey.obj");
    /*if(!this->m_cube->load())
    {
        Log->WriteText("loader3ds failed load()");
        this->m_cube = NULL;
    }*/

    this->m_environment.initSkybox();

    inGUI->init();

 }

 void mainState::run()
 {
    /*if(angle>360.0f)
        angle = 0;*/

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    this->processPeripherie();
    camera->updateView();

    frustum->getFrustrum();


    glColor3f(0.8,0.8,0.8);
    this->m_environment.renderSkybox(camera->getPosition().x,camera->getPosition().y,camera->getPosition().z,1000,400,1000);
     //glTranslatef(0.0f,0.0f,-6.0f);
     //glRotatef(angle,0,1,0);



     /*  this->m_Texture1.bind();       glBegin(GL_QUADS);
            glTexCoord2f(0.0f,0.0f); glVertex3f(-1.0f,-1.0f,0.0f);
            glTexCoord2f(0.0f,1.0f); glVertex3f(-1.0f,1.0f,0.0f);
            glTexCoord2f(1.0f,1.0f); glVertex3f(1.0f,1.0f,0.0f);
            glTexCoord2f(1.0f,0.0f); glVertex3f(1.0f,-1.0f,0.0f);
        glEnd();*/

/*        glDisable(GL_TEXTURE_2D);

        glPushMatrix();
        glScalef(1000,1,1000);
        glTranslatef(0.0f,-1000.0f,0.0f);
        glColor3f(0.5f,0.5f,0.5f);
        glBegin(GL_QUADS);
            //glColor4f(0.5f,0.5f,0.5f,0.5f);
			glVertex3f(-50.0f,-1.0f, 50.0f);
			glVertex3f( 50.0f,-1.0f, 50.0f);
			glVertex3f( 50.0f,-1.0f,-50.0f);
			glVertex3f(-50.0f,-1.0f,-50.0f);
		glEnd();
		glEnable(GL_TEXTURE_2D);
		glPopMatrix();
*/
    //glColor3f(0.0f,0.0f,0.0);
    //this->m_cube->show();

    if(!fileManager->isInitialized())
        fileManager->GetFilesInFolder(Config->getValue("StartPath"));

    fileManager->renderFiles();


    //fileManager->renderFiles();

    glColor3f(0.0f,1.0f,0.0f);
    //fps->getFPS();
    //fps->getSpeedFactor(60);


    //this->m_font->print(3,0,0,"test");
    //inGUI->render(800,600);
    this->m_font->printEx(-0.95f,0.75f,"FPS: %d, dir: %s",fps->getFPS(), Config->getValue("StartPath"));
    inGUI->render(800,600);

    //angle += 0.05f;
 }

 void mainState::shutdown()
 {
     Log->WriteText("mainState shutdown");

    this->m_Texture1.remove();

     if(this->m_font)
     {

        delete this->m_font;
        this->m_font = NULL;
     }
     if(this->m_cube)
     {
         delete this->m_cube;
         this->m_cube = NULL;
     }

     inGUI->shutdown();
 }

 void mainState::processPeripherie()
 {
     if(fps->getSpeedFactor(60)<60)
     {
        if(GetKeyState('W') & 0x80) camera->Move(DIR_UP, fps->getSpeedFactor(60));
        if(GetKeyState('S') & 0x80) camera->Move(DIR_DOWN, fps->getSpeedFactor(60));
        if(GetKeyState('D') & 0x80) camera->RotateY(DIR_RIGHT, fps->getSpeedFactor(60));
        if(GetKeyState('A') & 0x80) camera->RotateY(DIR_LEFT, fps->getSpeedFactor(60));
        if(GetKeyState(VK_UP) & 0x80) camera->ChangeYLook(DIR_SHOW_UP,fps->getSpeedFactor(60));
        if(GetKeyState(VK_DOWN) & 0x80) camera->ChangeYLook(DIR_SHOW_DOWN,fps->getSpeedFactor(60));
        if(GetKeyState(VK_ADD) & 0x80) camera->setSpeedUp(camera->getSpeedUp()+0.05);
        if(GetKeyState(VK_SUBTRACT) & 0x80) camera->setSpeedUp(camera->getSpeedUp()-0.05);

     }
 }
