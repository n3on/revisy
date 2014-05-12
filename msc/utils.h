/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

#ifndef UTILS_H
#define UTILS_H

#include <windows.h>

class FPS
{
    public:
        FPS()
        {
            this->m_numFPS = 0;
            this->m_currTime = 0.0f;
            this->m_prevTime = 0.0f;
            this->m_tempFPS = 1;
        }
        ~FPS()
        {
        }

        int getFPS();
        float getSpeedFactor(int expectedFPS);

        static FPS* getInstance();

    private:
        static FPS *m_instance;
        int m_numFPS;
        int m_tempFPS;
        float m_currTime;
        float m_prevTime;
};

#define fps FPS::getInstance()
#endif
