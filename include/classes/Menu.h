#ifndef __MENU__
#define __MENU__

#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include "../callback.h"

class Menu{
    private:
    GLuint idTextures[4];
    GLuint idCurrentTexture;
    GLuint idCreditos;
    GLuint idInstrucoes;
    int i;
    
    public:
    int flagpermission;
    Menu(); //construtor
    GLuint load_texture(const char* file);
    void draw();
    void key_pressed(keyboard_t keys);
    void comum_key_pressed(keyboard_t keys);
    void inicializa();
    void show_Creditos();
    void show_Instrucoes();
    ~Menu(){}; //destrutor
};
#endif