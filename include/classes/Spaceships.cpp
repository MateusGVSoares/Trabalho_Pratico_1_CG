#include "Spaceships.h"

// __SHOOTER__
Shooter::Shooter(vec3f_t origin,
                 float angle,
                 float velocidade,
                 vec3f_t final_point) : Enemy(origin, angle, velocidade)
{
    // Inicializa o ponto em que ele deve parar
    this->final_point = final_point;
    this->texture = std::make_shared<Texturazer>("assets/scripts/Shooter.tscp");

    std::vector<vec3f_t> aux;
    if (parse_model(&aux, "assets/scripts/Shooter.mscp"))
    {
        printf("Deu ruim renderizando o modelo do inimigo SHOOTER \n");
    }

    this->model = aux;
    this->hit_box = aux;
    this->box_model = aux;
    this->id = 4;
}

void Shooter::move()
{
    // Incrementa o timer do shooter
    this->timer += 0.016;

    // Calcula a direcao de acordo com o ponto final passado no construtor
    this->calc_direction(&this->final_point);

    float distance = pow(this->direction.x, 2) + pow(this->direction.y, 2) + pow(this->direction.z, 2);

    this->direction.x /= distance;
    this->direction.y /= distance;
    this->direction.z /= distance;

    this->origin.x += this->direction.x * velocidade;
    this->origin.y += this->direction.y * velocidade;
    this->origin.z += this->direction.z * velocidade;
}

void Shooter::move(vec3f_t *point)
{
    this->timer += 0.016;
    if (!arrived)
    {

        // Calcula a direcao de acordo com o ponto final passado no construtor
        this->calc_direction(&this->final_point);

        float distance = pow(this->direction.x, 2) + pow(this->direction.y, 2) + pow(this->direction.z, 2);
        distance = sqrt(distance);
        if (distance >= this->velocidade)
        {
            this->direction.x /= distance;
            this->direction.y /= distance;
            this->direction.z /= distance;
        }
        else
        {
            this->direction.x = 1;
            this->direction.y = 0;
            arrived = true;
        }
    }
    else
    {   
        if(this->direction.y)
        {
            this->direction.y = 0;
        }
        if(!this->on_screen)
        {
            this->alive = 0;
            return;
        }
        if (this->border_x_col)
        {
            this->direction.x *= -1;
        }
    }


    this->origin.x += this->direction.x * velocidade;
    this->origin.y += this->direction.y * velocidade;
    this->origin.z += this->direction.z * velocidade;
}

Shot *Shooter::enemyFire()
{
    this->timer = 0.0;
    vec3f_t dir = {
        .x = 0,
        .y = -1,
        .z = 0};

    // Ajusta o ponto de origem do tiro
    vec3f_t shotOrigin = this->origin;

    shotOrigin.y -= 12;

    return new Shot(shotOrigin, 0, 3.5f, dir, 3, "assets/scripts/enemyShot.tscp", this->cont_stage_tex);
}

// _______________________________________________

// __KAMIKAZE__
Kamikaze::Kamikaze(vec3f_t origin,
                   float angle,
                   float velocidade) : Enemy(origin, angle, velocidade)
{
    this->angle = 180;
    this->texture = std::make_shared<Texturazer>("assets/scripts/Kamikaze.tscp");

    this->distance = 0;

    std::vector<vec3f_t> aux;

    if (parse_model(&aux, "assets/scripts/Kamikaze.mscp"))
    {
        printf("Deu ruim renderizando o modelo do inimigo KAMIKAZE \n");
    }

    this->model = aux;
    this->hit_box = aux;
    this->box_model = aux;
    this->id = 4;
}

void Kamikaze::move(vec3f_t *point)
{
    // Calcula a distancia do player ao centro do objeto
    this->calc_direction(point);

    float distance = pow(this->direction.x, 2) +
                     pow(this->direction.y, 2) +
                     pow(this->direction.z, 2);

    float aux_angle;

    distance = sqrt(distance);

    aux_angle = 180.0f / M_PI * acos(this->direction.x / distance);

    if (direction.y < 0)
    {
        aux_angle = 360 - aux_angle;
    }

    this->angle = -90 + aux_angle;

    this->direction.x /= distance;
    this->direction.y /= distance;
    this->direction.z /= distance;

    this->origin.x += direction.x * velocidade;
    this->origin.y += direction.y * velocidade;
    this->origin.z += 0;
}
// _____________________________________-

// __RUNNNER__
Kamikaze2::Kamikaze2(vec3f_t origin,
                     float angle,
                     float velocidade) : Enemy(origin, angle, velocidade)
{
    this->angle = 180;
    this->texture = std::make_shared<Texturazer>("assets/scripts/Kamikaze2.tscp");

    this->distance_angle = 90;

    std::vector<vec3f_t> aux;

    if (parse_model(&aux, "assets/scripts/Kamikaze2.mscp"))
    {
        printf("Deu ruim renderizando o modelo do inimigo KAMIKAZE \n");
    }

    this->model = aux;
    this->hit_box = aux;
    this->box_model = aux;
    this->id = 4;
    this->direction.y = -1;
}
void Kamikaze2::move(vec3f_t *point)
{
    if ((!this->on_screen) && this->hit_box[0].y < 0)
    {
        this->alive = 0;
        return;
    }

    this->distance_angle += 4;

    if (distance_angle >= 360)
    {
        this->distance_angle -= 360;
    }

    this->direction.x = cos(this->distance_angle * M_PI / 180.0f) * velocidade;

    this->origin.x += direction.x;
    this->origin.y += direction.y * velocidade;
    this->origin.z += direction.z;
}
// _____________________________________-

// __RUNNNER__

Runner::Runner(vec3f_t origin,
               float angle,
               float velocidade, int runner_type) : Enemy(origin, angle, velocidade)
{
    printf("%f velocidade \n", velocidade);
    this->direction.x = 0;
    this->direction.y = -1;
    this->direction.z = 0;

    if (runner_type)
        this->texture = std::make_shared<Texturazer>("assets/scripts/Runner1.tscp");
    else
        this->texture = std::make_shared<Texturazer>("assets/scripts/Runner0.tscp");

    std::vector<vec3f_t> aux;

    if (parse_model(&aux, "assets/scripts/Runner.mscp"))
    {
        printf("Deu ruim renderizando o modelo do inimigo RUNNER \n");
    }

    this->model = aux;
    this->hit_box = aux;
    this->box_model = aux;
    this->id = 4;
}

void Runner::move(vec3f_t *point)
{
    if ((!this->on_screen) && this->hit_box[0].y < 0)
    {
        this->alive = 0;
    }
    else
    {
        this->origin.x += direction.x * velocidade;
        this->origin.y += direction.y * velocidade;
        this->origin.z += direction.z;
    }
}

// ________________________________________

// ______ POWERED UP ______________________

PowerUp::PowerUp(vec3f_t origin,
                 float angle,
                 float velocidade, int type) : Enemy(origin, angle, velocidade)
{
    this->distance_angle = 90;
    this->direction.x = 0;
    this->direction.y = -1;
    this->direction.z = 0;
    this->type = type;

    this->texture = std::make_shared<Texturazer>("assets/scripts/powerUp.tscp");

    std::vector<vec3f_t> aux;

    if (parse_model(&aux, "assets/scripts/powerUp.mscp"))
    {
        printf("Deu ruim renderizando o modelo do POWERUP KKK \n");
    }

    this->model = aux;
    this->hit_box = aux;
    this->box_model = aux;

    this->id = 16;
}

void PowerUp::move()
{
    if ((!this->on_screen) && this->hit_box[0].y < 0)
    {
        this->alive = 0;
        return;
    }

    this->distance_angle += 2;

    if (distance_angle >= 360)
    {
        this->distance_angle -= 360;
    }

    this->direction.x = cos(this->distance_angle * M_PI / 180.0f);

    this->origin.x += direction.x;
    this->origin.y += direction.y * velocidade;
    this->origin.z += direction.z;
}

void PowerUp::draw()
{
    glPushMatrix();

    glTranslatef(this->origin.x, this->origin.y, this->origin.z);
    glRotatef(this->angle, 0, 0, 1);

    if (this->type)
        glColor3ub(255, 0, 0);
    else
        glColor3ub(255, 255, 255);

    // Carrega o objeto de textura para manipular no OpenGL
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
}

int PowerUp::getType()
{
    return this->type;
}
// ___________________________________________