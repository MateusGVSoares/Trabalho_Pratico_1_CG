#include "Boss.h"

Boss::Boss(vec3f_t origin, float angle, float velocidade,std::vector<vec3f_t> hit_box,std::vector<vec3f_t> model) : Enemy( origin, angle,  velocidade, hit_box,model)
{

    this->alive=1;
    this->hp =110;
    this->timer = 0.0f;
    this->cont_stage_tex=0;
    // Inicializa a velocidade
    this->velocidade = 0;
    this->count_inv=0;
    this->invecible=1;
    this->move_x=0;
    this->stop =0;
    this->especial=0;
    this->count_especial=0.0;

};

Shot * Boss::enemyFire(){

    this->timer=0.0;
    vec3f_t dir = {
        .x = 0,
        .y = -1,
        .z = 0};

    std::vector<vec3f_t> aux,aux2;
    if(especial ==0)
        !parse_model(&aux, "assets/scripts/tiro1.mscp");    
    if(especial ==1)
        !parse_model(&aux, "assets/scripts/tiro2boss.mscp");

    aux2=aux;

    aux2[0].x*=2.7;aux2[0].y*=1.4;
    aux2[1].x*=2.7;aux2[1].y*=1.4;
    aux2[2].x*=2.7;aux2[2].y*=1.4;
    aux2[3].x*=2.7;aux2[3].y*=1.4;  

    // origem,angle,velocidade,direcao,model,hitbox,const char name,const_satege,crator id      
    //printf("tiro boss , especial = %d \n",this->especial);
    if(especial ==1)
        return new Shot(this->origin,0, 3.0f, dir,aux2,aux,"assets/scripts/player_shot.tscp",2,4);
    else
        return new Shot(this->origin,0, 3.0f, dir,aux,aux,"assets/scripts/player_shot.tscp",0,4);

}

void Boss::move(){

    if(especial==1)
        this->timer+=1.4/1000.0;
    else
        this->timer+=16.0/1000.0;

    this->count_inv+=16.0/1000.0;
    this->count_especial+=16.0/1000.0;
    if(count_inv >2.5 && invecible==1 ){
        invecible=0;
        count_inv=0;
    }
    if(count_inv >2.5 && invecible==0 ){
        invecible=1;
        count_inv=0;
    }

    if(this->origin.x <= 194 && this->move_x ==0 && stop ==0 )
        this->origin.x+=1.0;

    if(this->origin.x >= -194 && this->move_x ==1 && stop ==0 )
        this->origin.x-=1.0;

    if(this->origin.x > 194)
        this->move_x=1;    

    if(this->origin.x < -194)
        this->move_x=0;

    if(this->count_especial >4.0 && stop==0){
        this->count_especial=0.0;
        this->especial = 1;
        this->stop=1;
        this->timer=0.9;
    }

    if(this->count_especial >4.0 && stop==1){
        this->count_especial=0.0;
        this->especial = 0;
        this->stop=0;
        this->timer=0;
    }


    return ;

};

void Boss::draw(){


glPushMatrix();

    glTranslatef(this->origin.x, this->origin.y, this->origin.z);
    glRotatef(180, 0, 0, 1);
    glColor3ub(255, 255, 255);

    // Carrega o objeto de textura para manipular no OpenGL
    if(this->hp > 55)
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

    if(invecible==1){
        glColor3ub(255, 10, 10);
        glBindTexture(GL_TEXTURE_2D, this->texture->loaded_textures[2]);

        glBegin(GL_TRIANGLE_FAN);
            for (int i = 0; i < this->model.size(); i++)
            {
                // Associa a textura ao objeto desenhado
                glTexCoord2f(this->texture->texture_cords[0][i].x, this->texture->texture_cords[0][i].y);
                glVertex3f(this->model[i].x, this->model[i].y, this->model[i].z);
            }
        glEnd();

        }

    glPopMatrix();


};

int Boss::destroy(){

    if(invecible==0){
            hp--;    
    }

    if(hp==0)
        return 1;
    else    
        return 0;

}
