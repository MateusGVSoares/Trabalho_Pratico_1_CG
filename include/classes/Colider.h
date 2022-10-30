#ifndef __COLIDER__
#define __COLIDER__

#include <vector>
#include <set>
#include "Entidade.h"
#include "../algebra.h"
//Classe Colider que vai ser responsavel de chamar a colisão
//e decidir o que sera feito na hora da colisão
// flags
//  1  = player
//  2  = tiro do player
//  4  = inimigo 
//  8  = tiro do inimigo
//  16  = power ups
// usar smartpointer
class Colider  //: Hitbox
{

public:

//metodo que recebe as coisas que estao na tela(vindo da classe WORLD)

std::vector<std::shared_ptr<Entidade>> check_colison(std::vector<std::shared_ptr<Entidade>> vec_hitboxes);

bool try_colison(vec3f_t * origin ,std::vector<vec3f_t> *  v1 , std::vector<vec3f_t> * v2);

//metodo que trata as flags para ser tradado os eventos
std::vector<std::shared_ptr<Entidade>> handle_colison(std::vector<std::shared_ptr<Entidade>> vec_hitboxes);

};





#endif
