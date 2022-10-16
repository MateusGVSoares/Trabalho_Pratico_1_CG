#ifndef __WORLD__
#define __WORLD__

#include "../parser.h"
#include <bits/stdc++.h>

// classe mundo que vai gerenciar o roteiro das missoes e os objetos chamando as outras classes

class World
{

private:
    std::queue<std::vector<mission_wave>> stack_mission;
    // wave 1, wave 2 , wave 3

public:
    World();

    // botar os roteiros das missions na queue para poder usar a start_mission
    void initialize_script_mission();

    // metodo que initicializa as missões
    void start_mission(std::queue<std::vector<mission_wave>> mission);

    // metodo que trata as fases que estao no script
    void mission_handler(std::vector<mission_wave> fase_script);

    // metodo para enviar os objetos que estao na tela para serem tratados pelo Colider
    void send_to_colider(std::vector<Entidade>);

    // metodo menu
    void show_menu();
};

#endif