#ifndef _STATE_UP_H_
#define _STATE_UP_H_
#include"matrix.h"

Matrix setInitialCondition(int N, Matrix u);
void write_pgm(Matrix m_trix, int rowStart, int rowEnd, int colStart, int colEnd, int printEveryNPoints, char* file_name, int rows, int cols);
void step(double k, double h, Matrix tip1, Matrix ti, Matrix tim1);

#endif