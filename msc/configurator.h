/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #ifndef CONFIGURATOR_H
 #define CONFIGURATOR_H

 #define CLIENT_WIDTH "clientWidth"
 #define CLIENT_HEIGHT "clientHeight"

 #include <windows.h>
 #include <map>
 #include <cmath>
 #include <limits.h>

 using namespace std;

 class Configurator
 {
     public:
        Configurator();
        ~Configurator();

        bool init(char *path);
        char* getValue(char* key);
        void setValue(char* key, char* value);
        int getIntValue(char* key);
        HWND getHWND();
        void setHWND(HWND  hwnd);
        void makeEntry(char *key, char *value);

        static Configurator* getInstance();

     private:
        static Configurator *m_instance;
        FILE *m_configFile;
        map<char *, char *> m_ConfigTable;
        map<char *, char *>::iterator m_ConfigIter;
        pair<char *, char *> m_ConfigEntry;
        HWND m_hwnd;
        char m_devider;

        char** tokenize(char* line);



 };

 #define Config Configurator::getInstance()

 #endif
