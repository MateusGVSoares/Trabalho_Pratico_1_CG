#include "callback.h"
#include <iostream>

float razaoAspecto = 0;
keyboard_t keyboard;

// Callback para pressionamento do teclado
void keyboardFct(unsigned char key, int x, int y)
{
#ifdef DEBUG
    printf("Keyboard Callback [%s] : Key [%c] | Mouse_Pos [%d][%d]\n", __func__, key, x, y);
#endif

    switch (key)
    {

    case 13:
        if (keyboard.enter)
            keyboard.enter = 0;
        else
            keyboard.enter = 1;
        break;

    case 'w':
    case 'W':
        if (keyboard.w)
            keyboard.w = 0;
        else
            keyboard.w = 1;
        break;
    case 'a':
    case 'A':
        if (keyboard.a == 1)
            keyboard.a = 0;
        else
            keyboard.a = 1;
        break;
    case 's':
    case 'S':
        if (keyboard.s)
            keyboard.s = 0;
        else
            keyboard.s = 1;
        break;
    case 'd':
    case 'D':
        if (keyboard.d)
            keyboard.d = 0;
        else
            keyboard.d = 1;
        break;
    case ' ':
        if (keyboard.space)
            keyboard.space = 0;
        else
            keyboard.space = 1;
        break;
    }
}

// Callback para pressionamento de Teclas Especiais
void keyboardSpecial(int key, int x, int y)
{
#ifdef DEBUG
    printf("Keyboard Callback [%s] : Key [%c] | Mouse_Pos [%d][%d]\n", __func__, key, x, y);
#endif

    switch (key)
    {
    case GLUT_KEY_UP:
        if (keyboard.up)
            keyboard.up = 0;
        else
            keyboard.up = 1;
        break;
    case GLUT_KEY_DOWN:
        if (keyboard.down)
            keyboard.down = 0;
        else
            keyboard.down = 1;
        break;
    case GLUT_KEY_LEFT:
        if (keyboard.left)
            keyboard.left = 0;
        else
            keyboard.left = 1;
        break;
    case GLUT_KEY_RIGHT:
        if (keyboard.right)
            keyboard.right = 0;
        else
            keyboard.right = 1;
        break;
    }
}

// Callback para redimensionamento
void reshapeFct(int width, int height)
{
#ifdef DEBUG
    printf("Reshape Callback [%s] : Width [%d] | Height [%d] \n", __func__, width, height);
#endif

    // Redimensiona o desenho do open_gl
    razaoAspecto = (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT);
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-100 * razaoAspecto, 100 * razaoAspecto, -100, 100, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}