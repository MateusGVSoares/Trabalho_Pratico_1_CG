#include "Texturazer.h"

//construtor
Texturazer::Texturazer(std::vector<GLuint> tex_vec,std::vector<std::pair<GLfloat,GLfloat>> texture_cord){
    this->texture_vec = tex_vec;
    this->texture_cord= texture_cord;
};
