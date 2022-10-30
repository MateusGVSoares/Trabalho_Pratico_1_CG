#ifndef __SHOT__
#define __SHOT__

#include "Entidade.h"
#include <memory>


class Shot : public Entidade
{
public:
    Shot(vec3f_t origin, float angle, float velocidade, vec3f_t direction,std::vector<vec3f_t> model,std::vector<vec3f_t> hit_box,const char *texture_name);
    Shot(vec3f_t origin, float angle, float velocidade,vec3f_t direction, int creator_id, const char *texture_name);
    void draw() override;
    void move() override;
    int destroy() override;
};

#endif