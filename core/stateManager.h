/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #ifndef STATE_MANAGER_H
 #define STATE_MANAGER_H

 #include <stdio.h>
 #include "programState.h"
 #include "splashState.h"
 #include "mainState.h"

 enum States
 {
     SM_SPLASH,
     SM_MAIN
 };

 class stateManager
 {
     public:
        stateManager();
        ~stateManager();

        static stateManager* getInstance();

        void setView(int width, int height);
        void init(HDC hdc);
        void run();
        void shutdown();

        void setState(States state);
        States getState();

    private:
        static stateManager *m_Instance;
        States m_currentState;
        programState *m_currentAction;

 };

 #define ProgramState stateManager::getInstance()

 #endif
