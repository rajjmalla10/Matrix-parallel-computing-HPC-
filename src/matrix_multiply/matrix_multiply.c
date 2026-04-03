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

int* matrix_multiplication(int* matrix_a, int* matrix_b,int chunks, int colm){
    int* local_b = (int*)malloc(sizeof(int)*chunks*colm);
    for(int i = 0; i < chunks; i++){
        for(int j = 0; j < colm; j++){
            local_b[i*colm+j]=0;
            for(int k = 0; k < colm; k++){
                local_b[i*colm+j] += matrix_a[i*colm+k] * matrix_b[k*colm+j]; 
        }
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
    int rows = 1000;
    int columns = 1000;
    int chunks = rows/size;
    int count = rows * columns;
    int* matrix_a = NULL;
    int* matrix_b = NULL;
    int* matrix_c = NULL;
    int* local_a = (int*)malloc(sizeof(int)*chunks*columns);
    matrix_b = (int*)malloc(sizeof(int)*count);   
    MPI_Barrier(MPI_COMM_WORLD);
    double start_time = MPI_Wtime();
 
    if(rank == root){

         matrix_a = matrix_allocation(rows,columns,count); 
         matrix_c = (int*)malloc(sizeof(int)*count); 

  

// SENDING ROWS OF MATRIX A TO ALL OTHER PROCESS
         for(int i = 0; i< count ; i++){
                 matrix_b[i] = i;
             }
   }
    MPI_Bcast(matrix_b,count,MPI_INT,root,MPI_COMM_WORLD);    
    MPI_Scatter(matrix_a,chunks*columns,MPI_INT,local_a,chunks*columns,MPI_INT,root,MPI_COMM_WORLD);
    int* local_c = matrix_multiplication(local_a,matrix_b,chunks,columns);
    MPI_Gather(local_c,chunks*columns,MPI_INT,matrix_c,chunks*columns,MPI_INT,root,MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    double end_time = MPI_Wtime();

    if(rank == root){
       

        printf("Time %f seconds\n", end_time-start_time);     
        free(matrix_a);
        free(matrix_c);
    }
    free(local_c);
    free(matrix_b);
    free(local_a);
    MPI_Finalize();
    return 0;
}
