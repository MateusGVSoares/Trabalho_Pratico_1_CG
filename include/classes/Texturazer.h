#ifndef __TEXTURAZER__
#define __TEXTURAZER__

#include <GL/freeglut.h>
#include <vector>
#include <SOIL/SOIL.h>
#include "Entidade.h"

class Texturazer
{
public:
    std::vector<GLuint> loaded_textures;
    std::vector<std::vector<vec3f_t>> texture_cords;
    int parse_script(const char *file_name);
    Texturazer(const char *script_name);
};

#endif