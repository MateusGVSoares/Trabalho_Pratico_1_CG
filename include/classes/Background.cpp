#include "Background.h"


Background::Background(vec3f_t origin, int layer, float angle, float velocidade, std::vector<vec3f_t> hit_box, std::vector<vec3f_t> model): Entidade(origin, layer, angle,velocidade)
{
    // Inicializa as parada
    this->origin = origin;
    this->layer = layer;
    this->angle = angle;
    this->model = model;

    // Inicializa o modelo e a HitBox
    this->box_model = hit_box;
    this->hit_box = hit_box;
    this->alive=1;
    this->cont_stage_tex = 1;
    this->const_anim_texture = 0.04428;
    this->timer_control_texture = 0.2;
    this->id = -1;
    // Inicializa a velocidade
    this->velocidade = velocidade;
};



void Background::setId(int a){
    this->id =a;
}

void Background::move(){
   

};

void Background::draw(){

    const_anim_texture+=0.001;

glPushMatrix();

    glTranslatef(this->origin.x, this->origin.y, this->origin.z);
    glRotatef(180, 0, 0, 1);

    glColor3ub(155,155,155);

    // Carrega o objeto de textura para manipular no OpenGL
    glBindTexture(GL_TEXTURE_2D, this->texture->loaded_textures[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < this->model.size(); i++)
    {
        // Associa a textura ao objeto desenhado
        if(i<2){
            glTexCoord2f(this->texture->texture_cords[0][i].x,const_anim_texture - 0.04428);
            //glTexCoord2f(this->texture->texture_cords[0][i].x, this->texture->texture_cords[0][i].y);
            glVertex3f(this->model[i].x, this->model[i].y, this->model[i].z);
        }
        else{
            glTexCoord2f(this->texture->texture_cords[0][i].x, const_anim_texture);
            //glTexCoord2f(this->texture->texture_cords[0][i].x, this->texture->texture_cords[0][i].y);
            glVertex3f(this->model[i].x, this->model[i].y, this->model[i].z);
        }
    }
    glEnd();

    glPopMatrix();

};


void Background::treatColide(int col_type){


};
int Background::destroy(){

    this->on_screen=1;
    return 1;
}