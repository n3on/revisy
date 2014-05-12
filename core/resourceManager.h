/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #ifndef RESOURCE_MANAGER_H
 #define RESOURCE_MANAGER_H

 #include <windows.h>
 //#include <stdlib.h>
 #include <map>
 #include "..\gfx_subsys\opengl\objLoader.h"
 #include "..\gfx_subsys\opengl\texture.h"

 using namespace std;

 class ResourceManager
 {
     public:
        ResourceManager();
        ~ResourceManager();

        void Init();
        ObjLoader getModel(char *name);
        static ResourceManager* getInstance();

    private:
        void LoadModels();
        static ResourceManager* m_instance;
        map<char *, ObjLoader> m_models;

 };

 #define resource ResourceManager::getInstance()

 #endif
