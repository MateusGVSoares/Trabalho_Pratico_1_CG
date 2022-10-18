#ifndef __TEXTURAZER__
#define __TEXTURAZER__

#include <GL/freeglut.h>
#include <bits/stdc++.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>



class Texturazer{

    protected:
        std::vector<GLuint> texture_vec;
        std::vector<std::pair<GLfloat,GLfloat>> texture_cord;
    
    public:
        Texturazer(std::vector<GLuint> tex_vec,std::vector<std::pair<GLfloat,GLfloat>> texture_cord);

};



#endif