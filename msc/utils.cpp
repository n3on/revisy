/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/
#include "utils.h"

FPS* FPS::m_instance = NULL;


int FPS::getFPS()
{
    this->m_currTime = GetTickCount()*0.001f;

    this->m_numFPS++;

    if(this->m_currTime-this->m_prevTime > 1)
    {
        this->m_prevTime = this->m_currTime;
        this->m_tempFPS = this->m_numFPS;
        this->m_numFPS = 0;
    }

    return this->m_tempFPS;

}

float FPS::getSpeedFactor(int expectedFPS)
{
    if(expectedFPS <= 0)
        expectedFPS = 1;

    return (float)expectedFPS/this->m_tempFPS;
    //return (float)this->m_tempFPS/expectedFPS;
}

FPS* FPS::getInstance()
{
    if(FPS::m_instance == NULL)
    FPS::m_instance = new FPS();

    return FPS::m_instance;
}

