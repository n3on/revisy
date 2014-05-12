/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #include "resourceManager.h"

 ResourceManager* ResourceManager::m_instance = NULL;

 ResourceManager* ResourceManager::getInstance()
 {
     if(!ResourceManager::m_instance)
        ResourceManager::m_instance = new ResourceManager();

    return ResourceManager::m_instance;
 }

 ResourceManager::ResourceManager()
 {

 }

 ResourceManager::~ResourceManager()
 {

 }

 void ResourceManager::Init()
 {
    this->LoadModels();
 }

 void ResourceManager::LoadModels()
 {
    ObjLoader model("data\\model\\cube.obj");
    model.load();
    pair<char *, ObjLoader> modelEntry;
    modelEntry.first ="File";
    modelEntry.second = model;
    this->m_models.insert(modelEntry);

    ObjLoader model2("data\\model\\sphere.obj");
    model2.load();
    modelEntry.first = "NormalFile";
    modelEntry.second = model2;
    this->m_models.insert(modelEntry);
 }

 ObjLoader ResourceManager::getModel(char *name)
 {
     map<char *, ObjLoader>::iterator i;

     for(i = this->m_models.begin(); i!=this->m_models.end(); ++i)
     {
         if(strcmp(name,i->first)==0)
            return i->second;
     }

     /*i = this->m_models.find(name);
     if(i!=this->m_models.end())
     {
        printf("found\n");
        return i->second;
     }
    else
    {
        printf("not found\n");
        return 0;
    }*/
 }
