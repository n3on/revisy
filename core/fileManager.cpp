/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/


#include "fileManager.h"

FileManager* FileManager::m_instance = NULL;

FileManager::FileManager()
{
    //this->m_fileModel.loadFile();
    this->m_list = 0;
    this->m_initFolder = false;

    this->m_hdc = GetDC(Config->getHWND());
    m_font = new OutFont(this->m_hdc);

}

FileManager::~FileManager()
{
     ReleaseDC(Config->getHWND(),this->m_hdc);
}

FileManager* FileManager::getInstance()
{
    if(FileManager::m_instance==NULL)
        FileManager::m_instance = new FileManager();

    return FileManager::m_instance;
}

void FileManager::renderFiles()
{
    //glPushMatrix();

    //if(!this->m_list)
    //{
       // this->m_list = glGenLists(1);
       // glNewList(this->m_list, GL_COMPILE);
        //glScalef(this->m_files[0].width,this->m_files[0].height,this->m_files[0].depth);
        //this->m_file.render();

        //printf("pos: x = %f, y = %f, z = %f\n",camera->getPosition().x, camera->getPosition().y,camera->getPosition().z);

        for(int i=0; i<this->m_files.size(); i++)
        {
            //glPushMatrix();
            //glRotatef(180.0f,0.0f,1.0f,0.0f);

            if(frustum->boxCheck(this->m_files[i].getPosition().x,
                                    this->m_files[i].getPosition().y,
                                    this->m_files[i].getPosition().z,
                                    this->m_files[i].width,
                                    this->m_files[i].height,
                                    this->m_files[i].depth))
           {
               glPushMatrix();


               /*        printf("pos: x = %f, y = %f, z = %f\n",camera->getPosition().x, camera->getPosition().y,camera->getPosition().z);

               printf("render: i = %d, x1 = %f, y2 = %f, z3 = %f\n",i,this->m_files[i].getPosition().x,
                                    this->m_files[i].getPosition().y,
                                    this->m_files[i].getPosition().z);*/


                //glPopMatrix();
                //glPushMatrix();
                this->m_files[i].render();

                glColor3f(0.0f,1.0f,0.0f);
                this->m_font->setBody(this->m_files[i].width,
                                      this->m_files[i].height,
                                      this->m_files[i].depth);

                this->m_font->print(this->m_files[i].getPosition().x,
                                this->m_files[i].getPosition().y+this->m_files[i].height+1,
                                this->m_files[i].getPosition().z,
                                this->m_files[i].getFileName());


                /*if(((abs(camera->getPosition().x-this->m_files[i].getPosition().x))<=this->m_files[i].width) &&
                   ((abs(camera->getPosition().y-this->m_files[i].getPosition().y))<=this->m_files[i].height)  &&
                   ((abs(camera->getPosition().z-this->m_files[i].getPosition().z))<=this->m_files[i].depth))
                {*/
                if(this->m_files[i].objectCollision(camera->getPosition()))
                {

                    if(this->m_files[i].getFileType()==FILE_TYPE_DIR)
                    {
                        this->m_initFolder = false;
                        //MessageBox(NULL,Config->getValue("StartPath"),"BeforePath",MB_OK);
                        char *newPath;
                        newPath = new char[1024];
                        //char *oldPath;
                        //memset(newPath,0,sizeof(newPath));
                        //oldPath = new char[1024];
                        strncpy(newPath, Config->getValue("StartPath"),strlen(Config->getValue("StartPath")));
                        newPath[strlen(Config->getValue("StartPath"))-1] = '\0';
                        //MessageBox(NULL,newPath,"NewPath",MB_OK);
                        sprintf(newPath,"%s%s\\*",newPath,this->m_files[i].getFileName());
                        //Config->makeEntry("StartPath",newPath);
                        Config->makeEntry("StartPath",newPath);
                        //MessageBox(NULL,Config->getValue("StartPath"),"StartPath",MB_OK);
                        camera->SetCamera(0,
                                  0,
                                  0,
                                  1,
                                  0,
                                  -1);

                        this->m_files.clear();

                    }
                    else
                    {
                         if(GetKeyState('W') & 0x80) camera->Move(DIR_DOWN, fps->getSpeedFactor(60));
                         if(GetKeyState('S') & 0x80) camera->Move(DIR_UP, fps->getSpeedFactor(60));
                         if(GetKeyState('D') & 0x80) camera->RotateY(DIR_LEFT, fps->getSpeedFactor(60));
                         if(GetKeyState('A') & 0x80) camera->RotateY(DIR_RIGHT, fps->getSpeedFactor(60));

                    }



                }

  //              printf("pos: x = %f, y = %f, z = %f\n",camera->getPosition().x, camera->getPosition().y,camera->getPosition().z);
                glPopMatrix();

            }
            else
            {
                //this->m_files[i].moveObject(this->m_files[i].getPosition().x,
                //                            this->m_files[i].getPosition().y+30.0f,
                //                            this->m_files[i].getPosition().z);

                /*glPushMatrix();
                glColor3f(1.0f,0.0f,0.0f);
                this->m_files[i].render();
                glPopMatrix();*/

            }
        }
        //glPopMatrix();
     //   glEndList();
    //}
    //else
    //        glCallList(this->m_list);
}

bool FileManager::isInitialized()
{
    return this->m_initFolder;
}

void FileManager::GetFilesInFolder(const char *path)
{
    //File fileModel;
    WIN32_FIND_DATA fileData;

    //glPushMatrix();
    //if(!this->m_list)
    //{
 //       glPushMatrix();
      //  this->m_list = glGenLists(1);
      //  glNewList(this->m_list, GL_COMPILE);

    this->m_fileHandle = FindFirstFile(path, &fileData);


        //fileModel.setPosition(0.0f,0.0f,0.0f);
        //glTranslatef(0.0f,0.0f,0.0f);

        float x = 160.0f;
        float y = 130.0f;
        float z = -100.0f;
        float posX = 0;
        float posY = 0;
        float posZ = 0;
        int numRowX = 0;
        int numRowZ = 0;


    do
    {
        File fileModel;
        fileModel.setFileName(fileData.cFileName);

        switch(fileData.dwFileAttributes)
        {
            case FILE_ATTRIBUTE_SYSTEM:
            case FILE_ATTRIBUTE_READONLY:
            case FILE_ATTRIBUTE_ARCHIVE:
            case FILE_ATTRIBUTE_NORMAL:
            case FILE_ATTRIBUTE_COMPRESSED:
            case FILE_ATTRIBUTE_TEMPORARY:
            case FILE_ATTRIBUTE_SPARSE_FILE:
            case FILE_ATTRIBUTE_REPARSE_POINT:
            case FILE_ATTRIBUTE_OFFLINE:
            case FILE_ATTRIBUTE_HIDDEN:
            case FILE_ATTRIBUTE_ENCRYPTED:
            case FILE_ATTRIBUTE_DIRECTORY:
            {
                fileModel.width = 8;
                fileModel.height = 16;
                fileModel.depth = 8;
                fileModel.setFileType(FILE_TYPE_DIR);
            }break;

            default:
            {
                fileModel.width = 16;
                fileModel.height = 16;
                fileModel.depth = 16;
                fileModel.setFileType(FILE_TYPE_NON);
            }break;
        }

        //if (!(((m_fileData.cFileName[0]=='.') && (m_fileData.cFileName[1]=='.')||(m_fileData.cFileName[1]==0))))
        //{
            if(numRowX<10)
            {
              /*  if(numRowZ>=10)
                {
                    this->m_file.moveObject(0.0f,20.0f,0.0f);
                    //glTranslatef(0.0f,100.0f,0.0f);
                    z = -z;
                    numRowZ = 0;
                }
                else*/
                    posX += x;
                    fileModel.moveObject(posX,posY,posZ);
                    //glTranslatef(x,0.0f,0.0f);
            }
            else
            {
                //glTranslatef(0.0f,0.0f,z);
                //x = -10*x;
                numRowZ++;
                numRowX = 0;
                //z = 20.0f;

                posX = x;
                posZ += z;
                fileModel.moveObject(posX,posY,posZ);
            }

            if(numRowZ>=10)
            {
                numRowZ = 0;

                posZ = z;
                posY += y;
            }

            //MessageBox(NULL,"File Found","Info",MB_OK);
            //glTranslatef(x,0.0f,z);
            //this->renderFiles();

            //i+=0.5;
            numRowX++;
            //this->m_file.moveObject(x,0.0f,0.0f);
            //this->m_file.moveObject(200.0f,0.0f,0.0f);

            this->m_files.push_back(fileModel);

            //this->renderFiles();
        //}
    }while(FindNextFile(this->m_fileHandle,&fileData));

    //i=0.0f;

//    glPopMatrix();

    FindClose(this->m_fileHandle);
    //glEndList();
    //}
    //else
    //        glCallList(this->m_list);
    this->m_initFolder = true;

}

