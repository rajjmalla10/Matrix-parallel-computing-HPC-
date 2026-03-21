#include <stdio.h> 
#include <stdlib.h>
#include <mpi.h>

int* matrix_allocation(int rows, int coln,int count){
    int* matrix_a = (int*)malloc(sizeof(int)*count);
    for(int i = 0; i<rows;i++){
        for(int j = 0; j<coln;j++){
            matrix_a[i*coln+j] = i*coln+j;
    }
    }
    return matrix_a;
}

int* matrix_multiplication(int* matrix_a, int* matrix_b, int colm){
    int* local_b = (int*)malloc(sizeof(int)*colm);
    for(int i = 0; i < colm; i++){
        local_b[i] = 0;
        for(int j = 0; j < colm; j++){
            local_b[i] += matrix_a[j] * matrix_b[j*colm+i]; 
        }
    }
    return local_b;
}


int main(int argc, char** argv){
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int root = 0;
    int rows = 4;
    int columns = 4;
    int chunks = 1;
    int count = rows * columns;
    int* matrix_a = NULL;
    int* matrix_b = NULL;
    int* matrix_c = NULL;
    MPI_Barrier(MPI_COMM_WORLD);
    int* local_a = (int*)malloc(sizeof(int)*columns);
    if(rank == root){
        matrix_a = matrix_allocation(rows,columns,count); 
        matrix_c = (int*)malloc(sizeof(int)*count); 
        // SENDING ROWS OF MATRIX A TO ALL OTHER PROCESS
   }
    matrix_b = matrix_allocation(rows,columns,count);
    MPI_Bcast(matrix_b,count,MPI_INT,root,MPI_COMM_WORLD);    
    MPI_Scatter(matrix_a,columns,MPI_INT,local_a,columns,MPI_INT,root,MPI_COMM_WORLD);
    int* local_c = matrix_multiplication(local_a,matrix_b,columns);
    MPI_Gather(local_c,columns,MPI_INT,matrix_c,columns,MPI_INT,root,MPI_COMM_WORLD);
    

    if(rank == root){
        for(int i = 0; i<rows;i++){
            for(int j = 0; j<columns;j++){
                printf("%d " , matrix_c[i*columns+j]);   
            }
             printf("\n");
        }
        free(matrix_a);
        free(matrix_c);
    }
    free(local_c);
    free(matrix_b);
    free(local_a);
    MPI_Finalize();
    return 0;
}
