/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

#include "loader3DS.h"

Loader3DS::Loader3DS(char *filename)
{
	this->modelFile = fopen(filename,"rb");
	this->objName = new char[512];
	this->vertexNum = 0;
	this->vertices = NULL;
	this->faces = NULL;
	this->mapCoord = NULL;

}

Loader3DS::~Loader3DS()
{
	fclose(this->modelFile);
	if(this->objName!=NULL)
	{
	    delete[] this->objName;
	    this->objName = NULL;
	}
	if(this->vertices!=NULL)
	{
	    delete[] this->vertices;
	    this->vertices = NULL;
	}
	if(this->mapCoord!=NULL)
	{
	    delete[] this->mapCoord;
	    this->mapCoord = NULL;
	}

}

bool Loader3DS::load()
{
	if(this->modelFile == NULL)
		return false;

	this->readChunk();
	return true;
}

void Loader3DS::readChunk()
{
	unsigned short chunkId = 0;
	unsigned int size    = 0;

	chunkId = this->read2Byte();

	if(feof(this->modelFile)==0)
	{
	switch(chunkId)
	{

		case MAINCHUNK:
			{
				size = this->read4Byte();

                this->read4Byte();
				//printf("main chunk. size = %x\n",size);
				this->readChunk();
			}break;

		case EDITORCHUNK:
			{
				size = this->read4Byte();
				//printf("editor chunk. size = %x\n",size);
				this->readChunk();
			}break;



		case OBJECTBLOCK:
			{
				size = this->read4Byte();

				for(int i = 0; (*(this->objName+i) = this->readByte()) && i<=512; i++);

				printf("object block. id = %x size = %x name = %s\n",chunkId,size,objName);

				this->readChunk();
			}break;


		case TRIANGULARMESH:
			{
				size = this->read4Byte();
				printf("trianglemesh chunk. size = %x\n",size);
				this->readChunk();
			}break;

		case VERTICESLIST:
			{
				size = this->read4Byte();
				this->vertexNum = read2Byte();
				printf("vertices list. size = %x, num of Vert = %d\n",size,this->vertexNum);
				this->vertices = new Vertex[this->vertexNum];
				for(int i=0; i<this->vertexNum; i++)
				{
					this->vertices[i].x = this->readFloat();
					this->vertices[i].y = this->readFloat();
					this->vertices[i].z = this->readFloat();

					printf("Vertex %d, x=%f, y=%f, z=%f\n",i,this->vertices[i].x, \
							this->vertices[i].y, this->vertices[i].z);
				}


				      this->readChunk();
			}break;

		case FACESDESCRIPTION:
			{
				size = this->read4Byte();
				this->faceNum = read2Byte();
				printf("face description. size = %x, num of Face = %d\n",size,this->faceNum);
				this->faces = new Face[this->faceNum];
				for(unsigned short i=0; i<this->faceNum; i++)
				{
					this->faces[i].vertex[0] = read2Byte();
					this->faces[i].vertex[1] = read2Byte();
					this->faces[i].vertex[2] = read2Byte();
					this->faceFlag = read2Byte();

					printf("Face %d, p=%u, p2=%u, p3=%u\n",i,this->faces[i].vertex[0],\
							this->faces[i].vertex[1],this->faces[i].vertex[2]);
				}
				this->readChunk();
			}break;

		case MAPPINGCOORDINATESLIST:
			{
				size = this->read4Byte();
				this->uvNum = read2Byte();
				printf(" mapping coordinates list. size = %x, uvNum = %x \n",size, this->uvNum);
				this->mapCoord = new uvCoord[this->uvNum];
				for(int i=0; i<this->uvNum; i++)
				{
				    this->mapCoord[i].u = readFloat();
				    this->mapCoord[i].v = readFloat();

				    printf("UV %d, u = %f, v = %f\n",i,this->mapCoord[i].u,this->mapCoord[i].v);
				}

				this->readChunk();
			}break;

		default:
			{
				//printf("no idea. id = %x\n",chunkId);
				this->readChunk();
			}break;
	}
	}

}

void Loader3DS::show()
{
    if(this->mapCoord!=NULL)
    {
        glBegin(GL_TRIANGLES);
        for(int i=0; i<this->faceNum; i++)
        {
            glTexCoord2f(this->mapCoord[this->faces[i].vertex[0]].u,
                        this->mapCoord[this->faces[i].vertex[0]].v);
            glVertex3f(this->vertices[this->faces[i].vertex[0]].x,
                        this->vertices[this->faces[i].vertex[0]].y,
                        this->vertices[this->faces[i].vertex[0]].z);

            glTexCoord2f(this->mapCoord[this->faces[i].vertex[1]].u,
                        this->mapCoord[this->faces[i].vertex[1]].v);
            glVertex3f(this->vertices[this->faces[i].vertex[1]].x,
                        this->vertices[this->faces[i].vertex[1]].y,
                        this->vertices[this->faces[i].vertex[1]].z);

            glTexCoord2f(this->mapCoord[this->faces[i].vertex[2]].u,
                        this->mapCoord[this->faces[i].vertex[2]].v);
            glVertex3f(this->vertices[this->faces[i].vertex[2]].x,
                        this->vertices[this->faces[i].vertex[2]].y,
                        this->vertices[this->faces[i].vertex[2]].z);
        }
        glEnd();
    }
    else
    {
        glBegin(GL_TRIANGLES);
        for(int i=0; i<this->faceNum; i++)
        {
             glVertex3f(this->vertices[this->faces[i].vertex[0]].x,
                        this->vertices[this->faces[i].vertex[0]].y,
                        this->vertices[this->faces[i].vertex[0]].z);


            glVertex3f(this->vertices[this->faces[i].vertex[1]].x,
                        this->vertices[this->faces[i].vertex[1]].y,
                        this->vertices[this->faces[i].vertex[1]].z);

            glVertex3f(this->vertices[this->faces[i].vertex[2]].x,
                        this->vertices[this->faces[i].vertex[2]].y,
                        this->vertices[this->faces[i].vertex[2]].z);
        }
        glEnd();
    }

}

char* Loader3DS::readnByte(int numBytes)
{
	char *buffer;
	buffer = new char[numBytes];
	fread(buffer,sizeof(char),numBytes,this->modelFile);

	return buffer;
}

unsigned char Loader3DS::readByte()
{
	unsigned char buffer;
	fread(&buffer,sizeof(char),1,this->modelFile);

	return buffer;
}

unsigned short Loader3DS::read2Byte()
{
	unsigned short buffer;
	fread(&buffer, sizeof(unsigned short),1,this->modelFile);

	//this->bigEndian(&buffer);

	return buffer;
}

unsigned int Loader3DS::read4Byte()
{
	unsigned int buffer;
	fread(&buffer, sizeof(unsigned int),1,this->modelFile);

	//this->bigEndian(&buffer);

	return buffer;
}

float Loader3DS::readFloat()
{
	float buffer;
	fread(&buffer,sizeof(float),1,this->modelFile);

	return buffer;
}


void Loader3DS::bigEndian(unsigned int *num)
{
	*num = (((*num &0xff000000)>>24) |
			((*num &0x00ff0000)>>8) |
			((*num & 0x0000ff00)<<8) |
			((*num & 0x000000ff)<<24));
}

void Loader3DS::bigEndian(unsigned short *num)
{
	*num = (((*num & 0xff00)>>8) |
			((*num & 0x00ff)<<8));
}
