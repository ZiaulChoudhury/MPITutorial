#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <stdlib.h> 
#include <time.h>
#include <math.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv); 
    int size, rank;
    srand(time(NULL));
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    enum role_ranks { SENDER, RECEIVER }; 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int token = rank;
    if(rank == 1) 
    {
	     int leftTreeSum;
	     int rightTreeSum;
             int nodeSum;
             MPI_Recv(&leftTreeSum,  1, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
             MPI_Recv(&rightTreeSum, 1, MPI_INT, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	     nodeSum = token + leftTreeSum + rightTreeSum;
	     printf("Step %d \n", (int)log2(rank));
	     printf("Sum %d ", nodeSum);
    }
    else if(rank > 1 && rank < size/2){
	     int leftTreeSum;
             int rightTreeSum;
             int nodeSum;
             MPI_Recv(&leftTreeSum,  1, MPI_INT, 2*rank,   0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
             MPI_Recv(&rightTreeSum, 1, MPI_INT, 2*rank+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
             nodeSum = token + leftTreeSum + rightTreeSum;
	     MPI_Send(&nodeSum,1,MPI_INT,(int)(rank/2),0,MPI_COMM_WORLD);	      
	     printf("Step %d \n", (int)log2(rank));
    }
    else if(rank >= size/2){
	     printf("Step %d \n", (int)log2(rank));
	     MPI_Send(&token,1,MPI_INT,(int)(rank/2),0,MPI_COMM_WORLD);;
    }
    MPI_Finalize(); 
    return EXIT_SUCCESS;
}

