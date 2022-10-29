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
        int hp ;
        int vidas ;
        
    public:
        Player(vec3f_t origin, int layer, float angle, float velocidade, std::vector<vec3f_t> hit_box, std::vector<vec3f_t> model,std::vector<GLuint> tex_vec,int id);
        using Entidade::Entidade;
        Shot* playerFire();
        int updateOnKeyboard(keyboard_t keys);
        
        // Virtual methods
        void move() override;
        void draw() override;
        int destroy() override;
        void treatColide(int col_type) override;
};

#endif