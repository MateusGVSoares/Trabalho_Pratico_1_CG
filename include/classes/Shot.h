#ifndef __SHOT__
#define __SHOT__

#include "Entidade.h"
#include <memory>


class Shot : public Entidade
{
private:
    int hp;
    
public:
    Shot(vec3f_t origin, float angle, float velocidade, vec3f_t direction,std::vector<vec3f_t> model,std::vector<vec3f_t> hit_box,const char *texture_name,int const_stage_tex,int creator_id);
    Shot(vec3f_t origin, float angle, float velocidade,vec3f_t direction, int creator_id, const char *texture_name,int const_stage_tex);
    Shot(vec3f_t origin, float angle, float velocidade,vec3f_t direction, int creator_id, const char *texture_name,int const_stage_tex,int level_gun);
    void draw() override;
    void move() override;
    int destroy() override;
};

#endif