#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Matrix create_matrix (int n, unsigned row, unsigned col) {
    Matrix m_trix;
    m_trix.N = n;
    m_trix.columns = col;
    m_trix.rows = row;
    m_trix.data =  malloc(row * sizeof(double));
    
    for (int i = 0; i < row; i++) {
        m_trix.data[i] =  calloc(col, sizeof(double));
    }
    return m_trix;
}

void print_matrix(Matrix matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.columns; j++){
            printf("%f ",matrix.data[i][j]);
        }
        printf("\n");
    }
}

void  free_matrix (Matrix matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        free(matrix.data[i]);
    }
    free(matrix.data);
}
