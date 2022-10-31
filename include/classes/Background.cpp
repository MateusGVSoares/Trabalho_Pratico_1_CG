#include "Background.h"

Background::Background(vec3f_t origin,
                       float angle,
                       float velocidade,
                       std::vector<vec3f_t> hit_box,
                       std::vector<vec3f_t> model) : Entidade(origin, angle, velocidade)
{
    // Inicializa as parada
    this->origin = origin;

    this->angle = angle;
    this->model = model;

    // Inicializa o modelo e a HitBox
    this->box_model = hit_box;
    this->hit_box = hit_box;
    this->alive = 1;
    this->cont_stage_tex = 1;
    this->const_anim_texture = 0.04428;
    this->timer_control_texture = 0.2;
    this->cont_stage_tex=0;
    this->velocidade=0.7;
    this->id = -1;
};

void Background::start_boss(){

    velocidade=2.1;

}

void Background::move()
{
    return;
};

void Background::draw()
{

    this->model[0].x = -max_x;
    this->model[1].x = max_x;
    this->model[2].x = max_x;
    this->model[3].x = -max_x;
    
    const_anim_texture += 0.001*this->velocidade;

    glPushMatrix();

    glTranslatef(this->origin.x, this->origin.y, this->origin.z);
    glRotatef(180, 0, 0, 1);

    glColor3ub(155, 155, 155);

    // Carrega o objeto de textura para manipular no OpenGL
    glBindTexture(GL_TEXTURE_2D, this->texture->loaded_textures[this->cont_stage_tex]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < this->model.size(); i++)
    {
        // Associa a textura ao objeto desenhado
        if (i < 2)
        {
            glTexCoord2f(this->texture->texture_cords[0][i].x, const_anim_texture - 0.04428);
            // glTexCoord2f(this->texture->texture_cords[0][i].x, this->texture->texture_cords[0][i].y);
            glVertex3f(this->model[i].x, this->model[i].y, this->model[i].z);
        }
        else
        {
            glTexCoord2f(this->texture->texture_cords[0][i].x, const_anim_texture);
            // glTexCoord2f(this->texture->texture_cords[0][i].x, this->texture->texture_cords[0][i].y);
            glVertex3f(this->model[i].x, this->model[i].y, this->model[i].z);
        }
    }
    glEnd();

    glPopMatrix();
};

void Background::trocar_back(){
    this->cont_stage_tex++;
}

int Background::destroy()
{

    this->on_screen = 1;
    return 1;
}
