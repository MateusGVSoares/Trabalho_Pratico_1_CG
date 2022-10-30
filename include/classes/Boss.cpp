#include "Boss.h"

Boss::Boss(vec3f_t origin, float angle, float velocidade,std::vector<vec3f_t> hit_box,std::vector<vec3f_t> model) : Enemy( origin, angle,  velocidade, hit_box,model)
{

    this->alive=1;
    this->hp =6;
    this->timer = 0.0f;
    this->cont_stage_tex=0;
    // Inicializa a velocidade
    this->velocidade = 0;

};

Shot * Boss::enemyFire(){

    this->timer=0.0;

    vec3f_t dir = {
        .x = 0,
        .y = -1,
        .z = 0};

    std::vector<vec3f_t> aux;
    if(cont_stage_tex==0)
        !parse_model(&aux, "assets/scripts/tiro1.mscp");    
    if(cont_stage_tex==1)
        !parse_model(&aux, "assets/scripts/tiro2.mscp");    

    return new Shot(this->origin,0, 3.0f, dir,this->id,"assets/scripts/player_shot.tscp",this->cont_stage_tex);

}

void Boss::move(){
    this->timer+=16.0/1000.0;
    //printf("timer boss =%0.2f \n",this->timer);
    return ;

};

void Boss::draw(){


glPushMatrix();

    glTranslatef(this->origin.x, this->origin.y, this->origin.z);
    glRotatef(180, 0, 0, 1);
    glColor3ub(255, 255, 255);

    // Carrega o objeto de textura para manipular no OpenGL
    if(this->hp >3)
        glBindTexture(GL_TEXTURE_2D, this->texture->loaded_textures[0]);
    else
        glBindTexture(GL_TEXTURE_2D, this->texture->loaded_textures[1]);

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < this->model.size(); i++)
    {
        // Associa a textura ao objeto desenhado
        glTexCoord2f(this->texture->texture_cords[0][i].x, this->texture->texture_cords[0][i].y);
        glVertex3f(this->model[i].x, this->model[i].y, this->model[i].z);
    }
    glEnd();

    glPopMatrix();


};

int Boss::destroy(){

    if(this->hp>0)
        hp--;
    else
        return 1;

    return 0;

}
