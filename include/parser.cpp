#include "parser.h"


// Parser para modelo de arquivo
int parse_model(std::vector<vec3f_t> * target,const char *file_name)
{
    char *input_str = (char *)malloc(sizeof(char) * 31);
    std::ifstream *file = new std::ifstream();
    vec3f_t aux = {0};
    int i = 0;

    file->open(file_name, std::ios::in);

    // Verifica se o arquivo está aberto
    if (!file->is_open())
        goto ERROR;

    // Verifica se o arquivo está vazio
    if (!file->eof())
    {
        file->getline(input_str, 30);

        if (strcmp("MODEL", input_str))
        {
            delete input_str;
            delete file;
            return 1;
        }
    }
    else
        goto ERROR;

  
    // Lê o modelo do arquivo 
    while (file->peek()!=EOF)
    {
        file->getline(input_str, 30);
        sscanf(input_str, "%f,%f,%f", &aux.x, &aux.y, &aux.z);
        target->push_back(aux);
    }

    // DEBUG 
    /*
    for (int i = 0; i < target->size(); i++)
    {
        printf("Vertices[%d] : %f, %f, %f \n", i, target->at(i).x, target->at(i).y, target->at(i).z);
    }
    */

    // Label para limpar a memória
ERROR:
    delete input_str;
    delete file;


    return 0;
}
//             3     logo terao 3 triplas 1:id tipo de inimigo,2:coordenada x,3:cordenada y;
//tipo: tempo;quantia_de_objetos;sequencia de triplas;

// Parser para modelo de arquivo
int parse_mission(std::list<mission_wave> * target,const char *file_name)
{
    char *input_str = (char *)malloc(sizeof(char) * 200);
    std::ifstream *file = new std::ifstream();
    mission_wave aux = {0};
    int i = 0,carry=0; 

    file->open(file_name, std::ios::in);

    // Verifica se o arquivo está aberto
    if (!file->is_open())
        goto ERROR;

    // Verifica se o arquivo está vazio
    if (!file->eof())
    {
        file->getline(input_str,100);

        if (strcmp("ROTEIRO", input_str))
        {
            delete input_str;
            delete file;
            return 1;
        }
    }
    else
        goto ERROR;

  
    // Lê o modelo do arquivo
    while (file->peek()!=EOF)
    {
        file->getline(input_str, 100,';');
        sscanf(input_str, "%f,%d", &aux.time, &carry);
        for(int x=0;x<carry;x++){
            file->getline(input_str, 100,',');
            sscanf(input_str, "%d %f %f,", &aux.id_enemy, &aux.x, &aux.y);
            target->push_back(aux);
        }   
        file->getline(input_str, 100);
    }

    // DEBUG
    for (auto i:*target)
    {
        printf("wave[] id=%d : x=%f, y=%f, time=%f \n" ,i.id_enemy, i.x, i.y, i.time);
    }

    // Label para limpar a memória
ERROR:
    delete input_str;
    delete file;


    return 0;
}

int parser_texture(std::vector<GLuint> *target,std::vector<std::pair<GLfloat,GLfloat>> *target2,const char *file_name){

    char *input_str = (char *)malloc(sizeof(char) * 31);
    std::ifstream *file = new std::ifstream();
    float faux,saux;
    int n_coordenadas;
    int i = 0;
    const char * nome;

    file->open(file_name, std::ios::in);
    // Verifica se o arquivo está aberto
    if (!file->is_open())
        goto ERROR;

    // Verifica se o arquivo está vazio
    if (!file->eof())
    {
        file->getline(input_str, 30);
        if (strcmp("TEXTURE_PLAYER", input_str))
        {
            delete input_str;
            delete file;
            return 1;
        }
    }
    else
        goto ERROR;


    // Lê o modelo do arquivo
    while (file->peek()!=EOF)
    {
        file->getline(input_str, 30,';');
        sscanf(input_str, "%d;", &n_coordenadas);
        for(int x=0;x<n_coordenadas;x++){
            file->getline(input_str, 30,';');
            sscanf(input_str, "%f,%f", &faux,&saux);
            //passa os pares de coordenadas para o vector por refencia
            target2->push_back(std::make_pair(faux,saux));

        }   
        //pula uma linha pq Deus quis
        file->getline(input_str, 50);
        //pega o nome do arquivo que ta na pasta
        file->getline(input_str, 100);
        //cria ID bota no vector de id passado por referencia
        printf(" ANTES DO IDTEXTURE\n");
        GLuint idTextura = SOIL_load_OGL_texture("textura_teste.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
        printf(" DEPOIS DO IDTEXTURE\n");
        if(idTextura == 0){
            printf("Erro do SOIL:  %s\n", SOIL_last_result());
        }
        target->push_back(idTextura);
    }


ERROR:
    delete input_str;
    delete file;


    return 0;
}