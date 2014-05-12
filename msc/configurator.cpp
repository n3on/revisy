/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #include "configurator.h"

 Configurator *Configurator::m_instance = NULL;

 Configurator::Configurator()
 {
    this->m_devider = '=';
    this->m_hwnd = NULL;
 }

 Configurator::~Configurator()
 {
 }

 Configurator* Configurator::getInstance()
 {
     if(Configurator::m_instance==NULL)
        Configurator::m_instance = new Configurator;

    return Configurator::m_instance;
 }

 bool Configurator::init(char *path)
 {
     if(strlen(path)>512)
        return false;

     this->m_configFile = NULL;

     if(!(this->m_configFile = fopen(path,"r")))
        return false;

    char tempKey[255];
    char tempValue[255];
    char tempLine[512];
    char *tempDeviderPos;

    memset(tempLine,'\0',sizeof(tempLine));

    int i=0;
    char byte = '\0';
    int numTerminator = 0;
    while(!feof(this->m_configFile))
    {
        if(i>512)
            break;

        fread(&byte,sizeof(char),1,this->m_configFile);

        //printf("byte %c, %d\n",byte, byte);

        if(byte > 0x20)
        {
            tempLine[i] = byte;
            i++;
        }
        if(byte<0x20 || feof(this->m_configFile))
        {

            //tempLine[strlen(tempLine)]='\0';

            char **tokenArray;

            //printf("string %s\n",tempLine);

             if((tokenArray = this->tokenize(tempLine))!=NULL)
             {
                this->makeEntry(tokenArray[0],tokenArray[1]);

             }
             delete[] tokenArray;

             memset(tempLine,'\0',sizeof(tempLine));
             i=0;
        }
    }

         fclose(this->m_configFile);

    return true;
 }

 char** Configurator::tokenize(char* line)
 {
     char **tokenArray = new char*[2];
     tokenArray[0] = new char[256];
     tokenArray[1] = new char[256];

     char *tempDeviderPos;
     int deviderPos;

      if((tempDeviderPos = strchr(line,this->m_devider))!=NULL)
      {

        deviderPos = tempDeviderPos-line+1;

        int i;
        for(i=0; i<deviderPos-1; i++)
        {
            tokenArray[0][i] = line[i];
        }
        tokenArray[0][i] = '\0';

        int j;
        for(i=deviderPos, j=0; i<=strlen(line)-1; i++, j++)
        {
            tokenArray[1][j] = line[i];

        }
        tokenArray[1][j] = '\0';

        return tokenArray;
      }


      delete[] tokenArray;

      return NULL;
 }

 void Configurator::makeEntry(char* key, char* value)
 {
     this->m_ConfigTable.erase(key);
     this->m_ConfigEntry = make_pair(key, value);
     this->m_ConfigTable.insert(this->m_ConfigEntry);
 }

 char* Configurator::getValue(char* key)
 {
     //this->m_ConfigIter = this->m_ConfigTable.find(key);
     //if(this->m_ConfigIter!=this->m_ConfigTable.end())
     //   return this->m_ConfigIter->second;
     for(this->m_ConfigIter = this->m_ConfigTable.begin(); this->m_ConfigIter!=this->m_ConfigTable.end(); ++this->m_ConfigIter)
     {
         if(strcmp(key,this->m_ConfigIter->first)==0)
            return this->m_ConfigIter->second;

     }

     return NULL;

 }

 void Configurator::setValue(char *key, char *value)
 {
        this->m_ConfigTable[key] = value;
 }

 int Configurator::getIntValue(char* key)
 {
     char *tempStr = new char[256];

     if(strcmp(this->getValue(key),"DEFAULT")==0)
     {
         if(strcmp(key,CLIENT_WIDTH)==0)
            return GetSystemMetrics(SM_CXSCREEN);
         if(strcmp(key,CLIENT_HEIGHT)==0)
            return GetSystemMetrics(SM_CYSCREEN);
     }

     tempStr = this->getValue(key);
     int intStr = 0;

     for(int i=strlen(tempStr)-1, j=0; i>=0; --i, ++j)
     {
        if((tempStr[i]-48)>9 || (tempStr[i]-48)<0)
            return -1;

        intStr+=(tempStr[i]-48)*(pow(10.0,j));
        if(intStr>=INT_MAX)
            return 0;
     }

     delete[] tempStr;
     return intStr;
 }

 void Configurator::setHWND(HWND hwnd)
 {
     this->m_hwnd = hwnd;
 }

 HWND Configurator::getHWND()
 {
     return this->m_hwnd;
 }


