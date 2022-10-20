#include "Menu.h"

Menu::Menu(){
flagpermission = 0;
};


void Menu::comum_key_pressed(keyboard_t keys){
	if(keys.enter==1 && (idCurrentTexture==idTextures[0])){
	flagpermission = 1;
	}
	if(keys.enter==1 && (idCurrentTexture==idTextures[1])){
	flagpermission = 2;
	}
	
    if(keys.enter==1 && (idCurrentTexture==idTextures[2])){
        exit(0);
    }
}

void Menu::key_pressed(keyboard_t keys)
{
    static int i  = 0;
    // Para cima
    if (keys.up || keys.w){
        if(i>0)
        i--;
        idCurrentTexture=idTextures[i];
    }
    // Para baixo
    if (keys.down|| keys.s){
        if(i<2)
        i++;
        idCurrentTexture=idTextures[i];
    }
}


GLuint Menu::load_texture(const char* file){
    GLuint idTextura = SOIL_load_OGL_texture(
                           file,
                           SOIL_LOAD_AUTO,
                           SOIL_CREATE_NEW_ID,
                           SOIL_FLAG_INVERT_Y
                       );

    if (idTextura == 0) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }

    return idTextura;
};

void Menu::draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (1, 1, 1);
    glPushMatrix();
        // Habilita o uso de texturas
        glEnable(GL_TEXTURE_2D);

        // Começa a usar a textura que criamos
        glBindTexture(GL_TEXTURE_2D, idCurrentTexture);
        glBegin(GL_TRIANGLE_FAN);
            // Associamos um canto da textura para cada vértice
            glTexCoord2f(0, 0);
            glVertex3f(-100, -100,  0);

            glTexCoord2f(1, 0);
            glVertex3f( 100, -100,  0);

            glTexCoord2f(1, 1);
            glVertex3f( 100,  100,  0);

            glTexCoord2f(0, 1);
            glVertex3f(-100,  100,  0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void Menu::inicializa()
{
    glClearColor(1, 1, 1, 1);

    // habilita mesclagem de cores, para termos suporte a texturas
    // com transparência
    glEnable(GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //guarda os ids das texturas
    idTextures[0] = load_texture("include/texturas/menuoption1.jpg");
    idTextures[1] = load_texture("include/texturas/menuoption2.jpg");
    idTextures[2] = load_texture("include/texturas/menuoption3.jpg");

    idCurrentTexture=idTextures[0];
}
