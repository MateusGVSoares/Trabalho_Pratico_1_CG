#include "callback.h"

int key_status[4];
float razaoAspecto = 0;

// Callback para pressionamento do teclado
void keyboardFct(unsigned char key, int x, int y)
{
#ifdef DEBUG
    printf("Keyboard Callback [%s] : Key [%c] | Mouse_Pos [%d][%d]\n", __func__, key, x, y);
#endif
    switch (key)
    {
    case 'w':

        if (key_status[0])
            key_status[0] = 0;
        else
            key_status[0] = 1;
        break;
    case 'a':
        if (key_status[1])
            key_status[1] = 0;
        else
            key_status[1] = 1;
        break;
    case 's':
        if (key_status[2])
            key_status[2] = 0;
        else
            key_status[2] = 1;
        break;
    case 'd':
        if (key_status[3])
            key_status[3] = 0;
        else
            key_status[3] = 1;
        break;
    case 0x27:
        exit(0);
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