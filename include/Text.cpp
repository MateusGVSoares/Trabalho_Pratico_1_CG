#include "Text.h"

void print(const char *text,
           void *font,
           float x,
           float y,
           GLuint red,
           GLuint green,
           GLuint blue,
           GLuint alpha)
{

    // Seleciona a cor e a posicao
    glColor4ub(red, green, blue,alpha);
    glRasterPos2f(x, y);

    // Printa a string
    while (*text != '\0')
    {
        glutBitmapCharacter(font, *text);
        text++;
    }
}