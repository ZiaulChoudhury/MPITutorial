#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
 
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    int root_rank = 0;
    int size = 0;
    int my_rank;
    int reduction_result = 0;
    int buffer;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    if(my_rank == root_rank)
	buffer = 10;
    MPI_Bcast(&buffer,1,MPI_INT,root_rank,MPI_COMM_WORLD);
    MPI_Reduce(&buffer, &reduction_result, 1, MPI_INT, MPI_SUM, root_rank, MPI_COMM_WORLD);
 
    if(my_rank == root_rank)
        printf("The sum of all ranks is %d.\n", reduction_result);
	
    MPI_Finalize(); 
    return EXIT_SUCCESS;
}

