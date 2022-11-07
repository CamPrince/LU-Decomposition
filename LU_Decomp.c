//Performs LU decomposition (The Doolittle method) on an input square matrix of dimensions nxn.
//the results are then places in two already declared matrices. The Doolittle method consists of making the
//diagonal of L equal to 1 then using the fact that the product of L and U must equal the input to calculate
//the remaining elements of U and L.


void LU_Decomp(float **input, float **u, float **l, int n){

    float sum;

    //Puts 1 in the diagonal of L//
    for(int i = 0; i<n; i++){
            l[i][i] = 1;
            }

    //First row of U and First column of L//
    for(int j = 0; j<n; j++){
            u[0][j]=input[0][j];
            l[j][0]=input[j][0]/input[0][0];
    }


    for(int i=1; i<(n-1); i++){
        sum = 0;
        for(int t=0; t<=(i-1); t++){
            sum=sum+(l[i][t]*u[t][i]);
        }

        u[i][i]=input[i][i]-sum; //The Diagonal of U

        for(int j=i; j<n; j++){
            sum = 0;
            for(int t=0; t<=(i-1); t++){
                sum=sum+(l[i][t]*u[t][j]);
            }
            u[i][j]=input[i][j]-sum; //ith row of U

            sum = 0;
            for(int t=0; t<=(i-1); t++){
                sum=sum+(l[j][t]*u[t][i]);
            }

            l[j][i]=(input[j][i]-sum)/u[i][i]; // ith column of L
            }
    }

    sum = 0;
    for(int t=0; t<n-1; t++){
        sum=sum+(l[n-1][t]*u[t][n-1]);
            }


    u[n-1][n-1]=input[n-1][n-1]-sum; //n,n element of U

}
