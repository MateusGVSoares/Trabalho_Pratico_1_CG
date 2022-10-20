#ifndef __PARSER__
#define __PARSER__

#ifdef __DEBUG__
#define__DEBUG__
#include <stdio.h>
#endif

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>


#include "classes/Entidade.h"

typedef struct mission{

    int id_enemy;
    float x;
    float y;
    float time;

} mission_wave;

int parse_model(std::vector<vec3f_t> * target,const char *file_name);

int parse_mission(std::list<mission_wave> * target,const char *file_name);

int parser_texture(std::vector<GLuint> * target,std::vector<vec3f_t> *model,const char *file_name);

#endif