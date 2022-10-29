
#include "Shot.h"

#define DRAW_BOX





Shot::Shot(vec3f_t origin,
    int layer,
    float angle,
    float velocidade,
    vec3f_t direction,
    std::vector<vec3f_t> model,
    std::vector<vec3f_t> hit_box,int id) : Entidade(origin, layer, angle, velocidade)
{
    this->model = model;
    this->box_model = hit_box;
    this->hit_box = hit_box;
    this->direction = direction;
    this->cont_stage_tex = 1;
    this->const_anim_texture = 1.0/5.0;
    this->timer_control_texture = 0.2;
    this->to_shot = std::unique_ptr<funcShot>(new funcShot);
    this->id =2;
    this->texture = std::make_shared<Texturazer>("assets/scripts/player.tscp");
}

void Shot::move()
{
    vec3f_t dir = {0};

    dir.x = this->direction.x * velocidade;
    dir.y = this->direction.y * velocidade;
    dir.z = this->direction.z * velocidade;

    this->to_shot->moveNormalShot(&this->origin, dir);
}

void Shot::draw()
{   //Sincronizar as render
    timer += (float) 16/1000.0;    
    if(timer >= 0.125)
    {
        if(timer_control_texture <= 0.8)
        {
            timer_control_texture += const_anim_texture;
        }
        else
        {
            timer_control_texture = 0.2;
        }
        timer = 0;
    }


    //printf("timer = %0.3f\n", timer);
    glPushMatrix();

    glTranslatef(this->origin.x, this->origin.y, this->origin.z);
    glRotatef(this->angle, 0, 0, 1);
    glColor3ub(150, 55, 150);

    // Carrega o objeto de textura para manipular no OpenGL
    glBindTexture(GL_TEXTURE_2D, this->texture->loaded_textures[cont_stage_tex]); 

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < this->model.size(); i++)
    {
        // Associa a textura ao objeto desenhado
        if(i<2){
            glTexCoord2f(this->texture->texture_cords[0][i].x , timer_control_texture - const_anim_texture);
            glVertex3f(this->model[i].x, this->model[i].y, this->model[i].z);
        }
        else{
            glTexCoord2f(this->texture->texture_cords[0][i].x , timer_control_texture);
            glVertex3f(this->model[i].x, this->model[i].y, this->model[i].z);
        }   
  
    }
    glEnd();

    glPopMatrix();

#ifdef DRAW_BOX
    glColor3ub(125, 125, 200);
    glBegin(GL_LINES);
    for (int r = 0, j = 1; r < this->hit_box.size(); r++, j = (r + 1) % (this->hit_box.size()))
    {
        // printf("%f %f \n", player->model[i].x, player->model[i].y);
        glVertex2f(this->hit_box[r].x, this->hit_box[r].y);
        glVertex2f(this->hit_box[j].x, this->hit_box[j].y);
    }
    glEnd();

#endif

}

int Shot::destroy(){

    return 1;
}

void Shot::treatColide(int col_type)
{
    return;
}