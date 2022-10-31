#ifndef __BOSS__
#define __BOSS__

#include "Entidade.h"
#include "Enemy.h"
#include "../parser.h"


class Boss: public Enemy{

private:

    int change;
    int invecible;
    float count_inv;
    int move_x;
    int stop;
    int especial;
    float count_especial;

public:
    int hp;
    using Enemy::Enemy;
    Boss(vec3f_t origin,float angle, float velocidade,std::vector<vec3f_t> hit_box,std::vector<vec3f_t> model);
    Shot* enemyFire() override;
    int getHp();
    void move(vec3f_t * point) override;
    void draw() override;
    int destroy() override;
};


#endif