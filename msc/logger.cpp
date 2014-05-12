/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

#include "logger.h"

Logger *Logger::instance = NULL;

Logger::Logger()
{

}

Logger::~Logger()
{
    //this->WriteText("Logger closed\n");
    //fclose(this->m_outputFile);
}

Logger *Logger::getInstance()
{
    if(!Logger::instance)
    {
        Logger::instance = new Logger;
    }

    return Logger::instance;
}

void Logger::Create(const char *Name)
{
    if(!this->m_outputFile)
    {
        this->m_outputFile = fopen(Name,"w");
    }
    else
    {
        this->m_outputFile = fopen(Name, "a");
    }

}

void Logger::Destroy()
{
    fclose(this->m_outputFile);
}

void Logger::WriteText(const char *String)
{
    this->Create("log.nfo");
    fprintf(this->m_outputFile, String);
    fprintf(this->m_outputFile, "\n");
    fflush(this->m_outputFile);
    this->Destroy();
}

void Logger::ExWriteText(const char *String, ...)
{
    this->Create("log.nfo");
    char buffer[256];
    va_list varList;

    va_start(varList,String);
    vsprintf(buffer,String,varList);
    va_end(varList);

    this->WriteText(buffer);
    this->Destroy();

}
