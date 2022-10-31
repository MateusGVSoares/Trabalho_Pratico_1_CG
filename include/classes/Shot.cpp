
#include "Shot.h"

#define DRAW_BOX

Shot::Shot(vec3f_t origin,
           float angle,
           float velocidade,
           vec3f_t direction,
           std::vector<vec3f_t> model,
           std::vector<vec3f_t> hit_box,
           const char *texture_name, int const_stage_tex, int creator_id) : Entidade(origin, angle, velocidade)
{

    this->texture = std::make_shared<Texturazer>(texture_name);
    if (creator_id == 1)
    {
        this->id = 2; // Tiro do player
    }
    else if (creator_id == 4)
    {
        this->id = 8; // Tiro do inimigo
    }

    // Coisas de posicao
    this->origin = origin;
    this->angle = angle;
    this->velocidade = velocidade;
    this->direction = direction;
    this->model = model;
    this->box_model = hit_box;
    this->hit_box = hit_box;

    // coisas da textura
    this->cont_stage_tex = const_stage_tex;
    this->const_anim_texture = 1.0 / 5.0;
    this->timer_control_texture = 0.2;

    // hp da bala
    if (this->cont_stage_tex == 0)
        this->hp = 1;
    if (this->cont_stage_tex == 1)
        this->hp = 2;
    if (this->cont_stage_tex == 2)
        this->hp = 99;
}
// construtor exclusivo do player
Shot::Shot(vec3f_t origin, float angle, float velocidade, vec3f_t direction, int creator_id, const char *texture_name, int const_stage_tex, int level_gun) : Entidade(origin, angle, velocidade)
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
    if (const_stage_tex != 2)
        this->timer_control_texture = 0.2;
    else
        this->timer_control_texture = 1.0 / 7.0;

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

    // hp da bala
    if (this->cont_stage_tex == 0)
        this->hp = 1;
    if (this->cont_stage_tex == 1)
        this->hp = 2 * level_gun;
}

Shot::Shot(vec3f_t origin, float angle, float velocidade, vec3f_t direction, int creator_id, const char *texture_name, int const_stage_tex) : Entidade(origin, angle, velocidade)
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
    // hp da bala
    if (this->cont_stage_tex == 0)
        this->hp = 1;
    if (this->cont_stage_tex == 1)
        this->hp = 2;
    if (this->cont_stage_tex == 2)
        this->hp = 1;
}

void Shot::move()
{
    if(!this->on_screen)
    {
        this->alive = 0;
        // printf(" PLEASE DELETE THIS SHOT KKKK \n");
        return;
    }
    // Movimenta o tiro de acordo com a direção
    this->origin.x += direction.x * velocidade;
    this->origin.y += direction.y * velocidade;
    this->origin.z += direction.z * velocidade;
}

void Shot::draw()
{
    // Sincronizar as render

    timer += (float)16 / 1000.0;
    // printf("const_stage = %d \n",this->cont_stage_tex);
    if (timer >= 0.035)
    { // Lógica baseada em powerUps
        if (cont_stage_tex == 0)
        {
            const_anim_texture = (float)(1.0 / 5.0);
            if (timer_control_texture <= 0.8)
            {
                timer_control_texture += const_anim_texture;
            }
            else
            {
                timer_control_texture = 0.2;
            }
        }

        if (cont_stage_tex == 1)
        {
            const_anim_texture = (float)(1.0 / 9.0);
            // printf("%0.3f const anim", const_anim_texture);
            if (timer_control_texture <= const_anim_texture)
            {
                timer_control_texture += const_anim_texture;
            }
            else
            {
                timer_control_texture = 0;
            }
        }

        if (cont_stage_tex == 2)
        {
            const_anim_texture = (float)(1.0 / 7.0);
            // printf("%0.3f const anim", const_anim_texture);
            if (timer_control_texture <= const_anim_texture)
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

    // printf("timer = %0.3f\n", timer);
    glPushMatrix();
    glTranslatef(this->origin.x, this->origin.y, this->origin.z);

    // if (cont_stage_tex == 1)
    //     glRotatef(270, 0, 0, 1);

    // else if (cont_stage_tex == 2)
    // {
    //     glRotatef(90, 0, 0, 1);
    // }

    if (this->id == 2 && cont_stage_tex == 0)
        glRotatef(90, 0, 0, 1);
    else if (cont_stage_tex == 1)
        glRotatef(270, 0, 0, 1);
    else if (cont_stage_tex == 2)
        glRotatef(90, 0, 0, 1);

    if (this->id == 8)
        glColor3ub(150, 55, 10);
    else
        glColor3ub(255, 255, 255);

    // Carrega o objeto de textura para manipular no OpenGL
    glBindTexture(GL_TEXTURE_2D, this->texture->loaded_textures[cont_stage_tex]);
    glBegin(GL_TRIANGLE_FAN);

    for (int i = 0; i < this->model.size(); i++)
    {

        // Purple Shoot
        if (cont_stage_tex == 0)
        {

            if (i < 2)
            {
                glTexCoord2f(this->texture->texture_cords[0][i].x, timer_control_texture - const_anim_texture);
                glVertex3f(this->model[i].x, this->model[i].y, this->model[i].z);
            }
            else
            {
                glTexCoord2f(this->texture->texture_cords[0][i].x, timer_control_texture);
                glVertex3f(this->model[i].x, this->model[i].y, this->model[i].z);
            }
        }

        // Energy Ball
        if (cont_stage_tex == 1)
        {

            // Inverto os eixos para inverter a disposição das imagens e multiplico o x por -1 pra inverter a disposição no eixo
            if (i == 0 || i == 3)
            {
                glTexCoord2f(timer_control_texture - const_anim_texture, this->texture->texture_cords[0][i].y);
                glVertex3f(this->model[i].y, -1 * this->model[i].x, this->model[i].z);
            }
            else
            {
                glTexCoord2f(timer_control_texture, this->texture->texture_cords[0][i].y);
                glVertex3f(this->model[i].y, -1 * this->model[i].x, this->model[i].z);
            }
        }

        // Rajada do Boss
        if (cont_stage_tex == 2)
        {
            // Inverto os eixos para inverter a disposição das imagens e multiplico o x por -1 pra inverter a disposição no eixo
            if (i == 1 || i == 2)
            {
                glTexCoord2f(timer_control_texture - const_anim_texture, this->texture->texture_cords[0][i].y);
                glVertex3f(this->model[i].y, -1 * this->model[i].x, this->model[i].z);
            }
            else
            {
                glTexCoord2f(timer_control_texture, this->texture->texture_cords[0][i].y);
                glVertex3f(this->model[i].y, -1 * this->model[i].x, this->model[i].z);
            }
        }
    }

    glEnd();

    glPopMatrix();

#ifdef DRAW_BOX
    glDisable(GL_BLEND);

    glColor3ub(55, 55, 55);
    glBegin(GL_LINES);
    for (int r = 0, j = 1; r < this->hit_box.size(); r++, j = (r + 1) % (this->hit_box.size()))
    {
        // printf("%f %f \n", player->model[i].x, player->model[i].y);
        glVertex2f(this->hit_box[r].x, this->hit_box[r].y);
        glVertex2f(this->hit_box[j].x, this->hit_box[j].y);
    }
    glEnd();
    glEnable(GL_BLEND);
#endif
}

int Shot::destroy()
{
    this->hp--;

    if (hp == 0)
        return 1;
    else
        return 0;
}
