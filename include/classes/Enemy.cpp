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

    //joga para dentro o Objeto Texturizer que tem as texturas do inimgo
    

    // Inicializa a velocidade
    this->velocidade = velocidade;
};

void Enemy::move(){
    

};

void Enemy::draw(){


};

void Enemy::treatColide(int col_type){


};
