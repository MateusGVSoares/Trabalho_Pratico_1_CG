#include "World.h"

void World::initialize_script_mission()
{

    std::list<mission_wave> aux;

    // missao 1
    parse_mission(&aux, "assets/scripts/roteiro1");
    this->stack_mission.push(aux);
    aux.clear();

    // missao 2
    parse_mission(&aux, "assets/scripts/roteiro2");
    this->stack_mission.push(aux);
    aux.clear();
    /*
    //missao 3
    parse_mission(&aux,"roteiro1");
    this->stack_mission.push(aux);
    aux.clear();

    //missao 4
    parse_mission(&aux,"roteiro1");
    this->stack_mission.push(aux);
    aux.clear();
    */
}

void World::start_mission(float *time)
{

    // criamos um vetor auxiliar para retirar os vetores(vetor=o roteiro de uma fase) que estao na queue

    // TODO logica de spawnar inimigos e controle de tempo
    // criar metodo que faz o controle da missao e chamar aqui

    if (!stack_mission.empty())
        mission_handler(&stack_mission.front(), time);

    if (*time > 7.0 && !stack_mission.empty())
    {
        *time = 0;
        stack_mission.pop();
        // troca a textura do background
        // background.reset();
        // background->setTexture(std::make_shared<Texturazer>("assets/scripts/background2.tscp"));
        printf("entrou 2 roteiro, time =%0.2f\n", *time);
    }
}

// metodo que recebe o vector<wave>, e gerencia a missao
void World::mission_handler(std::list<mission_wave> *fase_script, float *time)
{

    vec3f_t str_aux = {0}, shooter_aux = {0};
    std::shared_ptr<Enemy> shr_ptr;
    std::shared_ptr<Boss> shr_boss;
    // printf("now time is : %f\n",*time);
    for (int i = 0; i < fase_script->size(); i++)
    {

        if ((*fase_script->begin()).time <= *time)
        {

            // (1 a 3) ou 6 -> inimgo
            // 0 powerup
            // 4 e 5 boss

            if ((*fase_script->begin()).id_enemy == 4 || (*fase_script->begin()).id_enemy == 5)
            {
                str_aux.x = (*fase_script->begin()).x;
                str_aux.y = (*fase_script->begin()).y;
                str_aux.z = 0;

                // usando smartpointer para nao da merda
                // aloca um novo smartpointer dentro do vetor
                shr_boss = std::make_shared<Boss>(str_aux,
                                                  0,
                                                  0.5,
                                                  create_models((*fase_script->begin()).id_enemy),
                                                  create_models((*fase_script->begin()).id_enemy));

                send_texture((*fase_script->begin()).id_enemy, shr_boss);

                vec_entitys.push_back(shr_boss);
            }
            else if ((*fase_script->begin()).id_enemy == 0)
            {

                str_aux.x = (*fase_script->begin()).x;
                str_aux.y = (*fase_script->begin()).y;
                str_aux.z = 0;

                shr_ptr = std::make_shared<Enemy>(str_aux, 0.0f, 0.5f,
                                                  create_models((*fase_script->begin()).id_enemy),
                                                  create_models((*fase_script->begin()).id_enemy));
                send_texture((*fase_script->begin()).id_enemy, shr_ptr);
                shr_ptr.get()->setId(16);
            }
            else
            {
                // usando str_aux para auxiliar a criação dos objetos inimigos lidos no arquivo txt pelo parser
                str_aux.x = (*fase_script->begin()).x;
                str_aux.y = (*fase_script->begin()).y;
                str_aux.z = 0;

                // 1 e o RUNNER e o 6 e tbm um RUNNER, mas com textura diferenciada
                if ((*fase_script->begin()).id_enemy == 1)
                {
                    shr_ptr = std::make_shared<Runner>(str_aux, 180, 2.0f, 0);
                }
                else if ((*fase_script->begin()).id_enemy == 6)
                {
                    shr_ptr = std::make_shared<Runner>(str_aux, 180, 2.0f, 1);
                }
                // Kamikaze
                else if ((*fase_script->begin()).id_enemy == 2)
                {
                    shr_ptr = std::make_shared<Kamikaze>(str_aux, 0, 1.0f);
                }
                // Shooter
                else
                {
                    shooter_aux.x = str_aux.x;
                    shooter_aux.y = str_aux.y - 100;
                    shooter_aux.z = 0;
                    shr_ptr = std::make_shared<Shooter>(str_aux, 180, 3.0f, shooter_aux);
                }

                vec_entitys.push_back(shr_ptr);
            }

            printf("tempo =%0.2f ,i.time=%0.2f , id=%d ,x=%0.2f ,y=%0.2f \n ", *time, (*fase_script->begin()).time, (*fase_script->begin()).id_enemy, (*fase_script->begin()).x, (*fase_script->begin()).y);

            // retira o elemento da lista.
            fase_script->pop_front();
        }
    }
}

World::World()
{
    colisor = new Colider();
    initbackGround();
    initPlayer();
}

// metodo para enviar os objetos que estao na tela para serem tratados pelo Colider
std::vector<std::shared_ptr<Entidade>> World::send_to_colider(std::vector<std::shared_ptr<Entidade>> vec_hitbox)
{

    // chama o colider
    return colisor->check_colison(vec_hitbox);
}

// metodo para criar as coordenadas das hitbox e modelos para jogar dentro do vetor Entidades
std::vector<vec3f_t> World::create_models(int id)
{

    std::vector<vec3f_t> aux;

    // Seleciona qual modelo ira utilizar de acordo com o inimigo
    switch (id)
    {
    // powerup
    case 0:
        !parse_model(&aux, "assets/scripts/powerUp.mscp");
        break;

    // inimigo que anda reto pra baixo Runner
    case 1:
        !parse_model(&aux, "assets/scripts/Runner.mscp");
        break;

    // helicoptero que persegue Kamikaze
    case 2:
        !parse_model(&aux, "assets/scripts/Kamikaze.mscp");
        break;

    // inimigo que para e atira Shooter
    case 3:
        !parse_model(&aux, "assets/scripts/Shooter.mscp");
        break;

    // id = 4 é o chefao
    case 4:
        !parse_model(&aux, "assets/scripts/chefao1.mscp");
        break;

    // Boss stage 2
    case 5:
        !parse_model(&aux, "assets/scripts/chefao2.mscp");
        break;
    }

    return aux;
}

void World::draw_vec_entitys()
{

    std::vector<std::shared_ptr<Entidade>> to_colider;
    // printf("tamanho do vec entitys = %d \n",vec_entitys.size());
    // movo,atualizo e ordeno pro colider
    for (int x = 0; x < vec_entitys.size(); x++)
    {

        if (vec_entitys.at(x)->getOnScreen())
        {
            to_colider.push_back(vec_entitys.at(x));
        }
        else
        {
            vec_entitys.erase(vec_entitys.begin() + x);
            x--;
        }
    }
    // printf("tamanho sendotocolider = %d \n",to_colider.size());
    // depois de ordenado, mandar pro colider
    vec_entitys = send_to_colider(to_colider);
    to_colider.clear();
    // printf("tamanho do vec entitys depois = %d \n",vec_entitys.size());

    for (int x = 0; x < vec_entitys.size(); x++)
        vec_entitys.at(x)->draw();

    // Desenha os menus

    
}

void World::initPlayer()
{
    std::vector<vec3f_t> vector;

    if (!parse_model(&vector, "assets/scripts/player.mscp"))
    {
        printf("DEU BOM NO FILE \n");
    }

    vec3f_t origin = {
        .x = 0,
        .y = 0,
        .z = 0};

    joga = std::make_shared<Player>(origin, 0.0f, 1.0f, vector, vector);
    vec_entitys.push_back(joga);
}

void World::update_entitys(float *timer_count)
{

    int shot = 0;
    // Updates the movements
    if (joga != nullptr)
        shot = joga->updateOnKeyboard(keyboard);

    if (shot && *timer_count > 0.3)
    {
        *timer_count = 0;
        vec_entitys.push_back(std::shared_ptr<Shot>(joga->playerFire()));
    }
    int consta = vec_entitys.size();

    for (int i = 0; i < consta; i++)
    {
        // printf(" id =%d , timer =%0.2f \n",vec_entitys.at(i)->getId(),vec_entitys.at(i)->getTimer());
        if (vec_entitys.at(i)->getId() == 4 && vec_entitys.at(i)->getTimer() > 1.0)
        {
            vec_entitys.push_back(std::shared_ptr<Shot>(((Boss *)(vec_entitys.at(i).get()))->enemyFire()));
            // printf("entrou %d z\n",vec_entitys.at(i)->getId());
        }
        else if (vec_entitys.at(i)->getId() == 3 && vec_entitys.at(i)->getTimer() > 1.0)
        {

            vec_entitys.push_back(std::shared_ptr<Shot>(((Enemy *)(vec_entitys.at(i).get()))->enemyFire()));
            // printf("entrou %d z\n",vec_entitys.at(i)->getId());
        }
    }

    for (int i = 0; i < vec_entitys.size(); i++)
    {
        if (vec_entitys.at(i)->getId() == 4)
        {
            ((Enemy *)(vec_entitys.at(i).get()))->move(this->joga->getOrigin());
        }
        else
            vec_entitys.at(i)->move();

        vec_entitys.at(i)->updateModel();
    }

    // Reutilizando funcao - Adjailson >_<
    background->destroy();
}

void World::send_texture(int id, std::shared_ptr<Enemy> shr_ptr)
{

    // id =1, inimigo normal
    // id =3 ...
    switch (id)
    {
    // powerup
    case 0:
        shr_ptr->setTexture(std::make_shared<Texturazer>("assets/scripts/powerUp.tscp"));
        break;

    // inimigo que anda reto pra baixo
    case 1:
        shr_ptr->setTexture(std::make_shared<Texturazer>("assets/scripts/Runner.tscp"));
        break;

    // helicoptero que persegue
    case 2:
        shr_ptr->setTexture(std::make_shared<Texturazer>("assets/scripts/Kamikaze.tscp"));
        break;

    // inimigo que para e atira
    case 3:
        shr_ptr->setTexture(std::make_shared<Texturazer>("assets/scripts/Shooter.tscp"));
        break;
    // boss 1
    case 4:
        shr_ptr->setTexture(std::make_shared<Texturazer>("assets/scripts/chefao1.tscp"));
        break;
    case 5:
        shr_ptr->setTexture(std::make_shared<Texturazer>("assets/scripts/chefao2.tscp"));
        break;
    }
}

void World::initbackGround()
{

    std::vector<vec3f_t> str_aux;
    vec3f_t p1 = {-256, 224, -1};
    vec3f_t p2 = {256, 224, -1};
    vec3f_t p3 = {256, -224, -1};
    vec3f_t p4 = {-256, -224, -1};
    vec3f_t p5 = {0, 0, 0};
    str_aux.push_back(p1);
    str_aux.push_back(p2);
    str_aux.push_back(p3);
    str_aux.push_back(p4);

    background = std::make_shared<Background>(p5,
                                              0.0f,
                                              13.22f,
                                              str_aux,
                                              str_aux);

    background->setTexture(std::make_shared<Texturazer>("assets/scripts/background1.tscp"));
    vec_entitys.push_back(background);
}

void World::Credits()
{
}