
#include <math.h>
#include "object.h"

void calc_direction(Object_t *target)
{
    target->direction.x = cos(target->angle * M_PI / 180.0f);
    target->direction.y = sin(target->angle * M_PI / 180.0f);
}

void rotate_vec(vec2f_t *target, float angle)
{
    float x = target->x, y = target->y;
    target->x = x * cos(angle * M_PI / 180.0f) - y * sin(angle * M_PI / 180.0f);
    target->y = x * sin(angle * M_PI / 180.0f) + y * cos(angle * M_PI / 180.0f);
}

void translate_vec(vec2f_t *target, vec2f_t vector)
{
    target->x += vector.x;
    target->y += vector.y;
}
