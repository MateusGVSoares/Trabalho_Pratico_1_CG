#include "Boss.h"

Boss::Boss(vec3f_t origin, float angle, float velocidade, std::vector<vec3f_t> hit_box, std::vector<vec3f_t> model) : Entidade(origin, angle, velocidade)
{
    // Inicializa as parada
    this->origin = origin;
    this->angle = angle;
    this->model = model;

    // Inicializa o modelo e a HitBox
    this->box_model = hit_box;
    this->hit_box = hit_box;
    this->alive = 1;
    this->hp = 6;
    this->timer = 0.0f;

    // id que é tipo inimigo
    this->id = 4;

    // Inicializa a velocidade
    this->velocidade = velocidade;
};

Shot *Boss::enemyFire()
{

    vec3f_t dir = {
        .x = 0,
        .y = 1,
        .z = 0};

    // Cria um tiro com as informacoes do inimigo

    return new Shot(this->origin,
                    0,
                    0.5f,
                    dir,
                    this->model,
                    this->box_model,
                    "");
}

void Boss::move()
{
    origin.y -= 0.5;
};

void Boss::draw()
{

    glPushMatrix();

    glTranslatef(this->origin.x, this->origin.y, this->origin.z);
    glRotatef(this->angle, 0, 0, 1);
    glColor3ub(140, 65, 43);

    // Carrega o objeto de textura para manipular no OpenGL
    glBindTexture(GL_TEXTURE_2D, this->texture->loaded_textures[0]);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < this->model.size(); i++)
    {
        // Associa a textura ao objeto desenhado
        glTexCoord2f(this->texture->texture_cords[0][i].x, this->texture->texture_cords[0][i].y);
        glVertex3f(this->model[i].x, this->model[i].y, this->model[i].z);
    }
    glEnd();

    glPopMatrix();
};

int Boss::destroy()
{

    if (this->hp > 0)
        hp--;
    else
        return 1;

    return 0;
}

