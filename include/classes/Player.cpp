#include "Player.h"

// #define DRAW_BOX

Player::Player(vec3f_t origin,
               float angle,
               float velocidade,
               std::vector<vec3f_t> hit_box,
               std::vector<vec3f_t> model) : Entidade(origin, angle, velocidade){
    // Deixa o player alocar os modelos
    this->model = model;
    this->box_model = hit_box;
    this->hit_box = hit_box;

    this->texture = std::make_shared<Texturazer>("assets/scripts/player.tscp");
    this->hp = 2;
    this->vidas = 2;
    this->cont_stage_tex=0;
    this->velocidade =3;
    // ID para colisao(não é o id de carregamento das coisas do script)
    this->id = 1;
};

int Player::updateOnKeyboard(keyboard_t keys)
{
    int x_mov = (keys.d || keys.right) - (keys.left || keys.a);
    int y_mov = (keys.up || keys.w) - (keys.down || keys.s);

    float aux = 0.0;

    if (x_mov != 0 && y_mov != 0)
    {
        if (x_mov > 0)
        {
            if (y_mov > 0)
            {
                aux = 45;
            }
            else
                aux = 315;
        }
        else if (x_mov < 0)
        {
            if (y_mov > 0)
            {
                aux = 135;
            }
            else
                aux = 225;
        }
        this->direction.x = cos(aux * M_PI / 180.0);
        this->direction.y = sin(aux * M_PI / 180.0);
    }
    else
    {
        this->direction.x = x_mov;
        this->direction.y = y_mov;
    }

    this->direction.z = 0;
    return keys.space;
}

void Player::move()
{
    updateOnKeyboard(keyboard);
    // Movimenta o player usando o vetor unitário de direção
    this->origin.x += this->direction.x * velocidade;
    this->origin.y += this->direction.y * velocidade;
    this->origin.z += this->direction.z * velocidade;

    // printf("Player [Velocity : %0.2f, Vec : %0.2f %0.2f %0.2f] || x->%0.2f y->%0.2f \n", this->velocidade, this->origin.x, this->origin.y, this->origin.z,max_x,max_y);
}

void Player::draw()
{
    glPushMatrix();

    glTranslatef(this->origin.x, this->origin.y, this->origin.z);
    glRotatef(this->angle, 0, 0, 1);
    glColor3ub(255,255,255);

    // Carrega o objeto de textura para manipular no OpenGL
    // glBindTexture(GL_TEXTURE_2D, this->texture->loaded_textures[0]);

    // A é a textura 1

    if(this->direction.x > 0)
    {
        glBindTexture(GL_TEXTURE_2D, this->texture->loaded_textures[2]);
    }
    else if( this->direction.x < 0)
    {
         glBindTexture(GL_TEXTURE_2D, this->texture->loaded_textures[1]);
    }
    else
        glBindTexture(GL_TEXTURE_2D, this->texture->loaded_textures[0]);

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < this->model.size(); i++)
    {
        // Associa a textura ao objeto desenhado
        glTexCoord2f(this->texture->texture_cords[0][i].x, this->texture->texture_cords[0][i].y);
        glVertex3f(this->model[i].x, this->model[i].y, this->model[i].z);
    }
    glEnd();

    glPopMatrix();

#ifdef DRAW_BOX
    glColor3ub(125, 125, 200);
    glBegin(GL_LINES);
    for (int r = 0, j = 1; r < this->hit_box.size(); r++, j = (r + 1) % (this->hit_box.size()))
    {
        // printf("%f %f \n", player->model[i].x, player->model[i].y);
        glVertex2f(this->hit_box[r].x, this->hit_box[r].y);
        glVertex2f(this->hit_box[j].x, this->hit_box[j].y);
    }
    glEnd();

#endif
}

Shot *Player::playerFire()
{
    vec3f_t dir = {
        .x = 0,
        .y = 1,
        .z = 0};

    vec3f_t shot_origin = this->origin;
    shot_origin.y += 12;

    // Passa os dados para serem criado o tiro para ser tratado no colider
    // Tiro com id=2 --> tiro do player
    return new Shot(shot_origin, 90.0f, 2.0f, dir,this->id,"assets/scripts/player_shot.tscp",this->cont_stage_tex);
}

int Player::destroy()
{

    // printf("hp = %d , vidas= %d \n",this->hp,this->vidas);

    if (hp > 0)
    {
        hp--;
    }

    if (vidas > 0 && hp == 0)
    {
        hp = 2;
        vidas--;
    }

    if (vidas == 0 && hp == 0)
    {
        return 1;
    }

    return 0;
}
