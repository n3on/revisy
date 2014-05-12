/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

#ifndef _SKYBOX_H
#define _SKYBOX_H

#include "Texture.h"

#define SB_FRONT 0
#define SB_BACK 1
#define SB_LEFT 2
#define SB_RIGHT 3
#define SB_BOTTOM 4
#define SB_TOP 5

class skybox
{
public:
	skybox();
	~skybox();

	void initSkybox();
	void renderSkybox(float posX, float posY, float posZ, int width, int height, int lgth);
	void remove();

private:
	unsigned int dList;
	Texture texture[6];
};

#endif