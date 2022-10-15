#ifndef __OBJECT__
#define __OBJECT__

#include <vector>
#include <iostream>
#include <GL/gl.h>
#include "../algebra.h"
#include "../callback.h"

typedef struct vec3f
{
    float x;
    float y;
    float z;
} vec3f_t;

// Definição da classe Entidade
class Entidade
{
protected:
    float angle;
    int layer;
    vec3f_t origin;
    vec3f_t direction;
    std::vector<vec3f_t> model;     // Modelo gráfico
    std::vector<vec3f_t> box_model; // Modelo da hitbox
    std::vector<vec3f_t> hit_box;   // Hitbox em coordenada de mundo
    // TODO : Texture

public:
    // Entidade(vec3f_t origin, int layer, float angle);
    void updateModel();
    std::vector<vec3f_t> getModel();
    
    // Virtual functions
    virtual void move() = 0;
    virtual void draw() = 0;
    virtual void treatColide(int col_type) = 0; // Trata colisão depend
};

#endif