#ifndef __OBJECT__
#define __OBJECT__

typedef struct vec3f
{
    float x;
    float y;
    float z;
} vec3f_t;

#include <vector>
#include <memory>
#include <iostream>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <GL/gl.h>
#include "../algebra.h"
#include "../callback.h"
#include "Texturazer.h"

// Definição da classe Entidade
class Entidade
{

protected:
    bool border_x_col;
    bool border_y_col;
    float angle;
    bool on_screen;
    float velocidade;
    int id;
    float timer;
    float timer_control_texture;
    float const_anim_texture;
    int cont_stage_tex;
    vec3f_t origin;
    vec3f_t direction;
    std::vector<vec3f_t> model;          // Modelo gráfico
    std::vector<vec3f_t> box_model;      // Modelo da hitbox
    std::vector<vec3f_t> hit_box;        // Hitbox em coordenada de mundo
    std::shared_ptr<Texturazer> texture; // Objeto de textura

public:
    int alive;
    Entidade(vec3f_t origin, float angle, float velocidade);
    void updateModel();

    // Virtual functions
    virtual int destroy() = 0;
    virtual void move() = 0;
    virtual void draw() = 0;

    // getters
    std::vector<vec3f_t> *getHitbox();
    vec3f_t *getOrigin();
    bool getOnScreen();
    int getId();
    float getTimer();
    void setConst();

    // setters
    void setTexture(std::shared_ptr<Texturazer> target);
    void setId(int id);
};

#endif