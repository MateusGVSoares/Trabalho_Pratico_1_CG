#ifndef __MENU__
#define __MENU__

#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include "../callback.h"

class Menu{
    private:
    GLuint idTextures[3];
    GLuint idCurrentTexture;
    
    public:
    int flagpermission;
    Menu(); //construtor
    GLuint load_texture(const char* file);
    void draw();
    void key_pressed(keyboard_t keys);
    void comum_key_pressed(keyboard_t keys);
    void inicializa();
    ~Menu(){}; //destrutor
};
#endif