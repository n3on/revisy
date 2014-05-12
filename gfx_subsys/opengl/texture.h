/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #ifndef TEXTURE_H
 #define TEXTURE_H

 #include <GL\gl.h>
 #include <GL\glu.h>
 #include <stdio.h>
 #include "tgaLoader.h"

 class Texture
 {
     public:
        Texture();
        ~Texture();

        bool loadTGA(const char *image);
        void bind();

        void show(int x, int y, int width, int height);

        void remove();

     private:
        TGALoader *m_tgaTexture;

 };

 #endif
