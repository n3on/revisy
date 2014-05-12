/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

#include <windows.h>
#include <stdio.h>
#include "tgaLoader.h"

 TGALoader::TGALoader()
 {
     this->imageID = 0;
     this->m_imageData = NULL;
     this->m_width = 0;
     this->m_height = 0;
 }

 TGALoader::~TGALoader()
 {
 }

 unsigned short TGALoader::getWidth()
 {
     return this->m_width;
 }
 void TGALoader::setWidth(unsigned short width)
 {
     this->m_width = width;
 }
 unsigned short TGALoader::getHeight()
 {
     return this->m_height;
 }
 void TGALoader::setHeight(unsigned short height)
 {
     this->m_height = height;
 }
 unsigned char* TGALoader::getData()
 {
     return this->m_imageData;
 }

 bool TGALoader::load(const char *filename)
 {
     FILE *file;
     unsigned char uncmpHeader[12] = {0,0,2,0,0,0,0,0,0,0,0,0};
     unsigned char tgaHeader[12];
     unsigned char header[6];

     if(!filename) return false;
     file = fopen(filename, "rb");
     if(!file) return false;

     memset(&header,0,sizeof(header));

     fread(tgaHeader, 1, sizeof(tgaHeader), file);

     if(memcmp(uncmpHeader, tgaHeader, sizeof(uncmpHeader))!=0)
     {
         fclose(file);
         return false;
     }

     fread(header,1,sizeof(header),file);
     this->m_width = header[1]*256+header[0];
     this->m_height = header[3]*256+header[2];

     unsigned char bitCount = header[4];
     int colorMode = bitCount/8;
     long tgaSize = this->m_width * this-> m_height * colorMode;

     this->m_imageData = new unsigned char[sizeof(unsigned char)*tgaSize];
     fread(this->m_imageData,sizeof(unsigned char), tgaSize, file);

     unsigned char tempColor;

     for(long index = 0; index<tgaSize; index+=colorMode)
     {
         tempColor = this->m_imageData[index];
         this->m_imageData[index] = this->m_imageData[index+2];
         this->m_imageData[index+2] = tempColor;
     }

     fclose(file);

     if(colorMode == 3) this->m_ColorType = 3;
     else this->m_ColorType = 4;

     return true;
 }

 int TGALoader::getType()
 {
     return this->m_ColorType;
 }

 void TGALoader::unload()
 {
     if(this->m_imageData)
     {
         delete[] this->m_imageData;
         this->m_imageData = NULL;
     }
 }
