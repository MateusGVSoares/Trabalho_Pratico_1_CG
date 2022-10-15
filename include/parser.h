#ifndef __PARSER__
#define __PARSER__

#include <bits/stdc++.h>
#include "classes/Entidade.h"

typedef struct mission{

    int id_enemy;
    float x;
    float y;
    int time;

} mission_wave;

int parse_model(std::vector<vec3f_t> * target,const char *file_name);

int parse_mission(std::vector<mission_wave> * target,const char *file_name);

#endif