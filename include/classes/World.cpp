#include "World.h"



void World::initialize_script_mission(){

    std::list<mission_wave> aux;

    //missao 1
    parse_mission(&aux,"include/arquivos_txt/roteiro1");
    this->stack_mission.push(aux);
    aux.clear();

    //missao 2
    parse_mission(&aux,"include/arquivos_txt/roteiro2");
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
        //printf("entrou 2 roteiro, time =%0.2f\n",*time);
        
    }

}

//metodo que recebe o vector<wave>, e gerencia a missao
void World::mission_handler(std::list<mission_wave> *fase_script,float *time){

    vec3f_t str_aux;
    std::shared_ptr<Enemy> shr_ptr;
    //    printf("now time is : %f\n",*time);
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
            shr_ptr = std::make_shared<Enemy>(str_aux,0,0,0,
                                                create_models((*fase_script->begin()).id_enemy)
                                                ,create_models((*fase_script->begin()).id_enemy));
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
            shr_ptr = std::make_shared<Enemy>(str_aux,0,0,0,
                                                create_models((*fase_script->begin()).id_enemy)
                                                ,create_models((*fase_script->begin()).id_enemy));
            vec_entitys.push_back(shr_ptr);
            //printf("bool ta dentro = %d \n",vec_entitys[0]->tadentro());
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
            shr_ptr = std::make_shared<Enemy>(str_aux,0,0,0,
                                                create_models((*fase_script->begin()).id_enemy)
                                                ,create_models((*fase_script->begin()).id_enemy));
            vec_entitys.push_back(shr_ptr);
            //printf("bool ta dentro = %d \n",vec_entitys[0]->tadentro());
            //libera o smartpointer e libera o espaco


        }
        //printf("tempo =%0.2f ,i.time=%0.2f , id=%d ,x=%0.2f ,y=%0.2f \n ",*time,(*fase_script->begin() ).time,(*fase_script->begin() ).id_enemy,(*fase_script->begin() ).x,(*fase_script->begin() ).y);

        //retira o elemento da lista.
        fase_script->pop_front();

    }


    }

}

//metodo para enviar os objetos que estao na tela para serem tratados pelo Colider
void World::send_to_colider(std::vector<std::unique_ptr<Entidade>> vec_hitboxs){

//chama o colider

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
        /* code */
        break;

    //inimigo normal
    case 1:
        /* code */
        break;

    //helicoptero que persegue
    case 2:
        /* code */
        break;

    // inimigo difernte
    case 3:
        /* code */
        break;

    //id = 4 é o chefao
    case 4:
        /* code */
        break;
    
    default:
        break;
    }

    aux.push_back(batata);
    return aux;
}


//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

void World::Credits(){

}