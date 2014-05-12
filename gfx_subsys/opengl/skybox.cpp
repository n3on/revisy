/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

#include "skybox.h"

skybox::skybox() : dList(0)
{

}

skybox::~skybox()
{

}

void skybox::initSkybox()
{
	/*this->texture[SB_FRONT].LoadTGA("skybox_ft.tga");
	this->texture[SB_BACK].LoadTGA("skybox_bk.tga");
	this->texture[SB_LEFT].LoadTGA("skybox_lf.tga");
	this->texture[SB_RIGHT].LoadTGA("skybox_rt.tga");
	this->texture[SB_TOP].LoadTGA("skybox_up.tga");
	this->texture[SB_BOTTOM].LoadTGA("skybox_down.tga");*/
	this->texture[SB_FRONT].loadTGA("data\\skybox\\wall.tga");
	this->texture[SB_BACK].loadTGA("data\\skybox\\wall.tga");
	this->texture[SB_LEFT].loadTGA("data\\skybox\\wall.tga");
	this->texture[SB_RIGHT].loadTGA("data\\skybox\\wall.tga");
	this->texture[SB_TOP].loadTGA("data\\skybox\\back.tga");
	this->texture[SB_BOTTOM].loadTGA("data\\skybox\\back.tga");

}

void skybox::renderSkybox(float posX, float posY, float posZ, int width, int height, int lgth)
{

    glDisable(GL_LIGHTING);

	/*if(this->dList == 0)
	{*/
		//this->dList = glGenLists(1);
		//glNewList(this->dList, GL_COMPILE);

		posX = posX-width/2;
		posY = posY-height/2;
		posZ = posZ-lgth/2;

		this->texture[SB_FRONT].bind();
		glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(posX,		  posY,		posZ+lgth);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(posX,		  posY+height, posZ+lgth);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(posX+width, posY+height, posZ+lgth);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(posX+width, posY,		posZ+lgth);
		glEnd();

		this->texture[SB_BACK].bind();
		glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(posX+width, posY,		posZ);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(posX+width, posY+height, posZ);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(posX,		  posY+height,	posZ);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(posX,		  posY,		posZ);
		glEnd();

		this->texture[SB_LEFT].bind();
		glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(posX,		  posY+height,	posZ);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(posX,		  posY+height,	posZ+lgth);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(posX,		  posY,		posZ+lgth);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(posX,		  posY,		posZ);
		glEnd();

		this->texture[SB_RIGHT].bind();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(posX+width, posY,		posZ);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(posX+width, posY,		posZ+lgth);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(posX+width, posY+height,	posZ+lgth);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(posX+width, posY+height,	posZ);
		glEnd();

		this->texture[SB_TOP].bind();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(posX+width, posY+height, posZ);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(posX+width, posY+height, posZ+lgth);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(posX,		  posY+height,	posZ+lgth);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(posX,		  posY+height,	posZ);
		glEnd();

		this->texture[SB_BOTTOM].bind();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(posX,		  posY,		posZ);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(posX,		  posY,		posZ+lgth);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(posX+width, posY,		posZ+lgth);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(posX+width, posY,		posZ);
		glEnd();

		glEnable(GL_LIGHTING);

		//glEndList();
	/*}
	else
		glCallList(this->dList);
*/
}

void skybox::remove()
{
	this->dList = NULL;

	for(int i=0; i<6; i++)
		this->texture[i].remove();

	delete[] this->texture;
}
