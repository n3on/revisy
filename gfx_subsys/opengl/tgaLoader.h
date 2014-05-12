/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #ifndef TGA_LOADER_H
 #define TGA_LOADER

 class TGALoader
 {
     public:
        TGALoader();
        ~TGALoader();

        bool load(const char *filename);
        void unload();

        unsigned short getWidth();
        void setWidth(unsigned short width);
        unsigned short getHeight();
        void setHeight(unsigned short height);
        unsigned char* getData();
        int getType();


        unsigned int imageID;

     private:

        unsigned char m_colorDepth;
        unsigned char m_ColorType;
        unsigned char m_dataFormat;
        unsigned char *m_imageData;
        unsigned short m_width;
        unsigned short m_height;
        unsigned long m_imageSize;

 };

 #endif
