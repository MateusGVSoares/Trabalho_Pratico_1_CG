#ifndef __PLAYER__
#define __PLAYER__

#include "Entidade.h"
#include "Shot.h"
#include "Texturazer.h"
#include <vector>
#include <list>
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include "../parser.h"

class Player : public Entidade
{
private:
    int vidas;
    int level_gun1;
    int level_gun2;
    float timer_troca_gun;
    int invecible;
    float timer_invecible;
    std::vector<vec3f_t> shot_model;

public:
    int hp;
    int select_shot;
    Player(vec3f_t origin, float angle, float velocidade, std::vector<vec3f_t> hit_box, std::vector<vec3f_t> model);
    using Entidade::Entidade;
    Shot *playerFire();
    int updateOnKeyboard(keyboard_t keys);
    void treatUpgrade(int type);
    void setInvecible();
    int *getHp();
    // Virtual methods
    void move() override;
    void draw() override;
    int destroy() override;
};

#endif