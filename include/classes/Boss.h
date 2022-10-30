#ifndef __BOSS__
#define __BOSS__

#include "Entidade.h"
#include "Enemy.h"


class Boss: Entidade{

private:

    int hp;
    int change;
    float timer;


public:
    using Entidade::Entidade;
    Boss(vec3f_t origin, float angle, float velocidade,std::vector<vec3f_t> hit_box,std::vector<vec3f_t> model);

    Shot * enemyFire();
    void move() override;
    void draw() override;
    int destroy() override;
};


#endif