#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>







int main(int argc, char const *argv[])
{
    GLuint idTextura = SOIL_load_OGL_texture("pessoa.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

        if(idTextura == 0){
            printf("Erro do SOIL:  %s\n", SOIL_last_result());
        }

    printf("id = %d",idTextura);

    return 0;
}
