#include "Player.h"

#define DRAW_BOX

Player::Player(vec3f_t origin, int layer, float angle, float velocidade, std::vector<vec3f_t> hit_box, std::vector<vec3f_t> model) : Entidade(origin, layer, angle, velocidade)
{
    // Let the player handles the model things
    this->model = model;
    this->box_model = hit_box;
    this->hit_box = hit_box;
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
    // printf("Player [Velocity : %0.2f, Vec : %0.2f %0.2f %0.2f] \n", this->velocidade, this->origin.x, this->origin.y, this->origin.z);
    // Moves the player using the unitary direction vector
    this->origin.x += this->direction.x * velocidade;
    this->origin.y += this->direction.y * velocidade;
    this->origin.z += this->direction.z * velocidade;
}

void Player::draw()
{
    glPushMatrix();

    glTranslatef(this->origin.x, this->origin.y, this->origin.z);
    glRotatef(this->angle, 0, 0, 1);
    glColor3ub(234, 55, 43);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < this->model.size(); i++)
    {
        // chamar a gl texture pelo metodo que foi herdado do texturazer
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

    // TODO : Apply texture to the player
}

Shot Player::playerFire()
{
    vec3f_t dir = {
        .x = 0,
        .y = 1,
        .z = 0};

    Shot ret_shot(this->origin, 1, 0, 0.5f, dir, this->model, this->box_model);

    return ret_shot;
}

void Player::treatColide(int col_type)
{
    printf("Colided with %d layer \n", col_type);
}