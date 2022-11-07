//-----------------------------------------------------------------------------------------------------------------------
// Solving the Determinate of a Matrix using LU decomposition
//
// This program generates a random matrix of size NxN, which n is input in the terminal, the program then performs LU
// decomposition on the input matrix. The program then finds the determinate of the input by multiplying the diagonal elements
// of U together.
//
// Case 1  produces one matrix of a selectable size. If under 11x11 it prints this matrix, it then gives you the determinate
// and if a 3x3 also shows you a brute force calculation of the determinate as well.
//
// Case 2 times the time taken for the program to perform LU decomposition for each value of N up to a value input in the terminal,
// N and time taken, as well as log N and log time are saved to a text file so they can be plotted in GNUP Plot
//
// Author: Cameron Prince
//
// Date:04/11/22
// -----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "LU_Header.h"


int main(){

    int option;
    int n, row, col; //declaring variables //
    float **input, **u, **l; // declaring matrices //

    do{
        printf("******************************************************************\n");
        printf("Menu \n\n"
                   "1: Determinate of a single matrix"
                   "\t2: Produce graphs of N vs Time and Log N vs Log Time"
                   "\t\t0: Exit\n\n");

        scanf("%d", &option);
        printf("******************************************************************\n");

        switch(option){


            // Case for randomly generating a matrix and getting its determinate //
            case 1:{}

                printf("Enter an integer number for the n value of the generated nxn matrix:"); //Scans for value of N, plus sanity check//
                scanf("%d", &n);
                while(n<2){
                    printf("\nPlease enter a valid value\n\n");
                    scanf("%d", &n);
                }

                row=col=n;

                //Allocating Memory//

                input  = (float **)malloc(row * sizeof(float*));
                u  = (float **)malloc(row * sizeof(float*));
                l  = (float **)malloc(row * sizeof(float*));
                for(int i=0; i < row ; i++) {
                    input[i] = (float *)malloc(sizeof(float)*col);
                    u[i] = (float *)malloc(sizeof(float)*col);
                    l[i] = (float *)malloc(sizeof(float)*col);
                }

                do{
                    srand(time(0));  //Creates seed for random matrix//
                    for(int i = 0; i<n; i++){
                        for(int j = 0; j<n; j++){
                            input[i][j] = 1+rand()%9; //Put random number between 0-9 in matrix element//
                        }
                    }
                }while((input[0][0]*input[1][1]) == (input[1][0]*input[0][1])); //check to avoid generating with 0 det lead matrix//

                //If the input matrix is small (10x10 or smaller) it is shown in the terminal//
                if(n < 11){
                    printf("Input matrix =\n");
                    read_matrix(input, n, n);
                    }

                //If the input matrix is 3x3 the LU Decomp method is compared to a brute force method//
                if(n == 3){
                    float bute_det=(input[0][0]*((input[1][1]*input[2][2])-(input[2][1]*input[1][2])))-(input[0][1]*((input[1][0]*input[2][2])-(input[2][0]*input[1][2])))+(input[0][2]*((input[1][0]*input[2][1])-(input[2][0]*input[1][1])));
                    printf("Brute Force Det of input= %.1f\n\n", bute_det);
                }

                //LU DECOMP//
                LU_Decomp(input, u, l, n);


                //Det of input is the multiplication of the U diagonal in the doolittle method//

                double LU_det=1;
                for(int i = 0; i<n; i++){
                    LU_det=LU_det*u[i][i];
                }

                printf("LU Det of input= %.1f\n\n", LU_det);



                //Free Memory//
                for(int i = 0; i < row; i++){
                    free(input[i]);
                    free(u[i]);
                    free(l[i]);
                    }
                free(input);
                free(u);
                free(l);

                break;

            //Times the LU Decomp for each value of NxN up to a given value and stores the result in a text file//
            case 2:{}
                clock_t start, end;
                double cpu_time_used;

                //Scans value of max N with a sanity check//
                printf("Please enter the maximum value of N you want to time:");
                scanf("%d", &n);
                while(n<2){
                    printf("\nPlease enter a valid value\n\n");
                    scanf("%d", &n);
                }

                row = col = n;


                //Allocating Memory//

                input  = (float **)malloc(row * sizeof(float*));
                u  = (float **)malloc(row * sizeof(float*));
                l  = (float **)malloc(row * sizeof(float*));
                for(int i=0; i < row ; i++) {
                    input[i] = (float *)malloc(sizeof(float)*col);
                    u[i] = (float *)malloc(sizeof(float)*col);
                    l[i] = (float *)malloc(sizeof(float)*col);
                }


                /* Opening files for writing to be plotted later in gnuplot */
                FILE *data;
                data = fopen("NvsT.dat", "w");
                FILE *logr;
                logr = fopen("LogNvsLogT.dat", "w");


                fprintf(data, "#Table for N vs time plot\n");
                fprintf(data, "#N\t Time avg\n");
                fprintf(logr, "#Table for N vs time log plot\n");
                fprintf(logr, "#N\t Time log avg\n");


                for(int n=2; n<=row; n++){

                    printf("%d/%d", n, row);
                    do{
                        srand(time(0));  //Creates seed for random matrix//
                        for(int i = 0; i<n; i++){
                            for(int j = 0; j<n; j++){
                                input[i][j] = 1+rand()%9; //Put random number between 0-9 in matrix element//
                            }
                        }
                    }while((input[0][0]*input[1][1]) == (input[1][0]*input[0][1])); //check to avoid generating with 0 det lead matrix//


                    start = clock(); //Starts timer//

                    //LU DECOMP//
                    LU_Decomp(input, u, l, n);

                    end = clock(); //Ends Timer//

                    //Det of input is the multiplication of the U diagonal in the doolittle method//

                    double LU_det=1;
                    for(int i = 0; i<n; i++){
                        LU_det=LU_det*u[i][i];
                    }


                    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; //Calculates time//
                    cpu_time_used = cpu_time_used*1000; //change to millisecond


                    fprintf(data ,"%d\t%lf\n", n, cpu_time_used); //Prints unlogged results to file//

                    double logth= log(cpu_time_used);

                    fprintf(logr ,"%f\t%lf\n", log(n), logth); //Prints logged results to file//

                    printf("\r           ");

                }
                fclose(data);
                fclose(logr);
                printf("\ndone\n");

                //Free Memory//
                for(int i = 0; i < row; i++){
                    free(input[i]);
                    free(u[i]);
                    free(l[i]);
                    }
                free(input);
                free(u);
                free(l);

                break;

            case 0:
                printf("you have exited the program\n");
                return 0;

}

}while(option != 0);}
