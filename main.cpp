#include <bits/stdc++.h>
#include <GL/freeglut.h>
#include "include/classes/Entidade.h"
#include "include/classes/Player.h"
#include "include/algebra.h"
#include "include/callback.h"
#include "include/classes/Entidade.h"
#include "include/parser.h"


// vamos meu camisa 9
Player *joga;

void drawUpdate()
{
    glClear(GL_COLOR_BUFFER_BIT);

    joga->draw();

    glutSwapBuffers();
}

void onTimeUpdate(int time)
{
    // Updates the movements
    joga->updateOnKeyboard(keyboard);
    joga->move();
    
    // Updates the collisions boxes
    joga->updateModel();
    
    // Treats the collisions

    // Draws everything <3
    glutPostRedisplay();
    // Restarts the timerFunc
    glutTimerFunc(time, onTimeUpdate, time);
}

void configGlut()
{
    // Configura a janela da GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Game");

    // Configura os callbacks da GLUT
    glutDisplayFunc(drawUpdate);
    glutReshapeFunc(reshapeFct);
    glutKeyboardFunc(keyboardFct);
    glutKeyboardUpFunc(keyboardFct);
    glutSpecialFunc(keyboardSpecial);
    glutSpecialUpFunc(keyboardSpecial);

    glutTimerFunc(16, onTimeUpdate, 16);

    glClearColor(1, 1, 1, 1);

    // Ignora repetições de teclas e verifica apenas o pressionamento e qnd soltar
    glutIgnoreKeyRepeat(1);
}

void initPlayer()
{
    std::vector<vec3f_t> vector;

    if (!parse_model(&vector, "model"))
    {
        printf("DEU BOM NO FILE \n");
    }

    vec3f_t origin = {
        .x = 0,
        .y = 0,
        .z = 0};

    joga = new Player(origin, 0, 0, 1.0f, vector, vector);
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);

    initPlayer();

    configGlut();

    glutMainLoop();

    return 0;
}
