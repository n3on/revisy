/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #include "texture.h"

 Texture::Texture()
 {
     glEnable(GL_TEXTURE_2D);
     this->m_tgaTexture = NULL;
 }

 Texture::~Texture()
 {

 }

 bool Texture::loadTGA(const char *path)
 {
     this->m_tgaTexture = new TGALoader();
     if(!this->m_tgaTexture->load(path))
        return false;

    glGenTextures(1,&this->m_tgaTexture->imageID);

    glBindTexture(GL_TEXTURE_2D, this->m_tgaTexture->imageID);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    int type = this->m_tgaTexture->getType();
    if(type==3)
        type = GL_RGB;
    else
    {
        type = GL_RGBA;
        glEnable(GL_BLEND);
         glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    }

        gluBuild2DMipmaps(GL_TEXTURE_2D,type,this->m_tgaTexture->getWidth(),
                        this->m_tgaTexture->getHeight(),type,GL_UNSIGNED_BYTE,
                        this->m_tgaTexture->getData());

     return true;
 }

 void Texture::bind()
 {
     glBindTexture(GL_TEXTURE_2D,this->m_tgaTexture->imageID);
 }

 void Texture::show(int x, int y, int width, int height)
 {
     this->bind();

     glBegin(GL_QUADS);
		/*glTexCoord2f(1.0f,0.0f);
		glVertex3f(x,y,0.0f);
		glTexCoord2f(1.0f,1.0f);
		glVertex3f(x,y+height,0.0f);
		glTexCoord2f(0.0f,1.0f);
		glVertex3f(x+width,y+height,0.0f);
		glTexCoord2f(0.0f,0.0f);
		glVertex3f(x+width,y,0.0f);*/

        glTexCoord2f(0.0f,1.0f);
		glVertex3f(x,y,0.0f);
		glTexCoord2f(0.0f,0.0f);
		glVertex3f(x,y+height,0.0f);
		glTexCoord2f(1.0f,0.0f);
		glVertex3f(x+width,y+height,0.0f);
		glTexCoord2f(1.0f,1.0f);
		glVertex3f(x+width,y,0.0f);

     glEnd();
 }

 void Texture::remove()
 {
     if(this->m_tgaTexture != NULL)
     {
        this->m_tgaTexture->unload();
        delete this->m_tgaTexture;
        this->m_tgaTexture = NULL;
     }
 }
