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

            this->origin.x += this->direction.x * velocidade;
            this->origin.y += this->direction.y * velocidade;
            this->origin.z += this->direction.z * velocidade;
        }
        else
            arrived = true;
    }
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
    this->distance_angle = 0;

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

// ___________________________________________