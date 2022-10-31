#include "World.h"

void World::initialize_script_mission()
{

    std::list<mission_wave> aux;

    // missao 1
    parse_mission(&aux, "assets/scripts/roteiro1");
    this->stack_mission.push(aux);
    aux.clear();

    // missao 2
    /*
    parse_mission(&aux, "assets/scripts/roteiro2");
    this->stack_mission.push(aux);
    aux.clear();
    */
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

    if (!stack_mission.empty() )
        mission_handler(&stack_mission.front(), time);

    if (*time > 90.0 && !stack_mission.empty() && troca < 1)
    {
        troca++;
        *time = 0;
        stack_mission.pop();
        // troca a textura do background
        background->trocar_back();
        printf("entrou 2 roteiro, time =%0.2f\n", *time);
    }
}

// metodo que recebe o vector<wave>, e gerencia a missao
void World::mission_handler(std::list<mission_wave> *fase_script, float *time)
{

    vec3f_t str_aux, shooter_aux;
    std::shared_ptr<Enemy> shr_ptr;
    std::shared_ptr<Boss> shr_boss;
    // printf("now time is : %f\n",*time);
    for (int i = 0; i < fase_script->size(); i++)
    {

        if ((*fase_script->begin()).time <= *time)
        {
            if ((*fase_script->begin()).id_enemy == 4 )
            {
                printf("criando boss \n");
                str_aux.x = (*fase_script->begin()).x;
                str_aux.y = (*fase_script->begin()).y;
                str_aux.z = 0;

                // usando smartpointer para nao da merda
                // aloca um novo smartpointer dentro do vetor
                shr_boss = std::make_shared<Boss>(str_aux,
                                                  0,
                                                  1.5f,
                                                  create_models((*fase_script->begin()).id_enemy),
                                                  create_models((*fase_script->begin()).id_enemy));

                send_texture((*fase_script->begin()).id_enemy, shr_boss);
                actual_boss=shr_boss;
                //background->start_boss();
                vec_entitys.push_back(shr_boss);
            }

            else if ((*fase_script->begin()).id_enemy == 0)
            {
                str_aux.x = (*fase_script->begin()).x;
                str_aux.y = (*fase_script->begin()).y;
                str_aux.z = 0;

                shr_ptr = std::make_shared<PowerUp>(str_aux, 0.0f, 1.0f, 0);
                vec_entitys.push_back(shr_ptr);
            }
            else if ((*fase_script->begin()).id_enemy == 7)
            {
                str_aux.x = (*fase_script->begin()).x;
                str_aux.y = (*fase_script->begin()).y;
                str_aux.z = 0;

                shr_ptr = std::make_shared<PowerUp>(str_aux, 0.0f, 1.0f, 1);
                vec_entitys.push_back(shr_ptr);
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
                else if ((*fase_script->begin()).id_enemy == 3)
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
    actual_player.reset();

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
        parse_model(&aux, "assets/scripts/powerUp.mscp");
        break;

    // inimigo que anda reto pra baixo
    case 1:
        parse_model(&aux, "assets/scripts/inimigo_tipo1.mscp");
        break;

    // helicoptero que persegue
    case 2:
        parse_model(&aux, "assets/scripts/inimigo_tipo2.mscp");
        break;

    // inimigo que para e atira
    case 3:
        parse_model(&aux, "assets/scripts/inimigo_tipo3.mscp");
        break;

    // id = 4 é o chefao
    case 4:
        parse_model(&aux, "assets/scripts/Boss.mscp");
        break;

    // Boss stage 2
    case 5:
        parse_model(&aux, "assets/scripts/chefao2.mscp");
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

        if (vec_entitys.at(x)->alive) 
        {
            to_colider.push_back(vec_entitys.at(x));
        }
        else
        {
            printf("Deleted an entity of id %d \n", vec_entitys[x]->getId());
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

    actual_player = std::make_shared<Player>(origin, 0.0f, 3.0f, vector, vector);
    vec_entitys.push_back(actual_player);
}

void World::update_entitys(float *timer_count)
{

    int shot = 0;
    // Updates the movements
    if (actual_player != nullptr)
        shot = actual_player->updateOnKeyboard(keyboard);

    if (shot && actual_player->getTimer() > 0.3)
    {
        vec_entitys.push_back(std::shared_ptr<Shot>(actual_player->playerFire()));
    }
    int consta = vec_entitys.size();
    for (int i = 0; i < consta; i++)
    {

        // printf(" id =%d , timer =%0.2f \n",vec_entitys.at(i)->getId(),vec_entitys.at(i)->getTimer());
        //logica tiro boss
        if (vec_entitys.at(i)->getId() == 4 && vec_entitys.at(i)->getTimer() > 1.0)
        {
            vec_entitys.push_back(std::shared_ptr<Shot>(((Enemy *)(vec_entitys.at(i).get()))->enemyFire()));
            // printf("entrou %d z\n",vec_entitys.at(i)->getId());
        }
        if (vec_entitys.at(i)->getId() ==3 && vec_entitys.at(i)->getTimer() > 0.8)
        {
            vec_entitys.push_back(std::shared_ptr<Shot>(((Enemy *)(vec_entitys.at(i).get()))->enemyFire()));
            // printf("entrou %d z\n",vec_entitys.at(i)->getId());
        }
    }

    for (int i = 0; i < vec_entitys.size(); i++)
    {
        if (vec_entitys.at(i)->getId() == 4)
            ((Enemy *)vec_entitys.at(i).get())->move(this->actual_player->getOrigin());
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
        shr_ptr->setTexture(std::make_shared<Texturazer>("assets/scripts/inimigo_tipo1.tscp"));
        break;

    // helicoptero que persegue
    case 2:
        shr_ptr->setTexture(std::make_shared<Texturazer>("assets/scripts/inimigo_tipo2.tscp"));
        break;

    // inimigo que para e atira
    case 3:
        shr_ptr->setTexture(std::make_shared<Texturazer>("assets/scripts/inimigo_tipo3.tscp"));
        break;
    // boss 1
    case 4:
        shr_ptr->setTexture(std::make_shared<Texturazer>("assets/scripts/Boss.tscp"));
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

// Por favor alguem me ajude >_< - RIP CAMISA 09
void World::drawFancyStuff()
{
    // Desenha a barra de vida do player
    vec3f_t aux = {0};
    float divs;

    // Verifica se tem um player na cena
    if (this->actual_player != nullptr)
    {
        aux.x = -max_x;
        aux.y = -max_y;

        glDisable(GL_TEXTURE_2D);
        // glDisable(GL_BLEND);
        // Cor do Menu 130, 196, 209
        glColor4ub(130, 196, 209,160);
        glBegin(GL_TRIANGLE_FAN);

        glVertex2f(aux.x + 15, aux.y + 35);
        glVertex2f(aux.x + 15, aux.y + 15);

        glVertex2f(aux.x + 70, aux.y + 15);
        glVertex2f(aux.x + 70, aux.y + 35);

        glEnd();

        divs = 0;

        // Divide pelo numero de vidas maxima do player
        // HARDCODED LLLL
        // printf("Hp do player : %d \n",actual_player->getHp());
        divs += 45 * actual_player->hp/10.0f;

        glColor4ub(0,255,0,160);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(aux.x + 20, aux.y + 30);
        glVertex2f(aux.x + 20, aux.y + 20);

        glVertex2f(aux.x +  20 + divs, aux.y + 20);
        glVertex2f(aux.x + 20 + divs, aux.y + 30);
        glEnd();

        // glEnable(GL_BLEND);
        glEnable(GL_TEXTURE_2D);
    }
    aux = {0};
    // Desenha a vida do boss
    if (this->actual_boss != nullptr)
    {
        aux.x = +max_x;
        aux.y = -max_y;

        glDisable(GL_TEXTURE_2D);
        // glDisable(GL_BLEND);
        // Cor do Menu 130, 196, 209
        glColor4ub(130, 196, 209,160);
        glBegin(GL_TRIANGLE_FAN);

        glVertex2f(aux.x - 15, aux.y + 35);
        glVertex2f(aux.x - 15, aux.y + 15);

        glVertex2f(aux.x - 70, aux.y + 15);
        glVertex2f(aux.x - 70, aux.y + 35);

        glEnd();

        divs = 0;

        // Divide pelo numero de vidas maxima do player
        // HARDCODED LLLL
        // printf("Hp do player : %d \n",actual_player->getHp());
        divs += 45 * (float)this->actual_boss->getHp() /110.0f;

        glColor4ub(255,0,0,160);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(aux.x -20, aux.y + 30);
        glVertex2f(aux.x -20, aux.y + 20);

        glVertex2f(aux.x  -20 - divs, aux.y + 20);
        glVertex2f(aux.x  -20 - divs, aux.y + 30);
        glEnd();

        // glEnable(GL_BLEND);
        glEnable(GL_TEXTURE_2D);
    }
}

void World::Credits()
{
}