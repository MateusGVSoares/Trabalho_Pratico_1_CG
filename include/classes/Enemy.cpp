#include "Enemy.h"

Enemy::Enemy(vec3f_t origin, float angle, float velocidade, std::vector<vec3f_t> hit_box, std::vector<vec3f_t> model) : Entidade(origin, angle, velocidade)
{
    // Inicializa as parada
    this->origin = origin;
    this->angle = angle;
    this->model = model;

    // Inicializa o modelo e a HitBox
    this->box_model = hit_box;
    this->hit_box = hit_box;
    this->alive = 1;
    // id fixa
    this->id = 4;
    // Inicializa a velocidade
    this->velocidade = velocidade;
    this->timer =0;
};

void Enemy::move(vec3f_t *point)
{
    this->origin.x += this->direction.x * velocidade;
    this->origin.y += this->direction.y * velocidade;
    this->origin.z += this->direction.z * velocidade;
}

Shot *Enemy::enemyFire()
{
    this->timer = 0.0;
    vec3f_t dir = {
        .x = 0,
        .y = -1,
        .z = 0};

    // Ajusta o ponto de origem do tiro
    vec3f_t shotOrigin = this->origin;

    shotOrigin.y -= 12;

    return new Shot(shotOrigin, 0, 1.0f, dir, this->id, "assets/scripts/enemyShot.tscp", this->cont_stage_tex);
}

void Enemy::draw()
{

    glPushMatrix();

    glTranslatef(this->origin.x, this->origin.y, this->origin.z);
    glRotatef(this->angle, 0, 0, 1);

    glColor3ub(255, 255, 255);

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

void Enemy::calc_direction(vec3f_t *point)
{
    // Calcula a direcao de movimento do inimgo
    // Para esse caso de inimigo,
    // faz com que se movimente do ponto inicial
    // ate o final
    this->direction.x = point->x - this->origin.x;
    this->direction.y = point->y - this->origin.y;
    this->direction.z = point->z - this->origin.z;
}
void Enemy::move()
{
    this->timer+=16.0/1000.0;
    this->origin.x += this->direction.x * velocidade;
    this->origin.y += this->direction.y * velocidade;
    this->origin.z += this->direction.z * velocidade;
}

int Enemy::destroy()
{

    return 1;
}