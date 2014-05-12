/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #include "objLoader.h"

 ObjLoader::ObjLoader()
 {

 }

 ObjLoader::ObjLoader(char *filename)
 {
     this->m_modelFile = fopen(filename,"r");
 }

 ObjLoader::~ObjLoader()
 {
 }

 void ObjLoader::init(char *filename)
 {
     this->m_modelFile = fopen(filename,"r");
 }

 bool ObjLoader::load()
 {
     if(!this->m_modelFile)
        return false;

     char buffer[512];

     while(!feof(this->m_modelFile))
     {
         fgets(buffer,512,this->m_modelFile);
         //printf("line: %s\n",buffer);
         this->processLine(buffer);
     }

     fclose(this->m_modelFile);

     /*for(int i=0; i<this->m_faces.size()-1; i++)
     {
         //printf("face %d, index0 = %d\n",i,this->m_faces[i].index[0]);
         //printf("face %d, index1 = %d\n",i,this->m_faces[i].index[1]);
         //printf("face %d, index2 = %d\n",i,this->m_faces[i].index[2]);
         //printf("face %d, index3 = %d\n",i,this->m_faces[i].index[3]);
     }*/

     return true;
 }

 void ObjLoader::processLine(char *line)
 {
        switch(line[0])
        {
            case '#':
            {
                //printf("comments\n");
            }break;
            case 'o':
            {
                //printf("object name\n");
            }break;
            case 'v':
            {
                if(line[1] == ' ')
                {
                    //printf("vertex data\n");
                    this->getVertices(line);
                }
                else if(line[1] == 'n')
                {
                    //printf("normal data\n");
                    this->getNormals(line);
                }
                else if(line[1] == 't')
                {
                    //printf("texture vertices\n");
                }
            }break;
            case 'f':
            {
                //printf("face\n");
                this->getFaces(line);
            }break;
            default:
            {
            }break;
        }
 }

 void ObjLoader::getVertices(char* line)
 {
     char *token;
     float tempVertex[3];
     SVertex tmpVertex;
     char *endptr;

     token = strtok(line, " ");
     int i=0;
     while(token != NULL)
     {
         token = strtok(NULL," ");
         if(token == NULL)
            break;
         //printf("token: %s\n",token);
         if(token != NULL && i<=3)
         {
            tempVertex[i] = strtof(token,&endptr);
            //printf("number: %f\n",tempVertex[i]);
         }
        i++;
     }

     tmpVertex.x = tempVertex[0];
     tmpVertex.y = tempVertex[1];
     tmpVertex.z = tempVertex[2];

     this->m_vertexes.push_back(tmpVertex);
     //printf("vertex x = %f, y = %f, z = %f\n",tmpVertex.x,tmpVertex.y,tmpVertex.z);
 }

 void ObjLoader::getNormals(char *line)
 {
     char *token;
     float tempNormals[3];
     SVertex tmpNormals;
     char *endptr;

     token = strtok(line, " ");
     int i=0;
     while(token != NULL)
     {
         token = strtok(NULL, " ");
         if(token != 0 && i<=3)
         {
                tempNormals[i] = strtof(token, &endptr);
                //printf("normal: %f\n",tempNormals[i]);
         }
         i++;
     }

     tmpNormals.x = tempNormals[0];
     tmpNormals.y = tempNormals[1];
     tmpNormals.z = tempNormals[2];

     this->m_normals.push_back(tmpNormals);
 }

 void ObjLoader::getFaces(char* line)
 {
     SFace tmpFace;
     vector<char*> tempTokens;
     int intStr = 0;
     char *token;
     char *tokenSlash;

     int index;
     index = 0;
     token = strtok(line, " ");
     while(token != NULL)
     {
         token = strtok(NULL, " ");

         if(token != NULL)
         {
            //printf("token: %s int: %d\n",token,intStr);
            /*for(int i=strlen(token)-1, j=0; i>=0; --i, ++j)
            {
                if((token[i]>=48) && (token[i]<=57))
                    intStr+=(token[i]-48)*(pow(10.0,j));
                else
                    j--;
            }*/

            tmpFace.index[index] = (int)strtol(token,NULL,10);//intStr;

            //printf("token int: %d\n",intStr);

            index++;
            intStr = 0;
         }
     }

     this->m_faces.push_back(tmpFace);
 }

 void ObjLoader::show()
 {
        glBegin(GL_TRIANGLES);
        for(int i=0; i<this->m_faces.size()-1; i++)
        {
            //glTexCoord2f(this->[this->faces[i].vertex[0]].u,
            //            this->mapCoord[this->faces[i].vertex[0]].v);
            glNormal3f(this->m_normals[i].x, this->m_normals[i].y,this->m_normals[i].z);
            glVertex3f(this->m_vertexes[this->m_faces[i].index[0]-1].x,
                        this->m_vertexes[this->m_faces[i].index[0]-1].y,
                        this->m_vertexes[this->m_faces[i].index[0]-1].z);
            //printf("Vertex %d = %f\n",this->m_faces[i].index[0]-1,this->m_vertexes[this->m_faces[i].index[0]-1].x);
            //printf("Vertex %d = %f\n",this->m_faces[i].index[0]-1,this->m_vertexes[this->m_faces[i].index[0]-1].y);
            //printf("Vertex %d = %f\n\n",this->m_faces[i].index[0]-1,this->m_vertexes[this->m_faces[i].index[0-1]].z);

            //glTexCoord2f(this->mapCoord[this->faces[i].vertex[1]].u,
            //            this->mapCoord[this->faces[i].vertex[1]].v);
            glNormal3f(this->m_normals[i].x, this->m_normals[i].y,this->m_normals[i].z);
            glVertex3f(this->m_vertexes[this->m_faces[i].index[1]-1].x,
                        this->m_vertexes[this->m_faces[i].index[1]-1].y,
                        this->m_vertexes[this->m_faces[i].index[1]-1].z);
            //printf("Vertex %d = %f\n",this->m_faces[i].index[1]-1,this->m_vertexes[this->m_faces[i].index[1]-1].x);
            //printf("Vertex %d = %f\n",this->m_faces[i].index[1]-1,this->m_vertexes[this->m_faces[i].index[1]-1].y);
            //printf("Vertex %d = %f\n\n",this->m_faces[i].index[1]-1,this->m_vertexes[this->m_faces[i].index[1]-1].z);



            //glTexCoord2f(this->mapCoord[this->faces[i].vertex[2]].u,
            //            this->mapCoord[this->faces[i].vertex[2]].v);
            glNormal3f(this->m_normals[i].x, this->m_normals[i].y,this->m_normals[i].z);
            glVertex3f(this->m_vertexes[this->m_faces[i].index[2]-1].x,
                        this->m_vertexes[this->m_faces[i].index[2]-1].y,
                        this->m_vertexes[this->m_faces[i].index[2]-1].z);
            //printf("Vertex %d = %f\n",this->m_faces[i].index[2]-1,this->m_vertexes[this->m_faces[i].index[2]-1].x);
            //printf("Vertex %d = %f\n",this->m_faces[i].index[2]-1,this->m_vertexes[this->m_faces[i].index[2]-1].y);
            //printf("Vertex %d = %f\n\n",this->m_faces[i].index[2]-1,this->m_vertexes[this->m_faces[i].index[2]-1].z);



            /*glVertex3f(this->m_vertexes[this->m_faces[i].index[3]-1].x,
                        this->m_vertexes[this->m_faces[i].index[3]-1].y,
                        this->m_vertexes[this->m_faces[i].index[3]-1].z);
            printf("Vertex %d = %f\n",this->m_faces[i].index[3],this->m_vertexes[this->m_faces[i].index[3]].x);
            */


        }
        glEnd();

        glNormal3f(0.0f,0.0f,0.0f);

        //Sleep(200000);
 }

