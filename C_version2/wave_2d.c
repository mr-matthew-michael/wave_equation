#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"matrix.h"
#include"initial_condition.h"
#include<string.h> 
#include"state_up.h"
#include<omp.h> 

int main(int argc, char **argv) 
{
    double h = atof(argv[1]);
    double k = atof(argv[2]);
    double end_time = atof(argv[3]);
    int print_steps = atoi(argv[4]);
    int print_points = atoi(argv[5]);
    int prefix = 0;

    /*
    printf("h: %f, k: %f, end_time: %f, print_steps: %d, print_point: %d", 
        h, k, end_time, print_steps,print_points);
    */

    char* filenamePrefix = malloc(100);
    if(argc > 6)
    {
        filenamePrefix = argv[6];
        prefix = 1;
    } else free(filenamePrefix);

    if (k>=h)
    {
        printf("error, cfl condition violated");
        exit(0);//exit
    }

    int N = (int)(1.0/h) + 1;
    printf("N=%d\n",N);

    Matrix *states = malloc(sizeof(Matrix)*3);
    states[0] = create_matrix(N,N,N);
    states[0] = setInitialCondition(N,states[0]);
    states[1] = create_matrix(N,N,N);
    states[1] = setInitialCondition(N,states[1]);
    states[2] = create_matrix(N,N,N);
    states[2] = setInitialCondition(N,states[2]);

    char *filename = malloc(strlen(filenamePrefix) + 10);
    sprintf(filename, "%06d.pgm", 0);
    char *tmp = strdup(filename);
    strcpy(filename, filenamePrefix);
    strcat(filename,tmp);
    free(tmp);

    //printf("\n%s\n",filename);
    write_pgm(states[1], 0, N-1, 0, N-1, print_points,filename, 
        (int)ceil((float)N/print_points),(int)ceil((float)N/print_points));

    int steps = 1;
    double t = 0.0;
    while (t<=end_time) 
    {
        Matrix uk = states[(steps+1)%3];
        Matrix ukm1 = states[steps%3];
        Matrix ukm2 = states[(steps-1)%3];
        step(k,h,uk,ukm1,ukm2);

        if(steps%print_steps == 0) 
        {
            sprintf(filename, "%06d.pgm", steps/print_steps);
            if (prefix == 1) 
            {
                char *tmp = strdup(filename);
                strcpy(filename, filenamePrefix);
                strcat(filename,tmp);
                free(tmp);
            }
            printf("file name: %s, t = %f\n", filename, t);
            write_pgm(uk, 0, N-1, 0, N-1, print_points, filename, (int)ceil((float)N/print_points),
            (int)ceil((float)N/print_points) );
            printf("\n");
        }
        ++steps;
        t=k*steps;
        //free(uk);
        //free(ukm1);
        //free(ukm2)
    }

    for(int i = 0; i < 3; i++) 
    { 
        free_matrix(states[i]);
    }
}