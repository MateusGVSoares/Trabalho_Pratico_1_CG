#ifndef __AL__
#define __AL__

#include <string.h>
#include <iostream>
#include <math.h>
/// @brief Simboliza uma matriz NxM 
/// @param row Quantidade de linhas
/// @param col Quantidade de colunas
/// @param mat Conteúdo da estrutura 
typedef struct Matrix
{
    int row;
    int col;
    float **mat;
} Matrix_t;

void freeMatrix(Matrix_t * target);

// Copia o conteudo de um vetor para a matriz
void vec_to_matrix(Matrix_t *target, float *vec);

// Faz uma linha da matriz ser igual a um vetor
void vec_to_row(Matrix_t *target, float *vec, int row);

// Funcao para printar a matriz
void print_matrix(const char *name, Matrix_t *target);

// Realiza a multiplicacao de matrizes de matriz_1 por matriz_2 
// Retorna NULL se forem incompativeis
Matrix_t *multiply_matrix(Matrix_t matriz_1, Matrix_t matriz_2);

// Aloca dinamicamente uma estrutura de matriz rowxcol
// @param row Matrix Row
//@param col Matrix Col
Matrix_t *alloc_matrix(int row, int col);



#endif