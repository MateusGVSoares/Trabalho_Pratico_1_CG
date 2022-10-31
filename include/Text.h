#ifndef __TEXT__
#define __TEXT__

#include <GL/glut.h>

void drawText(const char *text, void *font, float x, float y, GLuint red, GLuint green, GLuint blue)
{

    // Seleciona a cor e a posicao
    glColor3ub(red,green,blue);
    glRasterPos2f(x, y);
    
    // Printa a string
    while (*text != '\0')
    {
        glutBitmapCharacter(font, *text);
        text++;
    }
}

#endif