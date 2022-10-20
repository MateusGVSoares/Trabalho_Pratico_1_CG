#include "algebra.h"

void print_matrix(const char *name, Matrix_t *target)
{

    printf("Matriz => %s [%d][%d]\n", name, target->row, target->col);

    for (int i = 0; i < target->row; i++)
    {
        for (int j = 0; j < target->col; j++)
            printf("[%0.1f]", target->mat[i][j]);
        printf("\n");
    }
}

void vec_to_row(Matrix_t *target, float *vec, int row)
{
    for (int i = 0; i < target->col; i++)
    {
        target->mat[row][i] = vec[i];
    }
}

void vec_to_matrix(Matrix_t *target, float *vec)
{
    for (int i = 0; i < target->row; i++)
    {
        for (int j = 0; j < target->col; j++)
        {
            target->mat[i][j] = vec[(i * target->row)+ j];
        }
    }
}

void freeMatrix(Matrix_t * target)
{
    for(int i =0; i < target->row; i++)
    {
       
        delete target->mat[i];
    }
    delete target->mat;
}

Matrix_t *alloc_matrix(int row, int col)
{
    Matrix_t *ret = new Matrix_t;

    ret->row = row;
    ret->col = col;
    ret->mat = new float *[row];

    for (int i = 0; i < row; i++)
    {
        ret->mat[i] = new float[col]();
    }

    return ret;
}

Matrix_t *multiply_matrix(Matrix_t matriz_1, Matrix_t matriz_2)
{
    if (matriz_1.col != matriz_2.row)
    {
        // Sem esse printf o código n funciona >_<
        return NULL;
    }

    // Gera uma matriz de result
    Matrix_t *result = alloc_matrix(matriz_1.row, matriz_2.col);

    // printf("Creating a [%d]x[%d] Matrix\n", result->row, result->col);

    // Multiplica matriz_1 por matriz_2
    for (int k = 0; k < result->row; k++)
    {
        for (int i = 0; i < result->col; i++)
        {
            for (int j = 0; j < matriz_1.col; j++)
            {
                result->mat[k][i] +=

                    matriz_1.mat[k][j] * matriz_2.mat[j][i];
            }
        }
    }

    // Retorna o resultado da multiplicacão
    return result;
}

