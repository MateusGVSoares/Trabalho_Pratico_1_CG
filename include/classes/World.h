#ifndef __WORLD__
#define __WORLD__

#include "../parser.h"
#include "Enemy.h"
#include "Colider.h"
#include "Player.h"
#include "Boss.h"
#include "Background.h"
#include "Spaceships.h"
#include "../Text.h"
#include <vector>
#include <list>
#include <queue>

// classe mundo que vai gerenciar o roteiro das missoes e os objetos chamando as outras classes

class World
{

private:
    int troca = 0;

    std::queue<std::list<mission_wave>> stack_mission;
    // usar smartpointer
    std::vector<std::shared_ptr<Entidade>> vec_entitys;
    // Powerup *power;
    //  carrega o objeto colider para fazer o tratamento das colisoes
    Colider *colisor;
    std::shared_ptr<Player> actual_player;
    std::shared_ptr<Boss>  actual_boss;
    std::shared_ptr<Background> background;

public:
    World();

    void drawFancyStuff();

    // botar os roteiros das missions na queue para poder usar a start_mission
    void initialize_script_mission();

    // metodo que initicializa as missões
    void start_mission(float *time);

    // metodo que trata as fases que estao no script
    void mission_handler(std::list<mission_wave> *fase_script, float *time);

    // metodo para enviar os objetos que estao na tela para serem tratados pelo Colider
    std::vector<std::shared_ptr<Entidade>> send_to_colider(std::vector<std::shared_ptr<Entidade>> vec_hitboxs);

    // metodo para criar as coordenadas das hitbox e modelos para jogar dentro do vetor Entidades
    std::vector<vec3f_t> create_models(int id);

    // carrega o objeto textura dos inimigos criados
    void send_texture(int id, std::shared_ptr<Enemy> shr_ptr);

    // atualiza todas as entidades presentes na tela
    void update_entitys(float *timer_count);

    // inicializa o player
    void initPlayer();

    // inicializa o background
    void initbackGround();

    // E VAMOS DE CREDITOS FAMILIA
    void Credits();

    // Desenhar todos as entidades que estão no vector de entidade que estão na tela e vivos
    void draw_vec_entitys();
};

#endif
