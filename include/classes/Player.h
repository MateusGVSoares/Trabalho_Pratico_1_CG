#include "Entidade.h"
#include <bits/stdc++.h>

class Player : public Entidade
{

private:
    float velocidade;

public:
    Player(vec3f_t origin, int layer, float angle, float velocidade,std::vector<vec3f_t> hit_box,std::vector<vec3f_t> model);
    using Entidade::Entidade;
    void updateOnKeyboard(keyboard_t keys);
    void move() override;
    void draw() override;
    void treatColide(int col_type) override;
};