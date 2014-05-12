/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #include "stateManager.h"

 stateManager *stateManager::m_Instance = NULL;

 stateManager::stateManager()
                :m_currentState(SM_SPLASH)
 {
     this->m_currentAction = new splashState;

 }

 stateManager::~stateManager()
 {

 }

 stateManager* stateManager::getInstance()
 {
     if(!stateManager::m_Instance)
     {
         stateManager::m_Instance = new stateManager;
     }

     return stateManager::m_Instance;
 }

 void stateManager::setState(States state)
 {
     switch(state)
     {
         case SM_SPLASH:
         {
             this->m_currentState = SM_SPLASH;
             this->m_currentAction = new splashState;
         }break;

         case SM_MAIN:
         {
             this->m_currentState = SM_MAIN;
             this->m_currentAction = new mainState;
         }break;
     }
 }

 States stateManager::getState()
 {
     return this->m_currentState;
 }

 void stateManager::setView(int width, int height)
 {
     if(this->m_currentAction!=NULL)
        this->m_currentAction->setView(width, height);
 }

 void stateManager::init(HDC hdc)
 {
     if(this->m_currentAction!=NULL)
        this->m_currentAction->init(hdc);
 }

 void stateManager::run()
 {
     if(this->m_currentAction!=NULL)
        this->m_currentAction->run();
 }

 void stateManager::shutdown()
 {
     if(this->m_currentAction!=NULL)
        this->m_currentAction->shutdown();
 }




