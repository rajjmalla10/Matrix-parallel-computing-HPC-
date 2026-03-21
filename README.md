# Matrix-parallel-computing-HPC-
Parallel computing projects using MPI, Docker and Cloud

## What this project is?
It show case the Parellel matrix multiplication Using MPI, It showcase how a PC can disect a follwoing mathematical operation into small task and perform it on individual process and later on combine to present as a singular result.    
    
## What tools it uses? 
OpenMPI, Dockers, cloud

## why parellel matrix multiplication matters? 
Matric multiplication is fundamental operation in scientific computing, machine learning and HPC. Parallelizing it demonstrate core concept of distributed system at a practical level.

## Projects 
-[ ] Parellel Matrix multiplication with MPI
-[ ] COntainerzed with Docker
-[ ] Cloud Deployment


## How to complie and run. 
```bash
mpicc -o matrix_multiply src/matrix_multiply/matrix_multiply.c
mpirun -np 4 ./matrix_multiply
```

## Results 
Comming Soon.
