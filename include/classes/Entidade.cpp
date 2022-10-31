#include "Entidade.h"

Entidade::Entidade(vec3f_t origin, float angle, float velocidade)
{
    this->origin = origin;
    this->angle = angle;
    this->velocidade = velocidade;
    this->alive = 1;
    this->timer_control_texture = 0;
    this->const_anim_texture = 1.0 / 5.0;
    this->timer = 0;
    this->cont_stage_tex = 0;
    this->on_screen = 1;
}

bool Entidade::getOnScreen()
{
    return this->on_screen;
}

void Entidade::setTexture(std::shared_ptr<Texturazer> target)
{

    this->texture = target;
}

void Entidade::setConst()
{

    this->cont_stage_tex++;
}

float Entidade::getTimer()
{

    return this->timer;
}

int Entidade::getId()
{
    return this->id;
}

void Entidade::setId(int id)
{
    this->id = id;
}

vec3f_t *Entidade::getOrigin()
{
    return &this->origin;
}

void Entidade::updateModel()
{
    glPushMatrix();
    glTranslatef(this->origin.x, this->origin.y, this->origin.z);
    glRotatef(this->angle, 0, 0, 1);

    bool aux_x_col = 0, aux_y_col = 0;

    // Obtem a transformacao
    float *matrix = new float[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);

    // Constroi uma matriz para a transformacao
    Matrix_t *transform = alloc_matrix(4, 4);
    vec_to_matrix(transform, matrix);

    for (int i = 0; i < 4; i++)
    {
        // Corrige o componente de translação para a terceira coluna
        transform->mat[i][3] = transform->mat[3][i];
        transform->mat[3][i] = 0;
    }

    // print_matrix("Tranformation Matrix",transform);

    // Constroi uma matriz para os pontos
    Matrix_t *point = alloc_matrix(4, 1);

    Matrix_t *result = NULL;

    this->on_screen = this->border_x_col = this->border_y_col = 0;

    for (int i = 0; i < this->box_model.size(); i++)
    {
        aux_x_col = 0;
        aux_y_col = 0;

        // Pega os pontos do modelo de hit_box na origem
        point->mat[0][0] = this->box_model[i].x;
        point->mat[1][0] = this->box_model[i].y;
        point->mat[2][0] = this->box_model[i].z;
        point->mat[3][0] = 1;

        // Realiza as transformacoes e salva na hit_box
        result = multiply_matrix(*transform, *point);

        //  if(result != NULL)
        // {
        //     print_matrix("Resultado",result);
        // }

        this->hit_box[i].x = result->mat[0][0];
        this->hit_box[i].y = result->mat[1][0];
        this->hit_box[i].z = result->mat[2][0];

        freeMatrix(result);

        // if(result == NULL)
        // {
        //     std::cout << "Freed !! \n";
        // }

        if ((this->hit_box[i].x >= max_x) || (this->hit_box[i].x <= -max_x))
        {
            this->border_x_col = 1;
            aux_x_col = 1;
        }

        if ((this->hit_box[i].y >= max_y) || (this->hit_box[i].y <= -max_y))
        {
            this->border_y_col = 1;
            aux_y_col = 1;
        }

        if ((!aux_x_col) && (!aux_y_col))
        {
            this->on_screen = 1;
        }
    }

    glPopMatrix();

    // Free the memory allocated
    delete matrix;
    freeMatrix(transform);
    freeMatrix(point);
}

std::vector<vec3f_t> *Entidade::getHitbox()
{
    return &this->hit_box;
}