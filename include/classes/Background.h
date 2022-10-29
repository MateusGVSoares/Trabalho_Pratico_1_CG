#ifndef __BACKGROUND__
#define __BACKGROUND__

#include "Entidade.h"
#include "Shot.h"
#include <vector>
#include <GL/freeglut.h>

class Background : public Entidade
{ 

public:
    using Entidade::Entidade;
    Background(vec3f_t origin, int layer, float angle, float velocidade,std::vector<vec3f_t> hit_box,std::vector<vec3f_t> model);
    void setId(int a);
    void move() override;
    void draw() override;
    int destroy() override;
    void treatColide(int col_type) override;
};

#endif