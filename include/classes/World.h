#ifndef __WORLD__
#define __WORLD__

#include "../parser.h"
#include "Enemy.h"
#include <bits/stdc++.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>

//classe mundo que vai gerenciar o roteiro das missoes e os objetos chamando as outras classes

class World{

private:
    std::queue<std::list<mission_wave>> stack_mission; 
    std::vector<Entidade> vec_hitbox;
    Enemy *enemy;
    //Powerup *power;
    // wave 1, wave 2 , wave 3


public:


    //botar os roteiros das missions na queue para poder usar a start_mission
    void initialize_script_mission();

    //metodo que initicializa as missões
    void start_mission(float *time);

    //metodo que trata as fases que estao no script
    void mission_handler(std::list<mission_wave> *fase_script,float *time);

    //metodo para enviar os objetos que estao na tela para serem tratados pelo Colider
    void send_to_colider(std::vector<Entidade> vec_hitboxs);

    //metodo para criar as coordenadas das hitbox e modelos para jogar dentro do vetor Entidades
    std::vector<vec3f_t> create_models(int id);

    //metodo menu 
    void show_menu();

    //E VAMOS DE CREDITOS FAMILIA
    void Credits();

};




#endif