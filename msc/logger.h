/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

#ifndef LOGGER_H
#define LOGGER_H

#include <windows.h>
#include <stdio.h>

class Logger
{
    public:
        Logger();
        ~Logger();

        void Create(const char *Name);
        void Destroy();
        void WriteText(const char *String);
        void ExWriteText(const char *String, ...);


        static Logger *getInstance();

    private:
        static Logger *instance;
        FILE *m_outputFile;
};

#define  Log Logger::getInstance()

#endif
