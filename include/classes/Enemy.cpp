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
    
    this->id = 3;

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


void Enemy::move(){
    

};

void Enemy::draw(){


};

void Enemy::treatColide(int col_type){


};
