#ifndef __ENEMY__
#define __ENEMY__

#include "Entidade.h"
#include "Shot.h"
#include "../parser.h"
#include <vector>
#include <GL/freeglut.h>




class Enemy : public Entidade
{ 

public:
    // Constructors
    using Entidade::Entidade;
    Enemy(vec3f_t origin,float angle, float velocidade,std::vector<vec3f_t> hit_box,std::vector<vec3f_t> model);
    
    Shot* enemyFire();

    // Virtual methods
    void move() override;
    void draw() override;
    int destroy() override;
};

#endif