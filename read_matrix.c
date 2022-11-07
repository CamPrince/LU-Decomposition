//reads a 2D array of floats, N(row)xM(col), and prints the result to the terminal//

#include <stdio.h>

void read_matrix(float **arr,int row, int col){
    for (int i=0 ; i<row; ++i){ //loop through rows//
        printf("\n");
        for (int j=0 ; j<col; ++j){ //loops through columns//
            printf("%.2f ", arr[i][j]); //prints value to 2 sig fig//
        }
    }
    printf("\n\n");
}
