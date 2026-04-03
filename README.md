# Matrix-parallel-computing-HPC-
Parallel computing projects using MPI, Docker and Cloud

## What this project is?
It show case the Parellel matrix multiplication Using MPI, It showcase how a PC can disect a follwoing mathematical operation into small task and perform it on individual process and later on combine to present as a singular result.    
    
## What tools it uses? 
OpenMPI, Dockers, cloud

## why parellel matrix multiplication matters? 
Matric multiplication is fundamental operation in scientific computing, machine learning and HPC. Parallelizing it demonstrate core concept of distributed system at a practical level.

## Recent Update 
Scaled the matrix from 1000x1000 matrix, add timing and scaling analysis. For 1 process the speedup was around 1x, for 2 it was 1.76x, for 3 it was around 2.37x and for 4 process it was around 3.05x.


## Projects 
-[x] Parellel Matrix multiplication with MPI
-[ ] COntainerzed with Docker
-[ ] Cloud Deployment


## How to complie and run. 
```bash
mpicc -o matrix_multiply src/matrix_multiply/matrix_multiply.c
mpirun -np 4 ./matrix_multiply
```
## Results 
1000x1000 Matrix Multiplication Scaling Analysis

| Processes | Time (seconds) | Speedup |
|-----------|---------------|---------|
| 1         | 3.364554      | 1x      |
| 2         | 1.909534      | 1.76x   |
| 3         | 1.421748      | 2.37x   |
| 4         | 1.104457      | 3.05x   |

Speedup follows Amdahl's Law — diminishing returns at higher process counts
due to communication overhead between processes.
