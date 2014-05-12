/***************************************************************************
 *   This file is part of the ReViSy project
 *   Copyright (C) 2007 by Neon
 ***************************************************************************/

 #ifndef PROGRAM_STATE_H
 #define PROGRAM_STATE_H

 #include <windows.h>

 class programState
 {
     public:
        virtual void setView(int width, int height)=0;
        virtual void init(HDC hdc)=0;
        virtual void run() = 0;
        virtual void shutdown() = 0;
     private:

 };

 #endif
