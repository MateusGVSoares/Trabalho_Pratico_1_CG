
#include "Shot.h"

#define DRAW_BOX

Shot::Shot(vec3f_t origin,
           float angle,
           float velocidade,
           vec3f_t direction,
           std::vector<vec3f_t> model,
           std::vector<vec3f_t> hit_box, const char *texture_name) : Entidade(origin, angle, velocidade)
{

    this->texture = std::make_shared<Texturazer>(texture_name);

    this->model = model;
    this->box_model = hit_box;
    this->hit_box = hit_box;
    this->direction = direction;
    this->cont_stage_tex = 1;
    this->const_anim_texture = 1.0 / 5.0;
    this->timer_control_texture = 0.2;

    // HARD-CODED
    // Especifica o
    this->id = 2;
}

Shot::Shot(vec3f_t origin, float angle, float velocidade, vec3f_t direction, int creator_id, const char *texture_name) : Entidade(origin, angle, velocidade)
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
    this->cont_stage_tex = 1;
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
}

void Shot::move()
{
    // Movimenta o tiro de acordo com a direção
    this->origin.x += direction.x * velocidade;
    this->origin.y += direction.y * velocidade;
    this->origin.z += direction.z * velocidade;
}

void Shot::draw()
{ // Sincronizar as render
    timer += (float)16 / 1000.0;
    if (timer >= 0.125)
    {
        if (timer_control_texture <= 0.8)
        {
            timer_control_texture += const_anim_texture;
        }
        else
        {
            timer_control_texture = 0.2;
        }
        timer = 0;
    }

    // printf("timer = %0.3f\n", timer);
    glPushMatrix();

    glTranslatef(this->origin.x, this->origin.y, this->origin.z);
    glRotatef(this->angle, 0, 0, 1);
    glColor3ub(150, 55, 150);

    // Carrega o objeto de textura para manipular no OpenGL
    glBindTexture(GL_TEXTURE_2D, this->texture->loaded_textures[0]);

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < this->model.size(); i++)
    {
        // Associa a textura ao objeto desenhado
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
    glEnd();

    glPopMatrix();

#ifdef DRAW_BOX
    glDisable(GL_BLEND);
    glColor3ub(255, 255, 255);
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

    return 1;
}
