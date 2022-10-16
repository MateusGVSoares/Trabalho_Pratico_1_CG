#ifndef __CALLBACK__
#define __CALLBACK__

#include <GL/glut.h>

typedef struct Key
{
    int w;
    int a;
    int s;
    int d;
    int up;
    int down;
    int left;
    int right;
    int space;
} keyboard_t;

extern keyboard_t keyboard;
extern float razaoAspecto;

void keyboardFct(unsigned char key, int x, int y);
void reshapeFct(int width, int height);
void keyboardSpecial(int key, int x, int y);
#endif