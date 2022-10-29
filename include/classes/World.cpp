#include "World.h"



void World::initialize_script_mission(){

    std::list<mission_wave> aux;

    //missao 1
    parse_mission(&aux,"assets/scripts/roteiro1");
    this->stack_mission.push(aux);
    aux.clear();

    //missao 2
    parse_mission(&aux,"assets/scripts/roteiro2");
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

void World::start_mission(float *time){

    //criamos um vetor auxiliar para retirar os vetores(vetor=o roteiro de uma fase) que estao na queue

        
    //TODO logica de spawnar inimigos e controle de tempo
    //criar metodo que faz o controle da missao e chamar aqui

    if(!stack_mission.empty())
        mission_handler(&stack_mission.front(),time);    

    if(*time>7.0 && !stack_mission.empty() ){
        *time=0;
        stack_mission.pop();
        //troca a textura do background
        //background.reset();
        //background->setTexture(std::make_shared<Texturazer>("assets/scripts/background2.tscp"));
        printf("entrou 2 roteiro, time =%0.2f\n",*time);
        
    }

}

//metodo que recebe o vector<wave>, e gerencia a missao
void World::mission_handler(std::list<mission_wave> *fase_script,float *time){

    vec3f_t str_aux;
    std::shared_ptr<Enemy> shr_ptr;
    //printf("now time is : %f\n",*time);
    for(int i = 0;i<fase_script->size();i++){

    if( (*fase_script->begin() ).time <= *time){

        //TODO fazer a logica de jogar de spawnar inimigos e chamar o vector pro colider
        //qualquer id fora 0 é um inimigo
        // e seu id corresponde a um modelo que vai ser criado usando o metodo
        //create_models que retornara um vec de struct com seus pontos
        //para depois inicializar os modelos e bota no vec entidade
        if((*fase_script->begin() ).id_enemy>0 && (*fase_script->begin() ).id_enemy<4){
            //usando str_aux para auxiliar a criação dos objetos inimigos lidos no arquivo txt pelo parser
            str_aux.x=(*fase_script->begin() ).x;
            str_aux.y=(*fase_script->begin() ).y;
            str_aux.z=0;

            //usando smartpointer para nao da merda     
            //aloca um novo smartpointer dentro do vetor
            shr_ptr = std::make_shared<Enemy>(str_aux,0,0,0.5,
                                                create_models((*fase_script->begin()).id_enemy)
                                                ,create_models((*fase_script->begin()).id_enemy));
            send_texture((*fase_script->begin()).id_enemy,shr_ptr);

            vec_entitys.push_back(shr_ptr);
            //printf("bool ta dentro = %d \n",vec_entitys[0]->tadentro());
            //libera o smartpointer e libera o espaco

        }

        // id =4 ou 5 caso especial dos chefoes
        if((*fase_script->begin() ).id_enemy==4 || (*fase_script->begin() ).id_enemy==5){

            //usa Classe do chefao para criar 
            //a create models pode ser usada ainda , pois ela so devolve o vector
            //de pontos para ser usado do modelo apenas

            //usando str_aux para auxiliar a criação dos objetos inimigos lidos no arquivo txt pelo parser
            str_aux.x=(*fase_script->begin() ).x;
            str_aux.y=(*fase_script->begin() ).y;
            str_aux.z=0;

            //usando smartpointer para nao da merda     
            //aloca um novo smartpointer dentro do vetor
            shr_ptr = std::make_shared<Enemy>(str_aux,0,0,0.5,
                                                create_models((*fase_script->begin()).id_enemy)
                                                ,create_models((*fase_script->begin()).id_enemy));
            send_texture((*fase_script->begin()).id_enemy,shr_ptr);
            vec_entitys.push_back(shr_ptr);
            //libera o smartpointer e libera o espaco


        }

        //id =0 é powerup
        if((*fase_script->begin() ).id_enemy==0){

            //TODO criar objeto PowerUP ou re-ultilizar o objeto Player//ou criar um tipo de 
            //de inimigo novo com id diferente
            
            //usando str_aux para auxiliar a criação dos objetos inimigos lidos no arquivo txt pelo parser
            str_aux.x=(*fase_script->begin() ).x;
            str_aux.y=(*fase_script->begin() ).y;
            str_aux.z=0;

            //usando smartpointer para nao da merda     
            //aloca um novo smartpointer dentro do vetor
            //trocar o pointer para powerup depois
            shr_ptr = std::make_shared<Enemy>(str_aux,0,0,0.5,
                                                create_models((*fase_script->begin()).id_enemy)
                                                ,create_models((*fase_script->begin()).id_enemy));
            send_texture((*fase_script->begin()).id_enemy,shr_ptr);
            vec_entitys.push_back(shr_ptr);
            //libera o smartpointer e libera o espaco


        }
        printf("tempo =%0.2f ,i.time=%0.2f , id=%d ,x=%0.2f ,y=%0.2f \n ",*time,(*fase_script->begin() ).time,(*fase_script->begin() ).id_enemy,(*fase_script->begin() ).x,(*fase_script->begin() ).y);

        //retira o elemento da lista.
        fase_script->pop_front();

    }


    }

}

World::World(){

    colisor= new Colider();
    initbackGround();
    initPlayer();
}

//metodo para enviar os objetos que estao na tela para serem tratados pelo Colider
std::vector<std::shared_ptr<Entidade>> World::send_to_colider(std::vector<std::shared_ptr<Entidade>> vec_hitbox){

//chama o colider


    return colisor->check_colison(vec_hitbox);  

}

//metodo para criar as coordenadas das hitbox e modelos para jogar dentro do vetor Entidades
std::vector<vec3f_t> World::create_models(int id){

    std::vector<vec3f_t> aux;

    vec3f_t batata;
    batata.x =0;
    batata.y =0;
    batata.z =0;

    //deixar aqui pronto um switch case que dentro de cada case
    //ja vai inicializar o tipo de inimigo, por ex:
    //id ==3 vai criar o inimigo tipo padrao,
    //botar para dentro do vetor aux os pontos do modelo
    // e devolver para o world no mission_handler criar o inimigo e botar no vetor de identidades;

    switch (id)
        {
        //powerup
        case 0:
            break;
        //inimigo normal
        case 1:
            !parse_model(&aux, "assets/scripts/inimigo_tipo1.mscp");
            break;

        //helicoptero que persegue
        case 2:
            !parse_model(&aux, "assets/scripts/inimigo_tipo2.mscp");
            break;

        // inimigo difernte
        case 3:
            !parse_model(&aux, "assets/scripts/inimigo_tipo3.mscp");
            break;

        //id = 4 é o chefao
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

void World::draw_vec_entitys(){

    std::vector<std::shared_ptr<Entidade>> to_colider;
    //printf("tamanho do vec entitys = %d \n",vec_entitys.size());
    //movo,atualizo e ordeno pro colider
    for(int x=0;x<vec_entitys.size();x++){

        if(vec_entitys.at(x)->getOnScreen()){
            to_colider.push_back(vec_entitys.at(x));
        }
        else{
            vec_entitys.erase(vec_entitys.begin()+x);
            x--;
        }
    }
    //printf("tamanho sendotocolider = %d \n",to_colider.size());
    //depois de ordenado, mandar pro colider
    vec_entitys = send_to_colider(to_colider);
    to_colider.clear();
    //printf("tamanho do vec entitys depois = %d \n",vec_entitys.size());

    for(int x=0;x<vec_entitys.size();x++)
        vec_entitys.at(x)->draw();

}

void World::initPlayer()
{
    std::vector<vec3f_t> vector;
    std::vector<GLuint> texture_vec;
    if (!parse_model(&vector, "assets/scripts/player.mscp"))
    {
        printf("DEU BOM NO FILE \n");
    }


    vec3f_t origin = {
        .x = 0,
        .y = 0,
        .z = 0};
    joga =  std::make_shared<Player>(origin, 0, 0.0f, 1.0f, vector, vector, texture_vec, 2);
    vec_entitys.push_back(joga);
}

void World::update_entitys(float *timer_count){

    int shot =0;
     // Updates the movements
    if(joga != nullptr) 
        shot = joga->updateOnKeyboard(keyboard);

    if (shot && *timer_count > 0.3)
    {
        *timer_count = 0;
        vec_entitys.push_back(std::shared_ptr<Shot>(joga->playerFire()));
    }

    for (int i = 0; i < vec_entitys.size(); i++)
    {
        vec_entitys.at(i)->move();
        vec_entitys.at(i)->updateModel();
    }
    //re ultilizando funcao ele nao vai se auto destruir seu corno desgrçado
    background->destroy();
}

void World::send_texture(int id, std::shared_ptr<Enemy> shr_ptr){

    // id =1, inimigo normal
    // id =3 ...
    switch (id)
    {
        case 0:
            break;
        case 1:
            shr_ptr-> setTexture(std::make_shared<Texturazer>("assets/scripts/inimigo_tipo1.tscp"));
            break;    
        case 2:
            shr_ptr-> setTexture(std::make_shared<Texturazer>("assets/scripts/inimigo_tipo2.tscp"));
            break;    
        case 3:
            shr_ptr-> setTexture(std::make_shared<Texturazer>("assets/scripts/inimigo_tipo3.tscp"));
            break;    
        case 4:
            shr_ptr-> setTexture(std::make_shared<Texturazer>("assets/scripts/chefao1.tscp"));
            break;    
        case 5:
            shr_ptr-> setTexture(std::make_shared<Texturazer>("assets/scripts/chefao2.tscp"));
            break;    
    } 



}

void World::initbackGround(){

    std::vector<vec3f_t> str_aux;
    vec3f_t p1 ={-256,224,-1};
    vec3f_t p2 ={256,224,-1};
    vec3f_t p3 ={256,-224,-1};
    vec3f_t p4 ={-256,-224,-1};
    vec3f_t p5 ={0,0,0};
    str_aux.push_back(p1);
    str_aux.push_back(p2);
    str_aux.push_back(p3);
    str_aux.push_back(p4);

    background = std::make_shared<Background>(p5,0,0,0.1,
                                                str_aux
                                                ,str_aux);
 
    background->setTexture(std::make_shared<Texturazer>("assets/scripts/background1.tscp"));
    vec_entitys.push_back(background);

}

//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

void World::Credits(){

}