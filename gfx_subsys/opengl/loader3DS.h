/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

//
//
//3DS-Format:
//	Identifier = 2 Byte
//	Lenght of Identifier = 4 Byte
//

#ifndef LOADER_3DS_H
#define LOADER_3DS_H

#include <stdlib.h>
#include <stdio.h>
#include <GL\gl.h>
#include <GL\glu.h>

#define MAINCHUNK 0x4D4D
#define   EDITORCHUNK 0x3D3D
#define      OBJECTBLOCK 0x4000
#define         TRIANGULARMESH 0x4100
#define            VERTICESLIST 0x4110
#define            FACESDESCRIPTION 0x4120
#define               FACESMATERIAL 0x4130
#define            MAPPINGCOORDINATESLIST 0x4140
#define               SMOOTHINGGROUPLIST 0x4150
#define            LOCALCOORDINATESSYSTEM 0x4160
#define         LIGHT 0x4600
#define            SPOTLIGHT 0x4610
#define         CAMERA 0x4700
#define      MATERIALBLOCK 0xAFFF
#define         MATERIALNAME 0xA000
#define         AMBIENTCOLOR 0xA010
#define         DIFFUSECOLOR 0xA020
#define         SPECULARCOLOR 0xA030
#define         TEXTUREMAP 1 0xA200
#define         BUMPMAP 0xA230
#define         REFLECTIONMAP 0xA220
#define            MAPPINGFILENAME 0xA300
#define            MAPPINGPARAMETERS 0xA351
#define      KEYFRAMERCHUNK 0xB000
#define         MESHINFORMATION BLOCK 0xB002
#define         SPOTLIGHTINFORMATIONBLOCK 0xB007
#define         FRAMES 0xB008
#define            OBJECTNAME 0xB010
#define            OBJECTPIVOTPOINT 0xB013
#define            POSITIONTRACK 0xB020
#define            ROTATIONTRACK 0xB021
#define            SCALETRACK 0xB022
#define            HIERARCHYPOSITION 0xB030

struct Vertex
{
	Vertex()
	{
		x=y=z=0.0f;
	}
	~Vertex()
	{
	};

	float x, y, z;
};

struct Face
{
	Face()
	{
	}
	~Face()
	{
	}

	unsigned short vertex[3];
};

struct uvCoord
{
    float u,v;
};

class Loader3DS
{
	public:
		Loader3DS(char *filename);
		~Loader3DS();

		bool load();
		void show();

	private:
		FILE *modelFile;
		char *objName;

		unsigned short vertexNum;
		Vertex *vertices;

		unsigned short faceNum;
		unsigned short faceFlag;
		Face *faces;

		unsigned short uvNum;
		uvCoord *mapCoord;

		void readChunk();

		void bigEndian(unsigned int *num);
		void bigEndian(unsigned short *num);
		unsigned char readByte();
		unsigned short read2Byte();
		unsigned int read4Byte();
		float readFloat();

		char* readnByte(int numBytes);

};

#endif

