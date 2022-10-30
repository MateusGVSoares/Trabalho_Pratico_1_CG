
#include "Shot.h"

#define DRAW_BOX

Shot::Shot(vec3f_t origin,
           float angle,
           float velocidade,
           vec3f_t direction,
           std::vector<vec3f_t> model,
           std::vector<vec3f_t> hit_box,
           const char *texture_name,int const_stage_tex) : Entidade(origin, angle, velocidade)
{

    this->texture = std::make_shared<Texturazer>(texture_name);

    this->model = model;
    this->box_model = hit_box;
    this->hit_box = hit_box;
    this->direction = direction;
    this->cont_stage_tex = const_stage_tex;
    this->const_anim_texture = 1.0 / 5.0;
    this->timer_control_texture = 0.2;

    // HARD-CODED
    // Especifica o
    this->id = 2;
}

Shot::Shot(vec3f_t origin, float angle, float velocidade, vec3f_t direction, int creator_id, const char *texture_name,int const_stage_tex) : Entidade(origin, angle, velocidade)
{

    // TODO:
    // Ajustar quais valores devem ser do ID do tiro para inimigo ou player
    if (creator_id == 1)
    {
        this->id = 2; // Tiro do player
    }
    else if (creator_id == 4)
    {
        this->id = 8; // Tiro do inimigo
    }

    // Coisas da textura
    this->texture = std::make_shared<Texturazer>(texture_name);
    this->cont_stage_tex = const_stage_tex;
    this->const_anim_texture = 1.0 / 5.0;
    this->timer_control_texture = 0.2;
    this->cont_stage_tex = const_stage_tex;

    // Coisas de posicao
    this->origin = origin;
    this->angle = angle;
    this->velocidade = velocidade;
    this->direction = direction;

    // Coisas de hitbox (HARD-CODED KKK)
    std::vector<vec3f_t> modelo;
    vec3f_t aux;
    float size = 12;

    aux.x = -size;
    aux.y = size;
    aux.z = 0;
    modelo.push_back(aux);

    aux.x = -size;
    aux.y = -size;

    modelo.push_back(aux);

    aux.x = size;
    aux.y = -size;

    modelo.push_back(aux);

    aux.x = size;
    aux.y = size;

    modelo.push_back(aux);

    this->model = this->hit_box = this->box_model = modelo;
}

void Shot::move()
{
    // Movimenta o tiro de acordo com a direção
    this->origin.x += direction.x * velocidade;
    this->origin.y += direction.y * velocidade;
    this->origin.z += direction.z * velocidade;
}

void Shot::draw(){
//Sincronizar as render

    timer += (float) 16/1000.0;    
    if(timer >= 0.035)
    {   // Lógica baseada em powerUps
        if(cont_stage_tex == 0)
        {
            const_anim_texture = (float)(1.0/5.0);
            if(timer_control_texture <= 0.8 )
            {
                timer_control_texture += const_anim_texture;
            }
            else
            {
                timer_control_texture = 0.2;
            }
        }
           
        if(cont_stage_tex == 1)
        {
            const_anim_texture =(float)(1.0/9.0);
            //printf("%0.3f const anim", const_anim_texture);
            if(timer_control_texture <= const_anim_texture)
            {
                timer_control_texture += const_anim_texture;
            }
            else
            {
                timer_control_texture = const_anim_texture;
            }
        }
        timer = 0;
    }



    //printf("timer = %0.3f\n", timer);
    glPushMatrix();

    glTranslatef(this->origin.x, this->origin.y, this->origin.z);

    if(cont_stage_tex != 1)
        glRotatef(this->angle, 0, 0, 1);
    else
        glRotatef(270, 0, 0, 1);
    glColor3ub(150, 55, 150);

    // Carrega o objeto de textura para manipular no OpenGL
    glBindTexture(GL_TEXTURE_2D, this->texture->loaded_textures[cont_stage_tex]); 

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < this->model.size(); i++)
    {   
        //Lógica baseada em qual Stage o PowerUp está

        // Purple Shoot
        if(cont_stage_tex == 0)
        {
            if(i<2){
                glTexCoord2f(this->texture->texture_cords[0][i].x , timer_control_texture - const_anim_texture);
                glVertex3f(this->model[i].x, this->model[i].y, this->model[i].z);
            }
            else{
                glTexCoord2f(this->texture->texture_cords[0][i].x , timer_control_texture);
                glVertex3f(this->model[i].x, this->model[i].y, this->model[i].z);
            } 
        }

        // Energy Ball
        if(cont_stage_tex == 1)
        {   
            // Inverto os eixos para inverter a disposição das imagens e multiplico o x por -1 pra inverter a disposição no eixo
            if(i == 0 || i == 3){
                glTexCoord2f(timer_control_texture - const_anim_texture , this->texture->texture_cords[0][i].y);
                glVertex3f(this->model[i].y, -1*this->model[i].x, this->model[i].z);
            }
            else{
                glTexCoord2f(timer_control_texture, this->texture->texture_cords[0][i].y);
                glVertex3f(this->model[i].y, -1*this->model[i].x, this->model[i].z);
            } 
        }

    }
              
  

    glEnd();

    glPopMatrix();

#ifdef DRAW_BOX
    glColor3ub(55, 55, 55);
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

int Shot::destroy()
{

    return 1;
}
