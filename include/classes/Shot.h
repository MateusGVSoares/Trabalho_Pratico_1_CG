#ifndef __SHOT__
#define __SHOT__

#include "Entidade.h"
#include <memory>

struct funcShot
{

    void moveNormalShot(vec3f_t* origin, vec3f_t direction)
    {
        origin->x += direction.x;
        origin->y += direction.y;
        origin->z += direction.z;
    }
};

class Shot : public Entidade
{
public:
    std::unique_ptr<funcShot> to_shot;
    Shot(vec3f_t origin, int layer, float angle, float velocidade, vec3f_t direction, std::vector<vec3f_t> model, std::vector<vec3f_t> hit_box,int id);
    void draw() override;
    void move() override;
    int destroy() override;
    void treatColide(int col_type) override;
};

#endif