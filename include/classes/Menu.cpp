#include "Menu.h"

Menu::Menu(){
flagpermission = 0;
i=0;
};


void Menu::comum_key_pressed(keyboard_t keys){
	if(keys.enter==1 && (idCurrentTexture==idTextures[0])){
	    flagpermission = 1;
	}
	if(keys.enter==1 && (idCurrentTexture==idTextures[1])){
	    flagpermission = 2;
	}
    if(keys.enter==1 && (idCurrentTexture==idTextures[3])){
        flagpermission=  3;
    }
    if(keys.enter==1 && (idCurrentTexture==idTextures[2])){
        exit(0);
    }
    if(keys.enter==1 && (idCurrentTexture==idCreditos)){
        flagpermission = 0;
        i=0;
        idCurrentTexture=idTextures[0];
    }
    if(keys.enter==1 && (idCurrentTexture==idInstrucoes)){
        flagpermission = 0;
        i=0;
        idCurrentTexture=idTextures[0];
    }
}

void Menu::show_Creditos(){
idCurrentTexture=idCreditos;
}

void Menu::show_Instrucoes(){
idCurrentTexture=idInstrucoes;
}

void Menu::key_pressed(keyboard_t keys)
{
    // Para cima
    if (keys.up || keys.w){
        if(i>0)
        i--;
        idCurrentTexture=idTextures[i];
    }
    // Para baixo
    if (keys.down|| keys.s){
        if(i<4)
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
            glVertex3f(-256*razaoAspecto, -224,  0);

            glTexCoord2f(1, 0);
            glVertex3f( 256*razaoAspecto, -224,  0);

            glTexCoord2f(1, 1);
            glVertex3f( 256*razaoAspecto,  224,  0);

            glTexCoord2f(0, 1);
            glVertex3f(-256*razaoAspecto,  224,  0);
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
    idTextures[0] = load_texture("assets/texture/menuoption1.jpg");
    idTextures[1] = load_texture("assets/texture/menuoption2.jpg");
    idTextures[2] = load_texture("assets/texture/menuoption3.jpg");
    idTextures[3] = load_texture("assets/texture/menuoption4.jpg");
    idCreditos = load_texture("assets/texture/creditos.jpg");
    idInstrucoes = load_texture("assets/texture/instrucoes.jpg");

    idCurrentTexture=idTextures[0];
}

