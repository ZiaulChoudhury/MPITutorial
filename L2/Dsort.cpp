/**
 * @author RookieHPC
 * @brief Original source code at https://www.rookiehpc.com/mpi/docs/mpi_send.php
 **/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <stdlib.h> 
#include <time.h>

void swap(int *xp, int *yp)  
{  
    int temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}  
  
// A function to implement bubble sort  
void bubbleSort(int arr[], int n)  
{  
    int i, j;  
    for (i = 0; i < n-1; i++)      
      
    // Last i elements are already in place  
    for (j = 0; j < n-i-1; j++)  
        if (arr[j] > arr[j+1])  
            swap(&arr[j], &arr[j+1]);  
}

/**
 * @brief Illustrates how to send a message in a blocking fashion.
 * @details This program is meant to be run with 2 processes: a sender and a
 * receiver.
 **/
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv); 
    int size, rank;
    srand(time(NULL));
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    enum role_ranks { SENDER, RECEIVER }; 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   
    if(rank == 0) {
    	int bufferUnsorted[100];
	int bufferSorted[100];
	for(int i=0;i<100;i++)
		bufferUnsorted[i] = int(rand()%101) + 1;
	for(int i=1;i<11;i++)
		MPI_Send(bufferUnsorted+10*(i-1),10,MPI_INT,i,0,MPI_COMM_WORLD);
	for(int i=1;i<11;i++)
            	MPI_Recv(bufferSorted+10*(i-1), 10, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	printf(" Un Sorted \n");
	for(int i=0;i<10;i++)
		printf(" %d ", bufferUnsorted[i+20]);	
	printf("\n Sorted \n");	
	for(int i=0;i<10;i++)
		printf(" %d ", bufferSorted[i+20]);
    }
    else {
	    int received[10];
            MPI_Recv(received, 10, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	    bubbleSort(received,10);
	    MPI_Send(received, 10, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    	 
    MPI_Finalize(); 
    return EXIT_SUCCESS;
}

