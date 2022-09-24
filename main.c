#include <stdio.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Defs the animation time to 16ms or 60Hz
#define TICK_TIME 16
// #define DRAW_BOX
//#define DEBUG

typedef struct vec2f
{
    float x;
    float y;
} vec2f_t;

typedef struct Object
{
    int type;
    int draw_list;
    int onScreen;
    float angle;
    vec2f_t origin;
    vec2f_t direction;
    vec2f_t model[4];
    vec2f_t box[4];
    GLubyte color[3];
} Object_t;

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
} keyboard_t;

void updateModel(Object_t *);

// Velocidade de movimento do player
float speed = 0;

Object_t *player;

Object_t *elementList;

GLuint auxiliary_list;

keyboard_t keyboard;

float razaoAspecto = 0;

static int endGameFlag = 0;

void printText(float x, float y, void *font, char *string, GLubyte red, GLubyte green, GLubyte blue)
{
    glColor3ub(red, green, blue);
    glRasterPos2f(x, y);
    glutBitmapString(font, string);
}

// Callback para pressionamento do teclado
void keyboardFct(unsigned char key, int x, int y)
{
#ifdef DEBUG
    printf("Keyboard Callback [%s] : Key [%c] | Mouse_Pos [%d][%d]\n", __func__, key, x, y);
#endif
    switch (key)
    {
    case 'w':

        if (keyboard.w)
            keyboard.w = 0;
        else
            keyboard.w = 1;
        break;
    case 'a':
        if (keyboard.a == 1)
            keyboard.a = 0;
        else
            keyboard.a = 1;
        break;
    case 's':
        if (keyboard.s)
            keyboard.s = 0;
        else
            keyboard.s = 1;
        break;
    case 'd':
        if (keyboard.d)
            keyboard.d = 0;
        else
            keyboard.d = 1;
        break;
    }
}

// Callback para pressionamento de Teclas Especiais
void keyboardSpecial(int key, int x, int y)
{
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

    // Movimenta a parede do mundo na horizontal em X
    elementList[0].origin.x = 101 * razaoAspecto;
    elementList[2].origin.x = -101 * razaoAspecto;

    // aumenta os pontos do modelo das paredes verticais
    for (int i = 0; i < 4; i++)
    {
        elementList[1].model[i].y *= razaoAspecto;
        elementList[3].model[i].y *= razaoAspecto;
    }
}

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

void createListsPlayer()
{
    // Gera uma list para renderizar o quadrado
    player->draw_list = glGenLists(1);
    auxiliary_list = glGenLists(1);

    // Gera a lista para as rodas
    glNewList(auxiliary_list, GL_COMPILE);
    glColor3ub(0, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-2, 1);
    glVertex2f(-2, 0);
    glVertex2f(2, 0);
    glVertex2f(2, 1);
    glEnd();
    glEndList();

    // Gera a lista para o modelo principal do carro
    glNewList(player->draw_list, GL_COMPILE);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-10, 5);
    glVertex2f(-11, 4);
    // glVertex2f(-11.8, 3);
    // glVertex2f(-11.8, -3);
    glVertex2f(-11, -4);
    glVertex2f(-10, -5);
    glVertex2f(9, -5);
    glVertex2f(10, -4);
    glVertex2f(10.5, -3);
    glVertex2f(10.5, 3);
    glVertex2f(9, 5);
    glVertex2f(10, 4);
    glEnd();

    // Desenha o
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(190, 213, 248);
    glVertex2f(3, 4);
    glVertex2f(3, -4);
    glVertex2f(3.5, -3.5);
    glVertex2f(4, -3);
    glVertex2f(4.5, -2);
    glVertex2f(4.5, 2);
    glVertex2f(4, 3);
    glVertex2f(3.5, 3.5);
    glEnd();

    glPushMatrix();
    glTranslatef(-3, 0, 0);
    glRotated(180, 0, 0, 1);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(3, 4);
    glVertex2f(3, -4);
    glVertex2f(3.5, -3.5);
    glVertex2f(4, -3);
    glVertex2f(4.5, -2);
    glVertex2f(4.5, 2);
    glVertex2f(4, 3);
    glVertex2f(3.5, 3.5);
    glEnd();
    glPopMatrix();

    // Desenha o fundo do carro
    glColor3ub(0, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-6, 4);
    glVertex2f(-6, -4);
    glVertex2f(3, -4);
    glVertex2f(3, 4);
    glEnd();

    glColor3ub(0, 0, 0);
    // Desenha as rodas
    glPushMatrix();
    glTranslatef(6, 5, 0);
    glCallList(auxiliary_list);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, -6, 0);
    glCallList(auxiliary_list);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7, 5, 0);
    glCallList(auxiliary_list);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7, -6, 0);
    glCallList(auxiliary_list);
    glPopMatrix();

    glEndList();
}

// Gera modelos para os inimigos
int createListEnemyCaminhao()
{
    GLuint new_list = glGenLists(1);
    glNewList(new_list, GL_COMPILE);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(2, 5);
    glVertex2f(2, -5);
    glVertex2f(10, -5);
    glVertex2f(10, 5);
    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-21.0, 4.0);
    glVertex2f(-21.0, -4.0);
    glVertex2f(2, -4.0);
    glVertex2f(2, 4.0);
    glEnd();

    glColor3ub(100, 100, 100);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-21, 7);
    glVertex2f(-21, -7);
    glVertex2f(1, -7);
    glVertex2f(1, 7);
    glEnd();

    // Desenha as rodas
    glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef(6, 5, 0);
    glCallList(auxiliary_list);
    glPopMatrix();

    // Desenha as rodas
    glPushMatrix();
    glTranslatef(6, -6, 0);
    glCallList(auxiliary_list);
    glPopMatrix();

    // Desenha as rodas
    glPushMatrix();
    glTranslatef(-3, 7, 0);
    glCallList(auxiliary_list);
    glPopMatrix();

    // Desenha as rodas
    glPushMatrix();
    glTranslatef(-3, -8, 0);
    glCallList(auxiliary_list);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-13, 7, 0);
    glCallList(auxiliary_list);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-13, -8, 0);
    glCallList(auxiliary_list);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-18, 7, 0);
    glCallList(auxiliary_list);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-18, -8, 0);
    glCallList(auxiliary_list);
    glPopMatrix();

    glEndList();

    return new_list;
}

int createListEnemyCar()
{
    GLuint new_list = glGenLists(1);

    glNewList(new_list, GL_COMPILE);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-10, 5);
    glVertex2f(-11, 4);
    // glVertex2f(-11.8, 3);
    // glVertex2f(-11.8, -3);
    glVertex2f(-11, -4);
    glVertex2f(-10, -5);
    glVertex2f(9, -5);
    glVertex2f(10, -4);
    glVertex2f(10.5, -3);
    glVertex2f(10.5, 3);
    glVertex2f(9, 5);
    glVertex2f(10, 4);
    glEnd();

    // Desenha o
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(190, 213, 248);
    glVertex2f(3, 4);
    glVertex2f(3, -4);
    glVertex2f(3.5, -3.5);
    glVertex2f(4, -3);
    glVertex2f(4.5, -2);
    glVertex2f(4.5, 2);
    glVertex2f(4, 3);
    glVertex2f(3.5, 3.5);
    glEnd();

    glPushMatrix();
    glTranslatef(-3, 0, 0);
    glRotated(180, 0, 0, 1);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(3, 4);
    glVertex2f(3, -4);
    glVertex2f(3.5, -3.5);
    glVertex2f(4, -3);
    glVertex2f(4.5, -2);
    glVertex2f(4.5, 2);
    glVertex2f(4, 3);
    glVertex2f(3.5, 3.5);
    glEnd();
    glPopMatrix();

    // Desenha o fundo do carro
    glColor3ub(0, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-6, 4);
    glVertex2f(-6, -4);
    glVertex2f(3, -4);
    glVertex2f(3, 4);
    glEnd();

    glColor3ub(0, 0, 0);
    // Desenha as rodas
    glPushMatrix();
    glTranslatef(6, 5, 0);
    glCallList(auxiliary_list);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, -6, 0);
    glCallList(auxiliary_list);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7, 5, 0);
    glCallList(auxiliary_list);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7, -6, 0);
    glCallList(auxiliary_list);
    glPopMatrix();

    glEndList();
    return new_list;
}

int createListEnemyBike()
{
    GLuint new_list = glGenLists(1);

    glNewList(new_list, GL_COMPILE);

    glBegin(GL_TRIANGLE_FAN);

    glVertex2d(7, 0.5);
    glVertex2d(5, 0.5);
    glVertex2d(3, 1);
    glVertex2d(0, 1);
    glVertex2d(-2, 0.75);
    glVertex2d(-2, -0.75);
    glVertex2d(0, -1);
    glVertex2d(3, -1);
    glVertex2d(5, -0.5);
    glVertex2d(7, -0.5);
    glVertex2d(8, -1);
    glVertex2d(10, -1);

    glVertex2d(10, 1);
    glVertex2d(8, 1);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(8, 3);
    glVertex2f(8, -3);
    glVertex2f(9, -3);
    glVertex2f(9, 3);
    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(10, 0.5);
    glVertex2f(10, -0.5);
    glVertex2f(12, -0.5);
    glVertex2f(12, 0.5);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-1, 1.2);
    glVertex2f(-1, 0.9);
    glVertex2f(3, 0.9);
    glVertex2f(3, 1.2);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-1, -0.9);
    glVertex2f(-1, -1.2);
    glVertex2f(3, -1.2);
    glVertex2f(3, -0.9);
    glEnd();

    glEndList();
    return new_list;
}

void createPlayer()
{
    player = malloc(sizeof(Object_t));

    // Gera a cor para o player
    player->color[0] = 224;
    player->color[1] = 11;
    player->color[2] = 246;

    // Seta a posição inicial do player e o angulo, dps calcula a direção
    player->origin.x = 0;
    player->origin.y = 0;
    player->angle = 0;
    calc_direction(player);

    // Gera o modelo na origem para o player
    player->model[0].x = -10;
    player->model[0].y = 5;
    player->model[1].x = -10;
    player->model[1].y = -5;
    player->model[2].x = 10;
    player->model[2].y = -5;
    player->model[3].x = 10;
    player->model[3].y = 5;

    for (int i = 0; i < 4; i++)
    {

        // Rotaciona
        player->box[i] = player->model[i];

        // Translada
        translate_vec(&player->box[i], player->origin);
        rotate_vec(&player->box[i], player->angle);
    }
}

// Função de configuração

void updateModel(Object_t *target)
{
    // Rotaciona e translada o modelo original do jogador
    for (int i = 0; i < 4; i++)
    {
        // Pega o modelo original
        target->box[i] = target->model[i];

        // Rotaciona
        rotate_vec(&target->box[i], target->angle);
        // Translada
        translate_vec(&target->box[i], target->origin);
    }
}

void playerMovement()
{
    // vec2f_t vtec;

    // Verifica ser w e s estão sendo pressionados
    float x_movement = (keyboard.w || keyboard.up) - (keyboard.down || keyboard.s);
    // Verifica ser a e d estão sendo pressionados
    float y_movement = (keyboard.a || keyboard.left) - (keyboard.d || keyboard.right);

    // Verifica a rotação e calcula a direção do movimento
    player->angle += y_movement * 5;
    if (player->angle < 0)
        player->angle = 360;
    else if (player->angle > 360)
        player->angle = 0;
    calc_direction(player);

    // Verifica a translação e translada de acordo com a direção
    if (x_movement)
    {
        if (x_movement > 0 && speed < 2)
        {
            speed += 0.05;
        }
        else if (x_movement < 0 && speed > -2)
        {
            speed -= 0.05;
        }
        // Movimenta a nave de acordo com a direção apontada
        player->origin.x += player->direction.x * speed;
        player->origin.y += player->direction.y * speed;
    }
    else if (speed > 0.1 || speed < -0.1)
    {
        if (speed > 0)
            speed -= 0.04;
        else if (speed < 0)
            speed += 0.04;
        // Movimenta a nave de acordo com a direção apontada
        player->origin.x += player->direction.x * speed;
        player->origin.y += player->direction.y * speed;
    }
    else
    {
        speed = 0;
    }
    updateModel(player);
}

void drawObject(Object_t *target)
{
    if (target->draw_list > 0 && target->onScreen)
    {
        glPushMatrix();
        glColor3ubv(target->color);
        glTranslatef(target->origin.x, target->origin.y, 0);
        glRotatef(target->angle, 0, 0, 1);
        glCallList(target->draw_list);
        glPopMatrix();
    }
}

void genWalls()
{

    Object_t *wall;
    for (int i = 0; i < 4; i++)
    {
        wall = &elementList[i];

        // seta o tipo para mundo
        wall->type = 3;

        // Gera um modelo de colisão
        wall->model[0].x = -5;
        wall->model[0].y = 100;
        wall->model[1].x = -5;
        wall->model[1].y = -100;
        wall->model[2].x = 5;
        wall->model[2].y = -100;
        wall->model[3].x = 5;
        wall->model[3].y = 100;

        if (i == 0 || i == 2)
        {
            wall->angle = 0;
            wall->origin.x = i == 2 ? -105 : 105;
            wall->origin.y = 0;
        }
        else
        {
            wall->angle = 90;
            wall->origin.x = 0;
            wall->origin.y = i == 3 ? -105 : 105;
            // wall->origin.y = 0;
        }

        updateModel(&elementList[i]);
    }
}

void genEnemies()
{

    // Caminhao

    // Gera os inimigos e o modelo dos inimigos
    elementList[4].draw_list = createListEnemyCaminhao();
    elementList[5].draw_list = elementList[4].draw_list;

    // Gera o modelo na origem para o inimigo
    for (int i = 4; i < 6; i++)
    {
        elementList[i].model[0].x = -21;
        elementList[i].model[0].y = 7;
        elementList[i].model[1].x = -21;
        elementList[i].model[1].y = -7;
        elementList[i].model[2].x = 10;
        elementList[i].model[2].y = -7;
        elementList[i].model[3].x = 10;
        elementList[i].model[3].y = 7;

        elementList[i].color[0] = 102;
        elementList[i].color[1] = 51;
        elementList[i].color[2] = 0;
    }
    elementList[4].origin.x = 30;
    elementList[4].origin.y = 30;
    elementList[4].angle = 90;
    elementList[5].origin.x = -30;
    elementList[5].origin.y = -30;
    elementList[5].angle = 270;

    // Carro

    // Gera os inimigos e o modelo dos inimigos
    elementList[6].draw_list = createListEnemyCar();
    elementList[7].draw_list = elementList[6].draw_list;

    // Gera o modelo na origem para o inimigo
    for (int i = 6; i < 8; i++)
    {
        elementList[i].model[0].x = -10;
        elementList[i].model[0].y = 5;
        elementList[i].model[1].x = -10;
        elementList[i].model[1].y = -5;
        elementList[i].model[2].x = 10;
        elementList[i].model[2].y = -5;
        elementList[i].model[3].x = 10;
        elementList[i].model[3].y = 5;

        elementList[i].color[0] = 31;
        elementList[i].color[1] = 92;
        elementList[i].color[2] = 122;
    }
    elementList[6].origin.x = 50;
    elementList[6].origin.y = 50;
    elementList[6].angle = 90;
    elementList[7].origin.x = -50;
    elementList[7].origin.y = -50;
    elementList[7].angle = 270;

    elementList[8].draw_list = createListEnemyBike();
    elementList[9].draw_list = elementList[8].draw_list;

    elementList[8].origin.x = 90;
    elementList[8].origin.y = 90;

    elementList[9].origin.x = -80;
    elementList[9].origin.y = -80;

    elementList[8].angle = 180;
    elementList[9].angle = 90;

    for (int i = 8; i < 10; i++)
    {
        elementList[i].model[0].x = -2;
        elementList[i].model[0].y = 1;
        elementList[i].model[1].x = -2;
        elementList[i].model[1].y = -1;
        elementList[i].model[2].x = 10;
        elementList[i].model[2].y = -1;
        elementList[i].model[3].x = 10;
        elementList[i].model[3].y = 1;

        elementList[i].color[0] = 255;
        elementList[i].color[1] = 153;
        elementList[i].color[2] = 51;
    }

    for (int i = 4; i < 10; i++)
    {
        calc_direction(&elementList[i]);
        elementList[i].type = 2;
    }
}

void genWorld()
{
    // Gera o player e o modelo do player
    createPlayer();
    createListsPlayer();

    // Gera os elementos de mundo
    elementList = malloc(sizeof(Object_t) * 10);

    genWalls();
    genEnemies();
}

void Draw()
{

    glClear(GL_COLOR_BUFFER_BIT);
    if (!endGameFlag)
    {
        drawObject(player);

#ifdef DRAW_BOX
        glColor3ub(125, 125, 200);
        glBegin(GL_LINES);
        for (int r = 0, j = 1; r < 4; r++, j = (r + 1) % 4)
        {
            // printf("%f %f \n", player->model[i].x, player->model[i].y);
            glVertex2f(player->box[r].x, player->box[r].y);
            glVertex2f(player->box[j].x, player->box[j].y);
        }
        glEnd();

#endif

        for (int i = 0; i < 10; i++)
        {

            drawObject(&elementList[i]);

            //  Aqui é so pra printar os limites da caixa de colisão dos objetos
#ifdef DRAW_BOX
            glColor3ub(125, 125, 200);
            glBegin(GL_LINES);
            for (int r = 0, j = 1; r < 4; r++, j = (r + 1) % 4)
            {
                // printf("%f %f \n", player->model[i].x, player->model[i].y);
                glVertex2f((&elementList[i])->box[r].x, (&elementList[i])->box[r].y);
                glVertex2f((&elementList[i])->box[j].x, (&elementList[i])->box[j].y);
            }
            glEnd();

#endif
        }

        if (speed >= 2)
        {
            printText(player->box[3].x, player->box[3].y, GLUT_BITMAP_HELVETICA_18, "VTEC KICKS IN YO, VRUUUU", 224, 11, 146);
        }
    }
    else
    {
        printText(-20, 0, GLUT_BITMAP_TIMES_ROMAN_24, "BUSTED", 255, 152, 20);
    }
    glutSwapBuffers();
}

int colideStatic(Object_t *obj_1, Object_t *obj_2)
{
    vec2f_t diag_s = obj_1->origin,
            diag_e,
            edge_s,
            edge_e,
            move_vec;

    float limit = 0, det_1 = 0, det_2 = 0;

    int overlap = 0;

    for (int i = 0; i < 4; i++)
    {

        move_vec.x = 0;
        move_vec.y = 0;
        diag_e = obj_1->box[i];

        for (int j = 0; j < 4; j++)
        {
            edge_s = obj_2->box[j];
            edge_e = obj_2->box[(j + 1) % 4];

            limit = (edge_e.x - edge_s.x) * (diag_s.y - diag_e.y) - (diag_s.x - diag_e.x) * (edge_e.y - edge_s.y);
            det_1 = ((edge_s.y - edge_e.y) * (diag_s.x - edge_s.x) + (edge_e.x - edge_s.x) * (diag_s.y - edge_s.y)) / limit;
            det_2 = ((diag_s.y - diag_e.y) * (diag_s.x - edge_s.x) + (diag_e.x - diag_s.x) * (diag_s.y - edge_s.y)) / limit;

            if (det_1 >= 0.0f && det_1 < 1.0f && det_2 >= 0.0f && det_2 < 1.0f)
            {
                move_vec.x += (1.0f - det_1) * (diag_e.x - diag_s.x);
                move_vec.y += (1.0f - det_1) * (diag_e.y - diag_s.y);
                overlap = 1;
            }

            obj_1->origin.x += move_vec.x * -1;
            obj_1->origin.y += move_vec.y * -1;
        }
    }
    if (overlap)
        speed = 0;
    return overlap;
}

// static int col_counter = 0;
void verifyOnScreen(Object_t *target)
{
    target->onScreen = target->origin.x > -100 * razaoAspecto &&
                       target->origin.x < 100 * razaoAspecto && target->origin.y < 100 && target->origin.y > -100;
}

void movimentEnemy()
{
    elementList[4].origin.x += elementList[4].direction.x;
    elementList[4].origin.y += elementList[4].direction.y;
    elementList[6].origin.x += elementList[6].direction.x;
    elementList[6].origin.y += elementList[6].direction.y;

    elementList[5].origin.x += elementList[5].direction.x;
    elementList[5].origin.y += elementList[5].direction.y;
    elementList[7].origin.x += elementList[7].direction.x;
    elementList[7].origin.y += elementList[7].direction.y;

    for (int i = 4; i < 10; i++)
        verifyOnScreen(&elementList[i]);

    if (!elementList[4].onScreen)
    {
        elementList[4].origin.x = 30;
        elementList[4].origin.y = -100;
    }
    if (!elementList[5].onScreen)
    {
        elementList[5].origin.x = -30;
        elementList[5].origin.y = 100;
    }
    if (!elementList[6].onScreen)
    {
        elementList[6].origin.x = 60;
        elementList[6].origin.y = -100;
    }
    if (!elementList[7].onScreen)
    {
        elementList[7].origin.x = -60;
        elementList[7].origin.y = 100;
    }
}

void movimentEnemyBike()
{
    double angle;
    vec2f_t aux;
    for (int i = 8; i < 10; i++)
    {
        elementList[i].direction.x = aux.x = player->origin.x - elementList[i].origin.x;
        elementList[i].direction.y = aux.y = player->origin.y - elementList[i].origin.y;

        angle = (180.0f / M_PI) * atan(aux.y / aux.x);

        if ((aux.x <= 0 && aux.y < 0))
            angle += 180;
        else if ((aux.x <= 0 && aux.y > 0))
        {
            angle *= -1;
            angle = 180 - angle;
        }
        else if ((aux.x >= 0 && aux.y < 0))
        {
            angle += 360;
        }

        elementList[i].angle = angle;
        calc_direction(&elementList[i]);
        // printf("%d %f %f | %f\n", i, elementList[i].direction.x, elementList[i].direction.y, angle);
        elementList[i].origin.x += elementList[i].direction.x * 0.5;
        elementList[i].origin.y += elementList[i].direction.y * 0.5;
    }
}

void timerFct(int time)
{
    // Movimenta os objetos
    if (endGameFlag)
    {
        player->origin.x = 0;
        player->origin.y = 0;

        elementList[8].origin.x = 90;
        elementList[8].origin.y = 90;
        elementList[9].origin.x = -90;
        elementList[9].origin.y = -90;
        endGameFlag = 0;
    }
    playerMovement();
    movimentEnemy();
    movimentEnemyBike();

    // Atualiza os modelos dos objetos e inimigos
    for (int i = 0; i < 10; i++)
    {
        // printf("wall[%d] = x %f y %f \n", i, elementList[i].origin.x, elementList[i].origin.y);
        updateModel(&elementList[i]);
        verifyOnScreen(&elementList[i]);
    }

    // Verifica colisão com o player
    for (int i = 0; i < 10; i++)
    {
        if (colideStatic(player, &elementList[i]))
        {
            // Trata a colisão do player
            updateModel(player);
            updateModel(&elementList[i]);
            // col_counter++;
            // printf("%d  ", col_counter);
            if (elementList[i].type == 2)
            {
                // Trigga o reset do jogo
                // printf("COLIDIU COM INIMIGO ! \n");
                endGameFlag = 1;
            }
            // else
            // {
            //    printf("COLIDIU COM PAREDE ! \n");
            // }
        }
    }

    // Verifica se estão nos limites da tela
    verifyOnScreen(player);

    // Desenha os objetos
    glutPostRedisplay();

    // Restarts the timer
    glutTimerFunc(endGameFlag != 0 ? 1000 : time, timerFct, time);
}

void myInit()
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Questao 6");

    // Glut Callbacks
    glutDisplayFunc(Draw);
    glutReshapeFunc(reshapeFct);
    glutKeyboardFunc(keyboardFct);
    glutKeyboardUpFunc(keyboardFct);
    glutSpecialFunc(keyboardSpecial);
    glutSpecialUpFunc(keyboardSpecial);

    glutTimerFunc(TICK_TIME, timerFct, TICK_TIME);

    // Configura o OpenGL
#ifdef DRAW_BOX
    glLineWidth(5);
#endif
    glClearColor(1, 1, 1, 1);
    // Ignora repetições de teclas e verifica apenas o pressionamento e qnd soltar
    glutIgnoreKeyRepeat(1);
}

int main(int argc, char **argv)
{
    // Configura a glut e a janela
    glutInit(&argc, argv);
    myInit();

    genWorld();

    glutMainLoop();

    return 0;
}
