#include "Enemy.h"


Enemy::Enemy(vec3f_t origin, int layer, float angle, float velocidade, std::vector<vec3f_t> hit_box, std::vector<vec3f_t> model): Entidade(origin, layer, angle,velocidade)
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
    // id vindo do script;
    this->id = 4;
    // Inicializa a velocidade
    this->velocidade = velocidade;
};

Shot Enemy::enemyFire(){

    vec3f_t dir = {
        .x = 0,
        .y = 1,
        .z = 0};
    //Passa os dados para serem criado o tiro, tiro com id=4 tiro do inimigo para ser tratado no colider
    Shot ret_shot(this->origin, 1, 0, 0.5f, dir, this->model, this->box_model,4);

    return ret_shot;

}

void Enemy::setId(int a){
    this->id =a;
}

void Enemy::move(){
    
    origin.y -=velocidade;

};

void Enemy::draw(){

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


void Enemy::treatColide(int col_type){


};
int Enemy::destroy(){

    return 1;
}