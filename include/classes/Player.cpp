#include "Player.h"

// #define DRAW_BOX

Player::Player(vec3f_t origin,
               float angle,
               float velocidade,
               std::vector<vec3f_t> hit_box,
               std::vector<vec3f_t> model) : Entidade(origin, angle, velocidade)
{
    // Deixa o player alocar os modelos
    this->model = model;
    this->box_model = hit_box;
    this->hit_box = hit_box;

    this->texture = std::make_shared<Texturazer>("assets/scripts/player.tscp");
    this->hp = 10;
    this->vidas = 2;
    this->cont_stage_tex = 0;
    this->velocidade = velocidade;
    this->invecible = 0;
    this->timer_invecible = 0.0;
    // ID para colisao(não é o id de carregamento das coisas do script)
    this->id = 1;
    this->select_shot = 1;
    this->level_gun1 = 1;
    this->level_gun2 = 1;
    this->timer_troca_gun = 0.0;
};

int *Player::getHp()
{
    return &this->hp;
}

int Player::updateOnKeyboard(keyboard_t keys)
{
    int x_mov = (keys.d || keys.right) - (keys.left || keys.a);
    int y_mov = (keys.up || keys.w) - (keys.down || keys.s);

    float aux = 0.0;

    if (this->timer_troca_gun > 0.5)
    {

        if (keys.x == 1)
        {
            this->select_shot *= -1;
            // printf("entrou aqui \n");
            this->timer_troca_gun = 0.0;
        }
    }

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

    if (this->origin.x > (256 - this->model[0].x) * razaoAspecto)
        this->origin.x -= this->velocidade;

    if (this->origin.x < -(256 - this->model[0].x) * razaoAspecto)
        this->origin.x += this->velocidade;

    if (this->origin.y > (224 - this->model[0].y))
        this->origin.y -= this->velocidade;

    if (this->origin.y < -(224 - this->model[0].y))
        this->origin.y += this->velocidade;

    return keys.space;
}

void Player::move()
{
    if (this->select_shot == 1)
        this->timer += (9.0 / 1000.0 * level_gun1);

    else
        this->timer += (11.0 / 1000.0);

    this->timer_troca_gun += 16.0 / 1000.0;
    this->timer_invecible += 16.0 / 1000.0;

    if (invecible == 1 && timer_invecible > 1.5)
    {
        invecible = 0;
    }

    updateOnKeyboard(keyboard);
    // Movimenta o player usando o vetor unitário de direção
    this->origin.x += this->direction.x * velocidade;
    this->origin.y += this->direction.y * velocidade;
    this->origin.z += this->direction.z * velocidade;

    // printf("Player [Velocity : %0.2f, Vec : %0.2f %0.2f %0.2f] || x->%0.2f y->%0.2f \n", this->velocidade, this->origin.x, this->origin.y, this->origin.z,max_x,max_y);
}

void Player::treatUpgrade(int type)
{
    // Verifica se e upgrade ou vida :_:
    if (type == 0)
    {
        printf("Ta ficando monstro >_< \n");
        if (this->select_shot == 1 && this->level_gun1 < 3)
        {
            printf("entrou 1\n");
            this->level_gun1++;
        }

        else if (this->select_shot == -1 && this->level_gun2 < 3)
        {
            printf("entrou 2\n");
            this->level_gun2++;
        }

        else if (this->select_shot == 1 && this->level_gun1 == 3 && this->level_gun2 < 3)
        {
            printf("entrou 3\n");
            this->level_gun2++;
        }

        else if (this->select_shot == -1 && this->level_gun2 == 3 && this->level_gun1 < 3)
        {
            printf("entrou 4\n");
            this->level_gun1++;
        }
        else
        {
            // Se n fizer nada com o up, restaura hp
            if (this->hp < 10)
                this->hp += 1;
        }
    }
    else
    {
        printf("Pegou vidinha >_< \n");
        // Restaura 2 de hp
        if (this->hp < 10)
            this->hp += 1;
        printf("Hp do player : %d \n", this->hp);
    }
}

void Player::draw()
{
    glPushMatrix();

    glTranslatef(this->origin.x, this->origin.y, this->origin.z);
    glRotatef(this->angle, 0, 0, 1);

    glColor3ub(255, 255, 255);

    // Carrega o objeto de textura para manipular no OpenGL
    // glBindTexture(GL_TEXTURE_2D, this->texture->loaded_textures[0]);

    // A é a textura 1
    if (keyboard.a == 1 && keyboard.d == 0 || keyboard.left == 1 && keyboard.right == 0)
    {
        glBindTexture(GL_TEXTURE_2D, this->texture->loaded_textures[1]);
    }
    // D é a textura 2
    else if (keyboard.d == 1 && keyboard.a == 0 || keyboard.right == 1 && keyboard.left == 0)
    {
        glBindTexture(GL_TEXTURE_2D, this->texture->loaded_textures[2]);
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, this->texture->loaded_textures[0]);
    }

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < this->model.size(); i++)
    {
        // Associa a textura ao objeto desenhado
        glTexCoord2f(this->texture->texture_cords[0][i].x, this->texture->texture_cords[0][i].y);
        glVertex3f(this->model[i].x, this->model[i].y, this->model[i].z);
    }
    glEnd();
    if (invecible == 1)
    {
        glColor3ub(10, 10, 255);
        glBindTexture(GL_TEXTURE_2D, this->texture->loaded_textures[3]);

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
    this->timer = 0.0;
    vec3f_t dir = {
        .x = 0,
        .y = 1,
        .z = 0};

    vec3f_t shot_origin = this->origin;
    shot_origin.y += 12;

    // Passa os dados para serem criado o tiro para ser tratado no colider
    // Tiro com id=2 --> tiro do player
    if (select_shot == 1)
        return new Shot(shot_origin, 90.0f, 5.0f, dir, this->id, "assets/scripts/player_shot.tscp", 0, this->level_gun1);
    else
        return new Shot(shot_origin, 0.0f, 2.7f, dir, this->id, "assets/scripts/player_shot.tscp", 1, this->level_gun2);
}

int Player::destroy()
{

    // printf("hp = %d , vidas= %d \n",this->hp,this->vidas);
    if (invecible == 0)
    {
        invecible = 1;
        timer_invecible = 0.0;
        if (hp > 0)
        {
            hp--;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}
