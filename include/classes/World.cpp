#include "World.h"
#include "../parser.h"

World::World(){

};

void World::initialize_script_mission()
{

    std::vector<mission_wave> aux;

    // missao 1
    parse_mission(&aux, "roteiro1");
    this->stack_mission.push(aux);
    aux.clear();

    // missao 2
    parse_mission(&aux, "roteiro2");
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

    // TODO: TAVA DANDO ERRO ;-;
    // delete aux;
}

void World::start_mission(std::queue<std::vector<mission_wave>> script)
{

    // criamos um vetor auxiliar para retirar os vetores(vetor=o roteiro de uma fase) que estao na queue
    std::vector<mission_wave> aux;

    // enquanto a queue tiver elementos ira rodar o vetor que contem o roteiro da missao
    while (!script.empty())
    {
        aux = script.front();
        script.pop();

        // TODO logica de spawnar inimigos e controle de tempo
        // criar metodo que faz o controle da missao e chamar aqui

        mission_handler(aux);
        aux.clear();
    }
}

// metodo que recebe o vector<wave>, e gerencia a missao
void World::mission_handler(std::vector<mission_wave> fase_script)
{
}

// metodo para enviar os objetos que estao na tela para serem tratados pelo Colider
void World::send_to_colider(std::vector<Entidade>)
{
}

// metodo menu
void World::show_menu()
{
}