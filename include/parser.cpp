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
    while (!file->eof())
    {
        file->getline(input_str, 30);
        sscanf(input_str, "%f,%f,%f", &aux.x, &aux.y, &aux.z);
        target->push_back(aux);
    }

    // DEBUG
    for (int i = 0; i < target->size(); i++)
    {
        printf("Vertices[%d] : %f, %f, %f \n", i, target->at(i).x, target->at(i).y, target->at(i).z);
    }

    // Label para limpar a memória
ERROR:
    delete input_str;
    delete file;


    return 0;
}