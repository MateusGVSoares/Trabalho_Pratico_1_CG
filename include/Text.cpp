#include "Text.h"

void print(const char *text,
           void *font,
           float x,
           float y,
           GLuint red,
           GLuint green,
           GLuint blue)
{

    // Seleciona a cor e a posicao
    glColor3ub(red, green, blue);
    glRasterPos2f(x, y);

    // Printa a string
    while (*text != '\0')
    {
        glutBitmapCharacter(font, *text);
        text++;
    }
}