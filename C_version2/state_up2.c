#include"matrix.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"initial_condition.h"
#include <omp.h>

Matrix setInitialCondition(int N, Matrix u) 
{   
    int row;
    int col;
 
    double sigma=0.01;
    double mu=0.5;
    for (int row=0; row<N; ++row) {
        for (int col=0; col<N; ++col) {
            double x = 1.0/(N-1)*row;
            double y = 1.0/(N-1)*col;
            u.data[row][col] = initialCondition(x,y);
        }
    }
    
    return u;
}

double getMaxAbs(Matrix matrix) 
{
    double maxVal = fabs(matrix.data[0][0]);
    for (int row=0; row<matrix.N; ++row) {
        for (int col=0; col<matrix.N; ++col) {
            if (fabs(matrix.data[row][col])>maxVal) {
                maxVal = fabs(matrix.data[row][col]);
            }
        }
    }
    return maxVal;
}


void write_pgm(Matrix m_trix, int rowStart, int rowEnd, int colStart, int colEnd, 
    int printEveryNPoints, char* file_name, int rows, int cols) 
{
    FILE* pgm;
    pgm = fopen(file_name, "wb"); 
    fprintf(pgm, "P2\n"); 
    fprintf(pgm, "%d %d\n", rows, cols);
    fprintf(pgm, "255\n");
    double max_val = getMaxAbs(m_trix);
    
    for (int row = rowStart; row <=rowEnd; row+=printEveryNPoints) 
    {
        for (int col = colStart; col <= colEnd; col+=printEveryNPoints) 
        {
            int input = ((m_trix.data[row][col]/max_val)*127+127);
            fprintf(pgm,"%d ", input);
        }
        fprintf(pgm, "\n");
    }
    fclose(pgm);
}

void step(double k, double h, Matrix tip1, Matrix ti, Matrix tim1) 
{
    int row;
    int col;
    double sTime = omp_get_wtime();
    for (row=1; row<(((tip1.N-1))); ++row) 
    {
        for (col=1; col<(tip1.N-1); ++col) 
        {
            tip1.data[row][col] = k*k/(h*h)*(ti.data[row-1][col]-4*ti.data[row][col]+
            ti.data[row+1][col]+ti.data[row][col-1]+ti.data[row][col+1])+2*
            ti.data[row][col]-tim1.data[row][col];
        }
    }
    double eTime = omp_get_wtime();
    printf("time: %f\n",eTime-sTime);
}