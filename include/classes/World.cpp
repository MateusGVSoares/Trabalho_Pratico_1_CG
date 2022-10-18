#include "World.h"
#include "../parser.h"


void World::initialize_script_mission(){

    std::list<mission_wave> aux;

    //missao 1
    parse_mission(&aux,"roteiro1");
    this->stack_mission.push(aux);
    aux.clear();

    //missao 2
    parse_mission(&aux,"roteiro2");
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


    //    printf("now time is : %f\n",*time);
    for(auto i :*fase_script){

    if(i.time <= *time){

        //TODO fazer a logica de jogar de spawnar inimigos e chamar o vector pro colider

        printf("tempo =%0.2f ,i.time=%0.2f , id=%d ,x=%0.2f ,y=%0.2f \n ",*time,i.time,i.id_enemy,i.x,i.y);

    }

    }
    //consertar erro da retirada dos elementos;
    for(auto i:*fase_script){
        if(i.time<=*time)
            fase_script->pop_front();
    }

}

//metodo para enviar os objetos que estao na tela para serem tratados pelo Colider
void World::send_to_colider(std::list<Entidade> vec_hitboxs){

}

//metodo menu 
void World::show_menu(){

}

void World::Credits(){

}