/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #include "file.h"

 File::File()
 {
     //this->m_hdc = GetDC(Config->getHWND());
     this->m_fileName = new char[256];
     //HDC hdc = GetDC(Config->getHWND());
    //m_font = new OutFont(this->m_hdc);
 }

 File::~File()
 {
        //ReleaseDC(Config->getHWND(),this->m_hdc);
 }

// void File::loadFile()
// {
    //this->m_fileObject.init("data\\model\\cube.obj");
    //if(!this->m_fileObject.load())
    //    MessageBox(NULL,"couldn't load file","Error",MB_OK);
// }

bool File::objectCollision(Vector3D point)
{
    if(((abs((int)(point.x-this->m_position.x)))<=this->width) &&
       ((abs((int)(point.y-this->m_position.y)))<=this->height)  &&
       ((abs((int)(point.z-this->m_position.z)))<=this->depth))
    {
        return true;
    }
    else
    {
        return false;
    }
}

 void File::setPosition(Vector3D position)
 {
     this->m_position = position;
 }

 void File::setPosition(float x, float y, float z)
 {
    this->m_position.x = x;
    this->m_position.y = y;
    this->m_position.z = z;
 }


 void File::moveObject(float x, float y, float z)
 {
     //glPushMatrix();
     //this->m_position.x += x;
     //this->m_position.y += y;
     //this->m_position.z += z;
    this->setPosition(x,y,z);

        //glTranslatef(this->m_position.x,this->m_position.y,this->m_position.z);
        //this->setPosition(x,y,z);
     //glPopMatrix();
 }

 Vector3D File::getPosition()
 {
     return this->m_position;
 }

 void File::setFileName(char *filename)
 {
     if(strlen(filename)>256)
     {
            return;
     }

     strcpy(this->m_fileName, filename);
 }

 char* File::getFileName()
 {
     return this->m_fileName;
 }

 FileType File::getFileType()
 {
     return this->m_type;
 }

 void File::setFileType(FileType newFileType)
 {
        this->m_type = newFileType;
 }

 void File::render()
 {
     glPushMatrix();
     glTranslatef(this->m_position.x,
                    this->m_position.y,
                    this->m_position.z);
    glScalef(this->width, this->height, this->depth);
     //glPopMatrix();
     //this->m_fileObject.show();
     switch(this->m_type)
     {
         case FILE_TYPE_DIR:
         {
            resource->getModel("File").show();
         }//break;
         case FILE_TYPE_NON:
         {
            resource->getModel(/*"NormalFile"*/"File").show();
         }break;
     }

     glPopMatrix();
     //glPushMatrix();
     //glColor3f(0.0f,1.0f,0.0f);
     //this->m_font->print(this->m_position.x,this->m_position.y+0.5,this->m_position.z,
     //                       this->m_fileName);
     //glPopMatrix();
 }
