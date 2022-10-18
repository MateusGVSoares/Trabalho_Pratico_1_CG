#include "World.h"



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

    vec3f_t str_aux;
    //    printf("now time is : %f\n",*time);
    for(auto i :*fase_script){

    if(i.time <= *time){

        //TODO fazer a logica de jogar de spawnar inimigos e chamar o vector pro colider
        //qualquer id fora 0 é um inimigo
        // e seu id corresponde a um modelo que vai ser criado usando o metodo
        //create_models que retornara um vec de struct com seus pontos
        //para depois inicializar os modelos e bota no vec entidade
        if(i.id_enemy>0 && i.id_enemy<4){
            str_aux.x=i.x;
            str_aux.y=i.y;
            str_aux.z=0;

            //enemy = new Enemy(str_aux,0,0,0,create_models(i.id_enemy),create_models(i.id_enemy));
            //vec_hitbox.push_back(*enemy);
            //TODO ver uma forma de liberar o enemy que esta no ponteiro de world
            //free enemy;
        }

        // id =4 ou 5 caso especial dos chefoes
        if(i.id_enemy==4 || i.id_enemy==5){

            //usa Classe do chefao para criar 
            //a create models pode ser usada ainda , pois ela so devolve o vector
            //de pontos para ser usado do modelo apenas

        }

        //id =0 é powerup
        if(i.id_enemy==0){

            //TODO criar objeto PowerUP ou re-ultilizar o objeto Player

        }
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
void World::send_to_colider(std::vector<Entidade> vec_hitboxs){



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
    case 1:
        /* code */
        break;

    case 2:
        /* code */
        break;

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

//metodo menu 
void World::show_menu(){

}
//aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

void World::Credits(){

}