
// Libs
#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <GL/freeglut.h>
#include "include/algebra.h"
#include "include/callback.h"
#include "include/parser.h"

// Classes
#include "include/classes/Entidade.h"
#include "include/classes/Player.h"
#include "include/classes/Shot.h"
#include "include/classes/Texturazer.h"
#include "include/classes/World.h"
#include "include/classes/Enemy.h"
#include "include/classes/Colider.h"
#include "include/classes/Menu.h"


// VAMOS MEU CAMISA 09 >_< (Updated by Mateus on 16/08, 11:00:01)
std::vector<std::shared_ptr<Shot>> entities;
World *mundo;
Menu *menu;
//TODO 
//botar a IA do movimento dos inimigos
//terminar roteiro dos inimigos
// botar interface de vida e hp do player
//player 2 hp, 2vida
//tela de gamer over começa do começo
//so quando completar isso partir para os pontos extras

// variaveis globais
float timer_count = 0;
float world_time = 0;
int confirm = 0;

void drawUpdate()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // mostra o menu
    if(menu->flagpermission !=1 ){
          menu->draw();
        }
     //inicia o jogo
     if(menu->flagpermission == 1){
     //if (joga->getOnScreen())
     //{
        glEnable(GL_TEXTURE_2D);
        //joga->draw();
        mundo->draw_vec_entitys();
        glDisable(GL_TEXTURE_2D);

     }

    glutSwapBuffers();
}

void onTimeUpdate(int time)
{
    // tempo globais para auxiliar a classe World
    timer_count += (float)time / 1000;
    world_time += (float)time / 1000;
     if ((menu->flagpermission == 0 || menu->flagpermission == 2 || menu->flagpermission==3) && world_time >= 0.125)
     {
         menu->comum_key_pressed(keyboard);
         menu->key_pressed(keyboard);
         world_time = 0;
     }

     if (menu->flagpermission == 1)
     {
        //printf("time = %0.2f \n",world_time);
        mundo->start_mission(&world_time);
            mundo->update_entitys(&timer_count);
     }

     if (menu->flagpermission == 2)
     {
         // roda os creditos
         menu->show_Creditos();
     }
     if(menu->flagpermission ==3){
        menu->show_Instrucoes();
     }

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

    glLineWidth(8);
    glClearColor(1, 1, 1, 1);

    // Ignora repetições de teclas e verifica apenas o pressionamento e qnd soltar
    glutIgnoreKeyRepeat(1);
}

// YES, this cause a memory leak!
 void startMenu()
 {
     menu = new Menu();
     menu->inicializa();
 }

 void startMundo()
 {
     mundo = new World();
     mundo->initialize_script_mission();
 }

int main(int argc, char **argv)
{

    glutInit(&argc, argv);

    configGlut();

    glewInit();

    startMenu();

    startMundo();

    glutMainLoop();

    return 0;
}

/*
        Updated By : Camisa 09

        if you hear a voice within you say 'you cannot paint',
         then by all means paint, and that voice will be silenced.
        , Vincent Van Gogh

        -> https://www.youtube.com/watch?v=dQw4w9WgXcQ
*/
