#ifndef __ENEMY__
#define __ENEMY__

#include "Entidade.h"
#include "Shot.h"
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>

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

private:
    float velocidade;

public:
    Enemy(vec3f_t origin, int layer, float angle, float velocidade,std::vector<vec3f_t> hit_box,std::vector<vec3f_t> model);
    using Entidade::Entidade;
    Shot enemyFire();
    void move() override;
    void draw() override;
    void treatColide(int col_type) override;
};

#endif