#ifndef __BOSS__
#define __BOSS__

#include "Entidade.h"
#include "Enemy.h"
#include "../parser.h"


class Boss: public Enemy{

private:

    int hp;
    int change;

public:
    Boss(vec3f_t origin,float angle, float velocidade,std::vector<vec3f_t> hit_box,std::vector<vec3f_t> model);
    using Enemy::Enemy;
    Shot* enemyFire();
    void move() override;
    void draw() override;
    int destroy() override;
};


#endif