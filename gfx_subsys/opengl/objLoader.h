/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #ifndef OBJ_LOADER_H
 #define OBJ_LOADER_H

 #include <windows.h>
 #include <stdio.h>
 #include <math.h>
 #include <stdlib.h>
 #include <vector>

 #include <GL\gl.h>
 #include <GL\glu.h>

 using namespace std;

 struct SVertex
 {
     float x,y,z;
 };

 struct SFace
 {
     int index[4];
 };

 class ObjLoader
 {
     public:
        ObjLoader();
        ObjLoader(char *filename);
        ~ObjLoader();

        void init(char *filename);
        bool load();
        void show();

    private:
        void processLine(char *line);
        void getVertices(char *line);
        void getFaces(char *line);
        void getNormals(char *line);
        FILE *m_modelFile;
        vector<SVertex> m_vertexes;
        vector<SVertex> m_normals;
        vector<SFace> m_faces;
 };

 #endif
