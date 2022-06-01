#ifndef _MATRIX_H_
#define _MATRIX_H_

typedef struct matrix {
    int N;
    unsigned rows;
    unsigned columns; 
    double **data;
}Matrix;

Matrix create_matrix (int n, unsigned row, unsigned col);

void print_matrix(Matrix matrix);

void free_matrix(Matrix matrix);

#endif