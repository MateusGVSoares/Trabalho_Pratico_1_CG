#ifndef __OBJECT__
#define __OBJECT__

typedef struct vec2f
{
    float x;
    float y;
} vec2f_t;

typedef struct Object
{
    int type;
    int draw_list;
    float angle;
    vec2f_t origin;
    vec2f_t direction;
    vec2f_t model[4];
    vec2f_t box[4];

} Object_t;

void calc_direction(Object_t *target);

void rotate_vec(vec2f_t *target, float angle);

void translate_vec(vec2f_t *target, vec2f_t vector);

#endif