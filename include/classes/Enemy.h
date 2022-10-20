#ifndef __ENEMY__
#define __ENEMY__

#include "Entidade.h"
#include "Shot.h"
#include <vector>
#include <GL/freeglut.h>

class Enemy : public Entidade
{
struct iaMovement
{

    void typeNormal(vec3f_t* origin, vec3f_t direction)
    {
        origin->x += direction.x;
        origin->y += direction.y;
        origin->z += direction.z;
    }
    void typeKamikaze(vec3f_t* origin, vec3f_t direction)
    {
        origin->x += direction.x;
        origin->y += direction.y;
        origin->z += direction.z;
    }
    void typeStalker(vec3f_t* origin, vec3f_t direction)
    {
        origin->x += direction.x;
        origin->y += direction.y;
        origin->z += direction.z;
    }
};

public:
    using Entidade::Entidade;
    Enemy(vec3f_t origin, int layer, float angle, float velocidade,std::vector<vec3f_t> hit_box,std::vector<vec3f_t> model);
    Shot enemyFire();
    void move() override;
    void draw() override;
    bool tadentro();
    void treatColide(int col_type) override;
};

#endif