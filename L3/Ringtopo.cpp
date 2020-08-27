#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <stdlib.h> 
#include <time.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv); 
    int size, rank;
    srand(time(NULL));
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    enum role_ranks { SENDER, RECEIVER }; 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int token = rank;
  
    if(rank == 0) {
	     int sum;
	     MPI_Send(&token,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);	
             MPI_Recv(&sum, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	     printf("Step%d \n", rank);
	     printf("\nSum = %d ", sum); 
	
    }
    else {
	     int recvToken;
             MPI_Recv(&recvToken, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	     token += recvToken;
	     printf("Step%d \n", rank);
	     MPI_Send(&token, 1, MPI_INT, (rank+1)%size, 0, MPI_COMM_WORLD);
    }
    	 
    MPI_Finalize(); 
    return EXIT_SUCCESS;
}

