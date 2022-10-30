#include "Colider.h"

//metodo que calcula a colisao
bool Colider::try_colison(vec3f_t * origin ,std::vector<vec3f_t> *  v1 , std::vector<vec3f_t> * v2)
{
    vec3f_t diag_s = *origin,
            diag_e,
            edge_s,
            edge_e,
            move_vec;

    float limit = 0, det_1 = 0, det_2 = 0;

    int overlap = 0;

    for (int i = 0; i < v1->size(); i++)
    {

        // move_vec.x = 0;
        // move_vec.y = 0;
        diag_e = v1->at(i);

        for (int j = 0; j < v2->size(); j++)
        {
            edge_s = v2->at(j);
            edge_e = v2->at((j + 1) % v2->size());

            limit = (edge_e.x - edge_s.x) * (diag_s.y - diag_e.y) - (diag_s.x - diag_e.x) * (edge_e.y - edge_s.y);
            det_1 = ((edge_s.y - edge_e.y) * (diag_s.x - edge_s.x) + (edge_e.x - edge_s.x) * (diag_s.y - edge_s.y)) / limit;
            det_2 = ((diag_s.y - diag_e.y) * (diag_s.x - edge_s.x) + (diag_e.x - diag_s.x) * (diag_s.y - edge_s.y)) / limit;

            if (det_1 >= 0.0f && det_1 < 1.0f && det_2 >= 0.0f && det_2 < 1.0f)
            {
                // move_vec.x += (1.0f - det_1) * (diag_e.x - diag_s.x);
                // move_vec.y += (1.0f - det_1) * (diag_e.y - diag_s.y);
                // overlap = 1;
                //printf(" OCORREU COLISAO MEU\n");
                return 1 ;
            }

            // obj_1->origin.x += move_vec.x * -1;
            // obj_1->origin.y += move_vec.y * -1;
        }
    }
    // if (overlap)
    //     speed = 0;
    return 0;
}


//metodo que recebe as coisas que estao na tela
std::vector<std::shared_ptr<Entidade>> Colider::check_colison(std::vector<std::shared_ptr<Entidade>> vec_entitys){

    //vetor para alocar o q vai pro try_colisor ou so guardar em idle
    std::vector<std::shared_ptr<Entidade>> to_handle,idle;
    std::set<int> detect_col,no_col;

    for(int x=0;x< vec_entitys.size();x++){

        for(int z=x+1;z<vec_entitys.size();z++){

            switch (vec_entitys[x]->getId() + vec_entitys[z]->getId())
            {

            // colisao player com inimigo
            case 5:
                if(try_colison(vec_entitys.at(x)->getOrigin(),vec_entitys.at(x)->getHitbox(),vec_entitys.at(z)->getHitbox() ) ){
                    printf("colisao 5 de %d com %d \n",x,z);
                    detect_col.insert(x);
                    detect_col.insert(z);
                    }
                break;

            // colisao do tiro do player com inimigo
            case 6:
                if(try_colison(vec_entitys.at(x)->getOrigin(),vec_entitys.at(x)->getHitbox(),vec_entitys.at(z)->getHitbox() ) ){
                    printf("colisao 6 de %d com %d \n",x,z);
                    detect_col.insert(x);
                    detect_col.insert(z);
                    }
                break;

            //  player com tiro do inimigo
            case 9:
                if(try_colison(vec_entitys.at(x)->getOrigin(),vec_entitys.at(x)->getHitbox(),vec_entitys.at(z)->getHitbox() ) ){
                    printf("colisao 9 de %d com %d \n",x,z);
                    detect_col.insert(x);
                    detect_col.insert(z);
                    }
                break;

            case 17:
            // colisao do player com powerup pois a soma sempre será igual a 17
                if(try_colison(vec_entitys.at(x)->getOrigin(),vec_entitys.at(x)->getHitbox(),vec_entitys.at(z)->getHitbox() ) ){
                    printf("colisao 17 de %d com %d \n",x,z);
                        detect_col.insert(x);
                        detect_col.insert(z);
                        /*
                            if(vec_entitys[x]->getId() ==16)
                                //do powerup
                            else
                                //do powerup
                        */
                    }
                break;

            }


        }

        if(!detect_col.count(x))
            no_col.insert(x);

    }

    for(auto z: detect_col)
        to_handle.push_back(vec_entitys.at(z));
    

    for(auto z:no_col)
        idle.push_back(vec_entitys.at(z));


    //bota no vetor handle, apenas os que tiveam colisao
    //chama o handler para tratar as colisoes
    //ele vai devolver o que for feito. Ex se for para destruir devolverá faltando aquele ponteiro
    to_handle = handle_colison(to_handle);

    //coloca o q sobrou dentro do idle
    for(int x=0;x<to_handle.size();x++)
        idle.push_back(to_handle.at(x));

    //limpa o handle
    to_handle.clear();

    //devolve o que sobrou
    return idle;

}

//metodo que trata as flags para ser tradado os eventos

//metodos de tratamento:
//tiro player-> inimigo      //tiro inimigo->player
//tiro player->tiro inimigo  //player -> powerups


std::vector<std::shared_ptr<Entidade>> Colider::handle_colison(std::vector<std::shared_ptr<Entidade>> vec_entitys){

    for(int x=0;x<vec_entitys.size();x++){
        //chamar o metodo padrao de destruicao das coisas que vai ser implementado pela Entidade
        //
        if(vec_entitys.at(x)->destroy()){
            vec_entitys.erase(vec_entitys.begin()+x);
            x--;
        }
            
    }



    return vec_entitys;

}
