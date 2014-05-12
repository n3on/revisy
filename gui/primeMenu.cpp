/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #include "primeMenu.h"

 PrimeMenu::PrimeMenu()
 {

 }

 PrimeMenu::~PrimeMenu()
 {

 }

 void PrimeMenu::init()
 {
     this->m_isHovered[0] = NORMAL;
     this->m_isHovered[1] = NORMAL;
     this->m_isHovered[2] = NORMAL;

     glEnable(GL_TEXTURE_2D);
     if(!this->m_primeMenu.loadTGA("data\\gui\\primeMenu.tga"))
             MessageBox(NULL,"couldn't load texture","error",MB_OK);
    if(!this->m_close[NORMAL].loadTGA("data\\gui\\x.tga"))
             MessageBox(NULL,"couldn't load texture","error",MB_OK);
    if(!this->m_close[HOVERED].loadTGA("data\\gui\\x_h.tga"))
             MessageBox(NULL,"couldn't load texture","error",MB_OK);
    if(!this->m_size[NORMAL].loadTGA("data\\gui\\o.tga"))
             MessageBox(NULL,"couldn't load texture","error",MB_OK);
    if(!this->m_size[HOVERED].loadTGA("data\\gui\\o_h.tga"))
             MessageBox(NULL,"couldn't load texture","error",MB_OK);
    if(!this->m_minimize[NORMAL].loadTGA("data\\gui\\down.tga"))
             MessageBox(NULL,"couldn't load texture","error",MB_OK);
    if(!this->m_minimize[HOVERED].loadTGA("data\\gui\\down_h.tga"))
             MessageBox(NULL,"couldn't load texture","error",MB_OK);

 }

 void PrimeMenu::render(int width, int height)
 {
    this->m_primeMenu.show(width-(width/6),0,width/6,height/8);
    this->m_close[this->m_isHovered[0]].show(width-(width/16),height/40,width/25,height/16);
    this->m_size[this->m_isHovered[1]].show(width-(width/10),height/40,width/25,height/16);
    this->m_minimize[this->m_isHovered[2]].show(width-(width/8),height/40,width/25,height/16);

    this->processCollision(width, height);
 }

 void PrimeMenu::processCollision(int width, int height)
 {
     POINT position = Mouse::getPosition();

     if(position.x>(width-(width/16)) && position.x<width &&
                    position.y>height/40 && position.y<height/16)
    {
            this->m_isHovered[0] = HOVERED;
            if(Mouse::getLState())
                SendMessage(Config->getHWND(),WM_DESTROY,0,0);
    }
     else
     {
            this->m_isHovered[0] = NORMAL;
     }

     if(position.x>(width-(width/10)) && position.x<(width-(width/15)) &&
                    position.y>height/40 && position.y<height/16)
            this->m_isHovered[1] = HOVERED;
     else
            this->m_isHovered[1] = NORMAL;

    if(position.x>(width-(width/8)) && position.x<(width-(width/10)) &&
                    position.y>height/40 && position.y<height/10)
    {
            this->m_isHovered[2] = HOVERED;
            if(Mouse::getLState())
                MessageBox(NULL,"send","send",MB_OK);
    }
     else
     {
            this->m_isHovered[2] = NORMAL;
     }
 }

 void PrimeMenu::shutdown()
 {
    this->m_primeMenu.remove();
    this->m_close[NORMAL].remove();
    this->m_close[HOVERED].remove();
    this->m_size[NORMAL].remove();
    this->m_size[HOVERED].remove();
    this->m_minimize[NORMAL].remove();
    this->m_minimize[HOVERED].remove();
 }