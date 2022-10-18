#ifndef __PARSER__
#define __PARSER__

#include <bits/stdc++.h>
#include "classes/Entidade.h"
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>

typedef struct mission{

    int id_enemy;
    float x;
    float y;
    float time;

} mission_wave;

int parse_model(std::vector<vec3f_t> * target,const char *file_name);

int parse_mission(std::list<mission_wave> * target,const char *file_name);

int parser_texture(std::vector<GLuint> * target,std::vector<std::pair<GLfloat,GLfloat>> *target2,const char *file_name);

#endif